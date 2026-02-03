#include <math.h>
#include <limits.h>

#include "bit-ops.h"

// Helper to prevent aggressive compiler optimization that transforms
// (unsigned int)(long long)double to (unsigned int)double.
// The latter can trap on negative inputs with some vector instructions (e.g. vcvttsd2usi).
static inline unsigned int double_to_uint(double x) {
    volatile long long tmp = (long long)x;
    return (unsigned int)tmp;
}

/*
	bitwise complement for use with .Call to bitFlip masked to bitWidth
*/
SEXP bitFlip(SEXP a, SEXP bitWidth )
{
    PROTECT (a = coerceVector(a,REALSXP) ) ;
    PROTECT (bitWidth = coerceVector(bitWidth,INTSXP) ) ;
    int n = LENGTH(a);
    int *xbitWidth = INTEGER(bitWidth);
    double *xa = REAL(a);
    unsigned int mask = ( unsigned int ) -1 >> (32 - *xbitWidth);
    SEXP aflip = PROTECT(allocVector(REALSXP,n));
    double *xaflip = REAL(aflip);

    for (int i=0; i<n; i++ ) {
	if ( !R_FINITE(xa[i]) || logb(xa[i])>31 )
	    xaflip[i]=NA_REAL ;
	else {
		unsigned int tmp = double_to_uint(xa[i);
	    xaflip[i]=(double) ( ~tmp & mask ) ;
	}
    }
    UNPROTECT(3) ;
    return (aflip) ;
}


/*
	Improved version of bitwise __OP__ operator for S vectors for use
	with .C call where result is pre-allocated to length of a+b,
	operands are coerced to integer, but left at their original lengths.

	__OP__	is in { & , | , ^ }
		       AND OR  XOR
*/
#define bit2op_BODY(__OP__)					\
    PROTECT (a = coerceVector(a,REALSXP) ) ;			\
    PROTECT (b = coerceVector(b,REALSXP) ) ;			\
								\
    double *t, *longer = REAL(a),   *shorter = REAL(b)  ;	\
    int     i, nlonger = LENGTH(a), nshorter = LENGTH(b);	\
								\
    if ( nshorter > nlonger ) {	/* swap */			\
	i=nshorter ; nshorter=nlonger; nlonger=i ;		\
	t=shorter ;  shorter=longer ;  longer= t ;		\
    }								\
								\
    if ( !nshorter || !nlonger ) nlonger=0 ;			\
    else if ( nlonger % nshorter ) warning("longer object length is not a multiple of shorter object length\n") ; \
								\
    SEXP aAb = PROTECT(allocVector(REALSXP, nlonger));		\
    t = REAL(aAb);						\
								\
    for (int i=0; i < nlonger; )				\
	for (int j=0; j < nshorter; j++ ) {				\
	    if (!R_FINITE(shorter[j]) || !R_FINITE(longer[i]) ||	\
		logb(shorter[j]) > 31 || logb(longer[i]) > 31) {	\
									\
		*(t++)= NA_REAL;					\
	    }								\
	    else							\
		*(t++) = (double) (double_to_uint(shorter[j]) __OP__		\
		                   double_to_uint(longer [i]) ) ;		\
	    if (!(++i < nlonger)) break ;				\
	}								\
									\
    UNPROTECT(3) ;							\
    return (aAb)



SEXP bitAnd(SEXP a, SEXP b) {
    bit2op_BODY( & );

}

SEXP bitOr(SEXP a, SEXP b) {
    bit2op_BODY( | );

}

SEXP bitXor(SEXP a, SEXP b) {
    bit2op_BODY( ^ );
}



/*
	Improved version of bitwise Left SHIFT operator for S vectors for use
	with .C call where result is pre-allocated to length of a+b,
	operands are coerced to integer, but left at their original lengths
*/
#define bitshift_BODY(__OP__)						\
									\
    PROTECT (a = coerceVector(a,REALSXP) ) ;				\
    PROTECT (b = coerceVector(b, INTSXP) ) ;				\
									\
    double *xa = REAL(a);	int na=LENGTH(a);			\
    int* xb = INTEGER(b);	int nb=LENGTH(b);			\
									\
    int n = na>nb ? na : nb ;						\
									\
    if (!na || !nb ) n = na = nb = 0 ;					\
    else if (n%na || n%nb )  warning("longer object length is not a multiple of shorter object length\n") ; \
									\
    SEXP aAb = PROTECT(allocVector(REALSXP, n));			\
    double *xaAb = REAL(aAb);						\
									\
    int i, j;								\
    if (na > nb) {							\
	for (i=0; i < na; ) {						\
	    for (j=0; j < nb; j++ ) {					\
		if ( !R_FINITE(xa[i]) || xb[j]==NA_INTEGER || logb(xa[i]) > 31 ) { \
		    *(xaAb++) = NA_REAL ;				\
		}							\
		else *(xaAb++)=(double) (double_to_uint(xa[i]) __OP__ (unsigned int)(xb[j] & 31 ) ) ; \
		if (! (++i < na) ) break ;				\
	    }								\
	}								\
    }									\
    else {								\
	for (i=0; i < nb; )						\
	    for (j=0; j < na; j++ ) {					\
		if ( !R_FINITE(xa[j]) || xb[i]==NA_INTEGER || logb(xa[j]) > 31 ) { \
		    *(xaAb++) = NA_REAL ;				\
		}							\
		else *(xaAb++)=(double) (double_to_uint(xa[j]) __OP__ (unsigned int)(xb[i] & 31 )) ; \
		if (! (++i < nb) ) break ;				\
	    }								\
    }									\
    UNPROTECT(3) ;							\
    return (aAb)


SEXP bitShiftL(SEXP a, SEXP b) {
    bitshift_BODY( << );
}

SEXP bitShiftR(SEXP a, SEXP b) {
    bitshift_BODY( >> );
}
