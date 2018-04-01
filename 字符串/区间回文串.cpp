// 第一行一个字符串 和 q
// 接下来 q 行，每行 [l, r]，表示询问 [l, r] 内的回文串数

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
 
#define LL long long
#define maxn 200010
 
using namespace std;
 
int n,Q;
char st[maxn],s[maxn];
int p[maxn],Left[maxn],Right[maxn];
LL sm[maxn];
 
void manacher(){
    int id=1,mx=1;
    for(int i=1;i<=n;i++){
        p[i]=min(mx-i,p[2*id-i]);
        while(s[i+p[i]]==s[i-p[i]])p[i]++;
        if(i+p[i]>mx)mx=i+p[i],id=i;
    }
    for(int i=1;i<=n;i++)p[i]--;
}
 
LL Sm[maxn*40],Cnt[maxn*40];
int ls[maxn*40],rs[maxn*40],sz;
int rtL[maxn],rtR[maxn];
 
void update(int l,int r,int x,int &y,int k,int V){
    int M=l+r>>1;
    Sm[y=++sz]=Sm[x]+V;Cnt[y]=Cnt[x]+1;ls[y]=ls[x];rs[y]=rs[x];
    if(l==r)return;
    if(k<=M)update(l,M,ls[x],ls[y],k,V);else update(M+1,r,rs[x],rs[y],k,V);
}
 
void Init(){
    scanf("%s%d",st+1,&Q);
    n=strlen(st+1);
    for(int i=1;i<=n;i++)s[i*2]=st[i],s[i*2-1]='#';
    s[n*2+1]='#',s[n*2+2]='&',s[0]='@';n<<=1;
    manacher();
    for(int i=1;i<=n;i++)Left[i]=(i-p[i]+1)/2,Right[i]=(i+p[i]-1)/2;
    for(int i=1;i<=n;i++)sm[i]=sm[i-1]+(p[i]+1)/2;
    for(int i=1;i<=n;i++){
        rtL[i]=rtL[i-1];
        if(p[i])update(1,n,rtL[i],rtL[i],Left[i],Left[i]);
    }
    for(int i=n;i;i--){
        rtR[i]=rtR[i+1];
        if(p[i])update(1,n,rtR[i],rtR[i],Right[i],Right[i]);
    }
}
 
LL _cnt,_sm;
void query(int x,int y,int L,int R,int l,int r){int M=l+r>>1;
    if(L>R)return;
    if(L<=l&&R>=r){
        _cnt+=Cnt[y]-Cnt[x];_sm+=Sm[y]-Sm[x];
        return;
    }
    if(L<=M)query(ls[x],ls[y],L,R,l,M);if(R>M)query(rs[x],rs[y],L,R,M+1,r);
}
 
void Work(){
    LL ans=0;
    for(int i=1;i<=Q;i++){int l,r,l2,r2,M;
        scanf("%d%d",&l,&r);l2=l<<1,r2=r<<1,M=l2+r2>>1;ans=sm[r2]-sm[l2-1];
        _cnt=_sm=0;query(rtL[l2-1],rtL[M-1],1,l-1,1,n);
        ans-=1LL*l*_cnt-_sm;
        _cnt=_sm=0;query(rtR[r2+1],rtR[M+1],r+1,n,1,n);
        ans-=_sm-1LL*r*_cnt;
        if(Left[M]<l)ans-=l-Left[M];
        printf("%lld\n",ans);
    }
}
 
int main(){
    Init();
    Work();
    return 0;
}