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
	*/   //超时了
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
}