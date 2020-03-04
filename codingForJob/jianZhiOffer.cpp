#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

int findRepeatNumber_1(vector<int>& nums)    ////������03. �������ظ�������
{
	//ԭ���㷨,��sort����󣬲��ҵ�ǰ���һ����ͬ������
	if (nums.size() <= 1)
	{
		return 0;
	}
	sort(nums.begin(), nums.end());  //ʱ��O(nlogn)
	for (int i=0; i<nums.size() - 1; ++i)
	{
		if (nums.at(i)  == nums.at(i + 1))
		{
			return nums.at(i);
			break;
		}
	}
	return -1;
}

int findRepeatNumber_2(vector<int>& nums)    ////������03. �������ظ�������
{
	//ʹ��unorder_set������֮ǰ�Ƿ��Ѿ����ˣ��ռ�O(n)��ʱ��O(n)
	if (nums.size() <= 1)
	{
		return 0;
	}
	unordered_set<int> us;
	for (auto i : nums)
	{
		if (us.count(i))
		{
			return i;
			break;
		}
		else
		{
			us.insert(i);
		}
	}
	return -1;
}

int findRepeatNumber_3(vector<int>& nums)    ////������03. �������ظ�������
{
	//���Ҫ��û���ظ��Ļ����±���ֵӦ�����
	//�±�Ϊi��ֵΪm����m==i����������������ȵĻ������Ǿ�ȥ���±�Ϊm����k�����k=m�Ļ����ظ��˷���
	//������ȵĻ�����m��k������Ҳ����m�ŵ��±�Ϊm��λ�ã�k�ŵ��±�Ϊi��λ�ã���ȥ���±�Ϊk����n���������ϲ���
	if (nums.size() <= 1)
	{
		return -1;
	}
	for (int i : nums)
	{
		if (i < 0 || i > nums.size() - 1)
		{
			return -1;
		}
	}
	for (int i=0; i<nums.size(); ++i)
	{
		while (nums[i] != i)
		{
			if (nums[i] == nums[nums[i]])
			{
				return nums[i];
			}
			swap(nums[i], nums[nums[i]]);
		}
	}
	return -1;
}

bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
{
	//��ʣ��������Ͻ��Ǹ���m���������ֱ�ӷ��أ�
	//���m����target����ôm����һ���޳���Ҳ���Ǵ�ʱӦ�ÿ���mͬ�е���������
	//���С�ڣ���m�����б��޳�����ʱҪ����mͬ�е��������
	//ѭ������ִ����ȥ
	if (matrix.size() == 0 || matrix.at(0).size() == 0)
	{
		return false;
	}
	int n = matrix.size() - 1, m = matrix.at(0).size() - 1;
	if (matrix[0][0] > target || matrix[n][m] < target)
	{
		return false;
	}
	int i = 0;
	while (i <= n && m >= 0)
	{
		if (matrix[i][m] == target)
		{
			return true;
		}
		else if (matrix[i][m] > target)
		{
			--m;
		}
		else
		{
			++i;
		}
	}
	return false;
}

string replaceSpace_1(string s)  //������05. �滻�ո�
{
	//ԭ���㷨����s���ݣ�Ȼ��һ��ָ��p1��ԭ��δ���ݵ��ַ��������һ���ַ���ǰ��һ��ָ��p2�����ݺ���ַ����һ��λ����ǰ
	//���p1ָ���ֵ��Ϊ�ո���ô�Ͱ����ֵ��ֵ��p2ָ���λ�ã�
	//������ڿո���ôp2��ǰ�ֱ����02%��Ȼ����������ǰ��,ֱ��p1���˵�0���ַ�
	//���ڰѿո�ת��Ϊ%20��1����Ϊ������Ҳ����˵һ���ո��Ҫ�������2���ַ��ĳ��ȣ�����count���ո񣬾�Ҫ�������2*count������
	if (s.size() == 0)
	{
		return "";
	}
	int count = 0;
	for (char c : s)
	{
		if (c == ' ')
		{
			++count;
		}
	}
	int p1 = s.size() - 1;
	s.resize(s.size() + 2 * count);
	int p2 = s.size() - 1;
	for (; p1 >=0 && p2 >= 0; --p1)
	{
		if (s[p1] != ' ')
		{
			s[p2] = s[p1];
		}
		else
		{
			s[p2] = '0';
			--p2;
			s[p2] = '2';
			--p2;
			s[p2] = '%';
		}
		--p2;
	}
	return s;
}

string replaceSpace_2(string s)  //������05. �滻�ո�
{
	//��ԭ���㷨
	if (s.size() == 0)
	{
		return "";
	}
	string result;
	for (char c : s)
	{
		if (c != ' ')
		{
			result += c;
		}
		else
		{
			result += "%20";
		}
	}
	return result;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

vector<int> reversePrint_1(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��¼����ĳ��ȣ�Ȼ�󿪱�һ���˳��ȵ����飬Ȼ�������ͷ������ֵ�������дӺ���ǰд
	if (!head)
	{
		return {};
	}
	ListNode* p = head;
	int i = 0;
	while (p)
	{
		++i;
		p = p->next;
	}
	vector<int> result(i, 0);
	while (head && i >= 1)
	{
		result[i - 1] = head->val;
		head = head->next;
		--i;
	}
	return result;
}

vector<int> reversePrint_2(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��ջ
	if (!head)
	{
		return {};
	}
	stack<int> s;
	while (head)
	{
		s.push(head->val);
		head = head->next;
	}
	vector<int> result;
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}

vector<int> reversePrint_3(ListNode* head)  //������06. ��β��ͷ��ӡ����
{
	//��ת����
	if (!head)
	{
		return {};
	}
	ListNode* p = nullptr;
	while (head)
	{
		ListNode* tmp = head->next;
		head->next = p;
		p = head;  //��tmpΪnullptrʱ����һ��ѭ���ͽ���ȥ�ˣ�headΪnullptr�ˣ���p�Ǵ�ʱ��ͷԪ��
		head = tmp;
	}
	vector<int> result;
	while (p)
	{
		result.push_back(p->val);
		p = p->next;
	}
	return result;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)  //������07. �ؽ�������
{
	if (preorder.size() == 0 || inorder.size() == 0)
	{
		return nullptr;
	}
	TreeNode* root = new TreeNode(preorder[0]);
	int index = -1;
	for (int i=0; i<inorder.size(); ++i)
	{
		if (inorder[i] == preorder[0])
		{
			index = i;
			break;
		}
	}
	vector<int> inorder_left, inorder_right;
	inorder_left.assign(inorder.begin(), inorder.begin() + index);
	inorder_right.assign(inorder.begin() + index + 1, inorder.end());
	vector<int> preorder_left, preorder_right;
	preorder_left.assign(preorder.begin() + 1, preorder.begin() + 1 + index);
	preorder_right.assign(preorder.begin() + 1 + index, preorder.end());
	root->left = buildTree(preorder_left, inorder_left);
	root->right = buildTree(preorder_right, inorder_right);
	return root;
}

struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

	}
};
TreeLinkNode* GetNext(TreeLinkNode* pNode)  //����������һ�����---��ţ����
{
	//�����pNode�����Ǹ��ڵ㣬���Ƕ��������������һ���ڵ㣬����������������
	if (!pNode)
	{
		return nullptr;
	}
	TreeLinkNode* p = nullptr;
	if (pNode->right)   //���������������ô��һ���ڵ����������������ߵĽڵ�
	{
		p = pNode->right;
		while (p->left)
		{
			p = p->left;
		}
	}
	else if (pNode->next)  //��������������ڣ��Ҹ��ڵ����
	{
		p = pNode->next;  //ָ�򸸽ڵ�
		//������ڵ����ڵ���pNode����ô��һ���ڵ���Ǿ��Ǹ��ڵ�
		//������ڵ���ҽڵ���pNode����ô�������ң�ֱ�������ҵ���ĳ���ڵ�i��i�ĸ��ڵ����ڵ㣬��ô��һ���ڵ����i�ĸ��ڵ�
		while (p && pNode == p->right)
		{
			pNode = p;
			p = p->next;
		}
	}
	return p;
}

class CQueue_1 {       //������09. ������ջʵ�ֶ���
//ɾ��ʱ������һ����ʱջ���򱣴�s�е�Ԫ�أ���ô��ʱջ�Ķ�������Ҫɾ����Ԫ�أ�ɾ��֮���ٰ�Ԫ�ط��ص�s��
public:
	stack<int> s;
	CQueue_1() {

	}

	void appendTail(int value) {
		s.push(value);
	}

	int deleteHead() {
		if (s.empty())
		{
			return -1;
		}
		stack<int> tmp;
		while (!s.empty())
		{
			tmp.push(s.top());
			s.pop();
		}
		int result = tmp.top();
		tmp.pop();
		while (!tmp.empty())
		{
			s.push(tmp.top());
			tmp.pop();
		}
		return result;
	}
};

class CQueue_2 {       //������09. ������ջʵ�ֶ���
//����ջ��һ���ܲ��룬һ����ɾ��
public:
	stack<int> s1, s2;
	CQueue_2() {

	}

	void appendTail(int value) {
		s1.push(value);
	}

	int deleteHead() {
		int result = -1;
		if (!s2.empty())
		{
			result = s2.top();
			s2.pop();
		}
		else if (!s1.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			result = s2.top();
			s2.pop();
		}
		return result;
	}
};

class MyStack_1 {   //�ö���ʵ��ջ--09��������
//����ʱ��ֱ�Ӳ��룬ɾ��ʱ������ʱ����
public:
	queue<int> q;
	MyStack_1() {

	}

	void push(int x) {
		q.push(x);
	}

	int pop() {
		if (q.empty())
		{
			return -1;
		}
		queue<int> tmp;
		int result = -1;
		while (!q.empty())
		{
			result = q.front();
			q.pop();
			if (!q.empty())
			{
				tmp.push(result);
			}
		}
		while (!tmp.empty())
		{
			q.push(tmp.front());
			tmp.pop();
		}
		return result;
	}

	int top() {
		if (q.empty())
		{
			return -1;
		}
		queue<int> tmp;
		int result = -1;
		while (!q.empty())
		{
			result = q.front();
			q.pop();
			tmp.push(result);
		}
		while (!tmp.empty())
		{
			q.push(tmp.front());
			tmp.pop();
		}
		return result;
	}

	bool empty() {
		return q.empty();
	}
};

class MyStack_2 {   //�ö���ʵ��ջ--09��������
//�ĸ���Ϊ�վͲ��뵽�ĸ�����
//������popɾ��ʱ�򣬿���ѭ�����뵽��һ��Ϊ�յģ�ѭ�������һ��Ԫ��ʱ�򲻷���
public:
	queue<int> q1, q2;
	MyStack_2() {

	}

	void push(int x) {
		if (q2.empty())
		{
			q1.push(x);
		}
		else
		{
			q2.push(x);
		}
	}

	int pop() {
		if (q1.empty() && q2.empty())
		{
			return -1;
		}
		int result = -1;
		if (q2.empty())
		{
			while (!q1.empty())
			{
				result = q1.front();
				q1.pop();
				if (!q1.empty())
				{
					q2.push(result);
				}
			}
		}
		else
		{
			while (!q2.empty())
			{
				result = q2.front();
				q2.pop();
				if (!q2.empty())
				{
					q1.push(result);
				}
			}
		}
		return result;
	}

	int top() {
		if (q1.empty() && q2.empty())
		{
			return -1;
		}
		int result = -1;
		if (q2.empty())
		{
			while (!q1.empty())
			{
				result = q1.front();
				q1.pop();
				q2.push(result);
			}
		}
		else
		{
			while (!q2.empty())
			{
				result = q2.front();
				q2.pop();
				q1.push(result);
			}
		}
		return result;
	}

	bool empty() {
		return q1.empty() && q2.empty();
	}
};

int fib(int n)   //������10- I. 쳲���������
{
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}
	int p = 0, cur = 1;
	for (int i=2; i<=n; ++i)
	{
		if (p > 1000000007 - cur)   //��ĿҪ�����Ҫȡģ 1e9+7��1000000007��
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int numWays(int n)  //������10- II. ������̨������
{
	if (n <= 1)
	{
		return 1;
	}
	int p = 1, cur = 1;
	for (int i=2; i<=n; ++i)
	{
		if (p > 1000000007 - cur) //��ĿҪ�����Ҫȡģ 1e9+7��1000000007��
		{
			p = p % 1000000007;
			cur = cur % 1000000007;
		}
		cur += p;
		p = cur - p;
	}
	return cur % 1000000007;
}

int minArray(vector<int>& numbers)  //������11. ��ת�������С����
{
	if (numbers.size() == 0)
	{
		return -1;
	}
	if (numbers.size() == 1)
	{
		return numbers[0];
	}
	int result = INT_MAX;
	int l = 0, r = numbers.size() - 1;
	while (l <= r)
	{
		int mid = (r - l) / 2 + l;
		if (numbers[l] < numbers[mid])  //����ϸ�С�ڣ�˵��l��mid��������ôresult��ֵ�󣬿���������Ƿ��и�С��
		{
			result = min(result, numbers[l]);
			l = mid + 1;
		}
		else if(numbers[l] == numbers[mid])  //��ȵĻ�,��ֵ��ǰ��l��Ȼ��������������������������Сֵ
		{
			result = min(result, numbers[l]);
			++l;
		}
		else  //�������
		{
			result = min(result, numbers[mid]);
			r = mid - 1;
		}
	}
	return result;
}

int exist_direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
set< pair<int, int> > exist_s; //�洢�ù�������, ����Ҳ���Զ���һ����board��ͬ��С��boolֵ���󣬱�ʾ��i�е�j���Ƿ���ʹ����
bool exist_dfs(vector<vector<char>>& board, string word, int n, int row, int column)
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	if (n == word.size())
	{
		return true;
	}
	if (row == -1 || column == -1)  //��һ�����ֻ�û��ʼ��
	{
		for (int i=0; i < board.size(); ++i)
		{
			for (int j=0; j < board.at(i).size(); ++j)
			{
				if (board[i][j] == word[n])
				{
					pair<int, int> p(i, j);
					exist_s.insert(p);   //��һ���ַ�ֱ�ӷŽ�ȥ�Ϳ���
					bool flag = exist_dfs(board, word, n + 1, i, j);
					if (flag)
					{
						return true;
					}
					exist_s.erase(p);  //������ǰ�ù��ģ��ٴ���һ���ַ���ʼ��Ϊ��ͷ����
				}
			}
		}
	}
	else  //���������
	{
		for (int i=0; i<4; ++i)
		{
			int x = row + exist_direction[i][0], y = column + exist_direction[i][1];
			if (x >= 0 && x < board.size() && y >= 0 && y < board.at(0).size())
			{
				if (board[x][y] == word[n])
				{
					pair<int, int> p(x, y);
					set< pair<int, int> >::iterator ifind = exist_s.find(p);
					if (ifind != exist_s.end())  //�����ǰ�ַ��ù���
					{
						continue;
					}
					exist_s.insert(p);
					bool flag = exist_dfs(board, word, n + 1, x, y);
					if (flag)
					{
						return true;
					}
					exist_s.erase(p);  //������ǰ������ַ����ٴ�ʣ�෽����У���Ϊ����ַ����ܺ����õ�
				}
			}
		}
	}
	return false;
}
bool exist(vector<vector<char>>& board, string word)   //������12. �����е�·��
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	return exist_dfs(board, word, 0, -1, -1);
}
vector< vector<bool> > exist_1_visited;  //����һ����board��ͬ��С��boolֵ���󣬱�ʾ��i�е�j���Ƿ�ʹ����
bool exist_1_dfs(vector<vector<char>>& board, string word, int n, int row, int column)
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	if (n == word.size())
	{
		return true;
	}
	if (row == -1 || column == -1)  //��һ�����ֻ�û��ʼ��
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board.at(i).size(); ++j)
			{
				if (board[i][j] == word[n] && !exist_1_visited[i][j])
				{
					exist_1_visited[i][j] = true;
					bool flag = exist_dfs(board, word, n + 1, i, j);
					if (flag)
					{
						return true;
					}
					exist_1_visited[i][j] = false;  //������ǰ�ù��ģ��ٴ���һ���ַ���ʼ��Ϊ��ͷ����
				}
			}
		}
	}
	else  //���������
	{
		for (int i = 0; i < 4; ++i)
		{
			int x = row + exist_direction[i][0], y = column + exist_direction[i][1];
			if (x >= 0 && x < board.size() && y >= 0 && y < board.at(0).size())
			{
				if (board[x][y] == word[n] && !exist_1_visited[x][y])
				{
					exist_1_visited[x][y] = true;
					bool flag = exist_dfs(board, word, n + 1, x, y);
					if (flag)
					{
						return true;
					}
					exist_1_visited[x][y] = false;  //������ǰ������ַ����ٴ�ʣ�෽����У���Ϊ����ַ����ܺ����õ�
				}
			}
		}
	}
	return false;
}
bool exist_1(vector<vector<char>>& board, string word)   //������12. �����е�·��
{
	if (board.size() == 0 || board.at(0).size() == 0 || word.size() == 0)
	{
		return false;
	}
	for (int i = 0; i < board.size(); ++i)
	{
		vector<bool> tmp;
		for (int j = 0; j < board.at(i).size(); ++j)
		{
			tmp.push_back(false);
		}
		exist_1_visited.push_back(tmp);
	}
	return exist_1_dfs(board, word, 0, -1, -1);
}

int movingCount_direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
vector< vector<bool> > movingCount_visited;   //�ж��Ƿ��߹���
int movingCount_result = 1;   //���Ľ��,��һ��(0,0)�϶����ڣ���˾ʹ������ʼ��
int movingCount_sum(int n)  //����n�ĸ�λ������
{
	int sum = 0;
	while (n > 0)
	{
		sum += (n % 10);
		n /= 10;
	}
	return sum;
}
void movingCount_dfs(int row, int column, int k, int m, int n)
{
	if (k == 0)
	{
		movingCount_result = 1;
		return;
	}
	for (int i=0; i<4; ++i)
	{
		int x = row + movingCount_direction[i][0], y = column + movingCount_direction[i][1];
		if (x >= 0 && x < m && y >= 0 && y < n)
		{
			int sumx = movingCount_sum(x), sumy = movingCount_sum(y);
			if (sumx + sumy <= k && !movingCount_visited[x][y])
			{
				movingCount_visited[x][y] = true;  //�߹��˾Ͳ�Ҫ�߻����ˣ���˲����ٻָ�Ϊfalse
				++movingCount_result;
				movingCount_dfs(x, y, k, m, n);
			}
		}
	}
}
int movingCount(int m, int n, int k)  //������13. �����˵��˶���Χ
{
	if (k == 0)
	{
		return 1;
	}
	for (int i=0; i<m; ++i)
	{
		vector<bool> tmp;
		for (int j=0; j<n; ++j)
		{
			tmp.push_back(false);
		}
		movingCount_visited.push_back(tmp);
	}
	movingCount_visited[0][0] = true;
	movingCount_dfs(0, 0, k, m, n);
	delete[] movingCount_direction;  //ɾ��
	movingCount_visited.clear();  //�������
	return movingCount_result;
}

int cuttingRope(int n)  //������14- I. ������
{
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	//������֪��dp(n-1)Ϊn-1ʱ������ֵ��
	//��n=n-1+1��n=n-2+2��n=n-3+3��������n=1+n-1
	//Ҳ����˵dp(n) = max(dp(n-i)*dp(i))�� i��n-1��n/2
	//����һ���Ƕ���˵������ÿһ�����Ƕ�Ӧ���ֵʱ�������һ��
	//����һ��ʱ����1,2,3....n-1���������ô�ͼ�����i+j=n,Ȼ��dp(n) = max(dp(n-i)*dp(i))
	//��ô��û��һ���з��ܹ�ʹ�ý������max(dp(n-i)*dp(i))����
	//���Ǽ�����ڣ���ô��һ����ȥ�г���k+l=n,Ȼ����Ƕ�k��l�ֱ��У�Ȼ��k���ֻ����dp(k),l�����dp(l)�����dp(n)���ǵ���dp(k)*dp(l)
	vector<int> dp(n + 1, 0);
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;  //���ֻ��Ϊ�˵ó��������ʵ��n=2ʱ�򲻷�
	dp[3] = 3;  //���ֻ��Ϊ�˵ó��������ʵ��n=3ʱ�򲻷�
	for (int i = 4; i <= n; ++i)
	{
		for (int j = i - 1; j >= i / 2; --j)  //��Ȼ����i-j��j�ĶԳ��ԣ�j��i/2�Ϳ�����
		{
			dp[i] = max(dp[i], dp[j] * dp[i - j]);
		}
	}
	return dp[n];
}
int cuttingRope_1(int n)  //������14- I. ������
{
	//��2��3�Ļ��������г�2��3����Ϊ�г�4�����Կ�������2���г�5�������г�2��3���г�6�������г�3��3
	//�г�7������3��2��2.������Ҳ����˵�����г�2��3
	//�����ȽϵĻ��������г�3����˱ȷ�6�Ļ�3*3>2*2*2
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	int a = n / 3, b = n % 3;
	if (b == 0) //3�ı���
	{
		return pow(3, a);
	}
	else if (b == 1)//����7��3 3 1ҪС��3 2 2,Ҳ����˵Ӧ���г�3 3 3 ... 3 2 2
	{
		return pow(3, a - 1) * 4;
	}
	else  //b=2
	{
		return pow(3, a) * 2;
	}
}

int cuttingRope(int n)   //������14- II. ������ II  ��Ҫȡ��1000000007
{
	if (n <= 1)
	{
		return 0;
	}
	if (n == 2)
	{
		return 1;
	}
	if (n == 3)
	{
		return 2;
	}
	int a = n / 3, b = n % 3;
	if (b == 1)
	{
		a -= 1;
	}
	int result = 1;
	int tmp = result;
	for (int i = 1; i <= a; ++i)  //pow(3, a)�ֿ��ۼ�
	{
		if (result > INT_MAX / 3)
		{
			tmp = result;
			result = result % 1000000007 + result % 1000000007;
			result %= 1000000007;
			result += (tmp % 1000000007);
		}
		else
		{
			result *= 3;
		}
	}
	if (b == 1)
	{
		if (result > INT_MAX / 4)   //����4Ҫ�ֿ��ۼ�
		{
			tmp = result;
			result = result % 1000000007 + result % 1000000007;
			result %= 1000000007;
			result += (tmp % 1000000007);
			result %= 1000000007;
			result += (tmp % 1000000007);
		}
		else
		{
			result *= 4;
		}
	}
	else if (b == 2)
	{
		if (result > INT_MAX / 2)  //����2Ҫ�ֿ��ۼ�
		{
			result = result % 1000000007 + result % 1000000007;
		}
		else
		{
			result *= 2;
		}
	}
	return result % 1000000007;;
}

int hammingWeight(uint32_t n)  //������15. ��������1�ĸ���
{
	//n&(n-1)Ϊ������λ��1��n&(-n)Ϊ�õ����λ��1
	if (n == 0)
	{
		return 0;
	}
	int result = 0;
	while (n != 0)
	{
		++result;
		n &= (n - 1);
	}
	return result;
}

double myPow(double x, int n)  //������16. ��ֵ�������η�
{
	if (x == 0 && n < 0)
	{
		return 0.0;
	}
	if ((x == 0 && n == 0) || n == 0 || x == 1)
	{
		return 1.0;
	}
	if (n == 1)
	{
		return x;
	}
	unsigned int ui = 0; //ת��Ϊunsigned int
	if (n < 0)
	{
		ui = -(n + 1);  //����int_min���
		ui += 1;
	}
	else
	{
		ui = n;
	}
	double result = myPow(x, ui >> 1);   //���Ʊȳ���2��
	result = result * result;
	if (ui & 1)  //�ж�%2����ֱ����&1�Ϳ��ԣ��������������������Ϊtrue
	{
		result *= x;
	}
	if (n < 0)
	{
		result = 1.0 / result;
	}
	return result;
}

vector<int> printNumbers(int n)   //������17. ��ӡ��1������nλ��--leetcode��̫��
{
	if (n == 0)
	{
		return {};
	}
	//���ҵ�������
	int ma = 9;
	for (int i = 1; i < n; ++i)
	{
		ma = ma * 10 + 9;
	}
	vector<int> result(ma);
	for (int i = 0; i < ma; ++i)
	{
		result[i] = i + 1;
	}
	return result;
}

string printNumbers_string_plus1(string s)  //s��ʾ�����ּ���1,s��ʾ������>=0�ģ��Ǹ���
{
	if (s.size() == 0)
	{
		return "";
	}
	int i = s.size() - 1;
	int jinwei = 1;  //��Ϊ��ʾ����s�����ּ�1�����Ըտ�ʼҪ��Ϊ1ѽ
	while (i >= 0)
	{
		int tmp = s[i] - '0' + jinwei;
		if (tmp < 10)
		{
			s[i] = tmp + '0';
			jinwei = 0;
			break;
		}
		else
		{
			s[i] = tmp - 10 + '0';
			jinwei = 1;
			--i;
		}
	}
	if (jinwei)
	{
		s = "1" + s;
	}
	return s;
}
vector<string> printNumbers_string(int n)   //������17. ��ӡ��1������nλ��, ����Ҫ����n��������
{
	//����������ֵ��ַ���+1�ķ�����һֱ���ַ���+1��λ������nΪֹ
	if (n == 0)
	{
		return {};
	}
	vector<string> result;
	result.push_back("1");
	string s = "1";
	while (true)
	{
		s = printNumbers_string_plus1(s);
		if (s.size() > n)
		{
			break;
		}
		result.push_back(s);
	}
	return result;
}

vector<string> printNumbers_string_v;  //���
void printNumbers_string_1_dfs(string s, int n)
{
	if (s.size() == n)
	{
		//��ȥ��sǰ���0
		int i = 0;
		while (i < s.size() && s[i] == '0')
		{
			++i;
		}
		if (i < s.size())  //��ֹs="000000000"�������
		{
			s = s.substr(i);
			printNumbers_string_v.push_back(s);
		}
		return;
	}
	for (char k = '0'; k <= '9'; ++k)
	{
		s.push_back(k);
		printNumbers_string_1_dfs(s, n);  //��һλ��k��ȫ�����ˣ�Ȼ�󵯳�k������ȥ
		s.pop_back();
	}
}
vector<string> printNumbers_string_1(int n)   //������17. ��ӡ��1������nλ��, ����Ҫ����n��������
{
	//ʵ���Ͼ���0-9��n������ȫ���У�ֻ����Ҫ��ǰ���0ȥ��
	if (n == 0)
	{
		return {};
	}
	printNumbers_string_1_dfs("", n);
	return printNumbers_string_v;
}

ListNode* deleteNode(ListNode* head, int val)  //������18. ɾ������Ľڵ�
{
	if (!head)
	{
		return nullptr;
	}
	if (head->val == val)
	{
		head = head->next;
		return head;
	}
	ListNode* result = head;
	while (head->next && head->next->val != val)
	{
		head = head->next;
	}
	if (head->next)  //while�о�ֻ����head->next->val = val��������
	{
		ListNode* tmp = head->next->next;
		head->next = tmp;
	}
	//���Ҫ��head->next�������ˣ���˵����ǰԪ��ΪβԪ�أ�����˵Ӧ��Ҫ�ж�һ�����βԪ���Ƿ���val���
	//Ȼ����headΪ�����ڶ���Ԫ�ص�ʱ����while���Ѿ��ж��˵�����һ��Ԫ�ز�����val������headָ�벻���������
	//���������û��else��
	return result;
}

ListNode* deleteNode_1(ListNode* head, ListNode* p)  //������18. ɾ������Ľڵ�
{
	//����p�Ǵ�ɾ���Ľڵ�
	if (!head)  //ͷָ��Ϊ�գ�˵�����p����������
	{
		return nullptr;
	}
	//����Ҫ˵�����ǣ����p�����������������ô��ҪO(n)��ʱ���������ж��Ƿ��ڲ���
	//�����ĿҪ����ȷ˵�ڣ�ҲҪ��p�Ƿ���β�ڵ�
	//������ȷ˵����
	if (!p)  //���p�ǿ�
	{
		return head;
	}
	if (p->next)  //p����βָ��
	{
		//��p->next��ֱֵ�Ӹ���p��ֵ��Ȼ��pָ��ԭ��next��next
		ListNode* tmp = p->next->next;
		p->val = p->next->val;
		p->next = tmp;
	}
	else  //βָ��
	{
		if (head == p)  //���p��ͷָ��
		{
			head = head->next;
		}
		else  //p����ͷָ��
		{
			ListNode* tmp = head;
			while (tmp->next && tmp->next != p)
			{
				tmp = tmp->next;
			}
			//��Ȼp�϶����������У�����βָ�룬��ô��tmpΪ�����ڶ���Ԫ��ʱ���˳���while
			tmp->next = nullptr;  //ֱ���õ����ڶ���Ԫ�ص���һ��Ϊ�ռ���
		}
	}
	return head;
}

ListNode* deleteDuplicates(ListNode* head)  //18������--ɾ�����������е��ظ�Ԫ��,ɾ�������ظ���Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ��
{
	if (!head)
	{
		return nullptr;
	}
	//�����ظ���Ԫ�ر���һ�����ɣ�������Ǳ�����һ��
	ListNode* result = head;
	while (head)
	{
		ListNode* n = head->next;
		while (n && n->val == head->val)  //������Ԫ��Ҳ���ظ�Ԫ��ʱ��n��ָ��null���������ֱ��head��nextָ��null
		{
			n = n->next;
		}
		head->next = n;
		head = n;
	}
	return result;
}

ListNode* deleteDuplicates(ListNode* head) //18������--ɾ�����������е��ظ�Ԫ�� II, ֻ����ԭʼ������ û���ظ����ֵ�����
{
	if (!head || !head->next)
	{
		return head;
	}
	ListNode* result = new ListNode(0);  //�ڱ�
	ListNode* tmp = result;
	//�ȿ�ͷ�ڵ�
	if (head->val != head->next->val) //head��Ψһ��
	{
		result->next = head;  //���뵽result����
		tmp = tmp->next;  //ָ�����������ڵ���Ǹ�,��ʱ����head
	}
	//����Ҫ˵�����ǣ����һ��ֵ��ǰ���ֵ������ͬ����ô�����Ӧ���Ƿ��ؽ����һ����
	ListNode* pre = head;  //���ͷָ����Ψһ�ģ�ǰ����Ѿ������ˣ���˲���Ҫ����
	head = head->next;
	ListNode* n = head->next;
	while (pre && head && n)
	{
		if (head->val != pre->val && head->val != n->val)  //head��Ψһ��
		{
			tmp->next = head;
			tmp = tmp->next;
		}
		pre = pre->next;
		head = head->next;
		n = n->next;
	}
	//��nΪ��ʱ���˳����ˣ���ʱ������Ҫ����������һ��Ԫ���뵹���ڶ����Ƿ���ȣ�Ҳ����head��pre
	if (head->val != pre->val)  //�������ȣ���˵�����һ��Ԫ��Ψһ
	{
		tmp->next = head;
		tmp = tmp->next;
	}
	tmp->next = nullptr; //���һ��ָ��nullptr
	return result->next;
}

bool isMatch_recursion(string s, string p)
{
	if (p.empty())
	{
		return s.empty();
	}
	if (s.empty())
	{
		if (p.size() > 1 && p[1] == '*')
		{
			return isMatch_recursion(s, p.substr(2));
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (p.size() > 1 && p[1] == '*')
		{
			if (s[0] == p[0] || p[0] == '.')
			{
				//return isMatch_recursion(s.substr(1), p.substr(2)) || isMatch_recursion(s, p.substr(2)) || isMatch_recursion(s.substr(1), p);
				return isMatch_recursion(s, p.substr(2)) || isMatch_recursion(s.substr(1), p);  //ƥ��һ�ε�ʱ��Ҳ��������s�е�����ַ��������󣬱��������ַ������൱��ƥ��0��
			}
			else
			{
				return isMatch_recursion(s, p.substr(2));
			}
		}
		else
		{
			if (s[0] == p[0] || p[0] == '.')
			{
				return isMatch_recursion(s.substr(1), p.substr(1));
			}
			else
			{
				return false;
			}
		}
	}
}
bool isMatch(string s, string p)  //������19. ������ʽƥ��
{
	if (s.size() == 0 && p.size() == 0)
	{
		return true;
	}
	else if (p.size() == 0 && s.size() != 0)
	{
		return false;
	}
	return isMatch_recursion(s, p);
}

bool isNumber(string s)  //������20. ��ʾ��ֵ���ַ���
{
	if (s.size() == 0)
	{
		return false;
	}
	//�����ո�,ֻ�ܳ�����ĩβ�Ϳ�ͷ
	while (s.size() && s[0] == ' ')  //����ǰ��Ŀո�
	{
		s = s.substr(1);
	}
	if (s.size() == 0)  //����ǰ��Ŀո�֮��û��
	{
		return false;
	}
	while (s.size() && s[s.size() - 1] == ' ')  //��������Ŀո�
	{
		s.pop_back();
	} 
	if (s.size() == 0)  //��������Ŀո�֮��û��
	{
		return false;
	}
	int i = 0;
	if (s[i] == '+' || s[i] == '-')  //��������
	{
		++i;
	}
	string zhengshu, xiaoshu, zhishu;
	//Ѱ����������
	while (i < s.size())
	{
		if (s[i] >= '0' && s[i] <= '9')  //��������ֻ����0-9������.��e��EҪ����,����false
		{
			zhengshu = s[i] + zhengshu;
			++i;
		}
		else if (s[i] == '.' || s[i] == 'e' || s[i] == 'E')
		{
			break;
		}
		else
		{
			return false;
		}
	}
	if (i == s.size())  //���ȫ��������
	{
		return true;
	}
	if (s[i] == '.')  //�������������С���㣬��ôС�����ֿ�ʼ
	{
		++i;  //����С����
		while (i < s.size())
		{
			if (s[i] >= '0' && s[i] <= '9')  //С������ֻ����0-9������e��EҪ�����������ַ���Ϊfalse
			{
				xiaoshu = s[i] + xiaoshu;
				++i;
			}
			else if (s[i] == 'e' || s[i] == 'E')
			{
				break;
			}
			else
			{
				return false;
			}
		}
	}
	if (xiaoshu.size() == 0 && zhengshu.size() == 0)  //С������Ϊ������������Ϊ��,��������.e9�����ģ����У�����1.e9����
	{
		return false;
	}
	if (i == s.size())  //��������С��������һ������i��ͷ��
	{
		return true;
	}
	//���û��ͷ�Ļ���ֻ����e��E��ĳ��ѭ����break�ˣ����������ַ��ͻ᷵��false��
	//e��E�����
	++i; //����e��E
	if (i >= s.size())  //e��E�����һ���ַ�
	{
		return false;
	}
	if (s[i] == '+' || s[i] == '-')  //e��E����Ҫ���������ţ�������
	{
		++i;
	}
	if (i == s.size())  //�����������һ���ַ�
	{
		return false;
	}
	while (i < s.size()) //���������ж���e��E�Ƿ������һ���ַ��������ܵ������˵��e��E�������Ų������һ���ַ�
	{
		if (s[i] >= '0' && s[i] <= '9')  //e��E��������������ţ������ź���ֻ��������
		{
			zhishu = s[i] + zhishu;
			++i;
		}
		else
		{
			return false;
		}
	}
	return true;  //�п�������С����û�У���e9����ô��ʱ�϶�����
}

vector<int> exchange(vector<int>& nums)  //������21. ��������˳��ʹ����λ��ż��ǰ��
{
	if (nums.size() <= 1)
	{
		return nums;
	}
	int l = 0, r = nums.size() - 1;
	while (l < r)
	{
		//�ҵ���ߵ�
		while (l < r && (nums[l] & 1) == 1)  //����ż��Ҫbreak����������Ҫ����
		{
			++l;
		}
		while (l < r && (nums[r] & 1) == 0)  //��������Ҫbreak������ż��Ҫ����
		{
			--r;
		}
		if (l < r)
		{
			swap(nums[l], nums[r]);
			++l;
			--r;
		}
	}
	return nums;
}

ListNode* getKthFromEnd(ListNode* head, int k)   //������22. �����е�����k���ڵ�
{
	if (k <= 0 || !head)
	{
		return nullptr;
	}
	//��������ָ��
	ListNode* fast = head;
	int i = k;
	while (i > 0 && fast)
	{
		fast = fast->next;
		--i;
	}
	if (i > 0)  //���i��Ȼ����0��˵��fastΪ���ˣ�˵����û�߳�k������Ϳ��ˣ�˵������С��k
	{
		return nullptr;
	}
	while (fast)
	{
		fast = fast->next;
		head = head->next;
	}
	return head;
}

ListNode *detectCycle(ListNode *head) //������23. ������������
{
	//�����ͷָ�뵽����ڵĳ���Ϊl���ӻ���ڵ����������Ϊm������ʣ�ಿ��Ϊn
	//������ʱ����ָ������l+m����ָ������l+m+n+m=l+2m+n
	//���ڿ�ָ���ٶ�����ָ���2��������l+2m+n = 2(l+m)������l=n
	//��ô����ֻ��Ҫ��ָ������n�����ǻ������
	//�����ʱͷָ���ͷ��ʼ�ߣ���ָ��������㿪ʼ�ߣ������ٶ���ͬ
	//���������ٶ���ͬ����l=n����ô���õ�ͷָ������l��ʱ��ָ������l����Ҳ����n��������������Ҳ���Ƕ����ڻ������������
	//Ҳ����˵����������ʱ�����þ��ǻ������
	if (!head || !head->next)
	{
		return nullptr;
	}
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)  //������
		{
			break;
		}
	}
	if (!fast || !fast->next)  //���fast����һ��Ϊ�գ�˵��û�л�
	{
		return nullptr;
	}
	while (head != slow)  //���߲�������һֱ�ߣ�����������ʱ�����ǵ��˻������
	{
		head = head->next;
		slow = slow->next;
	}
	return head;
}

ListNode* reverseList(ListNode* head)  //������24. ��ת����
{
	if (!head)
	{
		return nullptr;
	}
	ListNode* p = nullptr;
	while (head)
	{
		ListNode* tmp = head->next;
		head->next = p;
		p = head;
		head = tmp;
	}
	return p;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)  //������25. �ϲ��������������
{
	//����
	if (!l1)
	{
		return l2;
	}
	if (!l2)
	{
		return l1;
	}
	ListNode* result = new ListNode(0);  //�ڱ��ڵ�
	ListNode* tmp = result;
	while (l1 && l2)
	{
		if (l1->val <= l2->val)
		{
			tmp->next = l1;
			l1 = l1->next;
		}
		else
		{
			tmp->next = l2;
			l2 = l2->next;
		}
		tmp = tmp->next;
	}
	if (l1)  //l1��Ϊ��
	{
		tmp->next = l1;
	}
	else if (l2)
	{
		tmp->next = l2;
	}
	else
	{
		tmp->next = nullptr;
	}
	return result->next;
}

bool isSubStructure_item(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	bool child = false;
	if (A->val == B->val)  //���ֵ��ͬ,���������ӽڵ��಻��ͬ�������ͬ�Ļ��������µݹ���������������Ͳ��ݹ�
	{
		if ((!A->left && !B->left) || (A->left && !B->left) || (A->left && B->left && A->left->val == B->left->val))  //���������������������,����A��Bû�У����߶�����ֵ���
		{
			if ((!A->right && !B->right) || (A->right && !B->right) || (A->right && B->right && A->right->val == B->right->val))
			{
				child = true;
			}
		}
		child = child && isSubStructure_item(A->left, B->left) && isSubStructure_item(A->right, B->right);
	}
	if (child)
	{
		return true;
	}
	return isSubStructure_item(A->left, B) || isSubStructure_item(A->right, B);
}
bool isSubStructure(TreeNode* A, TreeNode* B)  //������26. �����ӽṹ,�Լ��Ľⷨ
{
	if (!A || !B)  //Լ��������������һ�������ӽṹ
	{
		return false;
	}
	return isSubStructure_item(A, B);
}

bool isSubStructure_item_1_equal(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	if (A->val == B->val)
	{
		return isSubStructure_item_1_equal(A->left, B->left) && isSubStructure_item_1_equal(A->right, B->right);
	}
	else
	{
		return false;
	}
}
bool isSubStructure_item_1(TreeNode* A, TreeNode* B)
{
	if (!B)
	{
		return true;
	}
	else if (!A)
	{
		return false;
	}
	bool result = false;
	if (A->val == B->val)  //���A��ǰ�Ľڵ����B�Ľڵ�ֵ����ôȥ������A����ڵ�Ϊ���ڵ�����Ƿ���Bƥ��,ֻ������������ƥ�䣬�ſ���
	{
		result = isSubStructure_item_1_equal(A->left, B->left) && isSubStructure_item_1_equal(A->right, B->right);
	}
	if (result)  //�������������ƥ��
	{
		return true;
	}
	return isSubStructure_item_1(A->left, B) || isSubStructure_item_1(A->right, B);  //������������һ������֮ƥ�伴��
}
bool isSubStructure_1(TreeNode* A, TreeNode* B)  //������26. �����ӽṹ
{
	if (!A || !B)  //Լ��������������һ�������ӽṹ
	{
		return false;
	}
	return isSubStructure_item_1(A, B);
}

TreeNode* mirrorTree(TreeNode* root)  //������27. �������ľ���
{
	if (!root || (!root->left && !root->right))
	{
		return root;
	}
	//���һ���
	TreeNode* tmp = root->left;
	root->left = root->right;
	root->right = tmp;
	//�ݹ����������������
	mirrorTree(root->left);
	mirrorTree(root->right);
	return root;
}

bool isSymmetric_item(TreeNode* A, TreeNode* B)  //A�ǶԳ�����ߵ�����B�ǶԳ����ұߵ���
{
	if (!A && !B)
	{
		return true;
	}
	if ((!A && B) || (A && !B))
	{
		return false;
	}
	if (A->val != B->val)
	{
		return false;
	}
	//��Ӧ��ϵ�����������߶�Ӧ�ұ������ұߣ���������ұ߶�Ӧ�ұ������
	return isSymmetric_item(A->left, B->right) && isSymmetric_item(A->right, B->left);
}
bool isSymmetric(TreeNode* root)  //������28. �ԳƵĶ�����
{
	if (!root || (!root->left && !root->right))
	{
		return true;
	}
	if ((root->left && !root->right) || (!root->left && root->right))
	{
		return false;
	}
	//�����Ƕ��ڸ��ڵ�
	return isSymmetric_item(root->left, root->right);
}

vector<int> spiralOrder(vector<vector<int>>& matrix)  //������29. ˳ʱ���ӡ����
{
	if (matrix.size() == 0 || matrix.at(0).size() == 0)
	{
		return {};
	}
	vector< vector<bool> > visited(matrix.size(), vector<bool>(matrix.at(0).size(), false));  //�Ƿ񱻷����˵�
	//�ƶ������ȼ�����->��->��->��->��->...
	int direction[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	int n = matrix.size(), m = matrix.at(0).size(), i = 0, d = 0; //i���±꣬d�ǵ�ǰ�ķ���
	int row = 0, column = 0;  //��ʾ���������
	vector<int> result(n * m, 0);
	while (i < n * m)
	{
		if (row >= 0 && row < n && column >= 0 && column < m && !visited[row][column])
		{
			result[i] = matrix[row][column];
			visited[row][column] = true;
			row += direction[d][0];
			column += direction[d][1];
			++i; //д���˲�Ҫ��һ�������򲻶��ȴ�д��
		}
		else
		{
			//�ȷ���ԭ�ȵĵ㣬Ȼ���ٱ任����
			row -= direction[d][0];
			column -= direction[d][1];
			//�ٱ任����
			d = (d + 1) % 4;
			row += direction[d][0];
			column += direction[d][1];
		}
	}
	return result;
}

class MinStack {   // ������30. ����min������ջ
public:
	int minValue;
	stack<int> s;
	stack<int> tmp; //��Ų��뵽��i��Ԫ��ʱ����Ӧ����Сֵ
	/** initialize your data structure here. */
	MinStack() {
	}

	void push(int x) {
		if (tmp.empty() || x < minValue)  //���Ϊ�ջ���x��С�Ļ�
		{
			minValue = x;
		}
		tmp.push(minValue);  //��Զѹ�뵱ǰ��Сֵ
		s.push(x);
	}

	void pop() {
		//������Сֵ�ǲ�����ջ������Ҫ��tmp��ջ���������
		//��Ϊtmp��ŵ��ǽ�������ʱs�е���Сֵ,
		//Ҳ����˵s��ʣ��2����tmp��Ӧ����ʣ����������Ϊ�ǽ���s��������Ԫ��ʱ��Ӧ����Сֵ
		if (!s.empty() && !tmp.empty())
		{
			tmp.pop();
			s.pop();
			if (!tmp.empty())
			{
				minValue = tmp.top();
			}
		}
	}

	int top() {
		if (s.empty())
		{
			return -1;
		}
		return s.top();
	}

	int min() {
		return minValue;
	}
};

bool validateStackSequences(vector<int>& pushed, vector<int>& popped)  //������31. ջ��ѹ�롢��������
{
	if (pushed.size() == 0 && popped.size() == 0)
	{
		return true;
	}
	else if (pushed.size() != popped.size())
	{
		return false;
	}
	stack<int> s;
	int i = 0, j = 0;
	while (i < pushed.size() && j < popped.size())
	{
		while (i < pushed.size() && pushed[i] != popped[j]) //�����ǰ��i��j����ȣ���ô��ѹ��ջ�У��ȴ�һ��ʼ��
		{
			s.push(pushed[i]);
			++i;
		}
		//������ǰ��ȵģ�����û����ȵĻ���i�ͳ�����pushed��size���ͻ��˳�ѭ��
		++i;
		++j;
		while (j < popped.size() && !s.empty() && s.top() == popped[j])  //�����Ƿ����poped��Ԫ��һֱ��s��
		{
			++j;
			s.pop();
		}
	}
	return (i >= pushed.size() && j >= popped.size() && s.empty());
}

vector<int> levelOrder(TreeNode* root)  //������32 - I. ���ϵ��´�ӡ������
{
	if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector<int> result;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector<int> result;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		q.pop();
		result.push_back(root->val);
		if (root->left)
		{
			q.push(root->left);
		}
		if (root->right)
		{
			q.push(root->right);
		}
	}
	return result;
		result.push_back(root->val);
		if (root->left)
		{
			q.push(root->left);
		}
		if (root->right)
		{
			q.push(root->right);
		}
	}
	return result;
}

vector<vector<int>> levelOrder_ii(TreeNode* root)  //������32 - II. ���ϵ��´�ӡ������ II
{
	if (!root)
	{
		return {};
	}
	queue<TreeNode*> q;
	vector< vector<int> > result;
	q.push(root);
	while (!q.empty())
	{
		int i = q.size();
		vector<int> tmp;
		while (i > 0)
		{
			root = q.front();
			q.pop();
			--i;
			tmp.push_back(root->val);
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

vector<vector<int>> levelOrder_iii(TreeNode* root)  //������32 - III. ���ϵ��´�ӡ������ III
{
	if (!root)
	{
		return {};
	}
	bool flag = true;  //��һ���Ƿ��Ǵ�������
	queue<TreeNode*> q;
	vector< vector<int> > result;
	q.push(root);
	while (!q.empty())
	{
		flag = !flag;
		int i = q.size();
		vector<int> tmp;
		stack<TreeNode*> s;  //����queue��һ��������ұ�������ô�ڼ�����һ��ڵ����Һ���ʱ����Ҫ��һ��������Ҽ���s�У�Ȼ���ٲ��뵽q��
		while (i > 0)
		{
			root = q.front();
			q.pop();
			--i;
			tmp.push_back(root->val);
			if (flag)  //�����һ���Ǵ������ң���ôӦ���ȼ����Һ���
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
			else  //�����һ���Ǵ���������ôӦ���ȼ�������
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
		}
		while (!s.empty())
		{
			q.push(s.top());
			s.pop();
		}
		result.push_back(tmp);
	}
	return result;
}

vector<vector<int>> levelOrder_iii(TreeNode* root)  //������32 - III. ���ϵ��´�ӡ������ III,��ָoffer�Ľⷨ
{
	if (!root)
	{
		return {};
	}
	bool flag = true;  //��һ���Ƿ��Ǵ�������
	vector< vector<int> > result;
	vector< stack<TreeNode*> > vs(2); //��������ջ
	int cur = 0, next = 1;  //��ǰջ����һ��ջ
	vs[0].push(root);
	while (!vs[0].empty() || !vs[1].empty())  //����ջ��һ����Ϊ��
	{
		flag = !flag;
		vector<int> tmp;
		int i = vs[cur].size();
		while (i > 0)
		{
			root = vs[cur].top();
			vs[cur].pop();
			--i;
			tmp.push_back(root->val);
			if (flag)  //��һ��Ϊ����,��ʾ��һ��ı���˳���Ǵ��ҵ���,��ôӦ���ȼ����Һ��ӣ�����ջ��˳����Ǵ�����
			{
				if (root->right)
				{
					vs[next].push(root->right);
				}
				if (root->left)
				{
					vs[next].push(root->left);
				}
			}
			else  //��һ���������󣬱�ʾ��һ���Ǵ������ұ�������ô�ȼ�������,����ջ��˳����Ǵ�������
			{
				if (root->left)
				{
					vs[next].push(root->left);
				}
				if (root->right)
				{
					vs[next].push(root->right);
				}
			}
		}
		cur = 1 - cur;  //��һ��ѭ����cur����1-cur��
		next = 1 - next; //��һ��ѭ����next����1-next��
		result.push_back(tmp);
	}
	return result;
}

bool verifyPostorder_item(vector<int>& postorder)
{
	if (postorder.size() <= 1)
	{
		return true;
	}
	int rootVal = postorder[postorder.size() - 1];  //�������rootֵ�����
	bool flag = true;  //�Ƿ�����������ֵ
	vector<int> l, r;  //����������ֵ����
	for (int i = 0; i < postorder.size() - 1; ++i)
	{
		if (flag)  //С��rootֵ
		{
			if (postorder[i] > rootVal)  //flagΪtrue��˵����С��root��ֵ������ʱ������һ������rootֵ��˵��֮��Ӧ����������������
			{
				r.push_back(postorder[i]);
				flag = false;  //��ʱ��������������ֵ�����flagΪfalse
			}
			else
			{
				l.push_back(postorder[i]);
			}
		}
		else //��ʱ��������������ֵ,������˵Ӧ���Ǵ���root��ֵ
		{
			if (postorder[i] < rootVal)  //����˵��ʱӦ�ö�����������ֵ,��Ӧ�ô���rootֵ�����Ǵ�ʱ�и�ֵȴС��root��ֵ����ô˵�����Ƕ���������
			{
				return false;
			}
			else
			{
				r.push_back(postorder[i]);
			}
		}
	}
	return verifyPostorder_item(l) && verifyPostorder_item(r);  //ֻ�е����������������������Ƕ���������
}
bool verifyPostorder(vector<int>& postorder)  //������33. �����������ĺ����������
{
	if (postorder.size() <= 1)
	{
		return true;
	}
	return verifyPostorder_item(postorder);
}

vector< vector<int> > pathSum_result;
void pathSum_dfs(int sum, vector<int> tmp, TreeNode* root)
{
	if (!root)
	{
		return;
	}
	tmp.push_back(root->val);  //�����ʱ�ĸ��ڵ㣬��·����
	if (root->val == sum && !root->left && !root->right)  //���ʣ���sum�͵�ǰ���ڵ���ͬ�����Ҵ�ʱ�Ľڵ�ΪҶ�ӽڵ㣬��ô����
	{
		pathSum_result.push_back(tmp);
	}
	else  
	{
		//����Ҫ�����Ƿ�Ҷ�ӽڵ㣬��Ȼ�п��ܴ���root->val = sum��������������������ĵ����ˣ������Ҫ�ݹ���ȥ
		//����Ҫ������root->val != sum,�Ǹ�Ӧ�÷ֱ�ȡ��������Ѱ��,Ϊ�յ������Ͳ�Ҫ����,��Ϊ�վ͸�����Ҫ��������
		if (root->left)
		{
			pathSum_dfs(sum - root->val, tmp, root->left);
		}
		if (root->right)
		{
			pathSum_dfs(sum - root->val, tmp, root->right);
		}
	}
}
vector<vector<int>> pathSum(TreeNode* root, int sum)  //������34. �������к�Ϊĳһֵ��·��
{
	if (!root)
	{
		return {};
	}
	pathSum_dfs(sum, {}, root);
	return pathSum_result;
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
unordered_map<Node*, Node*> copyRandomList_m;  //���Դ�ڵ�͸��ƽڵ��ֵ��
Node* copyRandomList(Node* head)  //������35. ��������ĸ���
{
	if (!head)
	{
		return head;
	}
	Node* result = new Node(head->val); 
	Node* tmp = result;  //�������ӵ���ʱ�ڵ�
	Node* head_r = head;  //����randomָ�������
	//���ȸ���next���������Ƴ���
	copyRandomList_m.insert(pair<Node*, Node*>(head, result));
	head = head->next;
	while (head)
	{
		Node* t = new Node(head->val);
		tmp->next = t;
		copyRandomList_m.insert(pair<Node*, Node*>(head, t)); //�����ֵ��
		head = head->next;
		tmp = tmp->next;
	}
	//Ȼ��ʼ��ֵrandomָ��
	tmp = result;
	while (head_r && tmp) //������ͬ���ȣ�����дһ����ʵҲ����
	{
		if (head_r->random && copyRandomList_m.count(head_r->random))  //�������
		{
			tmp->random = copyRandomList_m[head_r->random];
		}
		else
		{
			tmp->random = nullptr;
		}
		head_r = head_r->next;
		tmp = tmp->next;
	}
	return result;
}

Node* copyRandomList(Node* head)  //������35. ��������ĸ���,��ָoffer�������ռ�ΪO(1)��ʱ��ΪO(n),�ҿ��ˣ�������ɺ�Դ����Ҫ�ָ�ԭ��
{
	if (!head)
	{
		return head;
	}
	//���ƵĽڵ������ڱ����ƽڵ�ĺ���
	Node* tmp = head;
	while (tmp)
	{
		Node* t = new Node(tmp->val);
		t->next = tmp->next;
		tmp->next = t;  //�����ƵĽڵ�ŵ������ƽڵ�ĺ���
		tmp = tmp->next->next;
	}
	//�����������1-1'-2-2'-3-3'������
	//����������random��ָ��,����1��randomָ��3����ôֻ��Ҫ��1'��randomָ��3'
	tmp = head;
	while (tmp)
	{
		if (!tmp->random)  //���Դ�����е�randomΪ�գ���ô���ƽڵ��randomҲ�ÿ�
		{
			tmp->next->random = nullptr;
		}
		else  //����Ļ������ƽڵ��random����Դ�ڵ�random����������Ҳ����Դ�ڵ�random����һ��
		{
			tmp->next->random = tmp->random->next;
		}
		tmp = tmp->next->next;  //ָ����һ��Դ����Ľڵ�
	}
	//�����ƵĽڵ�����,Դ����Ҫ�ָ�ԭ��
	Node* result = head->next;
	Node* t = result;
	tmp = head;
	while (t->next)
	{
		tmp->next = t->next;
		tmp = tmp->next;
		t->next = tmp->next;
		t = t->next;
	}
	tmp->next = nullptr;
	return result;
}

class Node {
public:
	int val;
	Node* left;
	Node* right;

	Node() {}

	Node(int _val) {
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};
Node* treeToDoublyList_item(Node* root) //�����ڲ���˫�����������׺�β����������
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		return root;
	}
	Node* l = treeToDoublyList_item(root->left);  //��������Ϊ˫����������û����β����,��������ȱ�����ߵ�
	Node* head = l;
	if (!l)  //������Ϊ��
	{
		head = root;
	}
	else
	{
		//�ҵ�����������ҵĽڵ�
		while (l->right)
		{
			l = l->right;
		}
		//���һ���������Ľڵ�ĺ��Ϊroot��root��ǰ��Ϊ���һ����������������Ľڵ�
		//lΪ���Ľڵ㣬�������ڵ�Ϊnullptr
		l->right = root;
		root->left = l;
	}
	Node* r = treeToDoublyList_item(root->right);  //��������Ϊ˫����������û����β������Ū��root����ߵģ�������������ұߵ�
	if(r)  //����������β���������rΪnullptrʱ�򲻹��ˣ���ʱroot�������һ��
	{
		//��������һ��Ϊroot�ĺ�̣�root�ĺ��Ϊ���������������һ��
		root->right = r;
		r->left = root;  //rΪ��ҵĽڵ㣬������ҽڵ�Ϊnullptr��������������һֱ������ѭ������������ѭ��
	}
	return head;
}
Node* treeToDoublyList(Node* root)  //������36. ������������˫������
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		root->left = root;
		root->right = root;
		return root;
	}
	Node* result = treeToDoublyList_item(root); //��ʱ��Ϊһ������������β��û��������
	Node* tmp = result;
	while (tmp->right)
	{
		tmp = tmp->right;
	}
	tmp->right = result;
	result->left = tmp;
	return result;
}

void treeToDoublyList_inorder(Node* root, stack<Node*> &s)
{
	while (root)
	{
		s.push(root);
		root = root->left;
	}
}
Node* treeToDoublyList(Node* root)  //������36. ������������˫������--�����������
{
	if (!root)
	{
		return nullptr;
	}
	if (!root->left && !root->right)
	{
		root->left = root;
		root->right = root;
		return root;
	}
	stack<Node*> s;
	Node* result = new Node(1);  //�ڱ��ڵ�
	Node* tmp = result;
	while (true)
	{
		treeToDoublyList_inorder(root, s);
		if (s.empty())
		{
			break;
		}
		root = s.top();
		s.pop();
		tmp->right = root;
		root->left = tmp;
		tmp = tmp->right;
		//������������ĵ�������
		root = root->right;
	}
	//break��tmpΪ���һ��Ԫ��
	result = result->right;  //�����ڱ�
	result->left = tmp;
	tmp->right = result;
	return result;
}

class Codec {  //������37. ���л�������
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {  //��α������л�--����
		if (!root)
		{
			return "[]";
		}
		string s;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			root = q.front();
			q.pop();
			if (!root)  //rootΪ��
			{
				s += "null,";
				continue;
			}
			//��Ϊ�յĻ�
			s += std::to_string(root->val);
			s += ",";
			//������һ��
			q.push(root->left);
			q.push(root->right);
		}
		//����������null�Ͷ���
		while (s[s.size() - 1] < '0' || s[s.size() - 1] > '9')
		{
			s.pop_back();
		}
		s = "[" + s + "]";
		return s;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.size() == 0)
		{
			return nullptr;
		}
		while (data.size() > 0 && (data[data.size() - 1] < '0' || data[data.size() - 1] > '9')) //���������
		{
			data.pop_back();
		}
		if (data.size() == 0)  //�������
		{
			return nullptr;
		}
		//����ǰ��ķ��������ַ����������������ַ���
		int i = 0;
		while (i < data.size())
		{
			if ((data[i] >= '0' && data[i] <= '9') || data[i] == '-' || data[i] == '+')
			{
				break;
			}
			++i;
		}
		data = data.substr(i);
		i = 0;
		queue<TreeNode*> q_t; //�洢���е�ָ��
		while (i < data.size())
		{
			string tmp;
			while (i < data.size() && data[i] != ',')
			{
				tmp += data[i];
				++i;
			}
			if (tmp == "null")
			{
				q_t.push(nullptr);
			}
			else if (tmp.size() > 0)
			{
				TreeNode* A = new TreeNode(std::stoi(tmp));
				q_t.push(A);
			}
			++i;
		}
		if (q_t.empty())
		{
			return nullptr;
		}
		TreeNode* root = q_t.front();
		TreeNode* tmp = root;
		q_t.pop();
		queue<TreeNode*> q;  //���ڴ������ɵĽڵ�
		q.push(root);
		while (!q.empty())
		{
			tmp = q.front();
			q.pop();
			if (!q_t.empty())
			{
				tmp->left = q_t.front();
				q_t.pop();
				if (tmp->left)
				{
					q.push(tmp->left);
				}
			}
			else
			{
				break;
			}
			if (!q_t.empty())
			{
				tmp->right = q_t.front();
				q_t.pop();
				if (tmp->right)
				{
					q.push(tmp->right);
				}
			}
			else
			{
				break;
			}
		}
		return root;
	}
};

void permutation_dfs(string &s, unordered_set<int> &us, unordered_set<string> &st, string &tmp)  //���ø��죬��ö�
{
	if (tmp.size() == s.size())
	{
		if (!st.count(tmp))
		{
			st.insert(tmp);
		}
		return;
	}
	else if (tmp.size() > s.size())
	{
		return;
	}
	for (int i = 0; i < s.size(); ++i)
	{
		unordered_set<int>::iterator ifind = us.find(i);
		if (ifind == us.end())  //˵����ǰ�±��Ԫ��û��
		{
			tmp.push_back(s[i]);
			us.insert(i);
			permutation_dfs(s, us, st, tmp);
			us.erase(i);
			tmp.pop_back();  //tmpҲҪ�ѵ�ǰ�ַ�ȥ��
		}
	}
}
vector<string> permutation(string s)  //������38. �ַ���������
{
	if (s.size() == 0)
	{
		return {};
	}
	if (s.size() == 1)
	{
		return { s };
	}
	unordered_set<string> st; //��ʱ��Ž��
	unordered_set<int> us;  //����±�ֵ�Ƿ��ù���
	string tmp;  //��������
	permutation_dfs(s, us, st, tmp);
	vector<string> result;
	unordered_set<string>::iterator i = st.begin();
	for (; i != st.end(); i++)
	{
		result.push_back(*i);
	}
	return result;
}

int majorityElement(vector<int>& nums)  //������39. �����г��ִ�������һ�������
{
	//ʱ�临�Ӷ�ΪO(n), �ռ�O(n)
	if (nums.size() == 0)
	{
		return -1;
	}
	int n = nums.size();
	unordered_map<int, int> um;
	for (int i : nums)
	{
		um[i]++;
		if (um[i] >= n / 2 + 1)
		{
			return i;
		}
	}
	return -1;
}

int majorityElement(vector<int>& nums)  //������39. �����г��ִ�������һ�������
{
	//ʱ�临�Ӷ�ΪO(n), �ռ�O(1)
	//ò����ʲôͶƱ�㷨
	if (nums.size() == 0)
	{
		return -1;
	}
	int candidate = nums[0];  //��ѡ��
	int count = 1;  //��ѡ�˵Ĵ���
	for (int i=1; i<nums.size(); ++i)
	{
		if (count == 0)
		{
			candidate = nums[i];
			count = 1;
		}
		else
		{
			if (nums[i] == candidate)
			{
				++count;
			}
			else
			{
				--count;
			}
		}
	}
	return count > 0 ? candidate : -1;
}

vector<int> getLeastNumbers(vector<int>& arr, int k)  //������40. ��С��k����
{
	if (arr.size() == 0 || k == 0 || k > arr.size())
	{
		return {};
	}
	multiset<int> ms;
	multiset<int>::iterator toDel;
	for (int i : arr)
	{
		if (ms.size() < k)
		{
			ms.insert(i);
		}
		else
		{
			if (i < *(ms.rbegin()))
			{
				toDel = ms.end();
				--toDel;
				ms.erase(toDel);
				ms.insert(i);
			}
		}
	}
	vector<int> result;
	result.assign(ms.begin(), ms.end());
	return result;
}

class MedianFinder {  //������41. �������е���λ��
public:
	/** initialize your data structure here. */
	vector<int> minHeap, maxHeap; //��С�Ѻ����ѣ�������С������������ڵ��������������
	MedianFinder() {

	}

	void addNum(int num) {
		if (((minHeap.size() + maxHeap.size()) & 1) == 0)  //���ƽ��������,�������󶥶ѷ�
		{
			//�������󶥶ѷ�Ҫע���ˣ�������������С�ѵĶѶ�Ԫ��(������С�ѵ���Сֵ)��Ļ���
			//��ôӦ�ý�������ŵ���С������ҽ���С�ѵ���С���ŵ�������
			if (minHeap.size() > 0 && num > minHeap[0])  //���������С�ѵĶѶ�Ԫ��(������С�ѵ���Сֵ)��
			{
				minHeap.push_back(num);  //�Ž���С��
				push_heap(minHeap.begin(), minHeap.end(), greater<int>());  //���µ����ѽṹ,greater����С�ѵ�
				num = minHeap[0];  //��num������Сֵ
				//pop_heap()������İ������С����Ԫ�شӶ��е�������������������ѡ�
				//����first��last������Ȼ��[first, last - 1)������������һ����
				pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
				minHeap.pop_back();  //��last����ɾ��
			}
			maxHeap.push_back(num);
			push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
		}
		else  //��������С�ѷ�
		{
			//����ҲҪע�⣬����С�ѷŵ�ʱ��������ֵС�����ѵ����ֵʱ��Ӧ�÷��������У�Ȼ�����ѵ����ֵ�ŵ���С��
			if (maxHeap.size() > 0 && num < maxHeap[0])  //���ֵС�����ѵ����ֵ
			{
				maxHeap.push_back(num);
				push_heap(maxHeap.begin(), maxHeap.end(), less<int>());
				num = maxHeap[0];
				pop_heap(maxHeap.begin(), maxHeap.end(), less<int>());
				maxHeap.pop_back();
			}
			minHeap.push_back(num);
			push_heap(minHeap.begin(), minHeap.end(), greater<int>());
		}
	}

	double findMedian() {
		if (minHeap.size() == 0 && maxHeap.size() == 0)
		{
			return 0.0;
		}
		else if (minHeap.size() == 0)
		{
			return maxHeap[0] * 1.0;
		}
		else if (maxHeap.size() == 0)
		{
			return minHeap[0] * 1.0;
		}
		else
		{
			if (((minHeap.size() + maxHeap.size()) & 1) == 0)  //�����ż��������ô���������Ѷ���ӳ���2
			{
				return (minHeap[0] + maxHeap[0]) * 1.0 / 2.0;
			}
			else  //������
			{
				//��Ϊ�������󶥶ѷţ����Ҫȥ�󶥶�Ѱ��
				return maxHeap[0];
			}
		}
	}
};

int maxSubArray(vector<int>& nums)  //������42. ���������������
{
	if (nums.size() == 0)
	{
		return 0;
	}
	if (nums.size() == 1)
	{
		return nums[0];
	}
	int result = nums[0];
	int sum = 0;
	for (int i : nums)
	{
		if (i > 0)  //˵����sum����������
		{
			sum += i;
		}
		else  //���������ã����ϻ�С��ԭ����,�������¿�ʼ
		{
			sum = i;
		}
		result = max(result, sum);
	}
	return result;
}

int maxSubArray(vector<int>& nums)  //������42. ���������������--��̬�滮
{
	if (nums.size() == 0)
	{
		return 0;
	}
	if (nums.size() == 1)
	{
		return nums[0];
	}
	vector<int> dp(nums.size(), 0);  //�±��i������Ϊ��β������������ֵ
	dp[0] = nums[0];
	int result = nums[0];
	for (int i=1; i<nums.size(); ++i)
	{
		if (dp[i - 1] < 0)  //������i-1�����ַ�С��0����ô������
		{
			dp[i] = nums[i];
		}
		else
		{
			dp[i] = dp[i - 1] + nums[i];
		}
		result = max(result, dp[i]);
	}
	return result;
}

int main()
{
	//������03. �������ظ�������
	//findRepeatNumber

	//������04. ��ά�����еĲ���
	//findNumberIn2DArray

	//������05. �滻�ո�
	//replaceSpace

	//������06. ��β��ͷ��ӡ����
	//reversePrint

	//������07. �ؽ�������
	//buildTree

	//����������һ�����---��ţ����
	//GetNext

	//������09. ������ջʵ�ֶ���
	//CQueue

	//�ö���ʵ��ջ--09��������

	//������10- I. 쳲���������
	//fib

	//������10- II. ������̨������
	//numWays

	//������11. ��ת�������С����
	//minArray

	//������12. �����е�·��
	//exist

	//������13. �����˵��˶���Χ
	//movingCount

	//������14- I. ������
	//cuttingRope

	//������14- II. ������ II
	//cuttingRope

	//������15. ��������1�ĸ���
	//hammingWeight

	//������16. ��ֵ�������η�
	//myPow

	//������17. ��ӡ��1������nλ��
	//printNumbers

	//������18. ɾ������Ľڵ�
	//deleteNode

	//18������--ɾ�����������е��ظ�Ԫ��,ɾ�������ظ���Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ��
	//deleteDuplicates

	//18������--ɾ�����������е��ظ�Ԫ�� II, ֻ����ԭʼ������ û���ظ����ֵ�����

	//������19. ������ʽƥ��
	//isMatch

	//������20. ��ʾ��ֵ���ַ���
	//isNumber

	//������21. ��������˳��ʹ����λ��ż��ǰ��
	//exchange

	//������22. �����е�����k���ڵ�
	//getKthFromEnd

	//������23. ������������
	//detectCycle

	//������24. ��ת����
	//reverseList

	//������25. �ϲ��������������
	//mergeTwoLists

	//������26. �����ӽṹ
	//isSubStructure

	//������27. �������ľ���
	//mirrorTree

	//������28. �ԳƵĶ�����
	//isSymmetric

	//������29. ˳ʱ���ӡ����
	//spiralOrder

	//������30. ����min������ջ
	//class MinStack

	//������31. ջ��ѹ�롢��������
	//validateStackSequences

	//������32 - I. ���ϵ��´�ӡ������
	//levelOrder

	//������32 - II. ���ϵ��´�ӡ������ II
	//levelOrder_ii

	//������32 - III. ���ϵ��´�ӡ������ III
	//levelOrder_iii

	//������33. �����������ĺ����������
	//verifyPostorder

	//������34. �������к�Ϊĳһֵ��·��
	//pathSum

	//������35. ��������ĸ���
	//copyRandomList

	//������36. ������������˫������
	//treeToDoublyList

	//������37. ���л�������
	//class Codec

	//������38. �ַ���������
	//permutation

	//������39. �����г��ִ�������һ�������
	//majorityElement

	//������40. ��С��k����
	//getLeastNumbers

	//������41. �������е���λ��
	//class MedianFinder

	//������42. ���������������
	//maxSubArray
	return 0;
}