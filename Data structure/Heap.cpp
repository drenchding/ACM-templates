template<typename T>
struct Heap {
  T g[MAXN];
  int size;
  Heap(): size(0) { }
  void push(T res) {
    int now = ++size, nxt = size >> 1;
    while(nxt) {
      if(res < g[nxt]) {
        g[now] = g[nxt], now = nxt, nxt >>= 1;
      } else break;
    }
    g[now] = res; 
  }
  T top() {
    return g[1];
  }
  void pop() {
    int now = 1, nxt = 2;
    T res = g[size--];
    while(nxt <= size) {
      if(nxt < size && g[nxt | 1] < g[nxt]) nxt |= 1;
      if(g[nxt] < res) {
        g[now] = g[nxt], now = nxt, nxt <<= 1;
      } else break;
    }
    g[now] = res;
  }
};