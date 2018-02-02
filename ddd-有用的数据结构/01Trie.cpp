namespace Trie {
  const int LEN = 31;
  struct Node *null;
  struct Node {
    int val;
    Node *ch[2];
    void init() {
      val = 0;
      ch[0] = ch[1] = null;
    }
  }pool[MAXN * LEN], *root;
  int d[LEN], res, segNode;
  Node *newNode() {
    pool[segNode].init();
    return &pool[segNode++];
  }
  void clear() { 
    segNode = 0;  
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
    if(!cur->ch[0]) cur = newNode();
    cur->val += v;
    if(deep == LEN) return;
    add(cur->ch[d[deep]], deep + 1, v);
  }
  void maxXor(Node *cur, int deep) {
    if(deep == LEN) return;
    int bit = d[deep];
    if(cur->ch[bit ^ 1]->val) {
      res += (1 << (LEN - deep - 1));
      maxXor(cur->ch[bit ^ 1], deep + 1);
    } else if(cur->ch[bit]->val) {
      maxXor(cur->ch[bit], deep + 1);
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
    if(root) maxXor(root, 0);
    return res;
  }
}