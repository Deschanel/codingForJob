// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>

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

int reverseNum(int x)  //这个方法
{
	int result = 0, minNum = -pow(2, 31), maxNum = pow(2, 31) - 1;
	while (x != 0)
	{
		int tmp = x % 10;
		if (result > maxNum / 10 || (result == maxNum/10 && tmp > 7))
		{
			return 0;
		}
		else if(result < minNum / 10 || (result == minNum/10 && tmp < -8))
		{
			return 0;
		}
		result = result * 10 + tmp;
		x /= 10;
	}
	return result;
}

bool isPalindrome_1(int x)  //方法一反转数字看是否相等
{
	if (x < 0)
	{
		return false;
	}
	if (x == 0)
	{
		return true;
	}
	unsigned int i = 1, result = 0, xt = x;
	while (x > 0)
	{
		int tmp = x % 10;
		//这里应加上判断if (result > maxNum / 10 || (result == maxNum/10 && tmp > 7))
		result = result * 10 + tmp;
		x /= 10;
	}
	if (result == xt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int isPalindrome_2(int x)  //改进，由于x肯定不会溢出，那么其对称中心的左右两边数字肯定也不会溢出,因此只需要判断对称中心两边是否相等
{
	if (x == 0)
	{
		return true;
	}
	if (x < 0 || x % 10 == 0)
	{
		return false;
	}
	int left = x, right = 0;
	while (left > right)  //若left不大于right，则说明已经在或者超过了对称中心，因此结束循环
	{
		int tmp = left % 10;
		right = right * 10 + tmp;
		left /= 10;
	}
	return (left == right) || (left == right / 10);
}

int romanToInt_1(string s)
{
	stack<int> st;
	int result = 0;
	for (int i=0; i<s.size(); ++i)
	{
		switch (s.at(i))
		{
		case 'I':
			st.push(1);
			break;
		case 'V':
			st.push(5);
			break;
		case 'X':
			st.push(10);
			break;
		case 'L':
			st.push(50);
			break;
		case 'C':
			st.push(100);
			break;
		case 'D':
			st.push(500);
			break;
		case 'M':
			st.push(1000);
			break;
		}
	}
	while (!st.empty())
	{
		int tmp = st.top();
		st.pop();
		if (st.empty())
		{
			result += tmp;
			break;
		}
		int tmp_1 = st.top();
		st.pop();
		if (tmp == 5 && tmp_1 == 1)
		{
			result += 4;
		}
		else if (tmp == 10 && tmp_1 == 1)
		{
			result += 9;
		}
		else if (tmp == 50 && tmp_1 == 10)
		{
			result += 40;
		}
		else if (tmp == 100 && tmp_1 == 10)
		{
			result += 90;
		}
		else if(tmp == 500 && tmp_1 == 100)
		{
			result += 400;
		}
		else if (tmp == 1000 && tmp_1 == 100)
		{
			result += 900;
		}
		else
		{
			result = result + tmp + tmp_1;
		}
	}
	return result;
}

int romanToInt_2(string s)
{
	int result = 0;
	int pre = 0;
	for (int i=0; i<s.size(); ++i)
	{
		switch (s.at(i))
		{
		case 'I':
			result += 1;
			pre = 1;
			break;
		case 'V':
			if (pre == 1)
			{
				result += 3;
			}
			else
			{
				result += 5;
			}
			pre = 5;
			break;
		case 'X':
			if (pre == 1)
			{
				result += 8;
			}
			else
			{
				result += 10;
			}
			pre = 10;
			break;
		case 'L':
			if (pre == 10)
			{
				result += 30;
			}
			else
			{
				result += 50;
			}
			pre = 50;
			break;
		case 'C':
			if (pre == 10)
			{
				result += 80;
			}
			else
			{
				result += 100;
			}
			pre = 100;
			break;
		case 'D':
			if (pre == 100)
			{
				result += 300;
			}
			else
			{
				result += 500;
			}
			pre = 500;
			break;
		case 'M':
			if (pre == 100)
			{
				result += 800;
			}
			else
			{
				result += 1000;
			}
			pre = 1000;
			break;
		}
	}
	return result;
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
	/*
	int test = -123;
	std::cout << reverseNum(test) << endl;
	*/
	//回文数
	/*
	int test = 10;
	std::cout << isPalindrome_2(test) << endl;
	*/
	//罗马数到int
	string s = "MCMXCIV";
	std::cout << romanToInt_1(s) << endl;
}
