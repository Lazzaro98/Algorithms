
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;

	Node(int val)
	{
		data = val;
		left = NULL;
		right = NULL;
	}
};

void preorder_r(Node* root) {
	if (root == nullptr)
		return;
	cout << root->data << " ";
	preorder_r(root->left);

	preorder_r(root->right);
}

void preorder_i(Node* root) {
	stack<Node*> s;
	s.push(root);
	Node* curr;
	while (!s.empty()) {
		curr = s.top();
		s.pop();

		while (curr != nullptr) {
			cout << curr->data << " ";
			if (curr->right) s.push(curr->right);
			curr = curr->left;
		}
	}
	cout << endl;
}


void inorder_r(Node* root) {
	if (root == nullptr)
		return;

	inorder_r(root->left);
	cout << root->data << " ";
	inorder_r(root->right);
}

void inorder_i(Node* root) {
	stack<Node*> s;

	Node* curr = root;
	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top();
		s.pop();
		cout << curr->data << " ";
		curr = curr->right;
	}
}


void postorder_r(Node* root) {
	if (root == nullptr)
		return;
	postorder_r(root->right);
	postorder_r(root->left);
	cout << root->data << " ";
}

void postorder_i(Node* root) {
	stack<Node*> s;
	Node* curr = root;
	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->right;
		}

		curr = s.top();
		s.pop();
		if (curr->left)
			s.push(curr->left);
		else
			cout << curr->data << " ";
		curr = s.top();
		s.pop();
	}
}

// If inorder is sorted, it is BST
bool isBST(Node* root) {
	stack<Node*> s;

	Node* prev = nullptr, * curr = root;
	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top(); s.pop();

		if (prev != nullptr && prev->data > curr->data) return false;
		prev = curr;
		curr = curr->right;

	}
	return true;
}

int maxDepth(Node* root) {
	if (root == nullptr)
		return -1;

	int ldepth = maxDepth(root->left);
	int rdepth = maxDepth(root->right);

	if (ldepth > rdepth)
		return ldepth + 1;
	return rdepth + 1;
}

int max(int a, int b) {
	if (a > b)return a;
	return b;
}
int maxDepth_i(Node* root) {
	int max_d = 0, curr_d = 0;
	stack<Node*> s;
	Node* curr = root;

	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->left;
			curr_d++;
			max_d = max(curr_d, max_d);
		}
		curr = s.top(); s.pop();
		curr_d--;
		max_d = max(curr_d, max_d);
		curr = curr->right;
		if (curr) { curr_d++; max_d = max(curr_d, max_d); }
	}

	return max_d;
}

void print_level(Node* root, int level) {
	if (root == nullptr)
		return;
	else if (level == 1)
		cout << root->data << " ";
	else if (level > 1) {
		print_level(root->left, level - 1);
		print_level(root->right, level - 1);
	}
}
void levelOrder_r(Node* root) {
	int h = maxDepth(root);
	for (int i = 1; i <= h; i++) {
		print_level(root, i);
		cout << "\n";
	}
}

void levelOrder_i(Node* root) {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* curr = q.front();
		q.pop();
		cout << curr->data << " ";
		if (curr->left) q.push(curr->left);
		if (curr->right) q.push(curr->right);
	}
}

int minDepth_p(Node* root, int level) {
	if (root == nullptr)
		return level;

	if (root->left == nullptr || root->right == nullptr) return level;
	return minDepth_p(root->left, level + 1);
	return minDepth_p(root->right, level + 1);

}

int minDepth(Node* root) {
	return minDepth_p(root, 1);
}

void bottom_view_formmap(Node* root, int dist, int level, map<int, Node*>& m) {
	if (root == nullptr)
		return;
	m[dist] = root;
	bottom_view_formmap(root->left, dist - 1, level + 1, m);
	bottom_view_formmap(root->right, dist + 1, level + 1, m);
}

vector<int> bottom_view(Node* root) {
	map<int, Node*> m;
	bottom_view_formmap(root, 0, 0, m);
	vector<int> ret;

	for (auto it = m.begin(); it != m.end(); it++)
		ret.push_back(it->second->data);
	return ret;
}

void print_vector(vector<int> vect) {
	for (int i = 0; i < vect.size(); i++)
		cout << vect[i] << " ";
	cout << endl;
}

int sum_tree(Node* root) {
	if (root == nullptr)
		return 0;
	int left = sum_tree(root->left);
	int right = sum_tree(root->right);
	int old = root->data;
	root->data = left + right;
	return root->data + old;

}
void transform_to_sumtree(Node* root) {
	sum_tree(root);
}
int determine_node_level_util(Node* root, int k, int level) {
	if (root == nullptr)
		return 0;
	if (root->data == k)
		return level;

	int res = determine_node_level_util(root->left, k, level + 1);

	if (res != 0)
		return res;

	res = determine_node_level_util(root->right, k, level + 1);

	return res;
}

int determine_node_level(Node* root, int k) {
	return determine_node_level_util(root, k, 1);
}

bool same_parents(Node* root, int k1, int k2) {
	Node* curr = root;
	stack<Node*> s;

	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top(); s.pop();

		int l = -1, r = -1;
		if (curr->left && curr->right) {
			l = curr->left->data;
			r = curr->right->data;
		}

		if ((l == k1 && r == k2) || (l == k2 && r == k1))
			return true;
		else if (l == k1 || r == k1 || l == k2 || r == k2)
			return false;


		curr = curr->right;
	}

	return false;
}

bool are_cousins(Node* root, int k1, int k2) {

	if (!same_parents(root, k1, k2))
		return false;

	int level1 = determine_node_level(root, k1);
	int level2 = determine_node_level(root, k2);

	return level1 == level2;

}

void printCousinsUtil(Node* root, int level, int target_level, int k) {

	if (root == nullptr)
		return;
	if (target_level == level)
		cout << root->data << " ";

	if (root->left && root->left->data == k || root->right && root->right->data == k)
		return;
	printCousinsUtil(root->left, level + 1, target_level, k);
	printCousinsUtil(root->right, level + 1, target_level, k);
}
void printCousins(Node* root, int k) {
	int level = determine_node_level(root, k);
	printCousinsUtil(root, 1, level, k);
}

int sum_(Node* root) {
	if (root == nullptr)
		return 0;
	if (!root->left && !root->right)
		return root->data;
	int old = root->data;
	int l = sum_(root->left);
	int r = sum_(root->right);

	if (l != INT_MIN && r != INT_MIN && old == l + r)
		return l + r + old;

	return INT_MIN;
}

bool is_sum_tree(Node* root) {
	return sum_(root) != INT_MIN;
}


// is tree subtree
void inorder(Node* root, vector<int>& vec) {
	if (root == nullptr)
		return;
	inorder(root->left, vec);
	vec.push_back(root->data);
	inorder(root->right, vec);
}

void preorder(Node* root, vector<int>& vec) {
	if (root == nullptr)
		return;
	vec.push_back(root->data);
	preorder(root->left, vec);
	preorder(root->right, vec);
}

bool is_subarray(vector<int> vec1, vector<int> vec2) {
	return search(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()) != vec1.end();
}

bool is_subtree(Node* root1, Node* root2) {
	if (root1 == nullptr || root2 == nullptr)
		return false;
	vector<int> inorder1;
	inorder(root1, inorder1);

	vector<int> inorder2;
	inorder(root2, inorder2);

	vector<int> preorder1;
	preorder(root1, preorder1);

	vector<int> preorder2;
	preorder(root2, preorder2);

	return is_subarray(inorder1, inorder2) && is_subarray(preorder1, preorder2);
}


void switch_kids(Node* root) {
	Node* pom = root->left;
	root->left = root->right;
	root->right = pom;
}

void mirror(Node* root) {
	if (root == nullptr)
		return;

	switch_kids(root);
	mirror(root->left);
	mirror(root->right);
}


bool printAncestors(Node* root, Node* node) {
	if (root == nullptr)
		return false;
	if (root == node)
		return true;

	bool left = printAncestors(root->left, node);
	bool right = false;
	if (!left) {
		right = printAncestors(root->right, node);
	}

	if (left || right)
		cout << root->data << " ";

	return left || right;
}

bool isNodePresent(Node* root, Node* node) {
	if (root == nullptr)
		return false;

	if (root == node)
		return true;

	return isNodePresent(root->left, node) || isNodePresent(root->right, node);
}

int findLevel(Node* root, int k, int level) {
	if (root == nullptr)
		return -1;
	if (root->data == k)
		return level;

	int left = findLevel(root->left, k, level + 1);
	if (left != -1) return left;
	return findLevel(root->right, k, level + 1);
}

Node* findLCA(Node* root, Node* x, Node* y) {
	if (root == nullptr)
		return nullptr;

	if (root == x || root == y)
		return root;

	Node* left = findLCA(root->left, x, y);
	Node* right = findLCA(root->right, x, y);

	if (left && right)
		return root;

	if (left)
		return left;

	if (right)
		return right;

}

int findDistance(Node* root, Node* x, Node* y) {
	Node* lca = nullptr;
	if (isNodePresent(root, x) && isNodePresent(root, y))
		lca = findLCA(root, x, y);
	else
		return INT_MIN;

	return findLevel(lca, x->data, 0) + findLevel(lca, y->data, 0);
}



int max_sum_route(Node* root) {
	if (root == nullptr)
		return 0;

	if (!root->left && !root->right)
		return root->data;

	int old = root->data;

	return max(max_sum_route(root->left), max_sum_route(root->right)) + old;
}

bool printMaxSumPath(Node* root, int sum) {
	if (root == nullptr && sum == 0)
		return true;
	if (root == nullptr)
		return false;

	bool l = printMaxSumPath(root->left, sum - root->data);
	bool r = false;
	if (!l)
		r = printMaxSumPath(root->right, sum - root->data);

	if (l || r)
		cout << root->data << " ";
	return l || r;
}
int printOneDistancedNodesFromLeafsUtil(Node* root, int target_dist) {
	if (root == nullptr)
		return 0;

	int level1 = printOneDistancedNodesFromLeafsUtil(root->left, target_dist);
	int level2 = printOneDistancedNodesFromLeafsUtil(root->right, target_dist);

	if (level1 == target_dist || level2 == target_dist)
		cout << root->data << " ";

	return min(level1, level2) + 1;

}
void printOneDistancedNodesFromLeafs(Node* root) {
	printOneDistancedNodesFromLeafsUtil(root, 2);

}

// BST one swap away
// inorder traversal and mark two nodes that are not correct
// after that, just swap them

void mark(Node*& first, Node*& second, Node* prev, Node* curr) {
	if (!first)
		first = prev;
	else 
		second = curr;
}
void swap_nodes(Node* first, Node* second) {
	int pom = first->data;
	first->data = second->data;
	second->data = pom;
}
void fixBST(Node* root) {
	Node* first_to_fix = nullptr, *second_to_fix = nullptr;

	stack<Node*> s;
	Node* curr = root;
	Node* prev = nullptr;
	int i = 0;
	while (!s.empty() || curr != nullptr) {
		while (curr != nullptr) {
			s.push(curr);
			curr = curr->left;
		}

		
		curr = s.top(); s.pop();
	
		if (prev && prev->data > curr->data)
			mark(first_to_fix, second_to_fix, prev, curr);

		prev = curr;

		curr = curr->right;
	}


	swap_nodes(first_to_fix, second_to_fix);
}

Node* insert(Node* root, int key)
{
	// if the root is null, create a new node and return it
	if (root == nullptr) {
		return new Node(key);
	}

	// if the given key is less than the root node, recur for the left subtree
	if (key < root->data) {
		root->left = insert(root->left, key);
	}
	// if the given key is more than the root node, recur for the right subtree
	else {
		root->right = insert(root->right, key);
	}

	return root;
}
int main()
{
	/* 4 becomes left child of 2
			   4
			/     \
		   2      5
		  / \     / \
		 10  3
	*/
	int keys[] = { 15, 10, 20, 8, 12, 16, 25 };
	Node* root = nullptr;
	for (int key : keys) {
		root = insert(root, key);
	}

	// swap any two nodes' values
	swap(root->left->data, root->right->right->data);


	cout << "Preorder:\n";
	preorder_r(root);
	cout << endl;
	preorder_i(root);


	cout << "\n\nInorder:\n";
	inorder_r(root);
	cout << endl;
	inorder_i(root);
	cout << endl;
	/*
	cout << "\n\nPostorder:\n";
	postorder_r(root);
	cout << endl;
	postorder_i(root);
	*/
	if (isBST(root))
		cout << "Tree is BST\n";
	else
		cout << "Tree is not BST\n";

	cout << "Max depth of the tree is " << maxDepth_i(root) << endl << endl;

	cout << "Level order:\n";
	levelOrder_i(root);
	cout << "\nMin depth of the tree is " << minDepth(root) << endl;

	cout << "Bottom view:";
	print_vector(bottom_view(root));
	/*transform_to_sumtree(root);
	cout << "\nNakon sumiranja, preorder stabla je:\n";
	preorder_i(root);*/
	cout << endl;
	int k = 3;
	cout << "Level of " << k << " is " << determine_node_level(root, k);
	cout << endl;
	cout << are_cousins(root, 4, 6);
	cout << endl;
	printCousins(root, 7);
	cout << endl;
	cout << is_sum_tree(root);
	cout << endl;
	is_subtree(root, root->right) ? cout << "Yes" : cout << "No";
	cout << endl;
	//mirror(root);
	preorder_i(root);
	cout << endl;
	cout << max_sum_route(root);
	cout << endl;
	printOneDistancedNodesFromLeafs(root);
	cout << endl;
	inorder_i(root);
	cout << endl;
	fixBST(root);
	inorder_i(root);
	return 0;
}
