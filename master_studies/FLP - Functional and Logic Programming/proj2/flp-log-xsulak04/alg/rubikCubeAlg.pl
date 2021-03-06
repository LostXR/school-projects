/*
* ---------------------------------------------------
* Name of the project		Rubikova kostka
* Author					Ladislav Sulak
* Login 					xsulak04
* Date						4/2016
* File 						rubikCube.pl
* Description				Project in Prolog for subject FLP (Functional and Logic Programming)
*							The aim of this project is to solve the Rubik's cube provided from standard input.
*							The current implementation solves only the upper 'cross' of the cube.
* Algorithm: 		http://thecube.guru/rubiks-cube-solution/
* Inspirated with:  http://www.amzi.com/ExpertSystemsInProlog/12rubikscube.php
* ----------------------------------------------------

Representation of Cube:

	555
	555		-> Upper side
	555
	111 222 333 444
	111 222 333 444		-> Middle: Front, Right, Back and Left faces
	111 222 333 444
	666
	666		-> Down side
	666

*/

:- dynamic solution/1. % Sequence of moves which leads to solution.


/* Prepared for high level rules (sequentions of rotations obtained from algorithms) */
firstStep(1, fMoveDownUp, [+f, +f]).
firstStep(1, lMoveDownUp, [+l, +l]).
firstStep(1, rMoveDownUp, [+r, +r]).
firstStep(1, bMoveDownUp, [+b, +b]).


/* 	
	Implementation of rotation itself - its based on unification.
	Cube is represented by list containing 6 lists, each for one side of cube.
	Numbers (indexes) are just in different order after rotation.
*/
rotate(+l, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[B9, U2, U3, B6, U5, U6, B3, U8, U9],
		 [U1, F2, F3, U4, F5, F6, U7, F8, F9],
		 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
		 [B1, B2, D7, B4, B5, D4, B7, B8, D1],
		 [L7, L4, L1, L8, L5, L2, L9, L6, L3],
		 [F1, D2, D3, F4, D5, D6, F7, D8, D9]].

rotate(-l, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[F1, U2, U3, F4, U5, U6, F7, U8, U9],
		 [D1, F2, F3, D4, F5, F6, D7, F8, F9],
		 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
		 [B1, B2, U7, B4, B5, U4, B7, B8, U1],
		 [L3, L6, L9, L2, L5, L8, L1, L4, L7],
		 [B9, D2, D3, B6, D5, D6, B3, D8, D9]].

rotate(+r, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, F3, U4, U5, F6, U7, U8, F9],
		 [F1, F2, D3, F4, F5, D6, F7, F8, D9],
		 [R7, R4, R1, R8, R5, R2, R9, R6, R3],
		 [U9, B2, B3, U6, B5, B6, U3, B8, B9],
		 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
		 [D1, D2, B7, D4, D5, B4, D7, D8, B1]].

rotate(-r, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, B7, U4, U5, B4, U7, U8, B1],
		 [F1, F2, U3, F4, F5, U6, F7, F8, U9],
		 [R3, R6, R9, R2, R5, R8, R1, R4, R7],
		 [D9, B2, B3, D6, B5, B6, D3, B8, B9],
		 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
		 [D1, D2, F3, D4, D5, F6, D7, D8, F9]].

rotate(+u, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U7, U4, U1, U8, U5, U2, U9, U6, U3],
		 [R1, R2, R3, F4, F5, F6, F7, F8, F9],
		 [B1, B2, B3, R4, R5, R6, R7, R8, R9],
		 [L1, L2, L3, B4, B5, B6, B7, B8, B9],
		 [F1, F2, F3, L4, L5, L6, L7, L8, L9],
		 [D1, D2, D3, D4, D5, D6, D7, D8, D9]].

rotate(-u, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U3, U6, U9, U2, U5, U8, U1, U4, U7],
		 [L1, L2, L3, F4, F5, F6, F7, F8, F9],
		 [F1, F2, F3, R4, R5, R6, R7, R8, R9],
		 [R1, R2, R3, B4, B5, B6, B7, B8, B9],
		 [B1, B2, B3, L4, L5, L6, L7, L8, L9],
		 [D1, D2, D3, D4, D5, D6, D7, D8, D9]].

rotate(+d, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
		 [F1, F2, F3, F4, F5, F6, L7, L8, L9],
		 [R1, R2, R3, R4, R5, R6, F7, F8, F9],
		 [B1, B2, B3, B4, B5, B6, R7, R8, R9],
		 [L1, L2, L3, L4, L5, L6, B7, B8, B9],
		 [D7, D4, D1, D8, D5, D2, D9, D6, D3]].

rotate(-d, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
		 [F1, F2, F3, F4, F5, F6, R7, R8, R9],
		 [R1, R2, R3, R4, R5, R6, B7, B8, B9],
		 [B1, B2, B3, B4, B5, B6, L7, L8, L9],
		 [L1, L2, L3, L4, L5, L6, F7, F8, F9],
		 [D3, D6, D9, D2, D5, D8, D1, D4, D7]].

rotate(+f, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, U3, U4, U5, U6, L9, L6, L3],
		 [F7, F4, F1, F8, F5, F2, F9, F6, F3],
		 [U7, R2, R3, U8, R5, R6, U9, R8, R9],
		 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
		 [L1, L2, D1, L4, L5, D2, L7, L8, D3],
		 [R7, R4, R1, D4, D5, D6, D7, D8, D9]].

rotate(-f, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U1, U2, U3, U4, U5, U6, R1, R4, R7],
		 [F3, F6, F9, F2, F5, F8, F1, F4, F7],
		 [D3, R2, R3, D2, R5, R6, D1, R8, R9],
		 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
		 [L1, L2, U9, L4, L5, U8, L7, L8, U7],
		 [L3, L6, L9, D4, D5, D6, D7, D8, D9]].

rotate(+b, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[R3, R6, R9, U4, U5, U6, U7, U8, U9],
		 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
		 [R1, R2, D9, R4, R5, D8, R7, R8, D7],
		 [B7, B4, B1, B8, B5, B2, B9, B6, B3],
		 [U3, L2, L3, U2, L5, L6, U1, L8, L9],
		 [D1, D2, D3, D4, D5, D6, L1, L4, L7]].

rotate(-b, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[L7, L4, L1, U4, U5, U6, U7, U8, U9],
		 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
		 [R1, R2, U1, R4, R5, U2, R7, R8, U3],
		 [B3, B6, B9, B2, B5, B8, B1, B4, B7],
		 [D7, L2, L3, D8, L5, L6, D9, L8, L9],
		 [D1, D2, D3, D4, D5, D6, R9, R6, R3]].

rotate(+z, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U7, U4, U1, U8, U5, U2, U9, U6, U3],
		 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
		 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
		 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
		 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
		 [D3, D6, D9, D2, D5, D8, D1, D4, D7]].

rotate(-z, 
	[[U1, U2, U3, U4, U5, U6, U7, U8, U9],
	 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
	 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
	 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]],
	Res) :-
	Res = 
		[[U3, U6, U9, U2, U5, U8, U1, U4, U7],
		 [L1, L2, L3, L4, L5, L6, L7, L8, L9],
		 [F1, F2, F3, F4, F5, F6, F7, F8, F9],
		 [R1, R2, R3, R4, R5, R6, R7, R8, R9],
		 [B1, B2, B3, B4, B5, B6, B7, B8, B9],
		 [D7, D4, D1, D8, D5, D2, D9, D6, D3]].


/* Tests if character is EOF or LF. */
isEOFEOL(C) :-
	C == end_of_file;
	(char_code(C, Code), Code == 10).


/*
	Reads line from stdin, terminates on LF or EOF. 
	If the current char is a space, skip it.
*/
readLine(L, C) :-
	get_char(C),
	(isEOFEOL(C), L = [], !;
		readLine(LL, _),
		(C == ' ' -> 
			(LL = L)
			;
			[C|LL] = L)).


/* Read specific number of the input Lines (9 for our cube). */
readLines([], 0).
readLines(Ls, N) :-
	N > 0,
	readLine(L,_),
	N1 is N-1,
	readLines(LLs, N1),
	Ls = [L|LLs].


/* Concatenates 3 lists. It is based on standard concatenation of 2 lists (append) principle. */
append3Lists([], [], L3, L3).
append3Lists([], [H2|T2], L3, [H2|Rest]) :-
	append3Lists([], T2, L3, Rest).
append3Lists([H1|T1], L2, L3, [H1|Rest]) :-
	append3Lists(T1, L2, L3, Rest).


/* Split line from the input to 4 lists - they are parts of 4 sides of the cube (front, back, right, left). */
splitSides([L1, L11, L111, L2, L22, L222, L3, L33, L333, L4, L44, L444], S1, S2, S3, S4) :-
	S1 = [L1, L11, L111],
	S2 = [L2, L22, L222],
	S3 = [L3, L33, L333],
	S4 = [L4, L44, L444].


/*
	Saves front, back, right and left sides of the cube to separate lists. 
	They were saved in three lines in the input originally.
*/
mergeMiddleSides(L4, L5, L6, Side2, Side3, Side4, Side5) :-
	splitSides(L4, S2firstPart,  S3firstPart,  S4firstPart,  S5firstPart),
	splitSides(L5, S2secondPart, S3secondPart, S4secondPart, S5secondPart),
	splitSides(L6, S2thirdPart,  S3thirdPart,  S4thirdPart,  S5thirdPart),

	append3Lists(S2firstPart, S2secondPart, S2thirdPart, Side2),
	append3Lists(S3firstPart, S3secondPart, S3thirdPart, Side3),
	append3Lists(S4firstPart, S4secondPart, S4thirdPart, Side4),
	append3Lists(S5firstPart, S5secondPart, S5thirdPart, Side5).


/*
	Input parameter is list containing 9 lists (lines from stdin/file) and 
	the output is a list containing 6 lists which represent 6 sides of cube. 
*/
fillCubeAsList([],[]).
fillCubeAsList([L1, L2, L3, L4, L5, L6, L7, L8, L9], Res) :- 
	append3Lists(L1, L2, L3, Side1),
	mergeMiddleSides(L4, L5, L6, Side2, Side3, Side4, Side5),
	append3Lists(L7, L8, L9, Side6),

	Res = [Side1, Side2, Side3, Side4, Side5, Side6].


/* Reading input and saving cube to the list representation. */
readCube(Cube) :-
	readLines(LL, 9),
	fillCubeAsList(LL, Cube).


/* Printing list containing 1 side of cube - for upper and bottom ones. */
print1Side([], _).
print1Side([H|T], C) :-
	Ci is C + 1,
	((Ci == 4; Ci == 7; Ci == 10) -> % Every side is printed this way - after 3 chars there is a new line.
	nl, write(H); write(H)),
	print1Side(T, Ci).


/*
	For splitting a middle sides into one list which can be easily outputted.
 	Format is same as for the input, as from the specification.
*/
splitMiddleSides(
	[[A1, A2, A3, A4, A5, A6, A7, A8, A9], 
	 [B1, B2, B3, B4, B5, B6, B7, B8, B9], 
	 [C1, C2, C3, C4, C5, C6, C7, C8, C9], 
	 [D1, D2, D3, D4, D5, D6, D7, D8, D9]], 
	Res) :- 
	Res =  [A1, A2, A3, ' ', B1, B2, B3, ' ', C1, C2, C3, ' ', D1, D2, D3, '\n',
			A4, A5, A6, ' ', B4, B5, B6, ' ', C4, C5, C6, ' ', D4, D5, D6, '\n',
			A7, A8, A9, ' ', B7, B8, B9, ' ', C7, C8, C9, ' ', D7, D8, D9, '\n'].


/* Prints cube to stdout. Used during outputting the final results of solving. */
writeCube([S1, S2, S3, S4, S5, S6]) :- 
	print1Side(S1, 0), nl,

	splitMiddleSides([S2, S3, S4, S5], Middle), 
	atom_string(Middle, Res), write(Res),	% Convert list to string for outputting.
	
	print1Side(S6, 0), nl, nl.


/* Check, if there is cross with correct edge colors in the middle. */
crossFinished([U, F, R, B, L, _], CrossCol, IsFinished) :-
	nth1(2, U, Cross1), 
	nth1(2, B, Edge1),
	nth1(5, B, MidEdge1),

	nth1(4, U, Cross2),
	nth1(2, L, Edge2),
	nth1(5, L, MidEdge2),

	nth1(6, U, Cross3),
	nth1(2, R, Edge3),
	nth1(5, R, MidEdge3),

	nth1(8, U, Cross4),
	nth1(2, F, Edge4),
	nth1(5, F, MidEdge4),

	(Cross1 == CrossCol, Cross2 == CrossCol, Cross3 == CrossCol, Cross4 == CrossCol,
	Edge1 == MidEdge1, Edge2 == MidEdge2, Edge3 == MidEdge3, Edge4 == MidEdge4 -> 
		IsFinished = true;
		IsFinished = fail).


/* Searching for specific color position on side. */
colorIsOnSide(Side, Col, Pos) :-
	nth1(2, Side, DstCol1), 
	nth1(4, Side, DstCol2),
	nth1(6, Side, DstCol3),
	nth1(8, Side, DstCol4),

	(DstCol1 == Col -> Pos = 2;
		(DstCol2 == Col -> Pos = 4;
			(DstCol3 == Col -> Pos = 6;
				(DstCol4 == Col -> Pos = 8;
					Pos = 0)))).


/*
	There is a field with cross-like color on bottom, we have to place him UP, 
	but with the correct edge color!
*/
rotateToCorrectSideDown(Pos, SearchingIn, ToMove, [U, F, R, B, L, D], ResCube) :-
	nth1(8, SearchingIn, NeighborCol),
	nth1(5, SearchingIn, MidNeighborCol),
	(MidNeighborCol == NeighborCol -> 
		firstStep(1, ToMove, Move),
		sequences(Move, [U, F, R, B, L, D], ResCube)
		;
		sequences([+d], [U, F, R, B, L, D], [U2, F2, R2, B2, L2, D2]),
		(Pos == 2 -> NextSearchingIn = R2, NextToMove = rMoveDownUp, NextPos = 6;
			(Pos == 4 -> NextSearchingIn = F2, NextToMove = fMoveDownUp, NextPos = 2;
				(Pos == 6 -> NextSearchingIn = B2, NextToMove = bMoveDownUp, NextPos = 8;
					(Pos == 8 -> NextSearchingIn = L2, NextToMove = lMoveDownUp, NextPos = 4; fail)))),
		rotateToCorrectSideDown(NextPos, NextSearchingIn, NextToMove, [U2, F2, R2, B2, L2, D2], ResCube)).


/* Rotate bottom colors to the correct position Upper */
moveDownCol(Pos, [U, F, R, B, L, D], Res) :- 
	(Pos == 2 -> SearchIn = F, ToMove = fMoveDownUp;
		(Pos == 4 -> SearchIn = L, ToMove = lMoveDownUp;
			(Pos == 6 -> SearchIn = R, ToMove = rMoveDownUp;
				(Pos == 8 -> SearchIn = B, ToMove = bMoveDownUp)))),
	rotateToCorrectSideDown(Pos, SearchIn, ToMove, [U, F, R, B, L, D], Res).


/* Moves colors from middle sides, according to algorithm */
moveMiddleCol(Pos, [U, F, R, B, L, D], Res) :- 
	nth1(5, F, MidNeighborCol),
	(Pos == 2 -> 
		nth1(8, U, NeighborCol),
		sequences([+f, +f], [U, F, R, B, L, D], Tmp)
		;
		(Pos == 4 -> 
			nth1(6, L, NeighborCol),
			sequences([-f], [U, F, R, B, L, D], Tmp)
			;
			(Pos == 6 -> 
				nth1(4, R, NeighborCol),
				sequences([+f], [U, F, R, B, L, D], Tmp)
				;
				(Pos == 8 -> 
					nth1(2, D, NeighborCol),
					Tmp = [U, F, R, B, L, D]
					; fail)))),

	(MidNeighborCol == NeighborCol ->
		sequences([-d, -l, +f, +l], Tmp, Res)
		;
		sequences([-d], Tmp, Tmp2),
		(Pos == 2 -> 
			sequences([-f, -f], Tmp2, Res)
			;
			(Pos == 4 -> 
				sequences([+f], Tmp2, Res)
				;
				(Pos == 6 -> 
					sequences([-f], Tmp2, Res)
					;
					(Pos == 8 -> 
						Tmp2 = Res
						; fail))))).


/*
	Tries to solve cross with correct positions.
	Firstly checks the bottom side, then Upper, and if there is no cross color,
	then check the other sides - middle. Rotate and then recursively tries to solve again.
	And for every 4 (middle) sides - just solve for Front, and then rotate by Z coordinate.
*/
solveCross(CrossCol, RotationCnt, [U, F, R, B, L, D], Res) :- 
	crossFinished([U, F, R, B, L, D], CrossCol, IsFinished),

	(IsFinished == true -> Res = [U, F, R, B, L, D]
		;
		% At least one color is on Down side - move every down color Up
		colorIsOnSide(D, CrossCol, PosD),
		(PosD \== 0 ->
			moveDownCol(PosD, [U, F, R, B, L, D], ResCubeD),
			solveCross(CrossCol, RotationCnt, ResCubeD, Res)
			;

			nth1(8, U, PosU),
			nth1(5, F, MidNeighborColU),
			nth1(2, F, NeighborColU),
			% Color is on Upper side but not on correct place - fix this
			(PosU == CrossCol, MidNeighborColU \== NeighborColU ->
				sequences([+f, +f], [U, F, R, B, L, D], ResCubeU),
				solveCross(CrossCol, RotationCnt, ResCubeU, Res)
				;

				colorIsOnSide(F, CrossCol, PosF),
				% Color(s) is on Front sides - rotate it
				(PosF \== 0 -> 
					moveMiddleCol(PosF, [U, F, R, B, L, D], ResCubeMid),
					solveCross(CrossCol, RotationCnt, ResCubeMid, Res)
					;

					RotationCntN is RotationCnt + 1,
					sequences([+z], [U, F, R, B, L, D], ShiftedCube),

					solveCross(CrossCol, RotationCntN, ShiftedCube, Res)
					)))).

/* 
	Receives list of moves which will be applicated on the input Cube. In third parameter returns the result cube.
	It also prints all cubes during the process. 
*/
sequences([], Cube, Cube).
sequences([H|T], Cube, NewCube) :-
	rotate(H, Cube, TmpCube), writeCube(TmpCube), assertz(solution(H)), sequences(T, TmpCube, NewCube).


/* The current implementation solves only cross, but its prepared for other steps in algorithm. */
solveCubeAlg([U, F, R, B, L, D]) :-
	nth1(5, U, UCol),
	solveCross(UCol, 0, [U, F, R, B, L, D], _).


main :-
	prompt(_, ''), 	 % Read from stdin
	readCube(Cube),	 % Read input by lines and fill cube into the list of lists. 
					 % Each sublist contain 1 side of cube.
	writeCube(Cube), % Write the input Cube
	solveCubeAlg(Cube),
	%listing(solution),	% Just for testing purposes, comment it.
	halt.
