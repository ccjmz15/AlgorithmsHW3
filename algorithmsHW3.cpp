#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Node {
	public:
		int data;
		Node* next;
};

class Graph {
	public:
		Graph(vector<int> V, map<int, map<int, int>> E) {
			vertices = V;
			edges = E;
			_numVertices = V.size();
			_numEdges = E.size();

			initializeAdjacencyList(); // Creates an array of linked lists, each linked list is filled with NULL value
			initializeVisited(); // Creates an array of size _numVertices and fills all values as 'false' or '0'

			fillAdjacencyList(); // Create the initial adjacency list, uses Edges to compute
		}

		void addEdge(int i, int j) { append(i, j); append(j, i); _numEdges++; } // Calls append twice, flipping the parameters.

		void deleteEdge(int i, int j);

		void printAdjacencyList() {
			cout << endl;
			for (int i = 0; i < _numVertices; ++i) {
				Node* temp = *(adjacencyList + i);

				cout << i << "-->\t";

				while (temp != NULL) {
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << '\n';
			}
		}

		void printVisited() { for (int i = 0; i < _numVertices; i++) { cout << visited[i] << endl; } }

	protected:
		void Components(); // computes the vertex sets of the connected components of G. Involves calling DFS(G, v), v = 0, 1, ..n – 1.

		void DFS(int vertex);

		void append(int i, int j) { // Appends vertex j to the end of linked list of vertex i
			// 1. create and allocate node
			Node* newNode = new Node;
			Node* last = adjacencyList[i];
			// 2. assign data to the node
			newNode->data = j;
			// 3. set next pointer of new node to null as its the last node
			newNode->next = NULL;
			// 4. if list is empty, new node becomes first node
			if (adjacencyList[i] == NULL)
			{
				adjacencyList[i] = newNode;
				return;
			}
			// 5. Else traverse till the last node
			while (last->next != NULL)
				last = last->next;
			// 6. Change the next of last node
			last->next = newNode;
			return;
		} 

		void fillAdjacencyList() { 
			map<int, map<int, int> >::iterator itr;
			map<int, int>::iterator ptr;

			for (itr = Edges.begin(); itr != Edges.end(); itr++) {
				for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
					addEdge(ptr->first, ptr->second);
				}
			}
		}

		void initializeVisited() { visited = new bool[_numVertices]; for (int i = 0; i < _numVertices; i++) { visited[i] = false; } }

		void initializeAdjacencyList() { adjacencyList = new Node * [_numVertices]; for (int i = 0; i < _numVertices; ++i) { adjacencyList[i] = NULL; } }

	private:
		int _numVertices;
		int _numEdges;

		Node** adjacencyList;
		Node* prev;

		bool* visited;

		vector<int> vertices;
		map<int, map<int, int>> edges;
};


void printVertices(vector<int> listOfVertices) {
	cout << "V = {";
	for (int i = 0; i < listOfVertices.size() - 1; i++) { cout << listOfVertices.at(i) << ","; }
	cout << listOfVertices.at(listOfVertices.size() - 1) << "}" << endl;
}

void printEdges(map<int, map<int, int>> edgeMapping) {
	int counter = edgeMapping.size();
	cout << "E = {";
	map<int, map<int, int> >::iterator itr;
	map<int, int>::iterator ptr;
	for (itr = edgeMapping.begin(); itr != edgeMapping.end(); itr++) {
		for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
			cout << "{" << ptr->first << "," << ptr->second << "}";
			if (counter != 1) { cout << ","; }
			counter--;
		}
	}
	cout << "}" << endl;
}

map<int, map<int,int>> addEdgeForE(map<int, map<int, int>> edgeMapping, int i, int j) {
	int index = edgeMapping.size();
	edgeMapping.insert(make_pair(index, map<int, int>()));
	edgeMapping[index].insert(make_pair(i, j));
	return edgeMapping;
}

vector<int> createVertices(int numVertices) {
	vector<int> listOfVertices;
	for (int counter = 0; counter < numVertices; counter++) { listOfVertices.push_back(counter); }
	return listOfVertices;
}

int main() {
	vector<int> V;
	map<int, map<int, int>> E;

	int numVertices, i, j = 0;
	int loopCount = 0;

	cout << "Input the # of vertices, then the sequence of edges, and end with neg integer." << endl << endl;

	cout << "Number of vertices = ";
	cin >> numVertices;
	cout << endl;

	V = createVertices(numVertices);

	while (true) {
		if (loopCount % 2 == 0) {
			cout << "i = ";
			cin >> i;
		}
		else {
			cout << "j = ";
			cin >> j;
		}
		if ((i < 0 || j < 0) || ((i || j) > numVertices - 1)) { break; }
		if (loopCount % 2 == 1) {
			E = addEdgeForE(E, i, j);
			cout << "[" << i << ", " << j << "]\n" << endl;
		}
		loopCount++;
	}
	cout << endl << endl;

	printVertices(V);
	printEdges(E);

	cout << endl;

	Graph graph = Graph(V, E);
	graph.printVisited();
	graph.printAdjacencyList();
}