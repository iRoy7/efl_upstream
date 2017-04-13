#include "evas_common_private.h"
#include "evas_private.h"
//#include "evas_cs.h"
#ifdef EVAS_CSERVE2
#include "evas_cs2_private.h"
#endif

typedef struct _Efl_Canvas_Output Efl_Canvas_Output;
struct _Efl_Canvas_Output
{
   Eo *canvas;

   void *info;/*, *context, *output;*/
   Evas_Coord x, y, w, h;
};

static Evas_Public_Data *
_efl_canvas_output_async_block(Efl_Canvas_Output *output)
{
   Evas_Public_Data *e;

   if (!output->canvas) return NULL;
   e = efl_data_scope_get(output->canvas, EVAS_CANVAS_CLASS);
   if (!e) return NULL;

   evas_canvas_async_block(e);

   return e;
}

EAPI Efl_Canvas_Output *
efl_canvas_output_add(Evas *canvas)
{
   Efl_Canvas_Output *r;
   Evas_Public_Data *e;

   if (!efl_isa(canvas, EVAS_CANVAS_CLASS)) return NULL;

   r = calloc(1, sizeof (Efl_Canvas_Output));
   if (!r) return NULL;

   efl_wref_add(canvas, &r->canvas);

   e = _efl_canvas_output_async_block(r);
   // Track this output in Evas
   e->outputs = eina_list_append(e->outputs, r);

   return r;
}

EAPI void
efl_canvas_output_del(Efl_Canvas_Output *output)
{
   if (output->canvas)
     {
        Evas_Public_Data *e;

        e = _efl_canvas_output_async_block(output);
        if (!e) goto on_error;

        // XXX: need to free output and context one they get allocated one day
        // e->engine.func->context_free(eo_dat->output, eo_dat->context);
        // e->engine.func->output_free(eo_dat->output);
        e->engine.func->info_free(output->canvas, output->info);
        e->outputs = eina_list_remove(e->outputs, output);

        efl_wref_del(output->canvas, &output->canvas);
     }

 on_error:
   free(output);
}

EAPI void
efl_canvas_output_view_set(Efl_Canvas_Output *output,
                           Evas_Coord x, Evas_Coord y, Evas_Coord w, Evas_Coord h)
{
   Evas_Public_Data *e;

   e = _efl_canvas_output_async_block(output);
   if (!e) return ;

   output->x = x;
   output->y = y;
   output->w = w;
   output->h = h;
   // XXX: tell engine about any output size etc. changes
   // XXX: tell evas to add damage if viewport loc/size changed
}

EAPI void
efl_canvas_output_view_get(Efl_Canvas_Output *output,
                           Evas_Coord *x, Evas_Coord *y, Evas_Coord *w, Evas_Coord *h)
{
   if (x) *x = output->x;
   if (y) *y = output->y;
   if (w) *w = output->w;
   if (h) *h = output->h;
}

EAPI Eina_Bool
efl_canvas_output_engine_info_set(Efl_Canvas_Output *output,
                                  Evas_Engine_Info *info)
{
   Evas_Public_Data *e;

   e = _efl_canvas_output_async_block(output);
   if (!e) return EINA_FALSE;
   if (output->info != info) return EINA_FALSE;

   // XXX: handle setting of engine info here

   return EINA_TRUE;
}

EAPI Evas_Engine_Info*
efl_canvas_output_engine_info_get(Efl_Canvas_Output *output)
{
   return output->info;
}

EAPI Eina_Bool
efl_canvas_output_lock(Efl_Canvas_Output *output EINA_UNUSED)
{
   return EINA_FALSE;
}

EAPI Eina_Bool
efl_canvas_output_unlock(Efl_Canvas_Output *output EINA_UNUSED)
{
   return EINA_FALSE;
}
