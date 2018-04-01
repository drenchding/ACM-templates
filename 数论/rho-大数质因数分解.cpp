namespace rho {
    typedef long long ll;
    ll prime[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    vector<pair<ll, int> > res;
    vector<ll> fac;
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
        if(y % 2) w = mul(w, x, MOD);
        return w;
    }
    ll gcd(ll x, ll y) {
        if(!y) return x;
        if(x % y == 0) return y;
        return gcd(y, x % y);
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
    int rho(ll n, ll c) {
        ll x1 = (ll)(rand() + 1) % n, x2 = x1, p = 1, k = 2;
        for(ll i = 1; p == 1; i++) {
            x1 = (mul(x1, x1, n) + c) % n;
            p = x1 > x2 ? x1 - x2 : x2 - x1;
            p = gcd(p, n);
            if(i == k) {
                x2 = x1; k += k;
            }
        }
        return p;
    }
    void solve(ll n) {
        if(n == 1) return;
        if(MR(n)) {
            for(int i = 0; i < res.size(); i++) {
                if(res[i].first == n) {
                    res[i].second++;
                    return;
                }
            }
            res.push_back(make_pair(n, 1));
            return;
        }
        ll t = n;
        while(t == n) {
            t = rho(n, rand() % (n - 1) + 1);
        }
        solve(t); solve(n / t);
    }
    void dfs(int cur, ll mul) {
        if(cur == res.size()) {
            fac.push_back(mul);
            return;
        }
        ll base = 1;
        for(int i = 0; i <= res[cur].second; i++) {
            dfs(cur + 1, mul * base);
            base *= res[cur].first;
        }
    }
    vector<ll> getFac(ll n) {
        res.clear(); solve(n);
        sort(res.begin(), res.end());
        fac.clear(); dfs(0, 1); 
        sort(fac.begin(), fac.end());
        return fac;
    }
}