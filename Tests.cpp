#include "TestAVLTree.hpp"
#include <string>
#include <iostream>
#include "AVLTree.h"
//#include "AVLNode.h"

bool existInArray(int *arr, int nrOf, int element) {
	bool theReturn = false;
	for (int i = 0; i < nrOf && !theReturn; i++) {
		if (arr[i] == element) {
			theReturn = true;
		}
	}
	return theReturn;
}

int main()
{
   if(UnitTests::AVLTREE::AVLTreeUnitTests())
    {
        std::cout << "\nAll Unit Tests passed." << std::endl;
    }
    else
    {
        std::cout << "\nUnit tests failed on one or more tests." << std::endl;
        std::cout << "Please note that all tests must pass for your submission to be assessed." << std::endl;
    }
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	AVLTree<int> trad;
	const int MAX = 50;
	int arr[MAX];
	for (int i = 0; i < MAX; i++) {
		int x = rand() % MAX + 50;
		while (existInArray(arr, i, x)) {
			x = rand() % MAX;
		}
		trad.insert(x);
		arr[i] = x;
		std::cout << "write" << std::endl;
		trad.writeTree();
	}

	
	std::cout << "stop" << std::endl;
	for (int i = 0; i < MAX; i++) {
		std::cout << arr[i] << std::endl;
		trad.remove(arr[i]);
		std::cout << "write" << std::endl;
		trad.writeTree();
	}*/

	
	
	getchar();
	return 0;
    
}