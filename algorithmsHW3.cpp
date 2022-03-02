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
			int userInput;
			int counter = 0;
			int i, j = 0;

			cout << "Please input the # of vertices, followed by a sequence of pairs, ending with - int to signify the end of the list." << endl << endl;

			cout << "Number of vertices = ";
			cin >> userInput;
			cout << endl;

			_numVertices = userInput; // Validate
			createVertices();
			createMark();

			while (true) {
				if (counter % 2 == 0) {
					cout << "i = ";
					cin >> i;
				}
				else {
					cout << "j = ";
					cin >> j;
				}
				if (i < 0 || j < 0) { break; }
				if (counter % 2 == 1) { 
					addEdgeForE(i, j);
					cout << "[" << i << ", " << j << "]\n" << endl;
				}
				counter++;
			}
			cout << endl << endl;
			printVertices();
			printEdges();
			printMark();

			initializeAdjacencyList();
			createAdjacencyList();
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

		void printMark() { for (int i = 0; i < _numVertices; i++) { cout << visited[i] << endl; } }

	protected:
		void Components(); // computes the vertex sets of the connected components of G. Involves calling DFS(G, v), v = 0, 1, ..n – 1.

		void DFS(int vertex) {
			int u;
			visited[vertex] = 1;
		}

		void addEdgeForE(int i, int j) {
			int index = E.size();
			E.insert(make_pair(index, map<int, int>()));
			E[index].insert(make_pair(i, j));
			_numEdges++;
		}

		void addEdge(int i, int j) {
			// To track last node of the list

				// Create a new node
			Node* temp = new Node();

				// Input the random data
			temp->data = j;
			temp->next = NULL;

				// If the node is first
			if (*(adjacencyList + i) == NULL) {
				*(adjacencyList + i) = temp;
			}
			else { prev->next = temp; }
			prev = temp;
		}

		void createVertices() {
			vector<int> listOfVertices;
			for (int counter = 0; counter < _numVertices; counter++) { listOfVertices.push_back(counter); }
			V = listOfVertices;
		}

		void createMark() {
			visited = new bool[_numVertices];
			for (int i = 0; i < _numVertices; i++) { visited[i] = false; }
		}

		void initializeAdjacencyList() {
			adjacencyList = new Node * [_numVertices];
			for (int i = 0; i < _numVertices; ++i) {
				*(adjacencyList + i) = NULL;
			}
		}

		void createAdjacencyList() {
			for (int i = 0; i < _numVertices; ++i) {
				for (itr = E.begin(); itr != E.end(); itr++) {
					for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
						addEdge(ptr->first, ptr->second);
						addEdge(ptr->second, ptr->first);
					}
				}
			}
			printAdjacencyList();
		}

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

void print_list(Node* n) {
	while (n != NULL) {
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}

int main() {
	Graph g;

	/*
	Node* head = NULL;
	Node* second = NULL;
	Node* third = NULL;

	head = new Node();
	second = new Node();
	third = new Node();

	head->data = 1;
	head->next = second;

	second->data = 2;
	second->next = third;

	third->data = 3;
	third->next = NULL;

	print_list(head);
	print_list(second);
	print_list(third);
	*/
}