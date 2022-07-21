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

const int maxn=300000+10;
int n,m,r;
int id[maxn],dep[maxn],fa[maxn],top[maxn];
int siz[maxn],son[maxn],cnt;
vector<int>e[maxn];


struct Segment_Tree {
  struct Info {
    int sum[8]; 
  };

  struct Tree {
    int l, r; 
    Info val;
  };  
  vector<Tree> tree;
  vector<int> lazy;

  Segment_Tree(int n) {
    tree.resize(n * 4 + 10);  
    lazy.resize(n * 4 + 10);
  }

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    for (int i = 0; i <= 7; i++) {
      res.sum[i] = a.sum[i] + b.sum[i];
    }
    return res;
  }

  void build(int pos, int l, int r) {

    tree[pos].l = l; tree[pos].r = r;
    lazy[pos] = 0;

    int m = l + (r - l) / 2;
    if (l == r) {
      tree[pos].val.sum[0] = 1; 
      for (int i = 1; i <= 7; i++) {
        tree[pos].val.sum[i] = 0;
      }
      return;
    } 
    build(pos << 1, l, m);
    build(pos << 1 | 1, m + 1, r);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, int val) {
    if (val == 8) {
      lazy[pos] = 8;

      for (int i = 0; i <= 7; i++) {
        tree[pos].val.sum[i] = 0;
      }
      tree[pos].val.sum[0] = tree[pos].r - tree[pos].l + 1;

    } else {
      lazy[pos] |= val;
      for (int i = 7; i > 0; i--) {
        for (int j = (i - 1) & i; j > 0; j = (j - 1) & i) {
          if ((j | val) != i) continue;
          tree[pos].val.sum[i] += tree[pos].val.sum[j];      
          tree[pos].val.sum[j] = 0;
        }
        if (i == val) {
          tree[pos].val.sum[i] += tree[pos].val.sum[0];
          tree[pos].val.sum[0] = 0;
        }
      }
    }
  }

  // 传递懒人标记
  void push_down(int pos) {
    if (tree[pos].l == tree[pos].r) {
      lazy[pos] = 0;
    } else {
      if (lazy[pos] == 0) return; 
      add(pos << 1, lazy[pos]); 
      add(pos << 1 | 1, lazy[pos]);
      lazy[pos] = 0;
    }
  } 

  void modify(int pos, int l, int r, long long val) {
    assert(l <= r);
    push_down(pos);
    if (tree[pos].l >= l && tree[pos].r <= r) {
      add(pos, val);
      return;
    }  
    int m = tree[pos].l + (tree[pos].r - tree[pos].l) / 2;
    if (l <= m) modify(pos << 1, l, r, val);
    if (r > m) modify(pos << 1 | 1, l, r, val);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {

    assert(l <= r);
    push_down(pos);
    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].val;
    }   
    int m = tree[pos].l + (tree[pos].r - tree[pos].l) / 2;
    Info res;

    if (l <= m && r > m) {
      res = merge(query(pos << 1, l, r), query(pos << 1 | 1, l , r));
    } else if (l > m) {
      res = query(pos << 1 | 1, l, r);
    } else if (r <= m) {
      res = query(pos << 1, l, r);
    }

    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
};


Segment_Tree T(maxn);

inline void updRange1(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
       T.modify(1,min(id[x],id[top[x]]),max(id[top[x]],id[x]),1);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
     T.modify(1,min(id[x],id[y]),max(id[x],id[y]),1);
}

inline void updRange2(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        T.modify(1,min(id[x],id[top[x]]),max(id[top[x]],id[x]),2);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    T.modify(1,min(id[x],id[y]),max(id[x],id[y]),2);
}


inline int qSon(int x){
    assert(siz[x]>0);
    return T.query(1,id[x],id[x]+siz[x]-1).sum[7];
}

inline void updSon(int x){
    assert(siz[x]-1>=0);
     T.modify(1,id[x],id[x]+siz[x]-1,4);
}

inline void dfs1(int x,int f,int deep){//x当前节点，f父亲，deep深度 
    dep[x]=deep;//标记每个点的深度 
    fa[x]=f;//标记每个点的父亲 
    siz[x]=1;//标记每个非叶子节点的子树大小 
    int maxson=-1;//记录重儿子的儿子数 
    for(int i=0;i<(int)e[x].size();i++){
        int y=e[x][i];
        if(y==f)continue;//若为父亲则continue 
        dfs1(y,x,deep+1);//dfs其儿子 
        siz[x]+=siz[y];//把它的儿子数加到它身上 
        if(siz[y]>maxson)son[x]=y,maxson=siz[y];//标记每个非叶子节点的重儿子编号 
    }
   // cout<<siz[x]<<endl;
}

inline void dfs2(int x,int topf){//x当前节点，topf当前链的最顶端的节点 
    id[x]=++cnt;//标记每个点的新编号 
    top[x]=topf;//这个点所在链的顶端 
    if(!son[x])return;//如果没有儿子则返回 
    dfs2(son[x],topf);//按先处理重儿子，再处理轻儿子的顺序递归处理 
     for(int i=0;i<(int)e[x].size();i++){
        int y=e[x][i];
        if(y==fa[x]||y==son[x])continue;
        dfs2(y,y);//对于每一个轻儿子都有一条从它自己开始的链 
    }
}

void init(){
	for(int i=1;i<=n;i++) siz[i]=fa[i]=dep[i]=top[i]=id[i]=son[i]=0;
    for(int i=0;i<=n;i++) e[i].clear();
     for(int i=2;i<=n;i++){int a=read();e[a].push_back(i);}
}

void doit(){
  n=read(),m=read();
    r=1; cnt=0;
    init(); 
    dfs1(r,0,1);
    dfs2(r,r);
    assert(siz[1] == n);

    T.build(1,1,n);

    while(m--){
        int x=read(),y=read(),z=read();

        T.build(1, 1, n);

//        T.modify(1, 1, n, 8); // 区间覆盖成 0
        
        for(int i=1;i<=x;i++){
            int now=read();
            updRange1(now,1);
        }
        for(int i=1;i<=y;i++){
             int now=read();
            updRange2(now,1);
        }
        for(int i=1;i<=z;i++){
             int now=read();
            updSon(now);
        }

        printf("%d\n",qSon(1));
    
     }
}

int main(){
    int T=read();
    while(T--){
        doit();
    }
}
