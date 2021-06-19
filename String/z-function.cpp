vector<int> z_function(string s) {
  int n = s.size();
  int l = 0, r = 0;
  // z[i]: s[0...n-1] 与 s[i...n-1] 的 LCP
  vector<int> z(n);
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i > r) {
      l = r = i;
      while (r < n && s[r - l] == s[r]) {
        r += 1;
      }
      z[i] = r - l;
      r -= 1;
    } else {
      int k = i - l;
      if (z[k] < r - i + 1) {
        z[i] = z[k];
      } else {
        l = i;
        while (r < n && s[r - l] == s[r]) {
          r += 1;
        }
        z[i] = r - l;
        r -= 1;
      }
    }
  }
  return z;
}
