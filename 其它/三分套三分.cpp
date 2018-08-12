// 给出平面若干点，求出一个点，使得到所有点的欧几里得距离之和最短
ld calc(ld ansX, ld ansY) {
  ld res = 0;
  for(int i = 1; i <= n; i++) {
    res += hypot(ansX - x[i], ansY - y[i]);
  }
  return res;
}
pair<ld, ld> solveY(ld ansX) {
  ld l = -1e6, r = 1e6;
  for(int i = 1; i <= 80; i++) {
    ld a = l + (r - l) / 3;
    ld b = r - (r - l) / 3;
    ld va = calc(ansX, a);
    ld vb = calc(ansX, b);
    if(va < vb) {
      r = b;
    } else {
      l = a;
    }
  }
  return make_pair(calc(ansX, l), l);
}
pair<ld, ld> solveX() {
  ld l = -1e6, r = 1e6;
  for(int i = 1; i <= 80; i++) {
    ld a = l + (r - l) / 3;
    ld b = r - (r - l) / 3;
    ld va = solveY(a).first;
    ld vb = solveY(b).first;
    if(va < vb) {
      r = b;
    } else {
      l = a;
    }
  }
  return make_pair(l, solveY(l).second);
}