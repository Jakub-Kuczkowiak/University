
#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000
typedef priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > MyHeap;
int n, m, k, *counter, *MyPairFirst[100005];
short *MyPairSecond[100005];

void readInput() {
  int *x = new int[m];
  int *y = new int[m];
  short *z = new short[m];
  int *mycounter = (int *) calloc(n, sizeof(int));
  counter = (int *) calloc(n, sizeof(int));

  for (int i = 0; i < m; i++) {
    int _x, _y, _z;
    scanf("%d %d %u", &_x, &_y, &_z);
    _x--; _y--; x[i] = _x; y[i] = _y; z[i] = _z;
    counter[_x]++; counter[_y]++; mycounter[_x]++; mycounter[_y]++;
  }

  for (int i = 0; i < n; i++) {
    MyPairFirst[i] = new int[counter[i]];
    MyPairSecond[i] = new short[counter[i]];
  }

  for (int i = 0; i < m; i++) {
    mycounter[x[i]]--; mycounter[y[i]]--;
    MyPairFirst[x[i]][mycounter[x[i]]] = y[i];
    MyPairFirst[y[i]][mycounter[y[i]]] = x[i];
    MyPairSecond[y[i]][mycounter[y[i]]] = MyPairSecond[x[i]][mycounter[x[i]]] = z[i];
  }

  delete[] x; delete[] y; delete[] z; free(mycounter);
}

void dijkstra() { // wzorowalem sie na ksiazce Competitive programming 3
  int *d = new int[n];
  fill_n(d, n, INF); d[0] = 0;
  MyHeap heap;
  heap.push({0, 0});

  while (!heap.empty()) {
    pair<int, int> top = heap.top(); heap.pop();
    if (top.first > d[top.second]) continue;
    for (int j = 0; j < counter[top.second]; j++) {
      if (d[top.second] + MyPairSecond[top.second][j] < d[MyPairFirst[top.second][j]]) {
        heap.push({(d[MyPairFirst[top.second][j]] = d[top.second] + MyPairSecond[top.second][j]),
                   MyPairFirst[top.second][j]});
      }
    }
  }

  unsigned long long wynik = 0;

  for (int i = 0; i < k; i++) {
    int x; scanf("%d", &x); x--;
    if (d[x] == INF) {
      printf("NIE\n");
      return;
    }
    else wynik += (d[x] << 1);
  }

  printf("%llu\n", wynik);
}

int main() { scanf("%d %d %d", &n, &m, &k); readInput(); dijkstra(); return 0; }

