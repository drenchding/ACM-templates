// 求满足 A ^ x = B (mod C) 最小的 x, 不存在返回 -1，不要求 gcd(A, C) = 1
int exBSGS(int A, int B, int C) { 
  if(C == 1) if(!B) return A != 1; else return -1;
  if(B == 1) if(A) return 0; else return -1;
  if(A % C == 0) if(!B) return 1; else return -1;
  int r, D = 1, num = 0;
  while((r = gcd(A, C)) > 1) {
    if(B % r) return -1; num++;
    B /= r; C /= r; D = ((ll)D * A / r) % C;
  }
  for(int i = 0, now = 1; i < num; i++, now = ((ll)now * A) % C)
    if(now == B) return i;
  int m = ceil(sqrt(C)), Base = 1; 
  map<int, int> f;
  for(int i = 0; i <= m - 1; i++) {
    if(!f.count(Base)) f[Base] = i;
    else f[Base] = min(f[Base], i);
    Base = ((ll)Base * A) % C;
  }
  for(int i = 0; i <= m - 1; i++) {
    int x, y, r = exgcd(D, C, x, y);
    x = ((ll)x * B % C + C) % C;
    if(f.count(x)) return i * m + f[x] + num;
    D = ((ll)D * Base) % C;
  }
  return -1;
}