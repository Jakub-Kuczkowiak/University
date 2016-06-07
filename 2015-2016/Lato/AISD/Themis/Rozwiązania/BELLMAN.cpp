#include <cstdio>
using namespace std;
const int INF = 999999999;

int main() {
  int n, m, s;
  scanf("%d %d %d", &n, &m, &s);
  int *d = new int[n];
  int *u = new int[m];
  int *v = new int[m];
  int *w = new int[m];

  for(int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;

  for(int i = 0; i < m; i++) {
    scanf("%d %d %d", &u[i], &v[i], &w[i]); 
  }

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(d[v[j]] > d[u[j]] + w[j] && d[u[j]] != INF ) {
        d[v[j]] = d[u[j]] + w[j];
        if(i == (n-1)) { printf("NIE\n"); return 0; } 
      }
    }
  }

  for(int i = 0; i < n; i++) {
    if(d[i] < INF && i != s) printf("%d %d\n", i, d[i]);
  }

  delete[] d;
  delete[] u;
  delete[] v;
  delete[] w;
  return 0;
}
