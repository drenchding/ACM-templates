const double eps = 1e-9;

int sgn(double x) {
  if(x < -eps) return -1;
  if(x > eps) return 1;
  return 0;
}

struct Point {
  double x, y;
  Point(double X = 0, double Y = 0): x(X), y(Y) { }
  double cross(const Point & rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  Point operator-(const Point & rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  bool operator<(const Point & rhs) const {
    if(sgn(x - rhs.x)) return x < rhs.x;
    if(sgn(y - rhs.y)) return y < rhs.y;
    return false;
  }
};

void convexHull(vector<Point> & p, vector<Point> & res) {
  res.clear();
  if(p.size() <= 3) {
    res = p;
  } else {
    sort(p.begin(), p.end());
    res.push_back(p[0]);
    res.push_back(p[1]);
    for(int i = 2; i < p.size(); i++) {
      while(res.size() >= 2 && sgn((res[res.size() - 1] - res[res.size() - 2]).cross(p[i] - res[res.size() - 2])) <= 0) {
        res.pop_back();
      }
      res.push_back(p[i]);
    }
    int down = res.size() - 1;
    res.push_back(p[p.size() - 2]);
    for(int i = p.size() - 3; i >= 0; i--) {
      while(res.size() - down >= 2 && sgn((res[res.size() - 1] - res[res.size() - 2]).cross(p[i] - res[res.size() - 2])) <= 0) {
        res.pop_back();
      }
      res.push_back(p[i]);
    }
  }
}