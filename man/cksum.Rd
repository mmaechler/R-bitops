\name{cksum}
\alias{cksum}
\title{Compute Check Sum}
\description{
  return a cyclic redundancy checksum for each element in the argument.
}
\usage{
cksum(a)
}
\arguments{
  \item{a}{coerced to character vector}
}
\details{
  NA's appearing in the argument are returned as NA's.

  The default calculation is identical to that given in pseudo-code in the
  ACM article (in the References).
}
\value{
  numeric vector of length \code{a}.
}
\references{
  Fashioned from \code{cksum(1)} UNIX command line utility, i.e.,
  \code{man cksum}.

  Dilip V. Sarwate (1988).
  Computation of Cyclic Redundancy Checks Via Table Lookup,
  \emph{Communications of the ACM}, August 1988.
  \bold{vol} 31, No.8  page 1008-1013
}
\author{Steve Dutky \email{sdutky@terpalum.umd.edu}
}
% \seealso{ ~~objects to See Also as \code{\link{~~fun~~}}, ~~~ }
\examples{
   b <- "I would rather have a bottle in front of me than frontal lobotomy\n"
   cksum(b) == 1342168430 ## -> TRUE
}
\keyword{arith}
\keyword{utilities}
