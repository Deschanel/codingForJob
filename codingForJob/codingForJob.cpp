// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
#include <cmath>

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

ListNode* removeElements(ListNode* head, int val)
{
	while  (head && head->val == val)
	{
		head = head->next;
	}
	if(!head)
	{
		return nullptr;
	}
	ListNode *result = head;
	ListNode *tmp = head;
	head = head->next;
	while (head)
	{
		if(head->val == val)
		{
			tmp->next = head->next;
		}
		else
		{
			tmp = tmp->next;
		}
		head = head->next;
	}
	return result;
}

bool isPrime(int n)
{
	if(n <= 3)
	{
		return true;
	}
	for (int i = 2; i <sqrt(n)+1; ++i)
	{
		if(n % i == 0)
		{
			return false;
		}
	}
	return true;
}

int countPrimes_1(int n)   //计数质数,超时了
{
	int result = 0;
	for(int i=2; i<n; ++i)
	{
		if(isPrime(i))
		{
			++result;
		}
	}
	return result;
}

int countPrimes_2(int n)   //计数质数,厄拉多塞筛法
{
	int result = 0;
	vector<bool> flag(n, true);
	for (int i = 2; i < n; i++)
	{
		if(flag.at(i))
		{
			++result;
			for (int j = i*2; j < n; j+=i)
			{
				flag.at(j) = false;
			}
		}
	}
	return result;
}

bool isIsomorphic_1(string s, string t)  //同构字符串
{
	if(s.size() ==  0 && t.size() == 0)
        {
            return true;
        }
        map<char, char> a_m;
        map<char, char> b_m;
        for (int i = 0; i < s.size(); ++i)
        {
			//key为s中的字符
            if(a_m.find(s.at(i)) != a_m.end())
            {
                if(a_m.find(s.at(i))->second != t.at(i))
                {
                    return false;
                }
            }
            else
            {
                a_m.insert(pair<char, char>(s.at(i), t.at(i)));
            }
			//key为t中的字符
            if(b_m.find(t.at(i)) != b_m.end())
            {
                if(b_m.find(t.at(i))->second != s.at(i))
                {
                    return false;
                }
            }
            else
            {
                b_m.insert(pair<char, char>(t.at(i), s.at(i)));
            }
        }
        return true;
}

bool isIsomorphic_2(string s, string t)  //同构字符串,骚操作，当前元素在字符串中的第一个出现的位置不一样就错误，否则正确
{
	if(s.size() ==  0 && t.size() == 0)
        {
            return true;
        }
	for (int i = 0; i < s.size(); i++)
	{
		if(s.find(s.at(i)) != t.find(t.at(i)))
		{
			return false;
		}
	}
	return true;
}

ListNode* reverseList_1(ListNode* head)  //反转链表,简单版本
{
	if(!head)
	{
		return nullptr;
	}
	if(!head->next)
	{
		return head;
	}
	stack<ListNode *> s;
	while (head)
	{
		s.push(head);
		head = head->next;
	}
	ListNode * tmp = s.top();
	s.pop();
	ListNode *result = tmp;
	while (!s.empty())
	{
		tmp->next = s.top();
		s.pop();
		tmp = tmp->next;
	}
	return result;
}

ListNode* reverseList_2(ListNode* head)  //反转链表,递归版本
{
	if(!head)
	{
		return nullptr;
	}
	if(!head->next)
	{
		return head;
	}
	ListNode *tmp = reverseList_2(head->next);
	head->next = nullptr;
	ListNode *result = tmp;
	while (true)
	{
		if(!tmp->next)
		{
			break;
		}
		tmp = tmp->next;
	}
	tmp->next = head;
	return result;
}

ListNode* reverseList_3(ListNode* head)  //反转链表,迭代版本
{
	ListNode *pre = nullptr;
	ListNode *now = head;
	while (now)
	{
		ListNode *tmp = now->next;
		now->next = pre;
		pre = now;
		now = tmp;
	}
	return pre;
}

bool containsDuplicate_1(vector<int>& nums)  //存在重复元素，set表
{
	set<int> s;
	for (int i : nums)
	{
		if (s.find(i) != s.end())
		{
			return true;
		}
		else
		{
			s.insert(i);
		}
	}
	return false;
}

bool containsDuplicate_2(vector<int>& nums)  //存在重复元素，先排序
{
	if (nums.size() == 0)
	{
		return false;
	}
	sort(nums.begin(), nums.end());
	for (int i=0; i<nums.size()-1; ++i)
	{
		if (nums.at(i) == nums.at(i + 1))
		{
			return true;
		}
	}
	return false;
}

bool containsNearbyDuplicate_1(vector<int>& nums, int k)  //存在重复元素II,笨办法,超时了
{
	if (k == 0 || nums.size() == 0)
	{
		return false;
	}
	if (k > nums.size() - 1)
	{
		k = nums.size() - 1;
	}
	for (int i=0; i<nums.size()-1; ++i)
	{
		int tmp = nums.at(i);
		for (int j=1; j<=k; ++j)
		{
			if (i + j > nums.size() - 1)
			{
				break;
			}
			if (tmp == nums.at(i + j))
			{
				return true;
			}
		}
	}
	return false;
}

bool containsNearbyDuplicate_2(vector<int>& nums, int k)  //存在重复元素II,map试一下
{
	if (k == 0 || nums.size() == 0)
	{
		return false;
	}
	if (k > nums.size() - 1)
	{
		k = nums.size() - 1;
	}
	map<int, int> m;
	for (int i=0; i<nums.size(); ++i)
	{
		if (m.find(nums.at(i)) != m.end())
		{
			if (abs(m.find(nums.at(i))->second - i) <= k)
			{
				return true;
			}
			else
			{
				m.find(nums.at(i))->second = i;
			}
		}
		else
		{
			m.insert(pair<int, int>(nums.at(i), i));
		}
	}
	return false;
}

class MyStack_1 {  //队列实现栈，pop里有个临时queue
public:
	/** Initialize your data structure here. */
	queue<int> q;
	int topNum;
	MyStack_1() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		q.push(x);
		topNum = x;
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		queue<int> tmp; //临时queue，来存储还没pop的元素
		while (1 < q.size())
		{
			topNum = q.front();
			tmp.push(q.front());
			q.pop();
			if (q.size() == 1)
			{
				break;
			}
		}
		int result = q.front();
		q.pop();
		q = tmp;
		return result;
	}

	/** Get the top element. */
	int top() {
		return topNum;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q.empty();
	}
};

class MyStack_2 {   //队列实现栈，没有临时queue
public:
	/** Initialize your data structure here. */
	queue<int> q;
	int topNum;
	MyStack_2() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		q.push(x);
		int i = 1;
		int qSize = q.size();
		while (i < qSize)  //反转
		{
			topNum = q.front();
			q.pop();
			q.push(topNum);
			++i;
		}
		topNum = x;
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int result = q.front();
		q.pop();
		topNum = q.front();
		return result;
	}

	/** Get the top element. */
	int top() {
		return topNum;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q.empty();
	}
};

TreeNode* invertTree(TreeNode* root)   //递归版本
{
	if (!root || (!root->left && !root->right))
	{
		return root;
	}
	if (!root->left && root->right && !root->right->left && !root->right->right)
	{
		root->left = root->right;
		root->right = nullptr;
	}
	else if (!root->right && root->left && !root->left->left && !root->left->right)
	{
		root->right = root->left;
		root->left = nullptr;
	}
	else if (root->left && root->right && !root->left->left && !root->left->right && !root->right->left && !root->right->right)
	{
		TreeNode *tmp = root->left;
		root->left = root->right;
		root->right = tmp;
	}
	else
	{
		TreeNode *ltmp = invertTree(root->left);
		TreeNode *rtmp = invertTree(root->right);
		root->left = rtmp;
		root->right = ltmp;
	}
	return root;
}

bool isPowerOfTwo_1(int n)  //2的幂，bitset做，二进制只能有一个1，否则不行
{
	if (n < 1)
	{
		return false;
	}
	bitset<32> b(n);
	int sum = 0;
	for (int i=0; i<b.size(); ++i)
	{
		sum += b[i] * b[i];
	}
	if (sum == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isPowerOfTwo_2(int n)  //转换成二进制，里面只能有一个1
{
	if (n < 1)
	{
		return false;
	}
	int sum = 0;
	while (n > 0)
	{
		int tmp = n % 2;
		sum += tmp * tmp;
		n /= 2;
	}
	if (sum == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class MyQueue {  //也可以用两个栈实现
public:
	/** Initialize your data structure here. */
	stack<int> s;
	int frontNum;
	MyQueue() {

	}

	void reverseStack(stack<int> &s)
	{
		if (s.empty() || s.size() == 1)
		{
			return;
		}
		int tmp1 = s.top();
		s.pop();
		reverseStack(s);
		int tmp2 = s.top();
		s.pop();
		reverseStack(s);
		s.push(tmp1);
		reverseStack(s);
		s.push(tmp2);
	}
	/** Push element x to the back of queue. */
	void push(int x) {
		reverseStack(s);  //由于先插入的在上面，因此要先反转回原来样子(后插入的在顶部)，然后插入，这样就是整体满足越往后插入越靠上
		s.push(x);
		reverseStack(s); 
		frontNum = s.top();
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		int result = s.top();
		s.pop();
		if (!s.empty())
		{
			frontNum = s.top();
		}
		else
		{
			frontNum = NULL;
		}
		return result;
	}

	/** Get the front element. */
	int peek() {
		return frontNum;
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return s.empty();
	}
};

bool isPalindrome_1(ListNode* head)  //回文链表,O(n)空间复杂度
{
	if (!head)
	{
		return true;
	}
	vector<int> v;
	while (head)
	{
		v.push_back(head->val);
		head = head->next;
	}
	int i = 0, j = v.size() - 1;
	while (i < j)
	{
		if (v[i] != v[j])
		{
			return false;
		}
		++i;
		--j;
	}
	return true;
}

bool isPalindrome_2(ListNode* head)  //回文链表,O(1)空间复杂度
{
	if (!head || !head->next)
	{
		return true;
	}
	ListNode *pre = nullptr;
	ListNode *prepre = nullptr;
	ListNode *slow = head;
	ListNode *fast = head->next;
	while (fast && fast->next)
	{
		//反转前半段链表
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
		//反转
		pre->next = prepre;
		prepre = pre;
	}
	ListNode *p2 = slow->next;
	slow->next = pre;
	ListNode *p1 = (fast == nullptr ? slow->next : slow);
	while (p1)
	{
		if (p1->val != p2->val)
		{
			return false;
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}

TreeNode* lowestCommonAncestor_1(TreeNode* root, TreeNode* p, TreeNode* q)  //二叉搜索树的最近公共祖先,递归版本
{
	//从中序遍历序列看出，如果pq的值都小于当前root值，那么都在左子树，都大于当前root值，都在右子树，如果一个大于一个小于，那么分别在左右子树，那么最小祖先就是当前root节点
	//很显然递归到最后,两个节点位置肯定是一个在左子树一个在右子树
	if (p->val < root->val && q->val < root->val)
	{
		return lowestCommonAncestor_1(root->left, p, q);
	}
	else if (p->val > root->val && q->val > root->val)
	{
		return lowestCommonAncestor_1(root->right, p, q);
	}
	else
	{
		return root;
	}
}

TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)  //二叉搜索树的最近公共祖先,迭代版本
{
	while (root)
	{
		if (p->val < root->val && q->val < root->val)
		{
			root = root->left;
		}
		else if (p->val > root->val && q->val > root->val)
		{
			root = root->right;
		}
		else
		{
			break;
		}
	}
	return root;
}

void deleteNode(ListNode* node)  //删除链表中的节点
{
	//刚看到这个题有点懵，没有给head节点
	if (!node->next)
	{
		node = nullptr;
	}
	else
	{
		node->val = node->next->val;
		node->next = node->next->next;
	}
}

bool isAnagram_1(string s, string t)  //有效的字母异位词,两个map
{
	if (s.size() != t.size())
	{
		return false;
	}
	map<char, int> s_m;
	map<char, int> t_m;
	for (int i=0; i<s.size(); ++i)
	{
		if (s_m.find(s[i]) != s_m.end())
		{
			s_m.find(s[i])->second++;
		}
		else
		{
			s_m.insert(pair<char, int>(s[i], 1));
		}
		if (t_m.find(t[i]) != t_m.end())
		{
			t_m.find(t[i])->second++;
		}
		else
		{
			t_m.insert(pair<char, int>(t[i], 1));
		}
	}
	map<char, int>::iterator si=s_m.begin(), ti=t_m.begin();
	for (; si!=s_m.end() && ti!=t_m.end(); si++,ti++)
	{
		if (si->first != ti->first)
		{
			return false;
		}
		if (si->second != ti->second)
		{
			return false;
		}
	}
	return true;
}

bool isAnagram_2(string s, string t)  //有效的字母异位词,一个map
{
	if (s.size() != t.size())
	{
		return false;
	}
	map<char, int> m;
	for (int i=0; i<s.size(); ++i)
	{
		if (t[i] == s[i])
		{
			continue;
		}
		if (m.find(s[i]) != m.end())
		{
			m.find(s[i])->second++;
		}
		else
		{
			m.insert(pair<char, int>(s[i], 1));
		}
		if (m.find(t[i]) != m.end())
		{
			m.find(t[i])->second--;
		}
		else
		{
			m.insert(pair<char, int>(t[i], -1));
		}
	}
	for (map<char, int>::iterator i=m.begin(); i!=m.end(); i++)
	{
		if (i->second > 0)
		{
			return false;
		}
	}
	return true;
}

void getAllPaths(TreeNode *root, string path, vector<string> &sv)
{
	if (!root)
	{
		return;
	}
	if (path.size() == 0)
	{
		path += std::to_string(root->val);
	}
	else
	{
		path += ("->" + std::to_string(root->val));
	}
	if (!root->left && !root->right)
	{
		sv.push_back(path);
		return;
	}
	getAllPaths(root->left, path, sv);
	getAllPaths(root->right, path, sv);
}

vector<string> binaryTreePaths_1(TreeNode* root)   //二叉树的所有路径,递归版本
{
	vector<string> result;
	getAllPaths(root, "", result);
	return result;
}

int addDigits_1(int num)   //各位相加，循环版本
{
	while (num >= 10)
	{
		int sum = 0;
		while (num > 0)
		{
			sum += num % 10;
			num /= 10;
		}
		num = sum;
	}
	return num;
}


int addDigits_2(int num)   //各位相加，递归版本
{
	if (num < 10)
	{
		return num;
	}
	int sum = 0;
	while (num > 0)
	{
		sum += (num % 10);
		num /= 10;
	}
	return addDigits_2(sum);
}

int addDigits_3(int num)   //各位相加，O(1)时间
{
	//这个需要去想想
	//我们来思考那个循环解法，假设当前到了某个数(各位的数字)x1x2x3x4...xi,也就是x1*pow(10, i-1) + x2*pow(10, i-2) +.....+xi，各位数字加起来就是x1+x2+x3+...+xi
	//前者减去后者就是x1*999..9(i-2个9)+x2*99..9(i-3个9)+....，最后得到的那个数就是小于9的结果，则累加得到
	//num = x1x2x3...xn - result = 9*(某个整数),而result是小于等于9的，则num - 1 = result - 1 + 9*(某个整数),result - 1小于9，则左右两边模9的话就是(num-1)%9 = result - 1
	//则答案就是(num - 1)%9+1
	return (num - 1) % 9 + 1;
}

bool isUgly(int num)   //递归求解,假设num除到某个数之前一直满足丑数定义，那么接下来，如果其模2为0，那么再看其除以2之后的是不是满足条件，同理
{
	if (num <= 0)
	{
		return false;
	}
	if (num == 1)
	{
		return true;
	}
	if (num % 2 == 0)
	{
		return isUgly(num / 2);
	}
	else if (num % 3 == 0)
	{
		return isUgly(num / 3);
	}
	else if (num % 5 == 0)
	{
		return isUgly(num / 5);
	}
	else
	{
		return false;
	}
}

int missingNumber_1(vector<int>& nums)  //缺失数字,先排序，然后找下标与值不对应的第一个数字，这个下标就是结果
{
	sort(nums.begin(), nums.end());
	for (int i=0; i<nums.size(); ++i)
	{
		if (i != nums.at(i))
		{
			return i;
		}
	}
	return nums.at(nums.size() - 1) + 1;   //如果一直到n-1都有的话，那么就是少了n
}

int missingNumber_2(vector<int>& nums)  //缺失数字,初始化数组元素都为0，哪个值有就令对应下标的值为1，最后看看哪个下标的值为0
{
	vector<int> v(nums.size() + 1, 0);
	for (int i: nums)
	{
		v.at(i) = 1;
	}
	for (int i=0; i<v.size(); ++i)
	{
		if (v.at(i) == 0)
		{
			return i;
		}
	}
	return NULL;
}

int missingNumber_3(vector<int>& nums)  //高斯公式
{
	int allSum = nums.size()*(nums.size() + 1) / 2;
	int sum = 0;
	for (int i : nums)
	{
		sum += i;
	}
	return allSum - sum;
}

bool isBadVersion(int version)  //随便写的，题目上没给出具体函数
{
	return false;
}

int firstBadVersion(int n)  //第一个错误的版本
{
	//二分查找
	int left = 0, right = n;
	while (left < right)
	{
		int mid = 0;
		if (left % 2 != 0 && right % 2 != 0)  //这个if else 是为了防止溢出
		{
			mid = left / 2 + right / 2 + 1;
		}
		else
		{
			mid = left / 2 + right / 2;
		}
		if (!isBadVersion(mid))  //这个函数没有
		{
			left = mid + 1;
		}
		else
		{
			if ( mid == 0 || (mid > 1 && !isBadVersion(mid - 1)) )
			{
				return mid;
			}
			right = mid;
		}
	}
	return left;
}

void moveZeroes_1(vector<int>& nums)  //移动零
{
	if (nums.size() == 0)
	{
		return;
	}
	if (nums.size() == 1 && nums.at(0) != 0)
	{
		return;
	}
	for (int i=0; i<nums.size(); ++i)
	{
		if (nums.at(i) == 0)
		{
			for (int j=i+1; j<nums.size(); ++j)
			{
				if (nums.at(j) != 0)
				{
					swap(nums.at(i), nums.at(j));
					break;
				}
			}
		}
	}
}

void moveZeroes_2(vector<int>& nums)  //移动零,记录当前最靠前的0的位置(也就是要交换的位置，让其与第一个不为0的元素交换)
{
	int pos = 0;  //当前位置是0且是要交换的位置
	for (int i=0; i<nums.size(); ++i)  //也就是pos和i构成快慢指针
	{
		if (nums.at(i) != 0)
		{
			swap(nums.at(i), nums.at(pos));
			pos++;
		}
	}
}

bool wordPattern(string pattern, string str)  //单词规律，用两个map来记录
{
	if (pattern.size() == 0 && str.size() == 0)
	{
		return true;
	}
	else if (pattern.size() == 0 || str.size() == 0)
	{
		return false;
	}
	map<char, string> p2s;
	map<string, char> s2p;
	int j = 0, i = 0;
	for (; i < pattern.size(); ++i)
	{
		string tmp = "";
		for (; j < str.size(); ++j)
		{
			if (str[j] != ' ')
			{
				tmp += str[j];
			}
			else
			{
				break;
			}
		}
		if (p2s.find(pattern[i]) != p2s.end())
		{
			if (p2s.find(pattern[i])->second != tmp)
			{
				return false;
			}
		}
		else
		{
			p2s.insert(pair<char, string>(pattern[i], tmp));
		}
		if (s2p.find(tmp) != s2p.end())
		{
			if (s2p.find(tmp)->second != pattern[i])
			{
				return false;
			}
		}
		else
		{
			s2p.insert(pair<string, char>(tmp, pattern[i]));
		}
		++j;  //因为当前的为空格，因此跳到下一个
	}
	return (i == pattern.size() && j == str.size() + 1);  //由于最后有个++j，因此这个j最后是超过str的size的
}

bool canWinNim_1(int n)  //Nim 游戏，减而治之
{
	//在这里我们可以分析，因为两个人最多拿6个，这里我们可以假设最后剩下1，2，3，4，5，6个
	//最后剩下1，2，3个，当且仅当你拿的时候才赢，也就是说朋友要拿到第n-3个或第n-2个或第n-1个，也就是说第n-3个朋友一定要拿，但是朋友是聪明的，怎么才能一定让他拿第n-3个呢，办法就是第n-4个你拿到，那么第n-3个朋友一定得拿，所以此时条件就是你上一次拿完时还剩4个
	//最后剩下4个，那么此时当且仅当是到了朋友拿的时候才行，也就是说条件是你上一次拿完时还剩4个
	//最后剩下5个，可以试一下，只有此时你拿1个的情况下，你才能赢，因此条件是你这次拿完还剩4个
	//最后6个时候，可以试一下，只有此时你拿2个的情况下，你才能赢，因此条件是你这次拿完还剩4个
	//综上所述，只有当你拿完还剩最后4个的情况下你才能赢；那么如何确保你拿完还剩4个呢，也就是确保你正好拿到第n-4个呢？
	//用减而治之思想，去掉最后4个，我们把第n-4个当作最后一个，也就是说你正好拿到第n-4个，这样才满足上述必赢条件，那么根据上述分析当且仅当你拿到第n-8个时候才行，同理。。。因此用下面递归
	if (n < 4)
	{
		return true;
	}
	else if (n == 4)
	{
		return false;
	}
	return canWinNim_1(n - 4);
}
bool canWinNim_2(int n)  //Nim 游戏,O（1）时间
{
	//根据上述减而治之得思想，我们可以一直往前推n,n-4,n-8,....begin(begin<=4)
	//也就是说n=begin+4*i,也就是说要赢的话，必须要恰好拿到第begin个，如果begin<=3得，那么能赢，如果begin==4得话，就赢不了
	//而且我们可以得到 n % 4 == begin % 4,而begin % 4 > 0得话，就是begin为1，2，3，那么能赢;begin % 4 = 0得话，就是begin=4，就输
	//也就是n % 4 > 0的话就赢，否则就输
	return n % 4;
}

string getHint(string secret, string guess)  //猜数字游戏
{
	int countA = 0, countB = 0;
	//先公牛
	for (int i = 0; i < secret.size(); ++i)
	{
		if (secret.at(i) == guess.at(i))
		{
			++countA;
			secret.at(i) = '#';
			guess.at(i) = '*';
		}
	}
	//再奶牛
	for (int i = 0; i < secret.size(); ++i)
	{
		int pos = guess.find(secret.at(i));
		if (pos != guess.npos)
		{
			++countB;
			guess.at(pos) = '*';
		}
	}
	return std::to_string(countA) + "A" + std::to_string(countB) + "B";
}

class NumArray_1 {  //区域和检索 - 数组不可变
public:
	vector<int> numv;
	NumArray_1(vector<int>& nums) {
		this->numv = nums;
	}

	int sumRange(int i, int j) {
		if (j >= numv.size())
		{
			return NULL;
		}
		int sum = 0;
		for (; i <= j; ++i)
		{
			sum += numv.at(i);
		}
		return sum;
	}
};

class NumArray_2 {  //区域和检索 - 数组不可变,建立缓存
public:
	vector<int> sum;  //建立和数组，每个下标i表示前i项的和
	NumArray_2(vector<int>& nums) {
		if (nums.size())
		{
			sum.push_back(nums.at(0));
			for (int i = 1; i < nums.size(); ++i)
			{
				sum.push_back(sum.at(i - 1) + nums.at(i));
			}
		}
	}

	int sumRange(int i, int j) {
		if (i == 0) 
		{
			return sum.at(j);
		}
		else
		{
			return sum.at(j) - sum.at(i - 1);
		}
	}
};

bool isPowerOfThree_1(int n)  //递归版本,3的幂
{
	if (n == 1 || n == 3)
	{
		return true;
	}
	if (n < 3)
	{
		return false;
	}
	if (n % 3 == 0)
	{
		return isPowerOfThree_1(n / 3);
	}
	return false;
}

bool isPowerOfThree_2(int n)  //循环版本,3的幂
{
	if (n < 1)
	{
		return false;
	}
	if (n == 1)
	{
		return true;
	}
	while (n > 1)
	{
		if (n % 3 != 0)
		{
			return false;
		}
		n /= 3;
	}
	return n == 1;
}

void reverseString(vector<char>& s)  //反转字符串
{
	if (s.size() <= 1)
	{
		return;
	}
	int begin = 0, end = s.size() - 1;
	while (begin < end)
	{
		swap(s.at(begin), s.at(end));
		++begin;
		--end;
	}
}

string reverseVowels(string s)  //反转字符串中的元音字母
{
	if (s.size() <= 1)
	{
		return s;
	}
	int begin = 0, end = s.size() - 1;
	string pattern = "aeiouAEIOU";
	while (begin < end)
	{
		if (pattern.find(s.at(begin)) != pattern.npos)
		{
			if (pattern.find(s.at(end)) != pattern.npos)
			{
				swap(s.at(begin), s.at(end));
				++begin;
				--end;
			}
			else
			{
				--end;
			}
		}
		else
		{
			if (pattern.find(s.at(end)) != pattern.npos)
			{
				++begin;
			}
			else
			{
				++begin;
				--end;
			}
		}
	}
	return s;
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2)  //两个数组的交集
{
	vector<int> result;
	set<int> s1, s2;
	for (int i : nums1)
	{
		s1.insert(i);
	}
	for (int i : nums2)
	{
		s2.insert(i);
	}
	set<int>::iterator s1i = s1.begin(), s2i = s2.begin();
	for (; s1i != s1.end() && s2i != s2.end();)
	{
		if ((*s1i) == (*s2i))
		{
			result.push_back(*s1i);
			s1i++;
			s2i++;
		}
		else if ((*s1i) < (*s2i))
		{
			s1i++;
		}
		else
		{
			s2i++;
		}
	}
	return result;
}

vector<int> intersect(vector<int>& nums1, vector<int>& nums2)  //两个数组的交集 II
{
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());
	vector<int> result;
	for (int i = 0, j = 0; j < nums2.size() && i < nums1.size();)
	{
		if (nums1.at(i) == nums2.at(j))
		{
			result.push_back(nums1.at(i));
			++i;
			++j;
		}
		else if (nums1.at(i) < nums2.at(j))
		{
			++i;
		}
		else
		{
			++j;
		}
	}
	return result;
}

bool isPerfectSquare(int num)  //有效的完全平方数
{
	if (num == 1 || num == 4)
	{
		return true;
	}
	else if (num == 2 || num == 3)
	{
		return false;
	}
	else if (num % 4 > 1)  //完全平方数模4只能是0或1
	{
		return false;
	}
	for (int i = 3; i < num / 2; ++i)
	{
		if (i*i == num)
		{
			return true;
		}
		else if (i*i > num)
		{
			break;
		}
	}
	return false;
}

int getSum(int a, int b)  //两整数之和
{
	bitset<32> a_b(a);
	bitset<32> b_b(b);
	bitset<32> result(0);
	int jinwei = 0;
	for (int i=0; i<32; ++i)
	{
		result[i] = (a_b[i] ^ b_b[i]) ^ jinwei;
		bool tmp = a_b[i] == 1 && b_b[i] == 1;
		tmp = tmp || (b_b[i] == 1 && jinwei == 1);
		tmp = tmp || (a_b[i] == 1 && jinwei == 1);
		if (tmp)
		{
			jinwei = 1;
		}
		else
		{
			jinwei = 0;
		}
	}
	return result.to_ulong();
}

int guess(int num)
{
	return 0;
}

int guessNumber(int n)  //猜数字大小
{
	int right = n, left = 0;
	//相当于在left和right之间找数
	while (left < right)
	{
		int mid = 0;
		if (left % 2 != 0 && right % 2 != 0)
		{
			mid = left / 2 + right / 2 + 1;
		}
		else
		{
			mid = left / 2 + right / 2;
		}
		if (guess(mid) == 0)
		{
			return mid;
		}
		else if(guess(mid) == 1)
		{
			left = mid + 1;
		}
		else if (guess(mid) == -1)
		{
			right = mid;
		}
	}
	return left;
}

bool canConstruct(string ransomNote, string magazine)  //赎金信
{
	map<char, int> m_m;
	for (auto i : magazine)
	{
		if (m_m.find(i) != m_m.end())
		{
			m_m.find(i)->second++;
		}
		else
		{
			m_m.insert(pair<char, int>(i, 1));
		}
	}
	for (auto i : ransomNote)
	{
		if (m_m.find(i) == m_m.end() || m_m.find(i)->second < 1)
		{
			return false;
		}
		m_m.find(i)->second--;
	}
	return true;
}

int firstUniqChar(string s)   //字符串中的第一个唯一字符
{
	map<char, int> m;  //int是其出现的次数
	for (auto i : s)  //先记录所有元素出现的次数
	{
		if (m.find(i) != m.end())
		{
			m.find(i)->second++;
		}
		else
		{
			m.insert(pair<char, int>(i, 1));
		}
	} 
	for (int i=0; i<s.size(); ++i)   //遍历s，如果其中某个元素在已经构建好的map中只出现一次，那就返回下标
	{
		if (m.find(s.at(i))->second == 1)
		{
			return i;
		}
	}
	return -1;
}

char findTheDifference(string s, string t)  //找不同
{   //由于t是s经过随机重排且再加上一个字母，随机重排后字母个数与出现次数是一样的，也就多了一个字母，因此就把char转换成int，s与t进行按位异或，最后的得到int值就是添加的值的ascii值
	int sum = 0;
	int i = 0, j = 0;
	for (; i<s.size()&& j<t.size(); ++i, ++j)
	{
		sum = sum ^ (static_cast<int>(s.at(i)) ^ static_cast<int>(t.at(j)));
	}
	sum = sum ^ static_cast<int>(t.at(j));
	return static_cast<char>(sum);
}

bool isSubsequence(string s, string t)  //判断子序列
{
	if (s.size() == 0)
	{
		return true;
	}
	if (s.size() > t.size())
	{
		return false;
	}
	int index = 0;
	int i = 0;
	for (; i<t.size(); ++i)  //依据顺序遍历，如果在t中找到s中下标为index的值，那么指针指向index+1的值，然后在i+1之后的字符串中寻找其，这样就能满足index之后的值只能在index对应的t中的值后面查找
	{
		if (index == s.size())
		{
			break;
		}
		if (t.at(i) == s.at(index))
		{
			index += 1;
		}
	}
	return index == s.size();
}

void combination(vector<string> &result, int start, int picked, int &num, vector<int> &tmp, vector<int> &tt)  //递归求解n个球取m个的所有可能这种问题
{
	if (picked == num)  //如果选入的个数picked与想要的个数num相等
	{
		int minsum = 0, hoursum = 0;
		for (int i : tt)
		{
			if (i < 60)
			{
				minsum += i;
			}
			else
			{
				hoursum += i;
			}
		}
		if (minsum < 60 && hoursum <= 660)
		{
			string s;
			if (minsum < 10)
			{
				s =  "0" + std::to_string(minsum);
			}
			else
			{
				s = std::to_string(minsum);
			}
			s = std::to_string(hoursum / 60) + ":" + s;
			result.push_back(s);
		}
		return;
	}
	int ma = tmp.size() - num + picked;  //ma指的是，选取了picked个后，从剩下的球中能够选取的最大的数值。比如1234选取2个，已经选取了0个，那么第一个数最大只能选取下标为2(也就是数3)，否则如果直接选择数4的话，第二个数没法选择了
	for (int i=start; i<=ma; ++i)
	{
		tt.at(picked) = tmp.at(i); //当前选择了
		combination(result, i + 1, picked + 1, num, tmp, tt);  //下一个选取
	}
}

vector<string> readBinaryWatch(int num)  //二进制手表
{
	vector<string> result;
	if (num > 8)
	{
		return result;
	}
	else if(num == 0)
	{
		return { "0:00" };
	}
	vector<int> tmp = { 1, 2, 4, 8, 16, 32, 60, 120, 240, 480 };
	vector<int> tt(num, 0);
	combination(result, 0, 0, num, tmp, tt);
	return result;
}

int sumOfLeftLeaves(TreeNode* root)  //左叶子之和
{
	if (!root)  //如果节点为空
	{
		return 0;
	}
	if (!root->left)  //如果节点左为空，那么就返回右孩子的左节点和
	{
		return sumOfLeftLeaves(root->right);
	}
	//如果左节点不为空
	int sum = 0;
	if (!root->left->right && !root->left->left)  //如果左孩子为叶子节点
	{
		sum += root->left->val;
	}
	else
	{
		sum += sumOfLeftLeaves(root->left);  //左孩子不为叶子节点就加上左孩子的左节点和
	}
	sum += sumOfLeftLeaves(root->right);
	//以下简写
	//if (!root->left->right && !root->left->left)  //如果左节点确实为叶子
	//{
	//	sum += root->left->val;
	//}
	//sum += (sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right));  //如果左节点为叶子，那么其实sumOfLeftLeaves(root->left)返回为0，这里加上也无伤大雅，如果左节点不为叶子，那么就应该加上左右孩子的左节点和
	return sum;
}


string toHex_1(int num)  //数字转换为十六进制数,笨做法
{
	if (num > 2147483647 || num < -2147483648)
	{
		return "";
	}
	if (num == 0)
	{
		return "0";
	}
	string result = "";
	vector<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	map<char, char> m;
	for (int i = 0; i < 16; ++i)
	{
		m.insert(pair<char, char>(digits[i], digits[15 - i]));
	}
	unsigned int tmp = 0;
	if (num < 0)
	{
		tmp = (unsigned int)0 - (unsigned int)num;
	}
	else
	{
		tmp = num;
	}
	while (tmp > 0)
	{
		result = digits[tmp % 16] + result;
		tmp /= 16;
	}
	if (num > 0 || num == -2147483648)  //-2147483648这个找其绝对值的正整数是有问题的
	{
		return result;
	}
	//取反
	for (int i = 0; i < result.size(); ++i)
	{
		result[i] = m.find(result[i])->second;
	}
	//加一
	int i = result.size() - 1;
	while (i >= 0)
	{
		if (result[i] != 'f')
		{
			if (result[i] == '9')
			{
				result[i] = 'a';
			}
			else
			{
				++result[i];
			}
			break;
		}
		else
		{
			if (i == 0)
			{
				return "";
			}
			result[i] = '0';
		}
		--i;
	}
	int n = 8 - result.size();
	for (int i = 0; i < n; ++i)
	{
		result = 'f' + result;
	}
	return result;
}

string toHex_2(int num)  //数字转换为十六进制数
{
	if (num == 0)
	{
		return "0";
	}
	string res = "";
	string hex[16] = { "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f" };
	unsigned int num2 = num;   //这里的unsigned int，把有符号的当作无符号的，可以使负数模16位正确的数，如-2模16=14，也就是e，就是-2的16进制补码
	while (num2 != 0)
	{
		res = hex[num2 % 16] + res;
		num2 /= 16;
	}
	return res;
}

int longestPalindrome(string s)  //最长回文串
{
	map<char, int> m;
	for (auto i : s)
	{
		if (m.find(i) != m.end())
		{
			m.find(i)->second++;
		}
		else
		{
			m.insert(pair<char, int>(i, 1));
		}
	}
	int sum = 0;
	//最长回文串是所有出现次数为偶数的字符+所有出现次数为奇数次的每个字符的个数-1(使得奇数次字符在回文串中为偶数个)+最后在回文串中间加上一个未使用的字符(比如某个奇数次字符)
	map<char, int>::iterator im = m.begin();
	bool hasOdd = false;  //是否有奇数个的字符
	for (; im != m.end(); im++)
	{
		if (im->second % 2 == 0)
		{
			sum += im->second;
		}
		else
		{
			hasOdd = true;
			sum += (im->second - 1);
		}
	}
	return (hasOdd ? sum + 1 : sum);  //如果有奇数个的字符要加一，否则就不能加一
}


vector<string> fizzBuzz(int n)  //Fizz Buzz
{
	vector<string> result;
	if (n == 0)
	{
		return result;
	}
	for (int i=1; i<=n; ++i)
	{
		if (i % 3 == 0 && i % 5 != 0)
		{
			result.push_back("Fizz");
		}
		else if (i % 3 != 0 && i % 5 == 0)
		{
			result.push_back("Buzz");
		}
		else if (i % 3 == 0 && i % 5 == 0)
		{
			result.push_back("FizzBuzz");
		}
		else
		{
			result.push_back(std::to_string(i));
		}
	}
	return result;
}

int thirdMax(vector<int>& nums)  //第三大的数,维护一个长度为3的set
{
	set<int> s;
	for (int i : nums)
	{
		s.insert(i);
		if (s.size() > 3)
		{
			s.erase(s.begin());
		}
	}
	if (s.size() < 3)
	{
		return *s.rbegin();
	}
	else
	{
		return *s.begin();
	}
}

string addStrings(string num1, string num2)  //字符串相加
{
	char p = '0';
	string result = "";
	int i = num1.size() - 1, j = num2.size() - 1;
	for (; i >= 0 || j >= 0; --i, --j)
	{
		char tmp;
		if (i >= 0 && j >= 0)
		{
			tmp = num1.at(i) + num2.at(j) - '0' + p - '0';
		}
		else if (i >= 0)
		{
			tmp = num1.at(i) + p - '0';
		}
		else if (j >= 0)
		{
			tmp = num2.at(j) + p - '0';
		}
		if (tmp > '9')
		{
			tmp = tmp - '9' - 1 + '0';
			p = '1';
		}
		else
		{
			p = '0';
		}
		result = tmp + result;
	}
	if (p == '1')
	{
		result = '1' + result;
	}
	return result;
}

int countSegments(string s)  //字符串中的单词数
{
	if (s.size() == 0)
	{
		return 0;
	}
	if (s.size() == 1 && s.at(0) != ' ')
	{
		return 1;
	}
	int sum = 0;
	int i = 0, j = 1;
	for (; i<s.size() && j<s.size(); ++i, ++j)
	{
		if (s.at(i) != ' ' && (s.at(j) == ' ' || j == s.size() - 1))
		{
			sum++;
		}
	}
	if (i == s.size() - 1 && s.at(i) != ' ' && s.at(i - 1) == ' ')
	{
		sum++;
	}
	return sum;
}

int arrangeCoins(int n)  //排列硬币
{
	if (n == 0)
	{
		return 0;
	}
	long unsigned tn = n;
	double tmp = sqrt(2 * tn + 0.25) - 0.5;
	return static_cast<int>(tmp);
}

int compress(vector<char>& chars)  //压缩字符串
{
	if (chars.size() < 2)
	{
		return chars.size();
	}
	int i = 0, j = 1; //i代表要写入的位置，j表示等于当前字符串的最后一个
	char preC = chars.at(0);
	int sum = 1;
	for (; j < chars.size(); ++j)
	{
		if (preC != chars.at(j))
		{
			chars.at(i) = preC;  //如果不等的话，就写上
			if (sum > 1)  //如果是大于1个的话
			{
				i += 1; //转入下一个要写的
				string tmp = "";
				while (sum > 0)  //这里循环时防止大于9个的
				{
					char p = sum % 10 + '0';
					tmp = p + tmp;
					sum /= 10;
				}
				for (int k = 0; k < tmp.size(); ++k)  //写入数字
				{
					chars.at(i) = tmp.at(k);
					++i;  //记得这里写入完后又向后进了一个字符
				}
			}
			else
			{
				i += 1; //字符只有一个的话不用写数字，直接跳过
			}
			preC = chars.at(j); //前一个字符(待写入的字符)变为当前字符
			sum = 1;  //初始化为1个
		}
		else
		{
			sum++;
		}
	}
	chars.at(i) = preC;  //讲最后字符传给i
	if (sum > 1)  //如果最后的字符大于1个
	{
		i += 1;
		string tmp = "";
		while (sum > 0)
		{
			char p = sum % 10 + '0';
			tmp = p + tmp;
			sum /= 10;
		}
		for (int k = 0; k < tmp.size(); ++k)
		{
			chars.at(i) = tmp.at(k);
			++i; //记得这里写入完后又向后进了一个字符
		}
	}
	else
	{
		i += 1;  //等于1个的话，直接将下标加一
	}
	chars.erase(chars.begin() + i, chars.end());
	return chars.size();
}

vector<int> findDisappearedNumbers(vector<int>& nums)  //找到所有数组中消失的数字
{
	if (nums.size() == 0)
	{
		return nums;
	}
	int len = nums.size();
	vector<int> result;
	for (int i = 1; i <= len; ++i)
	{
		result.push_back(i);
	}
	for (int num : nums)
	{
		result.at(num - 1) = 0;
	}
	int i = 0;
	while (i < result.size() && result.at(i) != 0)
	{
		i++;
	}
	for (int j = i + 1; j < result.size(); ++j)
	{
		if (result.at(j) > 0)
		{
			swap(result.at(j), result.at(i));
			i++;
		}
	}
	if (result.at(i) > 0)
	{
		i++;
	}
	result.erase(result.begin() + i, result.end());
	return result;
}

int minMoves(vector<int>& nums)  //最小移动次数使数组元素相等
{
	//这里假设定住第i个元素，其它元素加一，也就相当于，定住其它元素，第i个元素减一
	//按照减的思路，最后都会等于最小元素
	//因此，总的次数就是所有元素减去最小元素之差的和
	//首先找最小元素
	int can = nums.at(0);
	for (int num : nums)
	{
		if (num < can)
		{
			can = num;
		}
	}
	int sum = 0;
	for (int num : nums)
	{
		sum += (num - can);
	}
	return sum;
}

int findContentChildren(vector<int>& g, vector<int>& s)  //分发饼干
{
	if (g.size() == 0 || s.size() == 0)
	{
		return 0;
	}
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int i = g.size() - 1, j = s.size() - 1;
	int sum = 0;
	while (i >= 0 && j >= 0)
	{
		if (s.at(j) >= g.at(i))  //如果饼干大于胃口，当前孩子得到满足
		{
			sum += 1;
			--j;
			--i;
		}
		else
		{
			--i;  //胃口大，不是好孩子，就跳过，看看当前饼干能否满足下一个
		}
	}
	return sum;
}

bool repeatedSubstringPattern_1(string s)  //重复的子字符串, 笨方法
{
	//先找重复的字符
	string can = "";
	bool isSub = true;
	int sum = 0;
	for (int i = 0; i <= s.size() / 2; ++i)
	{
		can = can + s.at(i);
		if (s.size() % can.size() != 0)  //如果不整除的话，肯定不是
		{
			isSub = false;
			continue;
		}
		int j = 0, k = 0;
		sum = 0;
		while (j < s.size())
		{
			if (s.at(j) == can.at(k))
			{
				isSub = true;
				++j;
				++k;
			}
			else
			{
				isSub = false;
				break;
			}
			if (k == can.size())
			{
				sum += 1;
				k = 0;
			}
		}
		if (isSub)
		{
			break;
		}
	}
	return isSub && sum > 1;
}

bool repeatedSubstringPattern_2(string s)  //重复的子字符串,kmp很骚
{
	int len = s.size();
	vector<int> v(len + 1);
	v.at(0) = -1;
	int t = -1, j = 0;
	while (j < len)
	{
		if (t < 0 || s[t] == s[j])
		{
			++t;
			++j;
			v[j] = t;
		}
		else
		{
			t = v[t];
		}
	}
	//根据next表，j-t就是重复字符串最小的长度，
	//其实我们这里用的是一个更强的条件，普通字符串能成功，那么最小字符串肯定能成功，反之不然，所以这里就看最小字符串能不能成功
	//如果next[len] <= 0的话，就说明整个字符串是一个重复字符串，显然是不对的
	if (v[len] <= 0)
	{
		return false;
	}
	int minLen = len - v[len];
	bool result = true;
	int k = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == s[k])
		{
			result = true;
			k++;
		}
		else
		{
			return false;
		}
		if (k == minLen)
		{
			k = 0;
		}
	}
	return k == 0 && result;  //最后成功的话，k=0的
}

int DFS(TreeNode* root, int sum)
{
	if (!root)
	{
		return 0;
	}
	int result = 0;
	if (root->val == sum)
	{
		result++;
	}
	result += DFS(root->left, sum - root->val);
	result += DFS(root->right, sum - root->val);
	return result;
}

int pathSum(TreeNode* root, int sum)  //以每个节点都当作根节点,双重递归
{
	if (!root)
	{
		return 0;
	}
	int result = 0;
	result += DFS(root, sum);  //以当前root为根节点
	result += pathSum(root->left, sum);  //以当前root->left为根节点
	result += pathSum(root->right, sum);  //以当前root->right为根节点
	return result;
}

int numberOfBoomerangs(vector<vector<int>>& points)  //回旋镖的数量
{
	map<double, int> ranges; //第一个double为距离，第二个为次数
	int result = 0;
	for (int i = 0; i < points.size(); ++i)  //第i个为回旋镖元组的第一个元素
	{
		ranges.clear();  //由于此时记录第i个在第一个的位置，因此前面的第i-1个元素在首位置的情况清空
		for (int j=0; j<points.size(); ++j)
		{
			if (j == i)
			{
				continue;
			}
			double dis = pow(points.at(i).at(0) - points.at(j).at(0), 2) + pow(points.at(i).at(1) - points.at(j).at(1), 2);
			dis = sqrt(dis);
			if (ranges.find(dis) != ranges.end())
			{
				result += ranges.find(dis)->second * 2;  //假设已经有k个元素与第i个元素距离为d，则再加入当前j元素时，就会有2k种回旋镖情况，具体为(i,j,k中任意一个)和(i,k中任意一个,j)
				ranges.find(dis)->second++;
			}
			else
			{
				ranges.insert(pair<double, int>(dis, 1));
			}
		}
	}
	return result;
}

int hammingDistance(int x, int y)  //汉明距离
{
	bitset<32> bx(x);
	bitset<32> by(y);
	int result = 0;
	for (int i=0; i<32; ++i)
	{
		if (bx[i] != by[i])
		{
			++result;
		}
	}
	return result;
}

int islandPerimeter(vector<vector<int>>& grid)  //岛屿的周长
{
	if (grid.size() == 0)
	{
		return 0;
	}
	int result = 0;
	for (int i=0; i<grid.size(); ++i)  
	{
		for (int j=0; j<grid.at(i).size(); ++j)
		{
			if (grid.at(i).at(j) == 1)  //如果当前是岛屿的话
			{
				//先横向
				if (j == 0)  //如果当前为列的第一个，由于为1，所以其前面应该为是个海岸，所以加一
				{
					result++; 
				}
				else
				{
					if (grid.at(i).at(j - 1) == 0)  //如果不为第一列，且前一个为海(0)，则应该有一个海岸
					{
						result++;
					}
				}
				if (j == grid.at(i).size() - 1) //如果当前为列的最后一个，那么其后面也应该有海岸
				{
					result++;
				}
				if (i == 0)  //解释与上述列一样
				{
					result++;
				}
				else
				{
					if (grid.at(i - 1).at(j) == 0)
					{
						result++;
					}
				}
				if (i == grid.size() - 1)
				{
					result++;
				}
			}
			else  //如果当前为海
			{
				if (j > 0 && grid.at(i).at(j - 1) == 1)  //其前面为岛屿，则应该有海岸
				{
					result++;
				}
				if (i > 0 && grid.at(i-1).at(j) == 1)  //上面为岛屿，应该会有海岸
				{
					result++;
				}
			}
		}
	}
	//以上会不有重复的呢，不会的，每个海岸的寻找，都是按照当前元素与前面和上面元素的空隙来判断，对于行列最后的元素才会判断其后面一行或一列
	return result;
}

int findRadius_1(vector<int>& houses, vector<int>& heaters)  //供暖器，超时了
{
	//找到离每个房屋距离最近的炉子点，然后选取最大值
	set<int> s;
	for (int i = 0; i < houses.size(); i++)
	{
		int dis = abs(houses.at(i) - heaters.at(0));  
		for (int j = 0; j < heaters.size(); j++)
		{
			dis = min(dis, abs(heaters.at(j) - houses.at(i)));
		}
		s.insert(dis);
	}
	return *(s.rbegin());
}

int findRadius_2(vector<int>& houses, vector<int>& heaters)  //供暖器,二分查找,找到离每个房屋距离最近的炉子点，然后选取最大值
{
	sort(houses.begin(), houses.end());
	sort(heaters.begin(), heaters.end());
	int dis = 0;
	for (int i = 0; i < houses.size(); i++)
	{
		int left = 0, right = heaters.size() - 1;
		while (left < right)
		{
			int mid = (left+right) >> 1;
			if(heaters.at(mid) < houses.at(i))
			{
				left += 1;
			}
			else
			{
				right = mid;
			}
		}
		if(heaters.at(left) == houses.at(i))
		{
			dis = max(dis, 0);
		}
		else if(heaters.at(left) < houses.at(i))
		{
			if (left + 1 < heaters.size())
			{
				dis = max(dis, min(houses.at(i) - heaters.at(left), heaters.at(left + 1) - houses.at(i)));
			}
			else
			{
				dis = max(dis, houses.at(i) - heaters.at(left));
			}
		}
		else
		{
			if (left - 1 >= 0)
			{
				dis = max(dis, min(heaters.at(left) - houses.at(i), houses.at(i) - heaters.at(left - 1)));
			}
			else
			{
				dis = max(dis, heaters.at(left) - houses.at(i));
			}
		}
		
	}
	return dis;
}

int findComplement(int num)  //数字的补数
{
	int i = 0;
	int result = 0;
	while (num > 0)
	{
		result += (1 - num % 2)*pow(2, i);
		i++;
		num /= 2;
	}
	return result;
}

string licenseKeyFormatting(string S, int K) //密钥格式化
{
	string result = "";
	int j = 0;
	int e = 0;
	while (e < S.size() && S.at(e) == '-')
	{
		++e;
	}
	for (int i = S.size() - 1; i >= e; --i)
	{
		if (S.at(i) != '-')
		{
			result += static_cast<char>(toupper(S.at(i)));   //如果是 result = static_cast<char>(toupper(S.at(i))) + result会超出内存;
			++j;
			S.erase(S.begin() + i, S.end());
		}
		if (j == K && i > e)
		{
			j = 0;
			result += '-';
		}
	}
	reverse(result.begin(), result.end());
	return result;
}

int findMaxConsecutiveOnes(vector<int>& nums)  //最大连续1的个数
{
	int result = 0;
	int tmp = 0;
	for (int i : nums)
	{
		if (i == 1)
		{
			++tmp;
		}
		else
		{
			result = max(tmp, result);
			tmp = 0;
		}
	}
	result = max(result, tmp);
	return result;
}

vector<int> constructRectangle(int area)  //构造矩形
{
	double tmp = sqrt(area);
	if(tmp - static_cast<int>(tmp) < 1e-4)
	{
		return {static_cast<int>(tmp), static_cast<int>(tmp)};
	}
	int W = 1;
	for (int i=1; i < sqrt(area); ++i)  //这里当area大于4时，1到sqrt(area) 的个数小于sqrt(area)到area的个数，所以选择小的那个
	{
		if(area % i == 0)
		{
			W = i;
		}
	}
	return {area/W, W};
}

 vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)  //下一个更大元素 I
 {
	 vector<int> result;
	 for (int i : nums1)
	 {
		 bool isFind = false;
		 for (int j = 0; j < nums2.size(); j++)
		 {
			 if(isFind)
			 {
				 if(nums2.at(j) > i)
				 {
					 result.push_back(nums2.at(j));
					 break;
				 }
				 else if(j == nums2.size() - 1 && nums2.at(j) <= i)
				 {
					 result.push_back(-1);
				 }
			 }
			 else
			 {
				 if(nums2.at(j) == i)
				 {
					 isFind = true;
					 if(j == nums2.size() - 1)
					 {
						 result.push_back(-1);
					 }
				 }
			 }
		 }
	 }
	 return result;
 }

 vector<string> findWords(vector<string>& words)  //键盘行
 {
	map<char, int> m;
	m['q'] = 2; m['w'] = 2; m['e'] = 2; m['r'] = 2; m['t'] = 2; m['y'] = 2; m['u'] = 2; m['i'] = 2; m['o'] = 2; m['p'] = 2; 
	m['a'] = 1; m['s'] = 1; m['d'] = 1; m['f'] = 1; m['g'] = 1; m['h'] = 1; m['j'] = 1; m['k'] = 1; m['l'] = 1;
	m['z'] = 0; m['x'] = 0; m['c'] = 0; m['v'] = 0; m['b'] = 0; m['n'] = 0; m['m'] = 0;
	vector<string> result;
	for(string s : words)
	{
		if(s.size() == 0)
		{
			continue;
		}
		int tmp = m.find(static_cast<char>(tolower(s.at(0))))->second;
		for(int i=0; i<s.size(); ++i)   //这边从0开始，因为可能s只有一个元素
		{
			char t = static_cast<char>(tolower(s.at(i)));
			if(m.find(t)->second != tmp)
			{
				break;
			}
			if(i == s.size() - 1)
			{
				result.push_back(s);
			}
		}
	}
	return result;
 }

 void goAlongLeft_findMode(TreeNode* root, stack<TreeNode*> &s)
 {
	 while (root)
	 {
		 s.push(root);
		 root = root->left;
	 }
 }

void zhongXuBianLi(TreeNode* root, map<int, int> &tmp)
{
	stack<TreeNode *> s;
	while (true)
	{
		goAlongLeft_findMode(root, s);
		if(s.empty())
		{
			break;
		}
		root = s.top(); 
		s.pop();
		map<int, int>::iterator ifind = tmp.find(root->val);
		if(ifind != tmp.end())
		{
			ifind->second++;
		}
		else
		{
			tmp.insert(pair<int, int>(root->val, 1));
		}
		root = root->right;
	}
}

 vector<int> findMode(TreeNode* root)  //二叉搜索树中的众数
 {
	 if(!root)
	 {
		 return {};
	 }
	 //先中序遍历
	 map<int, int> tmp;
	zhongXuBianLi(root, tmp);
	map<int, int>::iterator i = tmp.begin();
	int can = i->second;  //候选人的出现次数
	vector<int> result = {i->first};
	++i;
	for (; i != tmp.end(); i++)
	{
		if(i->second > can)
		{
			result.clear();
			result.push_back(i->first);
			can = i->second;
		}
		else if(i->second == can)
		{
			result.push_back(i->first);
		}
	}
	return result;
 }

 string convertToBase7(int num) //七进制数
 {
	 if(num == 0)
	 {
		 return "0";
	 }
	  int tmp = abs(num);
	 string result = "";
	 while (tmp > 0)
	 {
		 result += std::to_string(tmp % 7);
		 tmp /= 7;
	 }
	 if(num < 0)
	 {
		 result += '-';
	 }
	reverse(result.begin(), result.end());
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
	*/

	//快乐数
	//isHappy

	//移除链表元素
	//removeElements

	//计数质数
	//countPrimes_2

	//同构字符串
	//isIsomorphic_2

	//反转链表
	//reverseList_3

	//存在重复元素
	//containsDuplicate_2

	//存在重复元素 II
	//containsNearbyDuplicate

	//用队列实现栈
	//MyStack

	//翻转二叉树
	//invertTree

	//2的幂
	//isPowerOfTwo

	//用栈实现队列
	//MyQueue

	//回文链表
	//isPalindrome

	//二叉搜索树的最近公共祖先
	//lowestCommonAncestor

	//删除链表中的节点
	//deleteNode

	//有效的字母异位词
	//isAnagram

	//二叉树的所有路径
	//binaryTreePaths

	//各位相加
	//addDigits

	//丑数
	//isUgly

	//缺失数字
	//missingNumber

	//第一个错误的版本
	//firstBadVersion

	//移动零
	//moveZeroes

	//单词规律
	//wordPattern

	//Nim 游戏
	//cout << canWinNim(1348820612) << endl;

	//猜数字游戏
	//getHint

	//区域和检索 - 数组不可变
	//NumArray

	//3的幂
	//isPowerOfThree

	//反转字符串
	//reverseString

	//反转字符串中的元音字母
	//reverseVowels

	//两个数组的交集
	//intersection

	//两个数组的交集 II
	//intersect

	//有效的完全平方数
	//isPerfectSquare

	//两整数之和
	//getSum

	//猜数字大小
	//guessNumber

	//赎金信
	//canConstruct

	//字符串中的第一个唯一字符
	//firstUniqChar

	//找不同
	//findTheDifference

	//判断子序列
	//isSubsequence

	// 二进制手表
	//readBinaryWatch

	//左叶子之和
	//sumOfLeftLeaves

	//数字转换为十六进制数
	//toHex

	//最长回文串
	//longestPalindrome

	//Fizz Buzz
	//fizzBuzz

	//第三大的数
	//thirdMax

	//字符串相加
	//addStrings
	
	//字符串中的单词数
	//countSegments

	//排列硬币
	//arrangeCoins

	//压缩字符串
	/*
	vector<char> c = { 'a', 'a', 'a', 'a','b' ,'a'};
	compress(c);
	*/

	//找到所有数组中消失的数字
	//findDisappearedNumbers

	//最小移动次数使数组元素相等
	//minMoves

	//分发饼干
	//findContentChildren

	//重复的子字符串
	//repeatedSubstringPattern

	//路径总和 III
	//pathSum

	//回旋镖的数量
	//numberOfBoomerangs

	//汉明距离
	//hammingDistance

	//岛屿的周长
	//islandPerimeter

	//供暖器
	//findRadius

	//数字的补数
	//findComplement

	//密钥格式化
	//licenseKeyFormatting

	//最大连续1的个数
	//findMaxConsecutiveOnes

	//构造矩形
	//constructRectangle

	//下一个更大元素 I
	//nextGreaterElement

	//键盘行
	//findWords

	//二叉搜索树中的众数
	//findMode

	//七进制数
	//convertToBase7
}
