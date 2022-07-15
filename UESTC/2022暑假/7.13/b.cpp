#include<bits/stdc++.h>
#define LOCAL
#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif
using namespace std;
typedef long long ll;
#define mp make_pair
#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define UNI(x) sort(ALL(x)),x.resize(unique(ALL(x))-x.begin())
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define ls (u<<1)
#define rs (u<<1|1)
const int inf=2e9+7;
const int N=2e6+10;
multiset<int> sum;
int a[22],b[N];
inline long long read(){
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if (ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int main(){
  file(); 
	int T=read();
	while(T--){
		int n=read();
		sum.clear();
		for(int i=0;i<(1<<n)-1;i++){
			int x=read();
			sum.insert(x);
		}
		int tot=0;
		bool f=true;
		for(int i=0;i<n;i++){
			multiset<int>::iterator iter;
			iter=sum.begin();
			a[i]=*iter;
			sum.erase(iter);
			int temp=tot;
			for(int j=0;j<temp;j++){
				multiset<int>::iterator iter2=sum.find(b[j]+a[i]);
				if(iter2==sum.end()){
					f=false;
					break;
				}else{
					sum.erase(iter2);
					b[tot++]=b[j]+a[i];
				}
			}
			if(!f)break;
			b[tot++]=a[i];
		}
		if(!f){
			printf("NO\n");
			continue;
		}
		for(int i=0;i<n;i++)printf("%d ",a[i]);
		printf("\n");
	}
  Timer();
	return 0;
}
