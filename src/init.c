#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include "bit-ops.h"

#define CDEF(name)  {#name, (DL_FUNC) &name, sizeof(name ## _typ)/sizeof(name ## _typ[0]), name ##_typ}

#define CALLDEF(name, n)  {#name, (DL_FUNC) &name, n}

static R_NativePrimitiveArgType cksum_typ[3] = {
    INTSXP, STRSXP, REALSXP
};

static const R_CMethodDef CEntries[]  = {
    CDEF(cksum),

    {NULL, NULL, 0}
};

static R_CallMethodDef CallEntries[] = {
    CALLDEF(bitFlip, 2),
    CALLDEF(bitAnd, 2),
    CALLDEF(bitOr, 2),
    CALLDEF(bitXor, 2),
    CALLDEF(bitShiftL, 2),
    CALLDEF(bitShiftR, 2),

    {NULL, NULL, 0}
};

/**
 * register routines
 * @param dll pointer
 * @return none
 * @author Martin Maechler
 */
void
#ifdef HAVE_VISIBILITY_ATTRIBUTE
__attribute__ ((visibility ("default")))
#endif
R_init_bitops(DllInfo *dll)
{
    R_registerRoutines(dll, CEntries, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}


