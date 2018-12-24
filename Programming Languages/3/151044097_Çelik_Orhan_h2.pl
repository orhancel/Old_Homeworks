flight(istanbul,izmir,3).

flight(izmir,istanbul,3).

flight(izmir,antalya,1).

flight(antalya,izmir,1).

flight(antalya,diyarbakır,5).

flight(diyarbakır,antalya,5).

flight(diyarbakır,konya,1).

flight(konya,diyarbakır,1).

flight(konya,ankara,8).

flight(ankara,konya,8).

flight(konya,kars,5).

flight(kars,konya,5).

flight(kars,gaziantep,3).

flight(gaziantep,kars,3).

flight(ankara,trabzon,2).

flight(trabzon,ankara,2).

flight(ankara,istanbul,5).

flight(istanbul,ankara,5).

flight(trabzon,istanbul,3).

flight(istanbul,trabzon,3).

flight(ankara,izmir,6).

flight(izmir,ankara,6).

flight(edirne,edremit,5).

flight(edremit,edirne,5).

flight(edremit,erzincan,7).

flight(erzincan,edremit,7).



route(X,Y,Z) :- flight(X,Y,Z).



routeA(X,Y,Z) :- flight(X,Y,Z).

routeA(X,Y,Z) :- router(X,Y,Z,0,[]).
	

router(X,Y,K,C1,_):-

    flight(X,Y,_), flight(X,Y,C2), K is C1+C2.

router(X,Y,K,C,V):-
    not(member(X,V)),
	append(V,[X],V1),
    flight(X,Z,T),C1 is C+T,

    router(Z,Y,K,C1,V1).

max(X):- findall(T,flight(_,_,T),L), sum_list(L,X).

    
sum_list([], 0).
sum_list([H|T], Sum) :-
   sum_list(T, Rest),
   Sum is H + Rest.

croute(X,Y,M):- 

     findall(Z,routeA(X,Y,Z),L),/*Get all posible paths and put them in a list*/
    max(Max_Path),/*This is cumulation of all paths in the map.Just for comparison with other paths.*/
	min(L,Max_Path,M),!,not(M=Max_Path). /*Find shortest path*/

min([],M,R):- R is M.

min([H|T],M,R) :- 
    H<M ,
    min(T,H,R).
min([_|T],M,R) :-
    min(T,M,R).
    


when(a,10).
when(b,12).
when(c,11).
when(d,16).
when(e,17).

when(x,9).
when(y,12).

where(a,101).
where(b,104).
where(c,102).
where(d,103).
where(e,103).

where(x,103).
where(y,102).


where(1,a).
where(1,b).
where(2,a).
where(3,b).
where(4,c).
where(5,d).
where(6,a).
where(6,d).

where(7,x).
where(7,y).
where(8,x).
where(8,a).
where(9,y).
where(10,a).
where(11,b).


schedule(S,P,T) :- where(S,P) , when(P,T).
usage(P,T) :- where(S,P),when(S,T).
conflict(X,Y) :- where(X,P1) ,when(X,T1) , where(Y,P2),when(Y,T2) , P1=P2 , (T1-T2)<2 .
meet(X,Y) :- where(X,S1), when(S1,T1),where(S1,P1),where(Y,S2), when(S2,T2),where(S2,P2),  S1=S2 , P1=P2 , (T1-T2)<2.







union([], L, L).
union([Head|L1tail], L2, L3) :-
       member(Head, L2),
    	!,
        union(L1tail, L2, L3).
union([Head|L1tail], L2, [Head|L3tail]) :-
        union(L1tail, L2, L3tail).


intersect([],_,[]).
intersect([Head1|Tail1],L2,I):-
    	not(member(Head1, L2)),
    	!,
        intersect(Tail1, L2, I).
intersect([Head1|Tail1], L2, [Head1|Tail3]) :-
        intersect(Tail1, L2, Tail3).

flatten(List, Flat) :-
        flatten(List, Flat, []).

flatten([], Res, Res) :- !.
flatten([Head|Tail], Res, Cont) :-
        !,
        flatten(Head, Res, Cont1),
        flatten(Tail, Cont1, Cont).
flatten(Term, [Term|Cont], Cont).
    


