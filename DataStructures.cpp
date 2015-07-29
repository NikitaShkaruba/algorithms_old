#include "DataStructures.h" // for solving Node-Edge self-including problem. Man. Sry if it bores you.
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

namespace algo {
	// Shit, add a header, dumb ass.
	class RedBlackTree {
	public:
		RedBlackTree::RedBlackTree(int value) : key_(value), color_(red), parent_(nullptr), left_(0), right_(0) {}
		RedBlackTree::RedBlackTree(int* arr, size_t size) : RedBlackTree(arr[0]) {
			this->color_ = black;

			for (size_t i = 1; i < size; i++)
				this->getRoot()->insert(arr[i]);
		}

		void insert(int value)  {
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
		void remove(int value)  { }
		bool contains(int value) {
			if (key_ < value && left_)
				return left_->contains(value);
			if (key_ > value && right_)
				return right_->contains(value);

			if (key_ == value)
				return true;
			return false;
		}
		void preTraversal(void action(RedBlackTree* node)) {
			action(this);

			if (left_)
				left_->preTraversal(action);

			if (right_)
				right_->preTraversal(action);
		}
		void inTraversal(void action(RedBlackTree* node)) {
			if (left_)
				left_->inTraversal(action);

			action(this);

			if (right_)
				right_->inTraversal(action);
		}
		void postTraversal(void action(RedBlackTree* node)) {
			if (left_)
				left_->postTraversal(action);

			if (right_)
				right_->postTraversal(action);

			action(this);
		}
		bool isBinaryTree() {
		if (this->left_ && this->right_)
			return this->left_->key_ < this->key_ && this->key_ < this->right_->key_;
		else if (this->left_)
			return this->left_->key_ < this->key_;
		else if (this->right_)
			return this->key_ < this->right_->key_;
	}
	
	private:
		void fix_() {
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
		RedBlackTree* getRoot() {
			RedBlackTree* current = this;
			while (current->parent_)
				current = current->parent_;

			return current;
		}
		bool isRoot() {
			return this->parent_ == nullptr;
		}
		bool isLeft() {
			return (parent_->left_ == this);
		}
		bool isRight() {
			return (parent_->right_ == this);
		}
		void leftRotate() {
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
		void rightRotate() {
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
		void growRight(RedBlackTree* node) {
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
		void growLeft(RedBlackTree* node) {
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
		enum colors { black = false, red = true };
		RedBlackTree* getGrandpa() {
			return parent_ ? parent_->parent_ : nullptr;
		}
		RedBlackTree* getUncle() {
			RedBlackTree* grandPa = getGrandpa();
			return(grandPa) ? ((this->parent_->isLeft()) ? grandPa->right_ : grandPa->left_) : nullptr;
		}
		RedBlackTree *parent_, *left_, *right_;
		bool color_;
		int key_;
	};
	class AVLTree {
	public:
		AVLTree(int key) : left_(0), right_(0), bFactor_(0), key_(key) {}
		AVLTree(int* arr, size_t size) : AVLTree(arr[0]) {
			for (size_t i = 0; i < size; i++) {
								
			}
		}

		void insert() {

		}
		void remove() {

		}
		bool contains(int value) {
			if (key_ < value && left_)
				return left_->contains(value);
			if (key_ > value && right_)
				return right_->contains(value);

			if (key_ == value)
				return true;
			return false;
		}
	
	private:
		void SmallLeftRotate() {
			
		}
		void SmallRightRotate() {
			AVLTree* child = this->left_;
		};
		void BigLeftRotate();
		void BigRightRotate();

		void GrowLeft(AVLTree* node) {
			
		}
		void GrowRight(AVLTree* node) {
				
		}

		AVLTree *left_, *right_;
		int bFactor_, key_;
	};
	class Heap {
	public:
		Heap() : arr(nullptr), count(0), memory(16) {}
		Heap(int* arr, size_t size) : count(0), memory(16) {
			for (size_t i = 0; i < size; i++)
				this->push(arr[i]);
		}
		~Heap() {
			this->clear();
		}

		bool empty(void) const { return (!count); }
		size_t size(void) const { return count; }

		void push(int value) {
			size_t current, parent; 

			_alloc();
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
		int pop() {
			if (count > 0) {
				int buff = arr[0];
				arr[0] = arr[--count];
				this->_heapify(0);
				return buff;
			} else {
				count = 0;
				throw "heap is empty, but you want to get element!";
			}
		}
		int peek() {
			if (count > 1)
				return arr[0];
			else 
				throw "heap is empty, but you want to get element!";
		}
		void clear() {
			if (arr != nullptr)
				delete[] arr;
			arr = nullptr;
			count = 0;
			memory = 16;
		} 

	private:
		int* arr;
		size_t count;
		size_t memory;

		void _alloc() {
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
		void _heapify(size_t index) {
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
	};
	
	template<typename T>
	class List {
	public:
		List() : memory(4), size(0) {
			arr = new T[memory]; 
		}
		List(int first) : memory(4), size(0) {
			this->arr = new T[memory]; 
			this->arr[0] = first;
		}
		List(int* arr_, size_t size_): memory(size_ + 4), size(size_) {
			arr = new T[memory];
			for(size_t i = 0; i < size; i++)
				arr[i] = arr_[i];
		}

		void insert(int element) {
			if (size == memory) {
				T* newArr = new int[memory *= 2];
				std::memcpy(newArr, arr, size);
				delete arr;
				arr = newArr;
			}
			arr[size++] = element;
		}
		void remove(int index) {
			for(size_t i = index; i < size-1; i++)
				arr[i] = arr[i+1];
			size--;
		}
		
		T* getArray() {
			return arr;
		}
		size_t getSize() {
			return size;
		}
		int operator[] (int index) {
			if (index < size)
				return arr[index];
			else 
				throw "List index out of size";
		}
	private:
		T* arr;
		size_t size;
		size_t memory;
	};

	class Edge {
	public:
		Edge(Edge& edge): from_(edge.from_), to_(edge.to_) {}
		Edge(Node* from, Node* to) : from_(from), to_(to) {}
		Edge(): from_(nullptr), to_(nullptr) {}
		~Edge() {
			from_->crop(to_);
			to_->crop(from_);
		}
		
		bool isSelfLoop() {
			return from_ == to_;
		}
		void fuse() {
			from_->merge(to_);
		}

		Node* from_;
		Node* to_;
	};
	class Node {
	public:
		Node(Node* nodesToConnect, size_t nodeCount) : edges_() {
			for(size_t i = 0; i < nodeCount; i++)
				this->attach(&nodesToConnect[i]);	
		}
		Node() : edges_() {}
		~Node() {
			for (auto i = edges_.begin(); i != edges_.end(); i++)
				delete *i;
		}

		void attach(Node* neighbour) {
			Edge* edge = new Edge(this, neighbour);
			
			neighbour->edges_.push_back(edge);
			this->edges_.push_back(edge);
		}
		void merge(Node* node) {
			for(auto i = node->edges_.begin(); i != node->edges_.end(); i++)
				attach((*i)->from_ == node ? (*i)->to_ : (*i)->from_);
			delete node;
		}
		void crop(Node* node) {
			for(auto i = edges_.begin(); i < edges_.end(); i++) 
				if ((*i)->from_ == node || (*i)->to_ == node) {
					edges_.erase(i);
					return;
				}
			throw "This node have not this edge.";
		}
		Node* go(Edge* edge) const  {
			if (edge->from_ == this || edge->to_ == this)
				return edge->from_ == this? edge->to_ : edge->from_;	
			else 
				throw "This node don't have this edge";
		}

	private:
		vector<Edge*> edges_;
	};
	class Graph {
	public:
		explicit Graph(Node* nodes, Edge* edges, size_t nodeCount, size_t edgeCount) : nodes_(nodes), edges_(edges), n_(nodeCount), m_(edgeCount) {}
		Graph(Graph& graph) {
			n_ = graph.n_;
			m_ = graph.m_;
			nodes_ = new Node[n_];
			edges_ = new Edge[m_];
		}

		Node* getNodes() {
			return nodes_;
		}
		Edge* getEdges() {
			return edges_;
		}
		size_t getNodesCount() {
			return n_;
		}
		size_t getEdgesCount() {
			return m_;
		}

	private:
		Node* nodes_;	// O(n)
		Edge* edges_;	// O(m)
		size_t n_, m_;	// node Count and edge Count respectively
	};
}