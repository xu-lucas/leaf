#include<stdio.h>
#include<stdlib.h>

typedef int SDataType;

typedef struct stack 
{
	SDataType* _data;
	int _size;
	int _capacity;
}stack;


void initstack(stack* st) 
{
	if (st == NULL)
		return;
	st->_data = NULL;
	st->_capacity = st->_size = 0;
}
void checkCapcitystack(stack* st) 
{
	if (st->_size == st->_capacity)
	{
		int newCap = st->_capacity == 0 ? 1 : 2 *st->_capacity;
		st->_data = (SDataType *)realloc(st->_data, sizeof(SDataType)*newCap);
		st->_capacity = newCap;
	}
}

void pushbackstack(stack* st, SDataType val) 
{
	if (st == NULL) return;
	checkCapcitystack(st);
	
	st->_data[st->_size++] = val;
}
void popbackstack(stack* st) 
{
	if (st == NULL || st->_size == 0) return;
	--st->_size;
}

int checkSizestack(stack* st) 
{
	if (st == NULL || st->_size == 0) return;
	return st->_size;
}
int stackEmpty(stack* st) 
{
	if (st == NULL || st->_size == 0) 
		return 1;
	else 
		return 0;
}
void Destorystack(stack* st) 
{
	while (st->_size != NULL) 
	{
		popbackstack(&st);
	}
	return;
}
SDataType Topstack(stack* st)
{
	return st->_data[st->_size - 1];
}

void test() 
{
	stack st;
	initstack(&st);
	pushbackstack(&st, 1);
	pushbackstack(&st, 2);
	pushbackstack(&st, 3);
	pushbackstack(&st, 4);
	while (!stackEmpty(&st)) 
	{
		printf("%d ", Topstack(&st));
		popbackstack(&st);
	}
	printf("\n");
}
int main()
{
	test();
	return 0;
}