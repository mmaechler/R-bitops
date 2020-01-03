#include <math.h>

#include "bit-ops.h"

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
	    // in case of a negative, cast twice;
	    unsigned int tmp = xa[i] < 0 ? (int) xa[i] : (unsigned) xa[i];
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
    int i, j, nshorter, nlonger ;				\
    double *shorter, *longer, *t ;				\
    SEXP aAb ;							\
								\
    PROTECT (a = coerceVector(a,REALSXP) ) ;			\
    PROTECT (b = coerceVector(b,REALSXP) ) ;			\
								\
    nlonger=LENGTH(a) ;						\
    longer=REAL(a) ;						\
    nshorter=LENGTH(b) ;					\
    shorter=REAL(b) ;						\
								\
    if ( nshorter > nlonger ) {					\
	i=nshorter ; nshorter=nlonger; nlonger=i ;		\
	t=shorter ;  shorter=longer ;  longer= t ;		\
    }								\
								\
    if ( !nshorter || !nlonger ) nlonger=0 ;			\
    else if ( nlonger % nshorter ) warning("longer object length is not a multiple of shorter object length\n") ; \
								\
    PROTECT (aAb = allocVector(REALSXP,nlonger) ) ;		\
    t=REAL(aAb) ;						\
								\
    for (i=0; i < nlonger; )					\
	for (j=0; j < nshorter; j++ ) {					\
	    if (!R_FINITE(shorter[j]) || !R_FINITE(longer[i]) ||	\
		logb(shorter[j]) > 31 || logb(longer[i]) > 31) {	\
									\
		*(t++)= NA_REAL;					\
		i++;							\
	    }								\
	    else							\
		*(t++) = (double) ((unsigned int) shorter[j] __OP__	\
		                   (unsigned int ) longer[i++] ) ;	\
	    if (!(i < nlonger)) break ;					\
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
    int i, j, na, nb, n, *xb ;						\
    double *xa, *xaAb;							\
    SEXP aAb ;								\
									\
    PROTECT (a = coerceVector(a,REALSXP) ) ;				\
    PROTECT (b = coerceVector(b,INTSXP) ) ;				\
									\
    na=LENGTH(a) ;							\
    xa=REAL(a) ;							\
    nb=LENGTH(b) ;							\
    xb=INTEGER(b) ;							\
									\
    n= na>nb ? na : nb ;						\
									\
    if (!na || !nb ) n=na=nb=0 ;					\
    else if (n%na || n%nb )  warning("longer object length is not a multiple of shorter object length\n") ; \
									\
    PROTECT (aAb= allocVector(REALSXP,n) ) ;				\
    xaAb=REAL(aAb) ;							\
									\
    if (na > nb ) {							\
	for (i=0; i< na; ) {						\
	    for (j=0; j< nb; j++ ) {					\
		if ( !R_FINITE(xa[i]) || xb[j]==NA_INTEGER || logb(xa[i]) > 31 ) { \
		    *(xaAb++) = NA_REAL ; i++ ;				\
		}							\
		else *(xaAb++)=(double) ( (unsigned int) xa[i++] __OP__ (xb[j] & 31 ) ) ; \
		if (! (i<na) ) break ;					\
	    }								\
	}								\
    }									\
    else {								\
	for (i=0; i< nb; )						\
	    for (j=0; j< na; j++ ) {					\
		if ( !R_FINITE(xa[j]) || xb[i]==NA_INTEGER || logb(xa[j]) > 31 ) { \
		    *(xaAb++) = NA_REAL ; i++;				\
		}							\
		else *(xaAb++)=(double) ( (unsigned int) xa[j] __OP__ (xb[i++] & 31 ) ) ; \
		if (! (i<nb) ) break ;					\
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
