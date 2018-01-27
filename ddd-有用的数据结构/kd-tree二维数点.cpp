namespace KDT {
  const int MAXN = 500005;
  const double rate = 0.66;
  int tot, D, x0, x1, y0, y1;
  struct Node {
    int d[2], l[2], r[2], size, val, sum;
    Node *ch[2];
    Node(int x, int y, int v) {
      d[0] = x, d[1] = y, val = v;
      ch[0] = ch[1] = NULL;
      pushup();
    }
    void pushup() {
      l[0] = r[0] = d[0], l[1] = r[1] = d[1];
      sum = val;
      size = 1;
      for(int i = 0; i < 2; i++) if(ch[i]) {
        sum += ch[i]->sum;
        size += ch[i]->size;
        for(int j = 0; j < 2; j++) {
          l[j] = min(l[j], ch[i]->l[j]);
          r[j] = max(r[j], ch[i]->r[j]);
        }
      }
    }
  }*pool[MAXN<<2], *root;
  bool cmp(Node *x, Node *y) {
    return x->d[D] < y->d[D];
  }
  Node *build(int l, int r, int d) {
    if(l > r) return NULL;
    D = d; int m = (l + r) / 2;
    nth_element(pool + l, pool + m, pool + r + 1, cmp);
    Node *p = pool[m];
    p->ch[0] = build(l, m - 1, d ^ 1);
    p->ch[1] = build(m + 1, r, d ^ 1);
    p->pushup(); return p;
  }
  void dfs(Node *cur) {   
    if(!cur) return;
    dfs(cur->ch[0]);
    pool[++tot] = cur;
    dfs(cur->ch[1]);
  }
  void rebuild(Node *&cur, int d) {
    tot = 0; dfs(cur);
    cur = build(1, tot, d);
  }
  void insert(Node *&cur, Node *p, int d) {
    if(!cur) cur = p;
    else insert(cur->ch[p->d[d] >= cur->d[d]], p, d ^ 1);
    cur->pushup();
    int maxs = 0;
    for(int i = 0; i < 2; i++) {
      if(cur->ch[i]) maxs = max(maxs, cur->ch[i]->size);
    }
    if(maxs > cur->size * rate) rebuild(cur, d);
  }
  int query(Node *cur) {
    if(!cur || cur->l[0] > x1 || cur->r[0] < x0) return 0;
    if(cur->l[1] > y1 || cur->r[1] < y0) return 0;
    if(x0 <= cur->l[0] && cur->r[0] <= x1) {
      if(y0 <= cur->l[1] && cur->r[1] <= y1) return cur->sum;
    } 
    int res = query(cur->ch[0]) + query(cur->ch[1]);
    if(x0 <= cur->d[0] && cur->d[0] <= x1) {
      if(y0 <= cur->d[1] && cur->d[1] <= y1) res += cur->val;  
    }
    return res;
  }
  void clear() { root = NULL; }
  void add(int x, int y, int w) {
    Node *p = new Node(x, y, w);
    insert(root, p, 0);
  }
  int query(int a, int b, int c, int d) {
    x0 = a, y0 = b, x1 = c, y1 = d;
    return query(root);
  }
}