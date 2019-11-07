﻿// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <queue>
#include <set>
#include <bitset>

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

string longestCommonPrefix(vector<string>& strs)  //最长公共子前缀
{
	string result = "";
	if (strs.size() == 0)
	{
		return result;
	}
	if (strs.size() == 1)
	{
		return strs.at(0);
	}
	string tmp = strs.at(0);
	for (int i=0; i<tmp.size(); ++i)
	{
		for (int j=1; j<strs.size(); ++j)
		{
			if (strs.at(j).size() <= i || strs.at(j).at(i) != tmp.at(i))
			{
				return result;
			}
		}
		result += tmp.at(i);
	}
	return result;
}

bool isBracketsValid(string s)
{
	if (s.size() == 0)
	{
		return true;
	}
	stack<char> st;
	for (auto c : s)
	{
		if (c == '(' || c == '[' || c == '{')
		{
			st.push(c);
		}
		else if(c == ')' && !st.empty() && st.top() == '(')
		{
			st.pop();
		}
		else if (c == ']' && !st.empty() && st.top() == '[')
		{
			st.pop();
		}
		else if (c == '}' && !st.empty() && st.top() == '{')
		{
			st.pop();
		}
		else
		{
			return false;
		}
	}
	return st.empty();
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
	if (!l1)
	{
		return l2;
	}
	else if (!l2)
	{
		return l1;
	}
	queue<int> q;
	while (l1 && l2)
	{
		if (l1->val <= l2->val)
		{
			q.push(l1->val);
			l1 = l1->next;
		}
		else
		{
			q.push(l2->val);
			l2 = l2->next;
		}
	}
	ListNode *l = new ListNode(q.front());
	ListNode *result = l;
	q.pop();
	while (!q.empty())
	{
		l->next = new ListNode(q.front());
		q.pop();
		l = l->next;
	}
	if (l1)
	{
		l->next = l1;
	}
	else if (l2)
	{
		l->next = l2;
	}
	return result;
}

int removeDuplicates(vector<int>& nums)
{
	if (nums.size() < 2)
	{
		return nums.size();
	}
	int pre = 0;
	for (int i = 1; i < nums.size(); ++i)
	{
		//解释一下下面
		/*
			由于是排好序的，因此必然有后面的大于等于前面的。
			这里把i代表的值直接与pre+1代表的值互换，那么问题来了，如果pre+1代表的值与pre代表的值相等，swap是显然的，如果pre+1代表的值大于pre代表的值不就不对了嘛
			这里其实不用担心，因为呢，i是遍历，因此i肯定会在之前某时刻(不妨假定为时刻1)遍历到此时刻(不妨假定为时刻2)的pre+1，而如果时刻1的i代表的值大于时刻1的pre代表的值的话，就会swap，也就是
			时刻2的pre+1代表的值是经过swap的，是重复的值；如果时刻1的i代表的值小于等于时刻1的pre代表的值的话，那么就说明[0， pre(时刻1)]里面有了i(时刻1)代表的值，因此就是不需要的
			因此，[pre+1, i)之间的值要不就是经过swap的值，要不就是不需要的重复的值，因此不会有以上的问题出现。
		*/
		if (nums.at(i) > nums.at(pre)) 								
		{                             
			swap(nums.at(i), nums.at(pre + 1));  //这里i是一直大于等于pre+1的，所以pre+1不会溢出
			pre++;
		}
	}
	return pre + 1;
}

int removeElement(vector<int>& nums, int val)
{
	if ((nums.size() == 0) || (nums.size() == 1 && nums.at(0) == val))
	{
		return 0;
	}
	if (nums.size() == 1 && nums.at(0) != val)
	{
		return 1;
	}
	int pre = 0;
	int i = 0;
	for (; i<nums.size(); ++i)
	{
		if (nums.at(i) == val)
		{
			pre = i;
			break;
		}
	}
	if (i >= nums.size())
	{
		return nums.size();
	}
	for (; i < nums.size(); ++i)
	{
		if (nums.at(i) != val)
		{
			swap(nums.at(i), nums.at(pre));
			pre++;
		}
	}
	return pre;
}

int strStr(string haystack, string needle)
{
	if (needle == "")
	{
		return 0;
	}
	if (haystack == "")
	{
		return -1;
	}
	bool result = false;
	for (int i=0; i<haystack.size(); ++i)
	{
		if (haystack.at(i) == needle.at(0))
		{
			result = true;
			for (int j=1; j<needle.size(); ++j)
			{
				if (i + j >= haystack.size())
				{
					return -1;
				}
				if (haystack.at(i + j) != needle.at(j))
				{
					result = false;
					break;
				}
			}
			if (result)
			{
				return i;
			}
		}
	}
	return -1;
}

int searchInsert(vector<int>& nums, int target)
{
	if (nums.size() == 0 || nums.at(0) > target)
	{
		return 0;
	}
	for (int i=0; i<nums.size(); ++i)
	{
		if (nums.at(i) == target)
		{
			return i;
		}
		else if(nums.at(i) > target && i > 0 && nums.at(i-1) < target)
		{
			return i;
		}
	}
	return nums.size();
}

string countAndSay(int n)  //递归版本
{
	if (n < 2)
	{
		return std::to_string(n);
	}
	string preStr = countAndSay(n - 1);
	int pre = 0;
	string result;
	for (int i=0; i< preStr.size(); ++i)
	{
		if (preStr.at(i) != preStr.at(pre))
		{
			result += std::to_string(i - pre);
			result += preStr.at(pre);
			pre = i;
		}
		if (i == preStr.size() - 1)
		{
			result += std::to_string(i - pre + 1);
			result += preStr.at(pre);
		}
	}
	return result;
}

int maxSubArray_1(vector<int>& nums)  //暴力解法
{
	if (nums.size() == 0)
	{
		return 0;
	}
	int result = nums.at(0);
	for (int i=0; i<nums.size(); ++i)
	{
		int tmp = 0;
		for (int j=i; j<nums.size(); ++j)
		{
			tmp += nums.at(j);
			if (tmp > result)
			{
				result = tmp;
			}
		}
	}
	return result;
}

int maxSubArray_2(vector<int>& nums)  //分而治之
{
	if (nums.size() == 1)
	{
		return nums.at(0);
	}
	if (nums.size() == 0)
	{
		return 0;
	}
	vector<int> left_nums;
	vector<int> right_nums;
	for (int i=0; i< nums.size(); ++i)
	{
		if (i < nums.size() / 2)
		{
			left_nums.push_back(nums.at(i));
		}
		else
		{
			right_nums.push_back(nums.at(i));
		}
	}
	int max_left = maxSubArray_2(left_nums);  //左侧最大值
	int max_right = maxSubArray_2(right_nums);  //右侧最大值
	int max_l = nums.at(nums.size() / 2);
	int tmp = 0;
	for (int i=nums.size() / 2; i>=0; --i)
	{
		tmp += nums.at(i);
		max_l = max(max_l, tmp);
	}
	tmp = 0;
	int max_r = nums.at(nums.size() / 2 + 1);
	for (int i=nums.size()/2+1; i<nums.size(); ++i)
	{
		tmp += nums.at(i);
		max_r = max(tmp, max_r);
	}
	int result = max(max_left, max_right);
	return max(result, max_l+max_r);
}

int maxSubArray_3(vector<int>& nums)  //动态规划
{
	if (nums.size() == 1)
	{
		return nums.at(0);
	}
	if (nums.size() == 0)
	{
		return 0;
	}
	int sum = 0;   //前面的最大子序列和。初始化是0
	int result = nums.at(0);
	for (auto num : nums)
	{
		if (sum > 0)  //如果前面的最大子序列和是正的，就说明对当前的num元素有增益效果，所以要加上，这里不会发生num前一个元素没包含的情况，也就是sum中包含当前遍历数的前一个元素，这里可以用数学归纳法来证明，因此不会断开
		{
			sum += num;
		}
		else   //否则的话从当前位置重新开始寻找
		{
			sum = num;
		}
		result = max(sum, result);
	}
	return result;
}

int lengthOfLastWord(string s)  //最后一个单词的长度
{
	if (s.size() == 0)
	{
		return 0;
	}
	int result = 0;
	int start = s.size()-1;
	for (int i = s.size() - 1; i>=0; --i)
	{
		if (s.at(i) != ' ')
		{
			start = i;
			break;
		}
	}
	for (int i=start; i>=0; --i)
	{
		if (s.at(i) != ' ')
		{
			result++;
		}
		else
		{
			break;
		}
	}
	return result;
}

vector<int> plusOne(vector<int>& digits)
{
	int i = digits.size() - 1;
	while (i > -1 && digits.at(i) == 9)
	{
		digits[i] = 0;
		i--;
	}
	if (i == -1)
	{
		digits.insert(digits.begin(), 1);
	}
	else
	{
		digits[i] += 1;
	}
	return digits;
}

string addBinary_1(string a, string b) //普通方法
{
	int i = a.size()-1, j = b.size()-1;
	int p = 0;
	string result;
	while (i > -1 || j > -1)
	{
		if (j <= -1)
		{
			result = std::to_string((static_cast<int>(a.at(i) - '0') + p) % 2) + result;
			if (static_cast<int>(a.at(i) - '0') + p == 2)
			{
				p = 1;
			}
			else
			{
				p = 0;
			}
		}else if (i <= -1)
		{
			result = std::to_string((static_cast<int>(b.at(j) - '0') + p) % 2) + result;
			if (static_cast<int>(b.at(j) - '0') + p == 2)
			{
				p = 1;
			}
			else
			{
				p = 0;
			}
		}
		else
		{
			result = std::to_string((static_cast<int>(b.at(j) + a.at(i) - '0' - '0') + p) % 2) + result;
			if (static_cast<int>(b.at(j) + a.at(i) - '0' - '0') + p < 2)
			{
				p = 0;
			}
			else
			{
				p = 1;
			}
		}
		j--;
		i--;
	}
	if (p == 1)
	{
		result = std::to_string(1) + result;
	}
	return result;
}

string addBinary_2(string a, string b) //短的在前面补0
{
	while (a.size() > b.size())
	{
		b = '0' + b;
	}
	while (a.size() < b.size())
	{
		a = '0' + a;
	}
	for (int i=a.size() -1; i>0; --i)
	{
		a[i] = a[i] - '0' + b[i];
		if (a[i] >= '2')
		{
			a[i] = (a[i] - '0') % 2 + '0';
			a[i - 1] = a[i - 1] + 1;
		}
	}
	a[0] = a[0] + b[0] - '0';
	if (a[0] >= '2')
	{
		a[0] = (a[0] - '0') % 2 + '0';
		a = '1' + a;
	}
	return a;
}

int mySqrt_1(int x)  //暴力解法
{
	if (x == 0)
	{
		return 0;
	}
	int i = 1;
	while (i*i < x)
	{
		i++;
	}
	return i - 1;
}

int mySqrt_2(int x)  //二分查找,当x>=4时。x/2的平方大于等于x的平方根
{
	if (x == 0 || x == 1)
	{
		return x;
	}
	long long left = 0, right = x;
	while (left < right)
	{
		long long mid = (right + left) >> 1;
		long long s = mid * mid;
		(x < s) ? (right = mid) : (left = mid + 1);
	}
	return --left;
}

int climbStairs_1(int n)  //动态规划递归----超时了
{
	if (n == 1)
	{
		return 1;
	}
	if (n == 2)
	{
		return 2;
	}
	return climbStairs_1(n - 1) + climbStairs_1(n - 2);
}

int climbStairs_2(int n)  //动态规划迭代----就是斐波那契数列啊
{
	if (n == 1)
	{
		return 1;
	}
	if (n == 2)
	{
		return 2;
	}
	int pre = 1, now = 2;
	while (n > 2)
	{
		now = now + pre;
		pre = now - pre;
		n--;
	}
	return now;
}

ListNode* deleteDuplicates_1(ListNode* head) //vector解决
{
	if (!head)
	{
		return nullptr;
	}
	vector<int> v;
	v.push_back(head->val);
	head = head->next;
	while (head)
	{
		if (v.at(v.size() - 1) < head->val)
		{
			v.push_back(head->val);
		}
		head = head->next;
	}
	ListNode *p = new ListNode(v.at(0));
	ListNode *result = p;
	for (int i = 1; i < v.size(); ++i)
	{
		p->next = new ListNode(v.at(i));
		p = p->next;
	}
	return result;
}
ListNode* deleteDuplicates_2(ListNode* head)  //链表解决
{
	ListNode *p = new ListNode(head->val);
	ListNode *result = p;
	while (head)
	{
		if (p->val < head->val)
		{
			p->next = head;
			p = p->next;
		}
		head = head->next;
	}
	p->next = NULL;  //如果head中最后的数字有好几个的话，在while中已经加入到p中一个了，因此要把后面重复的删掉，就是令next为null
	return result;
}

void merge_1(vector<int>& nums1, int m, vector<int>& nums2, int n)  //使用sort函数
{
	if (n < 1)
	{
		return;
	}
	for (int i=m; i<m+n; ++i)
	{
		nums1[i] = nums2.at(i - m);
	}
	std::sort(nums1.begin(), nums1.end());
}

void merge_2(vector<int>& nums1, int m, vector<int>& nums2, int n)  //双指针,从前往后
{
	vector<int> tmp;
	for (int i=0; i<m; ++i)
	{
		tmp.push_back(nums1.at(i));
	}
	int i = 0, j = 0, k = 0;
	while (i<n && j<m)
	{
		if (nums2.at(i) < tmp.at(j))
		{
			nums1[k] = nums2.at(i);
			++i;
		}
		else
		{
			nums1[k] = tmp.at(j);
			++j;
		}
		++k;
	}
	while (j < m)
	{
		nums1[k++] = tmp[j++];
	}
	while (i<n)
	{
		nums1[k++] = nums2[i++];
	}
}

void merge_3(vector<int>& nums1, int m, vector<int>& nums2, int n)  //双指针,从后往前
{
	int i = m-1, j = n-1, k = m + n-1;
	while (i>=0 && j>=0)
	{
		if (nums2.at(j) >= nums1.at(i))
		{
			nums1.at(k) = nums2.at(j);
			--j;
		}
		else
		{
			nums1.at(k) = nums1.at(i);
			--i;
		}
		--k;
	}
	while (j >= 0)
	{
		nums1[k--] = nums2[j--];
	}
	while (i >= 0)
	{
		nums1[k--] = nums1[i--];
	}
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSameTree(TreeNode* p, TreeNode* q)  //递归
{
	if (p == nullptr && q == nullptr)
	{
		return true;
	}
	else if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr))
	{
		return false;
	}
	else if (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSymmetric_1_item(TreeNode* left, TreeNode* right)
{
	if (!left && !right)
	{
		return true;
	}
	if (!left || !right)
	{
		return false;
	}
	if (left->val == right->val)
	{
		return isSymmetric_1_item(left->left, right->right) && isSymmetric_1_item(left->right, right->left);
	}
	else
	{
		return false;
	}
}
bool isSymmetric_1(TreeNode* root) //递归是否是对称的
{
	if (!root)
	{
		return true;
	}
	return isSymmetric_1_item(root->left, root->right);
}

bool isSymmetric_2(TreeNode* root) //迭代是否是对称的
{
	if (!root)
	{
		return true;
	}
	TreeNode *left = root->left, *right = root->right;
	stack<TreeNode *> lefts, rights;
	lefts.push(left);
	rights.push(right);
	while (!lefts.empty() && !rights.empty())
	{
		left = lefts.top();
		right = rights.top();
		lefts.pop(); rights.pop();
		if (!left && !right)
		{
			continue;  //因为两边可能都把null压入栈了，所以应该是跳过，不是返回
		}
		if (!left || !right)
		{
			return false;
		}
		if (left->val != right->val)
		{
			return false;
		}
		lefts.push(left->left);
		rights.push(right->right);
		lefts.push(left->right);
		rights.push(right->left);
	}
	return lefts.empty() && rights.empty();
}

int maxDepth(TreeNode* root)  //最大深度递归版本
{
	if (!root)
	{
		return 0;
	}
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

vector<TreeNode *> levelOrderBottom_item(vector<TreeNode *> v)
{
	vector<TreeNode *> result;
	for (int i=0; i<v.size(); ++i)
	{
		TreeNode* tmp = v.at(i);
		if (tmp->left)
		{
			result.push_back(tmp->left);
		}
		if (tmp->right)
		{
			result.push_back(tmp->right);
		}
	}
	return result;
}
vector<vector<int>> levelOrderBottom(TreeNode* root)  //自己的做法
{
	vector<vector<int>> result;
	if (!root)
	{
		return result;
	}
	vector<vector<TreeNode *>> r_t;
	vector<TreeNode *> tmp;
	tmp.push_back(root);
	while (true)
	{
		tmp = levelOrderBottom_item(tmp);
		if (tmp.size() < 1)
		{
			break;
		}
		r_t.push_back(tmp);
	}
	for (int i=r_t.size()-1; i>=0; --i)
	{
		vector<int> r_tmp;
		for (auto tn : r_t.at(i))
		{
			r_tmp.push_back(tn->val);
		}
		result.push_back(r_tmp);
	}
	return result;
}

void levelOrderBottom_c_item(vector<vector<int>> &result, queue<TreeNode *> q)
{
	if (q.empty())
	{
		return;
	}
	queue<TreeNode *> q_tmp;
	vector<int> r_tmp;
	while (!q.empty())
	{
		TreeNode *tmp = q.front();
		q.pop();
		r_tmp.push_back(tmp->val);
		if (tmp->left)
		{
			q_tmp.push(tmp->left);
		}
		if (tmp->right)
		{
			q_tmp.push(tmp->right);
		}
	}
	levelOrderBottom_c_item(result, q_tmp);
	result.push_back(r_tmp);
}
vector<vector<int>> levelOrderBottom_c(TreeNode* root)  //递归逆序
{
	vector<vector<int>> result;
	queue<TreeNode *> q;
	if (root)
	{
		q.push(root);
	}
	levelOrderBottom_c_item(result, q);
	return result;
}


TreeNode* sortedArrayToBST_item(vector<int>& nums, int start, int end)
{
	if (start == end)
	{
		return nullptr;
	}
	int tmp = nums.at((start+end) / 2);
	TreeNode *result = new TreeNode(tmp);
	result->left = sortedArrayToBST_item(nums, start, (start + end) / 2);
	result->right = sortedArrayToBST_item(nums, (start + end) / 2 + 1, end);
	return result;
}
TreeNode* sortedArrayToBST(vector<int>& nums)  //自己解法
{
	if (nums.size() == 0)
	{
		return nullptr;
	}
	if (nums.size() == 1)
	{
		return new TreeNode(nums.at(0));
	}
	return sortedArrayToBST_item(nums, 0, nums.size());
}

bool isBalanced(TreeNode* root)  //自己解法
{
	if (!root)
	{
		return true;
	}
	if (abs(maxDepth(root->left) - maxDepth(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int minDepth(TreeNode* root)
{
	if (!root)
	{
		return 0;
	}
	if (!root->right)  //由于要一直到叶子节点，因此如果右侧为空的话要遍历左侧
	{
		return minDepth(root->left) + 1;
	}
	if (!root->left)  //由于要一直到叶子节点，因此如果左侧为空的话要遍历右侧
	{
		return minDepth(root->right) + 1;
	}
	return min(minDepth(root->left), minDepth(root->right)) + 1;
}

bool hasPathSum(TreeNode* root, int sum)
{
	if (!root)
	{
		return false;
	}
	sum -= root->val;
	if (!root->left && !root->right)
	{
		return (sum == 0);
	}
	return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}

void generate_item(vector<vector<int>>& result, int numRows)
{
	vector<int> pre = result.at(result.size() - 1);
	vector<int> now(numRows, 1);
	for (int i = 1; i < numRows - 1; ++i)
	{
		now.at(i) = pre.at(i - 1) + pre.at(i);
	}
	result.push_back(now);
}
vector<vector<int>> generate(int numRows) 
{
	vector<vector<int>> result;
	if (numRows == 0)
	{
		return result;
	}
	for (int i = 1; i <= min(numRows, 2); ++i)
	{
		vector<int> tmp(i, 1);
		result.push_back(tmp);
	}
	for (int i = 3; i <= numRows; ++i)
	{
		generate_item(result, i);
	}
	return result;
}

vector<int> getRow(int rowIndex) 
{
	if (rowIndex <= 1)
	{
		return vector<int>(rowIndex + 1, 1);
	}
	vector<int> pre = getRow(rowIndex - 1);
	vector<int> result(rowIndex + 1, 1);
	for (int i = 1; i < rowIndex; ++i)
	{
		result.at(i) = pre.at(i - 1) + pre.at(i);
	}
	return result;
}

int maxProfit_1(vector<int>& prices) 
{
	int result = 0;
	for (int i = 0; i < prices.size(); ++i)
	{
		for (int j = i + 1; j < prices.size(); ++j)
		{
			result = max(result, prices.at(j) - prices.at(i));
		}
	}
	return result;
}

int maxProfit_2(vector<int>& prices) 
{
	if (prices.size() == 0)
	{
		return 0;
	}
	int minPrice = prices.at(0);
	int maxp = 0;
	for (auto i : prices)
	{
		if (i < minPrice)
		{
			minPrice = i;
		}
		else if (i - minPrice > maxp)
		{
			maxp = i - minPrice;
		}
	}
	return maxp;
}

int maxProfit_ii(vector<int>& prices) //买卖股票最大利润II
{
	if (prices.size() == 0)
	{
		return 0;
	}
	int minPrice = prices.at(0);
	int sum = 0;
	int prePrice = prices.at(0);
	for (int i = 1; i < prices.size(); ++i)
	{
		if (prices.at(i) <= prePrice)
		{
			sum += (prePrice - minPrice);
			minPrice = prices.at(i);
		}
		else if (i == prices.size() - 1 && prices.at(i) > minPrice)
		{
			sum += (prices.at(i) - minPrice);
		}
		prePrice = prices.at(i);
	}
	return sum;
}

bool isPalindrome(string s) //前后指针
{
	if (s.size() < 2)
	{
		return true;
	}
	int i = 0, j = s.size() - 1;
	while (j - i >= 1)
	{
		int iNum = static_cast<int>(s.at(i));
		int jNum = static_cast<int>(s.at(j));
		if (iNum < 48 || (iNum > 57 && iNum < 65) || (iNum > 90 && iNum < 97) || iNum > 122)
		{
			++i;
			continue;
		}
		if (jNum < 48 || (jNum > 57 && jNum < 65) || (jNum > 90 && jNum < 97) || jNum > 122)
		{
			--j;
			continue;
		}
		if (iNum > 47 && iNum < 58 && iNum != jNum)
		{
			return false;
		}
		if (iNum != jNum)
		{
			if (iNum > 64 && iNum < 91)
			{
				if (jNum - iNum != 32)
				{
					return false;
				}
			}
			else if (iNum > 96 && iNum < 123)
			{
				if (iNum - jNum != 32)
				{
					return false;
				}
			}
		}
		++i; --j;
	}
	return true;
}

int singleNumber_1(vector<int>& nums)  //map表，如果没有键值就添加，否则先前存在的话就是重复的，就删除
{
	map<int, int> m;
	for (auto i : nums)
	{
		if (m.find(i) == m.end())
		{
			m.insert(pair<int, int>(i, 1));
		}
		else
		{
			m.erase(i);
		}
	}
	return m.begin()->first;
}

int singleNumber_2(vector<int>& nums)  //先排序，再双指针
{
	sort(nums.begin(), nums.end());
	for (int i=0, j=1; j<nums.size(); i+=2, j+=2)  //因为重复元素出现两次，故为+2
	{
		if (nums.at(i) != nums.at(j))
		{
			return nums.at(i);
		}
	}
	return nums.at(nums.size() - 1);
}

int singleNumber_3(vector<int>& nums)  //先排序，然后当前元素与前后比较
{
	sort(nums.begin(), nums.end());
	if (nums.size() == 1 || nums.at(0) < nums.at(1))
	{
		return nums.at(0);
	}
	for (int i=1; i<nums.size()-1; ++i)
	{
		if (nums.at(i) > nums.at(i - 1) && nums.at(i) < nums.at(i + 1))
		{
			return nums.at(i);
		}
	}
	return nums.at(nums.size() - 1);
}

int singleNumber_4(vector<int>& nums)  //异或,元素异或自身为0，因此，只剩下单独的
{	
	int result = nums.at(0);
	for (int i = 1; i < nums.size(); ++i)
	{
		result = result ^ nums.at(i);
	}
	return result;
}

bool hasCycle_1(ListNode* head)  //set看是否重复
{
	set<ListNode*> s;
	while (head)
	{
		if (s.find(head) == s.end())
		{
			s.insert(head);
		}
		else
		{
			return true;
		}
		head = head->next;
	}
	return false;
}

bool hasCycle_2(ListNode* head)  //快慢指针,这里是快1步，实际上快几步都行
{
	if (!head || !head->next)
	{
		return false;
	}
	ListNode* fast = head->next->next;
	ListNode* slow = head->next;
	while (fast)
	{
		for (int i=0; i<2; ++i)
		{
			if (!fast)
			{
				return false;
			}
			if (fast == slow)
			{
				return true;
			}
			fast = fast->next;
		}
		slow = slow->next;
	}
	return false;
}

class MinStack {
public:
	/** initialize your data structure here. */
	stack<int> s;
	int minValue;
	MinStack() {

	}

	void push(int x) {
		if (s.empty() || this->minValue > x)
		{
			this->minValue = x;
		}
		s.push(x);
	}

	void pop() {   //这里可不可以改进呢
		if (minValue == s.top())
		{
			s.pop();
			if (s.empty())
			{
				this->minValue = NULL;
				return;
			}
			stack<int> s_tmp;
			this->minValue = s.top();
			while (!s.empty())
			{
				this->minValue = min(this->minValue, s.top());
				s_tmp.push(s.top());
				s.pop();
			}
			while (!s_tmp.empty())
			{
				s.push(s_tmp.top());
				s_tmp.pop();
			}
		}
		else
		{
			s.pop();
		}
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return this->minValue;
	}
};

ListNode *getIntersectionNode_1(ListNode *headA, ListNode *headB)  //相交链表,两个vector
{
	if (!headA || !headB)
	{
		return nullptr;
	}
	vector<ListNode *> a, b;
	while (headA)
	{
		a.push_back(headA);
		headA = headA->next;
	}
	while (headB)
	{
		b.push_back(headB);
		headB = headB->next;
	}
	int i = a.size() - 1, j = b.size() - 1;
	for (; i>=0 && j>=0; --i, --j)
	{
		if (a.at(i) != b.at(j))
		{
			break;
		}
	}
	if (i == a.size() - 1)
	{
		return nullptr;
	}
	i++;
	return a.at(i);
}

ListNode *getIntersectionNode_2(ListNode *headA, ListNode *headB)  //相交链表,将较长的那个多出来的部分可以裁剪掉
{
	if (!headA || !headB)
	{
		return nullptr;
	}
	int iA = 0, iB = 0;
	ListNode *tmpA = headA, *tmpB = headB;
	while (headA || headB)
	{
		if (headA)
		{
			++iA;
			headA = headA->next;
		}
		if (headB)
		{
			++iB;
			headB = headB->next;
		}
	}
	while (iA > iB)
	{
		tmpA = tmpA->next;
		--iA;
	}
	while (iB > iA)
	{
		tmpB = tmpB->next;
		--iB;
	}
	while (tmpA && tmpB)
	{
		if (tmpA == tmpB)
		{
			break;
		}
		tmpA = tmpA->next;
		tmpB = tmpB->next;
	}
	return tmpA;
}

vector<int> twoSum_ii(vector<int>& numbers, int target)  //两数之和 II - 输入有序数组
{                                                        //因为是已经排好序的，因此可以用前后双指针，当和大于target，则让右边指针减一，小于的话就让左边指针加一
	int i = 0, j = numbers.size() - 1;
	while (i != j)
	{
		if (numbers.at(i) + numbers.at(j) == target)
		{
			break;
		}
		else if (numbers.at(i) + numbers.at(j) > target)
		{
			--j;
		}
		else if (numbers.at(i) + numbers.at(j) < target)
		{
			++i;
		}
	}
	if (i == j)
	{
		return {};
	}
	else
	{
		return {i+1, j+1};
	}
}

string convertToTitle(int n)  //Excel表列名称
{
	string p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string result = "";
	while (n > 0)
	{
		int tmp = (n % 26 > 0 ? n % 26 - 1 : 25);   //由于题目中A是1，而这里A下标为0，因此要减一，而且n>=1的，如果要是余数为0的话，就是说n是26的倍数(非0),因此应该是Z，也即是下标为25的数
		result = p[tmp] + result;
		n /= 26;
		if (tmp == 25)  //当余数为0时，也就是说26的倍数，当前加的数p[tmp]成了z(就是26)，是从前一位借的1，所以前一位应该减去1，就是n--，比如26的话应该是z，26进制的话是A0，但是没有0，只能0变为26，A就要减去1变成没有了，故为z，26%26=0，p[tmp]="z",n /= 26为1，因为p[tmp]借了1，因此这个1应该减去1
		{
			n--;
		}
	}
	return result;
}

int majorityElement_1(vector<int>& nums)  //求众数--自己做法一
{
	int comp = nums.size() / 2;
	multimap<int, int> m;
	for (int i : nums)
	{
		if (m.find(i) != m.end())
		{
			m.find(i)->second += 1;
		}
		else
		{
			m.insert(pair<int, int>(i, 1));
		}
	}
	for (multimap<int, int>::iterator i = m.begin(); i != m.end(); i++)
	{
		if (i->second > comp)
		{
			return i->first;
		}
	}
	return NULL;
}

int majorityElement_2(vector<int>& nums)  //求众数--自己做法二
{
	if (nums.size() == 1)
	{
		return nums.at(0);
	}
	int comp = nums.size() / 2;
	multimap<int, int> m;
	for (int i : nums)
	{
		if (m.find(i) != m.end())
		{
			m.find(i)->second += 1;
			if (m.find(i)->second > comp)
			{
				return i;
			}
		}
		else
		{
			m.insert(pair<int, int>(i, 1));
		}
	}
	return NULL;
}

int majorityElement_3(vector<int>& nums)  //由于众数个数是大于n/2的，因此经过排序后，中间下界位置肯定是众数
{
	sort(nums.begin(), nums.end());
	return nums.at(nums.size() / 2);
}

int majorityElement_4(vector<int>& nums)  //Boyer-Moore 投票算法
{		
	//如果我们把众数记为 +1 ，把其他数记为 -1 ，将它们全部加起来，显然和大于 0 ，从结果本身我们可以看出众数比其他数多。
	//只要计数器等于0也就是说前面的众数与非众数数目相同，无法判断 ，我们就将 nums 中之前访问的数字全部忘记 ，并把当前数字当做候选的众数，直至最后计数器不为0的话的返回的数
	int count = 0;
	int candidate = NULL;
	for (int i : nums)
	{
		if (count == 0)
		{
			candidate = i;
		}
		count += (i == candidate ? 1 : -1);
	}
	return candidate;
}

int titleToNumber(string s)  //Excel表列序号
{
	int result = 0;
	for (int i = s.size() - 1; i >= 0; --i)
	{
		result += (pow(26, s.size() - 1 - i)* (s.at(i) - 'A' + 1));
	}
	return result;
}

int trailingZeroes(int n) //由于阶乘中肯定存在2的倍数大于5的倍数，因此这里用5的倍数来算
{
	//这里我们注意到，其实最后的0的个数，就是所有5的倍数，能够拆分成几个最小单位5来相乘，所有5的倍数拆出n/5个0，但是25的倍数拆出5后能继续拆出5，所以再加上n/25个0
	//而125的倍数经过上两个过程拆除了2个5后，还剩下5，共有n/125个0，同理625的倍数拆出3个5(5的三次方)后还剩下一个5，就是还有n/625个0，以此类推
	int result = 0;
	for (int i = 1; i <= log(n) / log(5); ++i)
	{
		result += (n / pow(5, i));
	}
	return result;
}

void rotate_1(vector<int>& nums, int k)   //旋转数组--暴力解法，每次旋转一个
{
	for (int i=0; i<k; ++i)
	{
		int tmp, pre = nums.at(nums.size() - 1);
		for (int j=0; j<nums.size(); ++j)
		{
			tmp = nums.at(j);
			nums.at(j) = pre;
			pre = tmp;
		}
	}
}

void rotate_2(vector<int>& nums, int k)  //环状替换
{
	if (k == 0 && nums.size() < 2)
	{
		return;
	}
	k = k % nums.size();
	int count = 0;
	for (int i = 0; count < nums.size(); ++i)  //所有元素都弄过一次，否则不会退出,因为有可能比如k=2，n=4，0->2->0就完了，但是1和3还没换呢，所以这里必须要再从1开始，也就是每个元素都要遍历一遍,所以count=nums.size才退出
	{
		int preIndex = i; //先前的元素的下标
		int preTmp = nums.at(i); //先前元素
		do 
		{
			int nowIndex = (preIndex + k) % nums.size();  //当前元素下标
			int nowTmp = nums.at(nowIndex);  //当前元素
			nums.at(nowIndex) = preTmp;
			preIndex = nowIndex;
			preTmp = nowTmp;
			++count;
		} while (i != preIndex);  //当前的环完了，再换下一个环
	}
}

void reverseRotate(vector<int> &nums, int start, int end)
{
	while (start < end)
	{
		int tmp = nums.at(end);
		nums.at(end) = nums.at(start);
		nums.at(start) = tmp;
		++start;
		--end;
	}
}

void rotate_3(vector<int>& nums, int k)  //反转--很骚
{
	//这个方法基于这个事实：当我们旋转数组 k 次， k%n个尾部元素会被移动到头部，剩下的元素会被向后移动。也就是反转三次，第一次整体反转，之后的第二三次是第一次反转完后前k个和后面的单独反转
	k = k % nums.size();
	reverseRotate(nums, 0, nums.size() - 1);
	reverseRotate(nums, 0, k - 1); //0到k-1一共k个数
	reverseRotate(nums, k, nums.size() - 1);
}

uint32_t reverseBits_1(uint32_t n)  //颠倒二进制位，就是反转,左移右移操作
{
	uint32_t result = 0;
	for (int i = 0; i < 32; ++i)
	{
		result <<= 1;  //移位之后再加n与1的按位且
		result += (n & 1);
		n >>= 1;
	}
	return result;
}

uint32_t reverseBits_2(uint32_t n)  //颠倒二进制位，就是反转,用bitset
{
	bitset<32> result = n;
	for (int i=0; i<16; ++i)
	{
		if (result[i] != result[31 - i])
		{
			result[i] = !result[i];
			result[31 - i] = !result[31 - i];
		}
	}
	return result.to_ulong();
}

int hammingWeight_1(uint32_t n)   //位1的个数,右移来做
{
	int count = 0;
	for (int i=0; i<32; ++i)
	{
		if (n & 1 > 0)
		{
			++count;
		}
		n >>= 1;
	}
	return count;
}

int hammingWeight_2(uint32_t n)   //位1的个数,bitset来做
{
	bitset<32> tmp = n;
	int count = 0;
	for (int i=0; i<32; ++i)
	{
		if (tmp[i] > 0)
		{
			++count;
		}
	}
	return count;
}

int hammingWeight_3(uint32_t n)  //骚操作，在二进制表示中，数字n中最低位的1总是对应n−1中的0.因此，将n和n−1进行与运算总是能把n中最低位的1变成0，并保持其他位不变。这样就消灭了一个1，计数器就加1
{
	int count = 0;
	while (n != 0)
	{
		++count;
		n &= (n - 1);
	}
	return count;
}

int rob(vector<int>& nums)  //很秀的一个动态规划题
{
	//这个题第一眼看上去，应该就能确定是用动态规划做，否则貌似没有其它办法.
	/*
	假设前i-1个房子已经有了最大值result[i-1]，前i-2个房子有了最大值result[i-2]，这时小偷走到了第i个房子，那他到底进不进去呢？
	如果要是进去，就说明第i-1个房子没有进去，也即是说在第i-1个房子他偷得的金额为0，也就是说，在进入第i个房子门但是还未偷钱时，他拥有的钱是前i-2个房子的最大值result[i-2]，此时最大值为result[i-2]+第i个房子的钱
	那要是不进去，那就走了，那他现在身上的钱就是前i-1个房子的最大值result[i-1]
	对于以上两种情况，小偷是贪婪的，因此肯定是取最大值啊
	所以递推式应该是result[i] = max(result[i-1], result[i-2]+nums.at(i))
	*/
	if (nums.size() == 1)
	{
		return nums.at(0);
	}
	if (nums.size() == 2)
	{
		return max(nums.at(0), nums.at(1));
	}
	int preMax = 0;  //代表result[i-2]
	int result = 0; 
	//迭代版本
	for (int i : nums)
	{
		int tmp = result;
		result = max(preMax + i, result);
		preMax = tmp;
	}
	return result;
}

bool isHappy_1(int n)  //快乐数
{   //经过大量实践，发现不是快乐数的话会有4->16->37->58->89->145->42->20->4->...的循环，所以你懂的
	while (true)
	{
		int sum = 0;
		while (n > 0)
		{
			int tmp = n % 10;
			sum += tmp * tmp;
			n /= 10;
		}
		if (sum == 4)
		{
			return false;
		}
		else if (sum == 1)
		{
			return true;
		}
		n = sum;
	}
	return false;
}

int squareSum(int n)  //平方和相加
{
	int sum = 0;
	while (n > 0)
	{
		int tmp = n % 10;
		sum += pow(tmp, 2);
		n /= 10;
	}
	return sum;
}
bool isHappy_2(int n)  //快乐数，快慢指针
{  //其实也是用了无论是否是快乐数都会产生循环
	int slow = n, fast = n;
	do 
	{  //因为循环，slow与fast总会在某个地方相遇
		slow = squareSum(slow);
		fast = squareSum(fast);
		fast = squareSum(fast);
	} while (slow != fast);
	return slow == 1;
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
	/*
	string s = "MCMXCIV";
	std::cout << romanToInt_1(s) << endl;
	*/

	//最长公共前缀
	/*
	vector<string> strs = {"flower","flow","flowht"};
	std::cout << longestCommonPrefix(strs) << endl;
	*/

	//判断有效括号
	/*
	string s = "))";
	std::cout << isBracketsValid(s) << endl;
	*/

	//合并两个有序链表 
	/*
	ListNode *l1 = new ListNode(1);
	ListNode *l2 = new ListNode(1);
	ListNode *l1t = l1;
	ListNode *l2t = l2;
	l1->next = new ListNode(2);
	l2->next = new ListNode(3);
	l1 = l1->next;
	l2 = l2->next;
	l1->next = new ListNode(4);
	l2->next = new ListNode(4);
	ListNode *l = mergeTwoLists(l1t, l2t);
	*/

	//删除排序数组中的重复项
	/*
	vector<int> v = {1,1,2};
	int len = removeDuplicates(v);
	std::cout << len << endl;
	for (int i=0; i<len; ++i)
	{
		std::cout << v.at(i) << " ";
	}
	std::cout << endl;
	*/

	//移除元素
	/*
	vector<int> v = {3,5};
	int len = removeElement(v, 3);
	std::cout << len << endl;
	for (int i = 0; i < len; ++i)
	{
		std::cout << v.at(i) << " ";
	}
	std::cout << endl;
	*/
	//实现 strStr(),给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。
	/*
	string haystack = "aaaaa";
	string needle = "baa";
	std::cout << strStr(haystack, needle) << endl;
	*/

	//给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。你可以假设数组中无重复元素
	/*
	vector<int> v = {1,3,5,6};
	std::cout << searchInsert(v, 5) << endl;
	*/

	//报数
	//报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。
	/*
	std::cout << countAndSay(7) << endl;
	*/

	//最大子序和
	//给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
	/*
	vector<int> v = {-2,1,-3,4,-1,2,1,-5,4};
	std::cout << maxSubArray_3(v) << endl;
	*/

	//最后一个单词的长度
	/*
	string s = "a ";
	std::cout << lengthOfLastWord(s) << endl;
	*/

	//加一
	//给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。
	/*
	vector<int> v = {8, 9};
	v = plusOne(v);
	for (auto i : v)
	{
		std::cout << i << " " << endl;
	}
	*/

	//二进制求和
	/*
	string a = "1", b = "111";
	std::cout << addBinary_1(a, b) << endl;
	*/

	//x 的平方根
	/*
	std::cout << mySqrt_2(3) << endl;
	*/

	//爬楼梯
	/*
	std::cout << climbStairs_2(4) << endl;
	*/

	//删除排序链表中的重复元素
	/*
	ListNode *l1 = new ListNode(1);
	ListNode *l1t = l1, *p;
	l1->next = new ListNode(1);
	l1 = l1->next;
	l1->next = new ListNode(2);
	l1 = l1->next;
	l1->next = new ListNode(4);
	p = deleteDuplicates_1(l1t);
	*/

	//合并两个有序数组
	/*
	vector<int> nums1 = {1,2,3,0,0,0};
	vector<int> nums2 = {2,5,6};
	merge_3(nums1, 3, nums2, 3);
	for (int num : nums1)
	{
		std::cout << num << " ";
	}
	std:; cout << endl;
	*/

	//相同的树
	//isSameTree

	//对称二叉树
	//isSymmetric_1
	
	//二叉树的最大深度
	//maxDepth

	//二叉树的层次遍历 II
	//levelOrderBottom

	//将有序数组转换为二叉搜索树
	//sortedArrayToBST

	//平衡二叉树
	//isBalanced

	// 二叉树的最小深度
	//minDepth

	//路径总和  
	//hasPathSum

	//杨辉三角
	//generate

	//杨辉三角2
	//getRow

	//买卖股票的最佳时机
	//maxProfit_2

	//买卖股票的最佳时机 II
	//maxProfit_ii

	//验证回文串
	/*
	string s = "";
	std::cout << isPalindrome(s) << endl;
	*/

	//只出现一次的数字
	/*
	vector<int> nums = {2,2,1};
	cout << singleNumber_4(nums) << endl;
	*/

	//环形链表
	//hasCycle_1;

	//相交链表
	//getIntersectionNode

	//两数之和 II - 输入有序数组
	//twoSum_ii

	//Excel表列名称
	/*
	cout << convertToTitle(701) << endl;
	*/

	//求众数
	//majorityElement

	//Excel表列序号
	/*
	string s = "ZY";
	cout << titleToNumber(s) << endl;
	*/

	//阶乘后的零
	//trailingZeroes

	//旋转数组
	/*
	vector<int> v = {-1,-100,3,99};
	rotate_1(v, 2);
	for (int i : v)
	{
		cout << i << " ";
	}
	cout << endl;
	*/

	//颠倒二进制位
	//reverseBits_2

	//位1的个数
	/*
	uint32_t n = 00000000000000000000000000001011;
	cout << hammingWeight_2(n) << endl;
	*/

	//打家劫舍
	/*
	vector<int> nums = {2,7,9,3,1};
	cout << rob(nums) << endl;
	

	//快乐数
	//isHappy
}
