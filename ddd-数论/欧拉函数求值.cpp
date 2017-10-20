// O(n) - O(1)
void init() {
    phi[1] = 1;
    for(int i = 2; i <= 10000000; i++) {
        if(phi[i]) continue;
        for(int j = i; j <= 10000000; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}

// O(sqrt(n))
int phi(int x) { 
    int i, res = x;  
    for(int i = 2; i * i <= x; i++)  
        if(x % i == 0) {
            res /= i; res *= i - 1;  
            while(x % i == 0)  
                x /= i;  
        }  
    if(x ^ 1) res /= x, res *= x - 1;  
    return res;  
}