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


vector<int>f[40005];
ll g[40005];

const ll MOD=998244353;
const ll mod=998244353;

long long solve(long long limit, vector<int> a) {
  if (limit == 0) return 1ll;

  vector<int> vis(100, 0);
  for (auto &it : a) vis[it] = 1;

  
  int high = -1;
  for (int i = 18; i >= 0; i--) {
    if (limit >> i & 1) {
      high = i;
      break;
    }
  }
  assert(high != -1);

  long long ans = 1;
  
  for (auto &it : a) {
    if (limit >> it & 1) ans = 0;
  }
  
  vector<int> sum(100, 0);

  if (vis[0] == 0) sum[0] = 1;
  for (int i = 1; i <= 18; i++) {
    sum[i] = sum[i - 1];
    if (vis[i] == 0) sum[i]++;
  }
  
  for (int i = high - 1; i >= 0; i--) {
    if (vis[i]) continue;    
    if (i == 0) {
      (ans += 1) %= MOD;
    } else {
      ans = (ans + (1ll << sum[i - 1]) % MOD) % MOD;
    }
  }

  for (int i = high - 1; i >= 0; i--) {
    if (limit >> i & 1) {
      if (i != 0)
        (ans += (1ll << sum[i - 1]) % MOD) %= MOD;
      else 
        (ans += 1) %= MOD;
      if (vis[i]) break;
    }
  }
  return (ans + 1)%mod;
}

void doit(){
    ll n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++) {
      g[i]=read(),f[i].clear();
    }
    for(int i=1;i<=k;i++){
        int b=read(),c=read();
        f[b].pb(c-1);
    }
    ll ans=1;
    for(int i=1;i<=n;i++){
      
        ans=ans*solve(m/g[i],f[i])%mod;
    }
    printf("%lld\n",ans);
}

int  main(){
    doit();
    return 0;
}
