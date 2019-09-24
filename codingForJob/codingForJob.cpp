// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include "LCS.h"
#include "fibonacci.h"
#include "sorting.h"
#include "search.h"

using namespace std;

//查找lcs的最大长度并打印
void getLCS()
{
	string s1 = "abcde";
	string s2 = "aceaaaa";
	LCS<string> l(s1, s2);
}

//斐波那契数列，用迭代实现.
void getFib(int n)
{
	fibonacci fib;
	cout << fib.getFib(n);
}

//冒泡排序--多版本--向量
void bubbleSort()
{
	int arr[] = {2, 5, 9, 3, 6, 2};
	int len = sizeof(arr) / sizeof(int);
	sorting<int> s;
	s.bubbleSort(arr, len);
	s.bubbleSortB(arr, len);
	s.bubbleSortC(arr, len);
}

//斐波那契查找--向量
void fibSearch()
{
	int arr[] = { 2, 3, 5, 7, 8, 9, 10, 13, 15 };
	searching<int> s;
	cout << s.fibSearch(arr, 5, 9, 9, 13);
}

//选择查找--链表
void selectionSort()
{
	sorting<int> s;
	s.selectionSort();
}

void insertionSort()
{
	sorting<int> s;
	s.insertionSort();
}

int main()
{
	//getLCS();
	//getFib(12);
	//bubbleSort();
	//fibSearch();
	insertionSort();
	return 1;
}