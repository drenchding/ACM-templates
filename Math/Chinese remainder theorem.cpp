// 初始在模 MOD 意义下为 x，新加一个 ax = b (mod m)，更新 x, MOD
// 初始时条件可以设 x = 0, MOD = 1，之后不断添加条件
bool chineseRemainder(ll &x, ll &MOD, int a, int b, int m) {
	ll p, q;
	int g = exgcd(a * MOD, m, p, q), t = m / g;
	ll c = b - a * x;
	if(c % g) return false;
	p = ((p + m) * (c / g % t + t)) % t;
	x += p * MOD; MOD *= t;
	return true;
}
