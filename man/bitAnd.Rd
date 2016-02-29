\name{bitAnd}
\alias{bitAnd}
\alias{\%&\%}
\alias{bitOr}
\alias{\%|\%}
\alias{bitXor}
\alias{\%^\%}
\title{Bitwise And, Or and Xor Operations}
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
  \item{a,b}{numeric vectors of compatible length.}
}
\details{
  The bitwise operations are applied to the arguments cast as 32 bit
  (unsigned long) integers.  NA is returned wherever the magnitude of the
  arguments is not less than \eqn{2^31}, or, where either of the arguments is
  not finite.
}
\value{
  non-negative integer valued numeric vector of maximum length of \code{a} or \code{b}.
}
%\references{ ~put references to the literature/web site here ~ }
\author{Steve Dutky}
\seealso{\code{\link{bitFlip}}, \code{\link{bitShiftL}}; further,
  \code{\link{cksum}}.
}
\examples{
	bitAnd(15,7) == 7
    15 \%&\% 7 == 7
	bitOr(15,7) == 15
    15 \%&\% 7 == 15
	bitXor(15,7) == 8
    15 \%^\% 7 == 8
	bitOr(-1,0) == 4294967295
    -1 \%|\% 0 == 4294967295
}
\keyword{arith}
\keyword{utilities}
