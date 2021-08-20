#include<stdio.h>
#define N 100
typedef int SLDataType;

//sequence list
//静态顺序表 <不需要容量判断>
//会占据栈上的空间，造成资源浪费
//sizeof(seqList):404byte;
//struct seqList1 
//{
//	SLDataType _data[N];
//	int _size;
//};

//动态顺序表
//sizeof(seqList):12byte;
typedef struct seqList
{
	SLDataType* _data;//数组指针
	int _size;//有效的元素的个数
	int _capacity;//数组的空间
}seqList;


void initseqList(seqList* s1);
//操作：增删改查
//尾插：给顺序表最后一个有效数据的末尾插入新的数据
//接口：用于声明函数
//尾插
void seqListPushBack(seqList* s1, SLDataType val);
//头插
void seqListPushFront(seqList* s1, SLDataType val);
//检查容量
void seqListCheckCapacity(seqList* s1);
//尾删
void seqListpopBack(seqList* s1);
//头删
void seqListPopFront(seqList* s1);
//打印函数
void seqListPrint(seqList* s1);

SLDataType seqListAt(seqList* s1, int pos);
//判空
int seqListEmpty(seqList* s1);
//检查有效数据大小
int seqListSize(seqList* s1);