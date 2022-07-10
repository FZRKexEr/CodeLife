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

ll a[1000005],b[1000005];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++) b[i]=read();
        while(m--){
            int f=read();
            if (f==1) {
                int x=read(),y=read();
                a[x]=y;
            }
            else if (f==2) {
                int x=read(),y=read();
                b[x]=y;
            }
            else {
                int l=read();
                ll now=0;
                for(int i=1;i<=l;i++){
                    now=max(now+b[i],a[i]);
                }
                cout<<now<<endl;
            }
        }
    }
    return 0;
}
