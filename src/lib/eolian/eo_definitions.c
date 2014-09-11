#include <stdio.h>
#include <stdlib.h>

#include "eo_definitions.h"

void
eo_definitions_class_def_free(Eo_Class_Def *kls)
{
   const char *s;
   Eolian_Function *func;
   Eolian_Event *sgn;
   Eolian_Implement *impl;
   Eolian_Constructor *ctor;

   if (kls->base.file)
     eina_stringshare_del(kls->base.file);

   if (kls->name)
     eina_stringshare_del(kls->name);
   if (kls->description)
     eina_stringshare_del(kls->description);
   if (kls->legacy_prefix)
     eina_stringshare_del(kls->legacy_prefix);
   if (kls->eo_prefix)
     eina_stringshare_del(kls->eo_prefix);
   if (kls->data_type)
     eina_stringshare_del(kls->data_type);

   EINA_LIST_FREE(kls->inherits, s)
     if (s) eina_stringshare_del(s);

   EINA_LIST_FREE(kls->implements, impl)
     database_implement_del(impl);

   EINA_LIST_FREE(kls->constructors, ctor)
     database_constructor_del(ctor);

   EINA_LIST_FREE(kls->properties, func)
     database_function_del(func);

   EINA_LIST_FREE(kls->methods, func)
     database_function_del(func);

   EINA_LIST_FREE(kls->events, sgn)
     database_event_del(sgn);

   free(kls);
}

void
eo_definitions_temps_free(Eo_Lexer_Temps *tmp)
{
   Eina_Strbuf *buf;
   Eolian_Function_Parameter *par;
   Eolian_Type *tp;
   Eolian_Variable *var;
   const char *s;

   EINA_LIST_FREE(tmp->str_bufs, buf)
     eina_strbuf_free(buf);

   EINA_LIST_FREE(tmp->params, par)
     database_parameter_del(par);

   if (tmp->legacy_def)
     eina_stringshare_del(tmp->legacy_def);

   if (tmp->kls)
     eo_definitions_class_def_free(tmp->kls);

   EINA_LIST_FREE(tmp->type_defs, tp)
     database_type_del(tp);

   EINA_LIST_FREE(tmp->var_defs, var)
     database_var_del(var);

   if (tmp->func)
     database_function_del(tmp->func);

   if (tmp->param)
     database_parameter_del(tmp->param);

   EINA_LIST_FREE(tmp->str_items, s)
     if (s) eina_stringshare_del(s);

   if (tmp->event)
     database_event_del(tmp->event);

   if (tmp->impl)
     database_implement_del(tmp->impl);

   if (tmp->ctor)
     database_constructor_del(tmp->ctor);

   EINA_LIST_FREE(tmp->strs, s)
     if (s) eina_stringshare_del(s);
}
