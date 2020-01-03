#include <R.h>
#include <Rinternals.h>

SEXP bitFlip( SEXP a, SEXP bitWidth );
SEXP bitAnd( SEXP a,  SEXP b );
SEXP bitOr ( SEXP a,  SEXP b );
SEXP bitXor( SEXP a,  SEXP b );
SEXP bitShiftL( SEXP a,  SEXP b);
SEXP bitShiftR( SEXP a,  SEXP b);

// ./cksum.c :
void cksum(int *nstrings, char **strings, double *crcs);
