#! /usr/bin/scheme --script

(import (rnrs))
(define (f n)
  (cond (( < n 3) n )
        (else (+ (+ (f (- n 1)) (* 2 (f (- n 2)))) (* 3 (f (- n 3)))))))


(define (print xxx)
  (display xxx)
  (newline))

(print (f 3))
(print (f 9))
(print (f 12))
