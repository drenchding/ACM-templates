//bzoj1251
//序列区间加, 区间翻转, 询问最值
//第一行两个整数n, m, 表示序列长度和操作次数
//接下来m行, 每行一个操作:
//1 l r v [l,r]加上v
//2 l r 翻转[l,r]
//3 l r 询问[l,r]最大值
//初始时序列都为0
#include <cstdio>
#include <iostream>
const int MAXN = 200005;
using namespace std;
int n, m, cnt, opt, l, r;
struct Node {
    int size, value, add, rev;
    Node *ls, *rs;
    Node(){ ls = rs = NULL; }
}pool[MAXN], *st[MAXN], *root, *null;
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
inline Node *newnode() {
    return &*st[cnt++];
}
inline void pushdown(Node *cur) {
    if(cur->add) {
        if(!cur->ls->size) {
            cur->value += cur->add;
        } else {
            cur->ls->add += cur->add;
            cur->rs->add += cur->add;
        }
        cur->add = 0;
    }
    if(cur->rev) {
        if(cur->ls->size) {
            cur->ls->rev ^= 1;
            cur->rs->rev ^= 1;
            swap(cur->ls, cur->rs);
        }
        cur->rev = 0;
    }
}
inline void update(Node *cur) {
    if(cur->ls->size) {
        cur->size = cur->ls->size + cur->rs->size;
        cur->value = max(cur->ls->value + cur->ls->add, cur->rs->value + cur->rs->add);
    }
}
inline Node *merge(Node *a, Node *b) {
    pushdown(a); pushdown(b);
    update(a); update(b);
    Node *cur = newnode();
    cur->size = a->size + b->size;
    cur->value = max(a->value, b->value);
    cur->ls = a; cur->rs = b;
    return cur;
}
void split(Node *cur, int x) {
    pushdown(cur);
    if(x > cur->ls->size) {
        split(cur->rs, x - cur->ls->size);
        cur->ls = merge(cur->ls, cur->rs->ls);
        st[--cnt] = cur->rs; 
        cur->rs = cur->rs->rs;
    } else if(x < cur->ls->size) {
        split(cur->ls, x);
        cur->rs = merge(cur->ls->rs, cur->rs);
        st[--cnt] = cur->ls;
        cur->ls = cur->ls->ls;
    }
    update(cur);
}
inline Node *getinterval(int l, int r) {
    split(root, r);
    split(root->ls, l - 1);
    return root->ls->rs;
}
Node *build(int l, int r) {
    if(l == r) {
        Node *cur = newnode();
        cur->size = 1;
        cur->value = 0;
        cur->ls = null;
        cur->rs = null;
        return cur;
    }
    int mid = (l + r) / 2;
    Node *ls = build(l, mid);
    Node *rs = build(mid + 1, r);
    return merge(ls, rs);
} 
int main() {
    n = read(); m = read();
    for(int i = 0; i < MAXN; i++) {
        st[i] = &pool[i];
    }
    null = newnode(); null->size = 0;
    root = build(0, n + 1);
    while(m--) {
        opt = read(); l = read() + 1; r = read() + 1;
        Node *cur = getinterval(l, r);
        if(opt == 1) {
            cur->add += read();
        } else if(opt == 2) {
            cur->rev ^= 1;
        } else {
            pushdown(cur);
            update(cur);
            printf("%d\n", cur->value);
        }
    }
    return 0;
}