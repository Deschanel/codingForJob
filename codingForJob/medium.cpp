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
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)  //两数相加
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

int lengthOfLongestSubstring_1(string s)  //无重复字符的最长子串
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

int lengthOfLongestSubstring_2(string s)  //无重复字符的最长子串
{
	if (s.size() <= 1)
	{
		return s.size();
	}
	int result = 1;
	unordered_map<char, int> um;
	unordered_map<char, int>::iterator ifind;
	for (int i=0, j=0; i<s.size(); ++i)   //j表示左端点
	{
		ifind = um.find(s.at(i));
		if (ifind != um.end())
		{
			j = max(ifind->second + 1, j);   //如果出现a(i)....b(j)....b(k)....a(m)这种情况(括号中为元素的下标)，就是b重复时更新左端点为j+1, 而当a重复时，左端点成了i+1，这样就会把两个b包含进去，因此j应该取大的那个
			//上个语句，其实就是，如果找到的重复字符在当前左端点右边的话，那么就更新左端点，在左边就是在当前候选最长子串中并没有重复，因此不需要更新
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

ListNode* swapPairs(ListNode* head)  //两两交换链表中的节点
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

ListNode *detectCycle_1(ListNode *head)  //环形链表 II--hash表
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

ListNode *detectCycle_2(ListNode *head)  //环形链表 II--快慢指针https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/huan-xing-lian-biao-ii-by-leetcode/
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

vector<vector<int>> threeSum(vector<int>& nums)  //三数之和
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
	else   //中序遍历
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
bool isValidBST_2(TreeNode* root)  //递归，上下界
{
	return isValidBST_2_item(root, LONG_MIN, LONG_MAX);
}

TreeNode* lowestCommonAncestor_1(TreeNode* root, TreeNode* p, TreeNode* q)  //二叉树的最近公共祖先
{
	if (!root)
	{
		return nullptr;
	}
	if (root == p || root == q)
	{
		return root;
	}
	TreeNode* l = lowestCommonAncestor_1(root->left, p, q);  //在左子树找二者之一
	TreeNode* r = lowestCommonAncestor_1(root->right, p, q); //在右子树找二者之一
	if (!l && r)  //如果右子树中有其中一个，左子树没有，说明肯定都在右子树,因此应该递归lowestCommonAncestor(root->right, p, q),而这个已经执行了
	{
		return r;
	}
	else if(l && !r) //如果左子树中有其中一个，右子树没有，说明肯定都在左子树
	{
		return l;
	}
	else if (!l && !r) //左右子树都不在
	{
		return nullptr;
	}
	else  //左右子树中都有两者之一，说明最近公共祖先就是root
	{
		return root;
	}
}

TreeNode* lowestCommonAncestor_2(TreeNode* root, TreeNode* p, TreeNode* q)  //二叉树的最近公共祖先--寻找路径
{
	stack<TreeNode*> s;  //存放迭代的节点
	unordered_map<TreeNode*, TreeNode*> um;  //第一个为当前节点，第二个为父节点
	um.insert(pair<TreeNode*, TreeNode*>(root, nullptr));
	s.push(root);
	while (um.find(p) == um.end() || um.find(q) == um.end()) //层次遍历，把每个的父节点记录下来
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
	unordered_set<TreeNode*> anc;  //p的所有祖先
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

double myPow(double x, int n)  //Pow(x, n)--分治，log(n)
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

vector<int> majorityElement(vector<int>& nums) //求众数 II--由于要求是超过[n/3]上整，因此最多有两个元素为众数
{
	if (nums.size() < 2)
	{
		return nums;
	}
	int count1 = 0, count2 = 0;
	int cx = 0, cy = 0;
	for (auto i : nums)
	{
		if ((count1 == 0 || cx == i) && i != cy)  //这里不加i != cy的话，会使cy少加一个
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
	//检验这两个是否是真的众数
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

vector<vector<int>> levelOrder(TreeNode* root)  //二叉树的层次遍历
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
		int len = q.size();  //每次的个数为当前层次的元素个数
		vector<int> tmp;
		while (len > 0)  //把当前所有层次元素遍历完后，加入的那些子树就是下一层次的个数
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
	if (l > r)   //剩下的左括号个数大于右括号，说明需要剪枝，当软这里也可以l < r，这样的话后面的就应该是"(" + s 和 ")" + s
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
vector<string> generateParenthesis_1(int n)  //括号生成--深度优先搜索https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/
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

vector<string> generateParenthesis_2(int n)  //括号生成--动态规划
{
	if (n == 0)
	{
		return {};
	}
	//对于n-1对括号时，假设可以从中间某处分为各自成立的两个字串，分别为p对括号，q对括号，p+q=n-1，则p的范围0->n-1,q的范围对应的为n-1->0
	//则当n对括号时，就是对每一个p和q的结果vector中的任意组合中(p)+q，或者p+(q),而p+()+q，或者p+q+(),或者()+p+q，在p或q为0时包括了,加上就重复了
	vector<string> result;
	for (int i = 0; i < n; ++i)
	{
		for (string leftString : generateParenthesis_2(i)) // 当i对括号时p的字符串
		{
			for (string rightString : generateParenthesis_2(n - 1 - i))  //n-1-i对括号时q的字符串
			{
				result.push_back("(" + leftString + ")" + rightString);
			}
		}
	}
	return result;
}
vector<int> findAnagrams(string s, string p)   //找到字符串中所有字母异位词
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

bool isValidSudoku(vector<vector<char>>& board)   //有效的数独
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

class Trie {   //实现 Trie (前缀树)
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
				tmp = tmp->children.at(word.at(i) - 'a');  //下面不需要判断是否当前元素是end，因为例如app和apple都插入的话，寻找apple时发现第二个p是end，那么就会返回false，然后apple是有的，所以这边要是判断的话就会出错，只需要最后一个字符判断是否是end就好了
			}
		}
		return tmp->isEndOfWord;  //看看最后一个字符是否是已有单词的最后一个元素
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
					if (exist_dfs(board, word, n + 1, i, j))  //如果下一层递归成功，那么就说明剩下的字符成功了，就直接返回true，否则的话还原当前字符串继续循环
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
bool exist(vector<vector<char>>& board, string word)  //单词搜索
{
	if (board.size() == 0 || word.size() == 0)
	{
		return false;
	}
	//深度优先搜索
	return exist_dfs(board, word, 0, 0, 0);
}

vector<int> countBits_1(int num)  //自己的 
{
	//加入已经知道n的时候1的个数，那么对于2n，就是直接将n的二进制左移，因此1的个数不变；如果是2n+1的话，是将n二进制左移，然后在末尾左移后多出来的一位0加上1，也就比原来n的1个数多一个
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

vector<int> countBits_2(int num) //通过i & (i - 1)
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
void minimumTotal_dfs(vector<vector<int>>& triangle, int i, int j, int tmp)  //深度优先搜索
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
int minimumTotal_1(vector<vector<int>>& triangle)  //三角形最小路径和--深度优先搜索超时了
{
	if (triangle.size() == 0)
	{
		return 0;
	}
	int tmp = 0;
	minimumTotal_dfs(triangle, 0, 0, tmp);
	return minimumTotal_result;
}

int minimumTotal_2(vector<vector<int>>& triangle)  //三角形最小路径和
{
	if (triangle.size() == 0)
	{
		return 0;
	}
	vector<int> dp(triangle.size(), 0);   //dp表示从最底层到当前的(i，j)的最小路径和
	dp.assign(triangle.at(triangle.size() - 1).begin(), triangle.at(triangle.size() - 1).end());
	for (int i = triangle.size() - 2; i >= 0; --i)
	{
		for (int j = 0; j < triangle.at(i).size(); ++j)
		{
			dp[j] = min(dp[j], dp[j + 1]) + triangle.at(i).at(j);
		}
	}
	return dp[0];  //最后回归成第一个元素
}

int maxProduct(vector<int>& nums)  //乘积最大子序列
{
	if (nums.size() == 0)
	{
		return 0;
	}
	vector< vector<int> > dp(nums.size(), vector<int>(2));  //表示到i为止的最大最小乘积
	dp[0][0] = nums.at(0);  //第二维为0表示正数最大值
	dp[0][1] = nums.at(0);  //第二维为1表示最小值(负数绝对值最大)
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

int maxProfit_cooldown(vector<int>& prices)  //要注意这里的冷冻期只有卖出后才有，买入后没有
{
	//dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
	//dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i])
	//解释：第 i 天选择 buy 的时候，要从 i - 2 的状态转移，而不是 i - 1 。
	if (prices.size() == 0)
	{
		return 0;
	}
	int n = prices.size();
	int dp_i_0 = 0, dp_i_1 = INT_MIN;
	int dp_pre_0 = 0;    //代表 dp[i-2][0]
	for (int i = 0; i < n; i++) {
		int temp = dp_i_0;
		dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
		dp_i_1 = max(dp_i_1, dp_pre_0 - prices[i]);
		dp_pre_0 = temp;
	}
	return dp_i_0;
}

int lengthOfLIS(vector<int>& nums)  //最长上升子序列
{
	if (nums.size() <= 1)
	{
		return nums.size();
	}
	vector<int> dp(nums.size());  //包含第i个元素的前i个数中的最长上升子序列, dp[i] = max(dp[j]) + 1, j=0->i-1
	dp[0] = 1;
	int result = 1;
	for (int i=1; i<nums.size(); ++i)
	{
		int tmp = 0;
		for (int j=0; j<i; ++j)
		{
			if (nums.at(j) < nums.at(i))  //要是大于等于，那么肯定不包括第i各元素了
			{
				tmp = max(tmp, dp[j]);
			}
		}
		dp[i] = tmp + 1;
		result = max(result, dp[i]);
	}
	return result;
}

int coinChange_1(vector<int>& coins, int amount)  //零钱兑换
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

int coinChange_2(vector<int>& coins, int amount)  //零钱兑换
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

int numIslands(vector<vector<char>>& grid)  //岛屿数量--并查集
{
	if (grid.size() == 0 || grid.at(0).size() == 0)
	{
		return 0;
	}
	int count = 0, n = grid.size(), m = grid.at(0).size();
	vector<int> parent(grid.size()*grid.at(0).size(), -1);
	vector<int> r(grid.size()*grid.at(0).size(), 0);  //考虑rank
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
					if (rootx != rooty)  //如果根不相同，但是由于是相邻的，因此要合并
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

int findCircleNum(vector<vector<int>>& M)  //朋友圈
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
				if (rootx != rooty) //第i个和第j个认识，按照那么他们的老大也应该认识
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
	//第一个int为key，第二个int为value，第三个int为使用频率，第四个int为最近使用或插入时间
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
			if (ifind->second.first != value)  //如果存在也值不等的话，就要修改值并且改变频率和时间
			{
				ifind->second.first = value;
				ifind->second.second.first += 1;
				ifind->second.second.second = time;
			}
			return;
		}
		if (lruUM.size() < this->_capacity)  //如果还有空间，直接插入
		{
			pair<int, pair<int, pair<int, int> > > p(key, pair<int, pair<int, int> >(value, pair<int, int>(1, time)));
			lruUM.insert(p);
		}
		else
		{
			ifind = lruUM.begin();
			int mint = ifind->second.second.second;
			for (; ifind != lruUM.end(); ifind++)  //先找到时间最先的那个
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
					else  //如果时间相同，那么就要去掉频率最低的那个
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

string longestPalindrome(string s)  //最长回文子串
{
	if (s.size() <= 1)
	{
		return s;
	}
	vector<vector<int> > dp(s.size(), vector<int>(s.size()));  //第i个到第j个元素(包括i和j)是否是回文串，是的话就是1，否则为0
	int maxLen = 1, start = 0;  //回文串最大长度和开始位置，如果有多个开始位置，那么start为其中一个
	for (int i=0; i<s.size(); ++i)
	{
		dp[i][i] = 1;  //单独一个字符肯定是回文
		if (i < s.size() - 1 && s[i] == s[i + 1])  //如果相邻的两个相同就是回文
		{
			dp[i][i + 1] = 1;
			maxLen = 2;
			start = i;
		}
	}
	for (int l=3; l<=s.size(); ++l)  //从长度为3开始
	{
		for (int i=0; i+l-1<s.size(); ++i)
		{
			int j = i + l - 1;
			if (s[i] == s[j] && dp[i + 1][j - 1] == 1)  //如果第i个和第j个一样，并且之间的已经是回文串了
			{
				maxLen = l;
				start = i;
				dp[i][j] = 1;
			}
		}
	}
	return s.substr(start, maxLen);
}

string convert(string s, int numRows)  //Z 字形变换
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

int myAtoi(string str)  //字符串转换整数 (atoi)
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

int maxArea_1(vector<int>& height)   //盛最多水的容器--暴力法超时了
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

int maxArea_2(vector<int>& height)   //盛最多水的容器--双指针
{
	int l = 0, r = height.size() - 1;
	int result = 0;
	while (l < r)
	{
		int tmp = (r - l) * min(height[l], height[r]);
		result = max(result, tmp);
		if (height[l] < height[r])  //如果右侧大，那么此时是以l为竖边，那么如果减小r的话，只会面积越来越小，因此要增加l
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

string intToRoman(int num)  // 整数转罗马数字
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
	--ii;  //从最大的往下找
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

int threeSumClosest(vector<int>& nums, int target)  //最接近的三数之和
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
		while (l < r)  //双指针，如果相等的话就是一样了
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
	vector<string> tmp = letterCombinations_item(index + 1, m, digits);  //已知从后截至到index+1(包含)的结果，那么当前的结果就是得到的tmp再跟当前数字代表的字符全组合
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
vector<string> letterCombinations(string digits)  //电话号码的字母组合
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

vector<vector<int>> fourSum(vector<int>& nums, int target)  //四数之和
{
	if (nums.size() <= 3)
	{
		return {};
	}
	sort(nums.begin(), nums.end());
	vector< vector<int> > result;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (i > 0 && nums[i] == nums[i - 1])  //如果当前与前一个相同，就说明已经用过了
		{
			continue;
		}
		for (int j = i + 1; j < nums.size(); ++j)
		{
			if (j > i + 1 && nums[j] == nums[j - 1])  //如果j是大于i+1，也就是说j-1 > i, 有重复的话就说明之前用过了,如果j=i+1就continue的话，就把第i个去掉了
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
					while (l < nums.size() && nums[l] == t) //如果之后的有等于nums[l]的，那么要一直往后越过去
					{
						++l;
					}
					t = nums[r];
					while (r >= 0 && nums[r] == t)  //如果之前有等于的，要一直往前越过去
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

ListNode* removeNthFromEnd(ListNode* head, int n)  //删除链表的倒数第N个节点
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
	if (index == 0)  //如果是删除第一个
	{
		if (i <= 1) //如果节点个数小于等于一个
		{
			return nullptr;
		}
		else  //如果节点个数大于1个，直接从第二个开始即可
		{
			return tmp[1];
		}
	}
	else  //如果不是删除第一个
	{
		if (n == 1)  //如果是删除最后一个，直接让倒数第二个的next指向nullptr
		{
			tmp[index - 1]->next = nullptr;
		}
		else  //否则的话就是让前一个指向后一个
		{
			tmp[index - 1]->next = tmp[index + 1];
		}
		return tmp[0];
	}
}

int divide(int dividend, int divisor)  //两数相除
{
	if (divisor == 0)
	{
		return INT_MAX;
	}
	if (dividend == 0)
	{
		return 0;
	}
	bool flag = true;  //结果是正数
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

void nextPermutation(vector<int>& nums)  //下一个排列
{
	/*
	我们还希望下一个数增加的幅度尽可能的小，这样才满足“下一个排列与当前排列紧邻“的要求。
	为了满足这个要求，我们需要
	1. 在尽可能靠右的低位进行交换，需要从后向前查找
	2. 将一个尽可能小的大数与前面的小数交换。比如 123465，下一个排列应该把 5 和 4 交换而不是把 6 和 4 交换
	3. 将大数换到前面后，需要将大数后面的所有数重置为升序，升序排列就是最小的排列。
	以 123465 为例：首先按照上一步，交换 5 和 4，得到 123564；
	然后需要将 5 之后的数重置为升序，得到 123546。
	显然 123546 比 123564 更小，123546 就是 123465 的下一个排列

	*/
	if (nums.size() <= 1)
	{
		return;
	}
	bool isJiangXu = true, isShengXu = true;
	int x = 0, y = 0; //升序的两个
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
	else  //非升序和降序两个特殊情况
	{
		//根据上个for循环，可以知道此时x和y为最后一对升序的，因此，y之后(包括y)的数为降序的
		for (int i = nums.size() - 1; i >= 0; --i)  //从后往前找到比x数大的第一个数，首先肯定有y数，二由于后面是降序的，因此找到的第一个肯定是大于x数的最小数
		{
			if (nums[i] > nums[x])
			{
				y = i;
				break;
			}
		}
		swap(nums[x], nums[y]);  //交换最小的大数与x
		sort(nums.begin() + x + 1, nums.end());  //再将后面的降序改为升序，找到大于原排列的最小的排列
	}
}

int search(vector<int>& nums, int target)  //搜索旋转排序数组
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
		if (nums[l] <= nums[mid])  //表示在l到mid是升序,因为可能mid=l,所以要有等于
		{
			if (nums[l] <= target && nums[mid] > target)  //在l到mid之间
			{
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		else  //那么l的数大于mid的数，也就是说mid到r是升序的
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
	if (l < 0)  //如果l为负的
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
		if (nums[mid] == target && isLeft) //如果相等这时候不返回，如果是要找左端点，就r往前走
		{
			r = mid - 1;
		}
		else if (nums[mid] > target)
		{
			r = mid - 1;
		}
		else   //这个else包括其中一个情况：如果相等且找的是右端点，则l往后走
		{
			l = mid + 1;
		}
	}
	if (l == 0)
	{
		return nums[l] == target ? 0 : -1;  //看看应该是返回0还是-1
	}
	else
	{
		int tmp = l - 1;
		return nums[tmp] == target ? tmp : l;   //如果l - 1的数等于target的话就返回这个下标较小的，否则就返回下标大的
	}
}
vector<int> searchRange(vector<int>& nums, int target)  //在排序数组中查找元素的第一个和最后一个位置
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
	result[0] = (nums[l] == target ? l : -1);  //判断返回的下标是否等于target
	result[1] = (nums[r] == target ? r : -1);
	return result;
}

set< vector<int> > combinationSum_s;
void combinationSum_dfs(vector<int>& candidates, int target, vector<int> s)  //深度优先搜索
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
		vector<int> tmp = s;  //这里是为了让用过的第i-1个数去掉，所以不能用s.push_back(candidates[i])
		tmp.push_back(candidates[i]);
		combinationSum_dfs(candidates, target - candidates[i], tmp);
	}
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target)  //组合总和
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
		if (s.find(i) != s.end())  //如果用过了
		{
			continue;
		}
		if (target - candidates[i] < 0)  //剪枝
		{
			continue;
		}
		s.insert(i);
		vector<int> tmp = v; //这里是为了让用过的第i-1个数去掉，所以不能用s.push_back(candidates[i])
		tmp.push_back(candidates[i]);
		combinationSum2_dfs(candidates, target - candidates[i], s, tmp);
		s.erase(i);  //把用过的这个删掉
	}
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)  //组合总和 II
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
string multiply(string num1, string num2)  //字符串相乘
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
		jinwei = 0;  //jinwei归零
		for (int j = num2.size() - 1; j >= 0; --j)
		{
			int y = num2[j] - '0';
			int z = (x * y + jinwei) % 10;
			jinwei = (x * y + jinwei) / 10;
			s = std::to_string(z) + s;
		}
		if (jinwei)  //如果还有jinwei，就放在最前面
		{
			s = std::to_string(jinwei) + s;
		}
		for (int k = 0; k < numOf0; ++k)
		{
			s = s + std::to_string(0);  //加上后面的零
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
vector<vector<int>> permute(vector<int>& nums)  //全排列
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
		s.erase(i);  //删掉用过的
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

void rotate(vector<vector<int>>& matrix)  //旋转图像
{
	//先转置，然后依据竖直中心线对称
	if (matrix.size() <= 1)
	{
		return;
	}
	for (int i = 0; i < matrix.size(); ++i)  //转置
	{
		for (int j = i + 1; j < matrix[i].size(); ++j)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
	}
	float xian = matrix[0].size() / 2.0 - 0.5; //竖直中心对称线
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j <= xian; ++j)
		{
			int tmp = 2 * xian - j;
			swap(matrix[i][j], matrix[i][tmp]);
		}
	}
}

vector<vector<string>> groupAnagrams(vector<string>& strs)  //字母异位词分组
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
		sort(tmp.begin(), tmp.end());  //以排好序的为key值
		ifind = um.find(tmp);  //如果发现当前字符串排好的之后的key值存在，那么就把当前字符串插入，否则插入新key值
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

vector<int> spiralOrder(vector<vector<int>>& matrix)  //螺旋矩阵
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
	int direction[][2] = { {0,1},{1,0},{0,-1},{-1,0} };  //右->下->左->上->右。。。。
	while (s.size() < nm)
	{
		if (i >= matrix.size() || j >= matrix.at(0).size() || i < 0 || j < 0)  //如果超出范围，那么返回上次未超出范围的更换方向前进
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
		else  //如果当前坐标已经用了，那么返回上次刚插入的，换方向前进
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

bool canJump(vector<int>& nums)  //跳跃游戏--动态规划
{
	if (nums.size() <= 1)
	{
		return true;
	}
	if (nums[0] == 0)
	{
		return false;
	}
	vector<bool> flag(nums.size(), false);  //从0到当前的位置是否能走到,初始化走不到
	flag[0] = true;  //第0个位置肯定能走到
	for (int i=1; i<nums.size(); ++i)
	{
		for (int j=i-1; j>=0; --j)  //往当前位置找，如果之前有一个位置能到达，且从这个之前的位置最大走的步数大于等于之间的距离，那么当前位置能走到
		{
			if (flag[j] && nums[j] >= i - j)
			{
				flag[i] = true;
				break;  //只需要找到其中一种方式即可,所以直接break
			}
		}
	}
	return flag[nums.size() - 1];
}

vector<vector<int>> merge(vector<vector<int>>& intervals)  //合并区间
{
	if (intervals.size() <= 1)
	{
		return intervals;
	}
	//按照较小值的大小排起来，若相等就比较较大值
	//如果不排的话，会出现[2,3][5,7][3,5]的结果为[2,5][3,7]
	//排序是为了一点一点递增加空间,比如两个不相交区间后面有可以让两者联系起来的区间，那么这个联系区间肯定介于两者之间，所以排序后，可以让前面的先和这个联系区间合并，再跟后面的合并
	sort(intervals.begin(), intervals.end());  
	vector< vector<int> > result;
	result.push_back(intervals[0]);  //先把第一个插进去
	for (int i=1; i<intervals.size(); ++i)
	{
		vector<int> tmp = intervals[i];
		for (int j=0; j<result.size(); ++j)  //寻找已经插入的是否可以合并区间
		{
			if (tmp[1] < result[j][0] || tmp[0] > result[j][1])  //如果区间不存在重叠
			{
				if (j == result.size() - 1)  //如果当前已经是最后一个判断区间了
				{
					result.push_back(tmp); //直接插入
					break;
				}
				else
				{
					continue;  //如果不是最后一个判断区间，那么继续下一个区间判断按
				}
			}
			else
			{
				//合并区间
				result[j][0] = min(result[j][0], tmp[0]);
				result[j][1] = max(result[j][1], tmp[1]);
				break;  
				//合并之后这个就用了，所以break掉，
				//因为是排好序的，因此接下来的那个区间，如果有关系就可以合并，不需要再循环来看看下一个是否合并
				//因为如果与当前能合并的话，肯定不能跟当前区间的之前的和之后的无法合并
				//若能与前面的合并，那么排序的话就应该是待合并的区间在当前区间前面，而实际sort是相反的
				//同理与后面的一样
			}
		}
	}
	//以下为去重
	set< vector<int> > s;
	for (int i=0; i<result.size(); ++i)
	{
		s.insert(result[i]);
	}
	result.clear();
	result.assign(s.begin(), s.end());
	return result;
}

vector<vector<int>> generateMatrix(int n)  //螺旋矩阵 II
{
	if (n == 1)
	{
		return { {1} };
	}
	set< pair<int, int> > s;
	vector< vector<int> > result(n, vector<int>(n));
	int fangxiang = 0, i = 0, j = 0;
	int num = 1;
	int direction[][2] = { {0,1},{1,0},{0,-1},{-1,0} };  //右->下->左->上->右。。。。
	while(num <= n * n)
	{
		if (j < 0 || i < 0 || j >= n || i >= n)  //如果超过范围，就返回并选择下一个方向
		{
			i -= direction[fangxiang][0];
			j -= direction[fangxiang][1];
			fangxiang = (fangxiang >= 3 ? 0 : fangxiang + 1);
			i += direction[fangxiang][0];
			j += direction[fangxiang][1];
			continue;
		}
		pair<int, int> p(i, j); 
		if (s.find(p) != s.end())  //如果当前坐标已经用过，那么就转换方向
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

string getPermutation_item(string s)  //获取下一个数
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
string getPermutation(int n, int k)  //第k个排列
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

ListNode* rotateRight(ListNode* head, int k)  //旋转链表
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
	pre->next = head; //将最后一个元素的下一个指向开头
	int i = n - k;
	while (i > 1)  //因为已经成环了，所以这里要找到返回值的前一个元素,所以是>1
	{
		head = head->next;
		--i;
	}
	tmp = head;  //暂存这个前一个元素
	head = head->next;  //让head成为真正的返回值
	tmp->next = nullptr;  //将这个前一个元素的下一个为null，这样就不是环了
	return head;
}

int uniquePaths(int m, int n)  //不同路径
{
	if (m == 0 || n == 0)
	{
		return 0;
	}
	else if (m == 1 || n == 1)
	{
		return 1;
	}
	vector< vector<int> > dp(m, vector<int>(n));  //到ij坐标最多多少个路径
	for (int i=0; i<m; ++i)  //第0行只能一个路径
	{
		dp[i][0] = 1;
	}
	for (int j=0; j<n; ++j)  //第0列只能有一个路径
	{
		dp[0][j] = 1;
	}
	for (int i=1; i<m; ++i)
	{
		for (int j=1; j<n; ++j)
		{
			//由于只能向右和向下，因此每个坐标的路径，只能是左边一个或上边一个过来
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)  //不同路径 II--带障碍物--动态规划
{
	if (obstacleGrid.size() == 0)
	{
		return 0;
	}
	vector< vector<long int> > dp(obstacleGrid.size(), vector<long int>(obstacleGrid[0].size(), 0));
	if (obstacleGrid[0][0] == 0)  //如果第一个不为障碍物则为1，否则为0
	{
		dp[0][0] = 1;
	}
	for (int i=1; i<obstacleGrid.size(); ++i) 
	{
		//第0列，如果是障碍物的位置则为0，否则就只能是上边一个过来，左侧过来的为0，因此是dp[i - 1][0]+0
		if (obstacleGrid[i][0] == 0)
		{
			dp[i][0] = dp[i - 1][0];
		}
	}
	for (int j=1; j<obstacleGrid.at(0).size(); ++j)
	{
		//第0行，如果障碍物则为0，否则就只能是左边一个过来的，上面的过来为0，因此是dp[0][j - 1]+0
		if (obstacleGrid[0][j] == 0)
		{
			dp[0][j] = dp[0][j - 1];
		}
	}
	for (int i=1; i<obstacleGrid.size(); ++i)
	{
		for (int j=1; j<obstacleGrid.at(i).size(); ++j)
		{
			if (obstacleGrid[i][j] == 0)  //不为障碍物的话，等于左侧+上侧过来的总数
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
			else  //如果障碍物则为0
			{
				dp[i][j] = 0;
			}
		}
	}
	return dp[obstacleGrid.size() - 1][obstacleGrid.at(0).size() - 1];
}

int minPathSum(vector<vector<int>>& grid)  //最小路径和--动态规划
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
	//dp表示到达ij的最小和
	vector< vector<int> > dp(grid.size(), vector<int>(grid.at(0).size(), 0));
	dp[0][0] = grid[0][0];
	for (int i=1; i<grid.size(); ++i)
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];  //只能上侧过来，因此没有最小一说，只能相加
	}
	for (int j=1; j<grid.at(0).size(); ++j)
	{
		dp[0][j] = dp[0][j - 1] + grid[0][j];  //只能左侧过来，因此没有最小一说，只能相加
	}
	for (int i=1; i<grid.size(); ++i)
	{
		for (int j=1; j<grid.at(i).size(); ++j)
		{
			//只能是左侧和上侧移动过来，因此取最小的那个
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[grid.size() - 1][grid.at(0).size() - 1];
}

string simplifyPath(string path)  //简化路径
{
	stringstream is(path);   //作为输入流
	vector<string> strs;
	string res = "", tmp = "";
	while (getline(is, tmp, '/')) {  //依次查输入流的每个字符直到遇到/，然后进入循环执行结束后继续流
		if (tmp == "" || tmp == ".")  //跳过
			continue;
		else if (tmp == ".." && !strs.empty())  //..是返回上一级，因此要把里面的最后一个去掉
			strs.pop_back();
		else if (tmp != "..")  //添加进去
			strs.push_back(tmp);
	}
	for (string str : strs)
		res += "/" + str;
	if (res.empty())
		return "/";
	return res;
}

void setZeroes(vector<vector<int>>& matrix)  //矩阵置零
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
			if (matrix[i][j] == 0)  //等于0就加入这个行和列
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

bool searchMatrix(vector<vector<int>>& matrix, int target)  //搜索二维矩阵
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
	//整个为递增的
	int n = matrix.size(), m = matrix.at(0).size(), hang = 0;
	for (int i=0; i<n; ++i)  //先找到第几行
	{
		if (matrix[i][0] <= target && matrix[i][m - 1] >= target)
		{
			hang = i;
			break;
		}
	}
	vector<int> tmp = matrix[hang];
	int l = 0, r = m - 1;
	while (l <= r)  //二分查找
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

void sortColors(vector<int>& nums)  //颜色分类
{
	if (nums.size() <= 1)
	{
		return;
	}
	int l = 0, r = nums.size() - 1, index = 0; //l表示元素0的右哨兵边界，r表示元素2的左哨兵边界，index表示当前的元素
	while (index <= r)
	{
		if (nums[index] == 0)  //如果当前这个为0，那么就交换0的右边界哨兵和这个
		{
			swap(nums[index], nums[l]);
			//因为l哨兵肯定小于等于index，也就是说l哨兵已经扫描过了，所以交换后index的数不是0就是1，因此直接跳过即可
			//并且这里可以看到，l指向的值肯定是1，因为如果是0的话，那么当index指向这个0的时候，就已经都加一而跳过了.
			++index;
			++l;
		}
		else if (nums[index] == 2) //换过来之后index的值可能还为2，因此还需要继续判断当前值,所以index不动
		{
			swap(nums[index], nums[r]);
			--r;
		}
		else
		{
			index++;  //等于1直接跳过即可
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
		combine_item(n, k, v, i+1);  //下一次就从i+1开始
		v.pop_back();  //把用过的去掉
	}
}
vector<vector<int>> combine(int n, int k)  //组合
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
		subsets_item(nums, k, i + 1, v);  //当前位置加上后，再从下一个位置开始
		v.pop_back();
	}
}
vector<vector<int>> subsets(vector<int>& nums)  //子集
{
	if (nums.size() == 0)
	{
		return { {} };
	}
	sort(nums.begin(), nums.end());
	subsets_v.push_back({});
	for (int i=1; i<=nums.size(); ++i)
	{
		subsets_item(nums, i, 0, {});  //每次从下标0开始
	}
	return subsets_v;
}

int removeDuplicates(vector<int>& nums)  //删除排序数组中的重复项 II
{
	/*
	快指针：遍历整个数组；
	慢指针：记录可以覆写数据的位置；
	题目中规定每个元素最多出现两次，
	因此，应检查快指针指向的元素和慢指针指针所指向单元的前一个元素是否相等。
	相等则不更新慢指针，只更新快指针；
	不相等时，先将慢指针后移一位，再将快指针指向的元素覆写入慢指针指向的单元，最后更新快指针
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

bool search_1(vector<int>& nums, int target)  //搜索旋转排序数组 II--一趟搜索竟然不慢
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

bool search_2(vector<int>& nums, int target)  //搜索旋转排序数组 II--二分查找
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
		if (nums[l] < nums[mid])   //在l到mid为升序
		{
			if (target > nums[mid] || nums[l] > target)  //如果不在这部分区间，那么直接跳过
			{
				l = mid + 1;
			}
			else
			{
				r = mid - 1;
			}
		}
		else  //后半部分有序
		{
			if (target > nums[r] || target < nums[mid])  //如果不在这部分区间，直接跳过
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

ListNode* deleteDuplicates(ListNode* head) //删除排序链表中的重复元素 II
{
	if (!head || !head->next)
	{
		return head;
	}
	//先找头
	if (head->val != head->next->val)  //如果与头指针值与第二个不同，那么头指针就是返回值的第一个元素
	{
		head = head;
	}
	else  //如过第一个与第二个一样，那么三个指针，pre，now（head），next(n)
	{
		ListNode *pre = head;
		head = head->next;
		ListNode* n = head->next;
		//只要存在pre->val = now->val 或者now->val = n->val，就说明当前这个now不是唯一的，因此不能当头元素
		while ( pre && head && n && (pre->val == head->val || head->val == n->val))
		{
			pre = pre->next;
			head = head->next;
			n = n->next;
		}
		if (!n)  //如果此时n到了null元素了，也就是说之前的元素不满足唯一，此时head就是最后一个元素
		{
			if (head->val != pre->val)  //如果最后一个不等于前一个，那么此时只有最后一个元素满足要求，因此直接返回
			{
				return head;
			}
			else  //如果相等的话，说明最后一个元素与倒数第二个元素相等，因此此时没有满足的元素，直接返回
			{
				return nullptr;
			}
		}
	}
	ListNode* tmp = head;  //头元素
	ListNode* result = tmp;  //返回结果
	ListNode* x = head;  //相当于pre
	head = head->next;  //相当于now
	ListNode* y = head->next;  //相当于next
	while (x && head && y)
	{
		if (x->val != head->val && head->val != y->val)  //如果一个值满足唯一，那么就接入到结果中
		{
			tmp->next = head;
			tmp = tmp->next;
		}
		//向后移动
		x = x->next;
		head = head->next;
		y = y->next;
	}
	//退出while时候，最后一个元素还未判断
	if (head->val != x->val)  //最后一个元素不等于倒数第二个，那么最后一个肯定要加入
	{
		tmp->next = head;
		tmp = tmp->next;
		tmp->next = nullptr;
	}
	else  //如果最后一个等于倒数第二个，那么直接不要了，直接等于null
	{
		tmp->next = nullptr;
	}
	return result;
}

ListNode* partition(ListNode* head, int x)  //分隔链表
{
	if (!head)
	{
		return head;
	}
	//初始化，t1表示小于x的，t2表示大于等于x的
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
	t2->next = nullptr;  //最后的话t2的后面应该置为nullptr
	t = t->next;  //跳过初始化的那个
	t1->next = t; //将t1的后面接上t
	return result->next;  //跳过初始化那个，然后返回
}

vector<int> grayCode(int n)  //格雷编码
{
	if (n == 0)
	{
		return { 0 };
	}
	else if (n >= 25)
	{
		return {};
	}
	//已知n-1的编码，那么n的编码，就是对n-1的编码倒序遍历，每个元素的二进制在后面添上1(也就是乘2加1)后push_back,并且把当前遍历到的这个二进制后面直接添0(也就是乘2)覆盖原值
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
		v.push_back(nums[i]);  //添加当前元素
		subsetsWithDup_item(nums, k, i + 1, v);  //从下一个元素开始
		v.pop_back();
	}
}
vector<vector<int>> subsetsWithDup(vector<int>& nums)  //子集 II
{
	if (nums.size() == 0)
	{
		return { {} };
	}
	sort(nums.begin(), nums.end());
	for (int i=1; i<=nums.size(); ++i)  //多个深度优先搜索
	{
		subsetsWithDup_item(nums, i, 0, {});
	}
	vector< vector<int> > result;
	result.assign(subsetsWithDup_s.begin(), subsetsWithDup_s.end());
	return result;
}

int numDecodings(string s)  //解码方法--动态规划
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
	vector<int> dp(s.size(), 0);  //截至到下标为i的字符得到的总数
	dp[0] = 1;
	//处理dp[1]的时候
	if (s[1] == '0') //当第二个字符为0的时候，只能跟前一个字符放在一起看
	{
		if (s[0] == '1' || s[0] == '2')  //如果前一个字符为1或2，那么只能是10或20，只有一个，否则就没有,整个字符串就没有，直接返回
		{
			dp[1] = 1;
		}
		else 
		{
			dp[1] = 0;
			return 0;
		}
	}
	else //如果s[1]不为0
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
		//下标第i个为0，那么只能与前一个合并起来看，
		//如果前一个1或2，那么就前i-2个的所有组合，再直接在后面加上合并起来的数
		//否则为0
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
		else  //如果不为0的话
		{
			if (s[i - 1] == '1')
			{
				//那么就是下标前i-1个组合后在后面加上下标第i个数
				//或者后两个组合起来，在下标前i-2个组合后加在后面
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			else if(s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6')
			{
				//同理上面的s[i-1] = '1'
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			else
			{
				//这样的话就只能把下标第i个数单独看，当下标前i-1个数组合后，加在后面
				dp[i] = dp[i - 1];
			}
		}
	}
	return dp[s.size() - 1];
}

ListNode* reverseBetween(ListNode* head, int m, int n)  //反转链表 II
{
	if (!head || m == n)
	{
		return head;
	}
	ListNode* t1 = new ListNode(0); //用来表示反转部分
	ListNode* result = head;
	ListNode* t2 = head;   //表示反转部分的前一个
	int flag = m;  //保存m的值
	while (m > 1)  //一直到反转部分的第一个结束
	{
		if (m == 2)
		{
			t2 = head;  //记录反转部分的前一个
		}
		head = head->next;
		--m;
		--n;
	}
	ListNode* t = head;  //记录反转部分的第一个，也就是反转后的最后一个
	while (n > 0)
	{
		ListNode* tmp = head;  //保存当前元素
		head = head->next;  //指向下一个
		tmp->next = t1;  //将当前元素的下一个指向前面那个，也就是反转过来
		t1 = tmp;  //将他指向反转后的前一个元素，以便当作接下来head的后一个元素，也就是反转
		--n;
	}
	t->next = head;  //反转后的最后一个的下一个要指向经过反转区后的第一个
	if (flag == 1)
	{
		return t1;  //如果要反转的包括第一个，那么直接返回反转后的反转区第一个
	}
	else
	{
		t2->next = t1;  //否则，就将反转区的前一个的下一个指向反转后的第一个
	}
	return result;  //返回结果
}

vector<string> restoreIpAddresses_v;
void restoreIpAddresses_item(int n, string s, string ip)
{
	if (n == 4)  //如果用到第4个. 
	{
		if (s.size() == 0)  //如果输入的string都用了，那么加入
		{
			restoreIpAddresses_v.push_back(ip);
		}
		return;
	}
	else if (n > 4)
	{
		return;
	}
	for (int i=1; i<4; ++i)  //两个点之间的数从1-3个
	{
		if (s.size() < i)  //如果剩余字符串的个数不足以加入到ip字符串中，那么直接break
		{
			break;
		}
		int val = std::stoi(s.substr(0, i));  //从剩余字符串中从下标0开始截取i个并转换为int
		if (val > 255 || i != std::to_string(val).size())  //如果截取的大于255，或者截取的字符串个数不等于当前需要的个数，继续下一个
		{
			continue;
		}
		//递归，用到了第n+1个点，剩余字符串为从下标第i到最后(因为从0-i用了)，ip加上从0到i的字符，如果n=3，说明用了3个了，因此不加点了，否则就加
		restoreIpAddresses_item(n + 1, s.substr(i), ip + s.substr(0, i) + (n == 3 ? "" : "."));
	}
}
vector<string> restoreIpAddresses(string s)  //复原IP地址
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
vector<int> inorderTraversal_1(TreeNode* root)  //二叉树的中序遍历--递归
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
vector<int> inorderTraversal_2(TreeNode* root)  //二叉树的中序遍历--迭代
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
		vector<TreeNode*> lTrees = generateTrees_item(zuixiao, i - 1);  //所有满足条件的左子树
		vector<TreeNode*> rTrees = generateTrees_item(i + 1, zuida);  //所有满足条件的右子树
		for (TreeNode* l : lTrees)
		{
			for (TreeNode* r : rTrees)
			{
				TreeNode* root = new TreeNode(i);  //这个必须加在这里，不能在lTrees上面，因为如果在那个上面，就相当于对同一个root反复修改其左右子树，最后pushback的只有修改到最后的一个,因此这里需要每次新建
				root->left = l;
				root->right = r;
				result.push_back(root);
			}
		}
	}
	return result;
}
vector<TreeNode*> generateTrees(int n)  //不同的二叉搜索树 II
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
int numTrees_1(int n)  //不同的二叉搜索树--递归超时了
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

int numTrees_2(int n)  //不同的二叉搜索树--动态规划
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	//定义序列长度为i的个数，result[i],因为是长度为i，所以4567这个也是result[4],1234也是result[4]
	//以i为根的话，个数就是[1, i-1]的个数与[i+1, n]的个数的乘积
	//那么把所有i从1到n的个数相加就是结果
	vector<int> result(n + 1, 0);
	result[0] = 1;
	result[1] = 1;
	for (int i=2; i<=n; ++i)  //个数依次为2-n
	{
		//当i个数时，以j为根的个数为result[j - 1] * result[i - j],把从1到i的所有当作根，累加就是i个数时的结果
		for (int j=1; j<=i; ++j)  //从1到i依次为根
		{
			result[i] += result[j - 1] * result[i - j];
		}
	}
	return result[n];
}

int numTrees_3(int n)  //不同的二叉搜索树--卡特兰数
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

vector<vector<int>> zigzagLevelOrder(TreeNode* root)  //二叉树的锯齿形层次遍历
{
	if (!root)
	{
		return {};
	}
	vector< vector<int> > result;
	bool flag = false;  //当前层是否是从右边往左走的
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())  //本质上是层次遍历，因此要用两个while
	{
		vector<int> tmp;
		int i = q.size();  //当前层元素个数
		flag = !flag;  //当前层与上一层相反
		stack<TreeNode*> s;  //记录下一层的顺序
		while (i > 0)
		{
			root = q.front();
			q.pop();
			tmp.push_back(root->val);
			//把下一层按照顺序添加进stack中
			if (flag)  //此层从右往左走，所以对于stack要先添加左边的
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
			else  //否则先添加右子树
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
		while (!s.empty())  //把下一层的加入进queue中，这里的stack已经保证了正确是顺序
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
	//前序遍历的第一个是当前树的根节点，
	//此根节点在中序遍历的位置的左侧为左子树，右侧为右子树
	//这样就循环递归下去就可以
	if (preorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(preorder[0]);  //当前根节点为前序遍历的第一个
	vector<int>::iterator ifind = find(inorder.begin(), inorder.end(), preorder[0]);  //在中序遍历中寻找根节点元素
	if (ifind == inorder.end())  //如果没有，就说明不能成为二叉树
	{
		return nullptr;
	}
	vector<int> inorder_left;  //中序遍历的左子树部分
	inorder_left.assign(inorder.begin(), ifind);  //应该是中序序列的第一个到根节点的前一个
	vector<int> inorder_right;  //中序遍历的右子树部分
	inorder_right.assign(++ifind, inorder.end()); //应该是中序序列的根节点后一个到最后
	vector<int> preorder_left;  //先序遍历的左子树部分
	vector<int> preorder_right;  //先序遍历的右子树部分
	//显然有中序遍历的左(右)子树部分的个数，与先序遍历的左(右)子树部分的个数分别相同，
	//即inorder_left.size = preorder_left.size, inorder_right.size = preorder_right.size
	//因为他们都是此时根节点的左(右)子树的所有元素，
	//而且在先序遍历中，第一个为根元素，然后是左子树的所有元素，然后是右子树的所有元素
	//那么也就是说，从先序遍历中的根节点后面的一个往后拿出inorder_left.size()个数个元素，
	//就是preorder_left的元素，同理剩下的为preorder_right的元素
	preorder_left.assign(preorder.begin() + 1, preorder.begin() + 1 + inorder_left.size());
	preorder_right.assign(preorder.begin() + 1 + inorder_left.size(), preorder.end());
	TreeNode* l = buildTree_item(preorder_left, inorder_left);
	TreeNode* r = buildTree_item(preorder_right, inorder_right);
	root->left = l;
	root->right = r;
	return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)  //从前序与中序遍历序列构造二叉树
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
	TreeNode* root = new TreeNode(postorder[postorder.size() - 1]); //后序遍历最后一个元素为当前的根元素
	vector<int>::iterator ifind = find(inorder.begin(), inorder.end(), postorder[postorder.size() - 1]);
	vector<int> inorder_left;
	vector<int> inorder_right;
	inorder_left.assign(inorder.begin(), ifind);  //中序序列根元素左侧为左子树
	inorder_right.assign(++ifind, inorder.end());  //中序序列的根元素右侧为右子树
	vector<int> postorder_left;
	vector<int> postorder_right;
	//后序遍历序列，前inorder_left.size()个元素为左子树元素，后面的除去最后一个剩下的为右子树元素
	postorder_left.assign(postorder.begin(), postorder.begin() + inorder_left.size());
	postorder_right.assign(postorder.begin() + inorder_left.size(), postorder.end() - 1);
	TreeNode* l = buildTree_item(inorder_left, postorder_left);
	TreeNode* r = buildTree_item(inorder_right, postorder_right);
	root->left = l;
	root->right = r;
	return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)  //从中序与后序遍历序列构造二叉树
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
	//给定列表中的中间元素将会作为二叉搜索树的根，
	//该点左侧的所有元素递归的去构造左子树，
	//同理右侧的元素构造右子树。这必然能够保证最后构造出的二叉搜索树是平衡的
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
TreeNode* sortedListToBST(ListNode* head)  //有序链表转换二叉搜索树
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
	if (!root)  //为空，则肯定不是叶子节点
	{
		return;
	}
	tmp.push_back(root->val);
	if (target == root->val && !root->left && !root->right)  //target的值等于当前节点值，且为叶子节点
	{
		pathSum_v.push_back(tmp);  //那么就加入结果
		return;
	}
	pathSum_item(root->left, target - root->val, tmp); //递归查找左子树
	pathSum_item(root->right, target - root->val, tmp);  //递归查找右子树
}
vector<vector<int>> pathSum(TreeNode* root, int sum)  //路径总和 II
{
	if (!root)
	{
		return {};
	}
	pathSum_item(root, sum, {});
	return pathSum_v;
}

void flatten(TreeNode* root)  //二叉树展开为链表--先序遍历
{
	if (!root)
	{
		return;
	}
	stack<TreeNode*> s;
	TreeNode* tmp = new TreeNode(0);
	TreeNode* result = tmp;
	s.push(root);
	while (!s.empty())  //先序遍历，然后按着顺序把上一个的右子树指向遍历到的这个
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
Node* connect(Node* root)  //填充每个节点的下一个右侧节点指针
{
	//根据锯齿状遍历呀，
	if (!root)
	{
		return nullptr;
	}
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		int i = q.size();
		if (i == 1)  //根节点时候
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
		//非根节点
		Node* t1 = q.front();  //先拿出第一个作为慢指针  
		q.pop();
		--i;  //减去数量
		if (t1->left)  //加入左右指针
		{
			q.push(t1->left);
		}
		if (t1->right)
		{
			q.push(t1->right);
		}
		while (i > 0) //由于i>1，所以这里肯定能进入
		{
			Node* t2 = q.front();  //当前指针
			q.pop();
			if (t2->left)  //加入左右子指针
			{
				q.push(t2->left);
			}
			if (t2->right)
			{
				q.push(t2->right);
			} 
			t1->next = t2;  //慢指针的下一个指向当前指针
			t1 = t2;  //更新慢指针为当前指针，等待下一次使用
			--i;  //数量减
		}
		t1->next = nullptr;  //最后一个指针的下一个指向nullptr
	}
	return root;  //因为这个题是完美二叉树，而root只在i=1时用的，所以root永远指向根节点
}

Node* connect(Node* root)  //填充每个节点的下一个右侧节点指针 II
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
		if (i == 1)  //根节点时候
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
		//非根节点
		Node* t1 = q.front();  //先拿出第一个作为慢指针  
		q.pop();
		--i;  //减去数量
		if (t1->left)  //加入左右指针
		{
			q.push(t1->left);
		}
		if (t1->right)
		{
			q.push(t1->right);
		}
		while (i > 0) //由于i>1，所以这里肯定能进入
		{
			Node* t2 = q.front();  //当前指针
			q.pop();
			if (t2->left)  //加入左右子指针
			{
				q.push(t2->left);
			}
			if (t2->right)
			{
				q.push(t2->right);
			}
			t1->next = t2;  //慢指针的下一个指向当前指针
			t1 = t2;  //更新慢指针为当前指针，等待下一次使用
			--i;  //数量减
		}
		t1->next = nullptr;  //最后一个指针的下一个指向nullptr
	}
	//因为此题不是完美二叉树，可能出现只有一个孩子的情况，
	//所以root会被使用很多次，所以会变，所以得用result保存刚开始的root
	return result;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList)  //单词接龙
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
	for (string s : wordList)  //构造邻接表
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
	if (flag)  //如果worlist里面没有endword，那么返回0
	{
		return 0;
	}
	queue< pair<string, int> > q;
	map<string, bool> visited;
	q.push(pair<string, int>(beginWord, 1));
	int n = beginWord.size();
	while (!q.empty())  //广度优先搜索
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
	if (!root->left && !root->right)  //如果是叶子节点，那么就加入进去，这条路径就结束了
	{
		sum = sum * 10 + root->val;
		tmp.push_back(sum);
		return;
	}
	sum = sum * 10 + root->val;
	if (root->left)
	{
		sumNumbers_item(root->left, sum, tmp);  //往左延伸路径
	}
	if (root->right)
	{
		sumNumbers_item(root->right, sum, tmp);  //往右延伸路径
	}
}
int sumNumbers(TreeNode* root)  //求根到叶子节点数字之和
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

void solve(vector<vector<char>>& board)  //被围绕的区域
{
	if (board.size() == 0 || board[0].size() == 0)
	{
		return;
	}
	int n = board.size(), m = board[0].size();
	vector<int> parent(n * m, -1);
	set<int> s;  //记录O且是在边缘的索引
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<m; ++j)
		{
			if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && board[i][j] == 'O')
			{
				s.insert(i * m + j);  //插入数据
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
			while (rootx != parent[rootx])  //当前O位置的老大
			{
				rootx = parent[rootx];
			}
			for (int k=0; k<4; ++k)  //四个方向各找
			{
				int x = i + direction[k][0], y = j + direction[k][1];
				if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 'O')
				{
					int rooty = parent[x * m + y];
					while (rooty != parent[rooty])
					{
						rooty = parent[rooty];
					}
					if (rootx != rooty)  //如果老大不同
					{
						if (s.find(rooty) == s.end())  //如果rooty是属于O且边缘的，那么应该让他当老大
						{
							parent[rooty] = rootx;
						}
						else  //否则就是rootx老大
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
			while (root != parent[root])   //寻找当前老大
			{
				root = parent[root];
			}
			if (s.find(root) == s.end())  //如果老大在s里面
			{
				board[i][j] = 'X';
			}
		}
	}
}

vector< vector<string> > partition_v;
bool isHuiWenChuan(string s)  //判断是否是回文串
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
	if (s.size() == 0)  //如果剩下的size为0，那么就加入
	{
		if (tmp.size() > 0)
		{
			partition_v.push_back(tmp);
		}
		return;
	}
	for (int i=1; i<=s.size(); ++i)  //从s中分割出i个长度的字符串
	{
		string newString = s.substr(0, i);
		if (isHuiWenChuan(newString))   //如果是回文串，就说明此次分割有效，那么继续剩下字符串的分割，否则就剪枝
		{
			tmp.push_back(newString);
			partition_item(s.substr(i), tmp);
			tmp.pop_back();  //将前面分割的去掉，继续分割i+1个试试
		}
	}
}
vector<vector<string>> partition(string s)  //分割回文串
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
Node* cloneGraph(Node* node)  //克隆图
{
	if (!node)
	{
		return nullptr;
	}
	if (cloneGraph_m.count(node)) //如果已经有了这个克隆了，直接返回
	{
		return cloneGraph_m[node];
	}
	Node* result = new Node(node->val);
	cloneGraph_m[node] = result;
	for (Node* nei : node->neighbors)
	{
		if (nei)
		{
			Node* tmp = cloneGraph(nei); //返回每个邻居的克隆
			result->neighbors.push_back(tmp);
		}
	}
	return result;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost)  //加油站
{
	if (gas.size() == 0 || cost.size() == 0)
	{
		return -1;
	}
	if (gas.size() != cost.size())
	{
		return -1;
	}
	vector<int> dp(gas.size(), 0); //表示i出发到i+1(不在i+1加油)油的实际获得量
	for (int i = 0; i < gas.size(); ++i)
	{
		dp[i] = gas[i] - cost[i];
	}
	bool flag = true; //是否有成功的
	int result = -1;
	for (int i = 0; i < dp.size(); ++i)
	{
		if (dp[i] >= 0)  //刚开始出发的必须要能到达第i+1站，因此要大于等于0
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
			if (!flag)  //从i到最后一个是满足要求的
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
			if (flag)  //从0到i也是满足要求的，加上上面的，因此整个循环是满足要求的
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
map<Node*, Node*> copyRandomList_m;  //指针与拷贝一一对应
Node* copyRandomList(Node* head)  //复制带随机指针的链表
{
	if (!head)  //如果null，那么返回null
	{
		return nullptr;
	
	}
	if (copyRandomList_m.count(head))  //如果存在了，就直接返回拷贝
	{
		return copyRandomList_m[head];
	}
	Node* result = new Node(head->val);  //创建拷贝
	copyRandomList_m[head] = result;  //加入一一对应关系
	Node* n = copyRandomList(head->next);  //递归进行下一个
	Node* r = copyRandomList(head->random);  //递归进行随机指针
	result->next = n;  //赋值
	result->random = r; //赋值
	return result;  //返回结果
}

bool wordBreak_item(string s, vector<string>& wordDict)
{
	if (s.size() == 0)
	{
		return true;
	}
	bool flag = false;
	for (string word : wordDict)   //遍历单词表
	{
		if (s.size() < word.size())  //如果s的长度小，说明此时的单词肯定不行
		{
			continue;
		}
		string tmp = s;  //每次循环得需要传过来的s，所以得暂存,否则下一个单词时候就是截取了的字符串里
		string newString = tmp.substr(0, word.size());  //对tmp截取根word一样长的字符串
		if (newString == word)  //如果相等继续操作，否则剪枝看看下一个单词
		{
			while (newString.size() == word.size() && newString == word)  //循环，既然截取后与单词相等，那么就要一直循环把相等的去掉,是为了减少时间,否则会超时
			{
				tmp = tmp.substr(word.size());
				newString = tmp.substr(0, word.size());
			}
			bool t = wordBreak_item(tmp, wordDict);  //剩下不相等的，递归看看其他单词是否可以
			if (t)  //如果有一个成功，就返回就可以了
			{
				flag = true;
				break;
			}
		}
	}
	return flag;
}
bool wordBreak(string s, vector<string>& wordDict)  //单词拆分
{
	return wordBreak_item(s, wordDict);
}

void reorderList(ListNode* head)  //重排链表
{
	if (!head)
	{
		return;
	}
	vector<ListNode*> tmp;  //保存所有节点
	int n = 0;
	while (head)
	{
		++n;
		tmp.push_back(head);
		head = head->next;
	}
	int t = n - 1;
	n % 2 == 0 ? n /= 2 : n = n / 2 + 1;  //如果是偶数个，那么只需遍历前n/2个，否则需要遍历到第n/2+1个，并且中间那个需要特殊处理
	ListNode* result = new ListNode(0);
	ListNode* temp = result;
	for (int i = 0; i < n; ++i)
	{
		if (t - i == i)  //中间的那个特殊处理
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
	result->next = nullptr;  //最后一个需要指向null
	head = temp->next;
}

vector<int> preorderTraversal(TreeNode* root)  //二叉树的前序遍历--迭代
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
vector<int> preorderTraversal_1(TreeNode* root)  //二叉树的前序遍历--递归
{
	if (!root)
	{
		return {};
	}
	vector<int> result;
	preorderTraversal_1_item(root, result);
	return result;
}

ListNode* insertionSortList(ListNode* head)  //对链表进行插入排序
{
	if (!head)
	{
		return nullptr;
	}
	ListNode* preHead = new ListNode(0);  ////哨兵节点
	ListNode* cur = head;
	ListNode* pre = preHead;  
	ListNode* n = nullptr;  //下一个指针
	while (cur)
	{
		n = cur->next;
		while (pre->next && pre->next->val < cur->val)  //如果pre的下一个小于当前值，一直找到比当前值大的
		{
			pre = pre->next;
		}
		cur->next = pre->next;  //当前值的下一个就是第一个比他大的
		pre->next = cur;  //前一个指向当前值
		pre = preHead;  //再重新开始
		cur = n;
	}
	return preHead->next;
}


ListNode* sortList(ListNode* head)  //排序链表--归并排序
{
	//在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序
	if (!head)
	{
		return nullptr;
	}
	if (!head->next)
	{
		return head;
	}
	ListNode* slow = head;
	ListNode* fast = head->next;  //快慢指针
	while (fast && fast->next)  //直到slow到达中点，fast->next到达了终点
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	ListNode* mid = slow->next;  //mid为后半程的起点
	slow->next = nullptr;  //slow代表的中点下一个为null
	slow = head;  //前半段开始
	slow = sortList(slow);  //排序好前面的
	mid = sortList(mid);  //排序好后面的
	ListNode* result = new ListNode(0);  //哨兵
	ListNode* t = result;  //记录哨兵
	//下面是合并操作
	while (slow || mid)  //合并操作
	{
		if (slow && mid)  //如果两者都有，则较小的上去
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
		else if (slow && !mid)  //只有slow，整体分别加入到后面
		{
			result->next = slow;
			slow = slow->next;
		}
		else  //只有mid，整体加入后面
		{
			result->next = mid;
			mid = mid->next;
		}
		result = result->next;
	}
	result->next = nullptr;  //最后一个下一个指向null
	return t->next;  //返回哨兵后边的实际
}

int evalRPN(vector<string>& tokens)  //逆波兰表达式求值
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

string reverseWords(string s)  //翻转字符串里的单词
{
	if (s.size() == 0)
	{
		return "";
	}
	int n = s.size();
	string result;
	int i = 0;
	while (i < n)  //遍历
	{
		while (i < n && s[i] == ' ')  //如果是空格，就跳过
		{
			++i;
		}
		if (i == n)  //如果一直到最后一个是空格，就直接break
		{
			break;
		}
		string tmp;
		while (i < n && s[i] != ' ')  //从不是空格的开始，直到遇到空格
		{
			tmp += s[i];
			++i;
		}
		result = tmp + ' ' + result;  //加入进结果
	}
	while (result[result.size() - 1] == ' ')  //把多的空格删除掉
	{
		result.pop_back();
	}
	return result;
}

int findMin(vector<int>& nums)  //寻找旋转排序数组中的最小值
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
		if (nums[l] <= nums[mid]) //l->mid为升序
		{
			result = min(nums[l], result);
			l = mid + 1;
		}
		else //mid->r为升序
		{
			result = min(result, nums[mid]);
			r = mid - 1;
		}
	}
	return result;
}

int findPeakElement(vector<int>& nums)  //寻找峰值
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
	while (l <= r)  //二分法
	{
		//如果mid大于mid+1的话，说明峰值在mid和其左侧，否则就是在右侧
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

int compareVersion(string version1, string version2)  //比较版本号
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
		while (i < version1.size())  //一直循环到点结束
		{
			if (version1[i] == '.')
			{
				break;
			}
			s1 += version1[i];
			++i;
		}
		while (j < version2.size())  //一直循环到点结束
		{
			if (version2[j] == '.')
			{
				break;
			}
			s2 += version2[j];
			++j;
		}
		if (s1.size() == 0 && s2.size() > 0)  //如果没有了，就是说i到头了
		{
			y = std::stoi(s2);
			if (y > 0)  //如果v2剩下的大于0，如1和1.1就说明v2大
			{
				return -1;
			}
		}
		else if (s1.size() > 0 && s2.size() == 0)  //如果没有了，就是j到头了
		{
			x = std::stoi(s1);
			if (x > 0)  //如果v1剩下的大于0，如1.1和1，就是v1大
			{
				return 1;
			}
		}
		else if (s1.size() == 0 && s2.size() == 0)  //如果都没有了，就直接返回0
		{
			return 0;
		}
		else  //如果都有的话
		{
			x = std::stoi(s1);
			y = std::stoi(s2);
			if (x > y)  //如果x>y,就是v1大
			{
				return 1;
			}
			else if (x < y) //如果y>x，就是v2大
			{
				return -1;
			}
			//这里省略了相等情况，就得继续比较后面的
		}
		//跳过点
		++i;
		++j;
	}
	return 0;
}

string fractionToDecimal(int numerator, int denominator)  //分数到小数
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
	result.push_back('.');  //不整除的话就是小数，就应该插入小数点
	unordered_map<int, int> um;  //记录重复余数的下标,这里不能记录结果中的数字出现坐标，因为比如1.255，这里不是循环小数，但是要记录5的话，就成了循环小数，应该是记录除法中余数的出现
	int index = result.size() - 1;
	while (num && um.count(num) == 0)  //如果num不为0，且之前没出现过
	{
		++index;  //下标指向哨兵
		um[num] = index;  //插入这个
		num *= 10;
		result += std::to_string(num / den);
		num %= den;
	}
	if (um.count(num) == 1)  //如果出现过这个数，那么在它位置上插入(
	{
		result.insert(um[num], "(");
		result.push_back(')');
	}
	return result;
}

class BSTIterator {   //二叉搜索树迭代器
public:
	vector<int> tmp;
	int index = -1;  //表示已经用过的数
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

		return tmp[++index];  //因为index表示已经用过的数，因此要先++
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		if (index + 1 < tmp.size())  //因为index表示已用过的数，因此要看看index+1是否还有吗
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

static bool largestNumber_compare(string s1, string s2)  //返回s1>s2 ?
{
	if (s1.size() == 0)  //如果s1为空的，那么直接返回s2
	{
		return false;
	}
	if (s2.size() == 0)  //如果s2为空的，直接返回s1
	{
		return true;
	}
	if (s1.size() == 1 && s2.size() == 1)  //都为1个，那么返回较大的那个
	{
		int x = s1[0] - '0', y = s2[0] - '0';
		return (x > y);
	}
	int i = 0, j = 0;
	while (i < s1.size() || j < s2.size())  //遍历所有的字符串
	{
		////如果此时i超过了最大下标，那么从0开始，
		//这里必须要说一下，假设234与2344比较的话，肯定是2344234大于2342344，
		//也就是说如果某一个字符串遍历到最后了，还没分出大小的话(这里234到最后了)，此时i=2,j=2
		//接下来要比较2344中的j=3也就是4和i=0的大小，谁大谁就在前面
		//上面的2344中的4大于234中的2，因此2344大于234
		//再假设543，5432，肯定是5435432大于5432543，也就是当543到达3(i=2)时，5432此时也到达3(j=2)，
		//那么很显然此时，要不就是543加入到5432后面，要不就是5432加入到543后面，前面的三位是543是相同的
		//那么第四位肯定是较大的一个，而这个第四位，
		//要不就是还剩下字符的那个(5432)的下一位(2)，此时是543放在5432的后面5432543，
		//要不就是还剩下字符的那个(5432)的第一位(5)，也就是5432放在543的后面，而由于当前位的前面所有位都是相同的，因此也就是用完字符的那个的第一位
		//如果此时还未分出胜负，则还是要i++,j++，直到分出胜负,
		//此时还要说明的是，比如11和111，是不是就一直循环了呢，显然由于i和j的变换不同步，总会退出循环的
		//自己可以按照代码试试这个例子
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
string largestNumber(vector<int>& nums)  //最大数
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
	sort(tmp.begin(), tmp.end(), largestNumber_compare);  //按照自定义排序
	if (tmp[0] == "0")
	{
		return "0";
	}
	//sort后会得到[1,102,21]->[21, 102, 1],直接组合起来就行
	for (string s : tmp)  //组合
	{
		result += s;
	}
	while (result[0] == '0' && result.size() > 1)  //除掉result前面的0
	{
		result = result.substr(1);
	}
	return result;
}

int main()
{
	//两数相加
	//addTwoNumbers

	//无重复字符的最长子串
	//lengthOfLongestSubstring

	//两两交换链表中的节点
	//swapPairs

	//环形链表 II
	//detectCycle_1

	//三数之和
	//threeSum

	//验证二叉搜索树
	//isValidBST

	//二叉树的最近公共祖先
	//lowestCommonAncestor

	//Pow(x, n)
	//myPow

	//求众数 II
	//majorityElement

	//二叉树的层次遍历
	//levelOrder

	//括号生成
	//generateParenthesis

	//找到字符串中所有字母异位词
	//findAnagrams

	//有效的数独
	//isValidSudoku

	//实现 Trie (前缀树)
	//Trie

	//单词搜索
	//exist

	//比特位计数
	//countBits

	//三角形最小路径和
	//minimumTotal

	//乘积最大子序列
	//maxProduct

	//最佳买卖股票时机含冷冻期
	//maxProfit_cooldown

	//最长上升子序列
	//lengthOfLIS

	//零钱兑换
	//coinChange

	//岛屿数量
	//numIslands

	//朋友圈
	//findCircleNum

	//LRU缓存机制
	//class LRUCache

	//最长回文子串
	//longestPalindrome

	//Z 字形变换
	//convert

	//字符串转换整数 (atoi)
	//myAtoi

	//盛最多水的容器
	//maxArea

	//整数转罗马数字
	//intToRoman

	//最接近的三数之和
	//threeSumClosest

	//电话号码的字母组合
	//letterCombinations

	//四数之和
	//fourSum

	//删除链表的倒数第N个节点
	//removeNthFromEnd

	//两数相除
	//divide

	//下一个排列
	//nextPermutation

	//搜索旋转排序数组
	//search

	//在排序数组中查找元素的第一个和最后一个位置
	//searchRange

	//组合总和
	//combinationSum

	//组合总和 II
	//combinationSum2

	//字符串相乘
	//multiply

	//全排列
	//permute

	//全排列 II
	//permuteUnique

	//旋转图像
	//rotate

	//字母异位词分组
	//groupAnagrams

	//螺旋矩阵
	//spiralOrder

	//跳跃游戏
	//canJump

	//合并区间
	//merge

	//螺旋矩阵 II
	//generateMatrix

	//第k个排列
	//getPermutation

	//旋转链表
	//rotateRight

	//不同路径
	//uniquePaths

	//不同路径 II
	//uniquePathsWithObstacles

	//最小路径和
	//minPathSum

	//简化路径
	//simplifyPath

	//矩阵置零
	//setZeroes

	//搜索二维矩阵
	//searchMatrix

	//颜色分类
	//sortColors

	//组合
	//combine

	//子集
	//subsets

	//删除排序数组中的重复项 II
	//removeDuplicates

	//搜索旋转排序数组 II
	//search

	//删除排序链表中的重复元素 II
	//deleteDuplicates

	//分隔链表
	//partition

	//格雷编码
	//grayCode

	//子集 II
	//subsetsWithDup

	//解码方法
	//numDecodings

	//反转链表 II
	//reverseBetween

	//复原IP地址
	//restoreIpAddresses

	//二叉树的中序遍历
	//inorderTraversal

	//不同的二叉搜索树 II
	//generateTrees

	//不同的二叉搜索树
	//numTrees

	//二叉树的锯齿形层次遍历
	//zigzagLevelOrder

	//从前序与中序遍历序列构造二叉树
	//buildTree

	//从中序与后序遍历序列构造二叉树
	//buildTree

	//有序链表转换二叉搜索树
	//sortedListToBST

	//路径总和 II
	//pathSum

	//二叉树展开为链表
	//flatten

	//填充每个节点的下一个右侧节点指针
	//connect

	//填充每个节点的下一个右侧节点指针 II
	//connect

	//单词接龙
	//ladderLength

	//求根到叶子节点数字之和
	//sumNumbers

	//被围绕的区域
	//solve

	//分割回文串
	//partition

	//克隆图
	//cloneGraph

	//加油站
	//canCompleteCircuit

	//只出现一次的数字 II
	//singleNumber

	//复制带随机指针的链表
	//copyRandomList

	//单词拆分
	//wordBreak

	//重排链表
	//reorderList

	//二叉树的前序遍历
	//preorderTraversal

	//对链表进行插入排序
	//insertionSortList

	//排序链表
	//sortList

	//逆波兰表达式求值
	//evalRPN

	//翻转字符串里的单词
	//reverseWords

	//寻找旋转排序数组中的最小值
	//findMin

	//寻找峰值
	//findPeakElement

	//比较版本号
	//compareVersion

	//分数到小数
	//fractionToDecimal

	//二叉搜索树迭代器
	//class BSTIterator

	//最大数
	//largestNumber
}