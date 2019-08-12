#include "segSegIsect.hpp"
#include <cstdio>

int main() {
  Segment2D u;
  u.P0[0] = 0; u.P0[1] = 0; 
  u.P1[0] = 1; u.P1[1] = 0; 
  Segment2D v;
  v.P0[0] = .5; v.P0[1] = -1; 
  v.P1[0] = .5; v.P1[1] = 1; 
  Point2D a;
  Point2D b;
  int ret = intersect2D_2Segments(u,v,&a,&b);
  printf("ret %d I0 %.3f %.3f\n", ret, a.x, a.y);
  return 0;
}
