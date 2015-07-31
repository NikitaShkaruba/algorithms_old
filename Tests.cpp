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
		Node(list<Edge*> edges) {
			for each (auto var in edges)
				edges_.push_back(var);
		}
		Node() : edges_() {}
		~Node() {
			edges_.clear();
		}

		bool operator==(const Node& other) {
			if (edges_.size() != other.edges_.size())
				return false;

			for(auto i = 0; i < edges_.size(); i++)
				if (this->edges_.at(i) != other.edges_.at(i))
					return false;
			return true;
		}
		bool isConnected(const Node& node) {
			for (auto i = node.edges_.begin(); i != node.edges_.end(); i++)
				if (*(*i)->to_ == node || *(*i)->from_ == node)
					return true;
			return false;
		}

		vector<Edge*> edges_;
	};

	class Graph {
	public:
		Graph(vector<Node> nodes, size_t edgeCount) {
			nodes_ = nodes;
			edgeCount_ = edgeCount;
		}
		Graph(const Graph& graph) {
			nodes_ = graph.nodes_;
			edgeCount_ = graph.edgeCount_;
		}
		Graph() : nodes_(), edgeCount_(0) { }
		~Graph() {}
		
		Graph& operator=(const Graph& graph) {
			Graph buf = Graph(graph);
			this->swap(buf);
			return *this;
		}
		void swap(Graph& other) {
			vector<Node> buf2 = nodes_;
			nodes_ = other.nodes_;
			other.nodes_ = buf2;

			int buf = edgeCount_;
			edgeCount_ = other.edgeCount_;
			other.edgeCount_ = buf;
		}

		void removeSelfLoops(Node& node) {
			auto it = node.edges_.begin();
			while (it != node.edges_.end()) {
				if ((*it)->isSelfLoop()) {
					it = node.edges_.erase(it);
					edgeCount_--;
				} else {
					it++;
				}
			}
		}
		void fuse(Edge* edge) {
			Node* merged = edge->from_;
			Node* extincted = edge->to_;
			edgeCount_--;

			auto it = extincted->edges_.begin();
			while (it != extincted->edges_.end()) {
				if ((*it)->from_ == extincted)
					(*it)->from_ = merged;
				else 
					(*it)->to_ = merged;

				merged->edges_.push_back(*it);
				it = extincted->edges_.erase(it);
			}
			for (auto i = extincted->edges_.begin(); i != extincted->edges_.end(); i++) {
			}
			// delete their own link
			nodes_.erase(getIterator(*extincted));
		}
		void cut(Edge* edge) {
			//auto it = edge->from_->;
			//edge->from_->edges_.erase(it);
			//if (!edge->isSelfLoop())
			//	edge->to_->edges_.erase(it);
		}
		void connect(Node& a, Node& b) {
			Edge* link = new Edge(&a, &b);
			edgeCount_++;

			a.edges_.push_back(link);
			b.edges_.push_back(link);
		}
		void add(Node node) {
			assert(node.edges_.size() == 0);
			nodes_.push_back(node);
		}
		void add(Graph graph) {

		}
		vector<Node>::iterator getIterator(Node& node) {
			for(auto i = nodes_.begin(); i != nodes_.end(); i++)
				if (node == *i)
					return i;
			throw "Node does not exist";
		}
		//vector<Edge*>::iterator find(Edge& edge) {
		//	for(auto i = edges_.begin(); i != edges_.end(); i++)
		//		if (edge == **i)
		//			return i;
		//	throw "Edge does not exist";
		//}

		vector<Node> nodes_;	// O(n)
		size_t edgeCount_;	// O(m)
	};
	Graph getGraph(string fileName) {
		ifstream input(fileName);
		string line;
		Graph result;
		size_t nCount = 0, eCount = 0;
		for(size_t i = 0; i < 200; i++)
			result.add(Node {});

		while (getline(input, line)) {
			int i = 0, j = 0;
			istringstream stringStream(line);
	
			stringStream >> i; // first one
			nCount++;
			while (stringStream >> j) {
				if (!(result.nodes_.at(i-1).isConnected(result.nodes_.at(j-1))))
					result.connect(result.nodes_.at(i-1), result.nodes_.at(j-1));
			}
		}
		return result;
	}	
	Graph KargerMinCut(Graph graph) {
		// Complexity: O(m*n^2)
		size_t n = graph.edgeCount_;
		Graph best = Graph(graph);
	
		for (size_t i = 0; i < pow(n, 2)*log(n); i++) {		// O(log(n)*n^2)
			Graph copy = Graph(graph);
	
			while (copy.nodes_.size() != 2) {				// O(m/log(n))
				size_t j = rand() / copy.edgeCount_;
				Edge* chosen = copy.nodes_[j].edges_[rand() / copy.nodes_[j].edges_.size()]; //!
				Node* merged = chosen->from_;
				copy.fuse(chosen);
				copy.removeSelfLoops(*merged);
			}
	
			if (copy.edgeCount_ < best.edgeCount_) 
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
		Graph result = KargerMinCut(getGraph("Graph.txt"));
		std::cout << "Minimum cut edges count: " << result.edgeCount_ << std::endl;
 	}
}