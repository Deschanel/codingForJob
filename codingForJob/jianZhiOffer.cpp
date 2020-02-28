#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

int findRepeatNumber_1(vector<int>& nums)    ////������03. �������ظ�������
{
	//ԭ���㷨,��sort����󣬲��ҵ�ǰ���һ����ͬ������
	if (nums.size() <= 1)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());  //ʱ��O(nlogn)
	for (int i=0; i<nums.size() - 1; ++i)
	{
		if (nums.at(i)  == nums.at(i + 1))
		{
			return nums.at(i);
			break;
		}
	}
	return -1;
}

int findRepeatNumber_2(vector<int>& nums)    ////������03. �������ظ�������
{
	//ʹ��unorder_set������֮ǰ�Ƿ��Ѿ����ˣ��ռ�O(n)��ʱ��O(n)
	if (nums.size() <= 1)
	{
		return 0;
	}
	unordered_set<int> us;
	for (auto i : nums)
	{
		if (us.count(i))
		{
			return i;
			break;
		}
		else
		{
			us.insert(i);
		}
	}
	return -1;
}

int findRepeatNumber_3(vector<int>& nums)    ////������03. �������ظ�������
{
	//���Ҫ��û���ظ��Ļ����±���ֵӦ�����
	//�±�Ϊi��ֵΪm����m==i����������������ȵĻ������Ǿ�ȥ���±�Ϊm����k�����k=m�Ļ����ظ��˷���
	//������ȵĻ�����m��k������Ҳ����m�ŵ��±�Ϊm��λ�ã�k�ŵ��±�Ϊi��λ�ã���ȥ���±�Ϊk����n���������ϲ���
	if (nums.size() <= 1)
	{
		return -1;
	}
	for (int i : nums)
	{
		if (i < 0 || i > nums.size() - 1)
		{
			return -1;
		}
	}
	for (int i=0; i<nums.size(); ++i)
	{
		while (nums[i] != i)
		{
			if (nums[i] == nums[nums[i]])
			{
				return nums[i];
			}
			swap(nums[i], nums[nums[i]]);
		}
	}
	return -1;
}

bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
{
	//��ʣ��������Ͻ��Ǹ���m���������ֱ�ӷ��أ�
	//���m����target����ôm����һ���޳���Ҳ���Ǵ�ʱӦ�ÿ���mͬ�е���������
	//���С�ڣ���m�����б��޳�����ʱҪ����mͬ�е��������
	//ѭ������ִ����ȥ
	if (matrix.size() == 0 || matrix.at(0).size() == 0)
	{
		return false;
	}
	int n = matrix.size() - 1, m = matrix.at(0).size() - 1;
	if (matrix[0][0] > target || matrix[n][m] < target)
	{
		return false;
	}
	int i = 0;
	while (i <= n && m >= 0)
	{
		if (matrix[i][m] == target)
		{
			return true;
		}
		else if (matrix[i][m] > target)
		{
			--m;
		}
		else
		{
			++i;
		}
	}
	return false;
}

string replaceSpace_1(string s)  //������05. �滻�ո�
{
	//ԭ���㷨����s���ݣ�Ȼ��һ��ָ��p1��ԭ��δ���ݵ��ַ��������һ���ַ���ǰ��һ��ָ��p2�����ݺ���ַ����һ��λ����ǰ
	//���p1ָ���ֵ��Ϊ�ո���ô�Ͱ����ֵ��ֵ��p2ָ���λ�ã�
	//������ڿո���ôp2��ǰ�ֱ����02%��Ȼ����������ǰ��,ֱ��p1���˵�0���ַ�
	//���ڰѿո�ת��Ϊ%20��1����Ϊ������Ҳ����˵һ���ո��Ҫ�������2���ַ��ĳ��ȣ�����count���ո񣬾�Ҫ�������2*count������
	if (s.size() == 0)
	{
		return "";
	}
	int count = 0;
	for (char c : s)
	{
		if (c == ' ')
		{
			++count;
		}
	}
	int p1 = s.size() - 1;
	s.resize(s.size() + 2 * count);
	int p2 = s.size() - 1;
	for (; p1 >=0 && p2 >= 0; --p1)
	{
		if (s[p1] != ' ')
		{
			s[p2] = s[p1];
		}
		else
		{
			s[p2] = '0';
			--p2;
			s[p2] = '2';
			--p2;
			s[p2] = '%';
		}
		--p2;
	}
	return s;
}

string replaceSpace_2(string s)  //������05. �滻�ո�
{
	//��ԭ���㷨
	if (s.size() == 0)
	{
		return "";
	}
	string result;
	for (char c : s)
	{
		if (c != ' ')
		{
			result += c;
		}
		else
		{
			result += "%20";
		}
	}
	return result;
}

int main()
{
	//������03. �������ظ�������
	//findRepeatNumber

	//������04. ��ά�����еĲ���
	//findNumberIn2DArray

	//������05. �滻�ո�
	//replaceSpace
	return 0;
}