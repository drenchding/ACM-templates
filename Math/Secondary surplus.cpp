void mul(int &a1, int &a2, int b1, int b2, int p, int w) {
  int t = ((ll)a1 * b2 + (ll)a2 * b1) % p;
  a1 = ((ll)a1 * b1 + (ll)a2 * b2 % p * w) % p;
  a2 = t;
}
int sqrt(int p, int a) { // x^2 = a (mod p)
  if(a == 0) return 0;
  if(p == 2) return 1;
  if(power(a, (p - 1) / 2, p) != 1) return -1;
  int y, w;
  do y = rand() % p, w = ((ll)y * y - a + p) % p;
  while(power(w, (p - 1) / 2, p) == 1);
  int r1 = 1, r2 = 0, s1 = y, s2 = 1;
  for(int i = (p + 1) / 2; i; i >>= 1) {
    if(i & 1) mul(r1, r2, s1, s2, p, w);
    mul(s1, s2, s1, s2, p, w);
  }
  return r1;
}
// ax^2 + bx + c = 0 (mod p)
bool equation(int a, int b, int c, int p, int &x1, int &x2) {
  int t = (((ll)b * b - 4LL * a * c) % p + p) % p;
  ll res = sqrt(p, t);
  if(res == -1) return false;
  int inv = power(2 * a % p, p - 2, p);
  x1 = (-b + res + p) * inv % p;
  x2 = (-b - res + p * 2) * inv % p;
  return true;
}
