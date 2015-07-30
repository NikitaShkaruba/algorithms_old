#pragma once
#include <vector>

namespace algo {
	class RedBlackTree {
	public:
		RedBlackTree(int value);
		RedBlackTree(int* arr, size_t size);

		void insert(int value);
		void remove(int value);
		bool contains(int value) const;

		void preTraversal(void action(RedBlackTree* node));
		void inTraversal(void action(RedBlackTree* node));
		void postTraversal(void action(RedBlackTree* node));
		bool isBinaryTree() const;
	
	private:
		void fix_();
		RedBlackTree* getRoot();
		bool isRoot() const;
		bool isLeft() const;
		bool isRight() const;
		void leftRotate();
		void rightRotate();
		void growRight(RedBlackTree* node);
		void growLeft(RedBlackTree* node);

		enum colors { black = false, red = true };
		RedBlackTree* getGrandpa();
		RedBlackTree* getUncle();
		RedBlackTree *parent_, *left_, *right_;
		bool color_;
		int key_;
	};
	class AVLTree {
	public:
		AVLTree(int key);
		AVLTree(int* arr, size_t size);

		void insert();
		void remove();
		bool contains(int value) const;
	
	private:
		void SmallLeftRotate();
		void SmallRightRotate();
		void BigLeftRotate();
		void BigRightRotate();

		void GrowLeft(AVLTree* node);
		void GrowRight(AVLTree* node);

		AVLTree *left_, *right_;
		int bFactor_, key_;
	};

	class Heap {
	public:
		Heap();
		Heap(int* arr, size_t size);
		~Heap();

		bool empty(void) const;
		size_t size(void) const;

		void push(int value);
		int pop();
		int peek();
		void clear();

	private:
		int* arr;
		size_t count;
		size_t memory;

		void allocate();
		void heapify(size_t index);
	};

	class Edge; // early declaration coz of  Node's private vector of Edges
	class Node {
	public:
		Node(Node* nodesToConnect, size_t nodeCount);
		Node();
		~Node();
	
		void attach(Node* neighbour);
		void merge(Node* node);
		void crop(Node* node);
		Node* go(Edge* edge) const;
		bool isConnected(Node* neighbour) const;
	
	private:
		std::vector<Edge*> edges_;
	};
	class Edge {
	public:
		Edge(Node* from, Node* to);
		Edge(Edge& edge);
		Edge();
		~Edge();
		
		bool isSelfLoop() const;
		void fuse();
	
		Node* from_;
		Node* to_;
	};
	class Graph {
	public:
		Graph(Node* nodes, Edge* edges, size_t nodesCount, size_t edgesCount);
		Graph(Node* nodes, size_t nodesCount);
		Graph(Graph& graph);
	
		Node* getNodes();
		Edge* getEdges();
		size_t getNodesCount() const;
		size_t getEdgesCount() const;
	
	private:
		Node* nodes_;	// O(n)
		Edge* edges_;
		size_t n_, m_;	// node Count and edge Count respectively
	};
}