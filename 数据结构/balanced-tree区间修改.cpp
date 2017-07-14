//bzoj4923
//平衡树打标记
//第一行两个数n,m 分别表示序列长度和操作数
//接下来一行n个数表示初始值
//接下来m行, 每行一个操作:
//1 k 输出kth
//2 k 将所有大于k的数减k
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
const int ratio = 4;
int n, m, cnt, a[MAXN];
struct Node {
	int size, val, tag;
	Node *ls, *rs;
	Node() {}
	Node(int s, int v, Node *l, Node *r): size(s), val(v), ls(l), rs(r) {}
}pool[MAXN], *st[MAXN], *root, *null, *fa;
Node *newnode(int s, int v, Node *l, Node *r) {
	return &(*st[cnt++] = Node(s, v, l, r));
}
void pushup(Node *cur) {
	if(cur->ls->size) {
		cur->size = cur->ls->size + cur->rs->size;
		cur->val = cur->rs->val + cur->rs->tag;
	}
}
void pushdown(Node *cur) {
	if(cur->tag) {
		cur->val += cur->tag;
		cur->ls->tag += cur->tag;
		cur->rs->tag += cur->tag;
		cur->tag = 0;
	}
}
Node *merge(Node *l, Node *r) {
    Node *cur = newnode(0, 0, 0, 0);
    cur->ls = l; cur->rs = r;
    pushup(cur); return cur;
}
void maintain(Node *cur) {
    if(cur->ls->size > cur->rs->size * ratio) {
        pushdown(cur->ls); pushdown(cur->ls->rs); pushdown(cur->rs);
        cur->rs = merge(cur->ls->rs, cur->rs);
        st[--cnt] = cur->ls;
        cur->ls = cur->ls->ls;
    } else if(cur->rs->size > cur->ls->size * ratio) {
    	pushdown(cur->ls); pushdown(cur->rs); pushdown(cur->rs->ls);
        cur->ls = merge(cur->ls, cur->rs->ls);
        st[--cnt] = cur->rs;
        cur->rs = cur->rs->rs;
    }
}
void insert(Node *cur, int x) {
	pushdown(cur);
	if(cur->size == 1) {
		cur->ls = newnode(1, min(cur->val, x), null, null);
		cur->rs = newnode(1, max(cur->val, x), null, null);
	} else {
		if(x > cur->ls->val + cur->ls->tag) {
			insert(cur->rs, x);
		} else {
			insert(cur->ls, x);
		}
	}
	pushup(cur); maintain(cur);
}
void erase(Node *cur, int x) {
	pushdown(cur);
	if(cur->size == 1) {
		st[--cnt] = fa->ls;
		st[--cnt] = fa->rs;
		if(cur == fa->ls) {
			*fa = *fa->rs;
		} else {
			*fa = *fa->ls;
		}
	} else {
		fa = cur;
		if(x > cur->ls->val + cur->ls->tag) {
			erase(cur->rs, x);
		} else {
			erase(cur->ls, x);
		}
	}
	pushup(cur); maintain(cur);
}
int find(Node *cur, int x) {
	pushdown(cur);
	if(cur->size == 1) {
		return cur->val;
	}
	if(x > cur->ls->size) {
		return find(cur->rs, x - cur->ls->size);
	} else {
		return find(cur->ls, x);
	}
}
int rnk(Node *cur, int x) {
	pushdown(cur);
	if(cur->size == 1) {
		return 1;
	}
	if(x > cur->ls->val + cur->ls->tag) {
		return rnk(cur->rs, x) + cur->ls->size;
	} else {
		return rnk(cur->ls, x);
	}
}
void add(Node *cur, int x, int y) { // if a[i] > x then a[i] += y
	pushdown(cur);
	if(cur->size == 1) {
		if(cur->val > x) {
			cur->val += y;
		}
	} else {
		if(x > cur->ls->val + cur->ls->tag) {
			add(cur->rs, x, y);
		} else {
			cur->rs->tag += y;
			add(cur->ls, x, y);
		}
	}
	pushup(cur);
}
int main() {
	for(int i = 0; i < MAXN; i++) {
		st[i] = &pool[i];
	}
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	random_shuffle(a + 1, a + n + 1);
	null = newnode(0, 0, 0, 0);
	root = newnode(1, a[1], null, null);
	for(int i = 2; i <= n; i++) {
		insert(root, a[i]);
	}
	while(m--) {
		int opt, k; scanf("%d %d", &opt, &k);
		if(opt == 1) {
			printf("%d\n", find(root, k));
		} else {
			int cur = find(root, rnk(root, k + 1));
			while(cur > k && cur <= 2 * k) {
				erase(root, cur);
				insert(root, cur - k);
				cur = find(root, rnk(root, k + 1));
			}
			add(root, 2 * k, -k);
		}
	}
	return 0;
}