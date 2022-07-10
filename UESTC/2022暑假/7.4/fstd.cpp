#include<bits/stdc++.h>
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


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int p,q;
		scanf("%d%d",&p,&q);
		int k=p-q;
		if(k<0){
			printf("%d\n",-k);
			continue;
		}
		int ans=inf;
		int res=0;
		int num=0;
		while(1){
			//printf("%d %d %d\n",k,res,ans);
			int cnt=0,temp=k;
			while(temp){
				temp>>=1;
				cnt++;
			}
			if(k==(1<<cnt)-1){
				ans=min(ans,res+cnt+num);
				break;
			}
			ans=min(ans,max(num,(1<<cnt)-1-k)+cnt+res);
      if (ans == 14) {
        cout << k << "-------------" << endl;
      }
			k-=(1<<(cnt-1))-1;
			res+=cnt-1;
			
			num++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
