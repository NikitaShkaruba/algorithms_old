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
		Edge(Node* from, Node* to) : from_(from), to_(to) {} 
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
				connect(it->from_, it->to_);
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

		void uncheckNodes() {
			for(auto i = nodes.begin(); i != nodes.end(); i++)
				i->isExplored = false;
		}
		Node* getNode(string content) {
				for(auto i = nodes.begin(); i != nodes.end(); i++)
					if (i->content == content)
						return &*i;

			throw "Can't find this node";
		}
		Edge* getEdge(const Edge& edge) {
			for (list<Edge>::iterator i = edges.begin(); i != edges.end(); i++)
				if (*i == edge)
					return &*i;

			throw "Can't find this node";
		}
		bool haveNode(Node* node) {
			for (auto i = nodes.begin(); i != nodes.end(); i++)
				if (&*i == node)
					return true;
			
			return false;
		}
		bool haveContent(Node node) {
			for (auto i = nodes.begin(); i != nodes.end(); i++)
				if (*i == node)
					return true;
			return false;
		}
		void add(Node node) {
			nodes.push_back(node);
		}
		Edge* getRandomEdge() {
			auto it = edges.begin();
			for (size_t i = rand() % edges.size(); i != 0; i--)
				it++;
			return &*it;
		}

		bool areConnected(Node* a, Node* b) {
			for (auto i = a->edges.begin(); i != a->edges.end(); i++)
				if (*(*i)->from_ == *b || *(*i)->to_ == *b)
					return true;
			
			return false;
		}
		void removeSelfLoops(Node* node) {
			vector<Edge*>::iterator i = node->edges.begin();
			while (i != node->edges.end()) {
				if ((*i)->isSelfLoop()) {
					this->edges.remove(*getEdge(**i));
					i = node->edges.erase(i);
				} else
					i++;
			}
		}
		Node* fuse(Edge* edge) {
			Edge weak = *edge;
			Node* merged = edge->from_;
			Node* extincted = edge->to_;

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
					j = merged->edges.erase(j);
				} else
					j++;
			}
			edges.remove(*getEdge(**j));
			// this is a fucking bug
			nodes.remove(*extincted);
			return merged;
		}
		void cut(Edge* edge) {
			throw "not implemented";
			edges.remove(*edge);
		}
		void connect(Node* a, Node* b) {
			Edge link(a, b);
			edges.push_back(link);
			
			Edge* pntr = getEdge(link);
			a->edges.push_back(pntr);
			b->edges.push_back(pntr);
		}
		
		list<Node> nodes;	// O(n)
		list<Edge> edges;   // O(m)
	};

	Node* BreadthFirstSearch(Graph graph, Node* start, string whatToFind) {
			// O(m + n) = O(n)
			// Warning! all nodes have to be initially unexplored
			queue<Node*> q;
			q.push(start);
			start->isExplored = true;

			while (!q.empty()) {
				Node* node = q.front(); q.pop();
				for (auto edge = node->edges.begin(); edge != node->edges.end(); edge++) {
					Node* next = ((*edge)->from_ == node)? (*edge)->to_ : (*edge)->from_;
					if (next->isExplored == false) {
						if (next->content == whatToFind)
							return next;
						next->isExplored = true;
						q.push(next);
					}
				}
			}
		}
	Node* DepthFirstSearch(Graph graph, Node* start, string whatToFind) {
		// Complexity: O(m + n)
		// Caution: all nodes have to be unexplored
		start->isExplored = true;
		for (vector<Edge*>::iterator it = start->edges.begin(); it != start->edges.end(); it++) {
			Node* next = ((*it)->from_ == start)? (*it)->to_ : (*it)->from_;
			if (next->isExplored == false) {
				next->isExplored = true;
				return DepthFirstSearch(graph, next, whatToFind);
			}
		}
		return nullptr;
	}
	vector<Graph> cutGraphs(Graph graph) {
		graph.uncheckNodes();
		vector<Graph> result;

		for (auto i = graph.nodes.begin(); i != graph.nodes.end(); i++) {
			if (i->isExplored == false) {
				Graph current;
				current.add(*i);

				queue<Node*> q;
				q.push(&*i);
				i->isExplored = true;

				while (!q.empty()) {
					Node* node = q.front(); q.pop();
					for (auto edge = node->edges.begin(); edge != node->edges.end(); edge++) {
						Node* next = ((*edge)->from_ == node)? (*edge)->to_ : (*edge)->from_;
						if (next->isExplored == false) {
							current.add(*next);
							// link them up--
							next->isExplored = true;
							q.push(next);
						}
					}
				}
				result.push_back(current);
			}
		}
	}
	Graph getGraph(string fileName) {
		ifstream input(fileName);
		string line;
		Graph result;
		int i = 0, j = 0;
		
		while (getline(input, line)) {
			istringstream stringStream(line);
	
			stringStream >> i; // first one
			Node center(std::to_string(i));
			if (!result.haveContent(center))
				result.add(center);

			while (stringStream >> j) {
				
				Node adjacent(std::to_string(j));
				if (!result.haveContent(adjacent))
					result.add(adjacent);

				Node* it = result.getNode(center.content);
				Node* jt = result.getNode(adjacent.content);

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
		BreadthFirstSearch(s, &*s.nodes.begin());
		Graph result = KargerMinCut(s);
		std::cout << "Minimum cut edges count: " << result.edges.size() << std::endl;
 	}
}