//堆排序:<1> 数组实现
//       <2> 优先级队列实现
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void adjust_max(vector<int>& v, int root, int size) 
{
	int temp =v[root];
	for (int left = 2 * root + 1; left < size; left = 2 * left+1)
	{
		if (left + 1 < size && v[left] < v[left + 1]) 
		{
			left++;
		}
		if (v[left] > temp) 
		{
			v[root] = v[left];
			root = left;
		}
		else 
		{
			break;
		}
	}
	v[root] = temp;
}

void adjust_min(vector<int>& v, int root, int size)
{
	int temp = v[root];
	for (int left = 2 * root + 1; left < size; left = 2 * left + 1)
	{
		if (left + 1 < size && v[left] > v[left + 1])
		{
			left++;
		}
		if (v[left] < temp)
		{
			v[root] = v[left];
			root = left;
		}
		else
		{
			break;
		}
	}
	v[root] = temp;
}
void heapsort(vector<int>& v) 
{
	//大小堆->建堆
	int size = v.size();
	//从最后一个非叶子节点开始建堆
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		//adjust_max(v, i, size);
		adjust_min(v, i, size);
	}
	//堆排序-->调整的不同-->排序顺序不同
	for (int i = v.size() - 1; i>0; --i) 
	{
		swap(v[0], v[i]);
		//adjust_max(v,0,i);
		adjust_min(v, 0, i);
	}
}

//优先级队列实现-->大小堆
//大根堆->升序
void heapsort_max(vector<int>& v) 
{
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 0; i < v.size(); ++i) 
	{
		q.push(v[i]);
	}
	for (int j = 0; j < v.size(); ++j) 
	{
		v[j] = q.top();
		q.pop();
	}
}

//小根堆->降序
void heapsort_min(vector<int>& v)
{
	priority_queue<int> q;
	for (int i = 0; i < v.size(); ++i)
	{
		q.push(v[i]);
	}
	for (int j = 0; j < v.size(); ++j)
	{
		v[j] = q.top();
		q.pop();
	}
}
int main() 
{
	vector<int> v1;
	v1.emplace_back(49);
	v1.emplace_back(38);
	v1.emplace_back(65);
	v1.emplace_back(97);
	v1.emplace_back(76);
	v1.emplace_back(13);
	v1.emplace_back(27);
	heapsort(v1);
	for (auto &it : v1)
	{
		cout << it << " ";
		++it;
	}
	cout << endl;
	return 0;
}

