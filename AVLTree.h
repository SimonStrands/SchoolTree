#include <vector>

template <typename T>
class AVLTree {
public:
	AVLTree();
	AVLTree(T element);
	void insert(T element);
	void remove(T element);
	bool find(T element);
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	size_t getTreeHeight();
	T getMin();
	T getMax();

private:
	//class Node {
	//private:
	//	Node *nodeHigher;
	//	Node *nodeLower;
	//	T data;
	//public:
	//	Node(T data);
	//};
	T data;
	AVLTree * nodeHigher;
	AVLTree * nodeLower;
};

template<typename T>
inline AVLTree<T>::AVLTree()
{
	data = NULL;
	nodeHigher = nullptr;
	nodeLower = nullptr;
}

template<typename T>
inline AVLTree<T>::AVLTree(T element)
{
	this->data = element;
}

template<typename T>
inline void AVLTree<T>::insert(T element)
{
	if (data == NULL) {
		data = element;
	}
	else {
		if (data < element) {
			if (nodeHigher == nullptr) {
				nodeHigher = new AVLTree<T>(element);
			}
			else {
				nodeHigher->insert(element);
			}
		}
		else if (data > element) {
			if (nodeLower == nullptr) {
				nodeLower = new AVLTree<T>(element);
			}
			else {
				nodeLower->insert(element);
			}
			
		}
	}
}

template<typename T>
inline bool AVLTree<T>::find(T element)
{
	bool theReturn = false;
	if (this->data == element) {
		theReturn = true;
	}
	else {
		if (data < element && nodeHigher != nullptr) {
			theReturn = nodeHigher.find(element);
		}
		else if (data > element && nodeLower != nullptr) {
			theReturn = nodeLower.find(element);
		}
	}
	return theReturn;
}

template<typename T>
inline T AVLTree<T>::getMin()
{
	if (nodeLower != nullptr) {

	}
	return T();
}

template<typename T>
inline T AVLTree<T>::getMax()
{
	return T();
}



#pragma region other
/*std::string ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if(root) // root is a pointer to the root node of the tree
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

void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if(toWorkWith->leftChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->leftChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
			
	if(toWorkWith->rightChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->rightChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}*/
#pragma endregion

