;;This program reads and executes code, translating high-level instructions 
;;into machine actions on the fly. Unlike a compiler, which translates 
;;the entire program before execution, an interpreter works line by line or statement by statement.

(ns csinterpreter.core
  (:gen-class))
;;Grammar for mini-program language

;;<stmt> ::= <assign> | <inc> |<cond> |<loop> |	<display>
;;<assign>  ::=  <val>  “:=”  < expression>
;;<expression>  = <term> { “+” <term> }.
;;<term> = <factor>  {"*” <factor> }
;;<factor ::=  “(“ <expression> “)” | letter | digit
;;<digit> ::=  “0”| “1”| “2”| “3”|... | “998”| “999”
;; <letter> ::=  “a” | “b” ... | “y” | “z”
;;<inc> ::=  <val>  "+" < val >
;;<val> ::= “(”  <digit> “)”  | <letter>
;;<cond> ::=  < if-then> <conditionals>
;;<if-then > ::= “(”  <if> “)” | <if-then>
;;<if> ::= ‘“f” | “else”
;<conditionals> ::=  <factor> < relational  > <value>.
;<relational>  ::= "=" | "!="
;;<loop> ::= <conditions> <state_list>
;;<conditions> ::= <expressions> ( “<” | “>” | “=” | “|!=” ) <expression>
;;state_list> ::= <stmt> { “;” <stmt> }
;;<display> ::= “(display “ <expression> “)”
;;<value>::= <factor>


;;Handles errors


;;Empty map that tracks variable
(def env (atom {}))

;;Evaluates expression
(defn eval-expr [expr]
  (cond
    (number? expr) expr
    (symbol? expr) (get @env expr)
    (seq? expr) (case (first expr)
                   inc (inc (eval-expr (second expr)))
                   < (< (eval-expr (second expr)) (eval-expr (nth expr 2)))
                   > (> (eval-expr (second expr)) (eval-expr (nth expr 2)))
                   = (= (eval-expr (second expr)) (eval-expr (nth expr 2)))
                   + (+ (eval-expr (second expr)) (eval-expr (nth expr 2)))
                   (throw (Exception. (str " Unknown operation: " (first expr)))))
    :else (throw (Exception. (str "Invalid expression: " expr)))))


;;Evaluates operation
(defn interpret [stmt]
  (if (seq? stmt)
    (if (keyword? (first stmt))
      (case (first stmt)

;;Assigns expression to variable
        := (swap! env assoc (second stmt ) (eval-expr (nth stmt 2)))
;;Display
        :display (println (eval-expr (second stmt)))
        (throw (Exception. (str "Invalid op: " (first stmt)))))

      (case (first stmt)
          inc (swap! env update  (second stmt) inc)

;;Condition
        if (if (eval-expr (second stmt))
            (interpret (nth stmt 2))
               (when (> (count stmt ) 3) (interpret (nth stmt 3))))

;;Loop
        for (let [[_[var start end] & body ] stmt]
              (doseq [i (range (eval-expr start) (inc (eval-expr end)))]
                (swap! env assoc var i)
                (doseq [s body] (interpret s))))

      (doseq [s stmt ] (interpret s))))
    (throw (Exception. (str "Invalid statement: " stmt )))))

;;Function to interpret a mini-pl program
(defn mini-pl-interpret [program]
  (reset! env {})
  (try
(interpret program)
(catch Exception e
      (println "Error:" (.getMessage e)))))

;;Test Examples
(def example1
  '(
    (:= x 3)
    (:= x (inc x))
    (for [i 100 110]
      (:= x (inc x))
      (:display i))
    (if (< x 14)
      (:= y 10)
      (:= y 0))
    (:display y)))

(def example2
  '(
    (:= x 3)
    (inc x)
    (if (< x 14)
      ((:= y 10)
       (inc y (inc y)))
    ((:= y 0)))
      (:display y)))
;;Main function for testing
(defn -main
  []
  (println "Running example 1: ")

  (mini-pl-interpret example1)


  (println "\n Running example 2: ")


  (mini-pl-interpret example2))


