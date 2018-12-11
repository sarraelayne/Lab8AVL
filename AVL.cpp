#include "AVL.h"
#include "Node.h"
#include <iostream>

using namespace std;

    AVL::AVL() {
        root = NULL;
    }
    AVL::~AVL() {
        clear();
    }
    NodeInterface * AVL::getRootNode() const {
	    cout << "getRootNode"<<endl;
	    return root;
	}

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool AVL::add(int val) {
	    return insert(root, val);	
	}
	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool AVL::remove(int val) {
		return removeNode(root, val);
	}
	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void AVL::clear() {
	    deleteNodes(root);
	    root = NULL;
	}
	bool AVL::insert(Node *&T, int val) {
		if (T == NULL) {
	        T = new Node(val);
	        return true;
	    }
	    if (T->val < val) {
	        return insert(T->rightChild, val);
	    }
	    if (val < T->val) {
	        return insert(T->leftChild, val);
	    }
	    return false;
	}
	bool AVL::removeNode(Node *&T, int val) {
		if (T == NULL) {
			return false;
		}
		if (val == T->val) {
			if(T->leftChild == NULL && T->rightChild == NULL) {
				Node* tempNode = T;
				T = NULL;
				delete tempNode;
				return true;
			}
			if (T->rightChild != NULL && T->leftChild == NULL) {
				Node* tempNode = T;
				T = T->rightChild;
				delete tempNode;
				return true;
			}
			if (T->rightChild == NULL && T->leftChild != NULL) {
				Node* tempNode = T;
				T = T->leftChild;
				delete tempNode;
				return true;
			}
			else {
				T->val = traverseTree(T->leftChild);
				removeNode(T->leftChild, T->val);
			}
		}
		else if (val < T->val) {
			removeNode(T->leftChild, val);
		}
		else {
			removeNode(T->rightChild, val);
		}
	}
	int AVL::traverseTree(Node *T) {
		if (T == NULL) {
			return -1;
		}
		int currVal = T->val;
		Node *leftChild = T->leftChild;
		Node *rightChild = T->rightChild;
		if (leftChild != NULL) {
			int left = traverseTree(leftChild);
			if (left > currVal) {
				currVal = left;
			}
		}
		if (rightChild != NULL) {
			int right = traverseTree(rightChild);
			if (right > currVal) {
				currVal = right;
			}
		}
		return currVal;
	}
	void AVL::deleteNodes(Node *T) {
		if (T == NULL) {
			return;
		}
		if (T->leftChild != NULL) {
			deleteNodes(T->leftChild);
		}
		if (T->rightChild != NULL) {
			deleteNodes(T->rightChild);
		}
		delete T;
		return;
	}
	int AVL::getBalance(Node *T) {
		int leftHeight;
		int rghtHeight;
		
		if (T->leftChild) {
			leftHeight = T->leftChild->height+1;
		}
		else {
			leftHeight = 0;
		}
		if (T->rightChild) {
			rghtHeight = T->rightChild->height + 1;
		}
		else {
			rghtHeight = 0;
		}
		return (rghtHeight - leftHeight);
	}
	void AVL::rebalance(Node *T) {
		int balance = getBalance(T);
		
		if (balance < -1) {
			if(getBalance(T->leftChild) < 1) {//LEFT LEFT
				rotateRight(T);
			}
			else { //LEFT RIGHT
				rotateLeft(T->leftChild);
				rotateRight(T);
			}
		}
		if (balance > 1) { //RIGHT RIGHT
			if (getBalance(T->rightChild) > -1) {
				rotateLeft(T);
			} 
			else { //RIGHT LEFT
				rotateRight(T->rightChild);
				rotateLeft(T);
			}
		}
	}
	//If diff > 1 rotate left
	//If diff < -1 rotate right
	
	void AVL::rotateLeft(Node *&T) {
		Node *prevNode = T;
		Node *newNode = T->rightChild;
		T = newNode;
		prevNode->rightChild = newNode->leftChild;
		newNode->leftChild = prevNode;
		prevNode->updateHeight();
		newNode->updateHeight();
	}
	void AVL::rotateRight(Node *&T) {
		Node *prevNode = T;
		Node *newNode = T->leftChild;
		T = newNode;
		prevNode->leftChild = newNode->rightChild;
		newNode->rightChild = prevNode;
		prevNode->updateHeight();
		newNode->updateHeight();
	}
	void AVL::updateHeight() {
		int lft = getHeight(T->leftChild);
		int rght = getHeight(T->rightChild);
		if (lft > rght) {
			height = lft + 1;
		}
		else {
			height = rght + 1;
		}
	}
	int getHeight (Node* T) {
		if (T == NULL) {
			return -1;
		}
		else {
			return T->height;
		}
	}
