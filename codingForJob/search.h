#pragma once
#include "common.h"
#include "fibonacci.h"

using namespace std;

/* 搜索 */
template<typename T>
class searching
{
public:
	searching();
	int simpleSearch(T arr[], int low, int high, int length, T value); //O(n)
	//接下来的四个查找，如果arr里面没有value的话，就会返回一个负数
	int binarySearchLow(T arr[], int low, int high, int length, T value);    //O(1.5logn)
	int binarySearchHigh(T arr[], int low, int high, int length, T value);  //O(1.5logn)
	int fibSearch(T arr[], int low, int high, int length, T value);  //O(1.44logn)
	int interpolationSearch(T arr[], int low, int high, int length, T value);  //插值查找  O(loglogn)
	//接下来这个查找，如果arr中存在value，则返回下标，否则的话，就返回不大于value的秩最大的那个数的下标
	int binarySearch(T arr[], int low, int high, int length, T value);  //O(1.5logn)
	~searching();

private:

};

template<typename T>
searching<T>::searching()
{
}

template<typename T>
int searching<T>::simpleSearch(T arr[], int low, int high, int length, T value)  //这里要注意的是，high为最后一个元素的右边，因此区间为[low, high)，左闭右开的
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	while (high > low)
	{
		if (arr[--high] == value)
		{
			return high;
		}
	}
	return -3;  //搜不到
}

//有序序列二分查找，这个是最好情况和最坏情况差别大的版本,如果arr里面没有value的话，就会返回一个负数
template<typename T>
int searching<T>::binarySearchLow(T arr[], int low, int high, int length, T value)  //复杂度O(1.5logn) 这里要注意的是，high为最后一个元素的右边，因此区间为[low, high)，左闭右开的
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	while (high > low)
	{
		int mid = (high + low) >> 1;
		if (value < arr[mid])
		{
			high = mid;
		}
		else if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -3;
}

//有序序列二分查找，这个是最好情况和最坏情况无差别的版本,如果arr里面没有value的话，就会返回一个负数
template<typename T>
inline int searching<T>::binarySearchHigh(T arr[], int low, int high, int length, T value)
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	while (1 < high - low)
	{
		int mid = (high + low) >> 1;
		(value < arr[mid]) ? (high = mid) : (low = mid);
	}
	return (value == arr[low]) ? low : -3;
}

//有序序列fib查找,如果arr里面没有value的话，就会返回一个负数
template<typename T>
int searching<T>::fibSearch(T arr[], int low, int high, int length, T value)  //这里要注意的是，high为最后一个元素的右边，因此区间为[low, high)，左闭右开的
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	//寻找到一个fib数列
	fibonacci fib;
	int k = 1;  //由以上得知high-low>=1
	while ((high - low) > fib.getFib(k) - 1)
	{
		k++;
	}
	k--;  //因为此时getFib得到的fibVector一共有k个数，最后一个下标为k-1，故k应该减一
	//扩展tmp
	T *tmp = new T[fib.fibVector[k] - 1 + low];  //别忘了high-low=fib(k)-1，所以要加上前面的low，所以tmp的长度为fib.getFib(k) - 1 + low
	for (int i = 0; i < fib.fibVector[k] - 1 + low; i++)
	{
		if (i < length)
		{
			tmp[i] = arr[i];
		}
		else
		{
			tmp[i] = arr[length - 1];
		}
	}
	while (high > low)
	{
		int mid = low + fib.fibVector[k - 1] - 1;
		if (value < tmp[mid])
		{
			high = mid;
			k = k - 1;
		}
		else if(tmp[mid] < value)
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if (mid < high)
			{
				delete[] tmp;
				return mid;
			}
			else
			{
				delete[] tmp;
				return -3;
			}
		}
	}
	delete[] tmp;
	return -4;
}

template<typename T>
inline int searching<T>::interpolationSearch(T arr[], int low, int high, int length, T value)  //插值查找
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	//在插值查找里high表示最后一个元素下标
	high = high - 1;
	while (high > low)
	{
		int mid = (int)( (value - arr[low])*(high - low) / (arr[high] - arr[low]) + low );
		if (mid < low)
		{
			mid = low;
		}
		(value < arr[mid]) ? (high = mid) : (low = mid + 1);
	}
	return --low;
}

//二分查找，版本binarySearchHigh的改进，如果arr中存在value，则返回下标，否则的话，就返回不大于value的秩最大的那个数的下标
template<typename T>
inline int searching<T>::binarySearch(T arr[], int low, int high, int length, T value)
{
	if (high > length)
	{
		cout << "搜索范围大于长度了" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	while (low < high)
	{
		int mid = (low + high) >> 1;
		(value < arr[mid]) ? (high = mid) : (low = mid + 1);
	}
	return --low;
}

template<typename T>
searching<T>::~searching()
{
}