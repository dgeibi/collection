#! /usr/bin/scheme --script

(import (rnrs))
(define (print x)
  (display x)
  (newline))

(define (check n)
  (- (fib n) (xx n)))

(define (fib n)
  (fib-iter 1 0 n))

(define (fib-iter a b count)
  (if (= count 0)
    b
    (fib-iter (+ a b) a (- count 1))))

(define (xx n)
  (/ (- (expt (/ (+ 1 (sqrt 5.0)) 2) n) (expt (/ (- 1 (sqrt 5.0)) 2) n)) (sqrt 5.0)))

(print (check 4))
(print (check 6))
