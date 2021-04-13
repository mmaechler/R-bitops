\name{bitShiftL}
\alias{bitShiftL}
\alias{bitShiftR}
\alias{\%<<\%}
\alias{\%>>\%}
\title{Bitwise Shift Operator (to the Left or Right)}
\description{
  These functions shift integers bitwise to the left or to the right,
  returning \emph{unsigned int}egers, i.e., values in
  \eqn{{0, 1, \ldots, 2^{32}-1}}.
}
\usage{
bitShiftL(a, b)
a \%<<\% b
bitShiftR(a, b)
a \%>>\% b
}
\arguments{
  \item{a}{numeric vector (integer valued), to be shifted.}
  \item{b}{integer (valued) vector.  Internally, only \code{b \%\% 32}
    is used, e.g, \code{b = 32} is equivalent to \code{b = 0}, i.e.,
    \emph{no} shift.  This corresponds to \emph{cyclic} rotation (to the
    left or right).}
}
%% \details{
%% }
\value{
  non-negative integer valued numeric vector of maximum length of
  \code{a} or \code{b} containing
  the value of \code{a} shifted to the left or right by \code{b} bits.
  NA is returned wherever the value of \code{a} or \code{b} is not finite,
  or, wherever the magnitude of \code{a} is greater than or equal to
  \eqn{2^{32}}.
}
%\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
\seealso{\code{\link{bitFlip}}, \code{\link{bitXor}}, etc.}
\examples{
 bitShiftL(0:4, 1) # 0 2 4 6 8
 bitShiftL(0:3, 2) # 0 4 8 12

 stopifnot(exprs = {
     identical(bitShiftL(0:4, 1), 0:4 \%<<\% 1)
     identical(bitShiftR(0:3, 2), 0:3 \%>>\% 2)
})

 bitShiftR(0:7, 1) # 0 0  1 1  2 2  3 3 <==> N \%/\% 2
 bitShiftR(0:7, 2) # 0 0 0 0  1 1 1 1   <==> N \%/\% 4
 ## all outputs are "unsigned integer" :
 stopifnot( bitShiftL(-1, 0) == 2^32 - 1   ,
            bitShiftL(-7, 0) == 4294967289 ,
            bitShiftL(-7, 0) == bitShiftR(-7, 0))

 bitShiftR(-1,1) == 2147483647
 bitShiftL(2147483647,1) == 4294967294 # <==> * 2
 bitShiftL( -1,       1) == 4294967294

 bitShiftL(47, 32) # is 47

## 5 Christmas trees  ( bitShiftL *rotates* to the left)
t(outer(1:5, 0:40, bitShiftL))

N <- as.numeric( rpois(1000, 100) )
stopifnot(identical(bitShiftL(N,0),   N),
          identical(bitShiftL(N,1), 2*N),
          identical(bitShiftL(N,2), 4*N),
          ## right shift:
          identical(bitShiftR(N,2), N \%/\% 4),
          identical(bitShiftR(N,4), N \%/\% 16))
}
\keyword{arith}
\keyword{utilities}
