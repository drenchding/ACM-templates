#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 100005;

#define ls ch[0]
#define rs ch[1]
#define newNode(v, s, l, r) segNode < MAXN ? &(pool[segNode++] = Node(v, s, l, r)) : new Node(v, s, l, r)

int segNode;

struct Node *pool, *null, *root;
struct Node {
  int val, size;
  Node *ch[2];
  Node(): val(0), size(0) {
    ch[0] = ch[1] = null;
  }
  Node(int v, int s, Node *l, Node *r): val(v), size(s) {
    ch[0] = l, ch[1] = r;
  }
  void pushup() {
    if(ls->size && rs->size) {
      size = ls->size + rs->size;
      val = max(ls->val, rs->val);
    }
  }
  void maintain() { 
    if(ls->size && rs->size) {
      for(int d = 0; d < 2; d++) {
        if(ch[d]->size > ch[d^1]->size * 4) {
          ch[d^1] = newNode(0, 1, ch[d]->ch[d^1], ch[d^1]);
          ch[d] = ch[d]->ch[d], ch[d^1]->pushup();
          if(d) swap(ch[d^1]->ch[d], ch[d^1]->ch[d^1]);
        }
      }
    }
  }
}mem[MAXN];

void insert(Node *cur, int v) {
  if(cur->size == 1) {
    cur->ls = newNode(min(cur->val, v), 1, null, null);
    cur->rs = newNode(max(cur->val, v), 1, null, null);
  } else {
    insert(cur->ch[v > cur->ls->val], v);
  }
  cur->pushup(), cur->maintain();
}

void erase(Node *cur, int v, Node *fa = null) {
  if(cur->size == 1) {
    *fa = fa->ls == cur ? *fa->rs : *fa->ls;
  } else {
    erase(cur->ch[v > cur->ls->val], v, cur);
    cur->pushup(), cur->maintain();
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
  segNode = 0, pool = mem;
  null = newNode(0, 0, NULL, NULL);
  root = newNode(2147483647, 1, null, null);
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