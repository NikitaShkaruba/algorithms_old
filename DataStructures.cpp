#include "DataStructures.h"

namespace algo {
	class Tree {
	public:
		explicit Tree() : left_(nullptr), right_(nullptr), key_(0) {}
		explicit Tree(int value) : left_(nullptr), right_(nullptr), key_(value) {}
		virtual ~Tree() {
			if (left_) {
				left_->~Tree();
				delete left_;
			}
			if (right_) {
				right_->~Tree();
				delete right_;
			}
		};

		virtual void insert(int value) = 0;
		virtual void remove(int value) = 0;
		virtual bool contains(int value) {
			if (key_ < value && left_)
				return left_->contains(value);
			if (key_ > value && right_)
				return right_->contains(value);
			
			if (key_ == value)
				return true;
			return false;
		}

		bool preTraversal(void action()) {
			action();

			if (left_)
				left_->inTraversal(action);

			if (right_)
				right_->inTraversal(action);
		}
		bool inTraversal(void action()) {
			if (left_)
				left_->inTraversal(action);
			
			action();

			if (right_)
				right_->inTraversal(action);
		}
		bool postTraversal(void action()) {
			if (left_)
				left_->inTraversal(action);

			if (right_)
				right_->inTraversal(action);
			
			action();
		}

	protected:
		Tree* left_;
		Tree* right_;
		int key_;
	};

	class RedBlackTree : Tree {
	// *******Red-Black requirements*******
	// 1. A node is either red or black.
	// 2. The root is black.
	// 3. All leaves are black.
	// 4. Every red node must have two black child nodes, and therefore it must have a black parent.
	// 5. Every path from a given node to any of its descendant leaves contains the same number of black nodes.
	public:
		explicit RedBlackTree(int value) : Tree(value), color_(red) { }
		void insert(int value) override {
			if (value < key_) {
				if (left_)
					left_->insert(value);
				else {
					left_ = new RedBlackTree(value); 
					dynamic_cast<RedBlackTree*>(left_)->parent_ = this;
					dynamic_cast<RedBlackTree*>(left_)->fix_();
				}
			}
			if (value > key_ && right_) {
				if (right_)
					right_->insert(value);
				else {
					right_ = new RedBlackTree(value);
					dynamic_cast<RedBlackTree*>(right_)->parent_ = this;
					dynamic_cast<RedBlackTree*>(right_)->fix_();
				}
			}
		}
		void remove(int value) override { }
	
	private:
		void fix_() {
			if (this->isRoot())												// case 1
				this->color_ = black;
			else {
				if (this->parent_->color_ == black)							// case 2
					return;
				else {
					if (this->uncle_() && this->uncle_()->color_ == red) {	// case 3
						this->parent_->color_ = black;
						this->uncle_()->color_ = black;
						this->grandpa_()->color_ = red;
						this->grandpa_()->fix_();

					} else {												// case 4
						RedBlackTree* lastOne = this;
						
						if (this == this->parent_->right_ && this->parent_ == this->grandpa_()->left_) {
							this->parent_->leftRotate();
							lastOne = dynamic_cast<RedBlackTree*>(this->left_);
						} else if (this == this->parent_->left_ && this->parent_ == this->grandpa_()->right_) {
							this->parent_->rightRotate();
							lastOne = dynamic_cast<RedBlackTree*>(this->right_);
						}

						lastOne->parent_->color_ = black;					// case 5
						lastOne->grandpa_()->color_ = red;
						if (lastOne == lastOne->parent_->left_)
							lastOne->grandpa_()->rightRotate();
						else
							lastOne->grandpa_()->leftRotate();
					}
				}
			}
		}
		bool isRoot() {
			return this->parent_ == nullptr;
		}
		enum colors { black = false, red = true };
		bool color_;


		void leftRotate() {
			// implement later
		}
		void rightRotate() {
			// impement later
		}
		RedBlackTree* grandpa_() {
			return parent_ ? parent_->parent_ : nullptr;
		}
		RedBlackTree* uncle_() {
			if (parent_)
				return dynamic_cast<RedBlackTree*>((grandpa_()->left_ == this) ? grandpa_()->right_ : grandpa_()->left_);
			else
				return nullptr;
		}
		RedBlackTree* parent_;
	};
}