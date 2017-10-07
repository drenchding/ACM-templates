//bzoj3224
//普通平衡树
//第一行一个数n, 表示有n个操作
//接下来n行, 每行一个操作:
//1 x 插入x
//2 x 删除x
//3 x 查询x的排名
//4 x 查询排名为x的数
//5 x 求x的前驱
//6 x 求x的后继
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN = 200005;
const int ratio = 5;
int n, cnt;
struct Node {
  int size, val;
  Node *ls, *rs;
  Node() { ls = rs = NULL; }
}pool[MAXN], *st[MAXN], *root, *fa;
Node *newnode(int v) {
  if(st[cnt] == NULL) {
    st[cnt] = &pool[cnt];
  }
  Node *cur = st[cnt++];
  cur->size = 1; cur->val = v;
  cur->ls = cur->rs = NULL;
  return cur;
}
void update(Node *cur) {
  if(cur->ls != NULL) {
    cur->size = cur->ls->size + cur->rs->size;
    cur->val = cur->rs->val;
  }
}
Node *merge(Node *l, Node *r) {
  Node *cur = newnode(0);
  cur->ls = l; cur->rs = r;
  update(cur); return cur;
}
void rotate(Node *cur, bool flag) {
  if(flag) {
    cur->ls = merge(cur->ls, cur->rs->ls);
    st[--cnt] = cur->rs;
    cur->rs = cur->rs->rs;
  } else {
    cur->rs = merge(cur->ls->rs, cur->rs);
    st[--cnt] = cur->ls;
    cur->ls = cur->ls->ls;
  }
}
void maintain(Node *cur) {
  if(cur->ls == NULL) {
    return;
  }
  if(cur->ls->size > cur->rs->size * ratio) {
    rotate(cur, 0);
  } else if(cur->rs->size > cur->ls->size * ratio) {
    rotate(cur, 1);
  }
  if(cur->ls->size > cur->rs->size * ratio) {
    rotate(cur->ls, 1); rotate(cur, 0);
  } else if(cur->rs->size > cur->ls->size * ratio) {
    rotate(cur->rs, 0); rotate(cur, 1);
  }
}
void insert(Node *cur, int x) {
  if(cur->size == 1) {
    cur->ls = newnode(min(x, cur->val));
    cur->rs = newnode(max(x, cur->val));
    update(cur); return;
  }
  if(x > cur->ls->val) {
    insert(cur->rs, x);
  } else {
    insert(cur->ls, x);
  }
  maintain(cur); update(cur);
}
void erase(Node *cur, int x) {
  if(cur->size == 1) {
    if(fa->ls == cur) {
      *fa = *fa->rs;
    } else {
      *fa = *fa->ls;
    }
  } else {
    fa = cur;
    if(x > cur->ls->val) {
      erase(cur->rs, x);
    } else {
      erase(cur->ls, x);
    }
  }
  maintain(cur); update(cur);
}
int rnk(Node *cur, int x) {
  if(cur->size == 1) {
    return 1;
  }
  if(x > cur->ls->val) {
    return rnk(cur->rs, x) + cur->ls->size;
  } else {
    return rnk(cur->ls, x);
  }
}
int find(Node *cur, int x) {
  if(cur->size == 1) {
    return cur->val;
  }
  if(x > cur->ls->size) {
    return find(cur->rs, x - cur->ls->size);
  } else {
    return find(cur->ls, x);
  }
}
void clear() {
  while(cnt) st[cnt--] = NULL;
}
int main() {
  root = newnode(2147483647);
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    int s, a; scanf("%d %d", &s, &a);
    if(s == 1) {
      insert(root, a);
    } else if(s == 2) {
      erase(root, a);
    } else if(s == 3) {
      printf("%d\n", rnk(root, a));
    } else if(s == 4) {
      printf("%d\n", find(root, a));
    } else if(s == 5) {
      printf("%d\n", find(root, rnk(root, a) - 1));
    } else {
      printf("%d\n", find(root, rnk(root, a + 1)));
    }
  }
  return 0;
}