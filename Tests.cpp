#include "Algorithms.h"
#include "Graph.h"
#include "DataStructures.cpp"
#include <iostream>
#include <cassert> 
#include <list>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace algo;

namespace polygon {
	class Node;  
	class Edge {
	public:
		Edge(Node* from, Node* to) : from_(from), to_(to) {} 
		~Edge() {}

		bool operator==(const Edge& other) {
			return (from_ == other.from_ && to_ == other.to_ || from_ == other.to_ && to_ == other.from_);
		}
		bool isSelfLoop() {
			return (from_ == to_);
		}

		Node* from_;
		Node* to_;
	};
	class Node {
	public:
		Node(string content) : content(content) {}
		~Node() {
			edges.clear();
		}
		bool operator==(const Node& other) {
			if (edges.size() != other.edges.size())
				return false;

			for(auto i = 0; i < edges.size(); i++)
				if (this->edges.at(i) != other.edges.at(i))
					return false;
			return true;
		}

		string content;
		vector<Edge*> edges;
	};
	class Graph {
	public:
		Graph(vector<Node> nodes, size_t edgeCount) {
			nodes = nodes;
			edgeCount = edgeCount;
		}
		Graph(const Graph& graph) : Graph(graph.nodes.size()) {
			for (size_t i = 0; i < graph.nodes.size(); i++)
				for (size_t j = 0; j < graph.nodes[i].edges.size(); j++) {
					Node& a = nodes[stoi(graph.nodes[i].edges[j]->from_->content)];
					Node& b = nodes[stoi(graph.nodes[i].edges[j]->to_->content)];
					
					if (!areConnected(a, b))
						connect(&a, &b);
				}

			edgeCount = graph.edgeCount;
		}
		Graph(size_t nodeCount) {
			for(size_t i = 0; i < nodeCount; i++)
				add(Node {std::to_string(i)});
		}
		Graph() : nodes(), edgeCount(0) { }
		~Graph() {}
		
		Graph& operator=(const Graph& graph) {
			Graph buf = Graph(graph);
			this->swap(buf);
			return *this;
		}
		void swap(Graph& other) {
			vector<Node> buf2 = nodes;
			nodes = other.nodes;
			other.nodes = buf2;

			int buf = edgeCount;
			edgeCount = other.edgeCount;
			other.edgeCount = buf;
		}

		Node& find(string content) {
			for(auto i = nodes.begin(); i != nodes.end(); i++)
				if (i->content == content)
					return *i;
			throw "Can't find this node";
		}
		bool areConnected(const Node& a, const Node& b) const {
			for (auto i = a.edges.begin(); i != a.edges.end(); i++)
				if (*(*i)->to_ == b || *(*i)->from_ == b)
					return true;
			return false;
		}
		void removeSelfLoops(Node& node) {
			auto it = node.edges.begin();
			while (it != node.edges.end()) {
				if ((*it)->isSelfLoop()) {
					it = node.edges.erase(it);
					edgeCount--;
				} else 
					it++;
			}
		}
		Node* fuse(Edge* edge) {
			Node* merged = edge->from_;
			Node* extincted = edge->to_;

			merged->content += "+" + extincted->content;
			auto it = extincted->edges.begin();
			while (it != extincted->edges.end()) {
				// need refactoring, coz this method ,eaves one self loop
				if ((*it)->from_ == extincted)
					(*it)->from_ = merged;
				else 
					(*it)->to_ = merged;

				merged->edges.push_back(*it);
				it = extincted->edges.erase(it);
			}
			nodes.erase(getIterator(*extincted));
			return merged;
		}
		void cut(Edge* edge) {
			throw "not implemented";
			//auto it = edge->from_->;
			//edge->from_->edges_.erase(it);
			//if (!edge->isSelfLoop())
			//	edge->to_->edges_.erase(it);
		}
		void connect(Node* a, Node* b) {
			Edge* link = new Edge(a, b);
			edgeCount++;

			a->edges.push_back(link);
			b->edges.push_back(link);
		}
		void add(Node node) {
			assert(node.edges.size() == 0);
			nodes.push_back(node);
		}
		void add(Graph graph) {

		}
		vector<Node>::iterator getIterator(Node& node) {
			for(auto i = nodes.begin(); i != nodes.end(); i++) {
				if (i->content == node.content)
					return i;
			}
			throw "Node does not exist";
		}

		vector<Node> nodes;	// O(n)
		size_t edgeCount;
	};

	Graph getGraph(string fileName) {
		Graph result(200);
		ifstream input(fileName);
		string line;
		int i = 0, j = 0;
		
		while (getline(input, line)) {
			istringstream stringStream(line);
	
			stringStream >> i; // first one
			while (stringStream >> j) {
				if (!(result.areConnected(result.nodes.at(i-1), result.nodes.at(j-1))))
					result.connect(&result.nodes.at(i-1), &result.nodes.at(j-1));
			}
		}
		return result;
	}	
	Graph KargerMinCut(Graph graph) {
		// Complexity: O(m*n^2)
		size_t n = graph.edgeCount;
		Graph best = Graph(graph);
	
		for (size_t i = 0; i < pow(n, 2)*log(n); i++) {		// O(log(n)*n^2)
			Graph copy = Graph(graph);
			int s = 0;
			while (copy.nodes.size() != 2) {				// O(m/log(n))
				if (++s == 22)
					cout << "shush";
				size_t r1 = rand() % copy.nodes.size(), r2 = rand() % copy.nodes[r1].edges.size();
				Edge* chosen = copy.nodes[r1].edges[r2]; //!
				Node* survived = copy.fuse(chosen);
				// node vector removes edge pointers, look at node[0].edges[13]
				copy.removeSelfLoops(*survived);
			}
	
			if (copy.edgeCount < best.edgeCount) 
				best = copy;
		}
		return best;
	}
	////////////////////////////////////
	int* GenerateRandomArray(size_t size) {
		int* arr = new int[size];

		for (size_t i = 0; i < size; i++)
			arr[i] = rand();

		return arr;
	}
	void printArray(int* arr, size_t size) {
		std::cout << "Array:" << std::endl;
		for (size_t i = 0; i < size; i++)
			std::cout << i << ") " << arr[i] << std::endl;
	}
	bool isSorted(int* arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] < arr[i - 1])
				return false;
		return true;
	}
	int* getArray(string name, size_t size) {
		ifstream file(name);
		int* arr = new int[size], i = 0;
		for(size_t i = 0; i < size; i++)
			 file >> arr[i];
	
		file.close();
		return arr;
	}

	void RunSortTests() {
		void(*sorts[])(int*, size_t) = { SelectionSort, InsertionSort, BubbleSort, MergeSort, QuickSort };
		size_t elementsCount = 10;

		for (size_t i = 0; i < 5; i++) {
			for (int j = 0; j < 50; j++) {
				int* arr = GenerateRandomArray(elementsCount);

				sorts[i](arr, elementsCount);
				assert(isSorted(arr, elementsCount));

				delete[] arr;
			}
		}
	}
	void RunCountInversionsTests() {
		int arr[] { 1, 2, 3, 4, 5 };
		assert(CountInversions(arr, 5) == 0);

		int arr2[] = { 1, 2, 5, 4, 3 }; // 5&4, 5&3, 4&3
		assert(CountInversions(arr2, 5) == 3);

		std::ifstream file("IntegerArray.txt");
		std::string buf;
		int* integers = new int[100000];
		int i = 0;
		while (getline(file, buf))
			integers[i++] = stoi(buf);
		// Stanford homework #1
		assert(CountInversions(integers, 100000) == 2407905288);
		delete integers;
	}
	void RunRedBlackTreeTests() {
		for (size_t i = 0; i < 11; i++) {
			size_t size = 7 + i;
			int* arr = new int[(int)pow(2, size)];
			for (size_t j = 0; j < size; j++)
				arr[j] = rand();
			RedBlackTree tree(arr, size);
			
			tree.inTraversal([](RedBlackTree* node) {
				assert(node->isBinaryTree());
			});
		}
	}
	void RunGraphTests() {
		Graph s = getGraph("Graph.txt");
		Graph result = KargerMinCut(s);
		std::cout << "Minimum cut edges count: " << result.edgeCount << std::endl;
 	}
}