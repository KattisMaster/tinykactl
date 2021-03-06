/* KTH ACM Contest Template Library
 *
 * Geometry/Convex Hull/Line Hull Intersection
 *
 * Credit:
 *   By David Rydh
 */

#include "point.cpp"
#include "point_line_relations.cpp (for linedist)"

template <class V, class T>
struct line_hull_isct {
  typedef point<T> P;
  const V &p;
  int n;
  const P &p1, &p2;
  int &s1, &s2;
  line_hull_isct(const V &_p, int _n, const P &_p1, const P &_p2,
		 int &_s1, int &_s2)
    : p(_p), n(_n), p1(_p1), p2(_p2), s1(_s1), s2(_s2) { }
  
  // assumes 0 <= md <= i1d, i2d
  bool isct(int i1, int m, int i2, double md) {
    if (md <= 0) {
      s1 = findisct(i1, m) % n;
      s2 = findisct(i2, m) % n;
      return true;
    }
    if( i2-i1 <= 2 ) return false;
    int l = (i1 + m) / 2, r = (m + i2) / 2;
    double ld = linedist(p1, p2, p[l % n]);
    double rd = linedist(p1, p2, p[r % n]);
    if (ld <= md && ld <= rd) return isct(i1, l, m, ld);
    if (rd <= md && rd <= ld) return isct(m, r, i2, rd);
    else return isct(l, m, r, md);
  }
  int findisct(int pos, int neg) {
    int m = (pos + neg) / 2;
    if (m == pos) return pos;
    if (m == neg) return neg;
    double d = linedist(p1, p2, p[m % n]);
    if (d <= 0) return findisct(pos, m);
    else return findisct(m, neg);
  }
};

template <class V, class T>
bool line_hull_intersect(const V &p, int n,
			 const point<T> &p1, const point<T> &p2,
			 int &s1, int &s2) {
  double d = linedist(p1, p2, p[0]);
  return line_hull_isct<V, T>(p, n, d >= 0 ? p1 : p2, 
			      d >= 0 ? p2 : p1, s1, s2).
    isct(0, n, 2*n, fabs(d));
}
