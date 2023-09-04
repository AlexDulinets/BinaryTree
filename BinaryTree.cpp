#include <iostream>

#include "BinaryTree.h"
using namespace std; 


Tree::Tree() 
{ 
	root = nullptr;
}


Tree::node* Tree::CreateLeaf(int key)
{
	node* n = new node; 
	n->key = key;
	n->left = nullptr;
	n->right = nullptr;
	n->parent = nullptr;

	return n;
}


//добавление эл.
void Tree::AddLeaf(int key)
{
	AddLeafPrivate(key, root);
}

void Tree::AddLeafPrivate(int key, node* Ptr) 
{
	if (root == nullptr) root = CreateLeaf(key);
	//слева
	else if (key < Ptr->key) {
		if (Ptr->left != nullptr) 
			AddLeafPrivate(key, Ptr->left);
		else {
			Ptr->left = CreateLeaf(key);
			Ptr->left->parent = Ptr;
		}
	}
	//справа
	else if (key > Ptr->key) {
		if (Ptr->right != nullptr) 
			AddLeafPrivate(key, Ptr->right);
		else {
			Ptr->right = CreateLeaf(key);
			Ptr->right->parent = Ptr;
		}
	}
	else cout << "#Key " << key << " already exists in this tree\n";
}


void Tree::PrintInOrder()
{
	PrintInOrderPrivate(root);
}

void Tree::PrintInOrderPrivate(node* Ptr)
{
	if (root != nullptr)
	{
		if (Ptr->left != nullptr) PrintInOrderPrivate(Ptr->left);
		wcout << Ptr->key << " ";
		if (Ptr->right != nullptr) PrintInOrderPrivate(Ptr->right);
	}
	else wcout << "#The Tree is empty.\n";
}


void Tree::PrintPreOrder()
{
	PrintPreOrderPrivate(root);
}

void Tree::PrintPreOrderPrivate(node* Ptr)
{
	if (root != nullptr)
	{
		wcout << Ptr->key << " ";
		if (Ptr->left != nullptr) PrintPreOrderPrivate(Ptr->left);
		if (Ptr->right != nullptr) PrintPreOrderPrivate(Ptr->right);
		v1.push_back(Ptr->key);
	}
	else wcout << "#The Tree is empty.\n";
}


void Tree::PrintPostOrder()
{
	PrintPostOrderPrivate(root);
}

void Tree::PrintPostOrderPrivate(node* Ptr)
{
	if (root != nullptr)
	{
		if (Ptr->left != nullptr) PrintPostOrderPrivate(Ptr->left);
		if (Ptr->right != nullptr) PrintPostOrderPrivate(Ptr->right);
		wcout << Ptr->key << " ";

	}
	else wcout << "#The Tree is empty.\n";
}


Tree::node* Tree::ReturnNode(int key)
{
	return ReturnNodePrivate(key, root);
}

Tree::node* Tree::ReturnNodePrivate(int key, node* Ptr)
{
	if (Ptr != nullptr)
	{
		if (Ptr->key == key) return Ptr;
		else 
		{
			if (key < Ptr->key) return ReturnNodePrivate(key, Ptr->left);
			else return ReturnNodePrivate(key, Ptr->right);
		}
	}
	else return nullptr;
}


int Tree::ReturnRootKey() 
{
	if (root != nullptr) return root->key;
	else return -1000;
}


void Tree::PrintChildren(int key)
{
	node* Ptr = ReturnNode(key);
	if (Ptr != nullptr)
	{
		wcout << "Parent Node = " << Ptr->key << endl;
		if (Ptr->left == nullptr) wcout << "Left Child = nullptr.\n";
		else wcout << "Left Child = " << Ptr->left->key << endl;
		if (Ptr->right == nullptr) wcout << "Right Child = nullptr.\n";
		else wcout << "Right Child = " << Ptr->right->key << endl;
	}
	else wcout << "#Key " << key << "is not in the tree.\n"; 
}


int Tree::findSmallest()
{
	return findSmallestPrivate(root);
}

int Tree::findSmallestPrivate(node* Ptr) 
{
	if (root == nullptr)
	{
		wcout << "#The Three is empty.\n";
		return -1000;
	}
	if (Ptr->left != nullptr) return findSmallestPrivate(Ptr->left);
	else return Ptr->key;
}


void Tree::RemoveNode(int key)
{
	RemoveNodePrivate(key, root);
}

void Tree::RemoveNodePrivate(int key, node* parent) 
{
	if (root != nullptr)
	{
		if (root->key == key) RemoveRootMatch();
		else
		{
			if (key < parent->key && parent->left != nullptr)
			{
				if (parent->left->key == key) RemoveMatch(parent, parent->left, true);
				else RemoveNodePrivate(key, parent->left);
			}
			else if (key > parent->key && parent->right != nullptr)
			{
				if (parent->right->key == key) RemoveMatch(parent, parent->right, false);
				else RemoveNodePrivate(key, parent->right);
			}
			else wcout << "#The key " << key << " was not found in the Tree.\n";
		}
	}
	else wcout << "#The Tree is empty.\n";
}


void Tree::RemoveRootMatch()
{
	if (root != nullptr)
	{
		node* delPtr = root;
		int rootKey = root->key;
		int smallestInRightSubTree;

		if (root->left == nullptr && root->right == nullptr)
		{
			root = nullptr;
			delete delPtr;
		}

		else if (root->left == nullptr && root->right != nullptr)
		{
			root = root->right;
			delPtr->right = nullptr;
			delete delPtr;
			wcout << "The root node with key " << rootKey << " was deleted. " <<
				"The new root contains key " << root->key << ".\n";
		}

		else if (root->right == nullptr && root->left != nullptr)
		{
			root = root->left;
			delPtr->left = nullptr;
			delete delPtr;
			wcout << "The root node with key " << rootKey << " was deleted. " <<
				"The new root contains key " << root->key << ".\n";
		}

		else
		{
			smallestInRightSubTree = findSmallestPrivate(root->right);
			RemoveNodePrivate(smallestInRightSubTree, root);
			root->key = smallestInRightSubTree;
			wcout << "The root containing key " << rootKey <<
				" was overwritten with key " << root->key << ".\n";
		}
	}
	else wcout << "#Can't remove root. The Tree is empty.\n";
}


void Tree::RemoveMatch(node* parent, node* match, bool left)
{
	if (root != nullptr) {
		node* delPtr;
		int matchKey = match->key;
		int smallestInRightSubTree;

		if (match->left == nullptr && match->right == nullptr)
		{
			delPtr = match;
			if (left == true) parent->left = nullptr;
			else parent->right = nullptr;
			delete delPtr;
			if(debug)wcout << "The node containing key " << matchKey << " was remove.\n";
		}

		else if (match->left == nullptr && match->right != nullptr)
		{
			if (left == true) parent->left = match->right;
			else parent->right = match->right;
			match->right = nullptr;
			delPtr = match;
			delete delPtr;
			if (debug)wcout << "The node containing key " << matchKey << " was remove.\n";
		}

		else if (match->right == nullptr && match->left != nullptr)
		{
			if (left == true) parent->left = match->left;
			else parent->right = match->left;
			match->left = nullptr;
			delPtr = match;
			delete delPtr;
			if (debug)wcout << "The node containing key " << matchKey << " was remove.\n";
		}

		else
		{
			smallestInRightSubTree = findSmallestPrivate(match->right);
			RemoveNodePrivate(smallestInRightSubTree, match);
			match->key = smallestInRightSubTree;
		}
	}
	else wcout << "#Can't remove match. The Tree is empty.\n";
}


int Tree::FindItem(int key)
{
	return FindItemPrivate(root, key);
}

int Tree::FindItemPrivate(node* Ptr, int key)
{
	if (root != nullptr)
	{
		if (Ptr->key == key) {
			lastUseNode = Ptr;
			return Ptr->key;

		}
		else {
			if (key < Ptr->key)
			{
				if (Ptr->left != nullptr) FindItemPrivate(Ptr->left, key);
				else
				{
					wcout << "#The key " << key << " was not found in the Tree.\n";
					return -1000;
				}
			}

			else {
				if (Ptr->right != nullptr) FindItemPrivate(Ptr->right, key);
				else
				{
					wcout << "#The key " << key << " was not found in the Tree.\n";
					return -1000;
				}
			}
		}
	}
	else
	{
		wcout << "#The Tree is empty.\n";
		return -1000;
	}
}


Tree::~Tree()
{
	RemoveSubTree(root);
}

void Tree::RemoveSubTree(node* Ptr) 
{
	if (Ptr == nullptr)
		return;
	RemoveSubTree(Ptr->left);
	RemoveSubTree(Ptr->right);
	delete Ptr;
}













void Tree::add(node* root, node* parent, int key) {
	while (root != nullptr) {
		parent = root;
		if (root->key > key) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	if (parent->key > key) {
		parent->left = new node(key);
	}
	else {
		parent->right = new node(key);
	}
}



int Tree::calcHeight(node* root) {
	if (root == nullptr) {
		return -1;
	}
	int l = calcHeight(root->left);
	int r = calcHeight(root->right);
	if (l != r) {
		ans.push_back(root->key);
	}
	return max(l, r) + 1;
}

int Tree::calcDeep(node* node) {

	//int rootHeight = calcHeight(root);
	//int nodeHeight = calcHeight(node);
	//return rootHeight - nodeHeight;

	int countDeep = 0;
	Tree::node* tempNode = CreateLeaf(0);

	tempNode->parent = node->parent;

	while (tempNode->parent != root) {
		tempNode = tempNode->parent;
		countDeep++;
		if (tempNode == nullptr)
			return countDeep;
	}
	return countDeep+1;
}


Tree::node*& Tree::getMin(node*& root) {
	if (root->left == nullptr) {
		return root;
	}
	return getMin(root->left);
}

void Tree::removeValue(node*& root, int key) {
	if (root == nullptr) {
		return;
	}
	if (root->key == key) {
		if (root->left != nullptr && root->right != nullptr) {
			node*& minVal = getMin(root->right);
			root->key = minVal->key;
			minVal = minVal->right;
		}
		else if (root->left != nullptr) {
			root = root->left;
		}
		else if (root->right != nullptr) {
			root = root->right;
		}
		else {
			root = nullptr;
		}
		return;
	}
	if (root->key > key) {
		removeValue(root->left, key);
	}
	else {
		removeValue(root->right, key);
	}
}

void Tree::print(node* root) {
	if (root == nullptr) {
		return;
	}
	wcout << root->key << endl;
	print(root->left);
	print(root->right);
}

bool Tree::haveKey(node* root, int x) {
	if (root == nullptr) {
		return false;
	}
	if (root->key == x) {
		return true;
	}
	if (root->key > x) {
		return haveKey(root->left, x);
	}
	return haveKey(root->right, x);
}