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

ListNode* reverseList(ListNode* head, ListNode* trail) //trailΪ�����ڱ�,�����뷴ת
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
	ListNode* pret = new ListNode(0);  //��¼��ת֮ǰ�Ѿ���ת���˵����һ��Ԫ��
	pret->next = head;
	ListNode* result = pret;
	while (head)
	{
		for (int i = 0; i < k - 1; ++i)  //��Ϊ��תʱ������ʼ��head�����ֻ��Ҫ�ж�head֮��k-1��next��Ϊnull�����������ʼ��head��������k��
		{
			head = head->next;
			if (!head)
			{
				return result->next;
			}
		}
		head = head->next;  //��Ϊǰ���for�������head�����ǵ�k��������ת�����ǰ�������ģ������Ҫǰ��һλ��Ϊ�ڱ�
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

vector<int> maxSlidingWindow_1(vector<int>& nums, int k)  //�����������ֵ--deque��¼ֵ
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

vector<int> maxSlidingWindow_2(vector<int>& nums, int k)  //�����������ֵ--deque��¼�±�,�ü�¼�±�ķ����������Ǹ���
{
	if (nums.size() == 0)
	{
		return{};
	}
	deque<int> d; //��¼���ֵ���±�
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
	if (row >= n)  //row��0��ʼ��n�еĻ��ǵ�n-1�����Ե�n�Ļ����˳��ݹ�
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
		//�ѽ���ŵ���ǰ��pos��
		pos.at(row) = col;
		solveNQueens_dfs(n, row + 1, pos);  //�ݹ鵽��һ��
		//�����һ�ֿ��ܵõ��Ľ��,�ٿ���ǰ����û�л������ܳ���
		columns.erase(col);
		pie.erase(row - col);
		na.erase(row + col);
	}
}
vector<vector<string>> solveNQueens(int n)  //N�ʺ�
{
	if (n == 0)
	{
		return {};
	}
	vector<int> pos(n, -1); //�±�����к�
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
		//ɾ����ǰcol�Ľ��
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
	//K ��һ�鷭ת����
	//reverseKGroup

	//�����������ֵ
	//maxSlidingWindow

	//N�ʺ�
	//solveNQueens

	//N�ʺ� II
	//totalNQueens
}