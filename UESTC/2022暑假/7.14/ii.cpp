#include<bits/stdc++.h>
#define ll long long 
#define mp make_pair
#define pb push_back

using namespace std;

const int inf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3fll;
inline long long read(){
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if (ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

const int N=1000000;
vector<int>a[N+5];
map<int,ll>q,ans;
int b[N+5];

void doit(){
    q.clear(); ans.clear();
    int n=read();
    for(int i=1;i<=n;i++) b[i]=read();
    sort(b+1,b+n+1);
    ll nowans=0;
    for(int i=n;i>=1;i--){
        q[b[i]]++;
        if (ans[b[i]]) {nowans+=ans[b[i]]; continue;}
        ll now=0;
        for(int j=0;j<a[b[i]].size();j++) now+=q[a[b[i]][j]];
        ans[b[i]]=now;
        nowans+=now;
    }
    printf("%lld\n",nowans);
    return ;
}

int  main(){
    for(int d=1;d<=N;d++)
        for(int i=d;i+d<=N;i+=d){
            if (__gcd(i,i+d)==(i^(i+d))) a[i].pb(i+d);
    }
    int T=read();
    while(T--){
    doit();
    }
    return 0;
}
