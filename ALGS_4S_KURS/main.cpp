#include <iostream>
#include <string>
#include <fstream>
#include "iterator.h"
#include "list.h"
#include "pair.h"
#include "queue.h"
#include "RBTree.h"
#include "map.h"
using namespace std;


struct Edge
{
public:
	string vertex1;
	string vertex2;
	double weight;

	Edge(string vertex1, string vertex2, double weight)
	{
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->weight = weight;
	}

	Edge()
	{
		this->vertex1 = "";
		this->vertex2 = "";
		this->weight = 0.0;
	}
};

struct Graph
{
	double** matrix;
	int size;

	Graph(int size) {
		this->size = size;
		matrix = new double* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
			for (int j = 0; j < size; j++)
				matrix[i][j] = 0;
		}
	}
	~Graph() {
		delete[] matrix;
	}
};


double minimum(double n1, double n2) //comperes two values and returns minimal one
{
	if (n1 <= n2)
		return n1;
	else
		return n2;
}

bool bfs(Graph& rGraph, int s, int t, int* parent)// bfs in Graph to find path from S to T
{
	bool* visited = new bool[rGraph.size];
	for (int i = 0; i < rGraph.size; i++)
		visited[i] = false;

	Queue<int> queue;
	queue.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!queue.empty()) {
		int i = queue.front();
		queue.pop();

		for (int j = 0; j < rGraph.size; j++) {
			if (visited[j] == false && rGraph.matrix[i][j] > 0) {
				if (j == t) {
					parent[j] = i; 
					return true;// quit in case we found path to T
				}

				queue.push(j);
				parent[j] = i;
				visited[j] = true;
			}
		}
	}

	return false;
}

double FordFulkerson(Graph& graph, int s, int t)
{
	int size = graph.size;
	Graph rGraph(size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			rGraph.matrix[i][j] = graph.matrix[i][j];

	int* parent = new int[size];

	double max_flow = 0.0;

	while (bfs(rGraph, s, t, parent))
	{
		double path_flow = INT_MAX;
		for (int i = t; i != s; i = parent[i])
		{
			int j = parent[i];
			path_flow = minimum(path_flow, rGraph.matrix[j][i]);
		}

		for (int i = t; i != s; i = parent[i])
		{
			int j = parent[i];
			rGraph.matrix[j][i] -= path_flow;
			rGraph.matrix[i][j] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

List<string> tokenize(string line, string separator = " ")//This function turns string from input file into list of Vertexes and edge weight values
{
	int start = 0;
	int end = line.find(separator);
	List<string> splittedLines;

	while (end != -1)
	{
		splittedLines.push_back(line.substr(start, end - start));
		start = end + separator.size();
		end = line.find(separator, start);
	}

	splittedLines.push_back(line.substr(start, end - start));

	return splittedLines;
}

List<Edge> getEdgeList(string fileName)//forming list of edges between vertexes
{
	List<Edge> edgeList;

	ifstream finput;
	finput.open(fileName);

	string line;
	while (getline(finput, line))
	{
		List<string> newEdgeSrting = tokenize(line, " ");

		auto newEdge_itr = newEdgeSrting.create_iterator();
		string token1 = newEdge_itr->next();
		string token2 = newEdge_itr->next();
		string token3 = newEdge_itr->next();;
		delete newEdge_itr;

		Edge newEdge(token1, token2, stod(token3));
		edgeList.push_back(newEdge);
	}

	finput.close();
	return edgeList;
}

Map<string, int> giveVertexUniqueNumbers(List<Edge>& edgeList)//Save vertexes in array, each vertex has unique numbers
{
	Map<string, int>* vertexUniqueNumbers = new Map<string, int>();

	auto itr = edgeList.create_iterator();
	int vertexCount = 0;

	while (itr->has_next())
	{
		Edge edge = itr->next();

		try
		{
			vertexUniqueNumbers->Insert(edge.vertex1, vertexCount);
			vertexCount++;
		}
		catch (const std::exception&) {}

		try
		{
			vertexUniqueNumbers->Insert(edge.vertex2, vertexCount);
			vertexCount++;
		}
		catch (const std::exception&) {}
	}
	delete itr;

	return *vertexUniqueNumbers;
}

Graph buildGraphByVertex(List<Edge>& edgeList, Map<string, int>& vertexNumerics)// Create Graph, fill the adjacency matrix
{
	Graph* graph = new Graph(vertexNumerics.size);

	auto itr = edgeList.create_iterator();
	while (itr->has_next())
	{
		Edge edge = itr->next();
		int numVertex1 = vertexNumerics.Find(edge.vertex1);
		int numVertex2 = vertexNumerics.Find(edge.vertex2);
		graph->matrix[numVertex1][numVertex2] = edge.weight;
	}
	delete itr;

	return *graph;
}

double findMaxFlow(List<Edge>& edgeList, string s, string t)//find max flow
{
	Map<string, int> vertexUniqueNumbers = giveVertexUniqueNumbers(edgeList);

	int size = vertexUniqueNumbers.size;
	int vertex1 = vertexUniqueNumbers.Find(s);
	int vertex2 = vertexUniqueNumbers.Find(t);

	Graph graph = buildGraphByVertex(edgeList, vertexUniqueNumbers);

	double max_path = FordFulkerson(graph, vertex1, vertex2);

	return max_path;
}


int main() {
	List<Edge> edgeList = getEdgeList("input.txt");
	double flow = findMaxFlow(edgeList, "S", "T");
	cout << "Flow: " << flow;
	return 0;
}