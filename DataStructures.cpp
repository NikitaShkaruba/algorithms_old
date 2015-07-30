#include "DataStructures.h" 
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

namespace algo {
	// Red-Black tree
	RedBlackTree::RedBlackTree(int value) : key_(value), color_(red), parent_(nullptr), left_(0), right_(0) {}
	RedBlackTree::RedBlackTree(int* arr, size_t size) : RedBlackTree(arr[0]) {
		this->color_ = black;

		for (size_t i = 1; i < size; i++)
			this->getRoot()->insert(arr[i]);
	}
	void RedBlackTree::insert(int value)  {
		if (value < key_) {
			if (left_)
				left_->insert(value);
			else {
				growLeft(new RedBlackTree(value));
				left_->fix_();
			}
		}
		if (value > key_) {
			if (right_)
				right_->insert(value);
			else {
				growRight(new RedBlackTree(value));
				right_->fix_();
			}
		}
	}
	void RedBlackTree::remove(int value)  { }
	bool RedBlackTree::contains(int value) const {
		if (key_ < value && left_)
			return left_->contains(value);
		if (key_ > value && right_)
			return right_->contains(value);

		if (key_ == value)
			return true;
		return false;
	}
	void RedBlackTree::preTraversal(void action(RedBlackTree* node)) {
		action(this);

		if (left_)
			left_->preTraversal(action);

		if (right_)
			right_->preTraversal(action);
	}
	void RedBlackTree::inTraversal(void action(RedBlackTree* node)) {
		if (left_)
			left_->inTraversal(action);

		action(this);

		if (right_)
			right_->inTraversal(action);
	}
	void RedBlackTree::postTraversal(void action(RedBlackTree* node)) {
		if (left_)
			left_->postTraversal(action);

		if (right_)
			right_->postTraversal(action);

		action(this);
	}
	bool RedBlackTree::isBinaryTree() const {
		if (this->left_ && this->right_)
			return this->left_->key_ < this->key_ && this->key_ < this->right_->key_;
		else if (this->left_)
			return this->left_->key_ < this->key_;
		else if (this->right_)
			return this->key_ < this->right_->key_;
	}
	void RedBlackTree::fix_() {
		if (this->isRoot())		// case 1
			this->color_ = black;
		else {
			if (this->parent_->color_ == black)		// case 2
				return;
			else {
				RedBlackTree* uncle = this->getUncle();
				RedBlackTree* grandpa = this->getGrandpa();

				if (uncle && uncle->color_ == red) {	// case 3
					this->parent_->color_ = black;
					uncle->color_ = black;
					grandpa->color_ = red;
					grandpa->fix_();
				}
				else {	// case 4
					RedBlackTree* lastOne = this;

					if (this->isRight() && this->parent_->isLeft()) {
						this->leftRotate();
						lastOne = this->left_;
					}
					else if (this->isLeft() && this->parent_->isRight()) {
						this->rightRotate();
						lastOne = this->right_;
					}

					lastOne->parent_->color_ = black;	// case 5					
					lastOne->getGrandpa()->color_ = red;
					if (lastOne->isLeft())
						lastOne->parent_->rightRotate();
					else
						lastOne->parent_->leftRotate();
				}
			}
		}
	}
	RedBlackTree* RedBlackTree::getRoot() {
		RedBlackTree* current = this;
		while (current->parent_)
			current = current->parent_;

		return current;
	}
	bool RedBlackTree::isRoot() const {
		return this->parent_ == nullptr;
	}
	bool RedBlackTree::isLeft() const {
		return (parent_->left_ == this);
	}
	bool RedBlackTree::isRight() const {
		return (parent_->right_ == this);
	}
	void RedBlackTree::leftRotate() {
		RedBlackTree* grandPa = this->getGrandpa();
		RedBlackTree* savedParent = this->parent_;
		RedBlackTree* savedChild = this->left_;

		if (grandPa) {
			if (savedParent->isLeft())
				grandPa->growLeft(this);
			else
				grandPa->growRight(this);
		}

		this->growLeft(savedParent);
		savedParent->growRight(savedChild);
	}
	void RedBlackTree::rightRotate() {
		RedBlackTree* grandPa = getGrandpa();
		RedBlackTree* savedParent = this->parent_;
		RedBlackTree* savedChild = this->right_;

		if (grandPa) {
			if (savedParent->isLeft())
				grandPa->growLeft(this);
			else
				grandPa->growRight(this);
		}

		this->growRight(savedParent);
		savedParent->growLeft(savedChild);
	}
	void RedBlackTree::growRight(RedBlackTree* node) {
		if (node) {
			if (node->parent_) {
				if (node->isLeft())
					node->parent_->left_ = nullptr;
				else
					node->parent_->right_ = nullptr;
			}
			node->parent_ = this;
		}

		if (right_)
			right_->parent_ = nullptr;
		right_ = node;
	}
	void RedBlackTree::growLeft(RedBlackTree* node) {
		if (node) {
			if (node->parent_) {
				if (node->isLeft())
					node->parent_->left_ = nullptr;
				else
					node->parent_->right_ = nullptr;
			}
			node->parent_ = this;
		}

		if (left_)
			left_->parent_ = nullptr;
		left_ = node;
	}
	RedBlackTree* RedBlackTree::getGrandpa() {
		return parent_ ? parent_->parent_ : nullptr;
	}
	RedBlackTree* RedBlackTree::getUncle() {
		RedBlackTree* grandPa = getGrandpa();
		return(grandPa) ? ((this->parent_->isLeft()) ? grandPa->right_ : grandPa->left_) : nullptr;
	}
	
	// AVL Tree
	AVLTree::AVLTree(int key) : left_(0), right_(0), bFactor_(0), key_(key) {}
	AVLTree::AVLTree(int* arr, size_t size) : AVLTree(arr[0]) {
		for (size_t i = 0; i < size; i++) {
								
		}
	}
	void AVLTree::insert() {

	}
	void AVLTree::remove() {

	}
	bool AVLTree::contains(int value) const {
		if (key_ < value && left_)
			return left_->contains(value);
		if (key_ > value && right_)
			return right_->contains(value);

		if (key_ == value)
			return true;
		return false;
	}
	void AVLTree::SmallLeftRotate() {
			
	}
	void AVLTree::SmallRightRotate() {
		AVLTree* child = this->left_;
	};
	void AVLTree::GrowLeft(AVLTree* node) {
			
	}
	void AVLTree::GrowRight(AVLTree* node) {
				
		}
	
	// Heap
	Heap::Heap() : arr(nullptr), count(0), memory(16) {}
	Heap::Heap(int* arr, size_t size) : count(0), memory(16) {
		for (size_t i = 0; i < size; i++)
			this->push(arr[i]);
	}
	Heap::~Heap() {
		this->clear();
	}
	bool Heap::empty(void) const { return (!count); }
	size_t Heap::size(void) const { return count; }
	void Heap::push(int value) {
		size_t current, parent; 

		allocate();
		arr[count] = value;

		current = count++;
		parent = (current == 0) ? 0 : (current - 1) >> 1;

		// pull new one up | reverse heapify 
		while ((current > 0) && arr[current] < arr[parent]) {
			int buf = arr[current];
			arr[current] = arr[parent];
			arr[parent] = buf;

			current = parent--;
			if (current == 0)
				break;
			parent >>= 1;
		}
	}
	int Heap::pop() {
		if (count > 0) {
			int buff = arr[0];
			arr[0] = arr[--count];
			this->heapify(0);
			return buff;
		} else {
			count = 0;
			throw "heap is empty, but you want to get element!";
		}
	}
	int Heap::peek() {
		if (count > 1)
			return arr[0];
		else 
			throw "heap is empty, but you want to get element!";
	}
	void Heap::clear() {
			if (arr != nullptr)
				delete[] arr;
			arr = nullptr;
			count = 0;
			memory = 16;
		} 
	void Heap::allocate() {
			size_t newMemory;
			int* newArr;

			if (arr == nullptr)
				arr = new int[memory];

			// If memory dried up
			if ((count + 1) >= memory) {
				newMemory = count * 2;
				newArr = new int[newMemory];
				for (size_t i = 0u; i < count; i++)
					newArr[i] = arr[i];
				delete[] arr;
				arr = newArr;
				memory = newMemory;
			}
		}
	void Heap::heapify(size_t index) {
		size_t l, r, small;

		while (true) {
			l = (index << 1) + 1u;
			r = (index << 1) + 2u;

			// Who's the smallest?
			if ((l < count) && arr[l] < arr[index])
				small = l;
			else
				small = index;
			if ((r < count) && arr[r] < arr[small])
				small = r;

			// put it in
			if (small != index) {
				int buffer = arr[index];
				arr[index] = arr[small];
				arr[small] = buffer;
				index = small; // And go down
			}
			else break;
		}
	}

	// Graph
	Graph::Graph(Node* nodes, Edge* edges, size_t nodesCount, size_t edgesCount) : nodes_(nodes), edges_(edges), n_(nodesCount), m_(edgesCount) {}
	Graph::Graph(Node* nodes, size_t nodesCount) : nodes_(nodes), n_(nodesCount) {
		// implement later
	}
	Graph::Graph(Graph& graph) {
		n_ = graph.n_;
		nodes_ = new Node[n_];
	}
	Node* Graph::getNodes() {
		return nodes_;
	}
	Edge* Graph::getEdges() {
		return edges_;
	}
	size_t Graph::getNodesCount() const {
		return n_;
	}
	size_t Graph::getEdgesCount() const {
			return m_;
		}
	
	// Node
	Node::Node(Node* nodesToConnect, size_t nodeCount) : edges_() {
		for(size_t i = 0; i < nodeCount; i++)
			this->attach(&nodesToConnect[i]);	
	}
	Node::Node() : edges_() {}
	Node::~Node() {
		for (auto i = edges_.begin(); i != edges_.end(); i++)
			delete *i;
	}
	void Node::attach(Node* neighbour) {
		Edge* edge = new Edge(this, neighbour);
			
		neighbour->edges_.push_back(edge);
		this->edges_.push_back(edge);
	}
	void Node::merge(Node* node) {
		for(auto i = node->edges_.begin(); i != node->edges_.end(); i++)
			attach((*i)->from_ == node ? (*i)->to_ : (*i)->from_);
		delete node;
	}
	void Node::crop(Node* node) {
		for(auto i = edges_.begin(); i < edges_.end(); i++) 
			if ((*i)->from_ == node || (*i)->to_ == node) {
				edges_.erase(i);
				return;
			}
		throw "This node have not this edge.";
	}
	Node* Node::go(Edge* edge) const  {
		if (edge->from_ == this || edge->to_ == this)
			return edge->from_ == this? edge->to_ : edge->from_;	
		else 
			throw "This node don't have this edge";
	}
	bool Node::isConnected(Node* neighbour) const {
		for(auto i = edges_.begin(); i != edges_.end(); i++)
			if ((*i)->from_ == neighbour || (*i)->to_ == neighbour)
				return true;
		return false;
	}
	
	// Edge
	Edge::Edge(Node* from, Node* to) : from_(from), to_(to) {}
	Edge::Edge(Edge& edge): from_(edge.from_), to_(edge.to_) {}
	Edge::Edge(): from_(nullptr), to_(nullptr) {}
	Edge::~Edge() {
		from_->crop(to_);
		to_->crop(from_);
	}
	bool Edge::isSelfLoop() const {
		return from_ == to_;
	}
	void Edge::fuse() {
		from_->merge(to_);
	}
}