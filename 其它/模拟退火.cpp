// 给出平面若干点，求出一个点，使得到所有点的欧几里得距离之和最短
double calc(double ansX, double ansY) {
  double tot = 0;
  for(int i = 1; i <= n; i++) {
    tot += sqrt((ansX - x[i]) * (ansX - x[i]) + (ansY - y[i]) * (ansY - y[i]));
  }
  return tot;
}
double getDoubleRand() {
  return 1.0 * rand() / RAND_MAX;
}
bool accept(double delta, double T) {
  return delta < 0;
}
pair<double, double> work(double ansX, double ansY) {
  double ansV = calc(ansX, ansY); // 初始坐标的费用
  double T = 1e6, ed = 1e-3, dec = 1 - 1e-3;
  // 初始温度，停止温度，降温幅度
  while(T > ed) {
    double nx = ansX + T * (getDoubleRand() * 2 - 1);
    double ny = ansY + T * (getDoubleRand() * 2 - 1);
    double nv = calc(nx, ny);
    if(accept(nv - ansV, T)) {
      ansX = nx, ansY = ny, ansV = nv;
    }
    T *= dec;
  }
  for(int i = 0; i < 10000000 / n; i++) {
    double nx = ansX + T * (getDoubleRand() * 2 - 1);
    double ny = ansY + T * (getDoubleRand() * 2 - 1);
    double nv = calc(nx, ny);
    if(nv < ansV) {
      ansX = nx, ansY = ny, ansV = nv;
    }
  }
  return make_pair(ansX, ansY);
}