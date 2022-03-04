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
		Graph(int numVertices, map<int, map<int, int>> E) {
			_numVertices = numVertices;
			_numEdges = E.size();

			initializeAdjacencyList(); // Creates an array of linked lists, each linked list is filled with NULL value
			initializeAdjacencyMatrix();
			resetVisited(); // Creates an array of size _numVertices and fills all values as 'false' or '0'

			fillAdjacencyList(E); // Create the initial adjacency list, uses Edges to compute
			fillAdjacencyMatrix();
		}

		~Graph() { deleteEntireAdjacencyList(); }

		void edgeAddition(int i, int j) { append(i, j); append(j, i); _numEdges++; } // Calls append twice, flipping the parameters.

		void edgeDeletion(int i, int j);

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

		void printAdjacencyMatrix() {
			for (int i = 0; i < _numVertices; i++) {
				cout << endl;
				for (int j = 0; j < _numVertices; j++) {
					cout << '\t' << adjacencyMatrix[i][j];
				}
			}
		}

		void printVisited() { for (int i = 0; i < _numVertices; i++) { cout << visited[i] << endl; } }

		void DFS(int vertex) {
			Node* head = adjacencyList[vertex];
			vector<int> adjacentVertices = Visit(head);
			int length = listLength(head);

			visited[vertex] = true;
			printVisited();
			cout << endl << endl;
			for (int i = 0; i < length; i++) {
				if (visited[adjacentVertices.at(i)] == false) {
					DFS(adjacentVertices.at(i));
				}
			}
		}

	protected: // Basically all helper methods that cannot be called from outside the Graph class.

		void Components() {// computes the vertex sets of the connected components of G. Involves calling DFS(G, v), v = 0, 1, ..n – 1.
			
			for (int i = 0; i < _numVertices; i++) { // Loop through each of the vertices
				resetVisited(); // Reset the visited list to all false.
				while (true) { // While DFS is running...
					DFS(i);
				
				} 
			}
		
		}

		vector<int> Visit(Node* head) {
			vector<int> vec;
			while (head != NULL) {
				vec.push_back(head->data);
				head = head->next;
			}
			return vec;
		}

		int listLength(Node* head) {
			if (head == NULL) { return 0; }
			return 1 + listLength(head->next);
		}

		void initializeAdjacencyMatrix() {
			bool** matrix = new bool*[_numVertices];
			for (int i = 0; i < _numVertices; i++) { matrix[i] = new bool[_numVertices]; }
			adjacencyMatrix = matrix;
		}

		void fillAdjacencyMatrix() {
			for (int i = 0; i < _numVertices; i++) {
				vector<int> connectedComponents = Visit(adjacencyList[i]);
				for (int j = 0; j < _numVertices; j++) {
					adjacencyMatrix[i][j] == false;
					for (vector<int>::iterator itr = connectedComponents.begin(); itr != connectedComponents.end(); ++itr) {
						adjacencyMatrix[i][*itr] == true;
					}
				}
			}
		}

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

		void fillAdjacencyList(map<int, map<int, int>> originalEdges) {
			map<int, map<int, int> >::iterator itr;
			map<int, int>::iterator ptr;

			for (itr = originalEdges.begin(); itr != originalEdges.end(); itr++) {
				for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
					edgeAddition(ptr->first, ptr->second);
				}
			}
		}

		void deleteEntireAdjacencyList() {
			for (int i = 0; i < _numVertices; i++) {
				Node* current = adjacencyList[i];
				Node* next;
				while (current != NULL) {
					cout << current->data << "\t";
					next = current->next;
					free(current);
					current = next;
				}
				adjacencyList[i] = NULL;
			}	
		}

		void resetVisited() { visited = new bool[_numVertices]; for (int i = 0; i < _numVertices; i++) { visited[i] = false; } }

		void initializeAdjacencyList() { adjacencyList = new Node * [_numVertices]; for (int i = 0; i < _numVertices; ++i) { adjacencyList[i] = NULL; } }

	private:
		int _numVertices;
		int _numEdges;

		Node** adjacencyList;
		Node* prev;

		bool** adjacencyMatrix;
		bool* visited;
};



void printVertices(int vertices) {
	cout << "V = {";
	for (int i = 0; i < vertices - 1; i++) { cout << i << ","; }
	cout << vertices - 1 << "}" << endl;
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


int main() {
	vector<int> V;
	map<int, map<int, int>> E;

	int numVertices, i, j = 0;
	int loopCount = 0;

	cout << "Input the # of vertices, then the sequence of edges, and end with neg integer." << endl << endl;

	cout << "Number of vertices = ";
	cin >> numVertices;
	cout << endl;

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

	printVertices(numVertices);
	printEdges(E);

	cout << endl;

	Graph graph = Graph(numVertices, E);
	graph.printVisited();
	graph.printAdjacencyList();

	graph.printAdjacencyMatrix();

	graph.~Graph();
}