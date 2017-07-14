//loj 6190
//区间绝对值最小查询
//第一行一个n, 表示序列长度
//接下来一行n个整数, 表示序列
//接下来一个m, 表示询问数
//接下来m行, 每行两个数l, r, 查询min{abs(a_s-a_t)},s!=t,l<=s<=t<=r
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 300005;
const int INF = 2147483647;
void chkmin(int &x, int y) {
	x = y < x ? y : x;
}
struct W {
	int l, r, id;
	bool operator<(const W &a) const {
		return r < a.r;
	}
}Q[MAXN];
int n, m, a[MAXN], ans[MAXN];
int A[MAXN*18], *allc = A;
int *P[MAXN<<2], Tree[MAXN<<2], Mi;
void build(int L, int R, int p) {
	Tree[p] = INF, P[p] = allc;
	int t = R - L + 1;
	for(int i = L; i <= R; i++) {
		P[p][i - L] = a[i];
	}
	sort(P[p], P[p] + t);
	allc += t;
	if(L == R) {
		return;
	}
	int mid = (L + R) / 2;
	build(L, mid, p<<1);
	build(mid + 1, R, p<<1|1);
}
void update(int L, int R, int p, int x, int v) {
	if(L == R) {
		chkmin(Tree[p], abs(v - P[p][0]));
		chkmin(Mi, Tree[p]);
		return;
	}
	int sz = R - L + 1;
	if(R <= x) {
		int op = lower_bound(P[p], P[p] + sz, v) - P[p];
		if((op == 0 || (v - P[p][op - 1] >= Mi)) && (op == sz||(P[p][op] - v >= Mi))) {
			chkmin(Mi, Tree[p]);
			return;
		}
	}
	int mid = (L + R) / 2;
	if(mid < x) {
		update(mid + 1, R, p<<1|1, x, v);
	}
	update(L, mid, p<<1, x, v);
	Tree[p] = min(Tree[p<<1], Tree[p<<1|1]);
}
int query(int L, int R, int p, int l, int r) {
	if(L == l && R == r) {
		return Tree[p];
	}
	int mid = (L + R) / 2;
	if(mid >= r) {
		return query(L, mid, p<<1, l, r);
	} else if(mid < l) {
		return query(mid + 1, R, p<<1|1, l, r);
	} else {
		return min(query(L, mid, p<<1, l, mid), query(mid + 1, R, p<<1|1, mid + 1, r));
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	build(1, n, 1);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d %d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q + 1, Q + m + 1);
	for(int i = 1, r = 1; i <= m; i++) {
		while(r < Q[i].r) {
			Mi = INF; r++;
			update(1, n, 1, r - 1, a[r]);
		}
		if(Q[i].l == Q[i].r) {
			ans[Q[i].id] = INF;
		} else {
			ans[Q[i].id] = query(1, n, 1, Q[i].l, Q[i].r - 1);
		}
	}
	for(int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}