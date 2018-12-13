#pragma once

#include "NodeInterface.h"
#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
public:
	Node* root;
	Node* T;
	AVL();
	~AVL();

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const; //DONE

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data); //DONE

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data); //DONE

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear(); //DONE
	bool insert(Node *&T, int val); //DONE
	bool removeNode(Node *&T, int val); //DONE
	Node* traverseTree(Node* &T); //DONE
	void deleteNodes(Node *T); //DONE
	void rotateLeft(Node *&T);
	void rotateRight(Node *&T);
	void rotateRightLeft(Node *&T);
	void rotateLeftRight(Node *&T);
	bool rebalance(Node *&T, int val);
};
