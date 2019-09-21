#pragma once
#include "common.h"
/* 排序 */
using namespace std;
template <typename T>
class sorting
{
public:
	sorting()
	{}
	void bubbleSort(T arr[], int len);  //冒泡排序
	void bubbleSortB(T arr[], int len); //冒泡排序，判断前缀是否已经是排序好的
	void bubbleSortC(T arr[], int len);  //冒泡排序，high为最后一个交换顺序的那个  所有冒泡排序最好是O(n),最差O(n平方)
	void mergeSort(T arr[], int low, int high);  //归并排序 最好最差O(nlogn)
	void merge(T arr[], int low, int high, int mid);  //归并排序的二份合并操作
	~sorting(){}
};

template<typename T>
void sorting<T>::bubbleSort(T arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	//打印出排序后的结果
	cout << "the result of bubble sort is: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << "bubble sort end" << endl;
}

template<typename T>
void sorting<T>::bubbleSortB(T arr[], int len)
{
	bool sorted = false;
	int i=0;
	while (!sorted)
	{
		sorted = true;
		for (int j=0; j<len-1-i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				sorted = false;
			}
		}
		i++;
	}
	//打印出排序后的结果
	cout << endl;
	cout << "the result of bubble B sort is: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << "bubble sort B end" << endl;
}

template<typename T>
void sorting<T>::bubbleSortC(T arr[], int len)   //int arr[] = { 2, 5, 9, 3, 6, 2 }
{
	if (len == 0)
	{
		return;
	}
	int last;  //最后一个元素下标
	int low = 0, high = len - 1;
	while (low < high)
	{
		last = low;
		while (low < high)
		{
			if (arr[low] > arr[low + 1])
			{
				swap(arr[low], arr[low + 1]);
				last = low;
			}
			low += 1;
		}
		high = last;
		low = 0;  //再从0开始
	}
	//打印出排序后的结果
	cout << endl;
	cout << "the result of bubble C sort is: ";
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << "bubble sort C end" << endl;
}

template<typename T>
void sorting<T>::mergeSort(T arr[], int low, int high)
{
	if (high - low < 2)  //此时只有一个元素
	{
		return;
	}
	int mid = (int)((high + low) / 2);
	mergeSort(arr, low, mid);
	mergeSort(arr, mid, high);
	merge(arr, low, high, mid);
}

template<typename T>
void sorting<T>::merge(T arr[], int low, int high, int mid)   //high是哨兵
{
	int lb = mid - low;
	int lc = high - mid;
	T *arrP = new int[lb];
	for (int i=0; i<lb; i++)
	{
		arrP[i] = arr[i];
	}
	int i = 0, j = 0, k = 0;
	/*while (k < lc || j < lb)
	{
		if ( (j<lb) && (lc <= k || arrP[j] <= arr[mid + k - low]) )  //短路逻辑， 当||的左侧为true的话，右侧就不会判断力，所以不会存在溢出， 当&&的左侧为false，那也不用判断后面了
		{
			arr[i] = arrP[j];
			j++;
		}
		if ((k < lc) && (lb <= j || arr[mid + k - low] < arrP[j]))
		{
			arr[i] = arr[mid + k - low];
			k++;
		}
		i++;
	}*/
	//实际上当arrP用光之后，因为C子向量就在arr中，所以就可以结束了,所以注释的可以再精简
	while (j < lb)
	{
		if (lc <= k || arrP[j] <= arr[mid + k - low])
		{
			arr[i] = arrP[j];
			j++;
		}
		if ((k < lc) && (arr[mid + k - low] < arrP[j]))
		{
			arr[i] = arr[mid + k - low];
			k++;
		}
		i++;
	}
	delete[] arrP;
}

