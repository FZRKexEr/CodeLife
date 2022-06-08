#include<bits/stdc++.h>
using namespace std;

bool dfs(unsigned long long x, unsigned long long ws, int d, int cs, int nowws);
int n;

int main()
{
    int i,ok = 1,ccnt = 0,ans;
    unsigned long long cnt = 1,temp,x;
    scanf("%d%llu",&n,&x);
    temp = x;
    while(temp > 0)
    {
        temp /= 10;
        cnt *= 10;
        ccnt ++;
    }
    cnt /= 10;
    for(i=1;i<68 && ok;i++)
    {
        if(dfs(x,cnt,i,1,ccnt))
        {
            ok = 0;
            ans = i-1;
        }
    }
    if(ok) printf("-1");
    else printf("%d",ans);
    return 0;
}
bool dfs(unsigned long long x, unsigned long long ws, int d, int cs, int nowws)
{
    if(nowws == n) return 1;
    if(d == cs || d-cs+nowws < n) return 0;
    int num[15];
    fill(num,num+15,0);
    unsigned long long i,temp = x;
    while(temp)
    {
        num[temp%10] ++;
        temp /= 10;
    }
    for(i=9;i>1;i--)
    {
        if(num[i])
        {
            if(x * i / ws / 10 > 0)
            {
                nowws ++;
                ws *= 10;
            }
            if(dfs(x*i,ws,d,cs+1,nowws))
                return 1;
        }
    }
    return 0;
}
