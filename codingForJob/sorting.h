#pragma once
#include "common.h"
/* 排序 */
using namespace std;

template<typename T>
struct node  //双向链表节点
{
	struct node *pre;
	T data;
	struct node *next;
};

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
	
	node<T> *createOneNode(T value);
	void selectionSort();  //选择排序
	node<T> *selectionSortMax(node<T> *p, int n);
	void removeNode(node<T> *p);
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

template<typename T>
node<T> * sorting<T>::createOneNode(T value)  //创造一个新节点
{
	node<T> *p = (node<T> *)malloc(sizeof(node<T>));
	if (p == nullptr)
	{
		cout << "申请动态内存失败" << endl;
		return nullptr;
	}
	p->pre = nullptr;
	p->data = value;
	p->next = nullptr;
	return p;
}

template<typename T>
inline void sorting<T>::selectionSort()  //选择排序主实现,最好最坏O(n平方)
{
	/* 初始化链表 */
	//初始化节点
	node<T> *head, *p, *tmp,*trail;
	tmp = createOneNode(NULL);
	trail = createOneNode(NULL);
	p = tmp;
	head = tmp;
	int length = 10, oldlength = 10;
	for (int i=length; i>=1; i--) //尾插法初始化
	{
		tmp = createOneNode(i);
		tmp->pre = p;
		p->next = tmp;
		p = tmp;
	}
	p->next = trail;
	trail->pre = p;
	cout << "初始化完成" << endl;

	cout << "排序前 ";
	tmp = head->next;
	for (int i = length; i >= 1; i--)
	{
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;

	//排序主功能实现
	while (length > 1)
	{
		//插入到前面
		tmp = selectionSortMax(head->next, length);
		//把当前最大节点与前后连接性断开
		removeNode(tmp);
		//把tmp插入到trail前面
		tmp->next = trail;
		tmp->pre = trail->pre;
		trail->pre->next = tmp;
		trail->pre = tmp;
		//向前进
		trail = trail->pre;
		length--;
	}

	cout << "排序后 ";
	tmp = head->next;
	while (tmp->next != nullptr)
	{
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;

	//删除指针
	delete head;
	head = nullptr;
	delete p;
	p = nullptr;
	delete tmp;
	tmp = nullptr;
}

template<typename T>
node<T>* sorting<T>::selectionSortMax(node<T>* p, int n)  //选择最大值
{
	node<T> *tmp = p;
	while (n > 1)
	{
		if (p->data <= p->next->data)
		{
			tmp = p;
		}
		p = p->next;
		n--;
	}
	return tmp;
}

template<typename T>
void sorting<T>::removeNode(node<T>* p)  //删除节点
{
	p->next->pre = p->pre;
	p->pre->next = p->next;
}

