// mu(x) = 1(x=1), (-1)^k(x=p1p2...pk(不重)), 0(otherwise)
void init(int MAXN) {
  mu[1] = 1;
  for(int i = 2; i < MAXN; i++) {  
    if(!vis[i]) prime[cnt++] = i, mu[i] = -1;  
    for(int j = 0; j < cnt && i * prime[j] < MAXN; j++) {  
      vis[i * prime[j]] = 1;
      if(i % prime[j]) mu[i * prime[j]] = -mu[i];
      else {  
        mu[i * prime[j]] = 0;  
        break;  
      }  
    }  
  }
}