// 你要维护一张无向简单图。你被要求加入删除一条边及查询两个点是否连通。
// 0：加入一条边。保证它不存在。
// 1：删除一条边。保证它存在。
// 2：查询两个点是否联通。

#include <bits/stdc++.h>

using namespace std;

const int N = 505005;

int n, q;

struct edge {
  int u, v, t;
}c[N];

struct info {
  int o, u, v;
}f[N];

struct vec {
  int u, v;
  vec(int u = 1e9, int v = 0): u(u), v(v){}
};

bool operator<(vec a, vec b){
  return a.u < b.u;
}

struct node;
typedef node* ptr;
struct node {
  ptr i, j, p;
  bool r;
  vec v, s;
  node();
  ptr up() {
    s = min(min(v, i->s), j->s);
    return this;
  }
  void down() {
    if(r) i->r ^= 1, j->r ^= 1, swap(i, j), r = 0;
  }
}e[N];

node::node() {
  i = j = p = e;
}

bool root(ptr o) {
  return o != o->p->i && o != o->p->j;
}

void turn(ptr o) {
  ptr s = o->p, t = s->p;
  if(!root(s)) (s == t->i ? t->i : t->j) = o;
  s->p = o, o->p = t;
  if(o == s->i) s->i = o->j, o->j->p = s, o->j = s->up();
  else s->j = o->i, o->i->p = s, o->i = s->up();
}

void push(ptr o) {
  if(!root(o)) push(o->p);
  o->down();
}

ptr splay(ptr o) {
  push(o);
  while(!root(o)) {
    if(!root(o->p)) turn(o == o->p->i ^ o->p == o->p->p->i ? o : o->p);
    turn(o);
  }
  return o->up();
}

ptr exp(ptr o) {
  ptr s = e;
  while(o != e) splay(o)->j = s, s = o->up(), o = o->p;
  return s;
}

void link(int i, int j) {
  exp(e + i)->r = 1, splay(e + i)->p = e + j;
}

void cut(int i, int j) {
  ptr s = e + i, t = e + j;
  exp(s)->r = 1, exp(t);
  if(s == t->i && s->j == e) t->i = s->p = e;
  if(t == s->j && t->i == e) s->j = t->p = e;
}

bool jud(int i, int j) {
  exp(e + i)->r = 1;
  ptr o = exp(e + j);
  while(o->i != e) o = o->i, o->down();
  return splay(o) == e + i;
}

void ins(int i) {
  if(c[i].u == c[i].v) return;
  int &v = c[i].t;
  if(!v) v = q + 1;
  e[n + i].v = vec(v, i);
  if(!jud(c[i].u, c[i].v)) {
    link(c[i].u, n + i);
    link(c[i].v, n + i);
  } else {
    int j = e[c[i].u].s.v;
    if(c[i].t > c[j].t) {
      cut(c[j].u, n + j);
      cut(c[j].v, n + j);
      link(c[i].u, n + i);
      link(c[i].v, n + i);
    }
  }
}

void del(int i) {
  cut(c[i].u, n + i);
  cut(c[i].v, n + i);
}

map<int, int> g[N];

int main() {
  int o, u, v, l1 = 0;
  scanf("%d %d", &n, &q);
  for(int i = 1; i <= q; i++) {
    scanf("%d %d %d", &o, &u, &v);
    if(u > v) swap(u,v);
    f[i] = {o, u, v};
    if(!o) c[++l1] = {u, v}, g[u][v] = l1;
    else if(o == 1) {
      int &t = c[g[u][v]].t;
      if(!t) t = i;
    }
  }
  l1 = 0;
  for(int i = 1; i <= q; i++) {
    if(f[i].o == 2) {
      puts(jud(f[i].u, f[i].v) ? "Y" : "N");
    } else if(f[i].o == 1) {
      del(g[f[i].u][f[i].v]);
    } else {
      ins(++l1);
      g[f[i].u][f[i].v] = l1;
    }
  }
  return 0;
}