\name{bitShiftL}
\alias{bitShiftL}
\alias{bitShiftR}
\title{Bitwise Shift Operator (to the Left or Right)}
\description{
 .......
}
\usage{
bitShiftL(a, b)
bitShiftR(a, b)
}
\arguments{
  \item{a}{numeric vector }
  \item{b}{integer vector }
}
%\details{
%  ~~ If necessary, more details than the __description__  above ~~
%}
\value{
  numeric vector of the maximum length as \code{a} or \code{b} containing
  the value of \code{a} shifted to the left or right by \code{b} bits.
  NA is returned wherever the value of \code{a} or \code{b} is not finite,
  or, wherever the magnitude of \code{a} is greater than or equal to 2**32.
}
%\references{ ~put references to the literature/web site here ~ }
%\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
%\seealso{ ~~objects to See Also as \code{\link{~~fun~~}}, ~~~ }
\examples{
  bitShiftR(-1,1) == 2147483647
  bitShiftL(2147483647,1) == 4294967294
  bitShiftL(-1,1) == 4294967294

}
\keyword{arith}
\keyword{utilities}
