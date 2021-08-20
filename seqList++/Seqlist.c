#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Seqlist.h"

void initSqlist(Sqlist* s1)
{
	if (s1 == NULL) {
		return;
	}
	s1->_data = NULL;
	s1->_size = 0;
	s1->_capacity = 0;
}

void SqlistCheckCapacity(Sqlist* s1)
{
	if (s1->_size == s1->_capacity)
	{
		int newCapacity = s1->_capacity = 0 ? 1 : 2 * s1->_capacity;
		SLDataType* tmp = (SLDataType*)malloc(newCapacity * sizeof(SLDataType));
		if (tmp != 0)
			memcpy(tmp, s1->_data, sizeof((SLDataType)s1->_size));
		free(s1->_data);
		s1->_data = tmp;
		s1->_capacity = newCapacity;
	}
}

SLDataType SqlistAt(Sqlist* s1, int pos)
{
	return s1->_data[pos];
}

void SqlistPrint(Sqlist* s1)
{
	if (s1 == NULL) {
		return;
	}
	for (int i = 0; i <= s1->_size; ++i)
	{
		printf("%d", s1->_data[i]);
	}
	printf("\n");
}

void SqlistInsert(Sqlist* s1, int pos, SLDataType val)
{
	if (s1 == NULL) {
		return;
	}
	SqlistCheckCapacity(s1);
	int end = s1->_size;
	while (pos < end)
	{
		s1->_data[end] = s1->_data[end - 1];
		--end;
	}
	s1->_data[pos] = val;
	++s1->_size;
}


void test()
{
	Sqlist s1;
	initSqlist(&s1);
	SqlistInsert(&s1, 0, 1);
	SqlistInsert(&s1, 1, 1);
	SqlistInsert(&s1, 2, 1);
	SqlistInsert(&s1, 3, 1);
	SqlistInsert(&s1, 4, 1);

}

int main()
{
	test();
	return 0;
}

