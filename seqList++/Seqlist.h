#pragma once
typedef int SLDataType;

typedef struct Sqlist
{
	SLDataType _data;
	int _size;
	int _capacity;
}Sqlist;

void initSqlist(Sqlist* s1);

void SqlistCheckCapacity(Sqlist* s1);

SLDataType SqlistAt(Sqlist* s1,int pos);

void SqlistInsert(Sqlist* s1, int pos,SLDataType val);

void SqlistPrint(Sqlist* s1);

