#pragma once
#include "common.h"
/* ���� */
using namespace std;

template<typename T>
struct node  //˫������ڵ�
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
	void bubbleSort(T arr[], int len);  //ð������
	void bubbleSortB(T arr[], int len); //ð�������ж�ǰ׺�Ƿ��Ѿ�������õ�
	void bubbleSortC(T arr[], int len);  //ð������highΪ���һ������˳����Ǹ�  ����ð�����������O(n),���O(nƽ��)
	void mergeSort(T arr[], int low, int high);  //�鲢���� ������O(nlogn)
	void merge(T arr[], int low, int high, int mid);  //�鲢����Ķ��ݺϲ�����
	
	node<T> *createOneNode(T value);
	void selectionSort();  //ѡ������
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
	//��ӡ�������Ľ��
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
	//��ӡ�������Ľ��
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
	int last;  //���һ��Ԫ���±�
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
		low = 0;  //�ٴ�0��ʼ
	}
	//��ӡ�������Ľ��
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
	if (high - low < 2)  //��ʱֻ��һ��Ԫ��
	{
		return;
	}
	int mid = (int)((high + low) / 2);
	mergeSort(arr, low, mid);
	mergeSort(arr, mid, high);
	merge(arr, low, high, mid);
}

template<typename T>
void sorting<T>::merge(T arr[], int low, int high, int mid)   //high���ڱ�
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
		if ( (j<lb) && (lc <= k || arrP[j] <= arr[mid + k - low]) )  //��·�߼��� ��||�����Ϊtrue�Ļ����Ҳ�Ͳ����ж��������Բ����������� ��&&�����Ϊfalse����Ҳ�����жϺ�����
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
	//ʵ���ϵ�arrP�ù�֮����ΪC����������arr�У����ԾͿ��Խ�����,����ע�͵Ŀ����پ���
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
node<T> * sorting<T>::createOneNode(T value)  //����һ���½ڵ�
{
	node<T> *p = (node<T> *)malloc(sizeof(node<T>));
	if (p == nullptr)
	{
		cout << "���붯̬�ڴ�ʧ��" << endl;
		return nullptr;
	}
	p->pre = nullptr;
	p->data = value;
	p->next = nullptr;
	return p;
}

template<typename T>
inline void sorting<T>::selectionSort()  //ѡ��������ʵ��,����O(nƽ��)
{
	/* ��ʼ������ */
	//��ʼ���ڵ�
	node<T> *head, *p, *tmp,*trail;
	tmp = createOneNode(NULL);
	trail = createOneNode(NULL);
	p = tmp;
	head = tmp;
	int length = 10, oldlength = 10;
	for (int i=length; i>=1; i--) //β�巨��ʼ��
	{
		tmp = createOneNode(i);
		tmp->pre = p;
		p->next = tmp;
		p = tmp;
	}
	p->next = trail;
	trail->pre = p;
	cout << "��ʼ�����" << endl;

	cout << "����ǰ ";
	tmp = head->next;
	for (int i = length; i >= 1; i--)
	{
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;

	//����������ʵ��
	while (length > 1)
	{
		//���뵽ǰ��
		tmp = selectionSortMax(head->next, length);
		//�ѵ�ǰ���ڵ���ǰ�������ԶϿ�
		removeNode(tmp);
		//��tmp���뵽trailǰ��
		tmp->next = trail;
		tmp->pre = trail->pre;
		trail->pre->next = tmp;
		trail->pre = tmp;
		//��ǰ��
		trail = trail->pre;
		length--;
	}

	cout << "����� ";
	tmp = head->next;
	while (tmp->next != nullptr)
	{
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;

	//ɾ��ָ��
	delete head;
	head = nullptr;
	delete p;
	p = nullptr;
	delete tmp;
	tmp = nullptr;
}

template<typename T>
node<T>* sorting<T>::selectionSortMax(node<T>* p, int n)  //ѡ�����ֵ
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
void sorting<T>::removeNode(node<T>* p)  //ɾ���ڵ�
{
	p->next->pre = p->pre;
	p->pre->next = p->next;
}

