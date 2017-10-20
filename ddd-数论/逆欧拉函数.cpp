// 已知phi(N)，求N。
// 两个正整数，分别表示phi(N)和K。
// 按升序输出满足条件的最小的K个N。

#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define M 10000009
using namespace std;
LL N,ans[M],prime[M];
int k,cnt,cnt2;
bool np[M];
void prepare(){
  np[0]=1,np[1]=1;
  for(int i=2;i<M;i++){
    if(!np[i]) {
      prime[++cnt]=i;
    }
    for(int j=1;j<=cnt&&1ll*i*prime[j]<M;j++){
      np[i*prime[j]]=1;
      if(i%prime[j]==0) break;
    }
  }
}
LL q_mul(LL a,LL b,LL mod){
  LL s=0;
  while(b){
    if(b&1) s=(s+a)%mod;
    a=(a+a)%mod;
    b>>=1;
  }
  return s;
} 
LL q_pow(LL a,LL b,LL mod){
  LL s=1;
  while(b){
    if(b&1) s=q_mul(s,a,mod);
    a=q_mul(a,a,mod);
    b>>=1;
  }
  return s;
}

bool MR(LL n){
  if (n==2) return 1;
  if (n%2==0) return 0;
  int lg=0;LL w=n-1;
  while (w%2==0) lg++,w/=2;
  for (int i=1;i<=9;i++){
    if (n==prime[i]) return 1;
    LL x=q_pow(prime[i],w,n);
    if (x==1||x==n-1) continue;
    for (int j=1;j<=lg;j++){
      LL y=q_mul(x,x,n);
      if (x!=1&&x!=n-1&&y==1) return 0;
      x=y;
    }
    if (x!=1) return 0;
  }
  return 1;
}

bool pd_prime(LL x){
  if(x<M) return (!np[x]);
  else return MR(x);
}

void dfs(int dep,LL x,LL res){
  if(x+1>prime[cnt]&&pd_prime(x+1)) {ans[++cnt2]=res*(x+1);}
  LL tres=res,tx=x,s;
  for(int i=dep;i>=1;i--){
    if(x%(prime[i]-1)==0){
      s=1;
      tres=res;
      tx=x/(prime[i]-1);
      while(tx%s==0){
        tres*=prime[i];
        dfs(i-1,tx/s,tres);
        s*=prime[i];
      }
    }
  } 
  if(x==1){ans[++cnt2]=res;return;} 
}

int main(){
  prepare();
  scanf("%lld%d",&N,&k);
  dfs(cnt,N,1);
  sort(ans+1,ans+cnt2+1);
  printf("%lld",ans[1]);k--;
  vector<LL>res;
  for(int i=2;k&&i<=cnt2;i++){
    if(ans[i]!=ans[i-1]) res.push_back(ans[i]),k--;
  }
  for(int i=0;i<res.size();i++){
    printf(" %lld", res[i]);
  }
  puts("");
  return 0;
}