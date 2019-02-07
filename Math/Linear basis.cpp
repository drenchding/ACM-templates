struct Base {
  ll b[55], p[55], cnt, tot;
  void add(ll x) {
    tot++;
    for(int i = 50; i >= 0; i--) {
      if(x & (1LL << i)) {
        if(b[i]) x ^= b[i];
        else { 
          b[i] = x; break; 
        }
      }
    }
  }
  void init() { // 查询前要 init
    for(int i = 1; i <= 50; i++) 
      for(int j = 0; j < i; j++)
        if(b[i] & (1LL << j)) b[i] ^= b[j];
    for(int i = 0; i <= 50; i++) if(b[i])
      p[cnt++] = b[i];
  }
  // 获得排名为 k 的异或和
  ll getKthXor(ll k) {
    if(tot != cnt) k--;
    if(k >= (1LL << cnt)) return -1;
    ll ans = 0;
    for(int i = 0; i <= 50; i++) 
      if(k & (1LL << i)) ans ^= p[i];
    return ans;
  }
}B;
