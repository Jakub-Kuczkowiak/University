
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

vector<int> With, Without;
vector< vector<int> > adj;

void fun(int v) {
  if(With[v] != -1) return;

  if(adj[v].size() == 0) {
    With[v] = 1; Without[v] = 0; return;
  }

  for(int i = 0; i < adj[v].size(); i++) {
    fun(adj[v][i]);
  }

  int ansWith = 1;
  int ansWithout = 0;

  for(int i = 0; i < adj[v].size(); i++) {
    int u = adj[v][i];
    ansWith += Without[u];
    ansWithout += max(Without[u], With[u]); 
  }

  With[v] = ansWith; Without[v] = ansWithout;
}

int main()
{
  int n; scanf("%d", &n);
  With.resize(n, -1); Without.resize(n, -1); adj.resize(n);
  
  for(int i = 1; i < n; i++) {
    int x; scanf("%d", &x); adj[x].push_back(i);
  }

  fun(0);
  printf("%d\n", max(With[0], Without[0]));
  return 0;
}

