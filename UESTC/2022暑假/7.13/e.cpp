#include<bits/stdc++.h>
#define LOCAL
#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif
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

int n,k,dep,ans;
string s[10000];
int f[20];

int dfs(int d,ll x){
    if (d>dep) {return 14;}
    int numx=x;
    for(int i=0;i<k;i++) {
        f[i]=x%10;
        x=x/10;
    }
    x=numx;
    int num[14],sum=0;
    for(int i=0;i<=k;i++) num[i]=0;
    for(int i=1;i<=n;i++){
        int ff=0;
        for(int j=0;j<k;j++){
            if (f[j]==0) continue;
            if (s[i][j]-'0'!=f[j]-1) {ff=1;break;}
        }
        if (ff) continue;
        sum++;
        for(int j=0;j<k;j++){
            num[j]+=s[i][j]-'0';
        }
    }
    
    if (sum==1) return d;
    if (sum==2) return d+1;
    if (sum==3) return d+2;
    int now=0;
    ll nownum=1;
     int nowans=14;
    for(int i=0;i<k;i++){
        nownum=nownum*10;
        if (f[i]) continue;
        if (num[i]==0||num[i]==sum) continue;
        now=max(dfs(d+1,x+ nownum/10),dfs(d+1,x+ nownum/5));
        nowans=min(nowans,now);
        if (nowans==dep) {
            break;
        }
    }   
    return nowans;
}

void doit(){
    n=read(),k=read();
    ans=0;
    for(int i=1;i<=n;i++) cin>>s[i];
    if (n==1) {printf("0\n");return ;}
    for(dep=1;dep<=k+1;dep++){
        int now=dfs(0,0);
        if (now==dep) {
            cout<<now<<endl;
            break;
        }
    }
}


int  main(){
  file();
    //     freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int n=read();
    while(n--){
    doit();
    
    Timer();
    }
    return 0;
}
