// Bartosz Bednarczyk
// 273 479
// KLO

// BARDZO BRZYDKI KOD, NIE POLECAM CZYTAC

#include <bits/stdc++.h>
//#include "header.h"
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
typedef long long LL;
typedef vector<LL> VI;
typedef pair<LL,LL> pii;
typedef pair<pii, LL> triple;

// Solution :

class MaxTree
{
	private: vector<LL> w, prev; LL M;	// M = 2^k. Przedział [0...M-1]
	public:

			MaxTree(LL m) { M = m; w.assign(2*M+5, 0); prev.assign(2*M+5, -1); }

			void insert(LL x, LL val, LL id)
			{
				LL v = M + x;  w[v] = val; prev[v] = id;
				while(v != 1) {
					v /= 2;
					if(w[2*v] >= w[2*v+1]) { w[v] = w[2*v]; prev[v] = prev[2*v]; }
					else  { w[v] = w[2*v+1]; prev[v] = prev[2*v+1]; }
				}
			}

			pii query(LL a, LL b)
			{
				LL va = M+a, vb = M+b, wynik = w[va], id = prev[va];
				if(va != vb) {
					if(w[vb] > wynik) id = prev[vb];
					wynik = max(wynik, w[vb]);
				}
			
				while(va/2 != vb/2)
				{
					if(va % 2 == 0) {
						if(w[va+1] > wynik) id = prev[va+1];
						wynik = max(wynik, w[va+1]); // Prawa bombka na lewej ścieżce
					}
					if(vb % 2 == 1) {
						if(w[vb-1] > wynik) id = prev[vb-1];
						wynik = max(wynik, w[vb-1]); // Lewa bombka na prawej ścieżce
					}
					va /= 2; vb /= 2;
				}

				return {wynik, id};
			}
};

LL n, m, k, MAXCOL;
vector<triple> V;
unordered_map<LL,LL> Map, RevMap;

void mapInput() {
	REP(i, SIZE(V)) {
		if(Map[V[i].first.first] == 0) {
			MAXCOL++;
			Map[V[i].first.first] = MAXCOL;
			RevMap[MAXCOL] = V[i].first.first;
		}
	}
}

void readInput() {
	scanf("%lld %lld %lld", &m, &n, &k);
	V.resize(k, {{0,0}, 0});

	REP(i, k) {
		LL x, y, z; scanf("%lld %lld %lld", &x, &y, &z);
		V[i].first = {x,y}; V[i].second = z;
	}

	sort(ALL(V));
	mapInput();

	REP(i, k) { V[i].first = {V[i].first.second, V[i].first.first};}
	sort(ALL(V));
	REP(i, k) { V[i].first = {V[i].first.second, V[i].first.first};}
}

LL maxTwoPow(LL x)
{
	LL res = 1;
	while(res <<= 1) {
		if(res > x) break;
	}
	return res;
}

int main()
{
	readInput();
	MaxTree Tree(maxTwoPow(MAXCOL));

	vector<pii> ans(k, {-1, -1});

	REP(i, SIZE(V)) {
		LL posX = Map[V[i].first.first]; 
		pii prev_max = Tree.query(1, posX);
		LL current_max = V[i].second + prev_max.first;
		ans[i] = {current_max, prev_max.second};
		Tree.insert(posX, current_max, i);
	}

	pii odp = Tree.query(1, MAXCOL);
	LL value = odp.first;
	LL prev = odp.second;

	vector<pii> odppkt;

	while(prev != -1) {
		odppkt.push_back(V[prev].first);
		prev = ans[prev].second;
	}

	printf("%lld\n%lld\n", value, SIZE(odppkt));

	for(int i = SIZE(odppkt)-1; i >= 0; i--) {
		printf("%lld %lld\n", odppkt[i].first, odppkt[i].second);
	}

	return 0;
}