#ifndef DOUFEI_DIJKSTRA_HEAD
#define DOUFEI_DIJKSTRA_HEAD
#include "adjacentList.h"
#include "multiBitmap.h"
#include <float.h>
#include <vector>
#include <queue>
using std :: vector;
using std :: priority_queue;
/*
*return true if can find a path from "start" to "end", else return false 
*1, graph -> the graph
*2, start -> the start position in the graph
*3, end -> the destination position in the graph
*4, path -> the result path from "start" to "end" position
*5, distance -> the distance between the position "start" and "end"
*/
template<typename dataType>
bool dijkstraPath(CAdjListGrahp<dataType>& graph, const int start, const int end, vector<int>& retPath, float &retDistance) 
{
	if (graph.empty()) return false ;
	int numOfNode = graph.getNumOfNodeCount() ;
	if ((start < 0 || start > numOfNode) || (end < 0 || end > numOfNode)) return false ;

	CMultiBitMap isPassed(numOfNode) ; // is the graph node passed
	vector<int> preNode(numOfNode, -1) ; //the previous node
	vector<float> distances(numOfNode, FLT_MAX) ; //the distance from the start to one node

	isPassed.setBit(start, true) ;
	preNode[start] = -1 ;
	distances[start] = 0 ;

	const ListNode* listNodePtr = graph.adjListForAdjNode(start) ;
	while (listNodePtr)
	{
		distances[listNodePtr->nodeIndex] = listNodePtr->weight ;
		preNode[listNodePtr->nodeIndex] = start ;
		listNodePtr = listNodePtr -> nextListNode ;
	}

	int curNode = -1 ;
	for (int i = 1; i < numOfNode && curNode != end; ++ i)
	{
		float minDis = FLT_MAX ;
		int minIndex = -1 ;
		for (int j = 0; j < numOfNode; ++ j)
			if ( !isPassed.getBit(j) && distances[j] < minDis)
			{
				minDis = distances[j] ;
				minIndex = j ;
			}

		curNode = minIndex ;
		if (curNode >= numOfNode || curNode == -1) return false ;
		isPassed.setBit(curNode, true) ;
		
		listNodePtr = graph.adjListForAdjNode(curNode) ;
		while (listNodePtr)
		{
			if (distances[curNode] + listNodePtr->weight < distances[listNodePtr->nodeIndex])
			{
				distances[listNodePtr->nodeIndex] = distances[curNode] + listNodePtr->weight ;
				preNode[listNodePtr->nodeIndex] = curNode ;
			}
			listNodePtr = listNodePtr->nextListNode ;
		}
	}

	if (curNode != end) return false ;

	retDistance = distances[end] ;
	retPath.clear() ;
	int tIndex = end ;
	while(tIndex != -1)
	{
		retPath.push_back(tIndex) ;
		tIndex = preNode[tIndex] ;
	}

	//reverse the result
	int s = 0, d = retPath.size() - 1 ;
	for ( ; s < d; ++s, --d)
		swap(retPath[s], retPath[d]) ;

	return true ;
}

#endif