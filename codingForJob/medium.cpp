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

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)  //�������
{
	if (!l1)
	{
		return l2;
	}
	else if (!l2)
	{
		return l1;
	}
	int preAdd = 0;
	ListNode *result = new ListNode(l1->val);
	ListNode *tmp = result;
	while (l1 && l2)
	{
		if (l1->val + l2->val + preAdd >= 10)
		{
			ListNode *t = new ListNode((l1->val + l2->val + preAdd) % 10);
			tmp->next = t;
			preAdd = 1;
		}
		else
		{
			ListNode *t = new ListNode(l1->val + l2->val + preAdd);
			tmp->next = t;
			preAdd = 0;
		}
		l1 = l1->next;
		l2 = l2->next;
		tmp = tmp->next;
	}
	while (l1)
	{
		if (l1->val + preAdd >= 10)
		{
			ListNode *t = new ListNode((l1->val + preAdd) % 10);
			tmp->next = t;
			preAdd = 1;
		}
		else
		{
			ListNode *t = new ListNode(l1->val + preAdd);
			tmp->next = t;
			preAdd = 0;
		}
		l1 = l1->next;
		tmp = tmp->next;
	}
	while (l2)
	{
		if (l2->val + preAdd >= 10)
		{
			ListNode *t = new ListNode((l2->val + preAdd) % 10);
			tmp->next = t;
			preAdd = 1;
		}
		else
		{
			ListNode *t = new ListNode(l2->val + preAdd);
			tmp->next = t;
			preAdd = 0;
		}
		l2 = l2->next;
		tmp = tmp->next;
	}
	if (preAdd == 1)
	{
		tmp->next = new ListNode(preAdd);
	}
	return result->next;
}

int lengthOfLongestSubstring_1(string s)  //���ظ��ַ�����Ӵ�
{
	if (s.size() <= 1)
	{
		return s.size();
	}
	int result = 1;
	unordered_set<char> tmp;
	for (int i=0; i<s.size(); ++i)
	{
		tmp.clear();
		tmp.insert(s.at(i));
		for (int j=i+1; j<s.size(); ++j)
		{
			if (j == s.size() - 1 && tmp.find(s.at(j)) == tmp.end())
			{
				result = max(j - i + 1, result);
			}
			else if (tmp.find(s.at(j)) != tmp.end())
			{
				result = max(j - i, result);
				break;
			}
			else
			{
				tmp.insert(s.at(j));
			}
		}
	}
	return result;
}

int lengthOfLongestSubstring_2(string s)  //���ظ��ַ�����Ӵ�
{
	if (s.size() <= 1)
	{
		return s.size();
	}
	int result = 1;
	unordered_map<char, int> um;
	unordered_map<char, int>::iterator ifind;
	for (int i=0, j=0; i<s.size(); ++i)   //j��ʾ��˵�
	{
		ifind = um.find(s.at(i));
		if (ifind != um.end())
		{
			j = max(ifind->second + 1, j);   //�������a(i)....b(j)....b(k)....a(m)�������(������ΪԪ�ص��±�)������b�ظ�ʱ������˵�Ϊj+1, ����a�ظ�ʱ����˵����i+1�������ͻ������b������ȥ�����jӦ��ȡ����Ǹ�
			//�ϸ���䣬��ʵ���ǣ�����ҵ����ظ��ַ��ڵ�ǰ��˵��ұߵĻ�����ô�͸�����˵㣬����߾����ڵ�ǰ��ѡ��Ӵ��в�û���ظ�����˲���Ҫ����
			ifind->second = i;
		}
		else
		{
			um.insert(pair<char, int>(s.at(i), i));
		}
		result = max(result, i - j);
	}
	return result;
}

ListNode* swapPairs(ListNode* head)  //�������������еĽڵ�
{
	if (!head || !head->next) {
		return head;
	}
	ListNode* t = new ListNode(0);
	ListNode* result = t;

	while (head && head->next)
	{
		ListNode* pre = head;
		ListNode* now = head->next;
		ListNode* tmp = head->next->next;
		now->next = pre;
		pre->next = tmp;
		t->next = now;
		head = tmp;
		t = t->next->next;
	}
	return result->next;
}

ListNode *detectCycle_1(ListNode *head)  //�������� II--hash��
{
	if (!head || !head->next)
	{
		return nullptr;
	}
	int i = 0;
	unordered_map<ListNode*, int> um;
	unordered_map<ListNode*, int>::iterator ifind, iend = um.end();
	while (head)
	{
		ifind = um.find(head);
		if (ifind == iend)
		{
			um.insert(pair<ListNode*, int>(head, i));
		}
		else
		{
			return ifind->first;
		}
		head = head->next;
		++i;
	}
	return nullptr;
}

ListNode *detectCycle_2(ListNode *head)  //�������� II--����ָ��https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/huan-xing-lian-biao-ii-by-leetcode/
{
	if (!head || !head->next)
	{
		return nullptr;
	}
	ListNode* slow = head;
	ListNode* fast = head;
	ListNode* meetPoint = nullptr;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			meetPoint = fast;
			break;
		}
	}
	if (!meetPoint)
	{
		return nullptr;
	}
	while (head != meetPoint)
	{
		head = head->next;
		meetPoint = meetPoint->next;
	}
	return head;
}

vector<vector<int>> threeSum(vector<int>& nums)  //����֮��
{
	if (nums.size() < 3)
	{
		return {};
	}
	sort(nums.begin(), nums.end());
	vector<vector<int>> result;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (nums.at(i) > 0)
		{
			break;
		}
		if (i > 0 && nums.at(i) == nums.at(i - 1))
		{
			continue;
		}
		int l = i + 1, r = nums.size() - 1;
		while (l < r)
		{
			if (nums.at(i) + nums.at(l) + nums.at(r) > 0)
			{
				--r;
			}
			else if(nums.at(i) + nums.at(l) + nums.at(r) < 0)
			{
				++l;
			}
			else
			{
				result.push_back({ nums.at(i), nums.at(l), nums.at(r) });
				++l;
				--r;
			}
		}
	}
	return result;
}

int main
{
	//�������
	//addTwoNumbers

	//���ظ��ַ�����Ӵ�
	//lengthOfLongestSubstring

	//�������������еĽڵ�
	//swapPairs

	//�������� II
	//detectCycle_1

	//����֮��
	//threeSum
}