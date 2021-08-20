#include<string>
#include<iostream>
#include<assert.h>
#define  _CRT_SECCURE_NO_WARNINGS
using namespace std;


class String
{
public:
	//String 迭代器来访问元素
	//实现：字符指针
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		//第一个元素的位置
		return _data;
	}

	const_iterator begin() const
	{
		//第一个元素的位置
		return _data;
	}

	iterator end()
	{
		//最后一个元素的下一个位置
		return _data + _size;
	}

	const_iterator end() const
	{
		//最后一个元素的下一个位置
		return _data + _size;
	}

	//构造函数
	//不传任何参数，给一个空的字符串
	String(const char* str = "")
		//空间的申请
		:_size(strlen(str))
		, _capacity(_size)
		, _data(new char[_size + 1])
	{
		//内容的拷贝
		strcpy(_data,str);
	}

	//拷贝构造-->复用拷贝的逻辑
	String(const String& str)
		:_size(0)
		, _capacity(0)
		, _data(nullptr)
	{
		//借助构造函数在创建局部对象时，进行空间申请 + 内容拷贝
		//创建临时对象
		String tmp(str._data);
		//通过交换成员的指向，最终达到拷贝构造的目的
		Swap(tmp);
	}

	//交换函数
	void Swap(String& str)
	{
		swap(_size, str._size);
		swap(_capacity, str._capacity);
		swap(_data, str._data);

	}  

	//赋值运算符 --> 复用拷贝
	//借助拷贝构造完成：进行空间申请 + 内容拷贝
	//借助局部对象的析构函数完成当前对象原有资源的释放
	String& operator=(String str)
	{
		Swap(str);
		return *this;
	}

	//析构函数
	~String()
	{
		if (_data)
		{
			delete[] _data;
			_data = nullptr;
			_size = _capacity = 0;
		}
	}

	//获取字符的个数
	size_t size() const
	{
		return _size;
	}

	//获取容量大小
	//const表示任何对象都可以调用这个接口
	size_t capacity() const
	{
		return _capacity;
	}

	//用[]形式来访问元素
	char& operator[](size_t pos)
	{
		assert(pos < _size);
		return _data[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _data[pos];
	}

	//尾插一个字符
	void pushBack(const char& ch)
	{
		//没有空余空间
		if (_size == _capacity)
		{
			//增容: 2倍
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}

		//假如有空余空间
		_data[_size] = ch;
		++_size;
		_data[_size] = '\0';
	}

	void reserve(size_t n)
	{
		//只增加容量
		if (n > _capacity)
		{
			//1、开辟空间
			char* tmp = new char[n + 1]; //把末尾\0的位置预留出来
			//2、拷贝内容
			strcpy(tmp, _data);
			//3、释放原有空间
			delete[] _data;

			//更新成员
			_data = tmp;
			_capacity = n;
		}
	}

	//改变字符个的数，对新增的位置进行填充
	void resize(size_t n, const char& ch = '\0')
	{
		//n > _capacity
		if (n > _capacity)
			//增容
			reserve(n);

		//_size < n <= _capacity：填充字符
		/*for (size_t pos = _size; pos < n; ++pos)
		_data[pos] = ch;*/
		if (n > _size)
			//起始位置，传入的值，大小
			memset(_data + _size, ch, sizeof(char)*(n - _size));

		//n <= _size
		_size = n;
		//给末尾字符添加'\0'表示字符串结束
		_data[_size] = '\0';
	}

	//追加字符串
	void append(const char* str)
	{
		//1、检查容量
		int len = strlen(str);
		if (_size + len > _capacity)
			reserve(_size + len);
		//2、插入 O(n)
		memcpy(_data + _size, str, sizeof(char)*len);
		//strcpy(_data + _size,str)  O(n),会把\0也拷贝过去，效率没有内存拷贝高效
		//3、更新
		_size += len;
		_data[_size] = '\0';
	}

	String& operator+=(const String& str)
	{
		//String对象 str
		append(str._data);
		return *this;
	}

	String& operator+=(const char* str)
	{
		//字符串 str
		append(str);
		return *this;
	}

	String& operator+=(const char ch)
	{
		//字符 ch
		pushBack(ch);
		return *this;
	}

	const char* c_str() const
	{
		return _data;
	}

	void insert(size_t pos,const char& ch)//插入数字，字符
	{
		assert(pos <= _size);//断言
		if (_size == _capacity)//检查容量
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			   reserve(newC);

		}
		//移动元素[pos,size]
        //从后往前              //bug写法：
		size_t end = _size + 1;//  size_t end=_size;
		while (end>pos )       //  while(end>=pos)
		{
			_data[end] = _data[end - 1]; //_data[end]=_data[end+1];  //解决办法： int size_end=_size;
			--end;
		}
		//插入：pos
		_data[pos] = ch;
		//更新size
		++_size;

	}
	/*
	void insert(size_t pos, const char& ptr)//插入字符串操作
	{
		assert(pos<= _size);//断言
		int len = strlen(ptr);
		if (_size+len > _capacity)//检查容量
		{
			reserve(_size + len);
		}
		//移动元素
		//[pos,size]
		size_t end = _size + len;
		while (end>pos+len-1)
		{
			_data[end] = _data[end - len]; 
			--end;
		}
		//插入
	  memcpy(_data + pos, ptr, size_t);
	    //更新
			_size += len;
		_data[_size] = '\0';
	}
	*/
	void erase(size_t pos, size_t len)//删除操作
	{
		assert(pos < _size);//断言
		//要删除的元素个数小于剩余字符的个数
		if (pos + len >= _size)
		{
			_size = pos;
		_data[_size]= '\0';
		}
		else{
			//移动元素
			//从前向后移动[pos+len,size]
			size_t start = pos + len;
			for (; start <= _size; ++start)
			{
				_data[pos++] = _data[start];	
			}
			_size = len;
		}
	}


	size_t find(const char& ch, size_t pos = 0)//查找字符
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] == ch)
				return i;
		}
		return npos;
	}
	/*
	size_t find(const char& str,size_t pos)//查找字符串
	{
		char* ptr = strstr(_data, str);
		if (ptr)
		{
			return ptr - _data;
		}
		return npos;
	}
	*/
private:
	//size：有效字符的个数
	size_t _size;
	//capacity:最大的存放字符的个数
	size_t _capacity;
	char* _data;
	static const size_t npos;
};

const size_t String::npos = -1;
ostream& operator<<(ostream& out,String str)
{
	for (const auto& ch : str)
	{
		out << ch;
		return out;
	}
}



//不能修改操作数的内容
String operator+(const String& str1, const String& str2)
{
	String str = str1;
	str += str2;
	return str;
}

String operator+(const char* str1, const String& str2)
{
	//用str1字符串创建一个String对象，调用构造函数
	String str(str1);
	str += str2;
	return str;
}


String operator+(const char ch, const String& str2)
{
	String str = str2;
	str += ch;
	return str;
}

int main()
{
	string str;
	system("pause");
	return 0;
}
/*String operator+(const char* str1, const String& str2)
{
	String copy(str1);
	copy += str2;
	return copy;
}
*/
/*
String operator+(const char* str1, const String& str2)
{
	String str;
	str += str1;
	str += str2;
	return str;
}
*/
/*
String operator+(const char* ch, const String& str2)
{
	String copy(str2);
	copy +=ch;
	return copy;
}
*/

void printString(const String& str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		cout << str[i] << " ";
		//const char& operator[](size_t pos) const
		//不能修改内容
		//str[i] = i + 'a';


		/*
		String str;//头插

		str.insert(0, 6);//6
		str.insert(1, 7);//67
		str.insert(1,'a');//6a7
		str.append("56789023456789");//6a756789023456789
		*/

		/*String  str("789");
		str.insert(3,'assd');
		str.insert(5, 'qfr');*/
		
		String str;
		str.erase(5, 3);

	}
}



/*
void test(){
string str = "12345";
string::reverse_iterator it = str.rbegin();
while (it != str.rend())
{
cout << "*it" << "";
++it;

}
}

int main()
{
test();
system("pause");
return 0;
}


*/

/*void test()
{
string str;
string copy(str);
string str2("abc");
string substr(str2, 1, 2);
string str3("12345678",5);
string str4(10, 'a');
string str5 = "abcde";//单参构造的隐式类型转换

}

int main()
{
test();
system("pause");
return 0;
}

*/



















