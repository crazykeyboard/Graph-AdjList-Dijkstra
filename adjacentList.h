#ifndef DOUFEI_ADJACENTLIST_HEAD
#define DOUFEI_ADJACENTLIST_HEAD
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;
#define  NULL 0


struct ListNode ;

template<typename dataType>
struct AdjNode //define the adjacent node structure
{
	dataType data ; // data area
	ListNode *adjNodesList ; // adjacent list node structure

	AdjNode(){ adjNodesList = NULL ;} ;
	AdjNode(const dataType initData, ListNode* const ptr = NULL) { data = initData; adjNodesList = ptr ; } ;
};

struct ListNode
{
	int nodeIndex ; //index of the map node that the ListNode represents
	float weight ; //weight from the AdjNode  to this ListNode
	ListNode *nextListNode ; //another adjacent node of AdjNode 
	
	ListNode() { nextListNode = NULL ; } ; 
	ListNode(const int i, const float w, ListNode* const ptr = NULL) { nodeIndex = i; weight = w ; nextListNode = ptr ; } ;
};

template<typename dataType>
class CAdjListGrahp // store map in the CAdjListGrahp class, it's an adjacent list data structure 
{
public:
	CAdjListGrahp() ;
	~CAdjListGrahp() ;
	inline int getNumOfNodeCount() { return nodeCount ; } ;
	inline int getNumOfEdgeCount() { return edgeCount ; } ;
	inline bool isADiagraph() { return isDigraph ; } ;
	inline bool isHaveDataArea() { return isHaveData ; } ;
	inline bool empty() { if (nodeCount <= 0) return true; return false ; } ;
	inline const AdjNode<dataType>* adjNode(const int index) { assert(index >= 0 && index < nodeCount) ;  return adjNodesArray[index] ;} ;
	inline const ListNode* adjListForAdjNode(const int index) { return adjNode(index)->adjNodesList ; } ;
	inline dataType adjNodeData(const int index) { return adjNode(index)->data ; } ;
	inline void setAdjNodeList(const int i, ListNode* const ptr) { assert(index >= 0 && index < nodeCount) ; adjNodesArray[i].adjNodesList = ptr ; } ;
	bool loadMapFromFile(const char* fileName) ; //load a map from the file 'fileName'
	void printGraph() ;
private:
	void destroyMemory() ; 
private:
	AdjNode<dataType> **adjNodesArray ; //store the adjacent nodes
	int nodeCount ; //number of nodes in the map, equals to the size of adjNodesArray
	int edgeCount ; //number of edges
	bool isDigraph ; //is digraph or not
	bool isHaveData ; // does the graph have data area ?
};


template<typename dataType>
CAdjListGrahp<dataType> :: CAdjListGrahp()
{
	nodeCount = 0 ;
	edgeCount = 0 ;
	isDigraph = false ;
	isHaveData = true ;
	adjNodesArray = NULL ;
}

template<typename dataType>
CAdjListGrahp<dataType> :: ~CAdjListGrahp()
{
	//clear memory
	destroyMemory() ;
}

template<typename dataType>
void CAdjListGrahp<dataType> :: destroyMemory()
{
	if (adjNodesArray != NULL)
	{
		for (int i = 0; i < nodeCount; ++ i)
		{
			const AdjNode<dataType> *tempPtr = adjNode(i) ;
			ListNode *tempListPtr = tempPtr->adjNodesList ;
			while(tempListPtr)
			{
				ListNode *temp = tempListPtr ;
				tempListPtr = tempListPtr ->nextListNode ;
				delete temp ;
			}
			delete tempPtr ;
		}
		delete[] adjNodesArray ;
		adjNodesArray = NULL ;
	}
	nodeCount = 0 ;
}

template<typename dataType>
bool CAdjListGrahp<dataType> :: loadMapFromFile(const char* fileName)
{
	ifstream in(fileName) ;
	if ( !in ) return false ;

	destroyMemory() ; //clear the original memory

	int isDigraph_int = -1 ; //0 for undirected graph and 1 for digraph
	int isHaveData_int = -1 ;
	in >> isDigraph_int >> isHaveData_int;
	if ((isDigraph_int != 0 && isDigraph_int != 1) || (isHaveData_int != 0 && isHaveData_int != 1)) // bad file
	{
		in.close() ;
		return false ;
	}

	if (isDigraph_int) this->isDigraph = true ;
	else	this->isDigraph = false ;
	if (isHaveData_int) this->isHaveData = true ;
	else	this->isHaveData = false ;


	int numOfNodes =0, numOfEdges = 0 ;
	in >> numOfNodes >> numOfEdges ;
	if (numOfEdges < 0 || numOfNodes < 0) //bad file
	{
		in.close();
		return false ;
	}

	this->nodeCount = numOfNodes ;
	this->edgeCount = numOfEdges ;

	adjNodesArray = new AdjNode<dataType>*[numOfNodes] ;
	for (int i = 0; i < numOfNodes; ++ i)
		adjNodesArray[i] = new AdjNode<dataType> ;

	if (this->isHaveData)
	{
		for (int i = 0; i < numOfNodes; ++ i)
		{
			dataType tempData ;
			in >> tempData ;
			adjNodesArray[i]->data = tempData ;
		}
	}

	//read edges and weights
	int from = -1,  to = -1 ;
	float edgeWeight = 0.f ;
	for (int i = 0; i < numOfEdges; ++ i)
	{
		in >> from >> to >> edgeWeight ;
		if ((from < 0 || from > numOfNodes) || (to < 0 || to > numOfNodes) || (edgeWeight < 0)) //bad file
		{
			in.close() ;
			return false ;
		}
		ListNode *tempListNode = adjNodesArray[from]->adjNodesList ;
		ListNode *addNode = new ListNode(to, edgeWeight) ;
		if ( !tempListNode )
			adjNodesArray[from]->adjNodesList = addNode ; //the first node
		else
		{
			while (tempListNode->nextListNode)
				tempListNode = tempListNode->nextListNode ;
			tempListNode->nextListNode = addNode ; //add one adjacent
		}
		
		if (!this->isDigraph) // undirected graph, add another edge<to , from>
		{
			tempListNode = adjNodesArray[to]->adjNodesList ;
			addNode = new ListNode(from, edgeWeight) ;

			if ( !tempListNode )
				adjNodesArray[to]->adjNodesList = addNode ;
			else
			{
				while (tempListNode->nextListNode)
					tempListNode = tempListNode->nextListNode ;
				tempListNode->nextListNode = addNode ;
			}
		}
	}
	in.close() ;
	return true ;
}

template<typename dataType>
void CAdjListGrahp<dataType> :: printGraph()
{
	cout << "number of graph nodes: " << this->nodeCount << ", number of graph edges: " << this->edgeCount << endl;
	cout << "nodes is as below: " << endl;
	for (int i = 0; i < nodeCount; ++ i)
	{
		cout << "node " << i ;
		if (this->isHaveData)
			cout << " with data: " << adjNodesArray[i]->data ;
		cout << endl;
	}

	cout << "edges is as below: " << endl;
	for (int i = 0; i < nodeCount; ++ i)
	{
		ListNode* tempNode = adjNodesArray[i]->adjNodesList ;

		while(tempNode)
		{
			cout << "edge < " << i << ", " << tempNode->nodeIndex << " >" << " with weight " << tempNode->weight << endl;
			tempNode = tempNode->nextListNode ;
		}

	}
	
	cout << "Print graph finished !" << endl;
}

#endif