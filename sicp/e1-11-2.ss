#! /usr/bin/scheme --script

(import (rnrs))

(define (f n)
  (fit 2 1 0 n))
(define (fit a b c count)
  (cond ((= count 0) c)
        ((= count 1) b)
        ((= count 2) a)
        (else (fit (+ (+ (* 2 b) a) (* 3 c)) a b (- count 1)))))

(define (print xxx)
  (display xxx)
  (newline))

(print (f 3))
(print (f 9))
(print (f 12))
