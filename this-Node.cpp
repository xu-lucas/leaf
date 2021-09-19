#include<iostream>
using namespace std;
class A 
{
public:
	A() 
	{
		++_count;
	}
	A(const A& a) 
	{
		++_count;
	}
	//this 指针的意义：指向当前调用此函数的对象
	//static成员函数不包括this指针
	//static函数可以通过类名访问，通过类名访问时，没有对象
	 static int getCount() 
	{
		 //缺少this指针,不能调用static成员函数
		 //fun();
		return _count;
	}
	 void fun() 
	 {
		 getCount();
		 cout << "fun()" << endl;
	 }
private:
	static int _count;
};
//static成员是所有对象共享
//static成员必须在类外初始化
int A::_count = 0;

A funA(A a) 
{
	return a;
}

void main() 
{
	A a;
	A b;
	A a1 = funA(a);
	cout << a1.getCount() << endl;
	cout << A::getCount() << endl;
}