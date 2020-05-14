#pragma once
#include <vector>
#include <iostream>

enum class rot { LL, RR, LR, RL, Balanced, ERROR };
template <typename T>
class Node {
public:
	Node();
	Node(T element);
	Node* nodeHigher;
	Node* nodeLower;
	T data;
};
template <typename T>
class AVLTree {
public:

	Node<T>* root;
	bool nodeNull(Node<T>* &node);
public:
	AVLTree();//done
	AVLTree(T element);//done
	void insert(T element, Node<T> *node = nullptr);//NOT DONE
	void remove(T element, Node<T> *node = nullptr);//NOT DONE
	bool find(T element, Node<T> *node = nullptr);//done
	std::vector<T> preOrderWalk();//done
	std::vector<T> inOrderWalk();//done
	std::vector<T> postOrderWalk();//done
	size_t getTreeHeight(Node<T> *node = nullptr);//done
	T getMin(Node<T> *node = nullptr);//done
	T getMax(Node<T> *node = nullptr);//done
									  //bool isBalanced(Node<T>** node = nullptr);
	bool isBalanced(Node<T>*& node);
	void balance();
	std::string ToGraphviz(Node<T>* root);
	void writeTree();
	void writeTree2(Node<T>* node, int space);
private:
	void preOrderWalk2(std::vector<T> &theReturn, Node<T> *node);//done
	void inOrderWalk2(std::vector<T> &theReturn, Node<T> *node);//done
	void postOrderWalk2(std::vector<T> &theReturn, Node<T> *node);//done
	int difference(Node<T> *node);
	Node<T>* LLRotation(Node<T> *node);
	Node<T>* RRRotation(Node<T> *node);
	Node<T>* LRRotation(Node<T> *node);
	Node<T>* RLRotation(Node<T> *node);
	//void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);

};

template<typename T>
inline AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template<typename T>
inline AVLTree<T>::AVLTree(T element)
{
	root = new Node<T>(element);
}

template<typename T>
inline bool AVLTree<T>::nodeNull(Node<T> *& node)
{
	if (node == nullptr)
	{
		if (this->root == nullptr) {
			std::cout << "error no Data" << std::endl;
			return false;
		}
		node = root;
	}
	return true;
}

template<typename T>
inline void AVLTree<T>::insert(T element, Node<T> * node)
{
	if (root == nullptr) {
		root = new Node<T>(element);
	}
	else {
		if (node == nullptr)
		{
			node = root;
		}
		if (element > node->data) {
			if (node->nodeHigher != nullptr) {
				insert(element, node->nodeHigher);
			}
			else {
				node->nodeHigher = new Node<T>(element);
			}
		}
		else if (element < node->data) {
			if (node->nodeLower != nullptr) {
				insert(element, node->nodeLower);
			}
			else {
				node->nodeLower = new Node<T>(element);
			}
		}
	}
	if (node == root) {
		isBalanced(root);
	}
}

template<typename T>
inline bool AVLTree<T>::find(T element, Node<T> * node)
{
	bool theReturn = false;
	if (!nodeNull(node)) {
		bool *error = new bool(false);
		return *error;
	}
	else {
		if (element == node->data) {
			theReturn = true;
		}
		else if (element > node->data) {
			if (node->nodeHigher != nullptr) {
				theReturn = find(element, node->nodeHigher);
			}
			else {
				theReturn = false;
			}
		}
		else if (element < node->data) {
			if (node->nodeLower != nullptr) {
				theReturn = find(element, node->nodeLower);
			}
			else {
				theReturn = false;
			}
		}
	}
	return theReturn;
}

template<typename T>
inline T AVLTree<T>::getMin(Node<T> * node)
{
	T theReturn;
	if (!nodeNull(node)) {
		T *error = new T();
		return *error;
	}
	if (node->nodeLower != nullptr) {
		theReturn = getMin(node->nodeLower);
	}
	else {
		theReturn = node->data;
	}
	return theReturn;
}

template<typename T>
inline T AVLTree<T>::getMax(Node<T> * node)
{
	T theReturn;
	if (!nodeNull(node)) {
		T *error = new T();
		return *error;
	}
	if (node->nodeHigher != nullptr) {
		theReturn = getMax(node->nodeHigher);
	}
	else {
		theReturn = node->data;
	}
	return theReturn;
}

template<typename T>
inline bool AVLTree<T>::isBalanced(Node<T>*& node)
{
	bool theReturn = false;
	if (!nodeNull(node)) {

	}
	else {
		if (node->nodeHigher != nullptr) {
			isBalanced(node->nodeHigher);
		}
		if (node->nodeLower != nullptr) {
			isBalanced(node->nodeLower);
		}

		if (difference(node) > 1) {
			if (difference(node->nodeLower) > 0) {
				node = LLRotation(node);
			}
			else {
				node = LRRotation(node);
			}
		}
		else if (difference(node) < -1) {
			if (difference(node->nodeHigher) > 0) {
				node = RLRotation(node);
			}
			else {
				node = RRRotation(node);
			}
		}
	}
	return theReturn;
}

template<typename T>
inline void AVLTree<T>::writeTree()
{
	writeTree2(root, 0);
}

template<typename T>
inline void AVLTree<T>::writeTree2(Node<T>* node, int space)//taken from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
{
	const int COUNT = 5;
	if (node == nullptr) {
		return;
	}
	space += COUNT;
	writeTree2(node->nodeHigher, space);
	for (int i = COUNT; i < space; i++) {
		std::cout << " ";
	}
	std::cout << node->data << std::endl;

	writeTree2(node->nodeLower, space);

}

template<typename T>
void AVLTree<T>::preOrderWalk2(std::vector<T>& theReturn, Node<T> *node)
{
	theReturn.push_back(node->data);
	if (node->nodeLower != nullptr) {
		preOrderWalk2(theReturn, node->nodeLower);
	}
	if (node->nodeHigher != nullptr) {
		preOrderWalk2(theReturn, node->nodeHigher);
	}
}

template<typename T>
inline void AVLTree<T>::inOrderWalk2(std::vector<T>& theReturn, Node<T> * node)
{
	if (node->nodeLower != nullptr) {
		inOrderWalk2(theReturn, node->nodeLower);
	}

	theReturn.push_back(node->data);

	if (node->nodeHigher != nullptr) {
		inOrderWalk2(theReturn, node->nodeHigher);
	}
}

template<typename T>
inline void AVLTree<T>::postOrderWalk2(std::vector<T>& theReturn, Node<T> * node)
{
	if (node->nodeLower != nullptr) {
		postOrderWalk2(theReturn, node->nodeLower);
	}
	if (node->nodeHigher != nullptr) {
		postOrderWalk2(theReturn, node->nodeHigher);
	}
	theReturn.push_back(node->data);
}

template<typename T>
inline int AVLTree<T>::difference(Node<T> * node)
{
	int theReturn = 0;
	int LDepth = 0;
	int HDepth = 0;
	if (node->nodeHigher != nullptr) {
		HDepth = (int)getTreeHeight(node->nodeHigher);
	}
	if (node->nodeLower != nullptr) {
		LDepth = (int)getTreeHeight(node->nodeLower);
	}
	theReturn = LDepth - HDepth;

	return theReturn;
}

template<typename T>
inline Node<T>* AVLTree<T>::LLRotation(Node<T> * node)
{
	Node<T> *temp;
	temp = node->nodeLower;
	node->nodeLower = temp->nodeHigher;
	temp->nodeHigher = node;
	return temp;
}

template<typename T>
inline Node<T>* AVLTree<T>::RRRotation(Node<T> * node)
{
	Node<T>* temp;
	temp = node->nodeHigher;
	node->nodeHigher = temp->nodeLower;
	temp->nodeLower = node;
	return temp;
}

template<typename T>
inline Node<T>* AVLTree<T>::LRRotation(Node<T> * node)
{
	Node<T> *temp;
	temp = node->nodeLower;
	node->nodeLower = RRRotation(temp);
	return LLRotation(node);
}

template<typename T>
inline Node<T>* AVLTree<T>::RLRotation(Node<T> * node)
{
	Node<T> *temp;
	temp = node->nodeHigher;
	node->nodeHigher = LLRotation(temp);
	return RRRotation(node);
}

template<typename T>
inline std::vector<T> AVLTree<T>::preOrderWalk()
{
	std::vector<T> theReturn;
	if (root != nullptr) {
		preOrderWalk2(theReturn, root);
	}
	else {
		std::cout << "error no Data" << std::endl;
	}
	return theReturn;
}

template<typename T>
inline std::vector<T> AVLTree<T>::inOrderWalk()
{
	std::vector<T> theReturn;

	if (root != nullptr) {
		inOrderWalk2(theReturn, root);
	}
	else {
		std::cout << "error no Data" << std::endl;
	}

	return theReturn;
}

template<typename T>
inline std::vector<T> AVLTree<T>::postOrderWalk()
{
	std::vector<T> theReturn;

	if (root != nullptr) {
		postOrderWalk2(theReturn, root);
	}
	else {
		std::cout << "error no Data" << std::endl;
	}

	return theReturn;
}

template<typename T>
size_t AVLTree<T>::getTreeHeight(Node<T> * node)
{
	size_t theReturn = 0;
	size_t rDepth = 0;
	size_t lDepth = 0;
	if (node == nullptr)
	{
		if (this->root == nullptr) {
			T *error = new T();
			std::cout << "error no Data" << std::endl;
			return *error;
		}
		node = root;
	}
	if (node->nodeHigher != nullptr) {
		rDepth = getTreeHeight(node->nodeHigher);
	}
	if (node->nodeLower != nullptr) {
		lDepth = getTreeHeight(node->nodeLower);
	}

	if (rDepth > lDepth) {
		theReturn = (rDepth + 1);
	}
	else {
		theReturn = (lDepth + 1);
	}
	return theReturn;
}

#pragma region other


/*template <typename T>
std::string AVLTree<T>::ToGraphviz(Node* node) // Member function of the AVLTree class
{
std::string toReturn = "";
if(node == root) // root is a pointer to the root node of the tree
{
std::string listOfNodes;
std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
toReturn += std::string("digraph {\n");
size_t id = 0;
ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
toReturn += listOfNodes;
toReturn += listOfConnections;
toReturn += std::string("}");
}
return std::move(toReturn);
}
template<typename T>
void AVLTree<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
size_t myID = uniqueID;
listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->data) + std::string("\"];\n");
if(toWorkWith->nodeLower)
{
listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->nodeLower, ++uniqueID);
}
else
{
listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
}
if(toWorkWith->nodeHigher)
{
listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->nodeHigher, ++uniqueID);
}
else
{
listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
}
}*/
#pragma endregion

template<typename T>
inline Node<T>::Node()
{
	nodeHigher = nullptr;
	nodeLower = nullptr;
}

template<typename T>
inline Node<T>::Node(T element)
{
	nodeHigher = nullptr;
	nodeLower = nullptr;
	data = element;
}