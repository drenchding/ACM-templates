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