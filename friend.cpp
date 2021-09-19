#include<iostream>
using namespace std;
//new和delete底层实现
struct ListNode
{
	void *operator new(size_t n)
	{
		cout << "operator new" << endl;
		allocator<ListNode> alloc;
		return alloc.allocate(1);
		cout << "memory pool allocate" << endl;
	}
	void operator delete(void* ptr)
	{
		cout << "operator delete" << endl;
		allocator<ListNode> alloc;
		alloc.deallocate((ListNode*)ptr,1);
		cout << "memory pool deallocate" << endl;
	}
	ListNode(int data = 1) 
		:_data(data)
	{
		cout << "ListNode(int)" << endl;
	}
	~ListNode() 
	{
		cout << "~ListNode()" << endl;
	}
private:
	int _data = 0;
	ListNode* _next = nullptr;
};


//友元函数、友元类
class A 
{
public:
	//友元函数：本身不是类的成员函数，可以访问类的私有成员
	//普通函数，可以放在类内的所有位置
	//friend void operator<<(ostream& _cout, const A&a);
	friend ostream& operator<<(ostream& _cout, const A&a);
	friend istream& operator>>(istream& _cin, A &a);
	A(int a=1,int b=2,int c=3)
	:_a(a)
	,_b(b)
	,_c(c)
	{}
	/*void operator<<(ostream& _cout) 
	{
		_cout << _a << "-" << _b << "-" << _c << "-" << endl;
	}*/

	
private:
	int _a;
	int _b;
	int _c;
};
ostream& operator<<(ostream& _cout, const A&a)
{
	_cout << a._a << "-" << a._b << "-" << a._c << endl;
	return _cout;

}
istream& operator>>(istream& _cin, A &a) 
{
	_cin >> a._a >> a._b >> a._c ;
	return _cin;
}
//void operator<<(ostream& _cout,const A&a)
//{
//	_cout << a._a << "-" << a._b << "-" << a._c << endl;
//}
void test() 
{
	A a;
	A b;
	//a.operator<<();
	//a << cout;
	operator<<(cout, a);
	cout << a << a << a << endl;
	//申请空间
	char* ptr = (char*)malloc(sizeof(char));
	
	//调整空间大小
	char* ptr1 = (char*)realloc(ptr, 2 * sizeof(char));
	//申请新的空间，功能和malloc相似
	char* ptr2 = (char*)realloc(NULL, sizeof(char));

	//ptr指向的空间不能释放
	//只能显式realloc返回之后的空间，传入realloc的指针空间显式释放
	free(ptr1);

	//申请空间+空间全部初始化为0
	char* ptr3 = (char*)calloc(4, sizeof(char));

	//new,delete
	int* ptr4 = new int;//申请空间
	int* ptr5 = new int(10);//申请空间+初始化
	delete ptr5;
	//连续空间:包含10个元素
	int* arr = new int[10];
	delete[] arr;
}