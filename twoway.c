#include<stdlib.h>
#include<stdio.h>

typedef int LDatatype;
typedef struct ListNode 
{
	LDatatype _data;
	struct Listnode* _prev;
	struct ListNode* _next;

}ListNode;

typedef struct List
{
	struct ListNode* _head;
}List;

void InsertList(ListNode* node, LDatatype val);
//初始化双向循环带头链表

void initList(List* lst)
{
	//构建循环结构
	//创建头节点
	lst->_head =  (struct ListNode*)malloc(sizeof(struct ListNode));
	lst->_head->_prev = lst->_head->_next = lst->_head;
}
//创建新节点
struct ListNode* creatNode(LDatatype val)
{
	struct ListNode* node= (struct ListNode*)malloc(sizeof(struct ListNode));
	node->_data = val;
	node->_next = node->_prev = NULL;
	return node;
}
//尾插
void pushbackList(List* lst, LDatatype val)
{
	if (lst == NULL||lst->_head==NULL) return NULL;
	struct ListNode* tail = lst->_head->_prev;
	struct ListNode* newNode = creatNode(val);

	tail->_next = newNode;
	newNode->_prev = tail;

	newNode->_next = lst->_head;
	lst->_head->_prev = newNode;
	//InsertList(lst->_head,val);
}
//尾删
void popbackList(List* lst) 
{
	if (lst == NULL || lst->_head == NULL) return NULL;
	struct ListNode* tail = lst->_head->_prev;
	struct ListNode* prev = tail->_prev;

	free(tail);

	prev->_next = lst->_head;
	lst->_head->_prev = prev;
}

//头插
void pushFrontList(List* lst, LDatatype val)
{
	if (lst == NULL || lst->_head == NULL) return NULL;
	struct ListNode* newNode = creatNode(val);
	struct ListNode* next = lst->_head->_next;

	lst->_head->_next = newNode;
	newNode->_prev = lst->_head;

	newNode->_next = next;
	next->_prev = newNode;
	//InsertList(lst->_head->_next, val);
}
//头删
void popFrontList(List* lst) 
{
	if (lst == NULL || lst->_head == NULL) return NULL;
	if (lst->_head->_next == lst->_head) return;
	struct ListNode* next = lst->_head->_next;
	struct ListNode* nextnext = lst->_head->_next->_next;

	free(next);

	lst->_head->_next = nextnext;
	nextnext->_prev = lst->_head;
}
//任意位置插入
void InsertList(ListNode* node, LDatatype val)
{
	struct ListNode* newNode = creatNode(val);
	struct ListNode* prev = node->_prev;

	newNode->_next = node;
	node->_prev = newNode;

	prev->_next = newNode;
	newNode->_prev = prev;
}
//任意位置删除
void EraseList(ListNode* node) 
{
	struct ListNode* prev = node->_prev;
	struct ListNode* next = node->_next;

	free(node);

	prev->_next = next;
	next->_prev = prev;
}

void Destory(List *lst) 
{
	struct ListNode* cur = lst->_head->_next;
	while (cur != lst->_head)
	{
		struct ListNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	free(lst->_head);
	lst->_head = NULL;
}

//打印
void printList(List *lst)
{
	struct ListNode* cur = lst->_head->_next;
	while (cur!=lst->_head) 
	{
		printf("%d", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}
//测试
void test() 
{
	struct List lst;
	initList(&lst);
	pushbackList(&lst, 1);
	pushbackList(&lst, 2);
	pushbackList(&lst, 3);
	printList(&lst);
	pushbackList(&lst, 4);
	pushbackList(&lst, 5);
	printList(&lst);
	popbackList(&lst);
	pushFrontList(&lst, -1);
	printList(&lst);
	popFrontList(&lst);
	printList(&lst);

	
}
int main()
{
	test();
	return 0;
}