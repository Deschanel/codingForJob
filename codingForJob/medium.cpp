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
	/*
	if (amount == 0)
	{
		return 0;
	}
	if (coins.size() == 0 || amount < 0)
	{
		return -1;
	}
	int minCount = amount + 1;
	for (int i = 0; i < coins.size(); ++i)
	{
		if (coins.at(i) <= amount)
		{
			int tmp = coinChange_2(coins, amount - coins.at(i));
			if (tmp == -1)
			{
				continue;
			}
			minCount = min(minCount, tmp + 1);
		}
	}
	return minCount > amount ? -1 : minCount;
	*/   //��ʱ��
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
}