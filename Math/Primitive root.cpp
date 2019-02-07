int calRoot(int mod) {
	int factor[20], num = 0, m = mod - 1, s = m;
	for(int i = 2; i * i <= s; i++) {
		if(s % i == 0) {
			factor[num++] = i;
			while(s % i == 0) s /= i;
		}
	}
	if(s != 1) factor[num++] = s;
	for(int i = 2; ; i++) {
		int j = 0;
		for(; j < num && power(i, m / factor[j], mod) != 1; j++);
		if(j == num) return i;
	}
}
