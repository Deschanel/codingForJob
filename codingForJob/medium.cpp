#include "pch.h"
#include <iostream>
#include <sstream>
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
	if (nums.size() < 2)
	{
		return nums;
	}
	int count1 = 0, count2 = 0;
	int cx = 0, cy = 0;
	for (auto i : nums)
	{
		if ((count1 == 0 || cx == i) && i != cy)  //���ﲻ��i != cy�Ļ�����ʹcy�ټ�һ��
		{
			count1++;
			cx = i;
			continue;
		}
		if (count2 == 0 || cy == i)
		{
			count2++;
			cy = i;
			continue;
		}
		if (cx != i && cy != i)
		{
			--count1;
			--count2;
		}
	}
	//�����������Ƿ����������
	count1 = 0;
	count2 = 0;
	for (auto i : nums)
	{
		if (i == cx)
		{
			++count1;
		}
		else if (i == cy)
		{
			++count2;
		}
	}
	vector<int> result;
	if (count1 > nums.size() / 3)
	{
		result.push_back(cx);
	}
	if (count2 > nums.size() / 3 && cx != cy)
	{
		result.push_back(cy);
	}
	return result;
}

vector<vector<int>> levelOrder(TreeNode* root)  //�������Ĳ�α���
{
	if (!root)
	{
		return {};
	}
	vector< vector<int> > result;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		int len = q.size();  //ÿ�εĸ���Ϊ��ǰ��ε�Ԫ�ظ���
		vector<int> tmp;
		while (len > 0)  //�ѵ�ǰ���в��Ԫ�ر�����󣬼������Щ����������һ��εĸ���
		{
			root = q.front();
			q.pop();
			tmp.push_back(root->val);
			len--;
			if (root->left)
			{
				q.push(root->left);
			}
			if (root->right)
			{
				q.push(root->right);
			}
		}
		result.push_back(tmp);
	}
	return result;
}

void generateParenthesis_dfs(string s, int l, int r, vector<string> &result)
{
	if (l == 0 && r == 0)
	{
		result.push_back(s);
		return;
	}
	if (l > r)   //ʣ�µ������Ÿ������������ţ�˵����Ҫ��֦����������Ҳ����l < r�������Ļ�����ľ�Ӧ����"(" + s �� ")" + s
	{
		return;
	}
	if (l > 0)
	{
		generateParenthesis_dfs(s + "(", l - 1, r, result);
	}
	if (r > 0)
	{
		generateParenthesis_dfs(s + ")", l, r - 1, result);
	}
}
vector<string> generateParenthesis_1(int n)  //��������--�����������https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/
{
	if (n == 0)
	{
		return {};
	}
	else if (n == 1)
	{
		return { "()" };
	}
	vector<string> result;
	generateParenthesis_dfs("", n, n, result);
	return result;
}

vector<string> generateParenthesis_2(int n)  //��������--��̬�滮
{
	if (n == 0)
	{
		return {};
	}
	//����n-1������ʱ��������Դ��м�ĳ����Ϊ���Գ����������ִ����ֱ�Ϊp�����ţ�q�����ţ�p+q=n-1����p�ķ�Χ0->n-1,q�ķ�Χ��Ӧ��Ϊn-1->0
	//��n������ʱ�����Ƕ�ÿһ��p��q�Ľ��vector�е����������(p)+q������p+(q),��p+()+q������p+q+(),����()+p+q����p��qΪ0ʱ������,���Ͼ��ظ���
	vector<string> result;
	for (int i = 0; i < n; ++i)
	{
		for (string leftString : generateParenthesis_2(i)) // ��i������ʱp���ַ���
		{
			for (string rightString : generateParenthesis_2(n - 1 - i))  //n-1-i������ʱq���ַ���
			{
				result.push_back("(" + leftString + ")" + rightString);
			}
		}
	}
	return result;
}
vector<int> findAnagrams(string s, string p)   //�ҵ��ַ�����������ĸ��λ��
{
	if (s.size() < p.size())
	{
		return {};
	}
	unordered_map<char, int> um, window;
	vector<int> result;
	int l = 0, r = 0, match = 0;
	for (char i : p)
	{
		um[i]++;
	}
	while (r < s.size())
	{
		if (um.count(s.at(r)))
		{
			window[s.at(r)]++;
			if (window[s.at(r)] == um[s.at(r)])
			{
				match++;
			}
		}
		r++;
		while (match == um.size())
		{
			if (r - l == p.size())
			{
				result.push_back(l);
			}
			if (um.count(s.at(l)))
			{
				window[s.at(l)]--;
				if (window[s.at(l)] < um[s.at(l)])
				{
					match--;
				}
			}
			l++;
		}
	}
	return result;
}

bool isValidSudoku(vector<vector<char>>& board)   //��Ч������
{
	if (board.size() == 0)
	{
		return false;
	}
	vector< vector<unordered_set<char> > > isValidSudoku_blocks(3, vector< unordered_set<char> >(3));
	vector< unordered_set<char> > isValidSudoku_rows(board.size());
	vector< unordered_set<char> > isValidSudoku_columns(board.size());
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board.at(i).size(); ++j)
		{
			if (board.at(i).at(j) != '.')
			{
				if (isValidSudoku_rows.size() > i && isValidSudoku_rows.at(i).find(board.at(i).at(j)) != isValidSudoku_rows.at(i).end())
				{
					return false;
				}
				else
				{
					isValidSudoku_rows.at(i).insert(board.at(i).at(j));
				}
				if (isValidSudoku_columns.size() > j && isValidSudoku_columns.at(j).find(board.at(i).at(j)) != isValidSudoku_columns.at(j).end())
				{
					return false;
				}
				else
				{
					isValidSudoku_columns.at(j).insert(board.at(i).at(j));
				}
				if (isValidSudoku_blocks.size() > i / 3 && isValidSudoku_blocks.at(i / 3).size() > j / 3 && isValidSudoku_blocks.at(i / 3).at(j / 3).find(board.at(i).at(j)) != isValidSudoku_blocks.at(i / 3).at(j / 3).end())
				{
					return false;
				}
				else
				{
					isValidSudoku_blocks.at(i / 3).at(j / 3).insert(board.at(i).at(j));
				}
			}
		}
	}
	return true;
}

class Trie {   //ʵ�� Trie (ǰ׺��)
public:
	struct TrieNode
	{
		char val;
		bool isEndOfWord = false;
		vector<TrieNode*> children;
		TrieNode(char value)
		{
			this->val = value;
			for (int i = 0; i < 26; i++)
			{
				children.push_back(nullptr);
			}
		}
	};
	/** Initialize your data structure here. */
	TrieNode *root;
	Trie() {
		root = new TrieNode(NULL);
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode* tmp = root;
		for (char c : word)
		{
			if (!tmp->children.at(c - 'a'))
			{
				tmp->children.at(c - 'a') = new TrieNode(c);
			}
			tmp = tmp->children.at(c - 'a');
		}
		tmp->isEndOfWord = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode* tmp = root;
		for (int i=0; i<word.size(); ++i)
		{
			if (!tmp->children.at(word.at(i) - 'a'))
			{
				return false;
			}
			else
			{
				tmp = tmp->children.at(word.at(i) - 'a');  //���治��Ҫ�ж��Ƿ�ǰԪ����end����Ϊ����app��apple������Ļ���Ѱ��appleʱ���ֵڶ���p��end����ô�ͻ᷵��false��Ȼ��apple���еģ��������Ҫ���жϵĻ��ͻ����ֻ��Ҫ���һ���ַ��ж��Ƿ���end�ͺ���
			}
		}
		return tmp->isEndOfWord;  //�������һ���ַ��Ƿ������е��ʵ����һ��Ԫ��
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		TrieNode* tmp = root;
		for (int i = 0; i < prefix.size(); ++i)
		{
			if (!tmp->children.at(prefix.at(i) - 'a'))
			{
				return false;
			}
			else
			{
				tmp = tmp->children.at(prefix.at(i) - 'a');
			}
		}
		return true;
	}
};

int direction[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
bool exist_dfs(vector<vector<char>>& board, string word, int n, int row, int column)
{
	if (n == word.size())
	{
		return true;
	}
	if (n == 0)
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j=0; j<board.at(i).size(); ++j)
			{
				if (board.at(i).at(j) == word.at(n))
				{
					char c = board.at(i).at(j);
					board.at(i).at(j) = '*';
					if (exist_dfs(board, word, n + 1, i, j))  //�����һ��ݹ�ɹ�����ô��˵��ʣ�µ��ַ��ɹ��ˣ���ֱ�ӷ���true������Ļ���ԭ��ǰ�ַ�������ѭ��
					{
						return true;
					}
					else
					{
						board.at(i).at(j) = c;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (row + direction[i][0] < 0 || row + direction[i][0] >= board.size() || column + direction[i][1] < 0 || column + direction[i][1] >= board.at(row).size())
			{
				continue;
			}
			else
			{
				if (board.at(row + direction[i][0]).at(column + direction[i][1]) == word.at(n))
				{
					char c = board.at(row + direction[i][0]).at(column + direction[i][1]);
					board.at(row + direction[i][0]).at(column + direction[i][1]) = '*';
					if (exist_dfs(board, word, n + 1, row + direction[i][0], column + direction[i][1]))
					{
						return true;
					}
					else
					{
						board.at(row + direction[i][0]).at(column + direction[i][1]) = c;
					}
				}
			}
		}
	}
	return false;
}
bool exist(vector<vector<char>>& board, string word)  //��������
{
	if (board.size() == 0 || word.size() == 0)
	{
		return false;
	}
	//�����������
	return exist_dfs(board, word, 0, 0, 0);
}

vector<int> countBits_1(int num)  //�Լ��� 
{
	//�����Ѿ�֪��n��ʱ��1�ĸ�������ô����2n������ֱ�ӽ�n�Ķ��������ƣ����1�ĸ������䣻�����2n+1�Ļ����ǽ�n���������ƣ�Ȼ����ĩβ���ƺ�������һλ0����1��Ҳ�ͱ�ԭ��n��1������һ��
	if (num == 0)
	{
		return { 0 };
	}
	else if (num == 1)
	{
		return { 0, 1 };
	}
	else if (num == 2)
	{
		return { 0, 1, 1 };
	}
	vector<int> result = { 0, 1, 1 };
	for (int i = 3; i <= num; ++i)
	{
		if (i % 2 == 1)
		{
			result.push_back(result.at(i / 2) + 1);
		}
		else
		{
			result.push_back(result.at(i / 2));
		}
	}
	return result;
}

vector<int> countBits_2(int num) //ͨ��i & (i - 1)
{
	if (num == 0)
	{
		return { 0 };
	}
	else if (num == 1)
	{
		return { 0, 1 };
	}
	else if (num == 2)
	{
		return { 0, 1, 1 };
	}
	vector<int> result = { 0, 1, 1 };
	for (int i=3; i<=num; ++i)
	{
		result.push_back(result.at(i & (i - 1)) + 1);
	}
	return result;
}

int minimumTotal_result = INT_MAX;
void minimumTotal_dfs(vector<vector<int>>& triangle, int i, int j, int tmp)  //�����������
{
	if (i >= triangle.size())
	{
		minimumTotal_result = min(tmp, minimumTotal_result);
		tmp = 0;
		return;
	}
	tmp += triangle.at(i).at(j);
	minimumTotal_dfs(triangle, i + 1, j, tmp);
	minimumTotal_dfs(triangle, i + 1, j + 1, tmp);
}
int minimumTotal_1(vector<vector<int>>& triangle)  //��������С·����--�������������ʱ��
{
	if (triangle.size() == 0)
	{
		return 0;
	}
	int tmp = 0;
	minimumTotal_dfs(triangle, 0, 0, tmp);
	return minimumTotal_result;
}

int minimumTotal_2(vector<vector<int>>& triangle)  //��������С·����
{
	if (triangle.size() == 0)
	{
		return 0;
	}
	vector<int> dp(triangle.size(), 0);   //dp��ʾ����ײ㵽��ǰ��(i��j)����С·����
	dp.assign(triangle.at(triangle.size() - 1).begin(), triangle.at(triangle.size() - 1).end());
	for (int i = triangle.size() - 2; i >= 0; --i)
	{
		for (int j = 0; j < triangle.at(i).size(); ++j)
		{
			dp[j] = min(dp[j], dp[j + 1]) + triangle.at(i).at(j);
		}
	}
	return dp[0];  //���ع�ɵ�һ��Ԫ��
}

int maxProduct(vector<int>& nums)  //�˻����������
{
	if (nums.size() == 0)
	{
		return 0;
	}
	vector< vector<int> > dp(nums.size(), vector<int>(2));  //��ʾ��iΪֹ�������С�˻�
	dp[0][0] = nums.at(0);  //�ڶ�άΪ0��ʾ�������ֵ
	dp[0][1] = nums.at(0);  //�ڶ�άΪ1��ʾ��Сֵ(��������ֵ���)
	int result = nums.at(0);
	for (int i=1; i<nums.size(); ++i)
	{
		if (nums.at(i) < 0)
		{
			dp[i][1] = min(dp[i - 1][0] * nums.at(i), nums.at(i));
			dp[i][0] = max(dp[i - 1][1] * nums.at(i), nums.at(i));
		}
		else
		{
			dp[i][0] = max(dp[i - 1][0] * nums.at(i), nums.at(i));
			dp[i][1] = min(dp[i - 1][1] * nums.at(i), nums.at(i));
		}
		result = max(result, dp[i][0]);
	}
	return result;
}

int maxProfit_cooldown(vector<int>& prices)  //Ҫע��������䶳��ֻ����������У������û��
{
	//dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
	//dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i])
	//���ͣ��� i ��ѡ�� buy ��ʱ��Ҫ�� i - 2 ��״̬ת�ƣ������� i - 1 ��
	if (prices.size() == 0)
	{
		return 0;
	}
	int n = prices.size();
	int dp_i_0 = 0, dp_i_1 = INT_MIN;
	int dp_pre_0 = 0;    //���� dp[i-2][0]
	for (int i = 0; i < n; i++) {
		int temp = dp_i_0;
		dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
		dp_i_1 = max(dp_i_1, dp_pre_0 - prices[i]);
		dp_pre_0 = temp;
	}
	return dp_i_0;
}

int lengthOfLIS(vector<int>& nums)  //�����������
{
	if (nums.size() <= 1)
	{
		return nums.size();
	}
	vector<int> dp(nums.size());  //������i��Ԫ�ص�ǰi�����е������������, dp[i] = max(dp[j]) + 1, j=0->i-1
	dp[0] = 1;
	int result = 1;
	for (int i=1; i<nums.size(); ++i)
	{
		int tmp = 0;
		for (int j=0; j<i; ++j)
		{
			if (nums.at(j) < nums.at(i))  //Ҫ�Ǵ��ڵ��ڣ���ô�϶���������i��Ԫ����
			{
				tmp = max(tmp, dp[j]);
			}
		}
		dp[i] = tmp + 1;
		result = max(result, dp[i]);
	}
	return result;
}

int coinChange_1(vector<int>& coins, int amount)  //��Ǯ�һ�
{
	vector<int> dp(amount + 1, amount + 1);
	dp[0] = 0;
	for (int i=1; i<=amount; ++i)
	{
		for (int j=0; j<coins.size(); ++j)
		{
			if (coins.at(j) <= i)
			{
				dp[i] = min(dp[i], dp[i - coins.at(j)] + 1);
			}
		}
	}
	return dp[amount] > amount ? -1 : dp[amount];
}

int coinChange_2(vector<int>& coins, int amount)  //��Ǯ�һ�
{
	if (amount < 0 || coins.size() == 0)
	{
		return -1;
	}
	if (amount == 0)
	{
		return 0;
	}
	sort(coins.begin(), coins.end());
	if (amount < coins[0])
	{
		return -1;
	}
	vector<int> dp(amount + 1, amount + 1);
	dp[0] = 0;
	for (int i = 1; i <= amount; ++i)
	{
		for (int j = 0; j < coins.size(); ++j)
		{
			if (i == coins[j])
			{
				dp[i] = 1;
				break;
			}
			else if (i - coins[j] > 0)
			{
				dp[i] = min(dp[i], dp[i - coins[j]] + 1);
			}
		}
	}
	return (dp[amount] == amount + 1 ? -1 : dp[amount]);
}

int numIslands(vector<vector<char>>& grid)  //��������--���鼯
{
	if (grid.size() == 0 || grid.at(0).size() == 0)
	{
		return 0;
	}
	int count = 0, n = grid.size(), m = grid.at(0).size();
	vector<int> parent(grid.size()*grid.at(0).size(), -1);
	vector<int> r(grid.size()*grid.at(0).size(), 0);  //����rank
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (grid.at(i).at(j) == '1')
			{
				count++;
				parent[i * m + j] = i * m + j;
			}
		}
	}
	int direction[][2] = { {1,0}, {0,1}, {-1,0},{0,-1} };
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (grid[i][j] == '0')
			{
				continue;
			}
			for (int k = 0; k < 4; ++k)
			{
				int ti = i + direction[k][0], tj = j + direction[k][1];
				if (ti >= 0 && tj >= 0 && ti < n && tj < m && grid[ti][tj] == '1')
				{
					int rootx = parent[i * m + j], rooty = parent[ti * m + tj];
					while (rootx != parent[rootx])
					{
						rootx = parent[rootx];
					}
					while (rooty != parent[rooty])
					{
						rooty = parent[rooty];
					}
					if (rootx != rooty)  //���������ͬ���������������ڵģ����Ҫ�ϲ�
					{
						if (r[rootx] > r[rooty])
						{
							parent[rooty] = rootx;
						}
						else if (r[rootx] < r[rooty])
						{
							parent[rootx] = rooty;
						}
						else
						{
							parent[rooty] = rootx;
							r[rootx] += 1;
						}
						--count;
					}
				}
			}
		}
	}
	return count;
}

int findCircleNum(vector<vector<int>>& M)  //����Ȧ
{
	if (M.size() == 0 || M.at(0).size() == 0)
	{
		return 0;
	}
	int count = 0, n = M.size(), m = M.at(0).size();
	vector<int> parent(m, -1);
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<m; ++j)
		{
			if (M[i][j] == 1 && i != j)
			{
				int rootx = i, rooty = j;
				while (parent[rootx] != -1)
				{
					rootx = parent[rootx];
				}
				while (parent[rooty] != -1)
				{
					rooty = parent[rooty];
				}
				if (rootx != rooty) //��i���͵�j����ʶ��������ô���ǵ��ϴ�ҲӦ����ʶ
				{
					parent[rooty] = rootx;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (parent[i] == -1)
		{
			count++;
		}
	}
	return count;
}

class LRUCache {
public:
	int _capacity;
	int time;
	//��һ��intΪkey���ڶ���intΪvalue��������intΪʹ��Ƶ�ʣ����ĸ�intΪ���ʹ�û����ʱ��
	unordered_map<int, pair<int, pair<int, int> > > lruUM; 
	LRUCache(int capacity) {
		this->_capacity = capacity;
		time = 1;
	}

	int get(int key) {
		unordered_map<int, pair<int, pair<int, int> > >::iterator ifind = lruUM.find(key);
		if (ifind == lruUM.end())
		{
			return -1;
		}
		time++;
		ifind->second.second.first += 1;
		ifind->second.second.second = time;
		return ifind->second.first;
	}

	void put(int key, int value) {
		time++;
		unordered_map<int, pair<int, pair<int, int> > >::iterator ifind = lruUM.find(key);
		if (ifind != lruUM.end())
		{
			if (ifind->second.first != value)  //�������Ҳֵ���ȵĻ�����Ҫ�޸�ֵ���Ҹı�Ƶ�ʺ�ʱ��
			{
				ifind->second.first = value;
				ifind->second.second.first += 1;
				ifind->second.second.second = time;
			}
			return;
		}
		if (lruUM.size() < this->_capacity)  //������пռ䣬ֱ�Ӳ���
		{
			pair<int, pair<int, pair<int, int> > > p(key, pair<int, pair<int, int> >(value, pair<int, int>(1, time)));
			lruUM.insert(p);
		}
		else
		{
			ifind = lruUM.begin();
			int mint = ifind->second.second.second;
			for (; ifind != lruUM.end(); ifind++)  //���ҵ�ʱ�����ȵ��Ǹ�
			{
				mint = min(mint, ifind->second.second.second);
			}
			int tmp = INT_MIN;
			for (ifind=lruUM.begin(); ifind != lruUM.end(); ifind++)
			{
				if (ifind->second.second.second == mint)
				{
					if (tmp == INT_MIN)
					{
						tmp = ifind->first;
					}
					else  //���ʱ����ͬ����ô��Ҫȥ��Ƶ����͵��Ǹ�
					{
						lruUM.find(tmp)->second.second.first > ifind->second.second.first ? tmp = ifind->first : tmp = tmp;
					}
				}
			}
			lruUM.erase(lruUM.find(tmp));
			pair<int, pair<int, pair<int, int> > > p(key, pair<int, pair<int, int> >(value, pair<int, int>(1, time)));
			lruUM.insert(p);
		}
	}
};

string longestPalindrome(string s)  //������Ӵ�
{
	if (s.size() <= 1)
	{
		return s;
	}
	vector<vector<int> > dp(s.size(), vector<int>(s.size()));  //��i������j��Ԫ��(����i��j)�Ƿ��ǻ��Ĵ����ǵĻ�����1������Ϊ0
	int maxLen = 1, start = 0;  //���Ĵ���󳤶ȺͿ�ʼλ�ã�����ж����ʼλ�ã���ôstartΪ����һ��
	for (int i=0; i<s.size(); ++i)
	{
		dp[i][i] = 1;  //����һ���ַ��϶��ǻ���
		if (i < s.size() - 1 && s[i] == s[i + 1])  //������ڵ�������ͬ���ǻ���
		{
			dp[i][i + 1] = 1;
			maxLen = 2;
			start = i;
		}
	}
	for (int l=3; l<=s.size(); ++l)  //�ӳ���Ϊ3��ʼ
	{
		for (int i=0; i+l-1<s.size(); ++i)
		{
			int j = i + l - 1;
			if (s[i] == s[j] && dp[i + 1][j - 1] == 1)  //�����i���͵�j��һ��������֮����Ѿ��ǻ��Ĵ���
			{
				maxLen = l;
				start = i;
				dp[i][j] = 1;
			}
		}
	}
	return s.substr(start, maxLen);
}

string convert(string s, int numRows)  //Z ���α任
{
	if (s.size() <= numRows || numRows == 1)
	{
		return s;
	}
	string result;
	int n = s.size();
	int cycle = 2 * numRows - 2;
	for (int i=0; i<numRows; ++i)
	{
		for (int j=0; j+i<n; j+=cycle)
		{
			result += s[j + i];
			if (i != 0 && i != numRows - 1 && j + cycle - i < n)
			{
				result += s[j + cycle - i];
			}
		}
	}
	return result;
}

int myAtoi(string str)  //�ַ���ת������ (atoi)
{
	if (str.size() == 0)
	{
		return 0;
	}
	int result = 0;
	bool isZhengShu = true;
	int i = 0;
	while (str[i] == ' ')
	{
		++i;
	}
	if (str[i] == '-')
	{
		isZhengShu = false;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		++i;
	}
	while (i < str.size() && str[i] >= '0' && str[i] <= '9')
	{
		int tmp = str[i] - '0';
		if (isZhengShu)
		{
			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && str[i] >= '7'))
			{
				return INT_MAX;
			}
		}
		else
		{
			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && str[i] >= '8'))
			{
				return INT_MIN;
			}
		}
		result = result * 10 + tmp;
		++i;
	}
	isZhengShu ? result : -result;
}

int maxArea_1(vector<int>& height)   //ʢ���ˮ������--��������ʱ��
{
	int result = 0;
	for (int i = 0; i < height.size(); ++i)
	{
		for (int j = i + 1; j < height.size(); ++j)
		{
			result = max(result, (j - i)*min(height[j], height[i]));
		}
	}
	return result;
}

int maxArea_2(vector<int>& height)   //ʢ���ˮ������--˫ָ��
{
	int l = 0, r = height.size() - 1;
	int result = 0;
	while (l < r)
	{
		int tmp = (r - l) * min(height[l], height[r]);
		result = max(result, tmp);
		if (height[l] < height[r])  //����Ҳ����ô��ʱ����lΪ���ߣ���ô�����Сr�Ļ���ֻ�����Խ��ԽС�����Ҫ����l
		{
			l++;
		}
		else
		{
			r--;
		}
	}
	return result;
}

string intToRoman(int num)  // ����ת��������
{
	if (num > 3999 || num < 1)
	{
		return "";
	}
	string result;
	map<int, string> m;
	m.insert(pair<int, string>(1, "I"));
	m.insert(pair<int, string>(4, "IV"));
	m.insert(pair<int, string>(5, "V"));
	m.insert(pair<int, string>(9, "IX"));
	m.insert(pair<int, string>(10, "X"));
	m.insert(pair<int, string>(40, "XL"));
	m.insert(pair<int, string>(50, "L"));
	m.insert(pair<int, string>(90, "XC"));
	m.insert(pair<int, string>(100, "C"));
	m.insert(pair<int, string>(400, "CD"));
	m.insert(pair<int, string>(500, "D"));
	m.insert(pair<int, string>(900, "CM"));
	m.insert(pair<int, string>(1000, "M"));
	map<int, string>::iterator ii = m.end();
	--ii;  //������������
	while (num > 0)
	{
		if (num >= ii->first)
		{
			result = result + ii->second;
			num -= ii->first;
		}
		else
		{
			--ii;
		}
	}
	return result;
}

int threeSumClosest(vector<int>& nums, int target)  //��ӽ�������֮��
{
	if (nums.size() <= 2)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());
	int cha = INT_MAX;
	int result = 0;
	for (int i=0; i<nums.size(); ++i)
	{
		int l = i + 1, r = nums.size() - 1;
		while (l < r)  //˫ָ�룬�����ȵĻ�����һ����
		{
			int tmp = nums[i] + nums[l] + nums[r];
			if (cha > abs(tmp - target))
			{
				cha = abs(tmp - target);
				result = tmp;
			}
			if (tmp == target)
			{
				return target;
			}
			else if(tmp < target)
			{
				++l;
			}
			else
			{
				--r;
			}
		}
	}
	return result;
}

vector<string> letterCombinations_item(int index, map<int, vector<char> > &m, string digits)
{
	if (index >= digits.size())
	{
		return {};
	}
	int d = digits[index] - '0';
	vector<string> result;
	vector<char> s = m.find(d)->second;
	vector<string> tmp = letterCombinations_item(index + 1, m, digits);  //��֪�Ӻ������index+1(����)�Ľ������ô��ǰ�Ľ�����ǵõ���tmp�ٸ���ǰ���ִ�����ַ�ȫ���
	if (tmp.size() == 0)
	{
		for (int j = 0; j < s.size(); ++j)
		{
			result.push_back("");
			result[j] = s[j] + result[j];
		}
	}
	else
	{
		for (int i = 0; i < tmp.size(); ++i)
		{
			for (int j = 0; j < s.size(); ++j)
			{
				result.push_back(s[j] + tmp[i]);
			}
		}
	}
	return result;
}
vector<string> letterCombinations(string digits)  //�绰�������ĸ���
{
	if (digits.size() == 0)
	{
		return {};
	}
	map<int, vector<char> > m;
	m[2] = { 'a', 'b', 'c' };
	m[3] = { 'd', 'e', 'f' };
	m[4] = { 'g', 'h', 'i' };
	m[5] = { 'j', 'k', 'l' };
	m[6] = { 'm', 'n', 'o' };
	m[7] = { 'p', 'q', 'r', 's' };
	m[8] = { 't', 'u', 'v' };
	m[9] = { 'w', 'x', 'y', 'z' };
	return letterCombinations_item(0, m, digits);
}

vector<vector<int>> fourSum(vector<int>& nums, int target)  //����֮��
{
	if (nums.size() <= 3)
	{
		return {};
	}
	sort(nums.begin(), nums.end());
	vector< vector<int> > result;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (i > 0 && nums[i] == nums[i - 1])  //�����ǰ��ǰһ����ͬ����˵���Ѿ��ù���
		{
			continue;
		}
		for (int j = i + 1; j < nums.size(); ++j)
		{
			if (j > i + 1 && nums[j] == nums[j - 1])  //���j�Ǵ���i+1��Ҳ����˵j-1 > i, ���ظ��Ļ���˵��֮ǰ�ù���,���j=i+1��continue�Ļ����Ͱѵ�i��ȥ����
			{
				continue;
			}
			int tmp = target - nums[i] - nums[j];
			int l = j + 1, r = nums.size() - 1;
			while (l < r)
			{
				if (nums[l] + nums[r] == tmp)
				{
					vector<int> tmp;
					tmp.push_back(nums[i]);
					tmp.push_back(nums[j]);
					tmp.push_back(nums[l]);
					tmp.push_back(nums[r]);
					result.push_back(tmp);
					int t = nums[l];
					while (l < nums.size() && nums[l] == t) //���֮����е���nums[l]�ģ���ôҪһֱ����Խ��ȥ
					{
						++l;
					}
					t = nums[r];
					while (r >= 0 && nums[r] == t)  //���֮ǰ�е��ڵģ�Ҫһֱ��ǰԽ��ȥ
					{
						--r;
					}
				}
				else if (nums[l] + nums[r] < tmp)
				{
					++l;
				}
				else
				{
					--r;
				}
			}
		}
	}
	return result;
}

ListNode* removeNthFromEnd(ListNode* head, int n)  //ɾ������ĵ�����N���ڵ�
{
	if (!head)
	{
		return head;
	}
	vector<ListNode*> tmp;
	int i = 0;
	while (head)
	{
		tmp.push_back(head);
		++i;
		head = head->next;
	}
	if (i < n)
	{
		return tmp[0];
	}
	int index = i - n;
	if (index == 0)  //�����ɾ����һ��
	{
		if (i <= 1) //����ڵ����С�ڵ���һ��
		{
			return nullptr;
		}
		else  //����ڵ��������1����ֱ�Ӵӵڶ�����ʼ����
		{
			return tmp[1];
		}
	}
	else  //�������ɾ����һ��
	{
		if (n == 1)  //�����ɾ�����һ����ֱ���õ����ڶ�����nextָ��nullptr
		{
			tmp[index - 1]->next = nullptr;
		}
		else  //����Ļ�������ǰһ��ָ���һ��
		{
			tmp[index - 1]->next = tmp[index + 1];
		}
		return tmp[0];
	}
}

int divide(int dividend, int divisor)  //�������
{
	if (divisor == 0)
	{
		return INT_MAX;
	}
	if (dividend == 0)
	{
		return 0;
	}
	bool flag = true;  //���������
	if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	unsigned int x = 0, y = 0;
	if (dividend > 0)
	{
		x = dividend;
	}
	else
	{
		if (dividend == INT_MIN)
		{
			x = INT_MAX + 1;
		}
		else
		{
			x = -dividend;
		}
	}
	if (divisor > 0)
	{
		y = divisor;
	}
	else
	{
		if (divisor == INT_MIN)
		{
			y = INT_MAX + 1;
		}
		else
		{
			y = -divisor;
		}
	}
	int result = 0;
	int i = 31;
	while (i >= 0)
	{
		if ((x >> i) >= y)
		{
			if (i == 31)
			{
				return flag ? INT_MAX : INT_MIN;
			}
			result += (1 << i);
			x -= (y << i);
		}
		--i;
	}
	return flag ? result : -result;
}

void nextPermutation(vector<int>& nums)  //��һ������
{
	/*
	���ǻ�ϣ����һ�������ӵķ��Ⱦ����ܵ�С�����������㡰��һ�������뵱ǰ���н��ڡ���Ҫ��
	Ϊ���������Ҫ��������Ҫ
	1. �ھ����ܿ��ҵĵ�λ���н�������Ҫ�Ӻ���ǰ����
	2. ��һ��������С�Ĵ�����ǰ���С������������ 123465����һ������Ӧ�ð� 5 �� 4 ���������ǰ� 6 �� 4 ����
	3. ����������ǰ�����Ҫ���������������������Ϊ�����������о�����С�����С�
	�� 123465 Ϊ�������Ȱ�����һ�������� 5 �� 4���õ� 123564��
	Ȼ����Ҫ�� 5 ֮���������Ϊ���򣬵õ� 123546��
	��Ȼ 123546 �� 123564 ��С��123546 ���� 123465 ����һ������

	*/
	if (nums.size() <= 1)
	{
		return;
	}
	bool isJiangXu = true, isShengXu = true;
	int x = 0, y = 0; //���������
	for (int i=1; i<nums.size(); ++i)
	{
		if (nums[i] > nums[i - 1])
		{
			isJiangXu = false;
			x = i - 1;
			y = i;
		}
		else if(nums[i] < nums[i - 1])
		{
			isShengXu = false;
		}
	}
	if (isJiangXu)
	{
		sort(nums.begin(), nums.end());
	}
	else if (isShengXu)
	{
		swap(nums[nums.size() - 1], nums[nums.size() - 2]);
	}
	else  //������ͽ��������������
	{
		//�����ϸ�forѭ��������֪����ʱx��yΪ���һ������ģ���ˣ�y֮��(����y)����Ϊ�����
		for (int i = nums.size() - 1; i >= 0; --i)  //�Ӻ���ǰ�ҵ���x����ĵ�һ���������ȿ϶���y���������ں����ǽ���ģ�����ҵ��ĵ�һ���϶��Ǵ���x������С��
		{
			if (nums[i] > nums[x])
			{
				y = i;
				break;
			}
		}
		swap(nums[x], nums[y]);  //������С�Ĵ�����x
		sort(nums.begin() + x + 1, nums.end());  //�ٽ�����Ľ����Ϊ�����ҵ�����ԭ���е���С������
	}
}

int search(vector<int>& nums, int target)  //������ת��������
{
	if (nums.size() == 0)
	{
		return -1;
	}
	if (nums.size() == 1)
	{
		return nums[0] == target ? 0 : -1;
	}
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == target)
		{
			return mid;
		}
		if (nums[l] <= nums[mid])  //��ʾ��l��mid������,��Ϊ����mid=l,����Ҫ�е���
		{
			if (nums[l] <= target && nums[mid] > target)  //��l��mid֮��
			{
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		else  //��ôl��������mid������Ҳ����˵mid��r�������
		{
			if (nums[mid] < target && nums[r] >= target)
			{
				l = mid + 1;
			}
			else
			{
				r = mid - 1;
			}
		}
	}
	--l;
	if (l < 0)  //���lΪ����
	{
		return -1;
	}
	return nums[l] == target ? l : -1;
}

int searchRange_item(vector<int> &nums, int target, bool isLeft)
{
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == target && isLeft) //��������ʱ�򲻷��أ������Ҫ����˵㣬��r��ǰ��
		{
			r = mid - 1;
		}
		else if (nums[mid] > target)
		{
			r = mid - 1;
		}
		else   //���else��������һ����������������ҵ����Ҷ˵㣬��l������
		{
			l = mid + 1;
		}
	}
	if (l == 0)
	{
		return nums[l] == target ? 0 : -1;  //����Ӧ���Ƿ���0����-1
	}
	else
	{
		int tmp = l - 1;
		return nums[tmp] == target ? tmp : l;   //���l - 1��������target�Ļ��ͷ�������±��С�ģ�����ͷ����±���
	}
}
vector<int> searchRange(vector<int>& nums, int target)  //�����������в���Ԫ�صĵ�һ�������һ��λ��
{
	if (nums.size() == 0)
	{
		return {-1, -1};
	}
	else if (target < nums[0] || target > nums[nums.size() - 1])
	{
		return {-1, -1};
	}
	vector<int> result = { -1, -1 };
	int l = searchRange_item(nums, target, true), r = searchRange_item(nums, target, false);
	result[0] = (nums[l] == target ? l : -1);  //�жϷ��ص��±��Ƿ����target
	result[1] = (nums[r] == target ? r : -1);
	return result;
}

set< vector<int> > combinationSum_s;
void combinationSum_dfs(vector<int>& candidates, int target, vector<int> s)  //�����������
{
	if (target == 0)
	{
		if (s.size() > 0)
		{
			sort(s.begin(), s.end());
			combinationSum_s.insert(s);
		}
		return;
	}
	else if (target < 0)
	{
		return;
	}
	for (int i=0; i<candidates.size(); ++i)
	{
		vector<int> tmp = s;  //������Ϊ�����ù��ĵ�i-1����ȥ�������Բ�����s.push_back(candidates[i])
		tmp.push_back(candidates[i]);
		combinationSum_dfs(candidates, target - candidates[i], tmp);
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target)  //����ܺ�
{
	if (candidates.size() == 0)
	{
		return {};
	}
	combinationSum_dfs(candidates, target, {});
	vector< vector<int> > result;
	result.assign(combinationSum_s.begin(), combinationSum_s.end());
	return result;
}

set< vector<int> > combinationSum2_s;
void combinationSum2_dfs(vector<int>& candidates, int target, set<int> s, vector<int> v)
{
	if (target == 0)
	{
		if (v.size() > 0)
		{
			sort(v.begin(), v.end());
			combinationSum2_s.insert(v);
		}
		return;
	}
	else if(target < 0)
	{
		return;
	}
	for (int i=0; i<candidates.size(); ++i)
	{
		if (s.find(i) != s.end())  //����ù���
		{
			continue;
		}
		if (target - candidates[i] < 0)  //��֦
		{
			continue;
		}
		s.insert(i);
		vector<int> tmp = v; //������Ϊ�����ù��ĵ�i-1����ȥ�������Բ�����s.push_back(candidates[i])
		tmp.push_back(candidates[i]);
		combinationSum2_dfs(candidates, target - candidates[i], s, tmp);
		s.erase(i);  //���ù������ɾ��
	}
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)  //����ܺ� II
{
	if (candidates.size() == 0)
	{
		return {};
	}
	sort(candidates.begin(), candidates.end());
	combinationSum2_dfs(candidates, target, {}, {});
	vector< vector<int> > result;
	result.assign(combinationSum2_s.begin(), combinationSum2_s.end());
	return result;
}

string multiply_item(int index, vector<string> &tmp)
{
	if (index == 0)
	{
		return tmp[0];
	}
	else if (index < 0)
	{
		return "0";
	}
	string s1 = multiply_item(index - 1, tmp);
	string s2 = tmp[index];
	int i = s1.size() - 1, j = s2.size() - 1, jinwei = 0;
	string result;
	while (i >= 0 || j >= 0)
	{
		int x = 0, y = 0;
		if (i >= 0)
		{
			x = s1[i] - '0';
		}
		if (j >= 0)
		{
			y = s2[j] - '0';
		}
		int z = (x + y + jinwei) % 10;
		jinwei = (x + y + jinwei) / 10;
		result = std::to_string(z) + result;
		--i;
		--j;
	}
	if (jinwei)
	{
		result = std::to_string(jinwei) + result;
	}
	return result;
}
string multiply(string num1, string num2)  //�ַ������
{
	if (num1.size() == 0 || num2.size() == 0)
	{
		return "";
	}
	else if (num1[0] == '0' || num2[0] == '0')
	{
		return "0";
	}
	vector<string> tmp;
	int jinwei = 0;
	int numOf0 = 0;
	for (int i = num1.size() - 1; i >= 0; --i)
	{
		string s;
		int x = num1[i] - '0';
		jinwei = 0;  //jinwei����
		for (int j = num2.size() - 1; j >= 0; --j)
		{
			int y = num2[j] - '0';
			int z = (x * y + jinwei) % 10;
			jinwei = (x * y + jinwei) / 10;
			s = std::to_string(z) + s;
		}
		if (jinwei)  //�������jinwei���ͷ�����ǰ��
		{
			s = std::to_string(jinwei) + s;
		}
		for (int k = 0; k < numOf0; ++k)
		{
			s = s + std::to_string(0);  //���Ϻ������
		}
		tmp.push_back(s);
		numOf0++;
	}
	return multiply_item(tmp.size() - 1, tmp);
}

set< vector<int> > permute_s;
void permute_item(vector<int> &nums, set<int> s, vector<int> v)
{
	if (v.size() == nums.size())
	{
		permute_s.insert(v);
		return;
	}
	else if (v.size() > nums.size())
	{
		return;
	}
	for (int i=0; i<nums.size(); ++i)
	{
		if (s.find(i) != s.end())
		{
			continue;
		}
		s.insert(i);
		vector<int> tmp = v;
		tmp.push_back(nums[i]);
		permute_item(nums, s, tmp);
		s.erase(i);
	}
}
vector<vector<int>> permute(vector<int>& nums)  //ȫ����
{
	if (nums.size() == 0)
	{
		return {};
	}
	else if (nums.size() == 1)
	{
		return { {nums[0]} };
	}
	permute_item(nums, {}, {});
	vector< vector<int> > result;
	result.assign(permute_s.begin(), permute_s.end());
	return result;
}

set< vector<int> > permuteUnique_s;
void permuteUnique_item(vector<int> &nums, set<int> s, vector<int> v)
{
	if (v.size() == nums.size())
	{
		permuteUnique_s.insert(v);
		return;
	}
	else if (v.size() > nums.size())
	{
		return;
	}
	for (int i = 0; i < nums.size(); ++i)
	{
		if (s.find(i) != s.end())
		{
			continue;
		}
		s.insert(i);
		vector<int> tmp = v;
		tmp.push_back(nums[i]);
		permuteUnique_item(nums, s, tmp);
		s.erase(i);  //ɾ���ù���
	}
}
vector<vector<int>> permuteUnique(vector<int>& nums) 
{
	if (nums.size() == 0)
	{
		return {};
	}
	else if (nums.size() == 1)
	{
		return { {nums[0]} };
	}
	permuteUnique_item(nums, {}, {});
	vector< vector<int> > result;
	result.assign(permuteUnique_s.begin(), permuteUnique_s.end());
	return result;
}

void rotate(vector<vector<int>>& matrix)  //��תͼ��
{
	//��ת�ã�Ȼ��������ֱ�����߶Գ�
	if (matrix.size() <= 1)
	{
		return;
	}
	for (int i = 0; i < matrix.size(); ++i)  //ת��
	{
		for (int j = i + 1; j < matrix[i].size(); ++j)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
	}
	float xian = matrix[0].size() / 2.0 - 0.5; //��ֱ���ĶԳ���
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j <= xian; ++j)
		{
			int tmp = 2 * xian - j;
			swap(matrix[i][j], matrix[i][tmp]);
		}
	}
}

vector<vector<string>> groupAnagrams(vector<string>& strs)  //��ĸ��λ�ʷ���
{
	if (strs.size() == 0)
	{
		return {};
	}
	else if (strs.size() == 0)
	{
		return { {strs[0]} };
	}
	unordered_map<string, vector<string> > um;
	unordered_map<string, vector<string> >::iterator ifind;
	for (int i=0; i<strs.size(); ++i)
	{
		string tmp = strs[i];
		sort(tmp.begin(), tmp.end());  //���ź����Ϊkeyֵ
		ifind = um.find(tmp);  //������ֵ�ǰ�ַ����źõ�֮���keyֵ���ڣ���ô�Ͱѵ�ǰ�ַ������룬���������keyֵ
		if (ifind != um.end())
		{
			ifind->second.push_back(strs[i]);
		}
		else
		{
			um.insert(pair<string, vector<string> >(tmp, {strs[i]}));
		}
	}
	vector< vector<string> > result;
	for (ifind=um.begin(); ifind != um.end(); ifind++)
	{
		result.push_back(ifind->second);
	}
	return result;
}

vector<int> spiralOrder(vector<vector<int>>& matrix)  //��������
{
	if (matrix.size() == 0)
	{
		return {};
	}
	else if (matrix.size() == 1)
	{
		return matrix[0];
	}
	set< pair<int, int> > s;
	vector<int> result;
	int i = 0, j = 0, fangxiang = 0;
	int nm = matrix.size() * matrix.at(0).size();
	int direction[][2] = { {0,1},{1,0},{0,-1},{-1,0} };  //��->��->��->��->�ҡ�������
	while (s.size() < nm)
	{
		if (i >= matrix.size() || j >= matrix.at(0).size() || i < 0 || j < 0)  //���������Χ����ô�����ϴ�δ������Χ�ĸ�������ǰ��
		{
			i -= direction[fangxiang][0];
			j -= direction[fangxiang][1];
			fangxiang = (fangxiang >= 3 ? 0 : fangxiang + 1);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
			continue;
		}
		pair<int, int> p(i, j);
		if (s.find(p) == s.end())  
		{
			s.insert(p);
			result.push_back(matrix[i][j]);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
		}
		else  //�����ǰ�����Ѿ����ˣ���ô�����ϴθղ���ģ�������ǰ��
		{
			i -= direction[fangxiang][0];
			j -= direction[fangxiang][1];
			fangxiang = (fangxiang >= 3 ? 0 : fangxiang + 1);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
			continue;
		}
	}
	return result;
}

bool canJump(vector<int>& nums)  //��Ծ��Ϸ--��̬�滮
{
	if (nums.size() <= 1)
	{
		return true;
	}
	if (nums[0] == 0)
	{
		return false;
	}
	vector<bool> flag(nums.size(), false);  //��0����ǰ��λ���Ƿ����ߵ�,��ʼ���߲���
	flag[0] = true;  //��0��λ�ÿ϶����ߵ�
	for (int i=1; i<nums.size(); ++i)
	{
		for (int j=i-1; j>=0; --j)  //����ǰλ���ң����֮ǰ��һ��λ���ܵ���Ҵ����֮ǰ��λ������ߵĲ������ڵ���֮��ľ��룬��ô��ǰλ�����ߵ�
		{
			if (flag[j] && nums[j] >= i - j)
			{
				flag[i] = true;
				break;  //ֻ��Ҫ�ҵ�����һ�ַ�ʽ����,����ֱ��break
			}
		}
	}
	return flag[nums.size() - 1];
}

vector<vector<int>> merge(vector<vector<int>>& intervals)  //�ϲ�����
{
	if (intervals.size() <= 1)
	{
		return intervals;
	}
	//���ս�Сֵ�Ĵ�С������������ȾͱȽϽϴ�ֵ
	//������ŵĻ��������[2,3][5,7][3,5]�Ľ��Ϊ[2,5][3,7]
	//������Ϊ��һ��һ������ӿռ�,�����������ཻ��������п�����������ϵ���������䣬��ô�����ϵ����϶���������֮�䣬��������󣬿�����ǰ����Ⱥ������ϵ����ϲ����ٸ�����ĺϲ�
	sort(intervals.begin(), intervals.end());  
	vector< vector<int> > result;
	result.push_back(intervals[0]);  //�Ȱѵ�һ�����ȥ
	for (int i=1; i<intervals.size(); ++i)
	{
		vector<int> tmp = intervals[i];
		for (int j=0; j<result.size(); ++j)  //Ѱ���Ѿ�������Ƿ���Ժϲ�����
		{
			if (tmp[1] < result[j][0] || tmp[0] > result[j][1])  //������䲻�����ص�
			{
				if (j == result.size() - 1)  //�����ǰ�Ѿ������һ���ж�������
				{
					result.push_back(tmp); //ֱ�Ӳ���
					break;
				}
				else
				{
					continue;  //����������һ���ж����䣬��ô������һ�������жϰ�
				}
			}
			else
			{
				//�ϲ�����
				result[j][0] = min(result[j][0], tmp[0]);
				result[j][1] = max(result[j][1], tmp[1]);
				break;  
				//�ϲ�֮����������ˣ�����break����
				//��Ϊ���ź���ģ���˽��������Ǹ����䣬����й�ϵ�Ϳ��Ժϲ�������Ҫ��ѭ����������һ���Ƿ�ϲ�
				//��Ϊ����뵱ǰ�ܺϲ��Ļ����϶����ܸ���ǰ�����֮ǰ�ĺ�֮����޷��ϲ�
				//������ǰ��ĺϲ�����ô����Ļ���Ӧ���Ǵ��ϲ��������ڵ�ǰ����ǰ�棬��ʵ��sort���෴��
				//ͬ��������һ��
			}
		}
	}
	//����Ϊȥ��
	set< vector<int> > s;
	for (int i=0; i<result.size(); ++i)
	{
		s.insert(result[i]);
	}
	result.clear();
	result.assign(s.begin(), s.end());
	return result;
}

vector<vector<int>> generateMatrix(int n)  //�������� II
{
	if (n == 1)
	{
		return { {1} };
	}
	set< pair<int, int> > s;
	vector< vector<int> > result(n, vector<int>(n));
	int fangxiang = 0, i = 0, j = 0;
	int num = 1;
	int direction[][2] = { {0,1},{1,0},{0,-1},{-1,0} };  //��->��->��->��->�ҡ�������
	while(num <= n * n)
	{
		if (j < 0 || i < 0 || j >= n || i >= n)  //���������Χ���ͷ��ز�ѡ����һ������
		{
			i -= direction[fangxiang][0];
			j -= direction[fangxiang][1];
			fangxiang = (fangxiang >= 3 ? 0 : fangxiang + 1);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
			continue;
		}
		pair<int, int> p(i, j); 
		if (s.find(p) != s.end())  //�����ǰ�����Ѿ��ù�����ô��ת������
		{
			i -= direction[fangxiang][0];
			j -= direction[fangxiang][1];
			fangxiang = (fangxiang >= 3 ? 0 : fangxiang + 1);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
		}
		else
		{
			s.insert(p);
			result[i][j] = num;
			num++;
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
		}
	}
	return result;
}

string getPermutation_item(string s)  //��ȡ��һ����
{
	int x = 0, y = s.size() - 1;
	for (int i=s.size() - 1; i >= 0; --i)
	{
		if (s[i] > s[i - 1])
		{
			x = i - 1;
			break;
		}
	}
	for (int i=s.size() - 1; i >= 0; --i)
	{
		if (s[i] > s[x])
		{
			y = i;
			break;
		}
	}
	swap(s[x], s[y]);
	sort(s.begin() + x + 1, s.end());
	return s;
}
string getPermutation(int n, int k)  //��k������
{
	if (n == 1)
	{
		return "1";
	}
	string result;
	for (int i=1; i<=n; ++i)
	{
		result += std::to_string(i);
	}
	while (k > 1)
	{
		result = getPermutation_item(result);
		--k;
	}
	return result;
}

ListNode* rotateRight(ListNode* head, int k)  //��ת����
{
	if (!head || k == 0)
	{
		return head;
	}
	ListNode* tmp = head;
	ListNode* pre = nullptr;
	int n = 0;
	while (tmp)
	{
		++n;
		pre = tmp;
		tmp = tmp->next;
	}
	k = k % n;
	pre->next = head; //�����һ��Ԫ�ص���һ��ָ��ͷ
	int i = n - k;
	while (i > 1)  //��Ϊ�Ѿ��ɻ��ˣ���������Ҫ�ҵ�����ֵ��ǰһ��Ԫ��,������>1
	{
		head = head->next;
		--i;
	}
	tmp = head;  //�ݴ����ǰһ��Ԫ��
	head = head->next;  //��head��Ϊ�����ķ���ֵ
	tmp->next = nullptr;  //�����ǰһ��Ԫ�ص���һ��Ϊnull�������Ͳ��ǻ���
	return head;
}

int uniquePaths(int m, int n)  //��ͬ·��
{
	if (m == 0 || n == 0)
	{
		return 0;
	}
	else if (m == 1 || n == 1)
	{
		return 1;
	}
	vector< vector<int> > dp(m, vector<int>(n));  //��ij���������ٸ�·��
	for (int i=0; i<m; ++i)  //��0��ֻ��һ��·��
	{
		dp[i][0] = 1;
	}
	for (int j=0; j<n; ++j)  //��0��ֻ����һ��·��
	{
		dp[0][j] = 1;
	}
	for (int i=1; i<m; ++i)
	{
		for (int j=1; j<n; ++j)
		{
			//����ֻ�����Һ����£����ÿ�������·����ֻ�������һ�����ϱ�һ������
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)  //��ͬ·�� II--���ϰ���--��̬�滮
{
	if (obstacleGrid.size() == 0)
	{
		return 0;
	}
	vector< vector<long int> > dp(obstacleGrid.size(), vector<long int>(obstacleGrid[0].size(), 0));
	if (obstacleGrid[0][0] == 0)  //�����һ����Ϊ�ϰ�����Ϊ1������Ϊ0
	{
		dp[0][0] = 1;
	}
	for (int i=1; i<obstacleGrid.size(); ++i) 
	{
		//��0�У�������ϰ����λ����Ϊ0�������ֻ�����ϱ�һ����������������Ϊ0�������dp[i - 1][0]+0
		if (obstacleGrid[i][0] == 0)
		{
			dp[i][0] = dp[i - 1][0];
		}
	}
	for (int j=1; j<obstacleGrid.at(0).size(); ++j)
	{
		//��0�У�����ϰ�����Ϊ0�������ֻ�������һ�������ģ�����Ĺ���Ϊ0�������dp[0][j - 1]+0
		if (obstacleGrid[0][j] == 0)
		{
			dp[0][j] = dp[0][j - 1];
		}
	}
	for (int i=1; i<obstacleGrid.size(); ++i)
	{
		for (int j=1; j<obstacleGrid.at(i).size(); ++j)
		{
			if (obstacleGrid[i][j] == 0)  //��Ϊ�ϰ���Ļ����������+�ϲ����������
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
			else  //����ϰ�����Ϊ0
			{
				dp[i][j] = 0;
			}
		}
	}
	return dp[obstacleGrid.size() - 1][obstacleGrid.at(0).size() - 1];
}

int minPathSum(vector<vector<int>>& grid)  //��С·����--��̬�滮
{
	if (grid.size() == 0)
	{
		return 0;
	}
	int sum = 0;
	if(grid.at(0).size() == 1)
	{
		for (int i=0; i<grid.size(); ++i)
		{
			sum += grid[i][0];
		}
		return sum;
	}
	//dp��ʾ����ij����С��
	vector< vector<int> > dp(grid.size(), vector<int>(grid.at(0).size(), 0));
	dp[0][0] = grid[0][0];
	for (int i=1; i<grid.size(); ++i)
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];  //ֻ���ϲ���������û����Сһ˵��ֻ�����
	}
	for (int j=1; j<grid.at(0).size(); ++j)
	{
		dp[0][j] = dp[0][j - 1] + grid[0][j];  //ֻ�������������û����Сһ˵��ֻ�����
	}
	for (int i=1; i<grid.size(); ++i)
	{
		for (int j=1; j<grid.at(i).size(); ++j)
		{
			//ֻ���������ϲ��ƶ����������ȡ��С���Ǹ�
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[grid.size() - 1][grid.at(0).size() - 1];
}

string simplifyPath(string path)  //��·��
{
	stringstream is(path);   //��Ϊ������
	vector<string> strs;
	string res = "", tmp = "";
	while (getline(is, tmp, '/')) {  //���β���������ÿ���ַ�ֱ������/��Ȼ�����ѭ��ִ�н����������
		if (tmp == "" || tmp == ".")  //����
			continue;
		else if (tmp == ".." && !strs.empty())  //..�Ƿ�����һ�������Ҫ����������һ��ȥ��
			strs.pop_back();
		else if (tmp != "..")  //��ӽ�ȥ
			strs.push_back(tmp);
	}
	for (string str : strs)
		res += "/" + str;
	if (res.empty())
		return "/";
	return res;
}

void setZeroes(vector<vector<int>>& matrix)  //��������
{
	if (matrix.size() == 0)
	{
		return;
	}
	unordered_set<int> heng, shu;
	for (int i=0; i<matrix.size(); ++i)
	{
		for (int j=0; j<matrix.at(i).size(); ++j)
		{
			if (matrix[i][j] == 0)  //����0�ͼ�������к���
			{
				heng.insert(i);
				shu.insert(j);
			}
		}
	}
	for (int i=0; i<matrix.size(); ++i)
	{
		for (int j=0; j<matrix.at(i).size(); ++j)
		{
			if (heng.find(i) != heng.end() || shu.find(j) != shu.end())
			{
				matrix[i][j] = 0;
			}
		}
	}
}

bool searchMatrix(vector<vector<int>>& matrix, int target)  //������ά����
{
	if (matrix.size() == 0)
	{
		return false;
	}
	else if (matrix.at(0).size() == 0)
	{
		return false;
	}
	else if (target < matrix[0][0])
	{
		return false;
	}
	else if (target > matrix[matrix.size() - 1][matrix.at(0).size() - 1])
	{
		return false;
	}
	//����Ϊ������
	int n = matrix.size(), m = matrix.at(0).size(), hang = 0;
	for (int i=0; i<n; ++i)  //���ҵ��ڼ���
	{
		if (matrix[i][0] <= target && matrix[i][m - 1] >= target)
		{
			hang = i;
			break;
		}
	}
	vector<int> tmp = matrix[hang];
	int l = 0, r = m - 1;
	while (l <= r)  //���ֲ���
	{
		int mid = (r - l) / 2 + l;
		if (tmp[mid] == target)
		{
			return true;
		}
		else if (tmp[mid] < target)
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	--l;
	return tmp[l] == target ? true : false;
}

void sortColors(vector<int>& nums)  //��ɫ����
{
	if (nums.size() <= 1)
	{
		return;
	}
	int l = 0, r = nums.size() - 1, index = 0; //l��ʾԪ��0�����ڱ��߽磬r��ʾԪ��2�����ڱ��߽磬index��ʾ��ǰ��Ԫ��
	while (index <= r)
	{
		if (nums[index] == 0)  //�����ǰ���Ϊ0����ô�ͽ���0���ұ߽��ڱ������
		{
			swap(nums[index], nums[l]);
			//��Ϊl�ڱ��϶�С�ڵ���index��Ҳ����˵l�ڱ��Ѿ�ɨ����ˣ����Խ�����index��������0����1�����ֱ����������
			//����������Կ�����lָ���ֵ�϶���1����Ϊ�����0�Ļ�����ô��indexָ�����0��ʱ�򣬾��Ѿ�����һ��������.
			++index;
			++l;
		}
		else if (nums[index] == 2) //������֮��index��ֵ���ܻ�Ϊ2����˻���Ҫ�����жϵ�ǰֵ,����index����
		{
			swap(nums[index], nums[r]);
			--r;
		}
		else
		{
			index++;  //����1ֱ����������
		}
	}
}

vector< vector<int> > combine_v;
void combine_item(int n, int k, vector<int> v, int index)
{
	if (v.size() == k)
	{
		combine_v.push_back(v);
		return;
	}
	else if (v.size() > k)
	{
		return;
	}
	for (int i=index; i<=n; ++i)
	{
		v.push_back(i);
		combine_item(n, k, v, i+1);  //��һ�ξʹ�i+1��ʼ
		v.pop_back();  //���ù���ȥ��
	}
}
vector<vector<int>> combine(int n, int k)  //���
{
	if (k > n || k == 0 || n == 0)
	{
		return {};
	}
	combine_item(n, k, {}, 1);
	return combine_v;
}

vector< vector<int> > subsets_v;
void subsets_item(vector<int> &nums, int k, int index, vector<int> v)
{
	if (v.size() == k)
	{
		subsets_v.push_back(v);
		return;
	}
	else if(v.size() > k)
	{
		return;
	}
	for (int i=index; i<nums.size(); ++i)
	{
		v.push_back(nums[i]);
		subsets_item(nums, k, i + 1, v);  //��ǰλ�ü��Ϻ��ٴ���һ��λ�ÿ�ʼ
		v.pop_back();
	}
}
vector<vector<int>> subsets(vector<int>& nums)  //�Ӽ�
{
	if (nums.size() == 0)
	{
		return { {} };
	}
	sort(nums.begin(), nums.end());
	subsets_v.push_back({});
	for (int i=1; i<=nums.size(); ++i)
	{
		subsets_item(nums, i, 0, {});  //ÿ�δ��±�0��ʼ
	}
	return subsets_v;
}

int removeDuplicates(vector<int>& nums)  //ɾ�����������е��ظ��� II
{
	/*
	��ָ�룺�����������飻
	��ָ�룺��¼���Ը�д���ݵ�λ�ã�
	��Ŀ�й涨ÿ��Ԫ�����������Σ�
	��ˣ�Ӧ����ָ��ָ���Ԫ�غ���ָ��ָ����ָ��Ԫ��ǰһ��Ԫ���Ƿ���ȡ�
	����򲻸�����ָ�룬ֻ���¿�ָ�룻
	�����ʱ���Ƚ���ָ�����һλ���ٽ���ָ��ָ���Ԫ�ظ�д����ָ��ָ��ĵ�Ԫ�������¿�ָ��
	*/
	if (nums.size() <= 2)
	{
		return nums.size();
	}
	int slow = 1, fast = 2;
	while (fast < nums.size())
	{
		if (nums[slow - 1] != nums[fast])
		{
			++slow;
			nums[slow] = nums[fast];
		}
		++fast;
	}
	return slow + 1;
}

bool search_1(vector<int>& nums, int target)  //������ת�������� II--һ��������Ȼ����
{
	if (nums.size() == 0)
	{
		return false;
	}
	for (int num : nums)
	{
		if (num == target)
		{
			return true;
		}
	}
	return false;
}

bool search_2(vector<int>& nums, int target)  //������ת�������� II--���ֲ���
{
	if (nums.size() == 0)
	{
		return false;
	}
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[mid] == target)
		{
			return true;
		}
		if (nums[l] == nums[mid])
		{
			++l;
			continue;
		}
		if (nums[l] < nums[mid])   //��l��midΪ����
		{
			if (target > nums[mid] || nums[l] > target)  //��������ⲿ�����䣬��ôֱ������
			{
				l = mid + 1;
			}
			else
			{
				r = mid - 1;
			}
		}
		else  //��벿������
		{
			if (target > nums[r] || target < nums[mid])  //��������ⲿ�����䣬ֱ������
			{
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
	}
	if (l == 0)
	{
		return nums[l] == target ? true : false;
	}
	--l;
	return nums[l] == target ? true : false;
}

ListNode* deleteDuplicates(ListNode* head) //ɾ�����������е��ظ�Ԫ�� II
{
	if (!head || !head->next)
	{
		return head;
	}
	//����ͷ
	if (head->val != head->next->val)  //�����ͷָ��ֵ��ڶ�����ͬ����ôͷָ����Ƿ���ֵ�ĵ�һ��Ԫ��
	{
		head = head;
	}
	else  //�����һ����ڶ���һ������ô����ָ�룬pre��now��head����next(n)
	{
		ListNode *pre = head;
		head = head->next;
		ListNode* n = head->next;
		//ֻҪ����pre->val = now->val ����now->val = n->val����˵����ǰ���now����Ψһ�ģ���˲��ܵ�ͷԪ��
		while ( pre && head && n && (pre->val == head->val || head->val == n->val))
		{
			pre = pre->next;
			head = head->next;
			n = n->next;
		}
		if (!n)  //�����ʱn����nullԪ���ˣ�Ҳ����˵֮ǰ��Ԫ�ز�����Ψһ����ʱhead�������һ��Ԫ��
		{
			if (head->val != pre->val)  //������һ��������ǰһ������ô��ʱֻ�����һ��Ԫ������Ҫ�����ֱ�ӷ���
			{
				return head;
			}
			else  //�����ȵĻ���˵�����һ��Ԫ���뵹���ڶ���Ԫ����ȣ���˴�ʱû�������Ԫ�أ�ֱ�ӷ���
			{
				return nullptr;
			}
		}
	}
	ListNode* tmp = head;  //ͷԪ��
	ListNode* result = tmp;  //���ؽ��
	ListNode* x = head;  //�൱��pre
	head = head->next;  //�൱��now
	ListNode* y = head->next;  //�൱��next
	while (x && head && y)
	{
		if (x->val != head->val && head->val != y->val)  //���һ��ֵ����Ψһ����ô�ͽ��뵽�����
		{
			tmp->next = head;
			tmp = tmp->next;
		}
		//����ƶ�
		x = x->next;
		head = head->next;
		y = y->next;
	}
	//�˳�whileʱ�����һ��Ԫ�ػ�δ�ж�
	if (head->val != x->val)  //���һ��Ԫ�ز����ڵ����ڶ�������ô���һ���϶�Ҫ����
	{
		tmp->next = head;
		tmp = tmp->next;
		tmp->next = nullptr;
	}
	else  //������һ�����ڵ����ڶ�������ôֱ�Ӳ�Ҫ�ˣ�ֱ�ӵ���null
	{
		tmp->next = nullptr;
	}
	return result;
}

ListNode* partition(ListNode* head, int x)  //�ָ�����
{
	if (!head)
	{
		return head;
	}
	//��ʼ����t1��ʾС��x�ģ�t2��ʾ���ڵ���x��
	ListNode* t1 = new ListNode(x);
	ListNode* t2 = new ListNode(x);
	ListNode* t = t2;
	ListNode* result = t1;
	while (head)
	{
		if (head->val < x)
		{
			t1->next = head;
			t1 = t1->next;
		}
		else
		{
			t2->next = head;
			t2 = t2->next;
		}
		head = head->next;
	}
	t2->next = nullptr;  //���Ļ�t2�ĺ���Ӧ����Ϊnullptr
	t = t->next;  //������ʼ�����Ǹ�
	t1->next = t; //��t1�ĺ������t
	return result->next;  //������ʼ���Ǹ���Ȼ�󷵻�
}

vector<int> grayCode(int n)  //���ױ���
{
	if (n == 0)
	{
		return { 0 };
	}
	else if (n >= 25)
	{
		return {};
	}
	//��֪n-1�ı��룬��ôn�ı��룬���Ƕ�n-1�ı��뵹�������ÿ��Ԫ�صĶ������ں�������1(Ҳ���ǳ�2��1)��push_back,���Ұѵ�ǰ����������������ƺ���ֱ����0(Ҳ���ǳ�2)����ԭֵ
	vector<int> result;
	result.push_back(0);
	for (int i=1; i<=n; ++i)
	{
		int n = result.size();
		for (int j = n - 1; j >= 0; --j)
		{
			int tmp = result[j];
			result.push_back(tmp * 2 + 1);
			result[j] = tmp * 2;
		}
	}
	return result;
}

set< vector<int> > subsetsWithDup_s;
void subsetsWithDup_item(vector<int>& nums, int k, int index, vector<int> v)
{
	if (v.size() == k)
	{
		subsetsWithDup_s.insert(v);
		return;
	}
	else if (v.size() > k)
	{
		return;
	}
	for (int i=index; i<nums.size(); ++i)
	{
		v.push_back(nums[i]);  //��ӵ�ǰԪ��
		subsetsWithDup_item(nums, k, i + 1, v);  //����һ��Ԫ�ؿ�ʼ
		v.pop_back();
	}
}
vector<vector<int>> subsetsWithDup(vector<int>& nums)  //�Ӽ� II
{
	if (nums.size() == 0)
	{
		return { {} };
	}
	sort(nums.begin(), nums.end());
	for (int i=1; i<=nums.size(); ++i)  //��������������
	{
		subsetsWithDup_item(nums, i, 0, {});
	}
	vector< vector<int> > result;
	result.assign(subsetsWithDup_s.begin(), subsetsWithDup_s.end());
	return result;
}

int numDecodings(string s)  //���뷽��--��̬�滮
{
	if (s.size() == 0)
	{
		return 0;
	}
	if (s[0] == '0')
	{
		return 0;
	}
	if (s.size() == 1)
	{
		return 1;
	}
	vector<int> dp(s.size(), 0);  //�������±�Ϊi���ַ��õ�������
	dp[0] = 1;
	//����dp[1]��ʱ��
	if (s[1] == '0') //���ڶ����ַ�Ϊ0��ʱ��ֻ�ܸ�ǰһ���ַ�����һ��
	{
		if (s[0] == '1' || s[0] == '2')  //���ǰһ���ַ�Ϊ1��2����ôֻ����10��20��ֻ��һ���������û��,�����ַ�����û�У�ֱ�ӷ���
		{
			dp[1] = 1;
		}
		else 
		{
			dp[1] = 0;
			return 0;
		}
	}
	else //���s[1]��Ϊ0
	{
		if (s[0] == '1' || (s[0] == '2' && s[1] >= '1' && s[1] <= '6'))
		{
			dp[1] = 2;
		}
		else
		{
			dp[1] = 1;
		}
	}
	for (int i=2; i<s.size(); ++i)
	{
		//�±��i��Ϊ0����ôֻ����ǰһ���ϲ���������
		//���ǰһ��1��2����ô��ǰi-2����������ϣ���ֱ���ں�����Ϻϲ���������
		//����Ϊ0
		if (s[i] == '0')  
		{
			if (s[i - 1] == '1' || s[i - 1] == '2')
			{
				dp[i] = dp[i - 2];
			}
			else
			{
				return 0;
			}
		}
		else  //�����Ϊ0�Ļ�
		{
			if (s[i - 1] == '1')
			{
				//��ô�����±�ǰi-1����Ϻ��ں�������±��i����
				//���ߺ�����������������±�ǰi-2����Ϻ���ں���
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			else if(s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6')
			{
				//ͬ�������s[i-1] = '1'
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			else
			{
				//�����Ļ���ֻ�ܰ��±��i���������������±�ǰi-1������Ϻ󣬼��ں���
				dp[i] = dp[i - 1];
			}
		}
	}
	return dp[s.size() - 1];
}

ListNode* reverseBetween(ListNode* head, int m, int n)  //��ת���� II
{
	if (!head || m == n)
	{
		return head;
	}
	ListNode* t1 = new ListNode(0); //������ʾ��ת����
	ListNode* result = head;
	ListNode* t2 = head;   //��ʾ��ת���ֵ�ǰһ��
	int flag = m;  //����m��ֵ
	while (m > 1)  //һֱ����ת���ֵĵ�һ������
	{
		if (m == 2)
		{
			t2 = head;  //��¼��ת���ֵ�ǰһ��
		}
		head = head->next;
		--m;
		--n;
	}
	ListNode* t = head;  //��¼��ת���ֵĵ�һ����Ҳ���Ƿ�ת������һ��
	while (n > 0)
	{
		ListNode* tmp = head;  //���浱ǰԪ��
		head = head->next;  //ָ����һ��
		tmp->next = t1;  //����ǰԪ�ص���һ��ָ��ǰ���Ǹ���Ҳ���Ƿ�ת����
		t1 = tmp;  //����ָ��ת���ǰһ��Ԫ�أ��Ա㵱��������head�ĺ�һ��Ԫ�أ�Ҳ���Ƿ�ת
		--n;
	}
	t->next = head;  //��ת������һ������һ��Ҫָ�򾭹���ת����ĵ�һ��
	if (flag == 1)
	{
		return t1;  //���Ҫ��ת�İ�����һ������ôֱ�ӷ��ط�ת��ķ�ת����һ��
	}
	else
	{
		t2->next = t1;  //���򣬾ͽ���ת����ǰһ������һ��ָ��ת��ĵ�һ��
	}
	return result;  //���ؽ��
}

vector<string> restoreIpAddresses_v;
void restoreIpAddresses_item(int n, string s, string ip)
{
	if (n == 4)  //����õ���4��. 
	{
		if (s.size() == 0)  //��������string�����ˣ���ô����
		{
			restoreIpAddresses_v.push_back(ip);
		}
		return;
	}
	else if (n > 4)
	{
		return;
	}
	for (int i=1; i<4; ++i)  //������֮�������1-3��
	{
		if (s.size() < i)  //���ʣ���ַ����ĸ��������Լ��뵽ip�ַ����У���ôֱ��break
		{
			break;
		}
		int val = std::stoi(s.substr(0, i));  //��ʣ���ַ����д��±�0��ʼ��ȡi����ת��Ϊint
		if (val > 255 || i != std::to_string(val).size())  //�����ȡ�Ĵ���255�����߽�ȡ���ַ������������ڵ�ǰ��Ҫ�ĸ�����������һ��
		{
			continue;
		}
		//�ݹ飬�õ��˵�n+1���㣬ʣ���ַ���Ϊ���±��i�����(��Ϊ��0-i����)��ip���ϴ�0��i���ַ������n=3��˵������3���ˣ���˲��ӵ��ˣ�����ͼ�
		restoreIpAddresses_item(n + 1, s.substr(i), ip + s.substr(0, i) + (n == 3 ? "" : "."));
	}
}
vector<string> restoreIpAddresses(string s)  //��ԭIP��ַ
{
	if (s.size() < 4 || s.size() > 12)
	{
		return {};
	}
	restoreIpAddresses_item(0, s, "");
	return restoreIpAddresses_v;
}


void inorderTraversal_item(TreeNode* root, vector<int> &result)
{
	if (!root)
	{
		return;
	}
	if (root->left)
	{
		inorderTraversal_item(root->left, result);
	}
	result.push_back(root->val);
	if (root->right)
	{
		inorderTraversal_item(root->right, result);
	}
}
vector<int> inorderTraversal_1(TreeNode* root)  //���������������--�ݹ�
{
	if (!root)
	{
		return {};
	}
	vector<int> result;
	inorderTraversal_item(root, result);
	return result;
}

void inorderTraversal_goAlongLeft(TreeNode* root, stack<TreeNode*> &s)
{
	while (root)
	{
		s.push(root);
		root = root->left;
	}
}
vector<int> inorderTraversal_2(TreeNode* root)  //���������������--����
{
	if (!root)
	{
		return {};
	}
	stack<TreeNode*> s;
	vector<int> result;
	while (true)
	{
		inorderTraversal_goAlongLeft(root, s);
		if (s.empty())
		{
			break;
		}
		root = s.top();
		s.pop();
		result.push_back(root->val);
		root = root->right;
	}
	return result;
}

vector<TreeNode*> generateTrees_item(int zuixiao, int zuida)
{
	vector<TreeNode*> result;
	if (zuixiao > zuida)
	{
		result.push_back(nullptr);
		return result;
	}
	for (int i=zuixiao; i<=zuida; ++i)
	{
		vector<TreeNode*> lTrees = generateTrees_item(zuixiao, i - 1);  //��������������������
		vector<TreeNode*> rTrees = generateTrees_item(i + 1, zuida);  //��������������������
		for (TreeNode* l : lTrees)
		{
			for (TreeNode* r : rTrees)
			{
				TreeNode* root = new TreeNode(i);  //�������������������lTrees���棬��Ϊ������Ǹ����棬���൱�ڶ�ͬһ��root�����޸����������������pushback��ֻ���޸ĵ�����һ��,���������Ҫÿ���½�
				root->left = l;
				root->right = r;
				result.push_back(root);
			}
		}
	}
	return result;
}
vector<TreeNode*> generateTrees(int n)  //��ͬ�Ķ��������� II
{
	if (n < 1)
	{
		return {};
	}
	if (n == 1)
	{
		TreeNode* result = new TreeNode(1);
		return { result };
	}
	return generateTrees_item(1, n);
}

int numTrees_item(int zuixiao, int zuida)
{
	if (zuixiao > zuida)
	{
		return 1;
	}
	int sum = 0;
	for (int i=zuixiao; i<=zuida; ++i)
	{
		int lsum = numTrees_item(zuixiao, i - 1);
		int rsum = numTrees_item(i + 1, zuida);
		sum += (lsum * rsum);
	}
	return sum;
}
int numTrees_1(int n)  //��ͬ�Ķ���������--�ݹ鳬ʱ��
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	return numTrees_item(1, n);
}

int numTrees_2(int n)  //��ͬ�Ķ���������--��̬�滮
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	//�������г���Ϊi�ĸ�����result[i],��Ϊ�ǳ���Ϊi������4567���Ҳ��result[4],1234Ҳ��result[4]
	//��iΪ���Ļ�����������[1, i-1]�ĸ�����[i+1, n]�ĸ����ĳ˻�
	//��ô������i��1��n�ĸ�����Ӿ��ǽ��
	vector<int> result(n + 1, 0);
	result[0] = 1;
	result[1] = 1;
	for (int i=2; i<=n; ++i)  //��������Ϊ2-n
	{
		//��i����ʱ����jΪ���ĸ���Ϊresult[j - 1] * result[i - j],�Ѵ�1��i�����е��������ۼӾ���i����ʱ�Ľ��
		for (int j=1; j<=i; ++j)  //��1��i����Ϊ��
		{
			result[i] += result[j - 1] * result[i - j];
		}
	}
	return result[n];
}

int numTrees_3(int n)  //��ͬ�Ķ���������--��������
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	long int result = 1;
	for (int i=1; i<=n; ++i)
	{
		result = 2 * (2 * i - 1) * result / (i + 1);
	}
	return result;
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root)  //�������ľ���β�α���
{
	if (!root)
	{
		return {};
	}
	vector< vector<int> > result;
	bool flag = false;  //��ǰ���Ƿ��Ǵ��ұ������ߵ�
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())  //�������ǲ�α��������Ҫ������while
	{
		vector<int> tmp;
		int i = q.size();  //��ǰ��Ԫ�ظ���
		flag = !flag;  //��ǰ������һ���෴
		stack<TreeNode*> s;  //��¼��һ���˳��
		while (i > 0)
		{
			root = q.front();
			q.pop();
			tmp.push_back(root->val);
			//����һ�㰴��˳����ӽ�stack��
			if (flag)  //�˲���������ߣ����Զ���stackҪ�������ߵ�
			{
				if (root->left)
				{
					s.push(root->left);
				}
				if (root->right)
				{
					s.push(root->right);
				}
			}
			else  //���������������
			{
				if (root->right)
				{
					s.push(root->right);
				}
				if (root->left)
				{
					s.push(root->left);
				}
			}
			--i;
		}
		while (!s.empty())  //����һ��ļ����queue�У������stack�Ѿ���֤����ȷ��˳��
		{
			q.push(s.top());
			s.pop();
		}
		result.push_back(tmp);
	}
	return result;
}

TreeNode* buildTree_item(vector<int> preorder, vector<int> inorder)
{
	//ǰ������ĵ�һ���ǵ�ǰ���ĸ��ڵ㣬
	//�˸��ڵ������������λ�õ����Ϊ���������Ҳ�Ϊ������
	//������ѭ���ݹ���ȥ�Ϳ���
	if (preorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(preorder[0]);  //��ǰ���ڵ�Ϊǰ������ĵ�һ��
	vector<int>::iterator ifind = find(inorder.begin(), inorder.end(), preorder[0]);  //�����������Ѱ�Ҹ��ڵ�Ԫ��
	if (ifind == inorder.end())  //���û�У���˵�����ܳ�Ϊ������
	{
		return nullptr;
	}
	vector<int> inorder_left;  //�������������������
	inorder_left.assign(inorder.begin(), ifind);  //Ӧ�����������еĵ�һ�������ڵ��ǰһ��
	vector<int> inorder_right;  //�������������������
	inorder_right.assign(++ifind, inorder.end()); //Ӧ�����������еĸ��ڵ��һ�������
	vector<int> preorder_left;  //�������������������
	vector<int> preorder_right;  //�������������������
	//��Ȼ�������������(��)�������ֵĸ������������������(��)�������ֵĸ����ֱ���ͬ��
	//��inorder_left.size = preorder_left.size, inorder_right.size = preorder_right.size
	//��Ϊ���Ƕ��Ǵ�ʱ���ڵ����(��)����������Ԫ�أ�
	//��������������У���һ��Ϊ��Ԫ�أ�Ȼ����������������Ԫ�أ�Ȼ����������������Ԫ��
	//��ôҲ����˵������������еĸ��ڵ�����һ�������ó�inorder_left.size()������Ԫ�أ�
	//����preorder_left��Ԫ�أ�ͬ��ʣ�µ�Ϊpreorder_right��Ԫ��
	preorder_left.assign(preorder.begin() + 1, preorder.begin() + 1 + inorder_left.size());
	preorder_right.assign(preorder.begin() + 1 + inorder_left.size(), preorder.end());
	TreeNode* l = buildTree_item(preorder_left, inorder_left);
	TreeNode* r = buildTree_item(preorder_right, inorder_right);
	root->left = l;
	root->right = r;
	return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)  //��ǰ��������������й��������
{
	if (preorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	if (preorder.size() == 1 || inorder.size() == 1)
	{
		TreeNode* root = new TreeNode(preorder[0]);
		return root;
	}
	return buildTree_item(preorder, inorder);
}

TreeNode* buildTree_item(vector<int> inorder, vector<int> postorder)
{
	if (inorder.size() == 0 || postorder.size() == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(postorder[postorder.size() - 1]); //����������һ��Ԫ��Ϊ��ǰ�ĸ�Ԫ��
	vector<int>::iterator ifind = find(inorder.begin(), inorder.end(), postorder[postorder.size() - 1]);
	vector<int> inorder_left;
	vector<int> inorder_right;
	inorder_left.assign(inorder.begin(), ifind);  //�������и�Ԫ�����Ϊ������
	inorder_right.assign(++ifind, inorder.end());  //�������еĸ�Ԫ���Ҳ�Ϊ������
	vector<int> postorder_left;
	vector<int> postorder_right;
	//����������У�ǰinorder_left.size()��Ԫ��Ϊ������Ԫ�أ�����ĳ�ȥ���һ��ʣ�µ�Ϊ������Ԫ��
	postorder_left.assign(postorder.begin(), postorder.begin() + inorder_left.size());
	postorder_right.assign(postorder.begin() + inorder_left.size(), postorder.end() - 1);
	TreeNode* l = buildTree_item(inorder_left, postorder_left);
	TreeNode* r = buildTree_item(inorder_right, postorder_right);
	root->left = l;
	root->right = r;
	return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)  //�����������������й��������
{
	if (postorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	if (postorder.size() == 1 || inorder.size() == 1)
	{
		TreeNode* root = new TreeNode(postorder[0]);
		return root;
	}
	return buildTree_item(inorder, postorder);
}

TreeNode* sortedListToBST_item(vector<int> tmp)
{
	//�����б��е��м�Ԫ�ؽ�����Ϊ�����������ĸ���
	//�õ���������Ԫ�صݹ��ȥ������������
	//ͬ���Ҳ��Ԫ�ع��������������Ȼ�ܹ���֤�������Ķ�����������ƽ���
	if (tmp.size() == 0)
	{
		return nullptr;
	}
	int n = tmp.size();
	n /= 2;
	TreeNode* root = new TreeNode(tmp[n]);
	vector<int> tmp_l, tmp_r;
	tmp_l.assign(tmp.begin(), tmp.begin() + n);
	tmp_r.assign(tmp.begin() + n + 1, tmp.end());
	TreeNode* l = sortedListToBST_item(tmp_l);
	TreeNode* r = sortedListToBST_item(tmp_r);
	root->left = l;
	root->right = r;
	return root;
}
TreeNode* sortedListToBST(ListNode* head)  //��������ת������������
{
	if (!head)
	{
		return nullptr;
	}
	vector<int> tmp;
	while (head)
	{
		tmp.push_back(head->val);
		head = head->next;
	}
	return sortedListToBST_item(tmp);
}

vector< vector<int> > pathSum_v;
void pathSum_item(TreeNode* root, int target, vector<int> tmp)
{
	if (!root)  //Ϊ�գ���϶�����Ҷ�ӽڵ�
	{
		return;
	}
	tmp.push_back(root->val);
	if (target == root->val && !root->left && !root->right)  //target��ֵ���ڵ�ǰ�ڵ�ֵ����ΪҶ�ӽڵ�
	{
		pathSum_v.push_back(tmp);  //��ô�ͼ�����
		return;
	}
	pathSum_item(root->left, target - root->val, tmp); //�ݹ����������
	pathSum_item(root->right, target - root->val, tmp);  //�ݹ����������
}
vector<vector<int>> pathSum(TreeNode* root, int sum)  //·���ܺ� II
{
	if (!root)
	{
		return {};
	}
	pathSum_item(root, sum, {});
	return pathSum_v;
}

void flatten(TreeNode* root)  //������չ��Ϊ����--�������
{
	if (!root)
	{
		return;
	}
	stack<TreeNode*> s;
	TreeNode* tmp = new TreeNode(0);
	TreeNode* result = tmp;
	s.push(root);
	while (!s.empty())  //���������Ȼ����˳�����һ����������ָ������������
	{
		root = s.top();
		s.pop();
		tmp->left = nullptr;
		tmp->right = root;
		tmp = root;
		if (root->right)
		{
			s.push(root->right);
		}
		if (root->left)
		{
			s.push(root->left);
		}
	}
	root = result->right;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};
Node* connect(Node* root)  //���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
{
	//���ݾ��״����ѽ��
	if (!root)
	{
		return nullptr;
	}
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		int i = q.size();
		if (i == 1)  //���ڵ�ʱ��
		{
			root = q.front();
			q.pop();
			root->next = nullptr;
			if (root->left)
			{
				q.push(root->left);
			}
			if (root->right)
			{
				q.push(root->right);
			}
			continue;
		}
		//�Ǹ��ڵ�
		Node* t1 = q.front();  //���ó���һ����Ϊ��ָ��  
		q.pop();
		--i;  //��ȥ����
		if (t1->left)  //��������ָ��
		{
			q.push(t1->left);
		}
		if (t1->right)
		{
			q.push(t1->right);
		}
		while (i > 0) //����i>1����������϶��ܽ���
		{
			Node* t2 = q.front();  //��ǰָ��
			q.pop();
			if (t2->left)  //����������ָ��
			{
				q.push(t2->left);
			}
			if (t2->right)
			{
				q.push(t2->right);
			} 
			t1->next = t2;  //��ָ�����һ��ָ��ǰָ��
			t1 = t2;  //������ָ��Ϊ��ǰָ�룬�ȴ���һ��ʹ��
			--i;  //������
		}
		t1->next = nullptr;  //���һ��ָ�����һ��ָ��nullptr
	}
	return root;  //��Ϊ���������������������rootֻ��i=1ʱ�õģ�����root��Զָ����ڵ�
}

Node* connect(Node* root)  //���ÿ���ڵ����һ���Ҳ�ڵ�ָ�� II
{
	if (!root)
	{
		return nullptr;
	}
	queue<Node*> q;
	Node* result = root;
	q.push(root);
	while (!q.empty())
	{
		int i = q.size();
		if (i == 1)  //���ڵ�ʱ��
		{
			root = q.front();
			q.pop();
			root->next = nullptr;
			if (root->left)
			{
				q.push(root->left);
			}
			if (root->right)
			{
				q.push(root->right);
			}
			continue;
		}
		//�Ǹ��ڵ�
		Node* t1 = q.front();  //���ó���һ����Ϊ��ָ��  
		q.pop();
		--i;  //��ȥ����
		if (t1->left)  //��������ָ��
		{
			q.push(t1->left);
		}
		if (t1->right)
		{
			q.push(t1->right);
		}
		while (i > 0) //����i>1����������϶��ܽ���
		{
			Node* t2 = q.front();  //��ǰָ��
			q.pop();
			if (t2->left)  //����������ָ��
			{
				q.push(t2->left);
			}
			if (t2->right)
			{
				q.push(t2->right);
			}
			t1->next = t2;  //��ָ�����һ��ָ��ǰָ��
			t1 = t2;  //������ָ��Ϊ��ǰָ�룬�ȴ���һ��ʹ��
			--i;  //������
		}
		t1->next = nullptr;  //���һ��ָ�����һ��ָ��nullptr
	}
	//��Ϊ���ⲻ�����������������ܳ���ֻ��һ�����ӵ������
	//����root�ᱻʹ�úܶ�Σ����Ի�䣬���Ե���result����տ�ʼ��root
	return result;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList)  //���ʽ���
{
	if (wordList.size() == 0)
	{
		return 0;
	}
	if (beginWord == endWord)
	{
		return 1;
	}
	bool flag = true;
	map<string, vector<string>> m;
	for (string s : wordList)  //�����ڽӱ�
	{
		if (s == endWord)
		{
			flag = false;
		}
		for (int i=0; i<s.size(); ++i)
		{
			string tmp = s;
			tmp[i] = '*';
			m[tmp].push_back(s);
		}
	}
	if (flag)  //���worlist����û��endword����ô����0
	{
		return 0;
	}
	queue< pair<string, int> > q;
	map<string, bool> visited;
	q.push(pair<string, int>(beginWord, 1));
	int n = beginWord.size();
	while (!q.empty())  //�����������
	{
		string currentString = q.front().first;
		int currentLevel = q.front().second;
		q.pop();
		for (int i=0; i<n; ++i)
		{
			string newWord = currentString;
			newWord[i] = '*';
			map<string, vector<string>>::iterator ifind = m.find(newWord);
			if (ifind != m.end())
			{
				vector<string> tmp = ifind->second;
				for (auto s : tmp)
				{
					if (s == endWord)
					{
						return currentLevel + 1;
					}
					map<string, bool>::iterator vfind = visited.find(s);
					if (vfind == visited.end() || !vfind->second)
					{
						visited[s] = true;
						q.push(pair<string, int>(s, currentLevel + 1));
					}
				}
			}
		}
	}
	return 0;
}

void sumNumbers_item(TreeNode* root, int sum, vector<int> &tmp)
{
	if (!root)
	{
		return;
	}
	if (!root->left && !root->right)  //�����Ҷ�ӽڵ㣬��ô�ͼ����ȥ������·���ͽ�����
	{
		sum = sum * 10 + root->val;
		tmp.push_back(sum);
		return;
	}
	sum = sum * 10 + root->val;
	if (root->left)
	{
		sumNumbers_item(root->left, sum, tmp);  //��������·��
	}
	if (root->right)
	{
		sumNumbers_item(root->right, sum, tmp);  //��������·��
	}
}
int sumNumbers(TreeNode* root)  //�����Ҷ�ӽڵ�����֮��
{
	if (!root)
	{
		return 0;
	}
	vector<int> tmp;
	sumNumbers_item(root, 0, tmp);
	long int result = 0;
	for (int i : tmp)
	{
		result += i;
	}
	return result;
}

void solve(vector<vector<char>>& board)  //��Χ�Ƶ�����
{
	if (board.size() == 0 || board[0].size() == 0)
	{
		return;
	}
	int n = board.size(), m = board[0].size();
	vector<int> parent(n * m, -1);
	set<int> s;  //��¼O�����ڱ�Ե������
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<m; ++j)
		{
			if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && board[i][j] == 'O')
			{
				s.insert(i * m + j);  //��������
			}
			parent[i * m + j] = i * m + j;
		}
	}
	int direction[][2] = { {1,0}, {0,1}, {-1,0},{0,-1} };
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<m; ++j)
		{
			if (board[i][j] == 'X')
			{
				continue;
			}
			int rootx = parent[i * m + j]; 
			while (rootx != parent[rootx])  //��ǰOλ�õ��ϴ�
			{
				rootx = parent[rootx];
			}
			for (int k=0; k<4; ++k)  //�ĸ��������
			{
				int x = i + direction[k][0], y = j + direction[k][1];
				if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 'O')
				{
					int rooty = parent[x * m + y];
					while (rooty != parent[rooty])
					{
						rooty = parent[rooty];
					}
					if (rootx != rooty)  //����ϴ�ͬ
					{
						if (s.find(rooty) == s.end())  //���rooty������O�ұ�Ե�ģ���ôӦ���������ϴ�
						{
							parent[rooty] = rootx;
						}
						else  //�������rootx�ϴ�
						{
							parent[rootx] = rooty;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (board[i][j] == 'X')
			{
				continue;
			}
			int root = parent[i * m + j];
			while (root != parent[root])   //Ѱ�ҵ�ǰ�ϴ�
			{
				root = parent[root];
			}
			if (s.find(root) == s.end())  //����ϴ���s����
			{
				board[i][j] = 'X';
			}
		}
	}
}

vector< vector<string> > partition_v;
bool isHuiWenChuan(string s)  //�ж��Ƿ��ǻ��Ĵ�
{
	if (s.size() == 1)
	{
		return true;
	}
	int i = 0, j = s.size() - 1;
	while (i < j)
	{
		if (s[i] != s[j])
		{
			return false;
		}
		++i;
		--j;
	}
	return true;
}
void partition_item(string s, vector<string> tmp)
{
	if (s.size() == 0)  //���ʣ�µ�sizeΪ0����ô�ͼ���
	{
		if (tmp.size() > 0)
		{
			partition_v.push_back(tmp);
		}
		return;
	}
	for (int i=1; i<=s.size(); ++i)  //��s�зָ��i�����ȵ��ַ���
	{
		string newString = s.substr(0, i);
		if (isHuiWenChuan(newString))   //����ǻ��Ĵ�����˵���˴ηָ���Ч����ô����ʣ���ַ����ķָ����ͼ�֦
		{
			tmp.push_back(newString);
			partition_item(s.substr(i), tmp);
			tmp.pop_back();  //��ǰ��ָ��ȥ���������ָ�i+1������
		}
	}
}
vector<vector<string>> partition(string s)  //�ָ���Ĵ�
{
	if (s.size() == 0)
	{
		return {};
	}
	if (s.size() == 1)
	{
		return { {s} };
	}
	partition_item(s, {});
	return partition_v;
}

class Node {
public:
	int val;
	vector<Node*> neighbors;

	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}

	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}

	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};
map<Node*, Node*> cloneGraph_m;
Node* cloneGraph(Node* node)  //��¡ͼ
{
	if (!node)
	{
		return nullptr;
	}
	if (cloneGraph_m.count(node)) //����Ѿ����������¡�ˣ�ֱ�ӷ���
	{
		return cloneGraph_m[node];
	}
	Node* result = new Node(node->val);
	cloneGraph_m[node] = result;
	for (Node* nei : node->neighbors)
	{
		if (nei)
		{
			Node* tmp = cloneGraph(nei); //����ÿ���ھӵĿ�¡
			result->neighbors.push_back(tmp);
		}
	}
	return result;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost)  //����վ
{
	if (gas.size() == 0 || cost.size() == 0)
	{
		return -1;
	}
	if (gas.size() != cost.size())
	{
		return -1;
	}
	vector<int> dp(gas.size(), 0); //��ʾi������i+1(����i+1����)�͵�ʵ�ʻ����
	for (int i = 0; i < gas.size(); ++i)
	{
		dp[i] = gas[i] - cost[i];
	}
	bool flag = true; //�Ƿ��гɹ���
	int result = -1;
	for (int i = 0; i < dp.size(); ++i)
	{
		if (dp[i] >= 0)  //�տ�ʼ�����ı���Ҫ�ܵ����i+1վ�����Ҫ���ڵ���0
		{
			flag = true;
			int sum = 0;
			for (int j = i; j < dp.size(); ++j)
			{
				sum += dp[j];
				if (sum < 0)
				{
					flag = false;
					break;
				}
			}
			if (!flag)  //��i�����һ��������Ҫ���
			{
				continue;
			}
			for (int j = 0; j < i; ++j)
			{
				sum += dp[j];
				if (sum < 0)
				{
					flag = false;
					break;
				}
			}
			if (flag)  //��0��iҲ������Ҫ��ģ���������ģ��������ѭ��������Ҫ���
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

int singleNumber(vector<int>& nums)
{
	unordered_set<int> s;
	long int sum = 0;
	for (int i: nums)
	{
		sum += i;
		s.insert(i);
	}
	long int tmp = 0;
	for (unordered_set<int>::iterator ii = s.begin(); ii != s.end(); ii++)
	{
		tmp += (*ii);
	}
	return (tmp * 3 - sum) / 2;
}

class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
map<Node*, Node*> copyRandomList_m;  //ָ���뿽��һһ��Ӧ
Node* copyRandomList(Node* head)  //���ƴ����ָ�������
{
	if (!head)  //���null����ô����null
	{
		return nullptr;
	
	}
	if (copyRandomList_m.count(head))  //��������ˣ���ֱ�ӷ��ؿ���
	{
		return copyRandomList_m[head];
	}
	Node* result = new Node(head->val);  //��������
	copyRandomList_m[head] = result;  //����һһ��Ӧ��ϵ
	Node* n = copyRandomList(head->next);  //�ݹ������һ��
	Node* r = copyRandomList(head->random);  //�ݹ�������ָ��
	result->next = n;  //��ֵ
	result->random = r; //��ֵ
	return result;  //���ؽ��
}

bool wordBreak_item(string s, vector<string>& wordDict)
{
	if (s.size() == 0)
	{
		return true;
	}
	bool flag = false;
	for (string word : wordDict)   //�������ʱ�
	{
		if (s.size() < word.size())  //���s�ĳ���С��˵����ʱ�ĵ��ʿ϶�����
		{
			continue;
		}
		string tmp = s;  //ÿ��ѭ������Ҫ��������s�����Ե��ݴ�,������һ������ʱ����ǽ�ȡ�˵��ַ�����
		string newString = tmp.substr(0, word.size());  //��tmp��ȡ��wordһ�������ַ���
		if (newString == word)  //�����ȼ��������������֦������һ������
		{
			while (newString.size() == word.size() && newString == word)  //ѭ������Ȼ��ȡ���뵥����ȣ���ô��Ҫһֱѭ������ȵ�ȥ��,��Ϊ�˼���ʱ��,����ᳬʱ
			{
				tmp = tmp.substr(word.size());
				newString = tmp.substr(0, word.size());
			}
			bool t = wordBreak_item(tmp, wordDict);  //ʣ�²���ȵģ��ݹ鿴�����������Ƿ����
			if (t)  //�����һ���ɹ����ͷ��ؾͿ�����
			{
				flag = true;
				break;
			}
		}
	}
	return flag;
}
bool wordBreak(string s, vector<string>& wordDict)  //���ʲ��
{
	return wordBreak_item(s, wordDict);
}

void reorderList(ListNode* head)  //��������
{
	if (!head)
	{
		return;
	}
	vector<ListNode*> tmp;  //�������нڵ�
	int n = 0;
	while (head)
	{
		++n;
		tmp.push_back(head);
		head = head->next;
	}
	int t = n - 1;
	n % 2 == 0 ? n /= 2 : n = n / 2 + 1;  //�����ż��������ôֻ�����ǰn/2����������Ҫ��������n/2+1���������м��Ǹ���Ҫ���⴦��
	ListNode* result = new ListNode(0);
	ListNode* temp = result;
	for (int i = 0; i < n; ++i)
	{
		if (t - i == i)  //�м���Ǹ����⴦��
		{
			result->next = tmp[i];
			result = result->next;
			break;
		}
		result->next = tmp[i];
		result = result->next;
		result->next = tmp[t - i];
		result = result->next;
	}
	result->next = nullptr;  //���һ����Ҫָ��null
	head = temp->next;
}

vector<int> preorderTraversal(TreeNode* root)  //��������ǰ�����--����
{
	if (!root)
	{
		return {};
	}
	stack<TreeNode*> s;
	s.push(root);
	vector<int> result;
	while (!s.empty())
	{
		root = s.top();
		s.pop();
		result.push_back(root->val);
		if (root->right)
		{
			s.push(root->right);
		}
		if (root->left)
		{
			s.push(root->left);
		}
	}
	return result;
}

void preorderTraversal_1_item(TreeNode* root, vector<int> &result)
{
	if (!root)
	{
		return;
	}
	result.push_back(root->val);
	preorderTraversal_1_item(root->left, result);
	preorderTraversal_1_item(root->right, result);
}
vector<int> preorderTraversal_1(TreeNode* root)  //��������ǰ�����--�ݹ�
{
	if (!root)
	{
		return {};
	}
	vector<int> result;
	preorderTraversal_1_item(root, result);
	return result;
}

ListNode* insertionSortList(ListNode* head)  //��������в�������
{
	if (!head)
	{
		return nullptr;
	}
	ListNode* preHead = new ListNode(0);  ////�ڱ��ڵ�
	ListNode* cur = head;
	ListNode* pre = preHead;  
	ListNode* n = nullptr;  //��һ��ָ��
	while (cur)
	{
		n = cur->next;
		while (pre->next && pre->next->val < cur->val)  //���pre����һ��С�ڵ�ǰֵ��һֱ�ҵ��ȵ�ǰֵ���
		{
			pre = pre->next;
		}
		cur->next = pre->next;  //��ǰֵ����һ�����ǵ�һ���������
		pre->next = cur;  //ǰһ��ָ��ǰֵ
		pre = preHead;  //�����¿�ʼ
		cur = n;
	}
	return preHead->next;
}


ListNode* sortList(ListNode* head)  //��������--�鲢����
{
	//�� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£��������������
	if (!head)
	{
		return nullptr;
	}
	if (!head->next)
	{
		return head;
	}
	ListNode* slow = head;
	ListNode* fast = head->next;  //����ָ��
	while (fast && fast->next)  //ֱ��slow�����е㣬fast->next�������յ�
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	ListNode* mid = slow->next;  //midΪ���̵����
	slow->next = nullptr;  //slow������е���һ��Ϊnull
	slow = head;  //ǰ��ο�ʼ
	slow = sortList(slow);  //�����ǰ���
	mid = sortList(mid);  //����ú����
	ListNode* result = new ListNode(0);  //�ڱ�
	ListNode* t = result;  //��¼�ڱ�
	//�����Ǻϲ�����
	while (slow || mid)  //�ϲ�����
	{
		if (slow && mid)  //������߶��У����С����ȥ
		{
			if (slow->val < mid->val)
			{
				result->next = slow;
				slow = slow->next;
			}
			else
			{
				result->next = mid;
				mid = mid->next;
			}
		}
		else if (slow && !mid)  //ֻ��slow������ֱ���뵽����
		{
			result->next = slow;
			slow = slow->next;
		}
		else  //ֻ��mid������������
		{
			result->next = mid;
			mid = mid->next;
		}
		result = result->next;
	}
	result->next = nullptr;  //���һ����һ��ָ��null
	return t->next;  //�����ڱ���ߵ�ʵ��
}

int evalRPN(vector<string>& tokens)  //�沨�����ʽ��ֵ
{
	if (tokens.size() == 0)
	{
		return 0;
	}
	stack<int> s;
	int result = 0;
	for (int i=0; i<tokens.size(); ++i)
	{
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
		{
			int x = s.top(); s.pop();
			int y = s.top(); s.pop();
			if (tokens[i] == "+")
			{
				s.push(x + y);
			}
			else if (tokens[i] == "-")
			{
				s.push(y - x);
			}
			else if (tokens[i] == "*")
			{
				s.push(x * y);
			}
			else
			{
				s.push(y / x);
			}
		}
		else
		{
			int tmp = std::stoi(tokens[i]);
			s.push(tmp);
		}
	}
	return s.empty() ? 0 : s.top();
}

string reverseWords(string s)  //��ת�ַ�����ĵ���
{
	if (s.size() == 0)
	{
		return "";
	}
	int n = s.size();
	string result;
	int i = 0;
	while (i < n)  //����
	{
		while (i < n && s[i] == ' ')  //����ǿո񣬾�����
		{
			++i;
		}
		if (i == n)  //���һֱ�����һ���ǿո񣬾�ֱ��break
		{
			break;
		}
		string tmp;
		while (i < n && s[i] != ' ')  //�Ӳ��ǿո�Ŀ�ʼ��ֱ�������ո�
		{
			tmp += s[i];
			++i;
		}
		result = tmp + ' ' + result;  //��������
	}
	while (result[result.size() - 1] == ' ')  //�Ѷ�Ŀո�ɾ����
	{
		result.pop_back();
	}
	return result;
}

int findMin(vector<int>& nums)  //Ѱ����ת���������е���Сֵ
{
	if (nums.size() == 0)
	{
		return 0;
	}
	if (nums.size() == 1)
	{
		return nums[0];
	}
	int l = 0, r = nums.size() - 1;
	int result = INT_MAX;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (nums[l] <= nums[mid]) //l->midΪ����
		{
			result = min(nums[l], result);
			l = mid + 1;
		}
		else //mid->rΪ����
		{
			result = min(result, nums[mid]);
			r = mid - 1;
		}
	}
	return result;
}

int findPeakElement(vector<int>& nums)  //Ѱ�ҷ�ֵ
{
	if (nums.size() <= 1)
	{
		return 0;
	}
	if (nums.size() == 2)
	{
		return nums[0] > nums[1] ? 0 : 1;
	}
	int l = 0, r = nums.size() - 1;
	while (l <= r)  //���ַ�
	{
		//���mid����mid+1�Ļ���˵����ֵ��mid������࣬����������Ҳ�
		int mid = (r - l) / 2 + l;
		if (mid + 1 < nums.size() && nums[mid] < nums[mid + 1])
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	return l;
}

int compareVersion(string version1, string version2)  //�Ƚϰ汾��
{
	if (version1.size() == 0 && version2.size() == 0)
	{
		return 0;
	}
	if (version1.size() == 0)
	{
		return -1;
	}
	if (version2.size() == 0)
	{
		return 1;
	}
	int i = 0, j = 0;
	while (i < version1.size() || j < version2.size())
	{
		int x = 0, y = 0;
		string s1, s2;
		while (i < version1.size())  //һֱѭ���������
		{
			if (version1[i] == '.')
			{
				break;
			}
			s1 += version1[i];
			++i;
		}
		while (j < version2.size())  //һֱѭ���������
		{
			if (version2[j] == '.')
			{
				break;
			}
			s2 += version2[j];
			++j;
		}
		if (s1.size() == 0 && s2.size() > 0)  //���û���ˣ�����˵i��ͷ��
		{
			y = std::stoi(s2);
			if (y > 0)  //���v2ʣ�µĴ���0����1��1.1��˵��v2��
			{
				return -1;
			}
		}
		else if (s1.size() > 0 && s2.size() == 0)  //���û���ˣ�����j��ͷ��
		{
			x = std::stoi(s1);
			if (x > 0)  //���v1ʣ�µĴ���0����1.1��1������v1��
			{
				return 1;
			}
		}
		else if (s1.size() == 0 && s2.size() == 0)  //�����û���ˣ���ֱ�ӷ���0
		{
			return 0;
		}
		else  //������еĻ�
		{
			x = std::stoi(s1);
			y = std::stoi(s2);
			if (x > y)  //���x>y,����v1��
			{
				return 1;
			}
			else if (x < y) //���y>x������v2��
			{
				return -1;
			}
			//����ʡ�������������͵ü����ȽϺ����
		}
		//������
		++i;
		++j;
	}
	return 0;
}

string fractionToDecimal(int numerator, int denominator)  //������С��
{
	if (numerator == 0)
	{
		return "0";
	}
	if (denominator == 0)
	{
		return "";
	}
	string result;
	long long num = static_cast<long long>(numerator);
	long long den = static_cast<long long>(denominator);
	if ((num > 0) ^ (den > 0))
	{
		result.push_back('-');
	}
	num = abs(num);  den = abs(den);
	result.append(std::to_string(num / den));
	num %= den;
	if (num == 0)
	{
		return result;
	}
	result.push_back('.');  //�������Ļ�����С������Ӧ�ò���С����
	unordered_map<int, int> um;  //��¼�ظ��������±�,���ﲻ�ܼ�¼����е����ֳ������꣬��Ϊ����1.255�����ﲻ��ѭ��С��������Ҫ��¼5�Ļ����ͳ���ѭ��С����Ӧ���Ǽ�¼�����������ĳ���
	int index = result.size() - 1;
	while (num && um.count(num) == 0)  //���num��Ϊ0����֮ǰû���ֹ�
	{
		++index;  //�±�ָ���ڱ�
		um[num] = index;  //�������
		num *= 10;
		result += std::to_string(num / den);
		num %= den;
	}
	if (um.count(num) == 1)  //������ֹ����������ô����λ���ϲ���(
	{
		result.insert(um[num], "(");
		result.push_back(')');
	}
	return result;
}

class BSTIterator {   //����������������
public:
	vector<int> tmp;
	int index = -1;  //��ʾ�Ѿ��ù�����
	BSTIterator(TreeNode* root) {
		stack<TreeNode*> s;
		while (true)
		{
			while (root)
			{
				s.push(root);
				root = root->left;
			}
			if (s.empty())
			{
				break;
			}
			root = s.top(); s.pop();
			tmp.push_back(root->val);
			root = root->right;
		}
	}

	/** @return the next smallest number */
	int next() {

		return tmp[++index];  //��Ϊindex��ʾ�Ѿ��ù����������Ҫ��++
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		if (index + 1 < tmp.size())  //��Ϊindex��ʾ���ù����������Ҫ����index+1�Ƿ�����
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

static bool largestNumber_compare(string s1, string s2)  //����s1>s2 ?
{
	if (s1.size() == 0)  //���s1Ϊ�յģ���ôֱ�ӷ���s2
	{
		return false;
	}
	if (s2.size() == 0)  //���s2Ϊ�յģ�ֱ�ӷ���s1
	{
		return true;
	}
	if (s1.size() == 1 && s2.size() == 1)  //��Ϊ1������ô���ؽϴ���Ǹ�
	{
		int x = s1[0] - '0', y = s2[0] - '0';
		return (x > y);
	}
	int i = 0, j = 0;
	while (i < s1.size() || j < s2.size())  //�������е��ַ���
	{
		////�����ʱi����������±꣬��ô��0��ʼ��
		//�������Ҫ˵һ�£�����234��2344�ȽϵĻ����϶���2344234����2342344��
		//Ҳ����˵���ĳһ���ַ�������������ˣ���û�ֳ���С�Ļ�(����234�������)����ʱi=2,j=2
		//������Ҫ�Ƚ�2344�е�j=3Ҳ����4��i=0�Ĵ�С��˭��˭����ǰ��
		//�����2344�е�4����234�е�2�����2344����234
		//�ټ���543��5432���϶���5435432����5432543��Ҳ���ǵ�543����3(i=2)ʱ��5432��ʱҲ����3(j=2)��
		//��ô����Ȼ��ʱ��Ҫ������543���뵽5432���棬Ҫ������5432���뵽543���棬ǰ�����λ��543����ͬ��
		//��ô����λ�϶��ǽϴ��һ�������������λ��
		//Ҫ�����ǻ�ʣ���ַ����Ǹ�(5432)����һλ(2)����ʱ��543����5432�ĺ���5432543��
		//Ҫ�����ǻ�ʣ���ַ����Ǹ�(5432)�ĵ�һλ(5)��Ҳ����5432����543�ĺ��棬�����ڵ�ǰλ��ǰ������λ������ͬ�ģ����Ҳ���������ַ����Ǹ��ĵ�һλ
		//�����ʱ��δ�ֳ�ʤ��������Ҫi++,j++��ֱ���ֳ�ʤ��,
		//��ʱ��Ҫ˵�����ǣ�����11��111���ǲ��Ǿ�һֱѭ�����أ���Ȼ����i��j�ı任��ͬ�����ܻ��˳�ѭ����
		//�Լ����԰��մ��������������
		if (i >= s1.size())  
		{
			i = 0;
		}
		if (j >= s2.size())
		{
			j = 0;
		}
		int x = s1[i] - '0', y = s2[j] - '0';
		if (x > y)
		{
			return true;
		}
		else if (y > x)
		{
			return false;
		}
		++i;
		++j;
	}
	return true;
}
string largestNumber(vector<int>& nums)  //�����
{
	if (nums.size() == 0)
	{
		return "";
	}
	if (nums.size() == 1)
	{
		return std::to_string(nums[0]);
	}
	vector<string> tmp;
	string result;
	for (int i : nums)
	{
		tmp.push_back(std::to_string(i));
	}
	sort(tmp.begin(), tmp.end(), largestNumber_compare);  //�����Զ�������
	if (tmp[0] == "0")
	{
		return "0";
	}
	//sort���õ�[1,102,21]->[21, 102, 1],ֱ�������������
	for (string s : tmp)  //���
	{
		result += s;
	}
	while (result[0] == '0' && result.size() > 1)  //����resultǰ���0
	{
		result = result.substr(1);
	}
	return result;
}

int main()
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

	//�������Ĳ�α���
	//levelOrder

	//��������
	//generateParenthesis

	//�ҵ��ַ�����������ĸ��λ��
	//findAnagrams

	//��Ч������
	//isValidSudoku

	//ʵ�� Trie (ǰ׺��)
	//Trie

	//��������
	//exist

	//����λ����
	//countBits

	//��������С·����
	//minimumTotal

	//�˻����������
	//maxProduct

	//���������Ʊʱ�����䶳��
	//maxProfit_cooldown

	//�����������
	//lengthOfLIS

	//��Ǯ�һ�
	//coinChange

	//��������
	//numIslands

	//����Ȧ
	//findCircleNum

	//LRU�������
	//class LRUCache

	//������Ӵ�
	//longestPalindrome

	//Z ���α任
	//convert

	//�ַ���ת������ (atoi)
	//myAtoi

	//ʢ���ˮ������
	//maxArea

	//����ת��������
	//intToRoman

	//��ӽ�������֮��
	//threeSumClosest

	//�绰�������ĸ���
	//letterCombinations

	//����֮��
	//fourSum

	//ɾ������ĵ�����N���ڵ�
	//removeNthFromEnd

	//�������
	//divide

	//��һ������
	//nextPermutation

	//������ת��������
	//search

	//�����������в���Ԫ�صĵ�һ�������һ��λ��
	//searchRange

	//����ܺ�
	//combinationSum

	//����ܺ� II
	//combinationSum2

	//�ַ������
	//multiply

	//ȫ����
	//permute

	//ȫ���� II
	//permuteUnique

	//��תͼ��
	//rotate

	//��ĸ��λ�ʷ���
	//groupAnagrams

	//��������
	//spiralOrder

	//��Ծ��Ϸ
	//canJump

	//�ϲ�����
	//merge

	//�������� II
	//generateMatrix

	//��k������
	//getPermutation

	//��ת����
	//rotateRight

	//��ͬ·��
	//uniquePaths

	//��ͬ·�� II
	//uniquePathsWithObstacles

	//��С·����
	//minPathSum

	//��·��
	//simplifyPath

	//��������
	//setZeroes

	//������ά����
	//searchMatrix

	//��ɫ����
	//sortColors

	//���
	//combine

	//�Ӽ�
	//subsets

	//ɾ�����������е��ظ��� II
	//removeDuplicates

	//������ת�������� II
	//search

	//ɾ�����������е��ظ�Ԫ�� II
	//deleteDuplicates

	//�ָ�����
	//partition

	//���ױ���
	//grayCode

	//�Ӽ� II
	//subsetsWithDup

	//���뷽��
	//numDecodings

	//��ת���� II
	//reverseBetween

	//��ԭIP��ַ
	//restoreIpAddresses

	//���������������
	//inorderTraversal

	//��ͬ�Ķ��������� II
	//generateTrees

	//��ͬ�Ķ���������
	//numTrees

	//�������ľ���β�α���
	//zigzagLevelOrder

	//��ǰ��������������й��������
	//buildTree

	//�����������������й��������
	//buildTree

	//��������ת������������
	//sortedListToBST

	//·���ܺ� II
	//pathSum

	//������չ��Ϊ����
	//flatten

	//���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
	//connect

	//���ÿ���ڵ����һ���Ҳ�ڵ�ָ�� II
	//connect

	//���ʽ���
	//ladderLength

	//�����Ҷ�ӽڵ�����֮��
	//sumNumbers

	//��Χ�Ƶ�����
	//solve

	//�ָ���Ĵ�
	//partition

	//��¡ͼ
	//cloneGraph

	//����վ
	//canCompleteCircuit

	//ֻ����һ�ε����� II
	//singleNumber

	//���ƴ����ָ�������
	//copyRandomList

	//���ʲ��
	//wordBreak

	//��������
	//reorderList

	//��������ǰ�����
	//preorderTraversal

	//��������в�������
	//insertionSortList

	//��������
	//sortList

	//�沨�����ʽ��ֵ
	//evalRPN

	//��ת�ַ�����ĵ���
	//reverseWords

	//Ѱ����ת���������е���Сֵ
	//findMin

	//Ѱ�ҷ�ֵ
	//findPeakElement

	//�Ƚϰ汾��
	//compareVersion

	//������С��
	//fractionToDecimal

	//����������������
	//class BSTIterator

	//�����
	//largestNumber
}