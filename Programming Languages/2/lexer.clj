(ns .hw2)



(defn tokenizeList                                          ;;Tokenizes given list

  [Liste]

  (def x (count Liste))


  (def i (atom (+ x -1)))
  (def newList '())
  (while (>= @i 0) (do (def newList (conj newList (seq (nth Liste @i)))) (swap! i dec)))

  newList

  )


(defn read-file [filename]
  (clojure.string/split (slurp filename) #"\s+()")

  )


(defn seperate_First_Paranthesis [tokens]                   ;;Tokenizes Left paranthesis
  (def p [])               ;;A temporary container
  (def size (count tokens))
  (def newList tokens)          ;;Input vector copied
  (loop [i 0]
    (when (> size i)

      (def temp (nth newList 0))   ;;A temporary that holds an element of input list
      (def newList (subvec  newList 1))



      (loop []
        (when (and  (not-empty temp)  (= \( (nth temp 0)));;When first element of the string is left paranthesis and not empty
        (def temp (subs temp 1))      ;;Remove first character of the string.It's a left paranthesis


        (def p (conj p "("))        ;;Add a left paranthesis to the temporary container

        (recur)
        )
      )
      (if (not-empty temp)
        (def p (conj p temp))  ;;Add a whatever is left of that string to the temporary container

        )

      (recur (+ i 1)))
    )


  p;;Return

  )

(defn seperate_Last_Paranthesis [tokens]  ;;Tokenizes Right paranthesis
  (def p [])             ;;A temporary container
  (def cnt 0)            ;; A counter
  (def size (count tokens));;Size of tokens input list
  (def newList tokens)     ;;Input list copied
  (loop [i 0]
    (when (> size i)

      (def temp (nth newList i));;A temporary that holds an element of input list

      (loop []
        (when (and (not-empty temp)  (= \) (last temp )));;When LAST element of the string is right paranthesis and not empty
          (def temp (subs temp 0 (- (count temp) 1) ) );;Remove first character of the string.It's a right paranthesis
          (def cnt (+ cnt 1))  ;;Increment the counter

          (recur)
          )
        )

      (if (not-empty temp)
        (def p (conj p temp))  ;;Add whatever left of the string to the temporary container
        )

      (loop [j 0]
        (when (< j cnt)
          (def p (conj p ")")) ;;Add as right paranhesis as the size of 'cnt' variable
          (recur (+ j 1))
          )

        )
      (def cnt 0);;Reset counter

      (recur (+ i 1)))
    )


  p     ;;Return

  )







(defn lexer [filename]                                      ;;;;LEXER  LEXER  LEXER  LEXER  LEXER  LEXER  LEXER  LEXER  LEXER  LEXER  LEXER

  (def dictionary (read-file filename))
  (def seperate1 (seperate_First_Paranthesis dictionary))


  (def tokenized (seperate_Last_Paranthesis seperate1))

  (println tokenized)
  (def size (count tokenized))
  (loop [i 0]
    (when (> (- size 1)  i)

       (cond
        (= (nth tokenized i) "equal") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "and") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "or") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "not") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "append") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "concat") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "set") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "deffun") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "for") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "while") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "if") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "then") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "else") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "true")(println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "false") (println (nth tokenized i ) " : Keyword" )
        (= (nth tokenized i) "+") (println (nth tokenized i )" : Operator" )
        (= (nth tokenized i) "-") (println (nth tokenized i )" : Operator" )
        (= (nth tokenized i) "(") (println (nth tokenized i )" : Operator" )
        (= (nth tokenized i) ")") (println (nth tokenized i )" : Operator" )
        (= (nth tokenized i) "*") (println (nth tokenized i )" : Operator" )
        (= (nth tokenized i) "/") (println (nth tokenized i )" : Operator" )
        (number? (read-string  (nth tokenized i)) ) (println (nth tokenized i )" : Integer" )
        :else (println (nth tokenized i )" : Identifier" )


         )


      (recur (+ i 1)))
    )

    (def newList (into '() tokenized))
    (def newList (tokenizeList newList ) )
    newList
  )


(println   (lexer "CoffeeSample.coffee"))
