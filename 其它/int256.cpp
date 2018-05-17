struct BigNumber {
	typedef unsigned __int128 lll;
  lll a, b;
  BigNumber(): a(0), b(0) { }
  BigNumber(int x): a(0), b(x) { }
  void mul2(int x) {
  	if(x == 0) return;
    a <<= x;
    lll tmpB = b >> (128 - x);
    a |= tmpB; b <<= x;
  }
  void add(const BigNumber & rhs) {
    lll maxV = ~(lll)0;
    a += rhs.a;
    if(maxV - b < rhs.b) a++;
    b += rhs.b;
  }
  BigNumber operator<<(int x) const {
  	BigNumber t = *this;
  	while(x > 100) mul2(100), x -= 100;
  	mul2(x);
  }
  bool operator<(const BigNumber & rhs) const {
    if(a == rhs.a) return b < rhs.b;
    return a < rhs.a;
  }
};