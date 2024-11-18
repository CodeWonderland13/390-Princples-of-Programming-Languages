% Facts 

male(tim).
male(steve).
male(tom).
male(lloyd).
male(dan).
male(george).
male(lewis).

female(claire).
female(samantha).
female(daphne). 
female(lindy).
female(list).
female(lynn).
female(cristine). 
female(nancy).
female(rebecca).


child(nancy,daphne).
child(nancy,tim).
child(steve, daphne).
child(steve, tim).
child(lynn, nancy).
child(lynn, tom).
child(lisa,nancy).
child(lisa,tom).
child(lindy,lynn).
child(lindy,lloyd).
child(george,lynn).
child(george,lloyd).
child(samantha, george).
child(samantha,rebecca).
child(lewis,george).
child(lewis,rebcca).
child(clare,dan).
child(claire,lisa).


%Rules

%Parent relationship
parent(P,C) :-
	child(C,P).

%Sibling relationship
sibling(X,Y) :-
	parent(P,X), 
	parent(P,Y), X\=Y.

%Sister and brother
sister(S,Y) :-
    siblings(S,Y), female(S).
brother(B,Y):-
    siblings(B,Y), male(B).

%Great Aunt and Uncle
great_aunt_or_uncle(GAU,N) :-
    grandparent(GP,N),sibling(GAU,GP).
great_aunt(GA,N):-
    great_aunt_or_uncle(GA,N),female(GA).
great_uncle(GU,N):-
    great_aunt_or_uncle(GU,N), male(GU).

%Great Grandparent
great_grandparent(GGP,GGC) :-
    grandparent(GP,GGC),grandparent(GGP,GP).
great_grandmother(GGM,GGC) :-
    great_grandparent(GGM,GGC), female(GGM).
great_grandfather(GGF,GGC) :- great_grandparent(GGF,GGC), male(GGF).

%Grandparent relationship
grandparent(GP,GC) :-
	parent(GP,P),
	parent(P, GC).

%Grandmother and grandfather
grandmother(GM,GC):-
    grandparent(GM,GC),female(GM).
    grandfather(GF,GC):-grandparent(GF,GC), male(GF).

%Aunt and Uncle Relationship
auntorUncle(AU,N) :-
	sibling(AU,P), 
	parent(P,N).

%firstCousin Relationship
first_cousin(C1,C2) :- 
	parent(P1,C1), 
	parent(P2,C2), 
	sibling(P1,P2).

%SecondCousin Relationship
second_cousin(C1,C2) :- 
	parent(P1,C1), 
	parent(P2,C2), 
	first_cousin(P1,P2).

%ThirdCousin relaitionship 
third_cousin(C1,C2) :- 
	parent(P1,C1),
	parent(P2,C2), 
	second_cousin(P1,P2).

cousins_degree(C1,C2,1) :- 
	first_cousin(C1,C2).
cousins_degree(C1,C2,2) :- 
	second_cousin(C1,C2).
cousins_degree(C1,C2,3) :- 
	third_cousin(C1,C2).

cousins_degree(C1,C2,INT) :- 
	INT > 3, parent(P1,C1), 
	parent(P2,C2), 
	INT1 is INT-1,
	cousins_degree(P1,P2,INT1).

%Ancestor
ancestor(Person,Descendant,0):-
    Ancestor = Person.
ancestor(Person,Ancestor, INT) :-
    INT > 0,
    INT1 is INT-1,
    parent(Parent,Person),
    ancestor(Parent,Ancestor,INT1).

%Descendant
descendant(Person,Descendant, 0) :-
    Descendant = Person.
descendant(Person, Descendant, INT) :-
INT = 0,
INT1 is INT - 1,
parent(Person,Child),
descendant(Child,Descendant,INT1).

%All Cousins Removed
all_cousins(Person,Degree, ListOfCousins) :-
    findall(Cousin, cousins_degree(Person, Cousin, Degree), ListOfCousins).

all_cousins(Person,Degree,Removed, up,ListOfCousins):-
    findall(Cousin, (ancestor(Person,Ancestor,Removed),cousins_degree(Descendant,Cousin,Degree)),ListOfCousins).

%Checking if single child
is_single_child(Person) :-
\+ sibling(Person,_), !.
