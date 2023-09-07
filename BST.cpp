#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}

//function b
bool BST::deepestNodes() {
	if (root == NULL) return false;
	else {
		int level = 1;
		int max = 1;
		level = depth(root, level, max);
		cout << "\nRoot considered as Level 1";
		cout << "\nDeepest Node at Level " << level << ":\n";
		int curr = 1;
		deepestNodes2(root, level, curr);
	}
	return true;
}

void BST::deepestNodes2(BTNode* cur, int level, int curr) {
	if (cur == NULL) {
		curr--;
		return;
	}
	if (curr == level) {
		cur->item.print(cout);
		return;
	}
	deepestNodes2(cur->left, level, curr + 1);
	deepestNodes2(cur->right, level, curr + 1);
}

int BST::depth(BTNode* cur, int level, int& max) {
	if (cur == NULL) {
		return level--;
	}
	if (level > max) 
		max = level;	

	// Recursion to find the maximum depth
	depth(cur->left, level + 1, max);
	depth(cur->right, level + 1, max);
	return max;
}

// function c
bool BST::display(int order, int source) {
	if (root == NULL) return false;
	if (source == 1) {			//Print to Display Screen
		if (order == 1) {		// Ascending 
			cout << "\nDisplaying Student Details in Ascending Order:\n";
			inOrderPrint();
		}
		else if (order == 2) {	//Descending
			cout << "\nDisplaying Student Details in Descending Order:\n";
			Reverse_inOrderPrint();
		}
	}
	else if (source == 2) {		//Print to File
		if (order == 1) {		//Ascending
			file_inOrderPrint();
			cout << "\nStudent Details has been saved to \"student-info.txt\" File via Ascending Order. \n";
		}
		else if (order == 2) {	//Descending
			file_Reverse_inOrderPrint();
			cout << "\nStudent Details has been saved to \"student-info.txt\" File via Descending Order. \n";
		}
	}
	return true;
}

void BST::Reverse_inOrderPrint() {
	if (root == NULL) return;
	else Reverse_inOrderPrint2(root);
	cout << endl;
}

void BST::Reverse_inOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	Reverse_inOrderPrint2(cur->right);
	cur->item.print(cout);
	Reverse_inOrderPrint2(cur->left);
}

void BST::file_inOrderPrint() {
	if (root == NULL) return;
	else {
		ofstream out;
		out.open("student-info.txt");
		file_inOrderPrint2(root, out);
		out.close();
	}
	cout << endl;
}

void BST::file_inOrderPrint2(BTNode* cur, ostream& out) {
	if (cur == NULL) return;
	file_inOrderPrint2(cur->left, out);
	cur->item.print(out);
	file_inOrderPrint2(cur->right, out);
}

void BST::file_Reverse_inOrderPrint() {
	if (root == NULL) return;
	else {
		ofstream out;
		out.open("student-info.txt");
		file_Reverse_inOrderPrint2(root, out);
		out.close();
	}
	cout << endl;
}

void BST::file_Reverse_inOrderPrint2(BTNode* cur, ostream& out) {
	if (cur == NULL) return;
	file_Reverse_inOrderPrint2(cur->right, out);
	cur->item.print(out);
	file_Reverse_inOrderPrint2(cur->left, out);
}

//function d
bool BST::CloneSubtree(BST t1, type item) {
	BTNode* SNode = NULL;
	Student subtree;
	if (t1.size() == 0) {
		cout << "\n\nAlert! The tree is empty.\n";
		return false;
	}
	if (!t1.searchNode(SNode, item)) {
		cout << "\n\nUnable to find requested Node!\n";					//Searchs for the node
		return false;
	}
	else insertSub(SNode, subtree);										//Inserts the subtree to a new tree
	return true;
}

bool BST::searchNode(BTNode*& SNode, type item) {
	if (root == NULL) return false;
	searchNode2(root, item, SNode);
	if (SNode != NULL) {
		return true;
	}
	return false;
}

void BST::searchNode2(BTNode* cur, type item, BTNode*& SNode) {
	if (cur == NULL) return;
	if (item.id == cur->item.id) {	//If matching, then node is found
		SNode = cur;
		return;
	}
	searchNode2(cur->right, item, SNode);
	searchNode2(cur->left, item, SNode);
	return;

}

void BST::insertSub(BTNode* cur, Student subtree) {
	if (cur == NULL) return;

	strcpy_s(subtree.name, sizeof(subtree.name), cur->item.name);
	subtree.id = cur->item.id;
	strcpy_s(subtree.address, sizeof(subtree.address), cur->item.address);
	strcpy_s(subtree.DOB, sizeof(subtree.DOB), cur->item.DOB);
	strcpy_s(subtree.phone_no, sizeof(subtree.phone_no), cur->item.phone_no);
	strcpy_s(subtree.course, sizeof(subtree.course), cur->item.course);
	subtree.cgpa = cur->item.cgpa;
	insert(subtree);

	insertSub(cur->left, subtree);
	insertSub(cur->right, subtree);
}

// function e 
bool BST::printLevelNodes() {
	if (root == nullptr) {
		return false;
	}

	Queue q;
	q.enqueue(root);
	int level = 1; // Initialize the level counter.

	while (!q.empty()) {
		int nodesInCurrentLevel = q.size(); // Get the number of nodes in the current level.
		cout << "Level " << level << " nodes: ";

		for (int i = 0; i < nodesInCurrentLevel; i++) {
			BTNode* cur;
			q.dequeue(cur);

			// Print the student ID directly
			cout << cur->item.id << " ";

			if (cur->left != nullptr) {
				q.enqueue(cur->left);
			}
			if (cur->right != nullptr) {
				q.enqueue(cur->right);
			}
		}

		cout << endl;
		level++; // Move to the next level.
	}

	return true;
}

// function f
bool BST::printPath() {
	if (root == nullptr) {
		return false;
	}

	cout << "Below are all the external paths for the tree:" << endl;
	printExternalPaths(root, "");

	return true;
}
void BST::printExternalPaths(BTNode* node, string path) {
	if (node == nullptr) {
		return;
	}

	// Append the student ID to the current path
	path += to_string(node->item.id) + " ";

	// If it's a leaf node (external node), print the path
	if (node->left == nullptr && node->right == nullptr) {
		cout << path << endl;
	}
	else {
		// Recursively traverse the left and right subtrees
		printExternalPaths(node->left, path);
		printExternalPaths(node->right, path);
	}
}

// -------------------------given-------------------------------------

bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}
