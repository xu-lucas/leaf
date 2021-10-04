//线性非比较排序：
//	1.计数排序-->O(n+k)-O(n+k),O(k)-----稳定
//	2.基数排序-->O(n*k)-O(n*k),O(n+k)---稳定
//  3.桶排序  -->O(n+k)-O(n^2),O(n+k)---稳定

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

//计数排序
void countsort(vector<int>& v)
{
	if (v.size() < 2) return;
	//找出传入数组范围
	int max = *(max_element(v.begin(), v.end()));
	int min = *(min_element(v.begin(), v.end()));
	//定义计数数组
	vector<int> v_count(max - min + 1, 0);
	for (int i = 0; i < v.size(); ++i)
	{
		v_count[v[i] - min]++;
	}
	int idx = 0;
	for (int j = 0; j <v_count.size(); ++j) {
		int n = v_count[j];
		while (n--) {
			v[idx++] = j + min;
		}
	}
}

//桶排序
void bucketsort(vector<int>& v,int bkcount) 
{
	if (v.size() < 2) return;
	
	//找出数组中max,min;
	int max = *(max_element(v.begin(), v.end()));
	int min = *(min_element(v.begin(), v.end()));
	
	//将待排序的元素分入对应桶中
	vector<vector<int>>bucket(bkcount);
	int bksize = ceil((double)(max - min + 1) / bkcount);
	for (int i = 0; i < v.size(); ++i) 
	{
		int bkIdx = (v[i] - min) / bksize;
		bucket[bkIdx].emplace_back(v[i]);
	}

	//对桶中的元素进行排序
    //将桶中排序好的元素进行插入数组；
	int idx = 0;
	for (int i = 0; i < bucket.size(); ++i)
	{
		sort(bucket[i].begin(),bucket[i].end());
		//一般sort排序是快排
		for (auto& val : bucket[i]) 
		{
			v[idx++] = val;
		}
	}
}


//基数排序
void RadixSort(vector<int>& v) {
	//最大位数
	int k = 0;
	for (int i = 0; i < v.size(); ++i)
		k = max(int(log(v[i])) + 1, k);
	for (int i = 0; i < k; ++i) {
		//十进制
		vector<vector<int>>radix(10);
		//分配
		for (int j = 0; j < v.size(); ++j) {
			int index = int(v[j] / pow(10, i)) % 10;
			radix[index].push_back(v[j]);
		}
		int index = 0;
		//收集
		for (int j = 0; j < radix.size(); ++j) {
			for (auto& val : radix[j]) {
				v[index++] = val;
			}
		}
	}
}


int main() 
{
	vector<int> v1 = {1, 9, 21 , 23, 14, 27, 35, 44};
	//ountsort(v1);
	//bucketsort(v1, v1.size() / 2);
	RadixSort(v1);
	for (auto &it : v1) 
	{
		cout << it << " ";
		++it;
	}
	cout << endl;
	return 0;
}








