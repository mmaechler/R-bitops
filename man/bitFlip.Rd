\name{bitFlip}
\alias{bitFlip}
\title{Binary Flip (Not) Operator}
\description{
  ...
}
\usage{
bitFlip(a, bitWidth=32)
}
\arguments{
  \item{a}{numeric vector.}
  \item{bitWidth} {scalar interger between 0 and 64}
}
\value{
  binary numeric vector of the same length as \code{a} masked with
  (2**\code{bitWidth})-1. NA is returned for any value of \code{a} that
  is not finite or whose magnitude fails to resolve 1 (ie > 2**52).
}
%\references{ ~put references to the literature/web site here ~ }
\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
%\seealso{ ~~objects to See Also as \code{\link{~~fun~~}}, ~~~ }
\examples{
}
\keyword{arith}
\keyword{utilities}
