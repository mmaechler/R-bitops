#include <R.h>
#include "bit-ops.h"
#include <math.h>

/*
	bitwise complement for use with .Call to bitFlip masked to bitWidth
*/
SEXP bitFlip(SEXP a, SEXP bitWidth ) {
	int i, n, *xbitWidth;
	unsigned long long  mask ;
	long long tmp ;
	double *xa, *xaflip ;
	SEXP aflip ;
	
	PROTECT (a = AS_NUMERIC(a) ) ;
	PROTECT (bitWidth = AS_INTEGER(bitWidth) ) ;

	n=LENGTH(a) ;
	PROTECT (aflip = NEW_NUMERIC(n) ) ;

	xa=NUMERIC_POINTER(a) ;
	xaflip=NUMERIC_POINTER(aflip) ;
	xbitWidth=INTEGER_POINTER(bitWidth)  ;

	mask = ( unsigned long long ) -1 >> (64 - *xbitWidth)  ;


	for (i=0; i<n; i++ ) {
		if ( !R_FINITE(xa[i]) || logb(xa[i])>52 ) xaflip[i]=NA_REAL ;

		else {
			tmp=(long long) xa[i] ;
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
#define bit2op_BODY(__OP__)				  \
    	int i, j, nshorter,  nlonger ;                    \
	double *shorter, *longer, *t ;	                  \
	SEXP aAb ;                                        \
							  \
	PROTECT (a = AS_NUMERIC(a) ) ;                    \
	PROTECT (b = AS_NUMERIC(b) ) ;                    \
                                                          \
	nlonger=LENGTH(a) ;                               \
	longer=NUMERIC_POINTER(a) ;                       \
	nshorter=LENGTH(b) ;                              \
	shorter=NUMERIC_POINTER(b) ;                      \
                                                          \
	if ( nshorter > nlonger ) {                       \
		i=nshorter ; nshorter=nlonger; nlonger=i ;\
		t=shorter ; shorter=longer ; longer= t ;  \
	}                                                 \
                                                          \
	if ( !nshorter || !nlonger || nlonger % nshorter ) nlonger=0 ; \
                                                          \
	PROTECT (aAb = NEW_NUMERIC(nlonger) ) ;           \
	t=NUMERIC_POINTER(aAb) ;                          \
                                                          \
							  \
	for (i=0; i<nlonger; )			          \
		for (j=0; j<nshorter; j++ ) {             \
			                                  \
			if (!R_FINITE(shorter[j]) || !R_FINITE(longer[i]) || logb(shorter[j])>52 || logb(longer[i])>52 ) *(t++)=NA_REAL ; \
                                                          \
	    		else *(t++) =(double) ( (long long) shorter[j] __OP__ (long long ) longer[i++] ) ; \
		}                                         \
                                                          \
	UNPROTECT(3) ;                                    \
	return (aAb) ;



SEXP bitAnd(SEXP a, SEXP b) {
    bit2op_BODY( & )
}

SEXP bitOr(SEXP a, SEXP b) {
    bit2op_BODY( | )
}

SEXP bitXor(SEXP a, SEXP b) {
    bit2op_BODY( ^ )
}



/*
	Improved version of bitwise Left SHIFT operator for S vectors for use
	with .C call where result is pre-allocated to length of a+b,
	operands are coerced to integer, but left at their original lengths
*/
#define bitshift_BODY(__OP__)                          \
	int i, j, na, nb, n, *xb ;		       \
	double *xa, *xaAb;                             \
	SEXP aAb ;                                     \
                                                       \
	PROTECT (a = AS_NUMERIC(a) ) ;                 \
	PROTECT (b = AS_INTEGER(b) ) ;                 \
                                                       \
	na=LENGTH(a) ;                                 \
	xa=NUMERIC_POINTER(a) ;                        \
	nb=LENGTH(b) ;                                 \
	xb=INTEGER_POINTER(b) ;                        \
                                                       \
	n=na>nb ? na : nb ;                            \
                                                       \
	if (!na || !nb || n%na || n%nb ) n=na=nb=0 ;   \
                                                       \
	PROTECT (aAb= NEW_NUMERIC(n) ) ;               \
	xaAb=NUMERIC_POINTER(aAb) ;                    \
                                                       \
                                                       \
	if (na > nb ) {                                \
		for (i=0; i< na; ) {                   \
			for (j=0; j< nb; j++ ) {       \
                                                       \
				if ( !R_FINITE(xa[i]) || xb[j]==NA_INTEGER || logb(xa[i]) > 52 ) *(xaAb++) = NA_REAL ; \
				else *(xaAb++)=(double) ( (long long) xa[i++] __OP__ (xb[j] & 63 ) ) ; \
			}                              \
		}                                      \
	}                                              \
    	else {                                         \
		for (i=0; i< nb; )                     \
			for (j=0; j< na; j++ ) {       \
                                                       \
				if ( !R_FINITE(xa[j]) || xb[i]==NA_INTEGER || logb(xa[j]) > 52 ) *(xaAb++) = NA_REAL ; \
				else *(xaAb++)=(double) ( (long long) xa[j] __OP__ (xb[i++] & 63 ) ) ; \
			}                              \
    	}                                              \
	UNPROTECT(3) ;                                 \
	return (aAb) ;


SEXP bitShiftL(SEXP a, SEXP b) {
    bitshift_BODY( << )
}

SEXP bitShiftR(SEXP a, SEXP b) {
    bitshift_BODY( >> )
}
