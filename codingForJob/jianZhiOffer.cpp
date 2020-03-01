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
	return 0;
}