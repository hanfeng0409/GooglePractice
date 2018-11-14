#include<iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
const int MAXL = 51;
const int MAXNUM = 50 * 51 / 2;

struct NodeB
{
	vector<string> nice;
}nb[MAXL];

bool is_element_in_vector(vector<string> v, string element) {
	vector<string>::iterator it;
	it = find(v.begin(), v.end(), element);
	if (it != v.end()) {
		return true;
	}
	else {
		return false;
	}
}

int f1() {
	int ans = 0;
	int L = 0;
	int T = 0;
	char arra[MAXL];
	char arrb[MAXL];
	string str;
	string a;
	string b;
	freopen("..\\data\\A-large-practice.in", "r", stdin);
	freopen("..\\data\\A-large-practice.out", "w", stdout);

	scanf("%d", &T);
	for (int _ = 1; _ <= T; _++)
	{
		scanf("%d", &L);
		scanf("%s", &arra);
		scanf("%s", &arrb);
		a = arra;
		b = arrb;
		ans = 0;
		for (int i = 1; i <= L; i++)
		{
			for (int j = 0; j < L - i+1; j++)
			{
				str.assign(b,j,i);
				sort(str.begin(), str.end());
				nb[i].nice.push_back(str);
			}
		}
		for (int i = 1; i <= L; i++)
		{
			for (int j = 0; j < L - i+1; j++)
			{
				str.assign(a, j, i);
				sort(str.begin(), str.end());
				if (is_element_in_vector(nb[i].nice, str))
				{
					ans++;
				}
			}
			vector<string>().swap(nb[i].nice);
		}
		printf("Case #%d: %lld\n", _, ans);
	}

	return 0;
}