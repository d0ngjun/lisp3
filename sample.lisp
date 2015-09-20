#!./lisp3

; empty
()

; constant number
-1
0
1

; free variable with no value.
a

; primitive calculous
(+ 0 1)
(- 2 3)
(* 4 5)
(/ 6 7)

; define global variable
(define a 8)
a

; define local variable
(let x 9 (+ x 1))
; will not find the value of x above.
x

; lambda expression.
(lambda (x) (+ x 10))

; invoke lambda expression.
((lambda (x) (+ x 11)) 0)

; assign a lambda expression to a variable.
(define x (lambda (x y) (+ x y)))
x
; use x to calculate.
(x 12 0)

; high order function.
(define high (lambda (x) (lambda (y) (+ x y))))
high
((high 13) 14)
(define hight (high 15))
hight
(hight 16)

; if expression.
(if (> 1 0) (+ 17 18) (+ 19 20))
; if expression without 'else' clause.
(if (> 1 1) (+ 21 22))

; define a recursive function. 'sum' will calculate the sum of [0, n].
(define sum
  (lambda (n)
    (if (> n 1)
      (+ n (sum (- n 1)))
      n)))
(sum 100)

; use operator '+' as a parameter.
(define sumf
  (lambda (f n)
    (if (> n 1)
      (f n (sumf f (- n 1)))
      n)))
(sumf + 100)

; use anonymous lambda for calculation.
(let ten 10
  ((lambda (n)
    (if (> n 1)
      (+ n (sum (- n 1)))
        n)) ten))

; tail recursion.
(define sum_tail
  (lambda (n s)
    (if (= n 0)
      s
      (sum_tail (- n 1) (+ s n)))))
(sum_tail 10 0)
