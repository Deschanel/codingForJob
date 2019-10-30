// codingForJob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <queue>

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
}
