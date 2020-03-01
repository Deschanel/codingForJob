#include <iostream>
#include <vector>
using namespace std;

//ð������--һ�����
void bubbleSort_1(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	for (int i=0; i<n; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (v[j + 1] < v[j])
			{
				swap(v[j + 1], v[j]);
			}
		}
	}
}
//ð������������ʱ��Ĵ���
void bubbleSort_2(vector<int> &v)
{
	//��һ������������õģ����߾���������ɨ���ܴﵽ�ź�����ô�Ͳ�����������ˣ��Ϳ��Է���
	//���������ԣ���˵��û�ź�
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	bool flag = false;
	for (int i = 0; i < n; ++i)
	{
		flag = false;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (v[j + 1] < v[j])
			{
				flag = true;   //���������
				swap(v[j + 1], v[j]);
			}
		}
		if (!flag)   //�������������
		{
			return;
		}
	}
}

//ѡ������
void selectionSort(vector<int> &v)
{
	//������δ�����������ҵ���С����Ԫ�أ���ŵ��������е��ڱ�λ�ã�
	//Ȼ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�
	//Ȼ��ŵ����������е�ĩβ���Դ����ƣ�ֱ������Ԫ�ؾ�������ϡ�
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	for (int i=0; i<n; ++i)
	{
		int index = i;  //ʣ��Ԫ����Сֵ���±�
		for (int j = i; j<n; ++j)
		{
			if (v[j] < v[index])
			{
				index = j;
			}
		}
		if (i != index)
		{
			swap(v[i], v[index]);
		}
	}
}

//��������
void insertionSort(vector<int> &v)
{
	//ͨ�������������У�����δ�������ݣ��������������дӺ���ǰɨ�裬�ҵ���Ӧλ�ò����롣
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	for (int i=0; i<n-1; ++i)
	{
		int cur = v[i + 1];  //��ǰҪ�����Ԫ��,�±�Ϊi+1,ǰ��һֱ���±�i���Ѿ��ź�����
		int j = i;  //�±�
		while (j >= 0 && v[j] > cur)
		{
			v[j + 1] = v[j];
			--j;
		}
		//��ʱ�ҵ��˵�һ������С��
		v[j + 1] = cur;
	}
}

//ϣ������
void shellSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	int gap = n / 2;
	while (gap > 0)
	{
		for (int i=gap; i<n; ++i)
		{
			int tmp = v[i];
			int j = i - gap;
			while (j >= 0 && v[j] > tmp)
			{
				v[j + gap] = v[j];
				j -= gap;
			}
			v[j + gap] = tmp;
		}
		gap /= 2;
	}
}

//�鲢����
void mergeSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	vector<int> l, r;
	l.assign(v.begin(), v.begin() + n / 2);
	r.assign(v.begin() + n / 2, v.end());
	mergeSort(l);
	mergeSort(r);
	int i = 0, j = 0, index = 0;
	while (i < l.size() || j < r.size())
	{
		if (i < l.size() && j < r.size())
		{
			if (l[i] <= r[j])  //�����ȵĻ�������߻�������ߣ�ά���ȶ�
			{
				v[index] = l[i];
				++i;
			}
			else
			{
				v[index] = r[j];
				++j;
			}
		}
		else if (j < r.size())
		{
			v[index] = r[j];
			++j;
		}
		else
		{
			v[index] = l[i];
			++i;
		}
		++index;
	}
}

int quickSort_partition(vector<int>& v, int start, int end)  //�ָ�
{
	if (v.size() <= 1 || start >= end || start < 0 || end >= v.size())
	{
		return;
	}
	int com = v[start];
	swap(v[start], v[end]);  //���Ƚϵ����ŵ�����ڴ�������ڽ���������ʹ�ñȽ��������ڱ����Ҳ�
	int shaobing = start - 1;
	for (int i=start; i<=end; ++i)
	{
		if (v[i] < com)  //ֻ��Ҫ��С�ڵķŵ��ڱ��Ǹ�ȥ
		{
			++shaobing;
			if (shaobing != i)
			{
				swap(v[shaobing], v[i]);
			}
		}
	}
	//����forѭ����ɺ��±�shaobing�����Լ�������С�ڷָ�����Ԫ��
	//���Դ�ʱ����С�ڷָ����ĸ�����Ҳ������Ҫshaobing+1���ٷ��أ���Ϊ�±��Ǵ�0��ʼ��,��shaobingһ����shaobing+1��
	++shaobing;
	swap(v[shaobing], v[end]);   //���ָ�������������ʱ�ָ��������ڱ���λ��,Ҳ���Ǵ�ʱ�ָ������±�Ϊshaobing
	return shaobing;
}
void quickSort_item(vector<int>& v, int start, int end)
{
	if (v.size() <= 1 || start >= end || start < 0 || end >= v.size())
	{
		return;
	}
	//�ָ������ڵ�λ��
	int n = quickSort_partition(v, start, end);  
	if (n > start)  //�ָ���֮ǰ��
	{
		quickSort_item(v, start, n - 1);
	}
	if (n < end)  //�ָ���֮���,��Ϊn�Ƿָ������ڵ��±�
	{
		quickSort_item(v, n + 1, end);
	}
}
//��������
void quickSort(vector<int>& v)
{
	if (v.size() <= 1)
	{
		return;
	}
	quickSort_item(v, 0, v.size() - 1);
}

//�����󶥶�
void adjustHeap(vector<int> &v, int i, int n)
{
	//���±�i��Ԫ�غ��������������ɵĴ󶥶ѽ��е���
	for (int k = i * 2 + 1; k < n; k = k * 2 + 1)  //k*2+1Ϊ��ǰ�ڵ����ڵ�
	{
		if (k + 1 < n && v[k] < v[k + 1])  //��ڵ�ֵС���ҽڵ��ֵ
		{
			++k;  //ָ���ҽڵ�
		}
		if (v[k] > v[i])  //��ʱ��iΪ���ڵ�Ĵ󶥶ѣ����ڵ��ֵС��������ӽڵ��ֵ
		{
			swap(v[k], v[i]);  //�����ڵ�ֵ
			i = k;  //��ʱ���ڵ㱻����ȥ����k�������i=k����ʱ����ѭ���������±�Ϊi(ԭ����k)��,������ȥ���Ǹ�ֵ�������������Ƿ�����
		}
		else  //���ڵ������ô��ֱ��break����ʱ��������������ĺ��ӻ����������ĺ����Ǳȸ��ڵ����Ϊ�Ǵ��µ��ϱ�����
		{
			break;
		}
	}
}
//������
void heapSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	//����󶥶�
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; --i)  //�����з�Ҷ�ӽڵ�������ϣ�����������е����󶥶ѽṹ
	{
		adjustHeap(v, i, n); 
	}
	//for��ȥ��͵������ˣ���ʱ���Ԫ���ڸ��ڵ�
	for (int j = n - 1; j >= 0; --j)
	{
		swap(v[j], v[0]);  //�����Ԫ��Ū��ĩβ,ĩβԪ���ڸ��ڵ㴦�����������Ҫ������
		adjustHeap(v, 0, j);  //��Ϊ��ʱ���Ԫ���Ѿ�������ĩβ���֣����ֻ��Ҫ����ʣ�µ�j�����ɣ����ڵ㻹�ǵ�0��Ԫ��
	}
}

//��������
void countingSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	int mi = v[0], ma = v[0];  //��С���ֵ
	for (int i : v)
	{
		if (i < mi)
		{
			mi = i;
		}
		if (i > ma)
		{
			ma = i;
		}
	}
	vector<int> tmp(ma - mi + 1, 0); //������������
	for (int i : v)  //�����Ǽ�¼ÿ�����ֳ��ֵĴ���
	{
		tmp[i - mi]++;
	}
	//Ȼ�󽫳��ֵĴ����ۼ�
	int sum = 0;
	for (int i = 0; i < tmp.size(); ++i)
	{
		sum += tmp[i];
		tmp[i] = sum;
	}
	//�����������--Ϊ�˱����ȶ���
	vector<int> result(v.size(), 0);
	for (int i = v.size() - 1; i >= 0; --i)
	{
		//v[i] - mi��ʾ��ǰ�ĳɼ��ڼ���������±�
		//�õ����������е�ֵx����ô�Ϳ���֪��<=v[i]�����鹲��x������ô�����ȶ��ԵĻ���
		//�����ǴӺ���ǰ��������˴�ʱ����ɼ�Ӧ�����±�x-1�����������ܱ�֤[0, x-1]�±��ܴ�x������
		result[tmp[v[i] - mi] - 1] = v[i];
		--tmp[v[i] - mi];
	}
	v = result;
}

//Ͱ����--�ݹ���Ͱ����
vector<int> bucketSort(vector<int> &v, int bucketSize)
{
	if (v.size() <= 1)
	{
		return v;
	}
	//�ҵ������Сֵ
	int mi = v[0], ma = v[0];
	for (int i : v)
	{
		if (i < mi)
		{
			mi = i;
		}
		if (i > ma)
		{
			ma = i;
		}
	}
	int bucketCount = (ma - mi) / bucketSize + 1;  //Ͱ�ĸ���
	vector< vector<int> > buckets(bucketCount);
	for (int i : v)
	{
		buckets[(i - mi) / bucketSize].push_back(i);  //�ŵ�Ͱ��
	}
	//��Ͱ�е�Ԫ������
	vector<int> result;
	for (int i = 0; i < bucketCount; ++i)
	{
		if (bucketSize == 1)  //Ҳ����bucketCount = ma - mi + 1, Ҳ���ǲ�ͬ�����ڲ�ͬ��Ͱ�У�ֱ�Ӽӵ�result��
		{
			for (int j = 0; j < buckets[i].size(); ++j)
			{
				result.push_back(buckets[i][j]);
			}
		}
		else
		{
			if (bucketCount == 1)  //ֻ��һ��Ͱ����ô����ma=mi,Ҳ�������е�ֵ����ͬ
			{
				for (int j = 0; j < buckets[i].size(); ++j)
				{
					result.push_back(buckets[i][j]);
				}
			}
			else
			{
				vector<int> tmp = bucketSort(buckets[i], bucketSize);  //��ÿ��Ͱ����
				for (int j : tmp)
				{
					result.push_back(j);
				}
			}
		}
	}
	return result;
}

//��������
void radixSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	//�ҵ����ֵ,����������λ
	int ma = v[0];
	for (int i : v)
	{
		if (i > ma)
		{
			ma = i;
		}
	}
	int maxWei = 0;  //����ж���λ
	while (ma > 0)
	{
		++maxWei;
		ma /= 10;
	}
	//����Ҫ�������£�����ĳ����1524��Ҫ�ҵ����һλ4Ӧ����%10����1���ڶ�λ2Ӧ����%100Ȼ�����10������λ5Ӧ����%1000Ȼ�����100
	vector< vector<int> > buckets(10);
	int mod = 10, div = 1;
	for (int i=1; i <= maxWei; ++i, mod *= 10, div *= 10)
	{
		for (int j : v)  //��Ԫ�صĵ�iλ�ŵ���Ӧ��Ͱ��
		{
			buckets[(j % mod) / div].push_back(j);
		}
		//��Ͱ�е�Ԫ�طŵ�ԭ������
		int index = 0;
		for (int j = 0; j < buckets.size(); ++j)
		{
			for (int k : buckets[j])
			{
				v[index] = k;
				++index;
			}
			buckets[j].clear();  //����������Ϣ������ֱ��buckets.clear(),������С�ͻ��Ϊ0������10��
		}
	}
}

int main()
{

}