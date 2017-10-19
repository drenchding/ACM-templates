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

int n, m, segNode, opt, l, r;

struct Node {
  int size, val, add, rev;
  Node *ls, *rs;
  Node(): add(0), rev(0), ls(NULL), rs(NULL) { }
  Node(int s, int v, Node *l, Node *r): size(s), val(v), ls(l), rs(r), add(0), rev(0) { }
}pool[MAXN], *st[MAXN], *root, *null;

Node *newNode(int s, int v, Node *l, Node *r) {
  return &(*st[segNode++] = Node(s, v, l, r));
}

int read() {
  int x; scanf("%d", &x); return x;
}

void pushdown(Node *cur) {
  if(cur->add) {
    if(!cur->ls->size) {
      cur->val += cur->add;
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

void pushup(Node *cur) {
  if(cur->ls->size) {
    cur->size = cur->ls->size + cur->rs->size;
    cur->val = max(cur->ls->val + cur->ls->add, cur->rs->val + cur->rs->add);
  }
}

Node *merge(Node *a, Node *b) {
  pushdown(a); pushup(a); 
  pushdown(b); pushup(b);
  if(a->size > b->size * 4) {
    a->rs = merge(a->rs, b);
    pushup(a); return a;
  }
  if(b->size > a->size * 4) {
    b->ls = merge(a, b->ls);
    pushup(b); return b;
  }
  Node *cur = newNode(a->size + b->size, max(a->val, b->val), a, b);
  return cur;
}

void split(Node *cur, int x) {
  pushdown(cur);
  if(x > cur->ls->size) {
    split(cur->rs, x - cur->ls->size);
    cur->ls = merge(cur->ls, cur->rs->ls);
    st[--segNode] = cur->rs; 
    cur->rs = cur->rs->rs;
  } else if(x < cur->ls->size) {
    split(cur->ls, x);
    cur->rs = merge(cur->ls->rs, cur->rs);
    st[--segNode] = cur->ls;
    cur->ls = cur->ls->ls;
  }
  pushup(cur);
}

Node *getinterval(int l, int r) {
  split(root, r);
  split(root->ls, l - 1);
  return root->ls->rs;
}

Node *build(int l, int r) {
  if(l == r) {
    Node *cur = newNode(1, 0, null, null);
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
  null = newNode(0, 0, 0, 0);
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
      pushup(cur);
      printf("%d\n", cur->val);
    }
  }
  return 0;
}
