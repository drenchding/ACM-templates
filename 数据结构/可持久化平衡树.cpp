// 普通平衡树的可持久化版
// 第i次操作后生成第i个版本
// 每次操作对之前的某个版本进行
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 500050;
const int maxlongint = 2147483647;
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
Node a[MAXN * 50];
int cnt = 0;
int new_node(int value) {
    cnt++;
    a[cnt] = Node(value);
    return cnt;
}
int copy_node(int x) {
    cnt++;
    a[cnt] = a[x];
    return cnt;
}
void update(int x) {
    a[x].cnt = a[a[x].left].cnt + a[a[x].right].cnt + 1;
}
void bl(int x) {
    if (x == 0) return;    
    bl(a[x].left);
    cout << a[x].value << ",";
    bl(a[x].right);
}
int merge(int x, int y) {
    if ((x == 0) || (y == 0)) return x + y;
    if (a[x].fix < a[y].fix) {
        x = copy_node(x);
        a[x].right = merge(a[x].right, y);
        update(x); return x;
    } else {
        y = copy_node(y);
        a[y].left = merge(x, a[y].left);
        update(y); return y;
    }
}
pair<int, int> split_by_rank(int x, int k) {
    if (x == 0) return pair<int, int>(0, 0);
    if (k <= a[a[x].left].cnt) {   
        x = copy_node(x);
        pair<int, int> pi = split_by_rank(a[x].left, k);
        a[x].left = pi.second; update(x);
        return pair<int, int>(pi.first, x);
    } else {
        x = copy_node(x);
        pair<int, int> pi = split_by_rank(a[x].right, k - 1 - a[a[x].left].cnt);
        a[x].right = pi.first; update(x);
        return pair<int, int>(x, pi.second); 
    }
}
pair<int, int> split_by_value(int x, int value) {
    if (x == 0) return pair<int, int>(0, 0);
    if (value <= a[x].value) { //相同值划分至右树 
        pair<int, int> pi = split_by_value(a[x].left, value);
        x = copy_node(x);
        a[x].left = pi.second; update(x);
        return pair<int, int>(pi.first, x);
    } else {
        pair<int, int> pi = split_by_value(a[x].right, value);
        x = copy_node(x); 
        a[x].right = pi.first; update(x);
        return pair<int, int>(x, pi.second); 
    }
}
void insert(int &root, int value) {
    pair<int, int> pi = split_by_value(root, value);
    int nn = new_node(value);
    root = merge(merge(pi.first, nn), pi.second);
}
int getRank(int root, int value) {
    if (root == 0) return 0;
    if (a[root].value < value)
        return a[a[root].left].cnt + 1 + getRank(a[root].right, value);
    else
        return getRank(a[root].left, value);
}
int findByRank(int root,int k) {
    if (k < 1) return -maxlongint;
    if (k > a[root].cnt) return maxlongint;
    if (a[a[root].left].cnt + 1 == k) return a[root].value;
    if (k <= a[a[root].left].cnt) 
        return findByRank(a[root].left, k);
    else
        return findByRank(a[root].right, k - 1 - a[a[root].left].cnt);
}
bool exists(int root, int value) {
    if (root == 0) return false;
    if (value == a[root].value) return true;
    if (value < a[root].value) 
        return exists(a[root].left, value);
    else
        return exists(a[root].right, value);
}
void remove(int &root, int value) {
    if (!exists(root, value)) return;
    pair<int, int> pi = split_by_value(root, value);
    pair<int, int> pi2 = split_by_rank(pi.second, 1);
    root = merge(pi.first, pi2.second);
}
int findPre(int root, int value) {
    if (root == 0) return -maxlongint;
    if (a[root].value < value) 
        return max(a[root].value, findPre(a[root].right, value));
    else
        return findPre(a[root].left, value);
}
int findSuc(int root, int value) {
    if (root == 0) return maxlongint;
    if (a[root].value > value) 
        return min(a[root].value, findSuc(a[root].left, value));
    else
        return findSuc(a[root].right, value);
}
int root[MAXN];
int main() {
    srand(time(NULL));
    cnt = 0; int n;
    a[0] = Node(); a[0].cnt = 0;
    scanf("%d", &n);
    root[0] = 0;
    for (int i = 1; i <= n; i++) {
        int times, opt, x; 
        scanf("%d %d %d", ×, &opt, &x);
        root[i] = root[times];
        if (opt == 1) {
            insert(root[i], x);
        } else if (opt == 2) {
            remove(root[i], x);
        } else if (opt == 3) {
            printf("%d\n", getRank(root[i], x) + 1);
        } else if (opt == 4) {
            printf("%d\n", findByRank(root[i], x));
        } else if (opt == 5) {
            printf("%d\n", findPre(root[i], x));
        } else if (opt == 6) {
            printf("%d\n", findSuc(root[i], x));
        }
    }
    return 0;
}