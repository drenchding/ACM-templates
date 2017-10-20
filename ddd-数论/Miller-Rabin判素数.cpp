namespace MR {
    typedef long long ll;
    ll prime[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23}, mx;
    ll mul(ll a, ll b, ll MOD) {
        ll tmp = a * b - (ll)((long double)a / MOD * b + 1e-8) * MOD;
        if(tmp < 0) tmp += MOD;
        return tmp;
    }
    ll ksm(ll x, ll y, ll MOD) {
        if(!y) return 1;
        if(y == 1) return x % MOD;
        ll w = ksm(x, y / 2, MOD);
        w = mul(w, w, MOD);
        if(y % 2 == 1) w = mul(w, x, MOD);
        return w;
    }
    ll gcd(ll x,ll y) {
        if(!y) return x;
        if(x % y == 0) return y;
        else return gcd(y, x % y);
    }
    bool MR(ll n) {
        if(n < 2) return 0;
        if(n == 2) return 1;
        if(n % 2 == 0) return 0;
        ll m = n - 1; int k = 0;
        while(m % 2 == 0) {
            k++; m /= 2;
        }
        for(int i = 0; i < 9; i++) {
            ll a = prime[i], w = ksm(a, m, n);
            if(w == 1 || w == n - 1 || a == n) continue;
            for(int j = 1; j <= k; j++) {
                ll u = mul(w, w, n);
                if(w != 1 && w != n - 1 && u == 1) return 0;
                w = u;
            }
            if(w != 1) return 0;
        }
        return 1;
    }
}