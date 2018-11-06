// hud.cpp
//

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAX_COURSE_NUM = 1 << 15;

struct Course
{
	int dead_line = 0;
	int cost = 0;
	char name[105];
}course[15];

struct node {
	int pre_id = -1;
	int negative_score = 0;
	int total_cost = 0;
}dp[MAX_COURSE_NUM];

int visted[MAX_COURSE_NUM];

int hud()
{
	freopen("..\\data\\test.in", "r", stdin);
	freopen("..\\data\\test.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int _ = 1; _ <= T; _++)
	{
		int n = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%s %d %d", &course[i].name, &course[i].dead_line, &course[i].cost);
		}
		memset(visted, 0, sizeof(visted));
		for (int i = 0; i < ((1 << n) - 1); i++)
		{
			for (int j = 1; j <= n; j++)
			{
				int one_course = 1 << (j - 1);
				if ((i & one_course) == 0)
				{
					int next_stat = i | one_course;
					int next_cost = dp[i].total_cost + course[j - 1].cost;
					int tmp = next_cost - course[j - 1].dead_line;
					int next_score = max((tmp), 0) + dp[i].negative_score;
					if ((visted[next_stat] == 0) || (dp[next_stat].negative_score > next_score))
					{
						//if (((dp[next_stat].negative_score == next_score)  && (i > dp[next_stat].pre_id))|| (dp[next_stat].negative_score < next_score)) continue;
						//if (dp[next_stat].negative_score < next_score) continue;
						dp[next_stat].negative_score = next_score;
						dp[next_stat].pre_id = i;
						dp[next_stat].total_cost = next_cost;
						visted[next_stat] = -1;
					}
					//else
					//{
					//	dp[next_stat].pre_id = i;
					//	dp[next_stat].total_cost = next_cost;
					//	dp[next_stat].negative_score = next_score;
					//	visted[next_stat] = -1;
					//}

				}

			}
		}
		cout << "Done!" << endl;

	}
	return 0;
}

