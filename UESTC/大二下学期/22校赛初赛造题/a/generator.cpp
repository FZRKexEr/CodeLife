//
//  generator.cpp
//  2022-05-05 17:07
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

// 传入两个参数, 数据组数 T 和 n, m 上限 limit

int main(int argc, char* argv[]) {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  long long z = atol(argv[1]);
  long long limit = atol(argv[2]);

  random_device rd; 
  mt19937 seed(rd());
  uniform_int_distribution<long long> U(1, limit); 

  cout << z << endl;
  for (int i = 1; i <= z; i++) {
    cout << U(seed) << " " << U(seed) << endl;
  }
   
  return 0;
}
