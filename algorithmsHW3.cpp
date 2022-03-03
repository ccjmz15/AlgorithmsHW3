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
		Graph() {
			_numVertices = 0;
			_numEdges = 0;

			int userInput;
			int counter = 0;
			int i, j = 0;

			cout << "Input the # of vertices, then the sequence of edges, and end with neg integer." << endl << endl;

			cout << "Number of vertices = ";
			cin >> userInput;
			cout << endl;

			_numVertices = userInput; // Validate

			createVertices();
			initializeVisited();
			initializeAdjacencyList();

			while (true) {
				if (counter % 2 == 0) {
					cout << "i = ";
					cin >> i;
				}
				else {
					cout << "j = ";
					cin >> j;
				}
				if ((i < 0 || j < 0) || ((i || j ) > _numVertices - 1)) { break; }
				if (counter % 2 == 1) { 
					addEdgeForE(i, j);
					addEdge(i, j);
					cout << "[" << i << ", " << j << "]\n" << endl;
				}
				counter++;
			}
			cout << endl << endl;
			printVertices();
			printEdges();
			printAdjacencyList();
		}

		void printVertices() {
			cout << "V = {";
			for (int i = 0; i < V.size() - 1; i++) { cout << V.at(i) << ","; }
			cout << V.at(V.size() - 1) << "}" << endl;
		}

		void printEdges() {
			int counter = E.size();
			cout << "E = {";
			for (itr = E.begin(); itr != E.end(); itr++) {
				for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
					cout << "{" << ptr->first << "," << ptr->second << "}";
					if (counter != 1) { cout << ","; }
					counter--;
				}
			}
			cout << "}" << endl;
		}

		void printAdjacencyList() {
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

		void addEdge(int i, int j) { append(i, j); append(j, i); _numEdges++; printAdjacencyList(); }

		void append(int i, int j) {
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

		void createVertices() {
			vector<int> listOfVertices;
			for (int counter = 0; counter < _numVertices; counter++) { listOfVertices.push_back(counter); }
			V = listOfVertices;
		}

		void addEdgeForE(int i, int j) {
			int index = E.size();
			E.insert(make_pair(index, map<int, int>()));
			E[index].insert(make_pair(i, j));
			_numEdges++;
		}

		void initializeVisited() { visited = new bool[_numVertices]; for (int i = 0; i < _numVertices; i++) { visited[i] = false; } }

		void initializeAdjacencyList() { adjacencyList = new Node * [_numVertices]; for (int i = 0; i < _numVertices; ++i) { adjacencyList[i] = NULL; } }

	private:
		int _numVertices;
		int _numEdges;

		Node** adjacencyList;
		Node* prev;

		vector<int> V;
		map<int, map<int, int>> E;

		bool* visited;

		// Helper variables for E
		map<int, map<int, int> >::iterator itr;
		map<int, int>::iterator ptr;
};

int main() {
	Graph g;
}