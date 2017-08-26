//bzoj3224
//普通平衡树
//第一行一个数n, 表示有n个操作
//接下来n行, 每行一个操作:
//1 x 插入x
//2 x 删除x
//3 x 查询x的排名
//4 x 查询排名为x的数
//5 x 求x的前驱
//6 x 求x的后继
#include <cstdio>

const int MAXN = 100001;

struct Node {
    int data, s, c;
    bool color;
    Node *fa, *ch[2];
    void set(const int & _v, const bool & _color, const int & i, Node * p) {
        data = _v, color = _color, s = c = i;
        fa = ch[0] = ch[1] = p;
    }
    void push_up() {
        s = ch[0]->s + ch[1]->s + c;
    }
    void push_down() {
        for(Node *x = this; x->s; x = x->fa) x->s--;
    }
    int cmp(const int & v) const {
        return data == v ? -1 : v > data;
    }
};
struct RedBlackTree {
    int top;
    Node *root, *null;
    Node stack[MAXN], *tail, *store[MAXN];
    void init() {
        tail = &stack[0];
        null = tail++;
        null->set(0, 0, 0, NULL);
        root = null;
        top = 0;
    }
    Node *newNode(const int & v) {
        Node *p = null;
        if(!top) p = tail++;
        else p = store[--top];
        p->set(v, 1, 1, null);
        return p;
    }
    void rotate(Node* &x, const bool & d ) {
        Node *y = x->ch[!d];
        x->ch[!d] = y->ch[d];
        if(y->ch[d]->s) y->ch[d]->fa = x;
        y->fa = x->fa;
        if(!x->fa->s) root = y;
        else x->fa->ch[x->fa->ch[0] != x] = y;
        y->ch[d] = x;
        x->fa = y;
        y->s = x->s;
        x->push_up();
    }
    void insert(const int & v) {
        Node *x = root, *y = null;
        while(x->s) {
            x->s++, y = x;    
            int d = x->cmp(v);
            if(-1 == d) {
                x->c++;
                return;
            }
            x = x->ch[d];
        }
        x = newNode(v);
        if(y->s) y->ch[v > y->data] = x;
        else root = x;
        x->fa = y;
        insert_fix(x);
    }
    void insert_fix(Node* &x) {
        while(x->fa->color) {
            Node *par = x->fa, *Gp = par->fa;
            bool d = par == Gp->ch[0];
            Node *uncle = Gp->ch[d];
            if(uncle->color) {
                par->color = uncle->color = 0;
                Gp->color = 1;
                x = Gp;
            } else if(x == par->ch[d]) {
                rotate(x = par, !d);
            } else {
                Gp->color = 1;
                par->color = 0;
                rotate(Gp, d);
            }
        }
        root->color = 0;
    }
    Node *find(Node *x, int data) {
        while(x->s && x->data != data) x = x->ch[x->data < data];
        return x;
    }
    void del_fix(Node * &x) {
        while(x != root && !x->color) {
            bool d = x == x->fa->ch[0];
            Node *par = x->fa, *sibling = par->ch[d];
            if(sibling->color) {
                sibling->color = 0;
                par->color = 1;
                rotate(x->fa, !d);
                sibling = par->ch[d];
            } else if(!sibling->ch[0]->color && !sibling->ch[1]->color) {
                sibling->color = 1, x = par;
            } else {
                if(!sibling->ch[d]->color) {
                    sibling->ch[!d]->color = 0;
                    sibling->color = 1;
                    rotate(sibling, d);
                    sibling = par->ch[d];
                }
                sibling->color = par->color;
                sibling->ch[d]->color = par->color = 0;
                rotate(par, !d);
                break;
            }
        }
        x->color = 0;
    }
    void del(const int & data) {
        Node *z = find(root, data);
        if(!z->s) return;
        if(z->c > 1) {        
            z->c--;
            z->push_down();
            return;
        }
        Node *y = z, *x = null;
        if(z->ch[0]->s && z->ch[1]->s) {
            y = z->ch[1];
            while(y->ch[0]->s) y = y->ch[0];
        }
        x = y->ch[!y->ch[0]->s];
        x->fa = y->fa;
        if(!y->fa->s) root = x;
        else y->fa->ch[y->fa->ch[1] == y] = x;
        if(z != y) z->data = y->data, z->c = y->c;
        y->fa->push_down();
        for(Node *k = y->fa; y->c > 1 && k->s && k != z; k = k->fa) k->s -= y->c - 1;
        if(!y->color) del_fix(x);
        store[top++] = y;
    }
    int kth(int k) {
        int t;
        Node *x = root;
        for(; x->s;) {
            t = x->ch[0]->s;
            if(k <= t) x = x->ch[0];
            else if(t + 1 <= k && k <= t + x->c) break;
            else k -= t + x->c, x = x->ch[1];
        }
        return x->data;
    }
    int rank(const int & v) {
        int t, cur = 0;
        Node *x = root;
        for(; x->s;) {
            t = x->ch[0]->s;
            if(v == x->data) break;
            else if(v < x->data) x = x->ch[0];
            else cur += t + x->c, x = x->ch[1];
        }
        return cur + t + 1;
    }
    int succ(const int & v) {
        int ret = 0;
        Node *x = root;
        while(x->s) {
            if(x->data > v) ret = x->data, x = x->ch[0];
            else x = x->ch[1];
        }
        return ret;
    }
    int pred(const int & v) {
        int ret = 0;
        Node *x = root;
        while(x->s) {
            if(x->data < v) ret = x->data, x = x->ch[1];
            else x = x->ch[0];
        }
        return ret;
    }
}rbt;
int main() {
    rbt.init();
    int n, op, v;
    scanf("%d", &n);
    while(n--) {
        scanf("%d %d", &op, &v);
        if(op == 1) rbt.insert(v);
        else if(op == 2) rbt.del(v);
        else if(op == 3) printf("%d\n", rbt.rank(v));
        else if(op == 4) printf("%d\n", rbt.kth(v));
        else if(op == 5) printf("%d\n", rbt.pred(v));
        else printf("%d\n", rbt.succ(v));
    }
    return 0;
}