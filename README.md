Graph-AdjList-Dijkstra
======================

In a adjacent list Graph, find the shortest path between two Nodes by Dijkstra's algorithm.

notation of files in the project
multiBitmap.h and multiBitmap.cpp is a test for the Bit-Map data structure,
in this CMulitBitmap, you can resize the size of a Bit-Map anytime you want
has been pushed to github: https://github.com/crazykeyboard/Bit-Map

The map file form is as below
---------------------------------------------------------------------------
|digraph or not (0 for undirected graph, 1 for digraph)	nodes have data or not(0 for no, 1 for yes)
|number of map nodes (nNum)	number of map edges(eNum)
|.......................|data0
|.......................|data1
|..............nNum --->| .................
|.......................|data nNum - 1
|.......................|ni	nj		wij
|.......................|ni	nj		wij
|.......................|ni	nj		wij
|..............eNum --->| .................
|.......................|ni	nj		wij
|.......................|ni	nj		wij
| 
----------------------------------------------------------------------------
