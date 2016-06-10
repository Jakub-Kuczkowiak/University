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
  vector<pii> edges, original_edges;
  
  for(int i = 0; i < m; i++) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c); a--; b--;
    edges.push_back(make_pair(c, i));
    original_edges.push_back(make_pair(a,b));
  }

  sort(edges.begin(), edges.end());
  int counter = 0, cost = 0;
  UnionFind u(n);

  for(int i = 0; i < m; i++) {
    if(counter == (n-1)) break;
    int edge_num = edges[i].second, weight = edges[i].first;
    int a = original_edges[edge_num].first, b = original_edges[edge_num].second;
    if(!u.isSameSet(a, b)) {
      u.unionSet(a,b); cost += weight; counter++;
      printf("%d\n", edge_num+1);
    }
  }
  return 0;
}