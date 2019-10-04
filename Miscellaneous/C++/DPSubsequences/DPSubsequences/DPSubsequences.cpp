#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;
typedef struct Node
{
	int val;
	struct Node* next;

	Node(int v) : val(v)
	{
		next = nullptr;
	};
} Node;


typedef struct LList
{
	Node* head;
	LList()
	{
		head = nullptr;
	}
	LList(Node *r)
	{
		if (r != nullptr) head = new Node(r->val);
		else head = nullptr;
	}
}LList;

LList *copyList(LList *l)
{
	LList *the_copy = new LList;
	if (l != nullptr)
	{
		if (l->head != nullptr)
		{
			Node *current = l->head;
			Node *previous = nullptr;
			while (current != nullptr)
			{
				if (the_copy->head == nullptr)
				{
					the_copy->head = new Node(l->head->val);
					previous = the_copy->head;
				}
				else
				{
					previous->next = new Node(current->val);
					previous = previous->next;
				}
				current = current->next;
			}
		}
	}
	return the_copy;
}

LList *change_front(int newKey, LList *l)
{
	Node r(newKey);
	if (!l || l->head == nullptr)
	{
		l = new LList(&r);
		return l;
	}
	//cout << "Change front from :" << l->head->val << " to : " << newKey << " : " << endl;
	l->head->val = newKey;
	return l;
}


LList *insert_back(int newKey, LList *l)
{
	//cout << "Inserting value :" << newKey << "   ";
	Node r(newKey);
	if (!l || !l->head)
	{
		l = new LList(&r);
		return l;
	}
	Node *current = l->head;
	Node *previous = nullptr;
	while (current != nullptr)
	{
		previous = current;
		current = current->next;
	}
	current = new Node(newKey);
	previous->next = current;
	return l;
}

LList *reverse_list(LList *l)
{
	Node *previous = nullptr;
	Node *_next = nullptr;
	if (l && l->head)
	{
		Node *my_Node = l->head;
		while (my_Node != nullptr)
		{
			_next = my_Node->next;
			my_Node->next = previous;
			previous = my_Node;
			my_Node = _next;
		}
	}
	LList* reverse_list = new LList;
	reverse_list->head = previous;
	return reverse_list;
}

void display(Node *myNode)
{
	if (myNode != nullptr)
	{
		cout << myNode->val;
		if (myNode->next != nullptr) cout << " ->";
		display(myNode->next);
	}
	else return;
}

int binarySearchLargestIndex_Inc(vector<int> const vec, int key)
{
	if (vec.empty()) return -1;
	int n = vec.size();
	int low = 1;
	int high = n - 1;
	int INF = numeric_limits<int>::max();
	int found = -1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (mid != 0 && vec[mid] == INF)
			high = mid - 1;
		else if (mid != n - 1 && vec[mid] < key && vec[mid + 1] > key)
			return mid;
		else
			low = mid + 1;
	}
	return found;
}


int binarySearchLargestIndex_NonDecreasing(vector<int> const vec, int key)
{
	if (vec.empty()) return -1;
	int n = vec.size();
	int low = 1;
	int high = n - 1;
	int INF = numeric_limits<int>::max();
	int found = -1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (mid != 0 && vec[mid] == INF)
			high = mid - 1;

		else if (mid != n - 1 && vec[mid] <= key)
		{
			if (vec[mid + 1] > key)
			{
				cout << " RESULTAT IS : " << mid << " \n";
				return mid;
			}
			else
				low = mid + 1;
		}
		else
			low = mid + 1;
	}
	cout << " RESULTAT IS : " << found << " \n";
	return found;
}

int binarySearchLargestIndex_Dec(vector<int> const vec, int key)
{
	int n = vec.size();
	int found = -1;
	int INF_min = numeric_limits<int>::min();
	int low = 1;
	int high = n - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (vec[mid] > key)
		{
			found = mid;
			low = mid + 1;
		}
		else if (vec[mid] < key || vec[mid] == INF_min)
		{
			high = mid - 1;
		}
		else
			low = mid + 1;
	}
	return found;
}


int longestIncreasingSubsequence(vector<int> const a)
{
	int n = a.size();
	if (n == 0) return -1;
	int INF = numeric_limits<int>::max();
	vector<int> distances(n + 1, INF);
	vector<vector<LList*>> allsubsequencesfound(n + 1);
	vector<LList*> seqs(n + 1, nullptr);
	int L = 1;
	for (int i = 0; i < a.size(); i++)
	{
		int current = a[i];
		if (current < distances[1])
		{
			distances[1] = current;
			seqs[1] = change_front(current, seqs[1]);
			Node single(current);
			LList *single_new = new LList(&single);
			allsubsequencesfound[1].push_back(single_new);
		}
		else
		{
			int j = binarySearchLargestIndex_Inc(distances, current);
			if (j != -1)
			{
				distances[j + 1] = current;
				seqs[j + 1] = copyList(seqs[j]); // you must copy here the LINKED LIST
				seqs[j + 1] = insert_back(current, seqs[j + 1]);
				if (j + 1 > L)
				{
					L = L + 1;
				}
				for (int u = 0; u < allsubsequencesfound[j].size(); u++)
				{
					LList *one = copyList(allsubsequencesfound[j][u]);
					LList * rev = reverse_list(one);
					one = reverse_list(rev);
					int head = (!rev || !rev->head) ? -1 : rev->head->val;
					if (head != -1 && head < current)
					{
						LList *one_changed = copyList(one);
						one_changed = insert_back(current, one_changed);
						allsubsequencesfound[j + 1].push_back(one_changed);
					}

				}
			}
		}
	}
	return L;
	//cout << "THE LONGEST INCREASING SUBSEQUENCE HAS LENGTH :" << L << "  \n";
	/*cout << "ONE POSSIBILITY OF A SUSBSEQUENCE OF LENGTH " << L << " is : ";
	LList *one = allsubsequencesfound[L][0];
	if (one) display(one->head);
	cout << "\n";*/
}




int longestDecreasingSubsequence(vector<int> const a)
{
	int n = a.size();
	if (n == 0) return -1;
	int INF = numeric_limits<int>::min();
	vector<int> distances(n + 1, INF);
	vector<LList*> seqs(n + 1, nullptr);
	vector<vector<LList*>> allsubsequencesfound(n + 1);
	int L = 1;
	for (int i = 0; i < a.size(); i++)
	{
		int current = a[i];

		if (current > distances[1])
		{
			distances[1] = current;
			seqs[1] = change_front(current, seqs[1]);
			Node single(current);
			LList *single_new = new LList(&single);
			allsubsequencesfound[1].push_back(single_new);
		}
		else
		{
			int j = binarySearchLargestIndex_Dec(distances, current);
			if (j != -1)
			{
				distances[j + 1] = current;
				seqs[j + 1] = copyList(seqs[j]);
				seqs[j + 1] = insert_back(current, seqs[j + 1]);
				if (j + 1 > L)
					L = L + 1;
				for (int u = 0; u < allsubsequencesfound[j].size(); u++)
				{
					LList *one = copyList(allsubsequencesfound[j][u]);
					LList * rev = reverse_list(one);
					one = reverse_list(rev);
					int head = (!rev || !rev->head) ? -1 : rev->head->val;
					if (head != -1 && head > current)
					{
						LList *one_changed = copyList(one);
						one_changed = insert_back(current, one_changed);
						allsubsequencesfound[j + 1].push_back(one_changed);
					}
				}
			}
		}
	}
	//cout << "THE LONGEST DECREASING SUBSEQUENCE HAS LENGTH :" << L << "\n";
	///* TO DISPLAY ONE EXAMPLE OF THE LONGEST SUBSEQUENCE */
	//cout << "ONE POSSIBILITY OF A SUSBSEQUENCE OF LENGTH " << L << " is : ";
	//LList *one = allsubsequencesfound[L][0];
	//if (one) display(one->head);
	//cout << "\n";
	return L;
}

int longestNonDecreasingSubsequence(vector<int> const a)
{
	int n = a.size();
	if (n == 0) return -1;
	int INF = numeric_limits<int>::max();
	vector<int> distances(n + 1, INF);
	vector<LList*> seqs(n + 1, nullptr);
	vector<vector<LList*>> allsubsequencesfound(n + 1);
	int L = 1;
	for (int i = 0; i < a.size(); i++)
	{
		int current = a[i];
		if (current <= distances[1])
		{
			distances[1] = current;
			seqs[1] = change_front(current, seqs[1]);
			Node single(current);
			LList *single_new = new LList(&single);
			allsubsequencesfound[1].push_back(single_new);
		}
		else
		{
			int j = binarySearchLargestIndex_NonDecreasing(distances, current);
			if (j != -1)
			{
				distances[j + 1] = current;
				seqs[j + 1] = copyList(seqs[j]); //you must copy here the LINKED LIST
				seqs[j + 1] = insert_back(current, seqs[j + 1]);

				if (j + 1 > L)
					L = L + 1;
				for (int u = 0; u < allsubsequencesfound[j].size(); u++)
				{
					LList *one = copyList(allsubsequencesfound[j][u]);
					LList * rev = reverse_list(one);
					one = reverse_list(rev);
					int head = (!rev || !rev->head) ? -1 : rev->head->val;
					if (head != -1 && head <= current)
					{
						LList *one_changed = copyList(one);
						one_changed = insert_back(current, one_changed);
						allsubsequencesfound[j + 1].push_back(one_changed);
					}
				}
			}
		}
	}
	/*cout << "THE LONGEST NON-DECREASING SUBSEQUENCE HAS LENGTH :" << L << "\n";
	cout << "ONE POSSIBILITY OF A SUSBSEQUENCE OF LENGTH " << L << " is : ";
	LList *one = allsubsequencesfound[L][0];
	if (one) display(one->head);
	cout << "\n";*/
	return L;
}


template<typename U>
void printLCS(vector<U> X, vector<U>Y, vector<vector<int>> const c, int i, int j)
{
	if (i <= 0 || j <= 0)
		return;
	if (X[i - 1] == Y[j - 1] && c[i][j] == (c[i - 1][j - 1] + 1))
	{
		printLCS(X, Y, c, i - 1, j - 1);
		cout << Y[j - 1]; // or put cout << X[i - 1];
	}
	else if (i > 0 && j > 0 && c[i - 1][j] >= c[i][j - 1])
	{
		printLCS(X, Y, c, i - 1, j);
	}
	else
		printLCS(X, Y, c, i, j - 1);
}

/* finding the longest common ancestor between two vector inputs*/
template<typename U>
int LCS(vector<U> X, vector<U > Y)
{
	int size_X = X.size();
	int size_Y = Y.size();
	int length = 0;
	vector<int> init(size_Y + 1);
	vector<vector<int>> c(size_X + 1, init);
	for (unsigned int i = 1; i < 1 + size_X; i++)
		c[i][0] = 0;
	for (unsigned int j = 0; j < 1 + size_Y; j++)
		c[0][j] = 0;
	for (unsigned int u = 1; u < 1 + size_X; u++)
	{
		for (unsigned int v = 1; v < 1 + size_Y; v++)
		{
			if (X[u - 1] == Y[v - 1])
			{
				c[u][v] = c[u - 1][v - 1] + 1;
			}
			else if (c[u - 1][v] >= c[u][v - 1])
			{
				c[u][v] = c[u - 1][v];
			}
			else
				c[u][v] = c[u][v - 1];
		}
	}
	cout << "Printing the longest common ancestor : \n";
	printLCS(X, Y, c, size_X, size_Y);
	cout << "Printing the longest common ancestor has length : " << c[size_X][size_Y] << " \n";
	return c[size_X][size_Y];
}

