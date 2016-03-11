/*
* The MIT License (MIT)
* Copyright (c) 2016 Ethan Gaebel
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial 
* portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "avl_tree.h"
#include <cassert>

int main() {
	
	using std::string;
	using std::cout;
	using std::endl;

	AVLTree<int> avl;
	avl.insert(17);
	assert(avl.size() == 1);
	cout << "added 17" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(22);
	assert(avl.size() == 2);
	cout << "added 22" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(33);
	assert(avl.size() == 3);
	cout << "added 33" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(7);
	assert(avl.size() == 4);
	cout << "added 7" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(2);
	assert(avl.size() == 5);
	cout << "added 2" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(-378);
	assert(avl.size() == 6);
	cout << "added -378" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(444);
	assert(avl.size() == 7);
	cout << "added 444" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(333);
	assert(avl.size() == 8);
	cout << "added 333" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(2000);
	assert(avl.size() == 9);
	cout << "added 2000" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.insert(-888);
	assert(avl.size() == 10);
	cout << "added -888" << endl;
	cout << avl.inOrderTraversal() << endl;
cout << "0---------------------------------------------------------------------0\n";
	avl.remove(17);
	assert(avl.size() == 9);
	cout << avl.inOrderTraversal() << endl;
	cout << "removed 17\n\n";
	avl.remove(15);
	assert(avl.size() == 9);
	cout << "removed 15 (or rather...I didn't!)\n" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(22);
	assert(avl.size() == 8);
	cout << "removed 22" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(2000);
	assert(avl.size() == 7);
	cout << "removed 2000" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(2);
	assert(avl.size() == 6);
	cout << "removed 2" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(-888);
	assert(avl.size() == 5);
	cout << "removed -888" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(333);
	assert(avl.size() == 4);
	cout << "removed 333" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(444);
	assert(avl.size() == 3);
	cout << "removed 444" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(7);
	assert(avl.size() == 2);
	cout << "removed 7" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(-378);
	assert(avl.size() == 1);
	cout << "removed -378" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(33);
	assert(avl.size() == 0);
	cout << "removed 33" << endl;
	cout << avl.inOrderTraversal() << endl;
	avl.remove(22);
	assert(avl.size() == 0);
	cout << "removed 22 (or rather..I DIDN't!" << endl;
	cout << avl.inOrderTraversal() << endl;

	cout << "--------------REGULAR-ISH ADD-REMOVE TESTS DONE--------------\nBEGIN AVL-ISH TESTS!\n";
	cout << "SINGLE ROTATION!\n";
	avl.insert(5);
	avl.insert(-17);
	avl.insert(10);
	avl.insert(-25);
	avl.insert(-15);
	cout << avl.inOrderTraversal() << endl;
	avl.remove(10);
	cout << avl.inOrderTraversal() << endl;

	cout << "\n\nDOUBLE ROTATION TESTS----------------\n";
	avl.insert(3);
	cout << "inserted 3\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(2);
	cout << "inserted 2\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(1);
	cout << "inserted 1\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(4);
	cout << "inserted 4\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(5);
	cout << "inserted 5\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(6);
	cout << "inserted 6\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(7);
	cout << "inserted 7\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(16);
	cout << "inserted 16\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(15);
	cout << "inserted 15\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(14);
	cout << "inserted 14\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(13);
	cout << "inserted 13\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(12);
	cout << "inserted 12\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(11);
	cout << "inserted 11\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(10);
	cout << "inserted 10\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(8);
	cout << "inserted 8\n";
	cout << avl.inOrderTraversal() << endl;
	avl.insert(9);
	cout << "inserted 9\n";
	cout << avl.inOrderTraversal() << endl;

	cout << "\n\n---------------------Find tests--------------------------\n";
	cout << avl.inOrderTraversal() << endl;
	assert(avl.find(4) != NULL);
	assert(avl.find(8) != NULL);
	assert(avl.find(222) == NULL);
	assert(avl.find(333) == NULL);
	assert(avl.find(10) != NULL);
	assert(avl.find(9) != NULL);
	assert(avl.find(6) != NULL);
	assert(avl.find(7) != NULL);
	assert(avl.find(16) != NULL);
	assert(avl.find(11) != NULL);
	assert(avl.find(12) != NULL);
	assert(avl.find(15) != NULL);
	assert(avl.find(13) != NULL);
	assert(avl.find(14) != NULL);

	cout << "\n\n---------------------------Clear tests----------------------\n";
	avl.clear();
	avl.inOrderTraversal();
	assert(avl.size() == 0);


	return 0;
}
