#include "segSegIsect.hpp"
#include <cstdio>
#include <cassert>

int main() {
  Real pts[4] = {0,0,1,0};
  Segment2D u = segment(pts);
  Real ptsv[4] = {.5,-1,.5,1};
  Segment2D v = segment(ptsv);
  Point2D a,b;
  int ret = intersect2D_2Segments(u,v,&a,&b);
  assert(ret == 1);
  assert(a.x == .5 && a.y == 0);
  printf("ret %d I0 %.3f %.3f\n", ret, a.x, a.y);
  return 0;
}
