#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include "constructors_mixin.h"
#include "constructors_simple2.h"

#define MY_CLASS SIMPLE2_CLASS

static void
_constructor(Eo *obj, void *class_data EINA_UNUSED)
{
   eo2_do_super(obj, MY_CLASS, eo2_constructor());

   eo_error_set(obj);
}

static Eo2_Op_Description op_descs[] = {
     EO2_OP_FUNC_OVERRIDE(_constructor, eo2_constructor),
     EO2_OP_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO2_VERSION,
     "Simple2",
     EO_CLASS_TYPE_REGULAR,
     EO2_CLASS_DESCRIPTION_OPS(op_descs),
     NULL,
     0,
     NULL,
     NULL
};

EO_DEFINE_CLASS(simple2_class_get, &class_desc, EO2_BASE_CLASS, NULL);

