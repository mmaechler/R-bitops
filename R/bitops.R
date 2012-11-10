## MM:  the "x <- a - a" (== integer(n)) and then
## ---      "x <- x + .C(...)"
## is probably for safety, normalization of unsigned int
## -- and for NA/NaN handling -- but that is done too complicated here.
##--- and: If I really want pack bits into integers,
##--- I cannot really deal with NA-bits in such a way!
##---> I'd need extra structure to store NA locations...
##
## OTOH: instead of CLASSES & COPY, we should use .Call() !!

bitFlip <- function(a)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    x <- a
    .C("bitFlip",
       length(a), a,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}


bitAnd <- function(a, b)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    if(any(is.na(b <- as.integer(b)))) stop("NAs in bit object ", sQuote(b))
    x <- a
    .C("bitAnd",
       length(a), a, length(b), b,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}

bitOr <- function(a, b)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    if(any(is.na(b <- as.integer(b)))) stop("NAs in bit object ", sQuote(b))
    x <- a
    .C("bitOr",
       length(a), a, length(b), b,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}

bitXor <- function(a, b)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    if(any(is.na(b <- as.integer(b)))) stop("NAs in bit object ", sQuote(b))
    x <- a
    .C("bitXor",
       length(a), a, length(b), b,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}


bitShiftL <- function(a, b)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    if(any(is.na(b <- as.integer(b)))) stop("NAs in bit object ", sQuote(b))
    x <- a
    .C("bitShiftL",
       length(a), a, length(b), b,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}

bitShiftR <- function(a, b)
{
    if(any(is.na(a <- as.integer(a)))) stop("NAs in bit object ", sQuote(a))
    if(any(is.na(b <- as.integer(b)))) stop("NAs in bit object ", sQuote(b))
    x <- a
    .C("bitShiftR",
       length(a), a, length(b), b,
       x, DUP = FALSE, PACKAGE = "bitops") #-> x has result
    x
}


crc <- function(a)
{
    x <- nchar(as.character(a))*0
    x <- x + .C("crc",
                length(a), as.character(a),
                val = as.numeric(x),
		## CLASSES = c("integer","character","numeric"),
		## COPY = c(FALSE, FALSE, TRUE),
                PACKAGE= "bitops")$val
    x[is.na(a)] <- NA
    x
}
