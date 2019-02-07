namespace Trie {
  const int LEN = 20;
  struct Node *null;
  struct Node {
    int val;
    Node *ch[2];
    void init() {
      val = 0;
      ch[0] = ch[1] = null;
    }
    bool isNull() {
      return !ch[0];
    }
  }pool[MAXN * LEN], *root;
  int d[LEN], res, cnt;
  Node *newNode() {
    pool[cnt].init();
    return &pool[cnt++];
  }
  void clear() { 
    cnt = 0;  
    null = newNode();
    null->ch[0] = NULL;
    root = null;
  }
  void pre(int val) {
    for(int i = 1; i <= LEN; i++) {
      d[LEN - i] = (val & 1);
      val >>= 1;
    }
  }
  void add(Node *&cur, int deep, int v) {
    if(cur->isNull()) cur = newNode();
    cur->val += v;
    if(deep == LEN) return;
    add(cur->ch[d[deep]], deep + 1, v);
  }
  void maxXor(Node *cur, int deep) {
    if(deep == LEN) return;
    if(cur->isNull()) return;
    int bit = d[deep];
    int v = cur->ch[bit ^ 1]->val;
    if(v) {
      res += (1 << (LEN - deep - 1));
      maxXor(cur->ch[bit ^ 1], deep + 1);
    } else {
      maxXor(cur->ch[bit], deep + 1);
    }
  }
  void xorMex(Node *cur, int deep) {
    if(deep == LEN) return;
    if(cur->isNull()) return;
    int bit = d[deep];
    int v = cur->ch[bit]->val;
    int size = (1 << (LEN - deep - 1));
    if(v < size) {
      xorMex(cur->ch[bit], deep + 1);
    } else {
      res += (1 << (LEN - deep - 1));
      xorMex(cur->ch[bit ^ 1], deep + 1);
    }
  }
  void add(int val) {
    pre(val); add(root, 0, 1);
  }
  void del(int val) {
    pre(val); add(root, 0, -1);
  }
  int maxXor(int val) {
    pre(val); res = 0;
    maxXor(root, 0);
    return res;
  }
  int xorMex(int val) { // 要先去重
    pre(val); res = 0;
    xorMex(root, 0);
    return res;
  }
}
