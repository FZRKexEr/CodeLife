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

int a[1000005];

int  main(){
//    freopen("in.txt","r",stdin);
    int n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    int m=read();
    while(m--){
        int x=read(),y=read();
        swap(a[x],a[y]);
        ll ans=0;
        for(int i=1;i<=n;i++){
            int num1=0,num2=0;
            for(int j=1;j<i;j++) if (a[j]<a[i]) num1++;
            for(int j=i+1;j<=n;j++) if (a[j]<a[i]) num2++;
            ans+=min(num1,num2);
        }
        cout<<ans<<endl;;
        swap(a[x],a[y]);
    }    
    return 0;
}
