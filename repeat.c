#include "postgres.h"
#include "common/int.h"
#include "funcapi.h"

// needed for work_mem constant
#include "miscadmin.h"

/* #include "implementations/valuepercall.c" */
#include "./implementations/materialize.c"
