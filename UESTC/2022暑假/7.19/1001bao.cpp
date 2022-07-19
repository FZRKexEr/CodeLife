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

int f[10000];

void doit(){
    string s;
    memset(f,0,sizeof (f));
    cin>>s;
    int l=s.size();
    int k=read();
    for(int i=0;i<l;i++){
            for(int j=0;j<=i;j++){
                int ff=0;
                for(int z=0;z<=i-j;z++){
                    if (s[z]!=s[j+z]) ff=1;
                }
                if (i-j-j+1<=0) continue;
                if (ff==0&&(i-j-j+1)%k==0) f[i]++;
            }
    }
    ll ans=1;
    for(int i=0;i<l;i++) ans=(ans*(f[i]+1))%998244353;
    cout<<ans<<endl;
}

int  main(){
    //     freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int n=read();
    while(n--){
    doit();
    }
    return 0;
}
