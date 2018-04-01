// 第一行表示数据组数
// 接下来每行一个 n
// 询问 sum_{i=1}^{n} phi(i) 和 sum_{i=1}^{n} mu(i)
// n 范围： int

#include <map>
#include <cstdio>
#include <utility>
#define N 3000010
using namespace std;
typedef long long ll;
map<ll, pair<ll, ll> > f;
map<ll, pair<ll, ll> >::iterator it;
ll phi[N], mu[N], prime[N], tot, sumphi[N], summu[N], m = 3000000;
bool np[N];
void query(ll n, ll &ans1, ll &ans2) {
  if(n <= m) {
    ans1 = sumphi[n], ans2 = summu[n];
    return;
  }
  it = f.find(n);
  if(it != f.end()) {
    ans1 = it->second.first;
    ans2 = it->second.second;
    return;
  }
  ans1 = n * (n + 1) / 2, ans2 = 1;
  ll i, last, tmp1, tmp2;
  for(i = 2 ; i <= n ; i = last + 1) {
    last = n / (n / i), query(n / i, tmp1, tmp2);
    ans1 -= (last - i + 1) * tmp1, ans2 -= (last - i + 1) * tmp2;
  }
  f[n] = make_pair(ans1, ans2);
}
int main() {
  int T;
  ll n, i, j, ans1, ans2;
  np[1] = 1, mu[1] = phi[1] = sumphi[1] = summu[1] = 1;
  for(i = 2 ; i <= m ; i ++ ) {
    if(!np[i]) prime[++tot] = i, phi[i] = i - 1, mu[i] = -1;
    for(j = 1 ; j <= tot && i * prime[j] <= m ; j ++ ) {
      np[i * prime[j]] = 1;
      if(i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        mu[i * prime[j]] = 0;
        break;
      } else {
        phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        mu[i * prime[j]] = -mu[i];
      }
    }
    sumphi[i] = sumphi[i - 1] + phi[i];
    summu[i] = summu[i - 1] + mu[i];
  }
  scanf("%d", &T);
  while(T--) {
    scanf("%lld", &n);
    query(n, ans1, ans2);
    printf("%lld %lld\n", ans1, ans2);
  }
  return 0;
}