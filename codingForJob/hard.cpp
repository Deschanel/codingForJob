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
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverseList(ListNode* head, ListNode* trail) //trail为假象哨兵,不参与反转
{
	if (!head || !head->next)
	{
		return head;
	}
	ListNode* pre = trail;
	while (head != trail)
	{
		ListNode* tmp = head->next;
		head->next = pre;
		pre = head;
		head = tmp;
	}
	return pre;
}
ListNode* reverseKGroup(ListNode* head, int k)
{
	if (k == 1 || !head || !head->next)
	{
		return head;
	}
	ListNode* t = head;
	ListNode* pret = new ListNode(0);  //记录反转之前已经反转好了的最后一个元素
	pret->next = head;
	ListNode* result = pret;
	while (head)
	{
		for (int i = 0; i < k - 1; ++i)  //因为反转时候包括最开始的head，因此只需要判断head之后k-1个next不为null，这样加上最开始的head就是正好k个
		{
			head = head->next;
			if (!head)
			{
				return result->next;
			}
		}
		head = head->next;  //因为前面的for结束后的head正好是第k个，而反转函数是包括这个的，因此需要前进一位成为哨兵
		t = reverseList(t, head);
		pret->next = t;
		for (int i = 0; i < k; ++i)
		{
			t = t->next;
			pret = pret->next;
		}
	}
	return result->next;
}

vector<int> maxSlidingWindow_1(vector<int>& nums, int k)  //滑动窗口最大值--deque记录值
{
	deque<int> d;
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		if (i < k - 1)
		{
			while (!d.empty() && d.back() < nums.at(i))
			{
				d.pop_back();
			}
			d.push_back(nums.at(i));
		}
		else
		{
			while (!d.empty() && d.back() < nums.at(i))
			{
				d.pop_back();
			}
			d.push_back(nums.at(i));
			result.push_back(d.front());
			if (!d.empty() && d.front() == nums.at(i - k + 1))
			{
				d.pop_front();
			}
		}
	}
	return result;
}

vector<int> maxSlidingWindow_2(vector<int>& nums, int k)  //滑动窗口最大值--deque记录下标,用记录下标的方法比上面那个好
{
	if (nums.size() == 0)
	{
		return{};
	}
	deque<int> d; //记录最大值的下标
	vector<int> result;
	for (int i=0; i<nums.size(); ++i)
	{
		if (i >= k && d.front() <= i - k)
		{
			d.pop_front();
		}
		while (!d.empty() && nums.at(i) > nums.at(d.back()))
		{
			d.pop_back();
		}
		d.push_back(i);
		if (i >= k - 1)
		{
			result.push_back(nums.at(d.front()));
		}
	}
	return result;
}

vector< vector<string> > result;
unordered_set<int> columns, pie, na;
void solveNQueens_dfs(int n, int row, vector<int> pos)  
{
	if (row >= n)  //row从0开始，n行的话是到n-1，所以到n的话就退出递归
	{
		vector<string> tmp;
		for (int i=0; i<n; ++i)
		{
			string s = "";
			for (int j=0; j<n; ++j)
			{
				if (j == pos.at(i))
				{
					s += "Q";
				}
				else
				{
					s += ".";
				}
			}
			tmp.push_back(s);
		}
		result.push_back(tmp);
		return;
	}
	for (int col=0; col < n; ++col)
	{
		if (columns.count(col) || pie.count(row - col) || na.count(row + col))
		{
			continue;
		}
		columns.insert(col);
		pie.insert(row - col);
		na.insert(row + col);
		//把结果放到当前的pos中
		pos.at(row) = col;
		solveNQueens_dfs(n, row + 1, pos);  //递归到下一层
		//清除上一种可能得到的结果,再看当前行有没有还有列能成立
		columns.erase(col);
		pie.erase(row - col);
		na.erase(row + col);
	}
}
vector<vector<string>> solveNQueens(int n)  //N皇后
{
	if (n == 0)
	{
		return {};
	}
	vector<int> pos(n, -1); //下标代表行号
	solveNQueens_dfs(n, 0, pos);
	return result;
}

void totalNQueens_dfs(int n, int row, int &result)
{
	if (row >= n)
	{
		result++;
		return;
	}
	for (int col=0; col<n; ++col)
	{
		if (columns.count(col) || pie.count(row - col) || na.count(row + col))
		{
			continue;
		}
		columns.insert(col);
		pie.insert(row - col);
		na.insert(row + col);
		totalNQueens_dfs(n, row + 1, result);
		//删除当前col的结果
		columns.erase(col);
		pie.erase(row - col);
		na.erase(row + col);
	}
}
int totalNQueens(int n)
{
	if (n == 0)
	{
		return 0;
	}
	int result = 0;
	totalNQueens_dfs(n, 0, result);
	return result;
}

int main
{
	//K 个一组翻转链表
	//reverseKGroup

	//滑动窗口最大值
	//maxSlidingWindow

	//N皇后
	//solveNQueens

	//N皇后 II
	//totalNQueens
}