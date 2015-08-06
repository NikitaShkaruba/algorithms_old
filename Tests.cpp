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
		Edge(Node* from_, Node* to_) : from(from_), to(to_) {} 
		~Edge() {}

		bool operator==(const Edge& other) {
			return (from == other.from && to == other.to || from == other.to && to == other.from);
		}
		bool operator!=(const Edge& other) {
			return (!(*this == other));
		}
		bool isSelfLoop() {
			return (from == to);
		}

		Node* from;
		Node* to;
	};
	struct Node {
	public:
		Node(string content) : edges(), label(content), isExplored(false) {}
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
			
			return this->label == other.label;
		}

		size_t f;
		Node* leader; // for kosaragu's
		bool isExplored;
		vector<Edge*> edges;
		string label;
	};
	class Graph {
	public:
		Graph(const Graph& graph) { // !
			for (auto it = graph.nodes.begin(); it != graph.nodes.end(); it++)
				this->nodes.push_back(Node {it->label});
			for (auto it = graph.edges.begin(); it != graph.edges.end(); it++)
				connect(it->from, it->to);
		}
		Graph() : nodes(), edges() {}
		~Graph() {}
		
		Graph& operator=(const Graph& graph) {
			// wut
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
					if (i->label == content)
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
		void reverseEdges() {
			for each (Edge edge in edges) {
				Node* buf = edge.from;
				edge.from = edge.to;
				edge.to = buf;
			}
		}

		bool areConnected(Node* a, Node* b) {
			for (auto i = a->edges.begin(); i != a->edges.end(); i++)
				if (*(*i)->from == *b || *(*i)->to == *b)
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
			Node* merged = edge->from;
			Node* extincted = edge->to;

			// concat content and rebind edges
			merged->label += "." + extincted->label;
			vector<Edge*>::iterator i = extincted->edges.begin();
			while (i != extincted->edges.end()) {
				if (**i != weak) {
					merged->edges.push_back(&**i);
					if ((*i)->from == extincted)
						(*i)->from = merged;
					else 
						(*i)->to = merged;
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
		
		bool isOrdered;
		list<Node> nodes;	// O(n)
		list<Edge> edges;   // O(m)
	};

	Node* BreadthFirstSearchCanon(Graph graph, Node* start, string whatToFind) { // Didn't tested
			// O(m + n) = O(n)
			// Warning! all nodes have to be initially unexplored
			queue<Node*> q;
			q.push(start);
			start->isExplored = true;

			while (!q.empty()) {
				Node* node = q.front(); q.pop();
				for (auto edge = node->edges.begin(); edge != node->edges.end(); edge++) {
					Node* next = ((*edge)->from == node)? (*edge)->to : (*edge)->from;
					if (next->isExplored == false) {
						if (next->label == whatToFind)
							return next;
						next->isExplored = true;
						q.push(next);
					}
				}
			}
		}
	Node* DepthFirstSearchCanon(Graph graph, Node* start, string whatToFind) { // Didn't tested
		// Complexity: O(m + n)
		// Caution: all nodes have to be unexplored
		start->isExplored = true;
		for (vector<Edge*>::iterator it = start->edges.begin(); it != start->edges.end(); it++) {
			Node* next = ((*it)->from == start)? (*it)->to : (*it)->from;
			if (next->isExplored == false) {
				if (next->label == whatToFind)
					return next;

				next->isExplored = true;
				return DepthFirstSearchCanon(graph, next, whatToFind);
			}
		}
		return nullptr;
	}
	Graph KargerMinCut(Graph graph) { // There's a bug i can't find
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
	void DepthFirstSearch(Graph graph, Node* start, list<Node*>& l) {
		// this function for Topological search
		for (auto edge = start->edges.begin(); edge != start->edges.end(); edge++) {
			Node* next = (*edge)->to;
			if (next->isExplored == false) {
				next->isExplored = true;
				DepthFirstSearch(graph, next, l);
			}
		}

		l.push_front(start);
	}
	list<Node*> TopologicalSort(Graph graph) { // Didn't tested
		graph.uncheckNodes();
		list<Node*> result;
		for (auto node = graph.nodes.begin(); node != graph.nodes.end(); node++)  {
			if (node->isExplored == false) {
				node->isExplored = true;
				DepthFirstSearch(graph, &*node, result);
			}
		}
		return result;
	};
	////////////////////////////////////
	static size_t nodesFinished = 0;
	static Node* source = nullptr;
	void DFS(Graph& graph, Node& node) {
		node.isExplored = true;
		node.leader = source;

		for each (Edge* edge in node.edges) {
			if (edge->to->isExplored == false)
				DFS(graph, node);
		}
		node.f = ++nodesFinished;
	}
	void DFS_Loop(Graph& graph) {

		// assume every nodes labeled 1 to n
		for each (Node node in graph.nodes) {
			if (node.isExplored == false) {
				source = &node;
				DFS(graph, node);
			}
		}
	}
	void KasaraguSCC(Graph graph) { // No tests at all
		// Complexity: O(2(m + n)) = O(n)

		// Part 1
		graph.reverseEdges();

		// Part 2 will compute magical ordering of nodes
		DFS_Loop(graph);

		// Part 3 will discover SCCs one by one
		graph.reverseEdges();
		DFS_Loop(graph);

		// Get all things right
		vector<vector<Node>> result;
		for each (Node node in graph.nodes) {
			result.at(stoi(node.label)).push_back(node);
		}
	}
	////////////////////////////////////
	vector<Graph> cutGraphs(Graph graph) { // Didn't tested
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
						Node* next = ((*edge)->from == node)? (*edge)->to : (*edge)->from;
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
		return result;
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

				Node* it = result.getNode(center.label);
				Node* jt = result.getNode(adjacent.label);

				if (!result.areConnected(it, jt))
					result.connect(it, jt);
			}
		}

		return result;
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