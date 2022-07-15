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

const int N=1000005;

struct node{
    ll num,pos;
}a[N];

int cmp(node a1,node a2){
    return a1.num<a2.num;
}

ll sum[N];
ll p,q;
int n;

int check(ll k){
    for(int i=1;i+k-1<=n;i++){
       // cout<<(sum[i+k-1]-sum[i-1])*p<<" "<<a[i+k-1].num*k*q<<" ";
      //  cout<<a[i+k-1].num<<" "<<k<<endl;
        if (1ll*(sum[i+k-1]-sum[i-1])*p>=1ll*a[i+k-1].num*k*q) return 1;
    }
    return 0;
}
vector<int>ans;
int c[N];
void doit(){
    ans.clear();
    n=read();
    for(int i=1;i<=n;i++) a[i].num=read(),a[i].pos=i,c[i]=0;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].num;
    // for(int i=1;i<=n;i++) cout<<sum[i]<<" ";
    // cout<<endl;
    cin>>p>>q;
    int l=1,r=n;
    while(l<=r){
        int mid=(l+r)/2;
        if (check(mid)) l=mid+1;
        else r=mid-1;
    }
    int x=l-1;
    for(int i=1;i+x-1<=n;i++){
        if ((sum[i+x-1]-sum[i-1])*p>=a[i+x-1].num*x*q) {c[i]+=1; c[i+x]+=-1;}
    }
    int now=0;
    for(int i=1;i<=n;i++) {
        now+=c[i];
        if (now==0) ans.pb(a[i].pos);
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
    cout<<endl;
}

int  main(){
    //freopen("output.out","w",stdout);
    int n=read();
    while(n--){
    doit();
    }
    return 0;
}
