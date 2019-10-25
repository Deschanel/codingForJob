// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

vector<int> twoSum_1(vector<int> &nums, int target)   //暴力解法
{
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		for (int j = 0; j < nums.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}
			if (nums.at(i) + nums.at(j) == target)
			{
				result.push_back(i);
				result.push_back(j);
				return result;
			}
		}
	}
	return result;
}

vector<int> twoSum_2(vector<int> &nums, int target)  //两个map表, 改进一
{
	map<int, int> tmp;
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		tmp.insert(pair<int, int>(nums.at(i), i));
	}
	for (int i=0; i<nums.size(); ++i)
	{
		int want = target - nums.at(i);
		if (tmp.find(want) != tmp.end() && tmp.at(want) != i)
		{
			result.push_back(i);
			result.push_back(tmp.at(want));
			return result;
		}
	}
	return result;
}

vector<int> twoSum_3(vector<int> &nums, int target)  //一个map表, 改进二
{
	map<int, int> tmp;
	vector<int> result;
	for (int i = 0; i < nums.size(); ++i)
	{
		int want = target - nums.at(i);
		if (tmp.find(want) != tmp.end() && tmp.at(want) != i)
		{
			if (i < tmp.at(want))
			{
				result.push_back(i);
				result.push_back(tmp.at(want));
			}
			else
			{
				result.push_back(tmp.at(want));
				result.push_back(i);
			}
			return result;
		}
		tmp.insert(pair<int, int>(nums.at(i), i));
	}
	return result;
}

int reverseNum_1(int x)  //这个方法慢
{
	int result = 0, minNum = -pow(2, 31), maxNum = pow(2, 31) - 1;
	stack<int> s;
	if (x > 0)
	{
		while (x > 0)
		{
			int tmp = x % 10;
			s.push(tmp);
			x /= 10;
		}
		int i = 0;
		while (!s.empty())
		{
			result += (s.top()*pow(10, i));
			if (result < minNum || result > maxNum)
			{
				return 0;
			}
			s.pop();
			i++;
		}
	}
	else
	{
		x = abs(x);
		while (x > 0)
		{
			int tmp = x % 10;
			s.push(tmp);
			x /= 10;
		}
		int i = 0;
		while (!s.empty())
		{
			result += (s.top()*pow(10, i));
			if (result < minNum || result > maxNum)
			{
				return 0;
			}
			s.pop();
			i++;
		}
		result *= -1;
	}
	return result;
}

int reverseNum_2(int x)
{
	int result = 0, minNum = -pow(2, 31), maxNum = pow(2, 31) - 1;
	while (x > 0)
	{
		int tmp = x % 10;
		int tmp_1 = x / 10;
		result += tmp;
	}
}

int main()
{
	//两数之和
	/*
	vector<int> nums, result;
	nums.push_back(2);
	nums.push_back(7);
	nums.push_back(11);
	nums.push_back(15);
	result = twoSum_3(nums, 9);
	for (int i=0; i<result.size(); ++i)
	{
		std::cout << result.at(i) << " ";
	}
	std::cout << endl;
	*/
	//反转整数
	int test = 120;
	std::cout << reverseNum_1(test) << endl;
}
