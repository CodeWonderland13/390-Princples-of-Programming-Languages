(ns mini-pl-example1.core
(:gen-class))
;;Calculate factorial
(defn factorial [n]
  (if ( = n 1)
    1
    (* n (factorial (dec n)))))
(defn main []
  (let [x 3]
    (println "Iinital value of x:" x)
 (inc x)
 (println "After incrementing x:" x)
 (if (< x 5)
    (do
        (println " x is less than 5")
        (println "Factorial of x: " (factorial x)))
        (println " x is not less than 5 "))))
(main)