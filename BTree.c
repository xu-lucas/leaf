#include<stdio.h>
#include<stdlib.h>
typedef char DataType;
typedef struct Node
{
	struct Node* _left;
	struct Node* _right;
	DataType _data;
}Node;

typedef struct BTree 
{
	Node* _root;
}BTree;

void createBTree(BTree* bt) 
{
	if (bt == NULL)
		return NULL;
	//创建一个空树
	bt->_root = NULL;
}
//创建一个二叉树，返回二叉树的根节点指针
//数组的顺序为前序遍历
//前序遍历的数组“ABD##E#H##CF##G##”

Node* creatBTree(DataType arr[], int* idx)
{
	if (arr[*idx] =='#')
	{
		(*idx)++;
		return NULL;//空树
	}
	Node* root = (Node*)malloc(sizeof(Node));
	root->_data = arr[*idx];
	(*idx)++;
	root->_left = creatBTree(arr, idx);
	root->_right = creatBTree(arr, idx);
	return root;
}

void Preorder(Node* root) 
{
	if (root) 
	{
		printf("%c ", root->_data);
		Preorder(root->_left);
		Preorder(root->_right);
	}
}
void Inorder(Node* root)
{
	if (root)
	{
		Inorder(root->_left);
		printf("%c ", root->_data);
		Inorder(root->_right);
	}	
}

void Postorder(Node* root)
{
	if (root)
	{
		Postorder(root->_left);
		Postorder(root->_right);
		printf("%c ", root->_data);
	}
}

int BTreeSize(Node* root) 
{
	if (root == NULL)
		return 0;
	return BTreeSize(root->_left) + BTreeSize(root->_right )+ 1;
}

int BTreeHigh(Node* root) 
{
	if (root == NULL)
		return 0;
	int left = BTreeHigh(root->_left);
	int right = BTreeHigh(root->_right);
	return left > right ? left + 1 : right + 1;
}
void test() 
{
	char arr[] = "ABD##E#H##CF##G##";
	int idx = 0;
	Node* root = creatBTree(arr, &idx);
	Preorder(root);
	printf("\n");
	Inorder(root);
	printf("\n");
	Postorder(root);
	printf("\n");
	printf("Size:%d\n",BTreeSize(root));
	printf("Hign:%d\n", BTreeHigh(root));
}

int main() 
{
	test();
	return 0;
}