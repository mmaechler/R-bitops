\name{bitFlip}
\alias{bitFlip}
\title{Binary Flip (Not) Operator}
\description{
  The binary flip (\sQuote{not}, \R's \code{\link{!}}) operator, \code{bitFlip(a, w)}, \dQuote{flips every
    bit} of \code{a} up to the \code{w}-th bit.
}
\usage{
bitFlip(a, bitWidth = 32)
}
\arguments{
  \item{a}{numeric vector.}
  \item{bitWidth}{scalar integer between 0 and 32.}
}
\note{\code{bitFlip(a, w)} is an \dQuote{involution}, i.e. it is its own
  inverse -- \emph{when} \code{a} is in \eqn{\{0, 1, .., 2^{32}-1\}}.
  Notably, negative values \code{a} are equivalent to their values in the
  above range, see also \code{bitUnique()} in the \sQuote{Examples}.
}
\value{
  (\dQuote{binary}) numeric vector of the same length as \code{a} masked with
  (2^\code{bitWidth})-1.  \code{\link{NA}} is returned for any value of
  \code{a} that is not finite or whose magnitude is greater or equal to
  \eqn{2^{32}}.
}
\author{Steve Dutky}
\seealso{\code{\link{bitShiftL}}, \code{\link{bitXor}}, etc.}
\examples{
bitFlip(0:5)
##
bitUnique <- function(x) bitFlip(bitFlip(x)) # "identity" when x in  0:(2^32-1)
bitUnique(  0:16 ) # identical (well, double precision)
bitUnique(-(1:16)) # 4294967295 ...
stopifnot(
  identical(bitUnique(-(1:16)), 2^32 -(1:16)),
  bitFlip(-1) == 0,
  bitFlip(0 ) == 2^32 - 1,
  bitFlip(0, bitWidth=8) == 255
)
}
\keyword{arith}
\keyword{utilities}
