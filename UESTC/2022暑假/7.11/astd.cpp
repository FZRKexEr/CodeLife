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

void doit(){
    int a,b;
    scanf("%d%d",&a,&b);
    if (a>=b){
        if (a<65) {printf("Impossible\n");return ;}
        if (a<75) {
            if (b>=50){
            printf("3:2\n");
            int  res=b-50;
            //printf("25:%d 25:%d 0:25 %d:25 15:0\n",res/2,res-res/2,a-65);
            return ;
            }
        }
        if (a==75) {
            if (b>69) {
                printf("3:1\n");
             //   printf("0:25 ");
                int res=b-25;
              //  printf("25:%d ",min(res,23));
                res-=23; res=max(res,0);
              //  printf("25:%d ",min(res,23));
                res-=23;     res=max(res,0);
               // printf("25:%d\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
            else {
                printf("3:0\n");
                int res=b;
                //printf("25:%d ",min(res,23));
                res-=23; res=max(res,0);
               // printf("25:%d ",min(res,23));
                res-=23; res=max(res,0);
               // printf("25:%d\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
        }
        else {
          if (a < 75) {printf("Impossible\n");return ;}
            if (a-b>73) {printf("Impossible\n");return ;}
            if (a-b<=5) {
                 printf("3:1\n");
              //  printf("0:25 ");
                int res=b-25;
               // printf("%d:%d ",a-50,a-52);
                res-=(a-52); res=max(res,0);
               // printf("25:%d ",min(res,23));
                res-=23;  res=max(res,0);
               // printf("25:%d\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
            else if (a-b<=52){
                 printf("3:0\n");
                 int res=b;
               //  printf("%d:%d ",a-50,a-52);
                 res-=(a-52); res=max(res,0);
               //  printf("25:%d ",min(res,23));
                res-=23; res=max(res,0);
               // printf("25:%d\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
            else if (b>=25){
                if (a<98){
                printf("3:1\n");
               // printf("%d:25 ",a-75);
                int res=b-25;
              // printf("25:%d ",min(res,23));
                res-=23;  res=max(res,0);
               // printf("25:%d ",min(res,23));
                res-=23;  res=max(res,0);
               // printf("25:%d\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
                }
                else {
                    printf("3:1\n");
               //     printf("%d:%d ",a-75,a-73);
                    int res=b-(a-73);
                //    printf("25:%d ",min(res,23));
                    res-=23;  res=max(res,0);
                 //   printf("25:%d ",min(res,23));
                 res-=23;  res=max(res,0);
               //  printf("25:%d\n",min(res,23));
                    res-=23; res=max(res,0);
                      return ;
                }
            }
        }
    }
    else {
        if (a>=75&&b-a<=19){
            printf("3:1\n");
   //         printf("0:25 ");
            int res=b-25;
    //        printf("%d:%d ",a-50,a-52);
            res-=(a-52); res=max(res,0);
     //       printf("25:%d ",min(res,23));
            res-=23;  res=max(res,0);
      //      printf("25:%d\n",min(res,23));
            res-=23; res=max(res,0);
            return ;
        }
        if (a>=65&&b-a<=44){
             printf("3:2\n");
             if(b<=109){
       //     printf("%d:25 0:25 ",a-65);
            int res=b-50;
        //    printf("25:%d ",min(res,23));
            res-=23;  res=max(res,0);
         //   printf("25:%d ",min(res,23));
            res-=23;  res=max(res,0);
          //  printf("15:%d\n",min(res,13));
            return ;
            res-=23; res=max(res,0);
            }
            else {
              //  printf("%d:25 0:25 ",a-(b-84)-40);
                int res=b-50;
           //     printf("%d:%d ",res-34,res-36);
                res-=(res-46);
            //    printf("25:%d ",min(res,23));
                res-=23;  res=max(res,0);
             //   printf("15:%d\n",min(res,13));
                return ;
            }
        }
        if (a>=50&&b-a<=61&&b>=65){
            printf("2:3\n");
            if (b>=111){
                int resa=a,resb=b;
    //            printf("%d:%d ",resb-86,resb-88);
                resa-=(resb-86); resb=88;
     //           printf("25:23 ");
                resa-=25; resa=max(resa,0);
      //           printf("%d:25 ",min(resa,23));
                 resa-=23; resa=max(resa,0);
       //         printf("%d:25 ",min(resa,23));
                resa-=23; resa=max(resa,0);
        //        printf("%d:15\n",min(resa,13));
                return ;
            }
            else {
                int res=a,resb=b-65;
         //       printf("25:%d ",min(resb,23));
                resb-=23; resb=max(resb,0);
          //      printf("25:%d ",min(resb,23));
                res-=50;
           //      printf("%d:25 ",min(res,23));
                 res-=23; res=max(res,0);
            //    printf("%d:25 ",min(res,23));
                res-=23; res=max(res,0);
             //   printf("%d:15\n",min(res,13));
                return ;
            }
        }
        if (a>=25&&b-a<=73&&b>=75){
            if (b-75>=24) {
                printf("1:3\n");
              //  printf("%d:%d ",b-73,b-75);
                int res=a-(b-73);
               // printf("%d:25 ",min(res,23));
                 res-=23; res=max(res,0);
                //printf("%d:25 ",min(res,23));
                res-=23; res=max(res,0);
                //printf("%d:25\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
            else {
                printf("1:3\n");
      //          printf("%d:%d ",25,b-75);
                int res=a-25;
       //         printf("%d:25 ",min(res,23));
                 res-=23; res=max(res,0);
        //        printf("%d:25 ",min(res,23));
                res-=23; res=max(res,0);
         //       printf("%d:25\n",min(res,23));
                res-=23; res=max(res,0);
                return ;
            }
        }
        if (b==75&&a<=69){
            printf("0:3\n");
            int res=a;
          //  printf("%d:25 ",min(res,23));
            res-=23; res=max(res,0);
           //  printf("%d:25 ",min(res,23));
            res-=23; res=max(res,0);
           //  printf("%d:25\n",min(res,23));
            res-=23; res=max(res,0);
            return ;
        }
        if (b>75&&b-a<=52){
            printf("0:3\n");
            int res=a;
    //        printf("%d:%d ",b-52,b-50);
            res-=(b-52);res=max(res,0);
     //       printf("%d:25 ",min(res,23));
            res-=23; res=max(res,0);
      //      printf("%d:25\n",min(res,23));
            res-=23; res=max(res,0);
            return ;
        }
        {printf("Impossible\n");return ;}
    }
     printf("Impossible\n");return ;
}

int  main(){
  freopen("in.txt", "r", stdin);
  freopen("out2.txt", "w", stdout);
    //     freopen("input.in","r",stdin);
    // freopen("output.out","w",stdout);
    int n=read();
  //  cout<<n<<endl;
    while(n--){
    doit();
    }
    return 0;
}
