#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
struct Node {
  Node *ls, *rs, *fa;
  int val, tag, maxV;
  bool rev;
}pool[MAXN];
void init(int n) { // 1 ~ n 号点初始化为一个没有边的森林
  for(int i = 1; i <= n; i++) {
    Node & t = pool[i];
    t.ls = t.rs = t.fa = &pool[0];
    t.val = t.tag = t.maxV = t.xorSum = 0;
    t.rev = false;
  }
}
void pushUp(Node *cur) {
  cur->maxV = max(cur->val, max(cur->ls->maxV, cur->rs->maxV));
}
void update(Node *cur, int tag) {
  cur->tag += tag;
  cur->val += tag;
  cur->maxV += tag;
}
void pushDown(Node *cur) {
  if(cur->tag) {
    if(cur->ls != pool) update(cur->ls, cur->tag);
    if(cur->rs != pool) update(cur->rs, cur->tag);
    cur->tag = 0;
  }
  if(cur->rev) {
    cur->rev = false;
    cur->ls->rev ^= 1;
    cur->rs->rev ^= 1;
    swap(cur->ls, cur->rs);
  }
}
void rotate(Node *cur) {
  Node *p = cur->fa, *q = p->fa;
  if(p->ls == cur) {
    p->ls = cur->rs;
    cur->rs->fa = p;
    cur->rs = p;
  } else {
    p->rs = cur->ls;
    cur->ls->fa = p;
    cur->ls = p;
  }
  if(q->ls == p) q->ls = cur;
  else if(q->rs == p) q->rs = cur;
  p->fa = cur, cur->fa = q;
  pushUp(p);
}
bool check(Node *t, Node *f) {
  return f->ls == t || f->rs == t;
}
void pushSign(Node *cur) {
  Node *f = cur->fa;
  if(check(cur, f)) pushSign(f);
  pushDown(cur);
}
void splay(Node *cur) {
  pushSign(cur);
  for(Node *f; check(cur, f = cur->fa); rotate(cur)) {
    if(check(f, f->fa)) {
      rotate((f->ls == cur) == (f->fa->ls == f) ? f : cur);
    }
  }
  pushUp(cur);
}
Node *access(Node *cur) {
  Node *t;
  for(t = pool; cur != pool; cur = cur->fa) {
    splay(cur);
    cur->rs = t, t = cur;
    pushUp(t);
  }
  return t;
}
void setRoot(Node *cur) {
  access(cur)->rev ^= 1;
}
Node *findRoot(Node *cur) {
  cur = access(cur);
  pushDown(cur);
  while(cur->ls != pool) {
    cur = cur->ls;
    pushDown(cur);
  }
  splay(cur);
  return cur;
}
bool connected(Node *t1, Node *t2) {
  setRoot(t1);
  return findRoot(t2) == t1;
}
void link(Node *t1, Node *t2) {
  Node *t = access(t1);
  t->rev ^= 1, t->fa = t2;
}
void cut(Node *t1, Node *t2) {
  setRoot(t1); splay(t2);
  if(t2->ls) {
    t2->ls->fa = t2->fa;
    t2->ls = t2->fa = pool;
    pushUp(t2);
  } else {
    t2->fa = pool;
  }
}
void add(Node *t1, Node *t2, int tag) {
  setRoot(t1);
  update(access(t2), tag);
}
int queryMax(Node *t1, Node *t2) {
  setRoot(t1);
  return access(t2)->maxV;
}
