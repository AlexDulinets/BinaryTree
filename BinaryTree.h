#include <iostream> 
#include <cstdio> 
#include <vector> 
#include <algorithm> 
#include <cstdlib>

using namespace std;



class Tree {
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	bool debug=true;
private:
	//для вычисления эл в 2 зд.
	vector<int> ans;

	class node {
	public:
		int key;
		node* left;
		node* right;
		node* parent;

		node() {
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			this->key = 0;

		};

		node(int k) {
			this->key = k;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
		}
	};

	

	void AddLeafPrivate(int key, node* Ptr);
	void PrintInOrderPrivate(node* Ptr);
	void PrintPreOrderPrivate(node* Ptr);
	void PrintPostOrderPrivate(node* Ptr);
	void SpecialPrintPrivate(node* Ptr, int level);
	node* ReturnNodePrivate(int key, node* Ptr);
	int findSmallestPrivate(node* Ptr);
	void RemoveNodePrivate(int key, node* Parent);
	void RemoveRootMatch();
	void RemoveMatch(node* parent, node* match, bool left);
	void RemoveSubTree(node* Ptr);
	int FindItemPrivate(node* Ptr, int key);

	node* CreateLeaf(int key);
	node* ReturnNode(int key);

public:

	node* root;
	node* lastUseNode;

	Tree();
	~Tree();
	void AddLeaf(int key);
	void PrintInOrder();
	void PrintPreOrder();
	void PrintPostOrder();
	void ColorPrint();
	int ReturnRootKey();
	void PrintChildren(int key);
	int findSmallest();
	void RemoveNode(int key);
	int FindItem(int key);

	//8
	void HeightDepthLevel() {
		cout << "Enter required item: "; 
		int x;
		cin >> x;

		if (FindItem(x)!=-1000) {

			int height = calcHeight(lastUseNode);
			cout << "Height: " << height << endl;

			int deep = calcDeep(lastUseNode);
			cout << "Depth: " << deep << endl;

			int level = calcHeight(root) - calcDeep(lastUseNode);
			cout << "Level: " << level << endl;
		}
		
	}




	

	void add(node* root, node* parent, int key);

	int calcHeight(node* root);
	int calcDeep(node* node);

	node*& getMin(node*& root);

	void removeValue(node*& root, int key);

	void print(node* root);

	bool haveKey(node* root, int x);
	
	void IndTask() {
		int index=0;
		for (int i = 0; i < v1.size(); i++) {
			if (FindItem(v1.at(i)) != -1000) {
				int deep = calcDeep(lastUseNode);
				v2.push_back(deep);
				v3.push_back(deep);
			}
		}
		sort(v3.begin(), v3.end());
		for (int i = 0; i < v2.size(); i++) {
			if (v3.at((v3.size()) - 2) == v2.at(i)) {
				index = i;
				break;
			}
		}

		if (FindItem(v1.at(index)) != -1000) {
			debug = false;
			RemoveNode(lastUseNode->parent->key);
			cout << "Individual task №8 complete\n";
		}
		debug = true;
	}
	



}; 

void purple();
void lime();
void red();
void yellow();
void grey();
void white();