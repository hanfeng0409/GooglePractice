#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <tuple>
#include <bitset>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <iomanip>
using namespace std;
typedef long long ll;
const int P = 1 << 15;
int map_arr[105][105];
int routine[105][105];
int tag_for_trap[105][105];
int dir[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
vector < tuple<int, int, int> > trap;
int energe[P];
int exitFlag[P];
int remainNum[P];
int dp[P];
int T=0;
int trap_num = 0;
int N, M, E, Sr, Sc, Tr, Tc = 0;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

ll dfs(int mask)
{
	if (~dp[mask]) return dp[mask];
	ll ans = -1;
	if (exitFlag[mask] == 1) ans = energe[mask];

	for (int i = 0; i < trap_num; i++)
	{
		if ((remainNum[mask] >> i) & 1)
		{
			if (energe[mask] + map_arr[get<0>(trap[i])][get<1>(trap[i])] >= 0)
			{
				ans = max(ans, dfs(mask | (1 << i)));
			}
		}
	}
	dp[mask] = ans;
	return ans;
}



int main()
{
	freopen("..\\data\\C-large-practice.in","r",stdin);
	freopen("..\\data\\C-large-practice.out2", "w", stdout);
	scanf("%d",&T);
	for (int _ = 1; _ <= T; _++)
	{
		scanf("%d %d %d %d %d %d %d", &N, &M, &E, &Sr, &Sc, &Tr, &Tc);

		trap.clear();
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				scanf("%d", &map_arr[i][j]);
				if (map_arr[i][j]<0 && map_arr[i][j]>-100000)
				{
					trap.emplace_back(i, j, map_arr[i][j]);
					tag_for_trap[i][j] = trap.size() - 1;
				}
			}
		}

		trap_num = trap.size();

		for (int i = 0; i < 1 << trap_num; i++)
		{
			ll remain_e = E;
			for (int j = 0; j < trap_num; j++)
			{
				if ((i >> j) & 1)
				{
					remain_e += get<2>(trap[j]);
					map_arr[get<0>(trap[j])][get<1>(trap[j])] = 0;
				}
			}

			memset(routine, 0, sizeof(routine));
			queue<tuple<int, int>> Q;
			int next_x, next_y = 0;
			int remain_t = 0;
			int flag = 0;
			Q.push(make_tuple(Sr, Sc));
			routine[Sr][Sc] = 1;
			while (!Q.empty())
			{
				int x = get<0>(Q.front());
				int y = get<1>(Q.front());
				Q.pop();
				if (x == Tr && y == Tc)
				{
					flag = 1;
				}
				for (int i = 0; i < 4; i++)
				{
					next_x = x + dir[i][0];
					next_y = y + dir[i][1];
					if (routine[next_x][next_y] == 1 || map_arr[next_x][next_y] == -100000 || next_x<1 || next_x > N || next_y<1 || next_y > M)
					{
						continue;
					}
					if (map_arr[next_x][next_y] < 0)
					{
						remain_t |= 1 << tag_for_trap[next_x][next_y];
						continue;
					}
					remain_e += map_arr[next_x][next_y];
					routine[next_x][next_y] = 1;
					Q.push(make_tuple(next_x, next_y));
				}

			}
			exitFlag[i] = flag;
			remainNum[i] = remain_t;
			energe[i] = remain_e;

			for (int j = 0; j < trap_num; j++)
			{
				if ((i >> j) & 1)
				{
					map_arr[get<0>(trap[j])][get<1>(trap[j])] = get<2>(trap[j]);
				}
			}


		}
		printf("Case #%d: %lld\n", _, dfs(0));

	}
	
}