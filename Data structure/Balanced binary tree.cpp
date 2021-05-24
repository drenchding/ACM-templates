#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
struct BBT {
  typedef int DATA;
  typedef tree<pair<DATA, int>, null_type, less<pair<DATA, int> >, rb_tree_tag, 
          tree_order_statistics_node_update> BST;
  BST B;
  size_t size() {
    return B.size();
  }
  void insert(int x) {
    static int count = 0;
    B.insert(make_pair(x, ++count));
  }
  void erase(int x) {
    B.erase(B.lower_bound(make_pair(x, -1)));
  }
  int query(int x) { // 多少个 <=x 的数
    return B.order_of_key(make_pair(x + 1, -1));
  }
  int kth(int k) { // 查询排名为 k 的数 (1-based)
    return B.find_by_order(k - 1)->first;
  }
  void clear() {
    B.clear();
  }
};
