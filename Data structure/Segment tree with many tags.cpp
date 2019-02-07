/*
1 l r c 区间 [l, r] 乘 c
2 l r c 区间 [l, r] 加 c
3 l r 求区间 [l, r] 的和
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long ll;
int segNode, n, m;
ll arr[MAXN], P;
struct Tag {
  ll add, mul;
  Tag():add(0), mul(1) { }
  Tag(ll A, ll M): add(A), mul(M) {}
  void insert(const Tag & rhs) {
    mul = (mul * rhs.mul) % P;
    add = (add * rhs.mul + rhs.add) % P;
  }
  void clear() {
    add = 0, mul = 1;
  }
};
struct Node {
  ll val;
  Tag tag;
  int len;
  Node *ls, *rs;
  Node(): val(0), len(0), ls(NULL), rs(NULL) { }
  void pushup() {
    val = (ls->val + rs->val) % P;
  }
  void update(Tag t) {
    val = (val * t.mul + t.add * len) % P;
  }
  void pushdown() {
    ls->tag.insert(tag);
    rs->tag.insert(tag);
    ls->update(tag);
    rs->update(tag);
    tag.clear();
  }
}pool[MAXN<<1];
Node *newNode() {
  return &pool[segNode++];
}
Node *build(int l, int r) {
  Node *cur = newNode();
  cur->len = r - l + 1;
  if(l == r) {
    cur->val = arr[l] % P;
    return cur;
  }
  int mid = (l + r) / 2;
  cur->ls = build(l, mid);
  cur->rs = build(mid + 1, r);
  cur->pushup();
  return cur;
}
ll query(Node *cur, int l, int r, int a, int b) {
  if(a <= l && b >= r) return cur->val;
  cur->pushdown();
  int mid = (l + r) / 2; ll res = 0;
  if(a <= mid) res += query(cur->ls, l, mid, a, b);
  if(b > mid) res += query(cur->rs, mid + 1, r, a, b);
  return res % P;
}
void insert(Node *cur, int l, int r, int a, int b, Tag t) {
  if(a <= l && b >= r) {
    cur->tag.insert(t);
    cur->update(t);
    return;
  }
  cur->pushdown();
  int mid = (l + r) / 2;
  if(a <= mid) insert(cur->ls, l, mid, a, b, t);
  if(b > mid) insert(cur->rs, mid + 1, r, a, b, t);
  cur->pushup();
}
int main() {
  scanf("%d %lld", &n, &P);
  for(int i = 1; i <= n; i++) {
    scanf("%lld", &arr[i]);
  }
  Node *root = build(1, n);
  scanf("%d", &m);
  while(m--) {
    int opt; scanf("%d", &opt);
    int l, r; scanf("%d %d", &l, &r);
    if(opt == 1) {
      int c; scanf("%d", &c);
      insert(root, 1, n, l, r, Tag(0, c));
    } else if(opt == 2) {
      int c; scanf("%d", &c);
      insert(root, 1, n, l, r, Tag(c, 1));
    } else {
      printf("%lld\n", query(root, 1, n, l, r));
    }
  }
  return 0;
}
