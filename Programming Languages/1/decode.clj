(ns .hw1)

(defn spell-checker-0
	[word dictionary]

	(if (>= (.indexOf dictionary word) 0) true false)


	;;(if (>= (.indexOf (read-file "D:\\dictionary2.txt") word) 0) true false)


	)

(defn read-as-list
	"Reads a file containing one word per line and returns a list of words (each word is in turn a list of characters)."
	[filename]
	(def Liste  (seq ( clojure.string/split-lines (slurp filename))) )
	(def x (count Liste))
	(def i (atom (+ x -1)))
	(def newList '())
	(while (>= @i 0 ) (do (def newList (conj  newList (seq (nth Liste @i))) )  (swap! i dec) )   )
	newList


	)


;;(println (read-as-list "dictionary2.txt"))


(defn read-file[filename]

	( clojure.string/split-lines (slurp filename))
	)


(defn check6 [word p-list dictionary]
	(def index0 (- (int (nth (word) 0 )) 97 ))
	(def index1 (- (int (nth (word) 1 )) 97 ))
	(def index2 (- (int (nth (word) 2 )) 97 ))
	(def index3 (- (int (nth (word) 3 )) 97 ))
	(def index4 (- (int (nth (word) 4 )) 97 ))
	(def index5 (- (int (nth (word) 5 )) 97 ))
	(def i (atom 0))
	(when (< @i (count (nth p-list index0 ) )  )
		(do (def k0 (nth  (nth  p-list index0) i))
				(def j (atom 0))
				(when (< @j (count (nth p-list index1 ) ) )

					(do (def k1 (nth  (nth  p-list index1) j))
							(def k (atom 0))
							(when (< @k (count (nth p-list index2 ) ) )

								(do (def k2 (nth  (nth  p-list index2) k))
										(def l (atom 0))
										(when (< @l (count (nth p-list index3 ) ) )

											(do (def k3 (nth  (nth  p-list index3) l))
													(def m (atom 0))

													(when (< @m (count (nth p-list index4 ) ) )

														(do  (def k4 (nth  (nth  p-list index4) m))
																 (def n (atom 0))
																 (when ( < @n (count (nth p-list index5 ) )  )

																	 (do  (def k5 (nth  (nth  p-list index5) n))

																				(def try-word  (str k0(str  k1(str  k2(str  k3(str k4(str k5)))))))

																				(if (spell-checker-0 try-word ))


																				)

																	 )

																 )

														)

													)

											)


										)

								)


							)

					)

				)

		)


	)


(defn check5 [word p-list  dictionary]
	(def index0 (- (int (nth (word) 0 )) 97 ))
	(def index1 (- (int (nth (word) 1 )) 97 ))
	(def index2 (- (int (nth (word) 2 )) 97 ))
	(def index3 (- (int (nth (word) 3 )) 97 ))
	(def index4 (- (int (nth (word) 4 )) 97 ))

	(def i (atom 0))
	(when (< @i (count (nth p-list index0 ) )  )
		(do (def k0 (nth  (nth  p-list index0) i))
				(def j (atom 0))
				(when (< @j (count (nth p-list index1 ) ) )

					(do (def k1 (nth  (nth  p-list index1) j))
							(def k (atom 0))
							(when (< @k (count (nth p-list index2 ) ) )

								(do (def k2 (nth  (nth  p-list index2) k))
										(def l (atom 0))
										(when (< @l (count (nth p-list index3 ) ) )

											(do (def k3 (nth  (nth  p-list index3) l))
													(def m (atom 0))

													(when (< @m (count (nth p-list index4 ) ) )

														(do  (def k4 (nth  (nth  p-list index4) m))

																 (def try-word  (str k0(str  k1(str  k2(str  k3(str k4)))))))



														)

													)

											)

										)


								)

							)


					)

				)

		)

	)


)



(defn check4 [word p-list  dictionary]
	(def index0 (- (int (nth (word) 0 )) 97 ))
	(def index1 (- (int (nth (word) 1 )) 97 ))
	(def index2 (- (int (nth (word) 2 )) 97 ))
	(def index3 (- (int (nth (word) 3 )) 97 ))

	(def i (atom 0))
	(when (< @i (count (nth p-list index0 ) )  )
		(do (def k0 (nth  (nth  p-list index0) i))
				(def j (atom 0))
				(when (< @j (count (nth p-list index1 ) ) )

					(do (def k1 (nth  (nth  p-list index1) j))
							(def k (atom 0))
							(when (< @k (count (nth p-list index2 ) ) )

								(do (def k2 (nth  (nth  p-list index2) k))
										(def l (atom 0))
										(when (< @l (count (nth p-list index3 ) ) )

											(do (def k3 (nth  (nth  p-list index3) l))

													(def try-word  (str k0(str  k1(str  k2(str  k3))))))

											)

										)


								)

							)


					)

				)

		)

	)


)


(defn check3 [word p-list  dictionary]
	(def index0 (- (int (nth (word) 0 )) 97 ))
	(def index1 (- (int (nth (word) 1 )) 97 ))
	(def index2 (- (int (nth (word) 2 )) 97 ))


	(def i (atom 0))
	(when (< @i (count (nth p-list index0 ) )  )
		(do (def k0 (nth  (nth  p-list index0) i))
				(def j (atom 0))
				(when (< @j (count (nth p-list index1 ) ) )

					(do (def k1 (nth  (nth  p-list index1) j))
							(def k (atom 0))
							(when (< @k (count (nth p-list index2 ) ) )

								(do (def k2 (nth  (nth  p-list index2) k))

										(def try-word  (str k0(str  k1(str  k2))))


										)

								)

							)


					)

				)

		)
	)





(defn check2 [word p-list  dictionary]
	(def index0 (- (int (nth (word) 0 )) 97 ))
	(def index1 (- (int (nth (word) 1 )) 97 ))


	(def i (atom 0))
	(when (< @i (count (nth p-list index0 ) )  )
		(do (def k0 (nth  (nth  p-list index0) i))
				(def j (atom 0))
				(when (< @j (count (nth p-list index1 ) ) )

					(do (def k1 (nth  (nth  p-list index1) j))

							(def try-word  (str k0(str  k1)))

							)


					)

				)

		)


	)

(defn find-in-common [str1 str2]

	(def i (atom (-  (count str1) 1))  )
	(def j (atom (-  (count str2) 1))  )

	(def newStr "")
	(while (>= @i 0 ) (do (def j (atom (-  (count str2) 1))  )
												(while (>= @j 0  ) (do
																						 (if (= (nth str1 @i) (nth str2 @j))  (def newStr (str newStr (nth str2 @j)))    ) (swap! j dec))  ) (swap! i dec) )   )

	newStr

	)

(defn Posibility-List [paragraph]

	(def posibility-list [""  ""  ""  "" ""  ""  ""  "" ""  ""  ""  "" ""  ""  ""  "" ""  ""  ""  "" ""  ""  ""  "" "" "" ])
	(def dictionary (read-as-list "D:\\dictionary2.txt"))
	(def dictionary (into [] dictionary) )
	(def dictionary (partition-by count (sort-by count dictionary)) )

	(into [] paragraph)
	(def i (atom 0))
	(while (< @i (count paragraph))
		(do  (def word (nth paragraph @i))
				 (println  "i  " @i)
				 (def tempi i)
				 (def j (atom 0))
				 (if (= 1 (count word) )
					 (do
						 (def posibility-list (assoc posibility-list (- (int (nth word 0)) 97 ) "ia"))


						 )

					 (while (< @j (count word))
						 (do
							 (println "count-2  " (- (count word) 2))
							 (println word)
							 (def dictionary-words-list (nth dictionary (- (count word) 2) ))
							 (def karakter (nth word @j))
							 (def index (- (int karakter) 97 ))
							 (println "index  " index )
							 (println "karakter  " karakter)
							 (println "posibility-list  " posibility-list)
							 (println "j " @j)
							 (def new-str "")
							 (def k (atom 0))
							 (while (< @k (count dictionary-words-list))
								 (do
									 (def dictionary-word (nth dictionary-words-list @k))
									 ;;(println "k  " @k)
									 ;;(println  "dictionary-word  "  dictionary-word)
									 (if ( < (.indexOf new-str (str (nth dictionary-word @j) ) ) 0 )

										 (def new-str (str new-str (str (nth dictionary-word @j) ) ))
										 )

									 ;;(println  "new-str  " new-str)

									 (swap! k inc)
									 )
								 (def temp j)
								 )
							 (if (empty? (nth posibility-list index))

								 (def posibility-list (assoc posibility-list index new-str))

								 (def posibility-list (assoc posibility-list index (find-in-common (nth posibility-list index) new-str)))

								 )
							 (def j temp)
							 (println "j inc "  @j)
							 (swap! j inc)
							 )
						 )
					 )

				 (def i tempi)
				 (println "i inc " @i)
				 (swap! i inc)
				 )


		)
	posibility-list




	)


(defn Gen-Decoder-A                                         ;;Returns posibilities of letters.Index 0 is a 1 is b 2 is c and so on..
	[paragraph]
	(def dictionary (read-as-list "D:\\dictionary2.txt"))
	(def posibilities-list (Posibility-List paragraph))



	posibilities-list
	)



(println (Gen-Decoder-A (read-as-list "D:\\test.txt")))

;;(println (count (nth  ( partition-by count  (sort-by count  (read-file "D:\\dictionary2.txt")) ) 4  ) )    )


"

(def i (atom 0))
(while (< @i (count paragraph))
	(do
		(if (= 2 (count (nth paragraph i)) )
			(do



				)

			)

		(if (= 3 (count (nth paragraph i)) )
			(do



				)

			)

		(if (= 4 (count (nth paragraph i)) )
			(do



				)

			)

		(if (= 5 (count (nth paragraph i)) )
			(do



				)

			)

		(if (= 6 (count (nth paragraph i)) )
			(do



				)

			)




		)

	)




"







