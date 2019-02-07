struct Bitset {
  typedef unsigned long long ull;
  static const int MAXL = MAXN / 64 + 1;
  ull bit[MAXL];
  void clear() {
    for(int i = 0; i < MAXL; i++) bit[i] = 0;
  }
  Bitset() { 
    clear(); 
  }
  void setBit(int x, int v) {
    if(v) bit[x >> 6] |= 1ULL << (x & 63);
    else bit[x >> 6] &= (~(1ULL << (x & 63)));
  }
  int getBit(int x) {
    return (bit[x >> 6] >> (x & 63)) & 1ULL;
  }
  void operator<<=(int x) {
    int a = x >> 6, b = x & 63;
    if(a >= MAXL) {
      this->clear();
    } else {
      if(b) {
        for(int i = MAXL - 1; i >= a + 1; i--) {
          bit[i] = (bit[i - a] << b) | (bit[i - a - 1] >> (64 - b));
        }
        bit[a] = bit[0] << b;
        for(int i = a - 1; i >= 0; i--) bit[i] = 0;
      } else {
        for(int i = MAXL - 1; i >= a; i--) bit[i] = bit[i - a];
        for(int i = a - 1; i >= 0; i--) bit[i] = 0;
      }
    }
  }
  void operator>>=(int x) {
    int a = x >> 6, b = x & 63;
    if(a >= MAXL) {
      this->clear();
    } else {
      if(b) {
        for(int i = 0; i <= MAXL - a - 2; i++) {
          bit[i] = (bit[i + a] >> b) | (bit[i + a + 1] << (64 - b));
        }
        bit[MAXL - a - 1] = bit[MAXL - 1] >> b;
        for(int i = MAXL - a; i < MAXL; i++) bit[i] = 0;
      } else {
        for(int i = 0; i <= MAXL - a - 1; i++) bit[i] = bit[i + a];
        for(int i = MAXL - a; i < MAXL; i++) bit[i] = 0;
      }
    } 
  }
  void operator|=(const Bitset & rhs) {
    for(int i = 0; i < MAXL; i++) bit[i] |= rhs.bit[i];
  }
  void operator&=(const Bitset & rhs) {
    for(int i = 0; i < MAXL; i++) bit[i] &= rhs.bit[i];
  }
  void operator^=(const Bitset & rhs) {
    for(int i = 0; i < MAXL; i++) bit[i] ^= rhs.bit[i];
  }
  Bitset operator<<(int x) {
    Bitset t = *this;
    t <<= x; return t;
  }
  Bitset operator>>(int x) {
    Bitset t = *this;
    t >>= x; return t;
  }
  Bitset operator|(const Bitset & rhs) {
    Bitset t = *this;
    t |= rhs; return t;
  }
  Bitset operator&(const Bitset & rhs) {
    Bitset t = *this;
    t &= rhs; return t;
  }
  Bitset operator^(const Bitset & rhs) {
    Bitset t = *this;
    t ^= rhs; return t;
  }
};
