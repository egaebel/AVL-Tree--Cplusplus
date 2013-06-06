/* Implementation of a basic self-balancing AVL Tree */
#ifndef AVL_TREE_
#define AVL_TREE_

#include <cmath>
#include <sstream>
#include <string>
#include <iostream>

using std::stringstream;
using std::string;

//Forward declaration of AVLTree
template<class T>
class AVLTree;

//The maximum imbalance that is allowed in the AVL Tree.
const static int MAX_IMBAL = 2;

/* AVL Node class, holds data and references to adjacent nodes. */
template<class T>
class AVLNode {

	public:
		friend class AVLTree<T>;
		AVLNode();
		AVLNode(const T & newData);
		AVLNode(const T & element, int theHeight);
		~AVLNode();
	private:
		AVLNode<T> * left;
		AVLNode<T> * right;
		const T & data;
		int leftHeight;
		int rightHeight;
		int height();
};

/* AVL Tree class, holds all of the functions etc for the AVL Tree. */
template<class T>
class AVLTree {

	public:
		friend class AVLNode<T>;
		AVLTree();
		AVLTree(const T & element);
		~AVLTree();
		void insert(const T & element);
		bool remove(const T & element);
		const T * find(const T & element);
		const T * findMax();
		const T * findMin();
		int size();
		const string inOrderTraversal();
		void clear();

	private:
		AVLNode<T> * root;
		int treeSize;

		void delete_traversal(AVLNode<T> * subRoot);
		AVLNode<T> * insert(AVLNode<T> * subRoot, const T & element);
		AVLNode<T> * remove(AVLNode<T> * subRoot, const T & element, bool * val);
		AVLNode<T> * balance(AVLNode<T> * subRoot);
		AVLNode<T> * singleRotateRightChild(AVLNode<T> * subRoot);
		AVLNode<T> * singleRotateLeftChild(AVLNode<T> * subRoot);
		const T * find(AVLNode<T> * subRoot, const T & element);
		AVLNode<T> * findMin(AVLNode<T> * subRoot);
		AVLNode<T> * findMax(AVLNode<T> * subRoot);
		void inOrderTraversal(AVLNode<T> * subRoot, string & output, int depth);
};

//~AVLTree Functions--------------------------------------------------------------------
/* AVLTree constructor, sets root to NULL. */
template<class T>
AVLTree<T>::AVLTree() {

	root = NULL;
	treeSize = 0;
}

/* AVLTree constructor, sets root to element. */
template<class T>
AVLTree<T>::AVLTree(const T & element) {

	root = new AVLNode<T>(element);
	treeSize = 1;
}

/* AVLTree destructor, deletes all of the nodes left in the tree. */
template<class T>
AVLTree<T>::~AVLTree() {

	delete_traversal(root);
}

/* Deletes all the nodes in the subTree that has subRoot as the root. */
template<class T>
void AVLTree<T>::delete_traversal(AVLNode<T> * subRoot) {

	if (!subRoot)
		return;

	delete_traversal(subRoot->left);
	delete_traversal(subRoot->right);
	delete subRoot;
}

/* Inserts the passed element into the AVLTree. */
template<class T>
void AVLTree<T>::insert(const T& element) {

	root = insert(root, element);
	treeSize++;
}

/* Helper method for inserting the passed element into the AVLTree. */
template<class T>
AVLNode<T> * AVLTree<T>::insert(AVLNode<T> * subRoot, const T & element) {

	AVLNode<T> * returnValue = subRoot;

	if (!subRoot) {
	
		returnValue = new AVLNode<T>(element);
	}
	else if (element >= subRoot->data) {
	
		subRoot->right = insert(subRoot->right, element);
		subRoot->rightHeight++;
	}
	else {
	
		subRoot->left = insert(subRoot->left, element);
		subRoot->leftHeight++;
	}

	return balance(returnValue);
}

/* Removes the passed element from the AVLTree (if it is present in the AVLTree). */
template<class T>
bool AVLTree<T>::remove(const T & element) {

	if (!root) {
	
		return false;
	}
	else {

		bool val = true;
		root = remove(root, element, &val);
		return val;
	}
}

/* Helper method to remove the passed element from the AVLTree (if it is present). */
template<class T>
AVLNode<T> * AVLTree<T>::remove(AVLNode<T> * subRoot, const T & element, bool * val) {

	AVLNode<T> * returnValue;

	if (!subRoot) {

		*val = false;
		returnValue = NULL;
	}
	else if (subRoot->data == element){

		treeSize--;

		//No children of the found node, remove it.
		if (!subRoot->left && !subRoot->right) {

			delete subRoot;
			returnValue = NULL;
		}
		//Two children of the found node. Remove it, complexly.
		else if (subRoot->left && subRoot->right) {

			AVLNode<T> * maxLeft = findMax(subRoot->left);
			AVLNode<T> * newSubRoot = new AVLNode<T>(maxLeft->data);
			newSubRoot->left = remove(subRoot->left, maxLeft->data, val);
			newSubRoot->right = subRoot->right;
			newSubRoot->leftHeight = subRoot->leftHeight;
			newSubRoot->rightHeight = subRoot->rightHeight;
			//Subtract from leftHeight to account for removal call above.
			newSubRoot->leftHeight--;
			//Increase the treeSize to make up for the remove called above.
			treeSize++;

			delete subRoot;
			returnValue = newSubRoot;
		}
		//One child of the found node. Remove it, and promote child.
		else {

			AVLNode<T> * temp = (subRoot->right) ? subRoot->right : subRoot->left;

			delete subRoot;
			returnValue = temp;
		}
	}
	else if (element >= subRoot->data) {

		subRoot->right = remove(subRoot->right, element, val);
		//If *val is true, then removal succeeded. Subtract from this node's rightHeight.
		if (*val)
			subRoot->rightHeight--;
		returnValue = subRoot;
	}
	else {

		subRoot->left = remove(subRoot->left, element, val);
		//If *val is true, then removal succeeded. Subtract from this node's leftHeight.
		if (*val)
			subRoot->leftHeight--;
		returnValue = subRoot;
	}

	return balance(returnValue);
}

/* Check the balance of the AVLTree that has subRoot as its root. */
template<class T>
AVLNode<T> * AVLTree<T>::balance(AVLNode<T> * subRoot) {

	AVLNode<T> * returnValue = subRoot;

	if (!subRoot) {

		returnValue = subRoot;
	}
	//If the left subTree is too large.
	else if (subRoot->leftHeight - subRoot->rightHeight > MAX_IMBAL) {

		//Single rotation is necessary if the left-subtree is larger than the right.
		if(subRoot->left->leftHeight >= subRoot->left->rightHeight) {

			returnValue = singleRotateLeftChild(subRoot);
		}
		//Double rotation is necessary if the right-subtree is larger than the left.
		else {

			subRoot->left = singleRotateRightChild(subRoot->left);
			returnValue = singleRotateLeftChild(subRoot);
		}
	}
	//If the right subTree is too large.
	else if (subRoot->rightHeight - subRoot->leftHeight > MAX_IMBAL) {

		//Single rotation is necessary if the right-subtree is larger than the left.
		if (subRoot->right->rightHeight >= subRoot->right->leftHeight) {

			returnValue = singleRotateRightChild(subRoot);
		}
		//Double rotation is necessary if the left sub-tree is larger than the right.
		else {

			subRoot->right = singleRotateLeftChild(subRoot->right);
			returnValue = singleRotateRightChild(subRoot);
		}
	}

	return returnValue;
}

/* Rotate the left subTree over to the root. */
template<class T>
AVLNode<T> * AVLTree<T>::singleRotateLeftChild(AVLNode<T> * subRoot) {

	AVLNode<T> * temp = subRoot->left;
	subRoot->left = temp->right;
	subRoot->leftHeight = temp->rightHeight;
	temp->right = subRoot;
	temp->rightHeight = subRoot->height() + 1;

	return temp;
}

/* Rotate the right subTree over to the root. */
template<class T>
AVLNode<T> * AVLTree<T>::singleRotateRightChild(AVLNode<T> * subRoot) {

	AVLNode<T> * temp = subRoot->right;
	subRoot->right = temp->left;
	subRoot->rightHeight = temp->leftHeight;
	temp->left = subRoot;
	temp->leftHeight = subRoot->height() + 1;

	return temp;
}

/* Searches the AVLTree for the passed in element.
 * Returns NULL if the element cannot be found.
 */
template<class T>
const T * AVLTree<T>::find(const T & element) {

	return find(root, element);
}

/* Helper method for finding the passed in element in the subTree with subRoot as the root. */
template<class T>
const T * AVLTree<T>::find(AVLNode<T> * subRoot, const T & element) {

	if (!subRoot)
		return NULL;
	else if (subRoot->data == element)
		return &subRoot->data;
	else if (subRoot->data > element)
		return find(subRoot->left, element);
	else 
		return find(subRoot->right, element);
}

/* Finds the minimum element in the tree. */
template<class T>
const T * AVLTree<T>::findMin() {

	if (!root)
		return NULL;
	return findMin(root)->data;
}

/* Helper function for finding the minimum element in the tree. */
template<class T>
AVLNode<T> * AVLTree<T>::findMin(AVLNode<T> * subRoot) {

	if (subRoot->left)
		return findMin(subRoot->left);
	else
		return subRoot;
}

/* Finds the maximum element in the AVLTree. */
template<class T>
const T * AVLTree<T>::findMax() {

	if (!root)
		return NULL;
	return findMax(root)->data;
}

/* Helper function for finding the maximum element in the tree. */
template<class T>
AVLNode<T> * AVLTree<T>::findMax(AVLNode<T> * subRoot) {

	if (subRoot->right)
		return findMax(subRoot->right);
	else
		return subRoot;
}

/* Performs an inOrderTraversal of the AVLTree. */
template<class T>
const string AVLTree<T>::inOrderTraversal() {

	string output;

	if (root)
		inOrderTraversal(root, output, 0);
	else
		output += "--|";

	return output;
}

/* Helper function for inOrderTraversal. Performs an inOrderTraversal of the subTree with subRoot as its root. */
template<class T>
void AVLTree<T>::inOrderTraversal(AVLNode<T> * subRoot, string & output, int depth) {

	stringstream ss;

	if (!subRoot)
		return;

	if (subRoot->left)
		inOrderTraversal(subRoot->right, output, depth + 1);

	for (int i = 0; i < depth; i++)
		output += "----";
	output += "|";
	ss << subRoot->data;// << "|||leftHeight = " << subRoot->leftHeight << "|||rightHeight = " << subRoot->rightHeight << "|||addr: " << subRoot;
	output += ss.str();
	output += "\n";
	
	if (subRoot->right)
		inOrderTraversal(subRoot->left, output, depth + 1);
}

/* Gets the size of the AVLTree. */
template<class T>
int AVLTree<T>::size() {

	return treeSize;
}

/* Empties out the AVLTree. */
template<class T>
void AVLTree<T>::clear() {

	delete_traversal(root);
	root = NULL;
	treeSize = 0;
}

//~AVLNode functions---------------------------------------------------------------------
/* Constructor for AVLNode, sets the node's data to element. */
template<class T>
AVLNode<T>::AVLNode(const T & element) : data(element) {

	leftHeight = 0;
	rightHeight = 0;
	left = NULL;
	right = NULL;
}

/* Destructor for AVLNode. */
template<class T>
AVLNode<T>::~AVLNode() {

	left = NULL;
	right = NULL;
}

/* Gets the total height of the node. Adds together leftHeight & rightHeight. */
template<class T>
int AVLNode<T>::height() {

	return leftHeight + rightHeight;
}

#endif