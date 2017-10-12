#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 200005;

#define ls ch[0]
#define rs ch[1]
#define newNode(s, v, l, r) segNode < MAXN ? &(pool[segNode++] = Node(s, v, l, r)) : new Node(s, v, l, r)

int segNode;

struct Node *pool, *root, *null;
struct Node {
  int size, val;
  Node *ch[2];
  Node() { }
  Node(int s, int v, Node *l, Node *r): size(s), val(v) {
    ch[0] = l; ch[1] = r;
  }
  bool isBad() {
    if(ls->size && rs->size) {
      return 4 * ls->size > 3 * size + 20 || 4 * rs->size > 3 * size + 20;
    }
    return false;
  }
  void pushup() {
    if(ls->size && rs->size) {
      size = ls->size + rs->size;
      val = max(ls->val, rs->val);
    }
  }
}mem[MAXN];

int scape[MAXN], scaNode;

void travel(Node *cur) {
  if(cur->size == 1) {
    scape[++scaNode] = cur->val;
  } else {
    for(int d = 0; d < 2; d++) {
      travel(cur->ch[d]);
    }
  }
}

Node *rebuild(int l, int r) {
  Node *cur = newNode(1, scape[l], null, null);
  if(l < r) {
    int mid = (l + r) / 2;
    cur->ls = rebuild(l, mid);
    cur->rs = rebuild(mid + 1, r);
    cur->pushup();
  }
  return cur;
}

void maintain(Node *&cur) {
  scaNode = 0; travel(cur);
  cur = rebuild(1, scaNode);
}

void insert(Node *cur, int v) {
  if(cur->size == 1) {
    cur->ls = newNode(1, min(v, cur->val), null, null);
    cur->rs = newNode(1, max(v, cur->val), null, null);
  } else {
    insert(cur->ch[v > cur->ls->val], v);
  }
  cur->pushup(); 
  if(!cur->isBad() && cur->size > 1) {
    for(int d = 0; d < 2; d++) {
      if(cur->ch[d]->isBad()) maintain(cur->ch[d]);
    }
  }
}

void erase(Node *cur, int v, Node *fa = null) {
  if(cur->size == 1) {
    *fa = fa->ls == cur ? *fa->rs : *fa->ls;
  } else {
    erase(cur->ch[v > cur->ls->val], v, cur);
    cur->pushup();
    if(!cur->isBad() && cur->size > 1) {
      for(int d = 0; d < 2; d++) {
        if(cur->ch[d]->isBad()) maintain(cur->ch[d]);
      }
    }
  }
}

int kth(Node *cur, int k) {
  if(cur->size == k) return cur->val;
  else {
    int d = k > cur->ls->size;
    return kth(cur->ch[d], d ? k - cur->ls->size : k);
  }
}

int rnk(Node *cur, int v) {
  if(cur->size == 1) return 1;
  else {
    int d = v > cur->ls->val;
    return rnk(cur->ch[d], v) + (d ? cur->ls->size : 0);
  }
}

void init() {
  segNode = 0; pool = mem;
  null = newNode(0, 0, NULL, NULL);
  root = newNode(1, 2147483647, null, null);
}

int main() {
  init();
  int n; scanf("%d", &n);
  while(n--) {
    int s, a; scanf("%d %d", &s, &a);
    if(s == 1) insert(root, a);
    if(s == 2) erase(root, a);
    if(s == 3) printf("%d\n", rnk(root, a));
    if(s == 4) printf("%d\n", kth(root, a));
    if(s == 5) printf("%d\n", kth(root, rnk(root, a) - 1));
    if(s == 6) printf("%d\n", kth(root, rnk(root, a + 1)));
  }
  return 0;
}