#ifdef HAVE_CONFIG_H
# include "elementary_config.h"
#endif

#include <Elementary.h>
#include "elm_priv.h"

//we need those for legacy compatible code
#include "elm_genlist.eo.h"
#include "elm_gengrid.eo.h"

#define API_ENTRY()\
   EINA_SAFETY_ON_NULL_RETURN(obj); \
   ELM_WIDGET_DATA_GET_OR_RETURN(obj, pd); \
   EINA_SAFETY_ON_FALSE_RETURN(elm_widget_is_legacy(obj));

#define API_ENTRY_VAL(val)\
   EINA_SAFETY_ON_NULL_RETURN_VAL(obj, val); \
   ELM_WIDGET_DATA_GET_OR_RETURN(obj, pd, val); \
   EINA_SAFETY_ON_FALSE_RETURN_VAL(elm_widget_is_legacy(obj), val);

#define MAPPING() \
        MAP(PREVIOUS, prev) \
        MAP(NEXT, next) \
        MAP(UP, up) \
        MAP(DOWN, down) \
        MAP(LEFT, left) \
        MAP(RIGHT, right)



static Eina_List*
_custom_chain_get(const Efl_Ui_Widget *node)
{
   ELM_WIDGET_DATA_GET_OR_RETURN(node, pd, NULL);

   return pd->legacy_focus.custom_chain;
}

static void
_custom_chain_set(Efl_Ui_Widget *node, Eina_List *lst)
{
   ELM_WIDGET_DATA_GET_OR_RETURN(node, pd);

   pd->legacy_focus.custom_chain = eina_list_free(pd->legacy_focus.custom_chain);
   pd->legacy_focus.custom_chain = lst;
}

Evas_Object*
legacy_elm_widget_next_targer(Efl_Ui_Widget *obj, Elm_Focus_Direction dir)
{
   API_ENTRY_VAL(NULL)
   Efl_Ui_Widget *target = NULL;

   #define MAP(direction, field)  if (dir == EFL_UI_FOCUS_DIRECTION_ ##direction && pd->legacy_focus.field) target = pd->legacy_focus.field;

   if (!target)
     {
        MAPPING()
     }
   #undef MAP

   return target;
}

EAPI void
elm_object_focus_next_object_set(Evas_Object        *obj,
                                 Evas_Object        *next EINA_UNUSED,
                                 Elm_Focus_Direction dir EINA_UNUSED)
{
   API_ENTRY()


   #define MAP(direction, field)  if (dir == EFL_UI_FOCUS_DIRECTION_ ##direction) pd->legacy_focus.field = next;
   MAPPING()
   #undef MAP
   ELM_WIDGET_DATA_GET_OR_RETURN(next, next_pd);
   dir = efl_ui_focus_util_direction_complement(EFL_UI_FOCUS_UTIL_CLASS, dir);
   #define MAP(direction, field)  if (dir == EFL_UI_FOCUS_DIRECTION_ ##direction) next_pd->legacy_focus.field = obj;
   MAPPING()
   #undef MAP
}

EAPI void
elm_object_focus_custom_chain_set(Evas_Object *obj,
                                  Eina_List   *objs EINA_UNUSED)
{
   API_ENTRY()
   _custom_chain_set(obj, objs);
}

EAPI void
elm_object_focus_custom_chain_unset(Evas_Object *obj)
{
   API_ENTRY()

   _custom_chain_set(obj, NULL);
}

EAPI const Eina_List *
elm_object_focus_custom_chain_get(const Evas_Object *obj)
{
   API_ENTRY_VAL(NULL)

   return _custom_chain_get(obj);
}

EAPI void
elm_object_focus_custom_chain_append(Evas_Object *obj,
                                     Evas_Object *child EINA_UNUSED,
                                     Evas_Object *relative_child EINA_UNUSED)
{
   API_ENTRY()

   pd->legacy_focus.custom_chain = eina_list_append_relative(pd->legacy_focus.custom_chain, child, relative_child);
}

EAPI void
elm_object_focus_custom_chain_prepend(Evas_Object *obj,
                                      Evas_Object *child EINA_UNUSED,
                                      Evas_Object *relative_child EINA_UNUSED)
{
   API_ENTRY()

   pd->legacy_focus.custom_chain = eina_list_prepend_relative(pd->legacy_focus.custom_chain, child, relative_child);
}

EINA_DEPRECATED EAPI void
elm_object_focus_cycle(Evas_Object        *obj,
                       Elm_Focus_Direction dir)
{
   elm_object_focus_next(obj, dir);
}

EAPI void
elm_object_focus_next(Evas_Object        *obj,
                      Elm_Focus_Direction dir)
{
   Eina_Bool legacy_focus_move = EINA_FALSE;
   Efl_Ui_Widget *o = NULL, *top;
   Efl_Ui_Focus_Object *regular, *logical;
   Efl_Ui_Focus_Manager *manager_top;
   API_ENTRY()

   top = elm_object_top_widget_get(obj);
   manager_top = efl_ui_focus_util_active_manager(EFL_UI_FOCUS_UTIL_CLASS, obj);
   regular = efl_ui_focus_manager_request_move(manager_top, dir, NULL, EINA_FALSE);
   logical = efl_ui_focus_manager_focus_get(manager_top);

   Efl_Ui_Focus_Object *legacy_target = legacy_elm_widget_next_targer(logical, dir);
   if (legacy_target)
     {
        o = legacy_target;
        efl_ui_focus_util_focus(EFL_UI_FOCUS_UTIL_CLASS, legacy_target);
        if (elm_object_focused_object_get(top) == legacy_target)
          {
             legacy_focus_move = EINA_TRUE;
          }
     }

   if (!legacy_focus_move)
     o = efl_ui_focus_manager_move(top, dir);
   if (!o)
     {
        if (dir == EFL_UI_FOCUS_DIRECTION_NEXT || dir == EFL_UI_FOCUS_DIRECTION_PREVIOUS)
          {
             Efl_Ui_Focus_Object *root;

             root = efl_ui_focus_manager_root_get(obj);
             efl_ui_focus_manager_setup_on_first_touch(obj, dir, root);
          }
     }
}

EAPI Evas_Object *
elm_object_focus_next_object_get(const Evas_Object  *obj,
                                 Elm_Focus_Direction dir)
{
   Efl_Ui_Widget *top = elm_object_top_widget_get(obj);
   API_ENTRY_VAL(NULL)

   #define MAP(direction, field)  if (dir == EFL_UI_FOCUS_DIRECTION_ ##direction && pd->legacy_focus.field) return pd->legacy_focus.field;
   MAPPING()
   #undef MAP

   return efl_ui_focus_manager_request_move(efl_ui_focus_util_active_manager(EFL_UI_FOCUS_UTIL_CLASS, top), dir, NULL, EINA_FALSE);
}

EAPI Elm_Object_Item *
elm_object_focus_next_item_get(const Evas_Object  *obj,
                               Elm_Focus_Direction dir EINA_UNUSED)
{
   API_ENTRY_VAL(NULL)
   /* FOCUS-FIXME */
   return NULL;
}

EAPI void
elm_object_focus_next_item_set(Evas_Object     *obj,
                               Elm_Object_Item *next_item EINA_UNUSED,
                               Elm_Focus_Direction dir EINA_UNUSED)
{
   API_ENTRY()
   /* FOCUS-FIXME */
}

EAPI Evas_Object *
elm_object_focused_object_get(const Evas_Object *obj)
{
   API_ENTRY_VAL(NULL)
   Efl_Ui_Focus_Manager *man = elm_object_top_widget_get(obj);

   while(efl_ui_focus_manager_redirect_get(man))
     {
        man = efl_ui_focus_manager_redirect_get(man);

        // legacy compatible code, earlier those containers have not exposed theire items
        if (efl_isa(man, ELM_GENGRID_CLASS) ||
            efl_isa(man, ELM_TOOLBAR_CLASS) ||
            efl_isa(man, ELM_GENLIST_CLASS)) return man;
     }

   return efl_ui_focus_manager_focus_get(man);
}

EAPI Eina_Bool
elm_object_focus_get(const Evas_Object *obj)
{
   Efl_Ui_Focus_Manager *m;
   Efl_Ui_Focus_Object *focused_child;
   API_ENTRY_VAL(EINA_FALSE)

   if (!elm_widget_is(obj))
     return evas_object_focus_get(obj);

   m = efl_ui_focus_object_focus_manager_get(obj);

   //no manager means not registered
   if (!m) return EINA_FALSE;

   //assertion: our redirect manager m is in the redirect chain
   m = efl_ui_focus_object_focus_manager_get(obj);

   //if obj is the redriect manager its kind of focused
   if (efl_ui_focus_manager_redirect_get(m) == obj) return EINA_TRUE;

   //if there is a redirect manager
   if (!!efl_ui_focus_manager_redirect_get(m)) return EINA_FALSE;

   //now take the focused object and walk down the parents, if this is
   focused_child = efl_ui_focus_manager_focus_get(m);

   while(focused_child)
     {
        if (focused_child == obj) return EINA_TRUE;

        focused_child = efl_ui_focus_object_focus_parent_get(focused_child);
     }

   return efl_ui_focus_object_focus_get(obj);
}

EAPI void
elm_object_focus_set(Evas_Object *obj,
                     Eina_Bool    focus)
{
   // ugly, but, special case for inlined windows
   if (efl_isa(obj, EFL_UI_WIN_CLASS))
     {
        Evas_Object *inlined = elm_win_inlined_image_object_get(obj);
        if (inlined)
          {
             evas_object_focus_set(inlined, focus);
             return;
          }
     }
   else if (elm_widget_is(obj))
     {
        if (focus)
          efl_ui_focus_util_focus(EFL_UI_FOCUS_UTIL_CLASS, obj);
        else
          {
             if (efl_ui_focus_manager_focus_get(efl_ui_focus_object_focus_manager_get(obj)) == obj)
               efl_ui_focus_manager_pop_history_stack(efl_ui_focus_object_focus_manager_get(obj));
          }
     }
   else
     {
        evas_object_focus_set(obj, focus);
     }
}
