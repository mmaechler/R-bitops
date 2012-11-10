\name{bitAnd}
\alias{bitAnd}
\alias{bitOr}
\alias{bitXor}
\title{Bitwise And, Or and Xor operations}
\description{
  returns the bitwise operation applied to the arguments
}
\usage{
bitAnd(a, b)
bitOr (a, b)
bitXor(a, b)
}
\arguments{
  \item{a,b}{numeric vectors of compatible length.}
}
\details{
  The bitwise operations are applied to the arguments cast as 32 bit
  (unigned long) integers.  NA is returned wherever the magnitude of the
  arguments is not less than 2**31, or, where either of the arguments is
  not finite.

}
\value{
  numeric vector of maximum length of \code{a} or \code{b}.

}
%\references{ ~put references to the literature/web site here ~ }
\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
%\seealso{ ~~objects to See Also as \code{\link{~~fun~~}}, ~~~ }
\examples{
	bitAnd(15,7) == 7
	bitOr(15,7) == 15
	bitXor(15,7) == 8
	bitOr(-1,0) == 4294967295

}
\keyword{arith}
\keyword{utilities}
