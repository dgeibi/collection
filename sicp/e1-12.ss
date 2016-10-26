#! /usr/bin/scheme --script

(import (rnrs))
(define (print x)
  (display x)
  (newline))

(define (pascal a b)
  (if (or (= b 1) (= a b))
    1
    (+ (pascal (- a 1) b) (pascal (- a 1) (- b 1)))))

(print (pascal 1 1))
(print (pascal 5 3))

