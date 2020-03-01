#include <iostream>
#include <vector>
using namespace std;

//冒泡排序--一般情况
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
//冒泡排序最好情况时候的代码
void bubbleSort_2(vector<int> &v)
{
	//当一个数组是排序好的，或者经过有限趟扫描能达到排好序，那么就不存在逆序对了，就可以返回
	//如果有逆序对，就说明没排好
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
				flag = true;   //存在逆序对
				swap(v[j + 1], v[j]);
			}
		}
		if (!flag)   //不存在逆序对了
		{
			return;
		}
	}
}

//选择排序
void selectionSort(vector<int> &v)
{
	//首先在未排序序列中找到最小（大）元素，存放到排序序列的哨兵位置，
	//然后，再从剩余未排序元素中继续寻找最小（大）元素，
	//然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	for (int i=0; i<n; ++i)
	{
		int index = i;  //剩余元素最小值的下标
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

//插入排序
void insertionSort(vector<int> &v)
{
	//通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
	if (v.size() <= 1)
	{
		return;
	}
	int n = v.size();
	for (int i=0; i<n-1; ++i)
	{
		int cur = v[i + 1];  //当前要插入的元素,下标为i+1,前面一直到下标i都已经排好序了
		int j = i;  //下标
		while (j >= 0 && v[j] > cur)
		{
			v[j + 1] = v[j];
			--j;
		}
		//此时找到了第一个比它小的
		v[j + 1] = cur;
	}
}

//希尔排序
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

//归并排序
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
			if (l[i] <= r[j])  //如果相等的话，让左边还是在左边，维持稳定
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

int quickSort_partition(vector<int>& v, int start, int end)  //分割
{
	if (v.size() <= 1 || start >= end || start < 0 || end >= v.size())
	{
		return;
	}
	int com = v[start];
	swap(v[start], v[end]);  //将比较的数放到最后，在代码最后在交换过来，使得比较数能在哨兵的右侧
	int shaobing = start - 1;
	for (int i=start; i<=end; ++i)
	{
		if (v[i] < com)  //只需要把小于的放到哨兵那个去
		{
			++shaobing;
			if (shaobing != i)
			{
				swap(v[shaobing], v[i]);
			}
		}
	}
	//以上for循环完成后，下标shaobing包括自己向左都是小于分割数的元素
	//所以此时返回小于分割数的个数，也就是需要shaobing+1后再返回，因为下标是从0开始的,到shaobing一共是shaobing+1个
	++shaobing;
	swap(v[shaobing], v[end]);   //将分割数返回来，此时分割数就在哨兵的位置,也就是此时分割数的下标为shaobing
	return shaobing;
}
void quickSort_item(vector<int>& v, int start, int end)
{
	if (v.size() <= 1 || start >= end || start < 0 || end >= v.size())
	{
		return;
	}
	//分割数所在的位置
	int n = quickSort_partition(v, start, end);  
	if (n > start)  //分割数之前的
	{
		quickSort_item(v, start, n - 1);
	}
	if (n < end)  //分割数之后的,因为n是分割数所在的下标
	{
		quickSort_item(v, n + 1, end);
	}
}
//快速排序
void quickSort(vector<int>& v)
{
	if (v.size() <= 1)
	{
		return;
	}
	quickSort_item(v, 0, v.size() - 1);
}

//调整大顶堆
void adjustHeap(vector<int> &v, int i, int n)
{
	//以下标i的元素和其左右子树构成的大顶堆进行调整
	for (int k = i * 2 + 1; k < n; k = k * 2 + 1)  //k*2+1为当前节点的左节点
	{
		if (k + 1 < n && v[k] < v[k + 1])  //左节点值小于右节点的值
		{
			++k;  //指向右节点
		}
		if (v[k] > v[i])  //此时以i为根节点的大顶堆，根节点的值小于其最大子节点的值
		{
			swap(v[k], v[i]);  //交换节点值
			i = k;  //此时根节点被换下去到了k处，因此i=k，此时继续循环看看以下标为i(原来的k)的,被换下去的那个值和其左右子树是否还满足
		}
		else  //根节点最大，那么就直接break，此时不会出现左子树的孩子或者右子树的孩子们比根节点大，因为是从下到上遍历的
		{
			break;
		}
	}
}
//堆排序
void heapSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	//构造大顶堆
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; --i)  //对所有非叶子节点从下往上，从右往左进行调整大顶堆结构
	{
		adjustHeap(v, i, n); 
	}
	//for出去后就调整完了，此时最大元素在根节点
	for (int j = n - 1; j >= 0; --j)
	{
		swap(v[j], v[0]);  //将最大元素弄到末尾,末尾元素在根节点处，则接下来就要调整了
		adjustHeap(v, 0, j);  //因为此时最大元素已经在数组末尾部分，因此只需要调整剩下的j个即可，根节点还是第0个元素
	}
}

//计数排序
void countingSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	int mi = v[0], ma = v[0];  //最小最大值
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
	vector<int> tmp(ma - mi + 1, 0); //创建计数数组
	for (int i : v)  //首先是记录每个数字出现的次数
	{
		tmp[i - mi]++;
	}
	//然后将出现的次数累加
	int sum = 0;
	for (int i = 0; i < tmp.size(); ++i)
	{
		sum += tmp[i];
		tmp[i] = sum;
	}
	//倒序遍历数组--为了保持稳定性
	vector<int> result(v.size(), 0);
	for (int i = v.size() - 1; i >= 0; --i)
	{
		//v[i] - mi表示当前的成绩在计数数组的下标
		//得到计数数组中的值x后，那么就可以知道<=v[i]的数组共有x个，那么保持稳定性的话，
		//由于是从后往前遍历，因此此时这个成绩应该在下标x-1处，这样才能保证[0, x-1]下标能存x个数据
		result[tmp[v[i] - mi] - 1] = v[i];
		--tmp[v[i] - mi];
	}
	v = result;
}

//桶排序--递归用桶排序
vector<int> bucketSort(vector<int> &v, int bucketSize)
{
	if (v.size() <= 1)
	{
		return v;
	}
	//找到最大最小值
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
	int bucketCount = (ma - mi) / bucketSize + 1;  //桶的个数
	vector< vector<int> > buckets(bucketCount);
	for (int i : v)
	{
		buckets[(i - mi) / bucketSize].push_back(i);  //放到桶中
	}
	//对桶中的元素排序
	vector<int> result;
	for (int i = 0; i < bucketCount; ++i)
	{
		if (bucketSize == 1)  //也就是bucketCount = ma - mi + 1, 也就是不同的数在不同的桶中，直接加到result中
		{
			for (int j = 0; j < buckets[i].size(); ++j)
			{
				result.push_back(buckets[i][j]);
			}
		}
		else
		{
			if (bucketCount == 1)  //只有一个桶，那么就是ma=mi,也就是所有的值都相同
			{
				for (int j = 0; j < buckets[i].size(); ++j)
				{
					result.push_back(buckets[i][j]);
				}
			}
			else
			{
				vector<int> tmp = bucketSort(buckets[i], bucketSize);  //对每个桶排序
				for (int j : tmp)
				{
					result.push_back(j);
				}
			}
		}
	}
	return result;
}

//基数排序
void radixSort(vector<int> &v)
{
	if (v.size() <= 1)
	{
		return;
	}
	//找到最大值,看看最多多少位
	int ma = v[0];
	for (int i : v)
	{
		if (i > ma)
		{
			ma = i;
		}
	}
	int maxWei = 0;  //最多有多少位
	while (ma > 0)
	{
		++maxWei;
		ma /= 10;
	}
	//这里要解释以下，假设某个数1524，要找到其第一位4应该是%10除以1，第二位2应该是%100然后除以10，第三位5应该是%1000然后除以100
	vector< vector<int> > buckets(10);
	int mod = 10, div = 1;
	for (int i=1; i <= maxWei; ++i, mod *= 10, div *= 10)
	{
		for (int j : v)  //将元素的第i位放到对应的桶中
		{
			buckets[(j % mod) / div].push_back(j);
		}
		//将桶中的元素放到原数组中
		int index = 0;
		for (int j = 0; j < buckets.size(); ++j)
		{
			for (int k : buckets[j])
			{
				v[index] = k;
				++index;
			}
			buckets[j].clear();  //清除里面的信息，不能直接buckets.clear(),这样大小就会变为0，不是10了
		}
	}
}

int main()
{

}