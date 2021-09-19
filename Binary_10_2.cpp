#include<iostream>
using namespace std;
#include<string>
int b2_int10(string str) {
	int sum = 0, t;
	for (int i = 0; i < str.size(); i++) {
		t = str[i] - '0';
		sum = 2 * sum + t;
	}
	return sum;
}
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
int  main() {
	//cout << b2_int10("111");
	cout << b10_int2(17);
	return 0;
}
