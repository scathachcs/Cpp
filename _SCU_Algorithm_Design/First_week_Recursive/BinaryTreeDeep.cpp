#include<iostream>
#include <cstring>
#include<stdio.h>

using namespace std;

class BinaryTree {
private:
	int Node[21][2];
public:
	BinaryTree() {
		memset(Node, 0, sizeof(Node));
	}
	void Creat() {
		int x,num;
		cin >> num;
		num = num - 1;
		while (num--) {
			cin >> x;
			if (Node[x][0] == 0)
				cin >> Node[x][0];
			else
				cin >> Node[x][1];
		}
	}
	int TreeDepth(int root) {
		if (Node[root][0] == 0 && Node[root][1] == 0)
			return 1;

		int left = 0;
		int right = 0;
		if(Node[root][0]!=0)
			left = TreeDepth(Node[root][0]);
		if (Node[root][1]!=0)
			right = TreeDepth(Node[root][1]);
		return left > right ? left+1 : right+1;
		
	}
};

int main() {
	BinaryTree tree;
	tree.Creat();
	cout<<tree.TreeDepth(1)<<endl;
	return 0;
}