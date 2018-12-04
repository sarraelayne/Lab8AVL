main: main.cpp Node.h NodeInterface.h AVL.h AVLInterface.h AVL.cpp
	g++ -std=c++11 main.cpp AVL.cpp -o main -g