// 第一行两个数n, m，分别表示序列长度和询问数
// 接下来一行n个数，表示序列
// 接下来m个询问，形如(l, r, k)，表示询问[l,r]排名第k的数
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
int n, m, cnt, a[MAXN], b[MAXN], c[MAXN];
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) { 
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)) { 
        x = x * 10 + ch - '0';
        ch = getchar(); 
    }
    return x * f;
}
struct Node {
	int val;
	Node *ls, *rs;
}pool[MAXN*10], *st[MAXN*10], *root[MAXN];
Node *newnode() {
	if(cnt > 2000000) {
		return new Node{0, 0, 0};
	}
	st[cnt] = &pool[cnt];
	return st[cnt++];
}
Node *build(int l, int r) {
	Node *cur = newnode();
	if(l == r) {
		*cur = Node{0, 0, 0};
		return cur;
	}
	int mid = (l + r) / 2;
	cur->ls = build(l, mid);
	cur->rs = build(mid + 1, r);
	cur->val = 0; return cur;
}
void add(Node *pre, Node *&cur, int l, int r, int pos, int val) {
	cur = newnode(); *cur = *pre; 
	cur->val += val;
	if(l == r) return;
	int mid = (l + r) / 2;
	if(pos <= mid) {
		add(pre->ls, cur->ls, l, mid, pos, val);
	} else{
		add(pre->rs, cur->rs, mid + 1, r, pos, val);
	}
}
int query(Node *pre, Node *cur, int l, int r, int k) {
	if(l == r) return l;
	int left = cur->ls->val - pre->ls->val;
	int mid = (l + r) / 2;
	if(left >= k) {
		return query(pre->ls, cur->ls, l, mid, k);
	} else {
		return query(pre->rs, cur->rs, mid + 1, r, k - left);
	}
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		b[i] = a[i] = read();
	}
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++) {
		int pos = lower_bound(b + 1, b + n + 1, a[i]) - b;
		c[pos] = a[i]; a[i] = pos;
	}
	root[0] = build(1, n);
	for(int i = 1; i <= n; i++) {
		add(root[i - 1], root[i], 1, n, a[i], 1);
	}
	while(m--) {
		int l = read(), r = read(), k = read();
		printf("%d\n", c[query(root[l - 1], root[r], 1, n, k)]);
	}
	return 0;
}