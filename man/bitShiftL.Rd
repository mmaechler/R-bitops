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
  or, wherever the magnitude of \code{a} fails to resolve 1.
}
%\references{ ~put references to the literature/web site here ~ }
%\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
%\seealso{ ~~objects to See Also as \code{\link{~~fun~~}}, ~~~ }
\examples{

}
\keyword{arith}
\keyword{utilities}
