#include <cstdio>
#include <algorithm>
#include <vector> 
#include <cstring>
const int N=600005;
using namespace std;
int bin[32],n,m,a[N],b[N],root[N];
vector<int> v[N];
struct trie{
	  int cnt,ch[N*32][2],sum[N*32];
	  void Initialize(){
	      memset(ch,0,sizeof(ch));
	      memset(sum,0,sizeof(sum));
	      cnt=0;
	  }
	  int insert(int x,int val){
		    int tmp,y;tmp=y=++cnt;
		    for(int i=31;i>=0;i--){
		        int t=val&bin[i];t>>=i;
			      ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
			      x=ch[x][t];
			      y=ch[y][t]=++cnt;
			      sum[y]=sum[x]+1; 
		    }
		    return tmp;
	  }
	  int query(int l,int r,int val){
		    int tmp=0;
		    for(int i=31;i>=0;i--){
			      int t=val&bin[i];t>>=i;
			      if(sum[ch[r][t^1]]-sum[ch[l][t^1]])tmp+=bin[i],r=ch[r][t^1],l=ch[l][t^1];
			      else r=ch[r][t],l=ch[l][t];
		    }
		    return tmp;
	  }
}trie;
int st[N],en[N],dfn,q,u,x;
int dfs(int x){
    st[x]=++dfn;
    for(int i=0;i<v[x].size();i++)dfs(v[x][i]);
    en[x]=dfn;
}
int main(){
    bin[0]=1; for(int i=1;i<32;i++)bin[i]=bin[i-1]<<1;
    while(~scanf("%d%d",&n,&q)){
        trie.Initialize(); dfn=0;
        for(int i=1;i<=n;i++)v[i].clear();
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=2;i<=n;i++){
            scanf("%d",&x);
            v[x].push_back(i);
        }dfs(1);
        for(int i=1;i<=n;i++)b[st[i]]=a[i];
        for(int i=1;i<=n;i++)root[i]=trie.insert(root[i-1],b[i]);
        while(q--){
            scanf("%d%d",&u,&x);
            // printf("%d %d\n",st[u],en[u]);
            printf("%d\n",trie.query(root[st[u]-1],root[en[u]],x));
        }
    }return 0;
}