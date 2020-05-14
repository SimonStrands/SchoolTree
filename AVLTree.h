#pragma once
#include <vector>
#include <iostream>
//test v.2
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
	
	
	void writeTree();
	
public:
	AVLTree();//done
	AVLTree(T element);//done
	
	void insert(T element);
	bool find(T element);
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	size_t getTreeHeight();
	T getMin();
	T getMax();
	void remove(T element);
	
private:
	void insert2(T element, Node<T> *node = nullptr);
	bool find2(T element, Node<T> *node = nullptr);
	void preOrderWalk2(std::vector<T> &theReturn, Node<T> *node);
	void inOrderWalk2(std::vector<T> &theReturn, Node<T> *node);
	void postOrderWalk2(std::vector<T> &theReturn, Node<T> *node);
	size_t getTreeHeight2(Node<T> *node = nullptr);
	T getMin2(Node<T> *node = nullptr);
	T getMax2(Node<T> *node = nullptr);
	void remove2(T element, Node<T> *&node);

private:
	bool isBalanced(Node<T>*& node);
	Node<T>* root;
	int difference(Node<T> *node);
	Node<T>* LLRotation(Node<T> *node);
	Node<T>* RRRotation(Node<T> *node);
	Node<T>* LRRotation(Node<T> *node);
	Node<T>* RLRotation(Node<T> *node);
	void writeTree2(Node<T>* node, int space);
	bool nodeNull(Node<T>* &node);
	Node<T>** findParent(T element, Node<T>*& node, bool &foundIt);
	Node<T>** findNode(T element, Node<T>*& node, bool &foundIt);
	Node<T>** getMinNode(Node<T> *node = nullptr);//done
	Node<T>** getMaxNode(Node<T> *node = nullptr);//done

	T getErsattare(Node<T> *node = nullptr);
	Node<T>** remove3(Node<T> *&node);
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
inline void AVLTree<T>::insert(T element)
{
	insert2(element, root);
}

template<typename T>
inline T AVLTree<T>::getMin()
{
	if (root == nullptr) {
		throw std::exception("Three is Empty");
	}
	
	return getMin2(root);
	
}

template<typename T>
inline T AVLTree<T>::getMax()
{
	if (root == nullptr) {
		throw std::exception("Three is Empty");
	}

	return getMax2(root);
}

template<typename T>
inline void AVLTree<T>::remove(T element)
{
	remove2(element, root);
}

template<typename T>
inline void AVLTree<T>::insert2(T element, Node<T> * node)
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
				insert2(element, node->nodeHigher);
			}
			else {
				node->nodeHigher = new Node<T>(element);
			}
		}
		else if (element < node->data) {
			if (node->nodeLower != nullptr) {
				insert2(element, node->nodeLower);
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
inline Node<T>** AVLTree<T>::remove3(Node<T>* &node)
{
	Node<T>** theReturn;

	if (node->nodeHigher != nullptr) {
		theReturn = remove3(node->nodeHigher);
	}
	else {
		theReturn = &node;
	}

	return theReturn;
}

template<typename T>
inline T AVLTree<T>::getErsattare(Node<T>* node)
{
	Node<T> *&ersattare = node;
	T theReturn;

	ersattare = *getMaxNode(node);
	theReturn = ersattare->data;

	return theReturn;
}

template<typename T>
inline void AVLTree<T>::remove2(T element, Node<T>*& node)
{
	if (root == nullptr) {
		return;
	}
	else {
		if (!nodeNull(node)) {

		}
		else {
			if (find2(element)) {
				bool foundNode = true;
				bool foundParent = true;

				//säker
				Node<T>*& deleteNode = *findNode(element, node, foundNode);

				
				//osäker
				Node<T>*Parent = *findParent(element, root, foundParent);

				if (deleteNode->nodeHigher == nullptr && deleteNode->nodeLower == nullptr) {
					if (foundParent && Parent != nullptr) {
				
						if (Parent->nodeHigher != nullptr && Parent->nodeHigher->data == element) {
							Parent->nodeHigher = nullptr;
						}
						else if (Parent->nodeLower != nullptr && Parent->nodeLower->data == element) {
							Parent->nodeLower = nullptr;
						}
					}
					delete deleteNode;
					deleteNode = nullptr;
				}
				else if (deleteNode->nodeHigher == nullptr && deleteNode->nodeLower != nullptr) {
					Node<T>* temp = deleteNode->nodeLower;
					delete deleteNode;
					deleteNode = temp;
				}
				else if (deleteNode->nodeHigher != nullptr && deleteNode->nodeLower == nullptr) {
					Node<T>* temp = deleteNode->nodeHigher;
					delete deleteNode;
					deleteNode = temp;
				}
				else if (deleteNode->nodeHigher != nullptr && deleteNode->nodeLower != nullptr) {
					
					Node<T>* ersattre = *remove3(deleteNode->nodeLower);
					bool foundErsattreParent;
					Node<T> *ersatterParent = *findParent(ersattre->data, node, foundErsattreParent);

					deleteNode->data = ersattre->data;
					if (ersattre->nodeLower != nullptr) {
						ersattre->data = ersattre->nodeLower->data;
						delete ersattre->nodeLower;
						ersattre->nodeLower = nullptr;

					}
					else if (foundErsattreParent) {
							if (ersatterParent->nodeHigher != nullptr && ersatterParent->nodeHigher->data == deleteNode->data) {
								ersatterParent->nodeHigher = nullptr;
							}
							else if (ersatterParent->nodeLower != nullptr && ersatterParent->nodeLower->data == deleteNode->data) {
								ersatterParent->nodeLower = nullptr;
							}
					}
				}
				isBalanced(root);
			}
			else {
				std::cout << "element doesn't exist" << std::endl;
			}
		}
	}
}


template<typename T>
inline bool AVLTree<T>::find(T element)
{
	return find2(element, root);
}



template<typename T>
inline Node<T>** AVLTree<T>::findParent(T element, Node<T>*& node, bool &foundIt)
{
	Node<T> **theReturn = nullptr;
	bool canReturn = false;
	if (node->data == element) {
		canReturn = true;
		theReturn = &node;//give it root so it doesnt give it nullptr and crash
		foundIt = false;
	}
	if (node->nodeHigher != nullptr && !canReturn) {
		if (node->nodeHigher->data == element) {
			theReturn = &node;
			canReturn = true;
		}
	}
	if (node->nodeLower != nullptr && !canReturn) {
		if (node->nodeLower->data == element) {
			theReturn = &node;
			canReturn = true;
		}
	}
	if(!canReturn) {
		if (element < node->data) {
			if (node->nodeLower != nullptr) {
				theReturn = findParent(element, node->nodeLower, foundIt);
			}
			else {
				std::cout << "error in findParent" << std::endl;
				theReturn = new Node<T>*();
				foundIt = false;
			}
		}
		else {
			if (node->nodeHigher != nullptr) {
				theReturn = findParent(element, node->nodeHigher, foundIt);
			}
			else {
				std::cout << "error in findParent" << std::endl;
				theReturn = new Node<T>*();
				foundIt = false;
			}
		}
	}


	return theReturn;
}

template<typename T>
inline Node<T>** AVLTree<T>::findNode(T element, Node<T>*& node, bool & foundIt)
{
	Node<T> **theReturn = nullptr;
	bool canReturn = false;
	if (node->data == element) {
		canReturn = true;
		theReturn = &node;//give it root so it doesnt give it nullptr and crash
		foundIt = false;
	}
	if (node->nodeHigher != nullptr && !canReturn) {
		if (node->nodeHigher->data == element) {
			theReturn = &node->nodeHigher;
			canReturn = true;
		}
	}
	if (node->nodeLower != nullptr && !canReturn) {
		if (node->nodeLower->data == element) {
			theReturn = &node->nodeLower;
			canReturn = true;
		}
	}
	if (!canReturn) {
		if (element < node->data) {
			if (node->nodeLower != nullptr) {
				theReturn = findNode(element, node->nodeLower, foundIt);
			}
			else {
				std::cout << "error in findNode" << std::endl;
				theReturn = new Node<T>*();
				foundIt = false;
			}
		}
		else {
			if (node->nodeHigher != nullptr) {
				theReturn = findNode(element, node->nodeHigher, foundIt);
			}
			else {
				std::cout << "error in findNode" << std::endl;
				theReturn = new Node<T>*();
				foundIt = false;
			}
		}
	}


	return theReturn;
}

template<typename T>
inline Node<T>** AVLTree<T>::getMinNode(Node<T>* node)
{
	Node<T>** theReturn;
	if (node->nodeLower != nullptr) {
		theReturn = getMinNode(node->nodeLower);
	}
	else {
		theReturn = &node;
	}
	return theReturn;
}

template<typename T>
inline Node<T>** AVLTree<T>::getMaxNode(Node<T>* node)
{
	Node<T>** theReturn;
	if (node->nodeHigher != nullptr) {
		theReturn = getMaxNode(node->nodeHigher);
	}
	else {
		theReturn = &node;
	}
	return theReturn;
}






template<typename T>
inline bool AVLTree<T>::isBalanced(Node<T>*& node)
{
	bool theReturn = true;
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
			theReturn = false;
			if (difference(node->nodeLower) > -1) {
				node = LLRotation(node);
				std::cout << "LL" << std::endl;
			}
			else {
				node = LRRotation(node);
				std::cout << "LR" << std::endl;
			}
		}
		else if (difference(node) < -1) {
			theReturn = false;
			if (difference(node->nodeHigher) > -1) {
				node = RLRotation(node);
				std::cout << "RL" << std::endl;
			}
			else {
				node = RRRotation(node);
				std::cout << "RR" << std::endl;
			}
		}
	}
	if (!theReturn) {
		this->isBalanced(node);
	}
	return theReturn;
}

template<typename T>
inline void AVLTree<T>::writeTree()
{
	writeTree2(root, 0);
}

template<typename T>
inline int AVLTree<T>::difference(Node<T> * node)
{
	int theReturn = 0;
	int LDepth = 0;
	int HDepth = 0;
	if (node->nodeHigher != nullptr) {
		HDepth = (int)getTreeHeight2(node->nodeHigher);
	}
	if (node->nodeLower != nullptr) {
		LDepth = (int)getTreeHeight2(node->nodeLower);
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
size_t AVLTree<T>::getTreeHeight()
{
	size_t theReturn = (int)getTreeHeight2(root) - 1;
	
	return theReturn;
}

template<typename T>
inline size_t AVLTree<T>::getTreeHeight2(Node<T>* node)
{
	size_t theReturn = 0;
	size_t rDepth = 0;
	size_t lDepth = 0;
	if (node == nullptr)
	{
		if (this->root == nullptr) {
			return theReturn;
		}
		node = root;
	}
	if (node->nodeHigher != nullptr) {
		rDepth = getTreeHeight2(node->nodeHigher);
	}
	if (node->nodeLower != nullptr) {
		lDepth = getTreeHeight2(node->nodeLower);
	}

	if (rDepth > lDepth) {
		theReturn = (rDepth + 1);
	}
	else {
		theReturn = (lDepth + 1);
	}
	return theReturn;
}

#pragma region secondFunctions

template<typename T>
inline T AVLTree<T>::getMin2(Node<T> * node)
{
	T theReturn;
	if (!nodeNull(node)) {
		T *error = new T();
		return *error;
	}
	if (node->nodeLower != nullptr) {
		theReturn = getMin2(node->nodeLower);
	}
	else {
		theReturn = node->data;
	}
	return theReturn;
}

template<typename T>
inline T AVLTree<T>::getMax2(Node<T> * node)
{
	T theReturn;
	if (!nodeNull(node)) {
		T *error = new T();
		return *error;
	}
	if (node->nodeHigher != nullptr) {
		theReturn = getMax2(node->nodeHigher);
	}
	else {
		theReturn = node->data;
	}
	return theReturn;
}



template<typename T>
inline bool AVLTree<T>::find2(T element, Node<T> * node)
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
				theReturn = find2(element, node->nodeHigher);
			}
			else {
				theReturn = false;
			}
		}
		else if (element < node->data) {
			if (node->nodeLower != nullptr) {
				theReturn = find2(element, node->nodeLower);
			}
			else {
				theReturn = false;
			}
		}
	}
	return theReturn;
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

#pragma endregion

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


