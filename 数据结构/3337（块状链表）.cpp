#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<cmath>  
#include<queue>  
#define N 10000  
#define LL long long  
#define inf 10000000000LL  
using namespace std;  
int n,m,line[N],blocksize,st[N];  
struct node  
{  
    int d[1003],s[1003];  
    int rev,delta,same,size,next;  
    LL sum;  
}a[N];  
queue<int> p;  
void clear(int t)  
{  
    a[t].sum=a[t].same=a[t].size=a[t].rev=a[t].delta=0;  
}  
int newnode()  
{  
    int temp=p.front(); p.pop();  
    return temp;  
}  
int del(int t)  
{  
    p.push(t); clear(t);  
}  
void init()  
{  
    for (int i=1;i<N;i++) p.push(i);  
    a[0].next=-1; a[0].size=0;  
}  
void pushdown(int t)  
{  
    if (a[t].rev)  
     {  
        a[t].rev=0;  
        for (int i=1;i<=a[t].size;i++)  
         line[i]=a[t].d[i];  
        for (int i=a[t].size;i>=1;i--)  
         a[t].d[a[t].size-i+1]=line[i];  
     }  
    if (a[t].same)  
    {  
        for (int i=1;i<=a[t].size;i++)  
         a[t].d[i]=a[t].same;  
        a[t].sum=a[t].same*a[t].size;  
        a[t].same=0;  
    }  
    if (a[t].delta)  
    {  
        for (int i=1;i<=a[t].size;i++)  
         a[t].d[i]+=a[t].delta;  
        a[t].sum+=a[t].size*a[t].delta;  
        a[t].delta=0;  
    }  
}  
void update(int x)  
{  
    a[x].sum=0;  
    for (int i=1;i<=a[x].size;i++)  
     a[x].sum+=a[x].d[i],a[x].s[i]=a[x].d[i];  
    sort(a[x].s+1,a[x].s+a[x].size+1);  
}  
void merge(int x)  
{  
    int k=a[x].next;  
    pushdown(x); pushdown(k);  
    for (int i=1;i<=a[k].size;i++)  
     a[x].d[++a[x].size]=a[k].d[i];  
    a[x].next=a[k].next; del(k);  
    update(x);  
}  
void maintain(int now)  
{  
    for (;now!=-1;now=a[now].next)  
     if (a[now].next!=-1&&a[now].size+a[a[now].next].size<=blocksize)  
      merge(now);  
}  
void find(int &pos,int &now)  
{  
    for (now=0;a[now].next!=-1&&pos>a[now].size;now=a[now].next)  
     pos-=a[now].size;  
}  
void spilt(int now,int pos)  
{  
    pushdown(now);   
    int t=newnode();  
    for (int i=pos;i<=a[now].size;i++)  
     a[t].d[++a[t].size]=a[now].d[i];  
    a[t].next=a[now].next;   
    a[now].next=t; a[now].size=max(pos-1,0);  
    update(t); update(now);  
}  
void insert(int pos,int val)  
{  
    int now; pos++;  
    find(pos,now); spilt(now,pos);  
    a[now].d[++a[now].size]=val;  
    update(now);  
    maintain(now);  
}  
void erase(int pos)  
{  
    int now;  
    find(pos,now); pushdown(now);   
    for (int i=pos+1;i<=a[now].size;i++)  
     a[now].d[i-1]=a[now].d[i];  
    a[now].size--;  
    update(now);  
    maintain(now);  
}  
void solve(int l,int r,int &lp,int &rp)  
{  
    int pos=l;  
    find(pos,lp);   
    spilt(lp,pos);   
    pos=r+1;   
    find(pos,rp);   
    spilt(rp,pos);  
    pos=r;  
    find(pos,rp);  
}  
void do_reverse(int l,int r)  
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    int now=lp;  
    int top=0;  
    for (int i=a[lp].next;i!=a[rp].next;i=a[i].next)  
     st[++top]=i,a[i].rev^=1;  
    a[st[1]].next=a[rp].next;  
    for (int i=top;i>1;i--)  
     a[st[i]].next=st[i-1];  
    a[lp].next=rp;  
    maintain(lp);  
}  
void do_move(int l,int r,int k)  
{  
    int lp,mp,rp,np;  
    solve(l,r-k,lp,mp);  
    solve(r-k+1,r,mp,rp);  
    np=a[lp].next;  
    a[lp].next=a[mp].next;  
    a[mp].next=a[rp].next;  
    a[rp].next=np;  
    maintain(lp);  
}  
void add(int l,int r,int val)  
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    int now;  
    for (now=a[lp].next;now!=a[rp].next;now=a[now].next)  
     {  
        a[now].delta+=val;  
        a[now].sum+=a[now].size*val;  
     }  
    maintain(lp);  
}  
void same(int l,int r,int val)  
{  
    int lp,rp,now;  
    solve(l,r,lp,rp);  
    for (now=a[lp].next;now!=a[rp].next;now=a[now].next)  
    {  
        a[now].delta=0;  
        a[now].same=val;  
        a[now].sum=a[now].size*val;  
    }  
    maintain(lp);  
}  
LL qjsum(int l,int r)  
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    LL ans=0;  
    int now;  
    for (now=a[lp].next;now!=a[rp].next;now=a[now].next)  
     ans+=a[now].sum;  
    maintain(lp);  
    return ans;  
}  
int range(int l,int r)  
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    int maxn=-inf,minn=inf;  
    for (int now=a[lp].next;now!=a[rp].next;now=a[now].next)  
     if (a[now].size!=0)  
      if (a[now].same)  
       {  
        minn=min(minn,a[now].same+a[now].delta);  
        maxn=max(maxn,a[now].same+a[now].delta);  
       }  
      else  
       {  
        minn=min(minn,a[now].s[1]+a[now].delta);  
        maxn=max(maxn,a[now].s[a[now].size]+a[now].delta);  
       }  
    maintain(lp);  
    return maxn-minn;  
}  
int near(int l,int r,int val)  
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    int ans=inf;  
    for (int now=a[lp].next;now!=a[rp].next;now=a[now].next)  
     if (a[now].same)  
      ans=min(ans,abs(val-a[now].same-a[now].delta));  
     else  
     {  
        int id=lower_bound(a[now].s+1,a[now].s+a[now].size+1,val-a[now].delta)-a[now].s;  
        if (id!=a[now].size+1)  
         ans=min(ans,a[now].s[id]+a[now].delta-val);  
        if (id!=1)  
         id--,ans=min(ans,val-a[now].s[id]-a[now].delta);  
     }  
    maintain(lp);  
    return ans;  
}  
int ask_mink(int l,int r,int k)   
{  
    int lp,rp;  
    solve(l,r,lp,rp);  
    int ans=0,ll=0,rr=inf;  
    while (ll<rr)  
    {  
        int mid=(ll+rr)/2+1;  
        ans=1;  
        for (int now=a[lp].next;now!=a[rp].next;now=a[now].next)  
         if (a[now].same)  
         {  
          if (a[now].same+a[now].delta<mid)  
           ans+=a[now].size;  
         }  
         else  
         {  
            int id=upper_bound(a[now].s+1,a[now].s+a[now].size+1,mid-a[now].delta-1)-a[now].s;  
            ans+=max(0,id-1);   
         }  
        if (k>=ans)  ll=mid;  
        else rr=mid-1;  
    }  
    maintain(lp);  
    return ll;  
}  
int ask_smaller(int l,int r,int val)  
{  
    int lp,rp;   
    solve(l,r,lp,rp);  
    int ans=0;  
    for (int now=a[lp].next;now!=a[rp].next;now=a[now].next)  
     if (a[now].same)  
      {  
        if (a[now].same+a[now].delta<val)  
         ans+=a[now].size;  
      }  
      else  
      {  
        int id=upper_bound(a[now].s+1,a[now].s+a[now].size+1,val-a[now].delta-1)-a[now].s;  
        ans+=id-1;  
      }  
    maintain(lp);   
    return ans;  
}  
int main()  
{  
    scanf("%d",&n);   
    blocksize=sqrt(n);  
    init();  
    for (int i=1;i<=n;i++)  
     {  
        int x; scanf("%d",&x);  
        insert(i-1,x);  
     }  
    scanf("%d",&m);  
    for (int i=1;i<=m;i++)  
    {  
        int op; int x,y,z;  
        scanf("%d",&op);  
        switch(op)  
        {  
            case 1:scanf("%d%d",&x,&y); insert(x,y); break;  
            case 2:scanf("%d",&x); erase(x); break;  
            case 3:scanf("%d%d",&x,&y); do_reverse(x,y); break;  
            case 4:scanf("%d%d%d",&x,&y,&z); do_move(x,y,z); break;  
            case 5:scanf("%d%d%d",&x,&y,&z); add(x,y,z); break;  
            case 6:scanf("%d%d%d",&x,&y,&z); same(x,y,z); break;  
            case 7:scanf("%d%d",&x,&y); printf("%lld\n",qjsum(x,y)); break;  
            case 8:scanf("%d%d",&x,&y); printf("%d\n",range(x,y)); break;  
            case 9:scanf("%d%d%d",&x,&y,&z); printf("%d\n",near(x,y,z)); break;  
            case 10:scanf("%d%d%d",&x,&y,&z); printf("%d\n",ask_mink(x,y,z)); break;  
            case 11:scanf("%d%d%d",&x,&y,&z); printf("%d\n",ask_smaller(x,y,z)); break;  
        }  
        /*for (int j=0;;j=a[j].next) 
         { 
            for (int k=1;k<=a[j].size;k++) 
             cout<<a[j].d[k]<<" "; 
            cout<<"!"<<a[j].rev<<" "; 
            if (a[j].next==-1) break; 
         } 
        cout<<endl;*/  
    }  
    return 0;  
}  