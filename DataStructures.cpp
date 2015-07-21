#include "DataStructures.h"

namespace algo {
	class RedBlackTree {
	public:
		explicit RedBlackTree(int value) : key_(value), color_(red), parent_(nullptr), left_(0), right_(0) {}
		explicit RedBlackTree(int* arr, size_t size) : RedBlackTree(arr[0]) {
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
		virtual bool contains(int value) {
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
			return(grandPa)? ((this->parent_->isLeft()) ? grandPa->right_ : grandPa->left_) : nullptr;
		}

		RedBlackTree *parent_, *left_, *right_;
		bool color_;
		int key_;
	};
}