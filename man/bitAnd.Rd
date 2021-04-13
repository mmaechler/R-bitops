\name{bitAnd}
\title{Bitwise And, Or and Xor Operations}
\alias{bitAnd}
\alias{bitOr}
\alias{bitXor}
\alias{\%&\%}
\alias{\%|\%}
\alias{\%^\%}
\description{
  Bitwise operations, \sQuote{and} (\code{\link{&}}),
  \sQuote{or} (\code{\link{|}}), and \sQuote{Xor} (\code{\link{xor}}).
}
\usage{
bitAnd(a, b)
a \%&\% b
bitOr (a, b)
a \%|\% b
bitXor(a, b)
a \%^\% b
}
\arguments{
  \item{a,b}{numeric vectors of compatible length, each treated as 32 bit \dQuote{strings}.}
}
\details{
  The bitwise operations are applied to the arguments cast as 32 bit
  (unsigned long) integers.  NA is returned wherever the magnitude of the
  arguments is not less than \eqn{2^31}, or, where either of the arguments is
  not finite.

  For bitwise \sQuote{not} (\code{\link{!}} in \R), use \code{\link{bitFlip}()}.
}
\value{
  non-negative integer valued numeric vector of maximum length of \code{a} or \code{b}.
}
\author{Steve Dutky; idea for operators: Dan L Robertson}
\seealso{\code{\link{bitFlip}}, \code{\link{bitShiftL}}; further,
  \code{\link{cksum}}.
}
\examples{
bitAnd(15,7) == 7 ;  identical(15 \%&\% 7, bitAnd(15, 7))
bitOr(15,7) == 15 ;  identical(15 \%|\% 7, bitOr (15, 7))
bitXor(15,7) == 8 ;  identical(15 \%^\% 7, bitXor(15,7))
bitOr(-1,0) == 4294967295 ; identical(-1 \%|\% 0, bitOr(-1,0))
}
\keyword{arith}
\keyword{utilities}
