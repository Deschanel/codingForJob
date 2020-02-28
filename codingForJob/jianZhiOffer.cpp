#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

int findRepeatNumber_1(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//原地算法,用sort排序后，查找当前与后一个相同的数字
	if (nums.size() <= 1)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());  //时间O(nlogn)
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

int findRepeatNumber_2(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//使用unorder_set，看看之前是否已经有了，空间O(n)，时间O(n)
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

int findRepeatNumber_3(vector<int>& nums)    ////面试题03. 数组中重复的数字
{
	//如果要是没有重复的话，下标与值应该相等
	//下标为i的值为m，如m==i，则跳过，如果不等的话，我们就去找下标为m的数k，如果k=m的话，重复了返回
	//如果不等的话，将m和k交换，也就是m放到下标为m的位置，k放到下标为i的位置，再去看下标为k的数n，继续以上操作
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
	//看剩余矩阵右上角那个数m，如果等于直接返回，
	//如果m大于target，那么m所在一列剔除，也就是此时应该看与m同行的左侧的数，
	//如果小于，则m所在行比剔除，此时要看与m同列的下面的数
	//循环这样执行下去
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

string replaceSpace_1(string s)  //面试题05. 替换空格
{
	//原地算法，将s扩容，然后一个指针p1从原先未扩容的字符串的最后一个字符往前，一个指针p2从扩容后的字符最后一个位置往前
	//如果p1指向的值不为空格，那么就把这个值赋值给p2指向的位置，
	//如果等于空格，那么p2往前分别加上02%后，然后两者再往前走,直到p1出了第0个字符
	//由于把空格转换为%20，1个变为三个，也就是说一个空格就要额外加上2个字符的长度，共有count个空格，就要额外加上2*count个长度
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

string replaceSpace_2(string s)  //面试题05. 替换空格
{
	//非原地算法
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
	//面试题03. 数组中重复的数字
	//findRepeatNumber

	//面试题04. 二维数组中的查找
	//findNumberIn2DArray

	//面试题05. 替换空格
	//replaceSpace
	return 0;
}