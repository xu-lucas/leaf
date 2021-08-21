#include<stdio.h>
#include<stdlib.h>

typedef int QDataType;

typedef struct QNode 
{
	QDataType _data;
	struct QNode* _next;
}QNode;

typedef struct Queue
{
	struct QNode* _head;
	struct QNode* _tail;
	int _size;
}Queue;

void initQueue(Queue* q)
{
	if (q == NULL)
		return;
	q->_head = q->_tail = NULL;
	q->_size = 0;
}
struct QNode* createNode(QDataType val) 
{
	struct QNode* node = (struct QNode*)malloc(sizeof(struct Queue));
	node->_data = val;
	node->_next = NULL;
	return node;
}
void PushQueue(Queue* q, QDataType val)
{
	if (q == NULL)
		return;
	struct QNode* node= createNode(val);
	if (q->_head == NULL) 
	{
		q->_head = q->_tail = node;
	}
	else
	{
		q->_tail->_next=node;
		q->_tail = node;
	}
	++q->_size;
}
void PopQueue(Queue* q) 
{
	if (q == NULL||q->_head==NULL)
		return;
	struct QNode* next = q->_head->_next;
	free(q->_head);
	q->_head = next;
	if (q->_head == NULL)
		q->_tail = NULL;
	--q->_size;
}
int EmptyQueue(Queue* q) 
{
	return q->_head==NULL;
}

QDataType FrontQueue(Queue* q)
{
	return q->_head->_data;
}

QDataType BackQueue(Queue* q) 
{
	return q->_tail->_data;
}
int QueueSize(Queue* q) 
{
	if (q == NULL)
		return 0;
	return q->_size;
}
void test()
{
	Queue q;
	initQueue(&q);
	PushQueue(&q, 1);
	PushQueue(&q, 2);
	PushQueue(&q, 3);
	PushQueue(&q, 4);
	while (!EmptyQueue(&q))
	{
		printf("%d ", FrontQueue(&q));
		PopQueue(&q);
	}
	printf("\n");
	PopQueue(&q);
	printf("%d\n", QueueSize(&q));
}

int main() 
{
	test();
	return 0;
}