mu[1] = 1;
for(int i = 2; i < 1000000; i++) {  
    if(!vis[i]) {  
        prime[cnt++] = i;  
        mu[i] = -1;  
    }  
    for(int j = 0; j < cnt && i * prime[j] < 1000000; j++) {  
        vis[i * prime[j]] = 1;
        if(i % prime[j]) {
            mu[i * prime[j]] = -mu[i];
        } else {  
            mu[i * prime[j]] = 0;  
            break;  
        }  
    }  
} 