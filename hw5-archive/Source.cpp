#include<iostream>
#include <fstream>
#include <string>
#include <list>
#include "ArgumentManager.h"
using namespace std;
class Graph
{
	int V;    
	list<int> *adj;    
public:
	Graph(int V);  
	void addEdge(int v, int w); 
	void BFS(int s);  
};
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); 
}
void Graph::BFS(int s)
{
	int num = s;
	int arr[1000] = {0};
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	list<int> queue;
	visited[s] = true;
	queue.push_back(s);
	list<int>::iterator i;
	int index = 0;
	while (!queue.empty())
	{
		s = queue.front();
		arr[index++] = s;
		queue.pop_front();
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}

	int k, j;
	int temp;
	for (k = 0; k< index - 1; k++)
	{
		for (j = 0; j<( index - k) - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int k = 0; k < index; k++)
	{
		if (arr[k] != num)
		cout << arr[k] << " ";
	}

}
int main(int argc, char * argv[])
{
	ArgumentManager am(argc, argv);
	string filename = am.get("E");
	fstream ifs(filename.c_str());
	string line = "";
	string str = "";
	int num = atoi(am.get("source").c_str());
	int arr[1000][3];
	int count = 0;
	int index = 0;
	Graph g(1000);

	while (getline(ifs, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (isdigit(line[i]))
			{
				str = str + line[i];
			}
			else
			{
				arr[count][index++] = stoi(str);
				str = "";
			}
		}		
		arr[count][index++] = stoi(str);
		str = "";
		count++;
		if (index == 3)
			index = 0;
	}

	for (int i = 0; i < count; i++)
	{
		if (arr[i][2] != 0)
		g.addEdge(arr[i][0], arr[i][1]);
	}	

	g.BFS(num);
	return 0;
}