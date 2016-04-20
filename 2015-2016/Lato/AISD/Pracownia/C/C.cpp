// Bartosz Bednarczyk
// 273 479
// KLO

#include <bits/stdc++.h>
using namespace std;

#define FOR(x, b, e) for(int x = b; x <= (e); x++)
#define FORD(x, b, e) for(int x = b; x >= (e); x--)
#define REP(x, n) for(int x = 0; x < (n); x++)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define PB push_back
#define ST first
#define ND second

typedef vector<int> VI;
typedef long long LL;
typedef pair<int,int> pii;

const double EPS = 10e-9;
const int INF = 1000000001;

// Solution :

bool comp(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
}

inline double distance(pii &p, pii &q) {
  double dist = ((LL)p.ST - (LL)q.ST) * ((LL)p.ST - (LL)q.ST) + ((LL)p.ND - (LL)q.ND) * ((LL)p.ND - (LL)q.ND);
  return sqrt(dist);
}

inline double getPerimeter(pii &p, pii &q, pii &r) {
  return distance(p, q) + distance(q, r) + distance(r, p);
}

inline double getPerimeter(tuple<pii, pii, pii> &triangle) {
  return getPerimeter(get<0>(triangle), get<1>(triangle), get<2>(triangle));
}

// a == b
inline bool _equal(double a, double b) {
  return ( (-EPS) <= fabs(a-b) && fabs(a-b) <= EPS);
}

// a < b
inline bool _smaller(double a, double b) {
  return (a-b) < ( (double) 0.0 );
}

// a > b
inline bool _greater(double a, double b) {
  return (a-b) > ( (double) 0.0 );
}

// a >= b
inline bool _greaterOrEqual(double a, double b) {
  return (_greater(a,b) || _equal(a,b));
}

// a <= b
inline bool _smallerOrEqual(double a, double b) {
  return (_smaller(a,b) || _equal(a,b));
}

tuple<pii,pii,pii> Null() {
  pii infPoint = {INF, INF};
  tuple<pii,pii,pii> t = make_tuple(infPoint,infPoint,infPoint);
  return t;
}

bool isNull(tuple<pii,pii,pii> &t) {
  return (get<0>(t).ST == INF && get<0>(t).ND == INF) &&
  (get<1>(t).ST == INF && get<1>(t).ND == INF) &&
  (get<2>(t).ST == INF && get<2>(t).ND == INF);
}


tuple<pii,pii,pii> brute(vector<pii> &points) {
  tuple<pii, pii, pii> answer = make_tuple(points[0], points[1], points[2]);
  double perimeter = getPerimeter(points[0], points[1], points[2]);

  FOR(i, 0, SIZE(points)-1) {
    FOR(j, i+1, SIZE(points)-1) {
      FOR(k, j+1, SIZE(points)-1) {
        double currentPerimeter = getPerimeter(points[i], points[j], points[k]);
        if(_smaller(currentPerimeter, perimeter)) {
          perimeter = currentPerimeter;
          answer = make_tuple(points[i], points[j], points[k]);
        }
      }
    }
  }

  return answer;
}

tuple<pii, pii, pii> merge(vector<pii> &points, double minPerimeter) {
  const size_t half = SIZE(points) / 2;
  double halfPosX = points[half].ST;
  double minn = halfPosX - minPerimeter / 2.0, maxx = halfPosX + minPerimeter / 2.0;
  vector<pii> closeToMiddle;

  FORD(i, half, 0) {
    double posX = points[i].ST;
    if( _smallerOrEqual(posX, maxx) && _greaterOrEqual(posX,minn) ) closeToMiddle.PB(points[i]);
    //else break; 
  }

  FOR(i, half+1, SIZE(points)-1) {
    double posX = points[i].ST;
    if(_smallerOrEqual(posX, maxx) && _greaterOrEqual(posX,minn)) closeToMiddle.PB(points[i]);
    //else break; 
  }

  sort(ALL(closeToMiddle), comp);
  tuple<pii, pii, pii> ans = Null();
  double ans_perimeter = -1;


  REP(i, SIZE(closeToMiddle)) {
    vector<pii> temp;
    temp.PB(closeToMiddle[i]);

    FOR(j, i+1, SIZE(closeToMiddle)-1) {
      double a = closeToMiddle[i].ND;
      double b = closeToMiddle[j].ND;

      if( _smallerOrEqual( fabs(a-b), minPerimeter/2.0) ) {
        temp.PB(closeToMiddle[j]);
      }
    }

    if(SIZE(temp) > 2) {
      tuple<pii, pii, pii> t = brute(temp);
      double perimeter_t = getPerimeter(t);

      if(_equal(ans_perimeter, -1.0) ||  _smaller(perimeter_t, ans_perimeter)) {
        ans_perimeter = perimeter_t;
        ans = t;
      }
      else break;
    }
  }

  return ans;
}

tuple<pii, pii, pii> solve(vector<pii> &points) {
  if(SIZE(points) < 6) return brute(points);
  
  const size_t half = SIZE(points) / 2;
  vector<pii> L(points.begin(), points.begin() + half);
  vector<pii> R(points.begin() + half, points.end());

  tuple<pii, pii, pii> answerForL = solve(L);
  tuple<pii, pii, pii> answerForR = solve(R);

  double perimeterL = getPerimeter(answerForL), perimeterR = getPerimeter(answerForR);
  tuple<pii, pii, pii> answerForLine = merge(points, min(perimeterL, perimeterR));  

  if(isNull(answerForLine)) {
    double minPerimeter = min(perimeterL, perimeterR);
    if(_equal(perimeterL,minPerimeter)) return answerForL;
    else return answerForR;
  }
  else {
    double perimeterLine = getPerimeter(answerForLine);
    double minPerimeter = min(perimeterLine, min(perimeterL, perimeterR));

    if(_equal(perimeterL,minPerimeter)) return answerForL;
    else if(_equal(perimeterR,minPerimeter)) return answerForR;
    else return answerForLine;
  }
}

int main() {
  int n; scanf("%d", &n);
  vector<pii> points(n);

  REP(i, n) {
    int x, y; scanf("%d %d", &x, &y);
    points[i] = {x,y};
  }

  sort(ALL(points));
  tuple<pii, pii, pii> answer = solve(points);
  //printf("OBW = %lf\n", getPerimeter(get<0>(answer), get<1>(answer), get<2>(answer)));
  printf("%d %d\n", get<0>(answer).ST, get<0>(answer).ND);
  printf("%d %d\n", get<1>(answer).ST, get<1>(answer).ND);
  printf("%d %d\n", get<2>(answer).ST, get<2>(answer).ND);

  return 0;
}