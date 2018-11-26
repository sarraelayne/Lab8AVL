
CC = g++
CCFLAGS = -std=c++11
bst: main.cpp BSTInterface.h NodeInterface.h BST.h BST.cpp Node.h 
	$(CC) $(CCFLAGS) -g -o bst main.cpp BST.cpp



