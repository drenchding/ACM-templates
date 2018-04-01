#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 500010;
const int INF = 2147483647;

struct Node {
  int value;
  int fix, cnt;
  int left, right;
  Node() { };
  Node(int value) {
    this->cnt = 1;
    this->left = 0;
    this->right = 0;
    this->fix = rand() * RAND_MAX + rand();
    this->value = value;
  }
};

Node a[MAXN*50];
int cnt = 0;

int newNode(int value) {
  a[++cnt] = Node(value);
  return cnt;
}

int copyNode(int x) {
  a[++cnt] = a[x];
  return cnt;
}

void update(int x) {
  a[x].cnt = a[a[x].left].cnt + a[a[x].right].cnt + 1;
}

int merge(int x, int y) {
  if(!x || !y) return x + y;
  if(a[x].fix < a[y].fix) {
    x = copyNode(x);
    a[x].right = merge(a[x].right, y);
    update(x); return x;
  } else {
    y = copyNode(y);
    a[y].left = merge(x, a[y].left);
    update(y); return y;
  }
}

pair<int, int> splitByRank(int x, int k) {
  if(x == 0) return pair<int, int>(0, 0);
  if(k <= a[a[x].left].cnt) {   
    x = copyNode(x);
    pair<int, int> pi = splitByRank(a[x].left, k);
    a[x].left = pi.second; update(x);
    return pair<int, int>(pi.first, x);
  } else {
    x = copyNode(x);
    pair<int, int> pi = splitByRank(a[x].right, k - 1 - a[a[x].left].cnt);
    a[x].right = pi.first; update(x);
    return pair<int, int>(x, pi.second); 
  }
}

pair<int, int> splitByValue(int x, int value) {
  if(x == 0) return pair<int, int>(0, 0);
  if(value <= a[x].value) { //相同值划分至右树 
    pair<int, int> pi = splitByValue(a[x].left, value);
    x = copyNode(x);
    a[x].left = pi.second; update(x);
    return pair<int, int>(pi.first, x);
  } else {
    pair<int, int> pi = splitByValue(a[x].right, value);
    x = copyNode(x); 
    a[x].right = pi.first; update(x);
    return pair<int, int>(x, pi.second); 
  }
}

void insert(int &root, int value) {
  pair<int, int> pi = splitByValue(root, value);
  int nn = newNode(value);
  root = merge(merge(pi.first, nn), pi.second);
}

int getRank(int root, int value) { // 答案要 +1
  if(root == 0) return 0;
  if(a[root].value < value)
    return a[a[root].left].cnt + 1 + getRank(a[root].right, value);
  return getRank(a[root].left, value);
}

int findByRank(int root, int k) {
  if(k < 1) return -INF;
  if(k > a[root].cnt) return INF;
  if(a[a[root].left].cnt + 1 == k) return a[root].value;
  if(k <= a[a[root].left].cnt) 
    return findByRank(a[root].left, k);
  return findByRank(a[root].right, k - 1 - a[a[root].left].cnt);
}

bool exists(int root, int value) {
  if(root == 0) return false;
  if(value == a[root].value) return true;
  if(value < a[root].value) 
    return exists(a[root].left, value);
  return exists(a[root].right, value);
}

void remove(int &root, int value) {
  if(!exists(root, value)) return;
  pair<int, int> pi = splitByValue(root, value);
  pair<int, int> pi2 = splitByRank(pi.second, 1);
  root = merge(pi.first, pi2.second);
}

int findPre(int root, int value) {
  if(root == 0) return -INF;
  if(a[root].value < value) 
    return max(a[root].value, findPre(a[root].right, value));
  return findPre(a[root].left, value);
}

int findSuc(int root, int value) {
  if(root == 0) return INF;
  if(a[root].value > value) 
    return min(a[root].value, findSuc(a[root].left, value));
  return findSuc(a[root].right, value);
}

int root[MAXN];

void init() {
  srand((unsigned long long)new char);
  cnt = 0; a[0] = Node(); a[0].cnt = 0;
  memset(root, 0, sizeof(root));
}

int main() {
  init();
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    int times, opt, x; 
    scanf("%d %d %d", &times, &opt, &x);
    root[i] = root[times];
    if(opt == 1) {
      insert(root[i], x);
    } else if(opt == 2) {
      remove(root[i], x);
    } else if(opt == 3) {
      printf("%d\n", getRank(root[i], x) + 1);
    } else if(opt == 4) {
      printf("%d\n", findByRank(root[i], x));
    } else if(opt == 5) {
      printf("%d\n", findPre(root[i], x));
    } else if(opt == 6) {
      printf("%d\n", findSuc(root[i], x));
    }
  }
  return 0;
}