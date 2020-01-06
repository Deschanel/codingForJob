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
				while (l < r && nums.at(l) == nums.at(l - 1))
				{
					++l;
				}
				while (l < r && nums.at(r) == nums.at(r + 1))
				{
					--r;
				}
			}
		}
	}
	return result;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void isValidBST_goAlongLeft(TreeNode* root, stack<TreeNode*> &s)
{
	while (root)
	{
		s.push(root);
		root = root->left;
	}
}
bool isValidBST_1(TreeNode* root)
{
	if (!root)
	{
		return true;
	}
	else if (!root->left && !root->right)
	{
		return true;
	}
	else   //�������
	{
		stack<TreeNode*> s;
		long comp = LONG_MIN;
		while (true)
		{
			isValidBST_goAlongLeft(root, s);
			if (s.empty())
			{
				break;
			}
			root = s.top();
			s.pop();
			if (root->val <= comp)
			{
				return false;
			}
			comp = root->val;
			root = root->right;
		}
	}
	return true;
}

bool isValidBST_2_item(TreeNode* root, long l, long r)
{
	if (!root)
	{
		return true;
	}
	if (root->val <= l || root->val >= r)
	{
		return false;
	}
	return isValidBST_2_item(root->left, l, root->val) && isValidBST_2_item(root->right, root->val, r);
}
bool isValidBST_2(TreeNode* root)  //�ݹ飬���½�
{
	return isValidBST_2_item(root, LONG_MIN, LONG_MAX);
}

TreeNode* lowestCommonAncestor_1(TreeNode* root, TreeNode* p, TreeNode* q)  //�������������������
{
	if (!root)
	{
		return nullptr;
	}
	if (root == p || root == q)
	{
		return root;
	}
	TreeNode* l = lowestCommonAncestor_1(root->left, p, q);  //���������Ҷ���֮һ
	TreeNode* r = lowestCommonAncestor_1(root->right, p, q); //���������Ҷ���֮һ
	if (!l && r)  //�����������������һ����������û�У�˵���϶�����������,���Ӧ�õݹ�lowestCommonAncestor(root->right, p, q),������Ѿ�ִ����
	{
		return r;
	}
	else if(l && !r) //�����������������һ����������û�У�˵���϶�����������
	{
		return l;
	}
	else if (!l && !r) //��������������
	{
		return nullptr;
	}
	else  //���������ж�������֮һ��˵������������Ⱦ���root
	{
		return root;
	}
}

TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)  //�������������������--Ѱ��·��
{
	stack<TreeNode*> s;  //��ŵ����Ľڵ�
	unordered_map<TreeNode*, TreeNode*> um;  //��һ��Ϊ��ǰ�ڵ㣬�ڶ���Ϊ���ڵ�
	um.insert(pair<TreeNode*, TreeNode*>(root, nullptr));
	s.push(root);
	while (um.find(p) == um.end() || um.find(q) == um.end()) //��α�������ÿ���ĸ��ڵ��¼����
	{
		TreeNode* root = s.top();
		s.pop();
		if (root->left)
		{
			s.push(root->left);
			um.insert(pair<TreeNode*, TreeNode*>(root->left, root));
		}
		if (root->right)
		{
			s.push(root->right);
			um.insert(pair<TreeNode*, TreeNode*>(root->right, root));
		}
	}
	unordered_set<TreeNode*> anc;  //p����������
	while (p)
	{
		anc.insert(p);
		p = um.find(p)->second;
	}
	while (anc.find(q) == anc.end())
	{
		q = um.find(q)->second;
	}
	return q;
}

double myPow(double x, int n)  //Pow(x, n)--���Σ�log(n)
{
	if (n == 0)
	{
		return 1.0;
	}
	double result = 1.0;
	if (n > 0)
	{
		if (n % 2 == 0)
		{
			result = myPow(x, n / 2);
			return result * result;
		}
		else
		{
			result = myPow(x, (n - 1) / 2);
			return result * result * x;
		}
	}
	else
	{
		int nn = -(n + 1);
		if (nn % 2 == 0)
		{
			result = myPow(x, nn / 2);
			return (1.0 / (result * result)) * (1.0 / x);
		}
		else
		{
			result = myPow(x, (nn - 1) / 2);
			return (1.0 / (result * result * x)) * (1.0 / x);
		}
	}
}

vector<int> majorityElement(vector<int>& nums) //������ II--����Ҫ���ǳ���[n/3]������������������Ԫ��Ϊ����
{
	
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

	//��֤����������
	//isValidBST

	//�������������������
	//lowestCommonAncestor

	//Pow(x, n)
	//myPow

	//������ II
	//majorityElement
}