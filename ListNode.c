#include<stdio.h>
#include<stdlib.h>

typedef int LDataType;
typedef struct Listnode 
{
	LDataType* _data;
	struct Listnode* _next;
}Listnode;

typedef struct list
{
	Listnode* _head;
}list;

Listnode* creatListnode(LDataType val)
{
    Listnode* node = (Listnode*)malloc(sizeof(Listnode));
	if(node!=NULL)
	node->_data = val;
	node->_next = NULL;
	return node;
}

void initlist(list* lst) 
{
	if (lst == NULL)
		return;
	lst->_head = NULL;
}

void listpushBack(list* lst, LDataType val)
{
	if (lst == NULL)
		return;
	if (lst->_head == NULL) 
	{
		lst->_head = creatListnode(val);
	}
	else 
	{
		Listnode* tail = lst->_head;
		while (tail->_next != NULL) 
		{
			tail = tail->_next;
		}
		tail->_next = creatListnode(val);
	}
}

void listPopBack(list* lst) 
{
	if (lst == NULL || lst->_head == NULL)
		return;
	Listnode* prev = NULL;
	Listnode* tail = lst->_head;
		while (tail->_next != NULL)
		{
			prev = tail;
			tail = tail->_next;
		}
		free(tail);
		if (prev == NULL)
			lst->_head = NULL;
		else
			prev->_next = NULL;
}

void listPushFront(list* lst, LDataType val)
{

	if (lst == NULL)
		return;
	Listnode* node = creatListnode(val);
	node->_next = lst->_head;
	lst->_head = node;
}

void listPopFront(list* lst)
{
	if (lst == NULL || lst->_head == NULL)
		return;
	Listnode* next = lst->_head->_next;
	free(lst->_head);
	lst->_head = next;
}

void listInsertAfter(Listnode* node, LDataType val)
{
	if (node == NULL)
		return;
	Listnode* next = node->_next;
	Listnode* newnode = creatListnode(val);
	node->_next = newnode;
	newnode->_next = next;
}

void listEraseAfter(Listnode* node)
{
	if (node == NULL || node->_next == NULL)
		return;
	Listnode* next = node->_next;
	Listnode* nextnext = next->_next;
	free(next);
	node->_next = nextnext;
}

Listnode* listFind(list* lst, LDataType val) 
{
	if (lst == NULL)
		return;
	Listnode* cur = lst->_head;
	while (cur) 
	{
		if (cur->_data == val)
			return cur;
		cur = cur->_next;
	}
	return NULL;

}

void test() 
{
	list lst;
	initlist(&lst);
	listpushBack(&lst, 1);
	listpushBack(&lst, 2);
	listpushBack(&lst, 3);
	listpushBack(&lst, 4);
	listPopBack(&lst);
	listPushFront(&lst,5);
	return ;
}

int main() 
{
	test();
	return 0;
}