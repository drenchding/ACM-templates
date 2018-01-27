template <typename T>
struct MonotoneQueue {
  std::deque<T> q, m;
  void push(const T &x) {
    q.push_back(x);
    while (!m.empty() && m.back() < x) m.pop_back();
    m.push_back(x);
  }
  void pop() {
    T x = q.front();
    q.pop_front();
    if (x == m.front()) m.pop_front();
  }
  size_t size() {
    return q.size();
  }
  T top() {
    return m.front();
  }
};