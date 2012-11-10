library(bitops)

i7 <- 0:127
ri7 <- bitFlip(i7)
stopifnot(identical(ri7, -(1:1 + i7)),
          identical(i7, bitFlip(ri7)),
          bitAnd(i7, ri7) == 0,

          bitAnd(15,17) ==  1,
          bitOr (15,17) == 31,
          bitXor(15,17) == 30
          )

for(N in 1:200) {
    j7 <- sample(i7)
    ## Commutative Law:
    stopifnot(identical(bitOr (i7, j7), bitOr (j7, i7)),
              identical(bitAnd(i7, j7), bitAnd(j7, i7)),
              identical(bitXor(i7, j7), bitXor(j7, i7)))
    ## Xor "+" And  == Or :
    stopifnot(identical(bitOr(i7, j7),
                        bitOr(bitXor(i7,j7), bitAnd(i7,j7))))
    ## Logic:  !(A & B)  <->  (!A) | (!B)
    stopifnot(identical(bitFlip(bitAnd(i7, j7)),
                        bitOr(bitFlip(i7), bitFlip(j7))))
    ##         !(A | B)  <->  (!A) & (!B)
    stopifnot(identical(bitFlip(bitOr(i7, j7)),
                        bitAnd(bitFlip(i7), bitFlip(j7))))
    ## Associative Law:
    k7 <- sample(j7)
    stopifnot(identical(bitOr(bitOr(i7, j7), k7),
                        bitOr(i7, bitOr(j7, k7))),
              identical(bitAnd(bitAnd(i7, j7), k7),
                        bitAnd(i7, bitAnd(j7, k7))),
              identical(bitXor(bitXor(i7, j7), k7),
                        bitXor(i7, bitXor(j7, k7))))
}
