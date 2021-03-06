// 622.cpp : Defines the entry point for the console application.
//  158 (string s, t)

#include "stdafx.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<set>
#include<queue>
#include<iostream>
using namespace std;

class Solution158 {
public:
	bool validAnagram(string s, string t) {
		if (s.size() != t.size()) return false;
		int m[26] = { 0 };
		for (int i = 0; i < s.size(); ++i) ++m[s[i] - 'a'];
		for (int j = 0; j < t.size(); ++j) {
			if (--m[t[j] - 'a'] < 0) return false;
		}
		return true;
	}
};

class Solution161 {
public:
	void rotateImage(vector<vector<int>> &matr){
		int n=matr.size();
		for (int i = 0; i < n; ++i) {
			for (int j=i+1; j<n; ++j) {
				int temp = matr[i][j];
				matr[i][j] = matr[j][i];
				matr[j][i] = temp;
			}
			reverse(matr[i].begin(), matr[i].end());
		}
	}
};

class Solution162 {
public:
	void setZeroes(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return ;
		int m = matrix.size();
		int n = m > 0 ? matrix[0].size() : 0;
		bool rowFlag = false, colFlag = false;

		for (int i = 0; i < m; ++i) {
			if (matrix[i][0] == 0) rowFlag = true;
		}
		for (int j = 0; j < n; ++j) {
			if (matrix[0][j] == 0) colFlag = true;
		}

		for (int i = 1; i < m;++i) {
			for (int j = 1; j < n;++j) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		if (rowFlag) {
			for (int i = 0; i < n;++i) {
				matrix[0][i] = 0;
			}
		}
		if (colFlag) {
			for (int i = 0; i < m;++i) {
				matrix[i][0] = 0;
			}
		}
	}
};

class ListNode{
public:
	int val;
	ListNode *next;
	ListNode(int val){
		this->val = val;
		this->next = NULL;
	}
};

class Solution165 {
public:
	ListNode *mergeTwoSortedLists(ListNode *l1, ListNode *l2) {
		ListNode *dummy = new ListNode(-1), *res = dummy;
		while (l1&&l2) {
			if (l1->val < l2->val) {
				res->next = l1;
				l1 = l1->next;
			}
			else {
				res->next = l2;
				l2 = l2->next;
			}
			res = res->next;
		}
		if (l1) res->next = l1;
		if (l2) res->next = l2;
		res=dummy->next;
		delete dummy;
		return res;
	}
};

class Solution167 {
public:
	ListNode *addList(ListNode *l1, ListNode *l2) {
		ListNode *dummy=new ListNode(-1), *res=dummy;
		int carry = 0;
		while (l1 || l2) {
			int n1 = l1?l1->val:0, n2 = l2?l2->val:0;
			int sum = n1 + n2 + carry;
			res->next = new ListNode(sum%10);
			carry=sum/10;
			res = res->next;
			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}
		if (carry) res->next = new ListNode(1);
		return res->next;
	}
};

class Solution200 {
public:
	string longestPalindrome(string &s) {
//		int dp[sam.size()][sam.size()] = {0};
		vector<vector<int>> dp(s.size(), vector<int>(s.size()));
		int len = 0, left = 0, right = 0;

		for (int i = 0; i < s.size();++i) {
			dp[i][i] = 1;
			for (int j = 0; j < i; ++j) {
				dp[j][i] = (s[i] == s[j]) && (dp[j + 1][i - 1] || (i-j<2));
				if (dp[j][i] && len < i - j + 1) {
					len = i - j + 1;
					left = j;
					right = i;
				}
			}
		}
		return s.substr(left, right-left+1);
	}
};

//471. topKFreqWord
class Solution471 {
public:
	vector<string> topKFreqWord(vector<string> &word, int k) {
		vector<string> res;
		unordered_map<string, int> freq;
		map<int, set<string>> m;
		for (auto wd : word) ++freq[wd];
		for (auto a:freq) {
			m[a.second].insert(a.first);
		}
		for (auto it = m.rbegin(); it != m.rend();++it) {
			if (k <= 0) break;
			auto t = it->second;
			vector<string> v(t.begin(), t.end());
			if (k >= t.size()) {
				res.insert(res.end(), v.begin(), v.end());
			}
			else {
				res.insert(res.end(), v.begin(), v.begin()+k);
			}
			k -= t.size();
		}
		return res;
	}
};
//course schedule
class Solution615 {
public:

};

//course schedule II
class Solution616 {
public:

};
class Solution627 {
public:
	/**
	* @param s: a string which consists of lowercase or uppercase letters
	* @return: the length of the longest palindromes that can be built
	*/
	int longestPalindrome(string &s){
		unordered_map<int, int> mp;
		int cnt = 0, carry = 0, left = 0;
		for (int i = 0; i < s.size(); ++i) ++mp[s[i] - 'a' + 1];

		for (auto it = mp.begin(); it != mp.end();++it) {
			int num=it->second;
			if (num % 2 != 0) left = 1;
			carry += num / 2;
		}
		return carry * 2 + left;
	}
};

//647. Find All Anagrams in a String
class Solution647 {
public:
	vector<int> findAnagrams(string &s, string &p) {
		if (s.empty()) return {};
		int ns = s.size(), np = p.size(), i = 0;
		vector<int> cnt(128, 0), res;
		for (char c : p) ++cnt[c];
		while (i < ns) {
			bool success = true;
			vector<int> tmp = cnt;
			for (int j = i; j < i + np;++j) {
				if (--tmp[s[j]] < 0) {
					success = false;
					break;
				}
			}
			if (success) {
				res.push_back(i);
			}
			++i;
		}
		return res;
	}
};

class Solution647a {
public:
	vector<int> findAna(string &s, string &p) {
		if (s.empty()) return { };
		int ns = s.size(), np = p.size(), left=0, right=0;
		vector<int> cnt(128, 0), res;
		for (char c:p) ++cnt[c];
		while (right<ns) {
			if (cnt[s[right++]]-- >= 1) --np;
			if (np == 0) res.push_back(left);
			if (right - left == p.size() && cnt[s[left++]]++ > 0) ++np;
		}
		return res;
	}
};

class TreeNode{
public:
	int val;
	TreeNode *left, *right;
	TreeNode(int val) {
		this->val = val;
		this->left = this->right = NULL;
	}
};
class Solution661 {
public:
	TreeNode *convertBST(TreeNode *root) {
		if (!root) return NULL;
		convertBST(root->right);
		root->val += sum;
		sum = root->val;
		convertBST(root->left);
		return root;
	}
private:
	int sum = 0;
};

//maximum width of tree
class Solution1101 {
public:
	int maxWidthTree(TreeNode *root) {
		int res = 0;
		if (!root) return 0;
		queue<pair<TreeNode*, int>> q;
		q.push({root, 1});
		while (!q.empty()) {
			int left = q.front().second, right = left, n = q.size();
			for (int i = 0; i < n;++i) {
				auto t = q.front().first;
				right = q.front().second; q.pop();
				if (t->left) q.push({t->left,right*2});
				if (t->right) q.push({t->right, right*2+1});
			}
			res = max(res, right-left+1);
		}
		return res;
	}
};

//
//merge two tree
class Solution1126 {
public:
	TreeNode * mergeTwoTree(TreeNode *t1, TreeNode *t2) {
		if (!t1) return t2;
		if (!t2) return t1;

		TreeNode *res = new TreeNode(t1->val+t2->val);
		res->left = mergeTwoTree(t1->left, t2->left);
		res->right = mergeTwoTree(t1->right, t2->right);
		return res;
	}
};

//1137.construct string from binary tree
class Solution1137 {
public:
	string constructTree(TreeNode *t){
		if (!t) return "";
		string res = to_string(t->val);

		if (!t->left && !t->right) return res;
		res += "(" + constructTree(t->left) + ")";
		if (t->right) res += "(" + constructTree(t->right) + ")";
		return res;
	}
};

//1310 product of array except self;
class Solution1310 {
public:
	vector<int> productArrayExp(vector<int> &nums) {
		if (nums.empty()) return {};
		int n = nums.size();
		vector<int> res(n, 1);
		for (int i = 1; i < n; ++i) {
			res[i] = res[i - 1] * nums[i - 1];
		}
		int right = 1;
		for (int i = n - 1; i >= 0;--i) {
			res[i] *= right;
			right *= nums[i];
		}
		return res;
	}
};
//1334 Rotate Array
class Solution1334 {
public:
	vector<int> rotate(vector<int> &nums, int k) {
		if (nums.empty() || (k %=nums.size()) == 0) return nums;
		//at this step, the k is updated to k=k%nums.size();
		int n = nums.size();
		reverse(nums.begin(), nums.begin()+n-k);
		reverse(nums.begin()+n-k, nums.end());
		reverse(nums.begin(),nums.end());
		return nums;
	}
};

//1354 Pascal's Triangle II
class Solution1354 {
public:
	vector<int> getRow(int rowIndex){
		vector<int> res(rowIndex+1,0);
		if (rowIndex <= 0) return {};
		
		for (int i = 1; i <= rowIndex; ++i) {
			res[0] = 1;
			for (int j = rowIndex; j >= 1;--j) {
				res[j] = res[j] + res[j - 1];
			}
		}
		return res;
	}
};

//repeated substring pattern
class Solution {
public:
	bool repeatedSubstringPattern(string &s){
		if (s.empty()) return true;
		int n = s.size();
		for (int i = n / 2; i >= 1; --i) {
			if (n%i==0) {
				int c = n / i;
				string t = "";
				for (int j = 0; j < c; ++j) {
					t += s.substr(0,i);
				}
				if (t == s) return true;
			}
		}
		return false;
	}
};
int main()
{
	string aa = "tryewq", bb = "yeqwtr", cc="abcabcabc";
	int k = 3;
	//Solution158 x;
	//bool key = x.validAnagram(aa,bb);
	//Solution1354 y;
	//vector<int> tey = y.getRow(k);
	//vector<int> re1 = {1,2};
	//Solution1334 z;
	//vector<int> re2 = z.rotate(re1,k);
	Solution1310 stry;
	//bool rept = stry.repeatedSubstringPattern(cc);
	vector<int> tk = { 1,2,3,4 };
	vector<int> res = stry.productArrayExp(tk);
    return 0;
}

