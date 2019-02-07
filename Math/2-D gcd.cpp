struct Vector {
  int x, y;
  Vector(): x(0), y(0) { }
  Vector(int X, int Y): x(X), y(Y) { }
  Vector operator*(const int & rhs) const {
    return Vector(x * rhs, y * rhs);
  }
  Vector operator+(const Vector & rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
  }
};
int Abs(int x) {
  return x > 0 ? x : -x;
}
void exgcd(int a, int b, int & x, int & y) {
  if(!b) {
    x = 1; y = 0;
  } else {
    exgcd(b, a % b, x, y);
    int t = x; x = y; y = t - a / b * y;
  }
}
int gcd(int a, int b) {
  int x, y;
  exgcd(a = Abs(a), b = Abs(b), x, y);
  return a * x + b * y;
}
int lcm(int a, int b) {
  return a / gcd(a, b) * b;
}
Vector A, B; // 初始都为 (0, 0)
void add(Vector C) {
  if(C.y < 0) C = C * (-1);
  if(!C.y) A.x = gcd(A.x, C.x);
  else {
    if(B.y) {
      int t = lcm(B.y, C.y);
      A.x = gcd(A.x, (t / B.y) * B.x - (t / C.y) * C.x);
    }
    int a, b;
    exgcd(C.y, B.y, a, b);
    B = C * a + B * b;
  }
  if(A.x) {
    if(B.x < 0) B.x += (-B.x / A.x + 1) * A.x;
    B.x -= B.x / A.x * A.x;
  }
}
