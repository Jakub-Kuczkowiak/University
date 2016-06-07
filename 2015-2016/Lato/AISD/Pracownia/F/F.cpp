/*
	Bartosz Jan Bednarczyk - "wiedzMAC"
	University Of Wroclaw
 */

#include <bits/stdc++.h>
//#include "header.h"
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define FORD(x, b, e) for(int x = b; x >= (e); x--)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second

inline string IntToStr(int x) { ostringstream ss; ss << x; return ss.str(); }
inline int StrToInt(string x) { int i; istringstream iss(x); iss >> i; return i; }

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;

// Solution :

int N;
vector<int> li;

inline int calculate_kj(int lj, int m) {
	return (lj % 9999991) % m;
}

inline int calculate_pos(int akj, int lj, long long ykj) {
	return (( (long long) akj * lj) % 9999991) % ykj;
}

inline bool check_ai(int a, vector<int> values, long long y) {
	vector<int> vec(y, 0);
	REP(i, SIZE(values)) {
		vec[calculate_pos(a, values[i], y)]++;
	}

	REP(i, y) {
		if(vec[i] > 1) return false;
	}

	return true;
}

int main() {
	scanf("%d", &N); li.resize(N);
	REP(i, N) scanf("%d", &li[i]);

	printf("%d\n", N);

	vector< vector<int> > ki(N);

	REP(i, N) {
		ki[calculate_kj(li[i], N)].push_back(li[i]);
	}

	REP(i, N) {
		printf("%lu ", ki[i].size() * ki[i].size() + 1);
	}

	printf("\n%d\n", 1);

	REP(i, N) {
		if(ki[i].size() == 0) printf("1 ");
		else
		{
			while(1) {
				int los = rand() % (5*10000000);
				if(check_ai(los, ki[i],  ki[i].size() * ki[i].size() + 1)) {
					printf("%d ", los);
					break;
				}
			}
		}
	}

	printf("\n");
	return 0;
}