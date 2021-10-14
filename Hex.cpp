#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<cmath>
using namespace std;

//二进制转换到十进制
int b2_int10(string str) {
	int sum = 0, t;
	for (int i = 0; i < str.size(); i++) {
		t = str[i] - '0';
		sum = 2 * sum + t;
	}
	return sum;
}

//十进制转换二进制
int b10_int2(int num)
{
	int mod, res = 0, k = 1;
	while (num != 0)
	{
		mod = num % 2;
		num = num / 2;
		res = res + mod * k;
		k = k * 10;
	}
	return res;
}

//十进制转换到十六进制
void b10_int16(int num) 
{
	vector<int> v;
	char s[] = "0123456789ABCDEF";

	     if (num == 0) {
		    v.push_back(0);
	     }
			
		while (num != 0)
		{
			v.push_back(num % 16);
			num /= 16;
		}

		vector<int>::reverse_iterator rit;
		for (rit = v.rbegin(); rit != v.rend(); rit++)
		{
			cout << s[*rit];
		}
}

//十六进制转换到十进制
void b16_int10(string& str) 
{
	int n = str.size();
	int sum = 0;
	for (int i = n-1; i >= 0; i--)//从十六进制个位开始，每位都转换成十进制  
	{
		if (str[i] >= '0'&&str[i] <= '9')//数字字符的转换  
		{
			sum += (str[i] - 48)*pow(16, n - i - 1);
		}
		else if (str[i] >= 'A'&& str[i] <= 'F')//字母字符的转换  
		{
			sum += (str[i] - 55)*pow(16, n - i - 1);
		}
		else if (str[i] >= 'a'&& str[i] <= 'f')//字母字符的转换  
		{
			sum += (str[i] - 87)*pow(16, n - i - 1);
		}
	}
	cout << sum;
}






int main() {
	//cout << b2_int10("111");
	//b10_int16(19);
	string str;
	str = "13";
	b16_int10(str);
	return 0;
	}

