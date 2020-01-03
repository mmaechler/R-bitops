## MM:  the "x <- a - a" (== integer(n)) and then
## ---      "x <- x + .C(...)"
## is probably for safety, normalization of unsigned int
## -- and for NA/NaN handling -- but that is done too complicated here.
##--- and: If I really want pack bits into integers,
##--- I cannot really deal with NA-bits in such a way!
##---> I'd need extra structure to store NA locations...
##
## OTOH: instead of CLASSES & COPY, we should use .Call() !!

bitFlip <- function(a,bitWidth=32)
{
    .Call(C_bitFlip, a, bitWidth)
}


bitAnd <- function(a, b)
{
    .Call(C_bitAnd, a, b)
}

bitOr <- function(a, b)
{
    .Call(C_bitOr, a, b)
}

bitXor <- function(a, b)
{
    .Call(C_bitXor, a, b)
}


bitShiftL <- function(a, b)
{
    .Call(C_bitShiftL, a, b)
}

bitShiftR <- function(a, b)
{
    .Call(C_bitShiftR, a, b)
}


cksum <- function(a)
{
    x <- nchar(as.character(a))*0
    x <- x + .C(C_cksum, # ../src/cksum.c
                length(a), as.character(a),
                val = as.numeric(x),
		NAOK=TRUE)$val
    x[is.na(a)] <- NA
    x
}
