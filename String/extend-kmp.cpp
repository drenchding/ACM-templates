vector<int> make_ext(string s) {
  int n = s.size();
  int i = 1;
  vector<int> ext(n);
  for (int j = 0, p = 1; i < n; i++) {
    if (ext[i - j] + i < p) {
      ext[i] = ext[i - j];
    } else {
      if (p < i) {
        p = i;
      }
      while (s[p] == s[p - i]) {
        p += 1;
      }
      ext[i] = p - i;
      j = i;
    }
  }
  return ext;
}

// search(s, s) 等价于 z_function(s)
vector<int> search(string s, string str) {
  int n = str.size();
  auto ext = make_ext(s);
  s += "#";
  vector<int> ret(n);
  // ret[i]: s 与 str[i...n-1] LCP
  for (int i = 0, j = 0, p = 0; i < n; i++) {
    if (ext[i - j] + i < p) {
      ret[i] = ext[i - j];
    } else {
      if (p < i) {
        p = i;
      }
      while (str[p] == s[p - i]) {
        p += 1;
      }
      ret[i] = p - i;
      j = i;
    }
  }
  return ret;
}
