int e_gcd(int a, int b, int & x, int & y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    int ans = e_gcd(b, a % b, x, y);
    int temp = x; x = y; y = temp - a / b * y;
    return ans;
}