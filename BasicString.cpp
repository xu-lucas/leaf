#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

class String 
{
public:
	String(const char* str ="" ) 
		:_data(new char[strlen(str)+1])
	{
		strcpy(_data, str);
	}
	//拷贝构造的经典写法
	/*String(const String& str)
		:_data(new char[strlen(str._data)+1])
	{
		strcpy(_data, str._data);
	}*/

	////拷贝构造的现代写法:
	//String(const String& str) 
	//	:_data(nullptr)
	//{
	//	String tmp(str._data);
	//	swap(_data, tmp._data);
	//}
	String(const String& str) 
		:_data(str._data)
	{
	}
	
	//析构函数
	~String() 
	{
		if (_data) 
		{
			delete[] _data;
			_data = nullptr;
		}
	}
private:
	char* _data;
};




void test() 
{
	String str("123");
	String copy(str);
	String str2("456");
	str = str2;
}

int main() 
{
	test();
	return 0;
}