#include<iostream>
#include<mutex>
using namespace std;

//只能在堆上创建对象
class Heapobj 
{
public:
	static Heapobj* creatObj() 
	{
		return new Heapobj();
	}
private:
	Heapobj() {}
	Heapobj(const Heapobj& obj) = delete;
	Heapobj& operator=(const Heapobj& obj) = delete;
};


//只能在栈上创建对象
class Stackobj 
{
public:
	static Stackobj creatobj() 
	{
		return Stackobj();
	}
private:
	Stackobj() {}
};


//不能被拷贝
class Nocopy 
{
private:
	Nocopy(const Nocopy & obj) = delete;
	Nocopy & operator=(const Nocopy & obj) = delete;
};

class A final  
{
};


//单例模式：
//饿汉模式

//饿汉式
class Singleton
{
public:
	//获取唯一实例的静态方法
	static Singleton* getSingleton()
	{
		return &_singleton;
	}

private:
	//私有构造
	Singleton() {};
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

	static Singleton _singleton;
};
Singleton Singleton::_singleton;

//懒汉式
class Singleton
{
public:
	static Singleton* getSingleton()
	{
		if (_singleton == nullptr)
		{
			_mutex.lock();
			if (_singleton == nullptr)
			{
				_singleton = new Singleton();
			}
			_mutex.unlock();
		}
		return _singleton;
	}

private:
	Singleton() {};
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&)=delete;

	static mutex _mutex;//互斥锁
	static Singleton* _singleton;
};
Singleton* Singleton::_singleton = nullptr;
mutex Singleton::_mutex;



void *memcpy(void *dst, const void *src, unsigned int n)
{
	if (dst == NULL || src == NULL || n == 0)
		return NULL;

	char * pdst = (char *)dst;
	char * psrc = (char *)src;

	if (pdst > psrc && pdst < psrc + n)
	{
		pdst = pdst + n - 1;
		psrc = psrc + n - 1;
		while (n--)
			*pdst-- = *psrc--;
	}
	else
	{
		while (n--)
			*pdst++ = *psrc++;
	}
	return dst;
}




