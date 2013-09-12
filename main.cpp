#include <iostream>
#include <queue>
#include "dijkstra.h"
#include "adjacentList.h"
using namespace  std;

int main(int argc, char** argv)
{
	CAdjListGrahp<char> testGraph ;
	if (testGraph.loadMapFromFile("graph.txt") )
		cout << "Load file finished" << endl;
	else
		exit(1) ;
	cout << "Number of vertices: " << testGraph.getNumOfNodeCount() << " Number of edges" << testGraph.getNumOfEdgeCount() << endl;

	vector<int> test ;
	float dis ;
	bool flag = dijkstraPath(testGraph, 0, testGraph.getNumOfNodeCount() - 1, test, dis) ;

	if (flag)
	{
		cout << "distance is : " << dis << endl;
		cout << "Path :" << endl;
		for (int i = 0 ; i < test.size() - 1; ++ i)
			cout << test[i] << "->" ;
		cout << test[test.size() - 1] << endl ;
	}
	else
	{
		cout << "No path found ! " << endl;
	}
	
	return 0 ;
}