#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 55;
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
ll a[MAXN], b[50];
int main() {
	int n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		for(int j = 49; j >= 0; j--) {
			if(a[i] & (1LL << j)) {
				if(b[j]) {
					a[i] ^= b[j];
				} else {
					b[j] = a[i];
					break;
				}
			}
		}
	}
	ll ans = 0;
	for(int i = 49; i >= 0; i--) {
		ans = max(ans, ans ^ b[i]);
	}
	printf("%lld\n", ans);
	return 0;
}