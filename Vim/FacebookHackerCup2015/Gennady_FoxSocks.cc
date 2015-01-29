#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <memory.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 4000010;

struct parity_tree {

  int n;
  vector <int> cnt0, cnt1, put, inv;

  void build(int x, int l, int r, vector <int> &s) {
    if (l == r) {
      put[x] = s[l] % 2;
      inv[x] = 0;
      cnt0[x] = (put[x] == 0);
      cnt1[x] = (put[x] == 1);
      return;
    }
    int y = (l + r) >> 1;
    build(x + x, l, y, s);
    build(x + x + 1, y + 1, r, s);
    put[x] = -1;
    inv[x] = 0;
    cnt0[x] = cnt0[x + x] + cnt0[x + x + 1];
    cnt1[x] = cnt1[x + x] + cnt1[x + x + 1];
  }

  parity_tree(vector <int> s) {
    n = s.size();
    cnt0.resize(4 * n + 10);
    cnt1.resize(4 * n + 10);
    put.resize(4 * n + 10);
    inv.resize(4 * n + 10);
    build(1, 0, n - 1, s);
  }

  void relax(int x, int l, int r) {
    if (put[x] != -1) {
      for (int y = x + x; y <= x + x + 1; y++) {
        int yl = (y == x + x ? l : ((l + r) >> 1) + 1);
        int yr = (y == x + x ? ((l + r) >> 1) : r);
        int len = yr - yl + 1;
        put[y] = put[x];
        inv[y] = inv[x];
        cnt0[y] = ((put[y] ^ inv[y]) == 0) * len;
        cnt1[y] = ((put[y] ^ inv[y]) == 1) * len;
      }
      put[x] = -1;
      inv[x] = 0;
    }
    if (inv[x]) {
      for (int y = x + x; y <= x + x + 1; y++) {
        inv[y] ^= 1;
        swap(cnt0[y], cnt1[y]);
      }
      inv[x] = 0;
    }
  }

  void invert(int x, int l, int r, int ll, int rr) {
    if (r < ll || rr < l || ll > rr) {
      return;
    }
    if (ll <= l && r <= rr) {
      inv[x] ^= 1;
      swap(cnt0[x], cnt1[x]);
      return;
    }
    relax(x, l, r);
    int y = (l + r) >> 1;
    invert(x + x, l, y, ll, rr);
    invert(x + x + 1, y + 1, r, ll, rr);
    cnt0[x] = cnt0[x + x] + cnt0[x + x + 1];
    cnt1[x] = cnt1[x + x] + cnt1[x + x + 1];
  }

  void modify_set(int x, int l, int r, int ll, int rr, int value) {
    if (r < ll || rr < l || ll > rr) {
      return;
    }
    if (ll <= l && r <= rr) {
      put[x] = value;
      inv[x] = 0;
      cnt0[x] = (value == 0) * (r - l + 1);
      cnt1[x] = (value == 1) * (r - l + 1);
      return;
    }
    relax(x, l, r);
    int y = (l + r) >> 1;
    modify_set(x + x, l, y, ll, rr, value);
    modify_set(x + x + 1, y + 1, r, ll, rr, value);
    cnt0[x] = cnt0[x + x] + cnt0[x + x + 1];
    cnt1[x] = cnt1[x + x] + cnt1[x + x + 1];
  }

  int count_ones(int x, int l, int r, int ll, int rr) {
    if (r < ll || rr < l || ll > rr) {
      return 0;
    }
    if (ll <= l && r <= rr) {
      return cnt1[x];
    }
    relax(x, l, r);
    int y = (l + r) >> 1;
    int res = 0;
    res += count_ones(x + x, l, y, ll, rr);
    res += count_ones(x + x + 1, y + 1, r, ll, rr);
    cnt0[x] = cnt0[x + x] + cnt0[x + x + 1];
    cnt1[x] = cnt1[x + x] + cnt1[x + x + 1];
    return res;
  }
};

parity_tree *odd_tree = NULL;
parity_tree *even_tree = NULL;

const int md = 1000000000;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}

inline int addr(int a, int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
  return a;
}

inline int mul(int a, int b) {
  return (long long)a * b % md;
}

vector <int> make(int len, int modulo, int add) {
  vector <int> ret;
  int v1, v2, x, y, z;
  scanf("%d %d %d %d %d", &v1, &v2, &x, &y, &z);
  ret.push_back(v1);
  ret.push_back(v2);
  for (int i = 2; i < len; i++) {
    ret.push_back((x * 1LL * ret[i - 2] + y * 1LL * ret[i - 1] + z) % modulo + add);
  }
  return ret;
}

int put[N], addc[N], addi[N], sum[N];

void build(int x, int l, int r, vector <int> &s) {
  if (l == r) {
    put[x] = s[l];
    addc[x] = 0;
    addi[x] = 0;
    sum[x] = s[l];
    return;
  }
  int y = (l + r) >> 1;
  build(x + x, l, y, s);
  build(x + x + 1, y + 1, r, s);
  put[x] = -1;
  addc[x] = 0;
  addi[x] = 0;
  sum[x] = addr(sum[x + x], sum[x + x + 1]);
}

int sum_ind(int from, int to) {
  int x = from + to;
  int y = to - from + 1;
  if (x % 2 == 0) {
    x /= 2;
  } else {
    y /= 2;
  }
  return mul(x, y);
}

void relax(int x, int l, int r) {
  if (put[x] != -1) {
    for (int y = x + x; y <= x + x + 1; y++) {
      int yl = (y == x + x ? l : ((l + r) >> 1) + 1);
      int yr = (y == x + x ? ((l + r) >> 1) : r);
      int len = yr - yl + 1;
      put[y] = put[x];
      addc[y] = addc[x];
      addi[y] = addi[x];
      sum[y] = addr(mul(addr(put[y], addc[y]), len), mul(addi[y], sum_ind(yl, yr)));
    }
    put[x] = -1;
    addc[x] = 0;
    addi[x] = 0;
  }
  if (addc[x] != 0) {
    for (int y = x + x; y <= x + x + 1; y++) {
      int yl = (y == x + x ? l : ((l + r) >> 1) + 1);
      int yr = (y == x + x ? ((l + r) >> 1) : r);
      int len = yr - yl + 1;
      add(addc[y], addc[x]);
      add(sum[y], mul(addc[x], len));
    }
    addc[x] = 0;
  }
  if (addi[x] != 0) {
    for (int y = x + x; y <= x + x + 1; y++) {
      int yl = (y == x + x ? l : ((l + r) >> 1) + 1);
      int yr = (y == x + x ? ((l + r) >> 1) : r);
      int len = yr - yl + 1;
      add(addi[y], addi[x]);
      add(sum[y], mul(addi[x], sum_ind(yl, yr)));
    }
    addi[x] = 0;
  }
}

int find_sum(int x, int l, int r, int ll, int rr) {
  if (r < ll || rr < l) {
    return 0;
  }
  if (ll <= l && r <= rr) {
    return sum[x];
  }
  relax(x, l, r);
  int y = (l + r) >> 1;
  int res = 0;
  add(res, find_sum(x + x, l, y, ll, rr));
  add(res, find_sum(x + x + 1, y + 1, r, ll, rr));
  sum[x] = addr(sum[x + x], sum[x + x + 1]);
  return res;
}

void modify_set(int x, int l, int r, int ll, int rr, int value) {
  if (r < ll || rr < l) {
    return;
  }
  if (ll <= l && r <= rr) {
    put[x] = value;
    addc[x] = 0;
    addi[x] = 0;
    sum[x] = mul(put[x], r - l + 1);
    return;
  }
  relax(x, l, r);
  int y = (l + r) >> 1;
  modify_set(x + x, l, y, ll, rr, value);
  modify_set(x + x + 1, y + 1, r, ll, rr, value);
  sum[x] = addr(sum[x + x], sum[x + x + 1]);
}

void modify_add(int x, int l, int r, int ll, int rr, int valuec, int valuei) {
  if (r < ll || rr < l) {
    return;
  }
  if (ll <= l && r <= rr) {
    add(addc[x], valuec);
    add(addi[x], valuei);
    add(sum[x], mul(valuec, r - l + 1));
    add(sum[x], mul(valuei, sum_ind(l, r)));
    return;
  }
  relax(x, l, r);
  int y = (l + r) >> 1;
  modify_add(x + x, l, y, ll, rr, valuec, valuei);
  modify_add(x + x + 1, y + 1, r, ll, rr, valuec, valuei);
  sum[x] = addr(sum[x + x], sum[x + x + 1]);
}

int n, ans;

void just_sum(int from, int to) {
  add(ans, find_sum(1, 0, n - 1, from, to));
}

void sum_and_set(int from, int to, int value) {
  add(ans, find_sum(1, 0, n - 1, from, to));
  modify_set(1, 0, n - 1, from, to, value);
  add(ans, find_sum(1, 0, n - 1, from, to));
  even_tree->modify_set(1, 0, even_tree->n - 1, (from + 1) / 2, to / 2, value & 1);
  odd_tree->modify_set(1, 0, odd_tree->n - 1, from / 2, (to + 1) / 2 - 1, value & 1);
}

void add_progression(int from, int to, int valuec, int valuei) {
  add(ans, md - find_sum(1, 0, n - 1, from, to));
  modify_add(1, 0, n - 1, from, to, valuec, valuei);
  add(ans, find_sum(1, 0, n - 1, from, to));
  if (valuec & 1) {
    even_tree->invert(1, 0, even_tree->n - 1, (from + 1) / 2, to / 2);
  }
  if ((valuec ^ valuei) & 1) {
    odd_tree->invert(1, 0, odd_tree->n - 1, from / 2, (to + 1) / 2 - 1);
  }
}

void go_parity(int from, int to) {
  add(ans, even_tree->count_ones(1, 0, even_tree->n - 1, (from + 1) / 2, to / 2));
  add(ans, odd_tree->count_ones(1, 0, odd_tree->n - 1, from / 2, (to + 1) / 2 - 1));
}

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int m;
    scanf("%d %d", &n, &m);
    vector <int> s = make(n, md, 0);
    vector <int> o = make(m, 4, 1);
    vector <int> a = make(m, n, 1);
    vector <int> b = make(m, n, 1);
    vector <int> c = make(m, md, 0);
    vector <int> d = make(m, md, 0);
    build(1, 0, n - 1, s);
    vector <int> even, odd;
    for (int i = 0; i < n; i++) {
      if (i & 1) {
        odd.push_back(s[i]);
      } else {
        even.push_back(s[i]);
      }
    }
    even_tree = new parity_tree(even);
    odd_tree = new parity_tree(odd);
    ans = 0;
    for (int id = 0; id < m; id++) {
      a[id]--;
//      cerr << "operation " << id << ": " << o[id] << " " << a[id] << " " << b[id] << " " << c[id] << " " << d[id] << endl;
      if (o[id] == 1) {
        int from = a[id];
        int to = a[id] + b[id] - 1;
        if (to >= n) {
          add_progression(from, n - 1, addr(c[id], md - mul(from, d[id])), d[id]);
          add_progression(0, to - n, addr(c[id], mul(n - from, d[id])), d[id]);
        } else {
          add_progression(from, to, addr(c[id], md - mul(from, d[id])), d[id]);
        }
      }
      if (o[id] == 2) {
        int from = a[id];
        int to = a[id] + b[id] - 1;
        if (to >= n) {
          sum_and_set(from, n - 1, c[id]);
          sum_and_set(0, to - n, c[id]);
        } else {
          sum_and_set(from, to, c[id]);
        }
      }
      if (o[id] == 3) {
        int from = a[id];
        int to = a[id] + b[id] - 1;
        if (to >= n) {
          just_sum(from, n - 1);
          just_sum(0, to - n);
        } else {
          just_sum(from, to);
        }
      }
      if (o[id] == 4) {
        int from = a[id];
        int to = a[id] + b[id] - 1;
        if (to >= n) {
          go_parity(from, n - 1);
          go_parity(0, to - n);
        } else {
          go_parity(from, to);
        }
      }
    }
    printf("%d\n", ans);
    fflush(stdout);
    cerr << "test " << qq << " ok, clock() = " << clock() << " ms" << endl;
  }
  return 0;
}
