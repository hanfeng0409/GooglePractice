// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//
//[1]	"https://www.geeksforgeeks.org/binary-indexed-tree-range-updates-point-queries/"
//[2]	"http://www.cnblogs.com/Basasuya/archive/2018/10/22/9833499.html"

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
#include <bitset>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <iomanip>
using namespace std;
typedef long long ll;
const int N = 4e5 + 5;
const int Q = 1e5 + 5;

void update(map<ll, ll> &arr, int ll, int rr, int val)
{
	arr[ll] += val;
	arr[rr + 1l] -= val;
}

int main(void)
{
	freopen("..\\data\\B-large-practice.in", "r", stdin);
	freopen("..\\data\\B-large-practice.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int _ = 1; _ <= T; ++_)
	{
		int n, q;
		ll  A[5], B[5], C[5], M[5];
		ll X[N], Y[N];
		ll Z[Q];
		ll num_of_arr = 0;					//numbers of Distinct scores 
		ll bit_arr[2 * N] = { 0 };			//for each score, the value in bit_arr means people_number/(score[i]-score[i-1])
		map<ll, ll> mymap;					//map to store score:offset, reference[1]  and [2]. Binary Indexed Tree : Range Updates and Point Queries.
		ll  l = 0;
		ll r = 0;

		scanf_s("%d %d", &n, &q);
		scanf_s("%lld %lld %lld %lld %lld %lld", &X[1], &X[2], &A[1], &B[1], &C[1], &M[1]);
		scanf_s("%lld %lld %lld %lld %lld %lld", &Y[1], &Y[2], &A[2], &B[2], &C[2], &M[2]);
		scanf_s("%lld %lld %lld %lld %lld %lld", &Z[1], &Z[2], &A[3], &B[3], &C[3], &M[3]);

		for (int i = 3; i <= n; ++i) {
			X[i] = (A[1] * X[i - 1] + B[1] * X[i - 2] + C[1]) % M[1];
			Y[i] = (A[2] * Y[i - 1] + B[2] * Y[i - 2] + C[2]) % M[2];
		}
		for (int i = 3; i <= q; ++i) {
			Z[i] = (A[3] * Z[i - 1] + B[3] * Z[i - 2] + C[3]) % M[3];
		}
		for (int i = 1; i <= n; ++i) {
			X[i] ++; Y[i] ++;
		}
		for (int i = 1; i <= q; ++i) Z[i] ++;

		ll var = 1;
		ll student_num = 0;
		for (int i = 1; i <= n; ++i)
		{
			l = min(X[i], Y[i]);
			r = max(X[i], Y[i]);
			if (mymap.find(l) == mymap.end())
			{
				mymap[l] = 0;
			}
			if (mymap.find(r + 1l) == mymap.end())
			{
				mymap[r + 1l] = 0;
			}

			update(mymap, l, r, var);
			student_num += r - l + var;
		}

		num_of_arr = mymap.size() - 1;
		ll offset_bit = 0;							//for each score, the value  means people_number/(score[i]-score[i-1])
		ll sum_1 = 0;								//means people numbers whos score less than score=key_arr[i]
		ll sum_arr[2 * N];							// all sum_l
		ll key_arr[2 * N];							//key of map and also score. for key is increase, the score is soreted from small to big also.
		map<ll, ll>::iterator iter;
		iter = mymap.begin();
		int i = 0;
		while (iter != mymap.end()) {
			offset_bit += iter->second;
			key_arr[i] = iter->first;
			bit_arr[i] = offset_bit;
			iter++;
			if (iter != mymap.end())
			{
				sum_1 += offset_bit * (iter->first - key_arr[i]);
				sum_arr[i++] = sum_1;
			}
		}

		ll ans = 0;
		for (int i = 1; i <= q; i++)
		{
			if (Z[i] > student_num)
			{
				continue;
			}
			ll pos = lower_bound(sum_arr, sum_arr + num_of_arr, student_num - Z[i] + 1) - sum_arr - 1;				//binary search the pos
			ll now = key_arr[pos + 1];																				//get score
			ll lef = student_num - Z[i] + 1 - sum_arr[pos];															//modify now_score based on people of each score
			now = now + lef / bit_arr[pos + 1];
			if (lef && (lef%bit_arr[pos + 1] == 0)) now--;
			ans += 1ll * i * (now);
		}
		printf("Case #%d: %lld\n", _, ans);
	}
	return 0;
}
