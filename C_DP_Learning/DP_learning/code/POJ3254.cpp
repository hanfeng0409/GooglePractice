#include<iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 12 + 1;
const int MAX_S = 1 << 12 + 1;
struct Node
{
	int num = 1;
	vector<int> id = {0};
	int dp[MAX_S] = { 0 };
}node[MAXN];

int poj3254();

int highbit(int x)
{
	int j = 0;
	for (int i = 0; i < MAXN; i++)
	{
		if (x&(1 << i)) j=i;
	}
	return j+1;
}

int poj3254()
{
	int stat[MAX_S];

	int dp[MAXN][MAX_S] = { 0 };
	int T = 0;
	int N, M = 0;
	int code[MAXN] = { 0 };
	int tmp = 0;
	int case_num = 0;
	int ans = 0;
	freopen("..\\data\\poj.in", "r", stdin);
	scanf("%d", &T);
	for (int _ = 1; _ <= T; _++)
	{
		memset(dp, 0, sizeof(dp));
		memset(code, 0, sizeof(code));
		case_num = 0;
		ans = 0;
		scanf("%d %d", &N, &M);
		// init all grid encode
		for (int i = 0; i < N; i++)
		{
			for (int j = M-1; j >= 0; j--)
			{
				scanf("%d", &tmp);
				code[i] = code[i] | (tmp << j);
			}
		}

		// init ll stat
		for (int i = 0; i < (1 << MAXN); i++)
		{
			if (!(i&(i << 1)))
			{
				stat[case_num] = i;
				case_num++;
			}
		}

		//
		//node[0].id.push_back(stat[0]);
		int h = highbit(code[0]);
		for (int i = 0; i < case_num; i++)
		{
			if (stat[i] >= (1 << h)) break;
			if ((stat[i] & code[0])) {
				node[0].dp[stat[i]] = 1;
				node[0].num += 1;
				node[0].id.push_back(stat[i]);
			}
		}
		node[0].dp[0] = 1;

		for (int i = 1; i < N; i++)
		{
			int h = highbit(code[i]);
			for (int j = 1; j < case_num; j++)
			{
				if (stat[j] >= (1 << h)) break;
				if ((stat[j] & code[i]))
				{
					//node[i].dp[stat[j]] = 1;
					node[i].num += 1;
					node[i].id.push_back(stat[j]);
				}
			}
			//node[i].dp[0] = 1;

			for (int j = 0; j < node[i].num; j++)
			{
				for (int k = 0; k < node[i-1].num; k++)
				{
					if ((node[i].id[j] & node[i-1].id[k]) == 0)
					{
						node[i].dp[node[i].id[j]] += node[i - 1].dp[node[i - 1].id[k]];
					}
				}
			}

		}

		for (int i = 0; i < node[N-1].num; i++)
		{
			ans += node[N-1].dp[node[N-1].id[i]];
		}
		ans = ans % 100000000;
		cout << ans << endl;
	}
	return 0;
}