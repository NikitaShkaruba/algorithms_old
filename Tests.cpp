#include "DataStructures.cpp"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <cassert> 
#include <time.h>
#include <string>
#include <queue>
#include <list>
using namespace algo;

namespace polygon {
	struct Node;  
	struct Edge {
	public:
		Edge(list<Node>::iterator from, list<Node>::iterator to) : from_(&*from), to_(&*to) {} 
		~Edge() {}

		bool operator==(const Edge& other) {
			return (from_ == other.from_ && to_ == other.to_ || from_ == other.to_ && to_ == other.from_);
		}
		bool operator!=(const Edge& other) {
			return (!(*this == other));
		}
		bool isSelfLoop() {
			return (from_ == to_);
		}

		Node* from_;
		Node* to_;
	};
	struct Node {
	public:
		Node(string content) : edges(), content(content), isExplored(false) {}
		~Node() {}
		bool operator==(const Node& other) {
			// if (this->edges.size() != other.edges.size())
			// 	return false;
			// 
			// auto j = other.edges.begin();
			// auto i = edges.begin();
			// while(i != edges.end()) {
			// 	if (*i != *j)
			// 		return false;
			// 	i++; 
			// 	j++;
			// }
			
			return this->content == other.content;
		}

		bool isExplored;
		vector<Edge*> edges;
		string content;
	};
	class Graph {
	public:
		Graph(const Graph& graph) { // !
			for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
				this->nodes.push_back(Node {it->content});
			for (auto it = graph.edges.begin(); it != graph.edges.end(); it++)
				connect(getNodeIterator(*it->from_), getNodeIterator(*it->to_));
		}
		Graph() : nodes(), edges() {}
		~Graph() {}
		
		Graph& operator=(const Graph& graph) {
			Graph buf = Graph(graph);
			this->swap(buf);
			return *this;
		}
		void swap(Graph& other) {
			list<Node> buf2 = nodes;
			nodes = other.nodes;
			other.nodes = buf2;

			list<Edge> buf = edges;
			edges = other.edges;
			other.edges = buf;
		}

		list<Node>::iterator getNodeIterator(const Node& node) {
				for(auto i = nodes.begin(); i != nodes.end(); i++)
					if (*i == node)
						return i;

			throw "Can't find this node";
		}
		list<Edge>::iterator getEdgeIterator(const Edge& edge) {
			for (list<Edge>::iterator i = edges.begin(); i != edges.end(); i++)
				if (*i == edge)
					return i;

			throw "Can't find this node";
		}
		bool haveNode(Node node) {
			for (auto i = nodes.begin(); i != nodes.end(); i++)
				if (*i == node)
					return true;
			
			return false;
		}
		void add(Node node) {
			nodes.push_back(node);
		}
		list<Edge>::iterator getRandomEdge() {
			auto it = edges.begin();

			for (size_t i = rand() % edges.size(); i != 0; i--)
				it++;

			return it;
		}

		bool areConnected(list<Node>::iterator a, list<Node>::iterator b) {
			for (auto i = a->edges.begin(); i != a->edges.end(); i++)
				if (*(*i)->from_ == *b || *(*i)->to_ == *b)
					return true;
			
			return false;
		}
		void removeSelfLoops(list<Node>::iterator it) {
			vector<Edge*>::iterator i = it->edges.begin();
			while (i != it->edges.end()) {
				if ((*i)->isSelfLoop()) {
					this->edges.erase(getEdgeIterator(**i));
					i = it->edges.erase(i);
				} else
					i++;
			}
		}
		list<Node>::iterator fuse(list<Edge>::iterator it) {
			Edge weak = *it;
			Node* merged = it->from_;
			Node* extincted = it->to_;

			// concat content and rebind edges
			merged->content += "." + extincted->content;
			vector<Edge*>::iterator i = extincted->edges.begin();
			while (i != extincted->edges.end()) {
				if (**i != weak) {
					merged->edges.push_back(&**i);
					if ((*i)->from_ == extincted)
						(*i)->from_ = merged;
					else 
						(*i)->to_ = merged;
				}

				i = extincted->edges.erase(i);
			}

			// remove all edges between those "merged" and "extincted"
			vector<Edge*>::iterator j = merged->edges.begin();
			while (j != merged->edges.end()) {
				if (**j == weak) {
					edges.erase(getEdgeIterator(**j));
					j = merged->edges.erase(j);
				} else
					j++;
			}
			// this is a fucking bug
			nodes.erase(getNodeIterator(*extincted));
			return getNodeIterator(*merged);
		}
		void cut(list<Edge>::iterator it) {
			throw "not implemented";
			edges.erase(getEdgeIterator(*it));
		}
		void connect(list<Node>::iterator a, list<Node>::iterator b) {
			Edge link(a, b);
			edges.push_back(link);
			
			Edge* pntr = &*getEdgeIterator(link);
			a->edges.push_back(pntr);
			b->edges.push_back(pntr);
		}
		list<Edge*> BreadthFirstSearch(Graph graph, Node start) {
			// O(m + n) = O(n)
			// Warning! all nodes have to be initially unexplored
			start.isExplored = true;
			

		}
		list<Node> nodes;	// O(n)
		list<Edge> edges;   // O(m)
	};

	Graph getGraph(string fileName) {
		ifstream input(fileName);
		string line;
		Graph result;
		int i = 0, j = 0;
		
		while (getline(input, line)) {
			istringstream stringStream(line);
	
			stringStream >> i; // first one
			Node center(std::to_string(i));
			if (!result.haveNode(center))
				result.add(center);

			while (stringStream >> j) {
				
				Node adjacent(std::to_string(j));
				if (!result.haveNode(adjacent))
					result.add(adjacent);

				auto it = result.getNodeIterator(center);
				auto jt = result.getNodeIterator(adjacent);

				if (!result.areConnected(it, jt))
					result.connect(it, jt);
			}
		}

		return result;
	}	
	Graph KargerMinCut(Graph graph) {
		// Complexity: O(m*n^2)
		size_t n = graph.edges.size();
		Graph best = Graph(graph);
	
		for (size_t i = 0; i < pow(n, 2)*log(n); i++) {		// O(log(n)*n^2)
			Graph copy = Graph(graph);

			int k = 0;
			while (copy.edges.size() != 2) {				// O(m/log(n))
				if (++k == 8)
					cout << "find it";
				auto survived = copy.fuse(copy.getRandomEdge());
				copy.removeSelfLoops(survived);
			}
	
			if (copy.edges.size() < best.edges.size()) 
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
		std::cout << "Minimum cut edges count: " << result.edges.size() << std::endl;
 	}
}