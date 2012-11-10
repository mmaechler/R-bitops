\name{bitFlip}
\alias{bitFlip}
\title{Binary Flip (Not) Operator}
\description{
  Binary flop (not) operator.
}
\usage{
bitFlip(a, bitWidth=32)
}
\arguments{
  \item{a}{numeric vector.}
  \item{bitWidth}{scalar integer between 0 and 32.}
}
\value{
  binary numeric vector of the same length as \code{a} masked with
  (2**\code{bitWidth})-1. NA is returned for any value of \code{a} that
  is not finite or whose magnitude is greater or equal to 2**32.
}
\author{ Steve Dutky <sdutky@terpalum.umd.edu> }
\examples{
  bitFlip(-1) == 0
  bitFlip(0) == 4294967295
  bitFlip(0,bitWidth=8) == 255
}
\keyword{arith}
\keyword{utilities}
