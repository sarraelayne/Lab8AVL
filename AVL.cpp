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
	    return root;
	}

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool AVL::add(int val) {
	    insert(root, val);	
	}
	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool AVL::remove(int val) {
		bool removeTrue = removeNode(root, val);
		rebalance(root, val);
		return removeTrue;
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
	        T->height = 0;
	        return true;
	    }
	    if (T->val == val) {
	    	return false;
	    }
	    if (T->val < val) {
	    	bool nodeBool = insert(T->rightChild, val);
	    	if (nodeBool == true) {
	    		if(T->getBalance() > 1) {
	    			rotateLeft(T);
	    		}
	    		if (T->getBalance() < -1) {
	    			rotateRight(T);
	    		}
	    	}
	        return nodeBool;
	    }
	    else if (T->val > val) {
	    	bool nodeBool2 = insert(T->leftChild, val);
	    	if (nodeBool2 == true) {
	    		if (T->getBalance() > 1) {
	    			rotateLeft(T);
	    		}
	    		if(T->getBalance() < -1) {
	    			rotateRight(T);
	    		}
	    	}
	        return nodeBool2;
	    }
	    if (T->getBalance() > 1) {
	    	rotateLeft(T);
	    }
	    if (T->getBalance() < -1) {
	    	rotateRight(T);
	    }
	    return false;
	}
	bool AVL::removeNode(Node *&T, int val) {
		bool removeOne;
		bool removeTwo;
		if (T == NULL) {
			return false;
		}
		if (val < T->val) {
			removeOne = removeNode(T->leftChild, val);
			cout << "rebalance1" << endl;
			rebalance(T, val);
			return removeOne;
		}
		if (val > T->val) {
			removeTwo = removeNode(T->rightChild, val);
			cout << "rebalance2" << endl;
			rebalance(T, val);
			return removeTwo;
		}
		if(T->leftChild == NULL && T->rightChild == NULL) {
			delete T;
			T = NULL;
			return true;
		}
		if (T->rightChild != NULL && T->leftChild == NULL) {
			Node* tempNode = T->rightChild;
			delete T;
			T = tempNode;
			cout << "rebalance3" << endl;
			rebalance(T, val);
			return true;
		}
		if (T->rightChild == NULL && T->leftChild != NULL) {
			Node* tempNode = T->leftChild;
			delete T;
			T = tempNode;
			cout << "rebalance4" << endl;
			rebalance(T, val);
			return true;
		}
		Node* tempNode = traverseTree(T->leftChild);
		tempNode->leftChild = T->leftChild;
		tempNode->rightChild = T->rightChild;
		delete T;
		T = tempNode;
		return true;
	}
	Node* AVL::traverseTree(Node *&T) {
		if (T->rightChild == NULL) {
			Node * tempNode = T;
			T = T->leftChild;
			return tempNode;
		}
		Node *tempNode = traverseTree(T->rightChild);
		rebalance(T, T->val);
		return tempNode;
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
	bool AVL::rebalance(Node *&T, int val) {
		if(T == NULL) {
			return false;
		}
		if (T->getBalance() > 1) {
			rotateLeft(T);
		}
		else if (T->getBalance() < -1) {
			rotateRight(T);
		}
		rebalance(T->leftChild, val);
		rebalance(T->rightChild, val);
	}
	
	void AVL::rotateLeft(Node *&T) {
		cout << "rotate left" << endl;
		if (T == NULL) {
			return;
		}
		if (T->rightChild->getBalance() <= -1) {
			rotateRightLeft(T->rightChild);
		}
		rotateLeftRight(T);
	}
	
	void AVL::rotateRight(Node *&T) {
		cout << "rotate right" << endl;
		if (T == NULL) {
			return;
		}
		if (T->leftChild->getBalance() >= 1) {
			rotateLeftRight(T->leftChild);
		}
		rotateRightLeft(T);
	}
	void AVL::rotateLeftRight(Node *&T) {
		Node * newNode = T->rightChild;
		T->rightChild = newNode->leftChild;
		newNode->leftChild = T;
		T = newNode;
	}
	void AVL::rotateRightLeft(Node* &T) {
		Node *newNode = T->leftChild;
		T->leftChild = newNode->rightChild;
		newNode->rightChild = T;
		T = newNode;
	}
