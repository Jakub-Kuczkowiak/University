#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pii;

class UnionFind
{
  private: vector<int> p, rank;
  public:

  UnionFind(int N) {
    rank.assign(N, 0); p.assign(N, 0);
    for(int i = 0; i < N; i++) p[i] = i;
  }
  
  int findSet(int i) {
    return (p[i] == i) ? i : (p[i] = findSet(p[i]));
  }

  bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
  }

  void unionSet(int i, int j) {
    if(!isSameSet(i, j)) {
      int x = findSet(i), y = findSet(j);
      if(rank[x] > rank[y]) p[y] = x;
      else {
        p[x] = y;
        if(rank[x] == rank[y]) rank[y]++;
      }
    }
  }
};

int main() {
  int n, m; scanf("%d %d", &n, &m);
  vector< pair<int, pair<int,int> > > edges;
  
  for(int i = 0; i < m; i++) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c); a--; b--;
    edges.push_back(make_pair(c, make_pair(a,b)));
  }

  sort(edges.begin(), edges.end());
  int counter = 0, cost = 0;
  UnionFind u(n);

  for(int i = 0; i < m; i++) {
    if(counter == (n-1)) break;
    int a = edges[i].second.first, b = edges[i].second.second, c = edges[i].first;
    if(!u.isSameSet(a, b)) {
      u.unionSet(a,b); cost += c; counter++;
    }
  }
  printf("%d\n", cost);
  return 0;
}