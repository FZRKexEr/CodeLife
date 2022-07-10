//
//  e.cpp
//  2022-06-23 21:43
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

#define endl '\n'
static struct FastInput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t chars_read = 0;
  size_t buf_pos = 0;
  FILE *in = stdin;
  char cur = 0;

  inline char get_char() {
    if (buf_pos >= chars_read) {
      chars_read = fread(buf, 1, BUF_SIZE, in);
      buf_pos = 0;
      buf[0] = (chars_read == 0 ? -1 : buf[0]);
    }
    return cur = buf[buf_pos++];
  }
 
  inline void tie(int) {}

  inline explicit operator bool() {
    return cur != -1;
  }

  inline static bool is_blank(char c) {
    return c <= ' ';
  }

  inline bool skip_blanks() {
    while (is_blank(cur) && cur != -1) {
      get_char();
    }
    return cur != -1;
  }
 
  inline FastInput& operator>>(char& c) {
    skip_blanks();
    c = cur;
    return *this;
  }
  
  inline FastInput& operator>>(string& s) {
    if (skip_blanks()) {
      s.clear();
      do {
        s += cur;
      } while (!is_blank(get_char()));
    }
    return *this;
  }
 
  template <typename T>
  inline FastInput& read_integer(T& n) {
    // unsafe, doesn't check that characters are actually digits
    n = 0;
    if (skip_blanks()) {
      int sign = +1;
      if (cur == '-') {
        sign = -1;
        get_char();
      }
      do {
        n += n + (n << 3) + cur - '0';
      } while (!is_blank(get_char()));
      n *= sign;
    }
    return *this;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, FastInput&>::type operator>>(T& n) {
    return read_integer(n);
  }
  
  #if !defined(_WIN32) || defined(_WIN64)
  inline FastInput& operator>>(__int128& n) {
    return read_integer(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, FastInput&>::type operator>>(T& n) {
    // not sure if really fast, for compatibility only
    n = 0;
    if (skip_blanks()) {
      string s;
      (*this) >> s;
      sscanf(s.c_str(), "%lf", &n);
    }
    return *this;
  }
} fast_input;

#define cin fast_input

static struct FastOutput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t buf_pos = 0;
  static constexpr int TMP_SIZE = 1 << 20;
  char tmp[TMP_SIZE];
  FILE *out = stdout;

  inline void put_char(char c) {
    buf[buf_pos++] = c;
    if (buf_pos == BUF_SIZE) {
      fwrite(buf, 1, buf_pos, out);
      buf_pos = 0;
    }
  }

  ~FastOutput() {
    fwrite(buf, 1, buf_pos, out);
  }

  inline FastOutput& operator<<(char c) {
    put_char(c);
    return *this;
  }

  inline FastOutput& operator<<(const char* s) {
    while (*s) {
      put_char(*s++);
    }
    return *this;
  }
 
  inline FastOutput& operator<<(const string& s) {
    for (int i = 0; i < (int) s.size(); i++) {
      put_char(s[i]);
    }
    return *this;
  }
 
  template <typename T>
  inline char* integer_to_string(T n) {
    // beware of TMP_SIZE
    char* p = tmp + TMP_SIZE - 1;
    if (n == 0) {
      *--p = '0';
    } else {
      bool is_negative = false;
      if (n < 0) {
        is_negative = true;
        n = -n;
      }
      while (n > 0) {
        *--p = (char) ('0' + n % 10);
        n /= 10;
      }
      if (is_negative) {
        *--p = '-';
      }
    }
    return p;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, char*>::type stringify(T n) {
    return integer_to_string(n);
  }

  #if !defined(_WIN32) || defined(_WIN64)
  inline char* stringify(__int128 n) {
    return integer_to_string(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, char*>::type stringify(T n) {
    sprintf(tmp, "%.17f", n);
    return tmp;
  }

  template <typename T>
  inline FastOutput& operator<<(const T& n) {
    auto p = stringify(n);
    for (; *p != 0; p++) {
      put_char(*p);
    }
    return *this;
  }
} fast_output;

#define cout fast_output


vector<string> vec_splitter(string s) {
	s += ',';
  vector<string> res;
	while(!s.empty()) {
    res.push_back(s.substr(0, s.find(',')));
		s = s.substr(s.find(',') + 1);
	}
	return res;
}

void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
  stringstream ss; ss << H;
  cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}


#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 2022
#endif

random_device rd; 
mt19937 seed(rd());
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> U(1, 1000000000ll); // 1 - 1e9

const int MOD = 1e9 + 7;
int power(int a, int b) {
  assert(b >= 0);
  int base = a, ans = 1;
  while (b) {
    if (b & 1) ans = ans * base % MOD;
    base = base * base % MOD;
    b >>= 1;
  }
  return ans;
}

int START_TIME = -1;
void file() {
#ifndef ONLINE_JUDGE
  START_TIME = clock();
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}
void Timer() {
#ifndef ONLINE_JUDGE
  if (START_TIME != -1)
    cout << endl << 1.0 * (clock() - START_TIME) / CLOCKS_PER_SEC << "s";
#endif
}


// 无旋 Treap
// 特性说明:
// 1. kth 可以求出 Treap 中第 k 小的数 1-indexed
// 2. merge_treap 可以合并两个 treap，并且不需要保证它们之间的大小关系, 例题: CF911G。
//    但是效率成迷, 感性理解大概是大常数 O(logn),  实测:
//    a. 在洛谷快速排序中 merge 可以 AC, merge_treap T 3组。
//    b. Treap 板题merge 和 merge_treap 都可以AC。(因为数据水)
//    c. Treap 板题加强版中 merge_treap 用时是 merge 的两倍, 但还是 AC 了
// 3. erase 可以删除一个 key, 如果要删光 key, 把 res2[1] 赋值成 -1 即可
// 4. 这个 Treap 是模拟的 multiset
// 5. 没有 lower_bound 和 upper_bound, nxt() pre() count() 够用了，不要尝试实现 lower_bound,
//    返回 pos(下标) 对 Treap 没用，因为不能保证是根结点。
// 
// 注意:
// 1. 不是根结点的点是完全没用的，不能提供任何有用性质。所以一定要用 split 来得到根结点。
// 2. 不要随意在外面修改 size。修改后要想办法 update
// 3. 时刻留意是不是数组访问了-1
// 4. create 一定不要用 mt19937, 花费时间是函数随机的两倍!
// 5. nxt pre 可以在找不到的时候返回-1，kth 必须找得到。 
// 6. 判断子树是否为空不能用 size = 0 判断，子树为空的时候下标是 -1 !
// 
// 修改:
// 1. push_down 只用在 merge merge_treap output 
// 2. 区间操作修改 push_down
// 
// 模板题: https://www.luogu.com.cn/problem/P6136

struct Treap {
  struct Node {
    int l, r; 
    int key, pri, size;
    int sum;
    int lazy;
    Node (int a, int b) : key(a), pri(b) { 
      l = r = -1, size = 1, lazy = 0; 
    }
  };

  vector<Node> tree; 
  vector<int> root; 
  int seed = 1;
  
  Treap(int n) : root(n + 1, -1) {} 

  void push_down(int pos) {
      
  }
  
  array<int, 2> split(int pos, int key) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    if (tree[pos].key <= key) {
      array<int, 2> res = split(tree[pos].r, key);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split(tree[pos].l, key);
      tree[pos].l = res[1]; 
      update(pos);
      return {res[0], pos};
    }
  }

  array<int, 2> split_sz(int pos, int sz) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
    if (lsize <= sz) {
      array<int, 2> res = split_sz(tree[pos].r, sz - lsize);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split_sz(tree[pos].l, sz); 
      tree[pos].l = res[1];
      update(pos);
      return {res[0], pos};
    }
  }

  int merge(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    if (tree[x].pri < tree[y].pri) {
      push_down(x);
      tree[x].r = merge(tree[x].r, y);  
      update(x);
      return x;
    } else {
      push_down(y);
      tree[y].l = merge(x, tree[y].l); 
      update(y);
      return y;
    }
  }

  int merge_treap(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    push_down(x), push_down(y);
    if (tree[x].pri > tree[y].pri) swap(x, y);
    array<int, 2> res = split(y, tree[x].key);
    tree[x].l = merge_treap(tree[x].l, res[0]);
    tree[x].r = merge_treap(tree[x].r, res[1]);
    update(x);
    return x;
  }

  vector<int> output(int pos) {
    if (pos == -1) return {};
    push_down(pos);
    vector<int> res;
    vector<int> l = output(tree[pos].l), r = output(tree[pos].r);
    res.insert(res.end(), l.begin(), l.end());
    res.push_back(tree[pos].key);
    res.insert(res.end(), r.begin(), r.end());
    return res;
  }

  void update(int pos) {
    if (pos == -1) return;
    tree[pos].size = 1;
    tree[pos].sum = tree[pos].key;
    if (tree[pos].l != -1) {
      tree[pos].size += tree[tree[pos].l].size;
      tree[pos].sum += tree[tree[pos].l].sum;
    }
    if (tree[pos].r != -1) {
      tree[pos].size += tree[tree[pos].r].size;
      tree[pos].sum += tree[tree[pos].r].sum;
    }
  }

  int func_rand() {
    return seed *= 19260817;
  }

  int create(int key) {
    tree.emplace_back(key, func_rand());
    return (int) tree.size() - 1;
  }
  
  void insert(int &pos, int key) {
    int o = create(key);
    array<int, 2> res = split(pos, key);
    pos = merge(merge(res[0], o), res[1]); 
  }

  int rank(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1);
    int rk = (res[0] == -1) ? 1 : tree[res[0]].size + 1;
    pos = merge(res[0], res[1]);
    return rk;
  }

  int kth(int pos, int k) {
    while (pos != -1) {
      int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
      if (lsize == k) return tree[pos].key; 
      if (k < lsize) pos = tree[pos].l;
      if (k > lsize) pos = tree[pos].r, k -= lsize;
    }
    assert(0);
  }

  void erase(int &pos, int key) {
    array<int, 2> res1 = split(pos, key); 
    array<int, 2> res2 = split(res1[0], key - 1); 
    if (res2[1] != -1) {
      res2[1] = merge(tree[res2[1]].l, tree[res2[1]].r);
    }
    pos = merge(merge(res2[0], res2[1]), res1[1]);
  }

  int pre(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1); 
    if (res[0] == -1) return -1;
    int ans = kth(res[0], tree[res[0]].size);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int nxt(int &pos, int key) {
    array<int, 2> res = split(pos, key);
    if (res[1] == -1) return -1;
    int ans = kth(res[1], 1);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int count(int &pos, int key) {
    array<int, 2> res1 = split(pos, key);
    array<int, 2> res2 = split(res1[0], key - 1);
    int ans = res2[1] == -1 ? 0 : tree[res2[1]].size;
    pos = merge(merge(res2[0], res2[1]), res1[1]);
    return ans;
  } 
  
  int ask_sum(int &pos, int l, int r) {
    if (l == 0 || r == 0) return 0;
    if (l > r) return 0;
    auto res1 = split_sz(pos, l - 1);   
    auto res2 = split_sz(res1[1], r - (l - 1));
    int ans = tree[res2[0]].sum;
    pos = merge_treap(res1[0], merge_treap(res2[0], res2[1]));
    return ans;
  }
};
signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);

  int z = 1;
  while (z--) {
    int n; cin >> n;
    Treap T(1);
    set<int> light;
    
    for (int i = 1; i <= n; i++) {
      int tp, d; cin >> tp >> d;
      if (d > 0) {
        if (tp) {
          light.insert(d);
        } 
        T.insert(T.root[1], d);
      } else {
        if (tp) {
          light.erase(-d);
        } 
        T.erase(T.root[1], -d);
      }
      if (T.root[1] == -1) {
        cout << 0 << endl;
        continue;
      }

      int size = T.tree[T.root[1]].size;
      if ((int) light.size() == 0) {
        cout << T.ask_sum(T.root[1], 1, size) << endl;
        continue;  
      }
      
      int goal = *light.begin();
      int rk = T.rank(T.root[1], goal);
      
      if ((int) light.size() + rk - 1 == size) {
        int ans = 0;
        ans += T.ask_sum(T.root[1], rk + 1, size);
        ans += T.ask_sum(T.root[1], rk - 1, rk - 1);
        ans *= 2;
        ans += T.ask_sum(T.root[1], rk, rk);
        ans += T.ask_sum(T.root[1], 1, rk - 2);
        cout << ans << endl;
      } else {
        int l = size - (int) light.size() + 1, r = size;
        int ans = T.ask_sum(T.root[1], l, r); 
        ans *= 2;
        ans += T.ask_sum(T.root[1], 1, l - 1);
        cout << ans << endl;
      }
    }
  }

  Timer();
  return 0;
}
