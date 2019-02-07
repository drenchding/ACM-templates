const double eps = 1e-7;
double F(double t) {
  // 关于 t 的一元函数
}
double simpson(double a, double b) {
  double c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
double asr(double a, double b, double eps, double A) {
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if(fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) { // 积分下界、 上界、 eps
  return asr(a, b, eps, simpson(a, b));
}
