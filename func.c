#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

//C语言标准库函数strcpy的一种典型的工业级的最简实现。 
//返回值：目标串的地址。
//对于出现异常的情况ANSI-C99标准并未定义，故由实现者决定返回值，通常为NULL。
//参数：des为目标字符串，source为原字符串。

//使用库函数-->assert();
char* m_strcpy(char* dst, const char* src) {

	char* r = dst;

	assert((dst != NULL) && (src != NULL));

	while ((*src) != '\0') 
	{
		*dst++ = *src++;
	}

	return dst;
}


//memcpy:内存拷贝函数
void *m_memcpy(void *dst, const void *src, int n)
{
	assert((dst != NULL) && (src != NULL));
	
	char * pdst = (char *)dst;
	char * psrc = (char *)src;
	//防止内存重叠
	if (pdst > psrc && pdst < psrc + n)
	{
		pdst = pdst + n - 1;
		psrc = psrc + n - 1;
		while (n--) 
		{
			*pdst-- = *psrc--;
		}
	}
	else
	{
		while (n--) 
		{
			*pdst++ = *psrc++;
		}
	}
	return dst;
}


//strncpy:在strcpy();基础上增加了拷贝字节数-->更加安全；
char* m_strncpy(char* dest, const char* src, size_t n)

{
	assert((dest != NULL) && (src != NULL));
	char *tmp = dest;
    size_t i = 0;
	/*while (n--) 
	{
		*tmp++ = *src++;
	}*/
	while ((i++ < n) && (*tmp++ = *src++) != '\0');
	return dest;

}



int main()
{
	char str[50] = "1234567890";
	char *str1= "abcde";

	//m_strncpy(str, str1, 5);
	m_memcpy(str, str1, 3);//注意n>sizeof(str1);发生越界错误
	//m_strcpy(str, str1);
	
	printf("%s\n", str);
	system("pause");
	return 0;
}
