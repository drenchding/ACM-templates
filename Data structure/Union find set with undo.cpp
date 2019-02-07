class UFS {
private:
  int *fa, *rnk;
  stack<pair<int*, int> > stk;
  stack<int> cnt;
public:
  UFS() { }
  void init(int n) {
    fa = new int[n + 1];
    rnk = new int[n + 1];
    for(int i = 1; i <= n; i++) {
      fa[i] = i, rnk[i] = 0;
    }
    while(!stk.empty()) stk.pop();
  }
  int find(int x) {
    while(x != fa[x]) x = fa[x];
    return x;
  }
  int _merge(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return 0;
    if(rnk[x] <= rnk[y]) {
      stk.push(make_pair(fa + x, fa[x]));
      fa[x] = y;
      if(rnk[x] == rnk[y]) {
        stk.push(make_pair(rnk + y, rnk[y]));
        ++rnk[y];
        return 2;
      }
      return 1;
    }
    stk.push(make_pair(fa + y, fa[y]));
    fa[y] = x;
    return 1;
  }
  void merge(int x, int y) {
    int c = _merge(x, y);
    if(c) cnt.push(c);
  }
  void undo() {
    for(int i = 1; i <= cnt.top(); i++) {
      *stk.top().first = stk.top().second;
      stk.pop();
    }
    cnt.pop();
  }
};
