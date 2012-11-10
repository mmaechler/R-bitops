
#include <R.h>
#include "bitOps.h"

/*
	bitwise complement for use with .C call to bitFlip
*/
void bitFlip(Sint *n, Sint *a, Sint *aflip )
{
    int i;
    for (i=0; i<(int) *n; i++ ) aflip[i]=~a[i];
}


/*
	Improved version of bitwise __OP__ operator for S vectors for use
	with .C call where result is pre-allocated to length of a+b,
	operands are coerced to integer, but left at their original lengths.

	__OP__	is in { & , | , ^ }
		       AND OR  XOR
*/
#define bit2op_BODY(__OP__)				\
    int i, j;						\
    Sint *nshorter, *shorter, *nlonger, *longer;	\
							\
    if (!*na || !*nb ) return;				\
							\
    if (*na > *nb ) {					\
	longer= a; nlonger= na;				\
	shorter=b; nshorter=nb;				\
    }							\
    else {						\
	longer= b; nlonger= nb;				\
	shorter=a; nshorter=na;				\
    }							\
							\
    for (i=0; i< (int) *nlonger; )			\
	for (j=0; j<(int) *nshorter; j++ )		\
	    *(aAb++) =shorter[j] __OP__ longer[i++];


void bitAnd(Sint *na, Sint *a, Sint *nb, Sint *b, Sint *aAb)
{
    bit2op_BODY( & )
}

void bitOr(Sint *na, Sint *a, Sint *nb, Sint *b, Sint *aAb)
{
    bit2op_BODY( | )
}

void bitXor(Sint *na, Sint *a, Sint *nb, Sint *b, Sint *aAb)
{
    bit2op_BODY( ^ )
}



/*
	Improved version of bitwise Left SHIFT operator for S vectors for use
	with .C call where result is pre-allocated to length of a+b,
	operands are coerced to integer, but left at their original lengths
*/
#define bitshift_BODY(__OP__)				\
    int i, j;						\
							\
    if (!*na || !*nb ) return;				\
							\
    if (*na > *nb ) {					\
	for (i=0; i< (int) *na; )			\
	    for (j=0; j<(int) *nb; j++ )		\
		*(aAb++) = a[i++] __OP__ (b[j] & 63);	\
    }							\
    else {						\
	for (i=0; i< (int) *nb; )			\
	    for (j=0; j<(int) *na; j++ )		\
		*(aAb++) = a[j] __OP__ (b[i++] & 63);	\
    }


void bitShiftL(Sint *na, Sint *a, Sint *nb, Sint *b, Sint *aAb )
{
    bitshift_BODY( << )
}

void bitShiftR(Sint *na, Sint *a, Sint *nb, Sint *b, Sint *aAb )
{
    bitshift_BODY( >> )
}
