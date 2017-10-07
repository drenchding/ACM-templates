inline int read() {
  int x = 0, f = 1; char ch = getchar();
  while(!isdigit(ch)) { 
    if(ch == '-') f = -1;
    ch = getchar();
  }
  while(isdigit(ch)) { 
    x = x * 10 + ch - '0';
    ch = getchar(); 
  }
  return x * f;
}

inline int read() {
  int x = 0; 
  char ch = getchar();
  while(!isdigit(ch)) ch = getchar();
  while(isdigit(ch)) { 
    x = x * 10 + ch - '0';
    ch = getchar(); 
  }
  return x;
}

struct io {
  char ibuf[1 << 20];
  char* s;
  int a[24];
  char obuf[1 << 20];
  char* t;
  io():t(obuf) {
    fread(s = ibuf, 1, 1 << 20, stdin);
  }
  ~io() {
    fwrite(obuf, 1, t - obuf, stdout);
  }
  void read(char* u) {
    while(*s < 48) ++s;
    while(*s > 32) *u++ = *s++;
    *u = 0;
  }
  int read() {
    int u = 0, v = 1;
    while(*s < 48) v = *s++ ^ 45 ? 1 : -1;
    while(*s > 32) u = u * 10 + *s++ - 48;
    return u * v;
  }
  void put(int u) {
    *t++ = u;
  }
  template<class T> void print(T u) {
    static int *v = a;
    if(!u) {
      put(48);
    } else {
      if(u < 0){
        put(45);
        u *= -1;
      }
      for(; u; u /= 10) *v++ = u % 10;
      while(v != a) put(*--v + 48);
    }
  }
  template<class T> void println(T u) {
    print(u), put(10);
  }
}io;

struct FastIO {
  static const int S=1310720;
  int wpos, pos, len;
  char wbuf[S];
  FastIO(): wpos(0) { }
  inline int xchar() {
    static char buf[S];
    if(pos == len) pos = 0, len = fread(buf, 1, S, stdin);
    if(pos == len) return -1;
    return buf[pos++];
  }
  inline int xuint() {
    int c = xchar(), x = 0;
    while(c <= 32 && ~c) c = xchar();
    if(c == -1) return -1;
    for(; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
    return x;
  }
}io;