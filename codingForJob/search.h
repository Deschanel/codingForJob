#pragma once
#include "common.h"
#include "fibonacci.h"

using namespace std;

/* ���� */
template<typename T>
class searching
{
public:
	searching();
	int simpleSearch(T arr[], int low, int high, int length, T value); //O(n)
	//���������ĸ����ң����arr����û��value�Ļ����ͻ᷵��һ������
	int binarySearchLow(T arr[], int low, int high, int length, T value);    //O(1.5logn)
	int binarySearchHigh(T arr[], int low, int high, int length, T value);  //O(1.5logn)
	int fibSearch(T arr[], int low, int high, int length, T value);  //O(1.44logn)
	int interpolationSearch(T arr[], int low, int high, int length, T value);  //��ֵ����  O(loglogn)
	//������������ң����arr�д���value���򷵻��±꣬����Ļ����ͷ��ز�����value���������Ǹ������±�
	int binarySearch(T arr[], int low, int high, int length, T value);  //O(1.5logn)
	~searching();

private:

};

template<typename T>
searching<T>::searching()
{
}

template<typename T>
int searching<T>::simpleSearch(T arr[], int low, int high, int length, T value)  //����Ҫע����ǣ�highΪ���һ��Ԫ�ص��ұߣ��������Ϊ[low, high)������ҿ���
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
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
	return -3;  //�Ѳ���
}

//�������ж��ֲ��ң����������������������İ汾,���arr����û��value�Ļ����ͻ᷵��һ������
template<typename T>
int searching<T>::binarySearchLow(T arr[], int low, int high, int length, T value)  //���Ӷ�O(1.5logn) ����Ҫע����ǣ�highΪ���һ��Ԫ�ص��ұߣ��������Ϊ[low, high)������ҿ���
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
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

//�������ж��ֲ��ң�������������������޲��İ汾,���arr����û��value�Ļ����ͻ᷵��һ������
template<typename T>
inline int searching<T>::binarySearchHigh(T arr[], int low, int high, int length, T value)
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
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

//��������fib����,���arr����û��value�Ļ����ͻ᷵��һ������
template<typename T>
int searching<T>::fibSearch(T arr[], int low, int high, int length, T value)  //����Ҫע����ǣ�highΪ���һ��Ԫ�ص��ұߣ��������Ϊ[low, high)������ҿ���
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	//Ѱ�ҵ�һ��fib����
	fibonacci fib;
	int k = 1;  //�����ϵ�֪high-low>=1
	while ((high - low) > fib.getFib(k) - 1)
	{
		k++;
	}
	k--;  //��Ϊ��ʱgetFib�õ���fibVectorһ����k���������һ���±�Ϊk-1����kӦ�ü�һ
	//��չtmp
	T *tmp = new T[fib.fibVector[k] - 1 + low];  //������high-low=fib(k)-1������Ҫ����ǰ���low������tmp�ĳ���Ϊfib.getFib(k) - 1 + low
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
inline int searching<T>::interpolationSearch(T arr[], int low, int high, int length, T value)  //��ֵ����
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
		return -1;
	}
	if (low < 0)
	{
		cout << "what the fuck!" << endl;
		return -2;
	}
	//�ڲ�ֵ������high��ʾ���һ��Ԫ���±�
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

//���ֲ��ң��汾binarySearchHigh�ĸĽ������arr�д���value���򷵻��±꣬����Ļ����ͷ��ز�����value���������Ǹ������±�
template<typename T>
inline int searching<T>::binarySearch(T arr[], int low, int high, int length, T value)
{
	if (high > length)
	{
		cout << "������Χ���ڳ�����" << endl;
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