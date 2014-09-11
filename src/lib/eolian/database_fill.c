#include "eo_parser.h"

static int
_func_error(Eolian_Class *cl, Eolian_Implement *impl)
{
   ERR("Error - %s%s not known in class %s", impl->full_name,
       eolian_class_name_get(cl), (impl->is_prop_get ? ".get"
              : (impl->is_prop_set ? ".set" : "")));
   return -1;
}

static Eina_Bool
_get_impl_func(Eolian_Class *cl, Eolian_Implement *impl,
               Eolian_Function_Type ftype, Eolian_Function **foo_id)
{
   size_t cllen = strlen(cl->full_name);
   size_t imlen = strlen(impl->full_name);
   const char *imstr = impl->full_name;
   *foo_id = NULL;
   if (imstr[0] == '.')
     ++imstr;
   else if ((imlen > (cllen + 1)) && (*(imstr + cllen) == '.')
        && !strncmp(imstr, cl->full_name, cllen))
     imstr += cllen + 1;
   else
     return EINA_TRUE;
   if (strchr(imstr, '.'))
     return EINA_FALSE;
   impl->klass = cl;
   *foo_id = (Eolian_Function*)eolian_class_function_get_by_name(cl, imstr,
                                                                 ftype);
   impl->foo_id = *foo_id;
   return !!*foo_id;
}

static void
_write_impl(Eolian_Function *fid, Eolian_Implement *impl)
{
   if (impl->is_prop_set)
     fid->set_impl = impl;
   else if (impl->is_prop_get)
     fid->get_impl = impl;
   else
     fid->get_impl = fid->set_impl = impl;
}

static int
_db_fill_implement(Eolian_Class *cl, Eolian_Implement *impl)
{
   const char *impl_name = impl->full_name;

   Eolian_Function *foo_id;
   Eolian_Function_Type ftype = EOLIAN_UNRESOLVED;

   if (impl->is_prop_get)
     ftype = EOLIAN_PROP_GET;
   else if (impl->is_prop_set)
     ftype = EOLIAN_PROP_SET;

   if (impl->is_virtual)
     {
        foo_id = (Eolian_Function*)eolian_class_function_get_by_name(cl,
          impl_name, ftype);
        if (!foo_id)
          return _func_error(cl, impl);
        if (impl->is_prop_set)
          foo_id->set_virtual_pure = EINA_TRUE;
        else
          foo_id->get_virtual_pure = EINA_TRUE;

        impl->full_name = eina_stringshare_printf("%s.%s", cl->full_name,
                                                  impl_name);
        eina_stringshare_del(impl_name);
        impl_name = impl->full_name;

        _write_impl(foo_id, impl);
     }
   else if (impl->is_auto)
     {
        if (!_get_impl_func(cl, impl, ftype, &foo_id))
          return _func_error(cl, impl);
        if (!foo_id)
          goto pasttags;
        if (impl->is_prop_set)
          foo_id->set_auto = EINA_TRUE;
        else
          foo_id->get_auto = EINA_TRUE;

        _write_impl(foo_id, impl);
     }
   else if (impl->is_empty)
     {
        if (!_get_impl_func(cl, impl, ftype, &foo_id))
          return _func_error(cl, impl);
        if (!foo_id)
          goto pasttags;
        if (impl->is_prop_set)
          foo_id->set_empty = EINA_TRUE;
        else
          foo_id->get_empty = EINA_TRUE;

        _write_impl(foo_id, impl);
     }
   else if (impl->is_class_ctor)
     {
        cl->class_ctor_enable = EINA_TRUE;
        return 1;
     }
   else if (impl->is_class_dtor)
     {
        cl->class_dtor_enable = EINA_TRUE;
        return 1;
     }
   else if (!_get_impl_func(cl, impl, ftype, &foo_id))
     return _func_error(cl, impl);

pasttags:
   if (impl_name[0] == '.')
     {
        impl->full_name = eina_stringshare_printf("%s%s", cl->full_name,
                                                  impl_name);
        eina_stringshare_del(impl_name);
     }

   cl->implements = eina_list_append(cl->implements, impl);
   return 0;
}

static void
_db_build_implement(Eolian_Class *cl, Eolian_Function *foo_id)
{
   if (foo_id->type == EOLIAN_PROP_SET)
     {
        if (foo_id->set_impl) return;
     }
   else if (foo_id->type == EOLIAN_PROP_GET)
     {
        if (foo_id->get_impl) return;
     }
   else if (foo_id->get_impl && foo_id->set_impl) return;

   Eolian_Implement *impl = calloc(1, sizeof(Eolian_Implement));

   if (foo_id->type == EOLIAN_PROP_SET)
     impl->base = foo_id->set_base;
   else
     impl->base = foo_id->base;
   eina_stringshare_ref(impl->base.file);

   impl->klass = cl;
   impl->foo_id = foo_id;
   impl->full_name = eina_stringshare_printf("%s.%s", cl->full_name,
                                             foo_id->name);

   if (foo_id->type == EOLIAN_PROPERTY)
     {
        if (foo_id->get_impl)
          {
             impl->is_prop_set = EINA_TRUE;
             foo_id->set_impl = impl;
          }
        else if (foo_id->set_impl)
          {
             impl->is_prop_get = EINA_TRUE;
             foo_id->get_impl = impl;
          }
        else
          foo_id->get_impl = foo_id->set_impl = impl;
     }
   else if (foo_id->type == EOLIAN_PROP_SET)
     {
        impl->is_prop_set = EINA_TRUE;
        foo_id->set_impl = impl;
     }
   else if (foo_id->type == EOLIAN_PROP_GET)
     {
        impl->is_prop_get = EINA_TRUE;
        foo_id->get_impl = impl;
     }
   else
     foo_id->get_impl = foo_id->set_impl = impl;

   cl->implements = eina_list_append(cl->implements, impl);
}

static Eina_Bool
_db_fill_implements(Eolian_Class *cl, Eo_Class_Def *kls)
{
   Eolian_Implement *impl;
   Eolian_Function *foo_id;
   Eina_List *l;

   EINA_LIST_FOREACH(kls->implements, l, impl)
     {
        int ret = _db_fill_implement(cl, impl);
        if (ret < 0) return EINA_FALSE;
        if (ret > 0) continue;
        eina_list_data_set(l, NULL); /* prevent double free */
     }

   EINA_LIST_FOREACH(cl->properties, l, foo_id)
     _db_build_implement(cl, foo_id);

   EINA_LIST_FOREACH(cl->methods, l, foo_id)
     _db_build_implement(cl, foo_id);

   return EINA_TRUE;
}

static void
_db_fill_constructor(Eolian_Class *cl, Eolian_Constructor *ctor)
{
   const char *ctor_name = ctor->full_name;
   if (ctor_name[0] == '.')
     {
        ctor->full_name = eina_stringshare_printf("%s%s", cl->full_name,
                                                  ctor_name);
        eina_stringshare_del(ctor_name);
     }

   cl->constructors = eina_list_append(cl->constructors, ctor);
}

static Eina_Bool
_db_fill_constructors(Eolian_Class *cl, Eo_Class_Def *kls)
{
   Eolian_Constructor *ctor;
   Eina_List *l;

   EINA_LIST_FOREACH(kls->constructors, l, ctor)
     {
        _db_fill_constructor(cl, ctor);
        eina_list_data_set(l, NULL); /* prevent double free */
     }
 
   return EINA_TRUE;
}

static Eina_Bool
_db_fill_events(Eolian_Class *cl, Eo_Class_Def *kls)
{
   Eolian_Event *event;
   Eina_List *l;

   EINA_LIST_FOREACH(kls->events, l, event)
     {
        cl->events = eina_list_append(cl->events, event);
        eina_list_data_set(l, NULL); /* prevent double free */
     }

   return EINA_TRUE;
}

static Eina_Bool
_db_fill_class(Eo_Class_Def *kls)
{
   Eolian_Class *cl = database_class_add(kls->name, kls->type);
   const char *s;
   Eina_List *l;

   eina_hash_set(_classesf, kls->base.file, cl);

   if (kls->description)
     cl->description = eina_stringshare_ref(kls->description);

   EINA_LIST_FOREACH(kls->inherits, l, s)
     cl->inherits = eina_list_append(cl->inherits, eina_stringshare_add(s));

   if (kls->legacy_prefix)
     cl->legacy_prefix = eina_stringshare_ref(kls->legacy_prefix);
   if (kls->eo_prefix)
     cl->eo_prefix = eina_stringshare_ref(kls->eo_prefix);
   if (kls->data_type)
     cl->data_type = eina_stringshare_ref(kls->data_type);

   cl->properties = kls->properties; kls->properties = NULL;
   cl->methods    = kls->methods   ; kls->methods    = NULL;

   if (!_db_fill_implements  (cl, kls)) return EINA_FALSE;
   if (!_db_fill_constructors(cl, kls)) return EINA_FALSE;
   if (!_db_fill_events      (cl, kls)) return EINA_FALSE;

   cl->base = kls->base;
   kls->base.file = NULL;

   return EINA_TRUE;
}

Eina_Bool
eo_parser_database_fill(const char *filename, Eina_Bool eot)
{
   Eina_List *k;
   Eo_Node *nd;
   Eina_Bool has_class = EINA_FALSE;

   Eo_Lexer *ls = eo_lexer_new(filename);
   if (!ls)
     {
        ERR("unable to create lexer");
        return EINA_FALSE;
     }

   /* read first token */
   eo_lexer_get(ls);

   if (!eo_parser_walk(ls, eot))
     {
        eo_lexer_free(ls);
        return EINA_FALSE;
     }

   if (eot) goto done;

   EINA_LIST_FOREACH(ls->nodes, k, nd) if (nd->type == NODE_CLASS)
     {
        has_class = EINA_TRUE;
        break;
     }

   if (!has_class)
     {
        ERR("No classes for file %s", filename);
        eo_lexer_free(ls);
        return EINA_FALSE;
     }

   EINA_LIST_FOREACH(ls->nodes, k, nd)
     {
        switch (nd->type)
          {
           case NODE_CLASS:
             if (!_db_fill_class(nd->def_class))
               goto error;
             break;
           default:
             break;
          }
     }

done:
   eo_lexer_free(ls);
   return EINA_TRUE;

error:
   eo_lexer_free(ls);
   return EINA_FALSE;
}
