#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <sstream>
#include <istream>
#include <strstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <cassert>
#include <math.h>

using namespace std;

class Node {
public:
	char data;
	Node* left;
	Node* right;
};

Node* newNode(char data) {
		Node* node = new Node();
		node->data = data;
		node->left = node->right = NULL;
		return (node);
}


Node* insertLevelOrder(vector<char> vec, Node* root, size_t i) {
		if (i < vec.size()) {
			Node* temp = newNode(vec[i]);
			root = temp;

			root->left = insertLevelOrder(vec, root->left, 2*i + 1);
			root->right = insertLevelOrder(vec, root->right, 2 * i + 2);

		}
		return root;

	}



void print(Node* root, size_t depth) {
	if (root != NULL) {
		print(root->right, depth+1);
		cout << setw(2*depth) << "" <<root->data << endl;
		print(root->left, depth+1);
	}
}


void level_order_print(Node* root) {
	queue<Node*> q;
	Node* n_ptr;
	q.push(root);
	n_ptr = root;
	size_t depth=0;
	
	size_t tab=1;

	while (n_ptr->left != NULL) {
		n_ptr = n_ptr->left;
		depth++;
	}
	
	
	for (size_t i = 1; i < depth+1; i++) {
		tab *= 2;
		
	}


	while (!q.empty()) {

		size_t size = q.size();
		while (size > 0) {
			n_ptr = q.front();
			
			cout << setw(tab) << n_ptr->data << setw(tab)<< "";
			
			q.pop();
			if (n_ptr->left != NULL) {
				q.push(n_ptr->left);
			}
			
			if (n_ptr->right != NULL) {
				q.push(n_ptr->right);
			}
			size--;
		
		}
		
		cout << endl;
		
		tab /= 2;
		
	}
}

int center(int n) {
	return n <= 1 ? 0 : 2 * center(n/ 4) + 1;
}

int depth(int n) {	
	return n <= 7 ? 1 : 2 * depth(n / 4);
}

void h_tree_print(int node, int i, int j, int depth, int U, int D, int R, int L, vector<char> vec, char H[][15]){
	int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

	int n = vec.size();


	

	if (node > n) return;
	{
		H[i][j] = vec[node - 1];
		//cout << H_tree[i][j] << endl;



		if (node * 2 <= n) {
			H[i + depth * V[L][0]][j + depth * V[L][1]] = vec[2 * node - 1];
			//cout << H_tree[i + depth * V[L][0]][j + depth * V[L][1]] << endl;
			h_tree_print(4 * node, i + (depth * (V[L][0] + V[U][0])), j + (depth * (V[L][1] + V[U][1])), depth / 2, D, U, L, R, vec,H);
			h_tree_print(4 * node + 1, i + depth * (V[L][0] + V[D][0]), j + depth * (V[L][1] + V[D][1]), depth / 2, U, D, R, L, vec,H);

		}
		if (2 * node + 1 <= n) {
			H[i + depth * V[R][0]][j + depth * V[R][1]] = vec[2 * node];
			//cout << H_tree[i + depth * V[R][0]][j + depth * V[R][1]] << endl;
			h_tree_print(4 * node + 2, i + depth * (V[R][0] + V[D][0]), j + depth * (V[R][1] + V[D][1]), depth / 2, U, D, R, L, vec,H);
			h_tree_print(4 * node + 3, i + depth * (V[R][0] + V[U][0]), j + depth * (V[R][1] + V[U][1]), depth / 2, D, U, L, R, vec,H);
		}
	}

}
	

	

void output(istream& ins) {
	char c;
	string str;
	int N = 0;
	int S = 1;
	int E = 2;
	int W = 3;
	
	vector<char> v;

	while (1) {
		ins >> str;
		if (str == "EOI") break;
		else if (str == "INS") {
			cin >> c;
			v.push_back(c);
			assert(v.size() <= 200);
			push_heap(v.begin(), v.end());
		}
						
		else if (str == "DEL") {
			pop_heap(v.begin(), v.end());
			v.pop_back();
		}
	}
	Node* root = new Node();
	root = insertLevelOrder(v, root, 0);
	cout << "1. rotated form" << endl;
	print(root, 0);
	cout << endl;
	cout << "2. not-rotated form" << endl;
	level_order_print(root);
	cout << endl;
		
	int n = root->data;
	n -= '0';
	
	
	cout << "3. H-tree form " << endl;
	char H_tree[15][15] = {-2};
	h_tree_print(1, center(n), center(n), depth(n), N, S, E, W, v, H_tree);
	
	
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (H_tree[i][j] != -2)
				cout << H_tree[i][j]<< " ";
		}
		cout << endl;
	}
	
	
	
	delete root;

}

int main() {
	output(cin);
	// 복사하기 INS 1 INS 2 INS 3 INS 4 INS 5 INS 6 INS 7 INS 8 INS 9
	/* 
	복사하기
	INS 1 INS 2 INS 3 INS 4 INS 5 INS 6 INS 7 INS 8 INS 9 INS a INS b INS c INS d INS e INS f INS g INS h INS i INS j INS k INS l INS m INS n INS o INS p INS q INS r INS s INS t INS u INS v INS w INS x INS y INS z
	*/
}
