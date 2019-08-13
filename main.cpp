#include "segSegIsect.hpp"
#include <cstdio>
#include <cassert>



void f1(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0, 0, 7, 7);
  *v = segment(3, 4, 4, 5);
  *res = 0;
}

void f2(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(-4, 4, -2, 1);
  *v = segment(-2, 3,  0, 0);
  *res = 0;
}

void f3(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0, 0, 0, 1);
  *v = segment(2, 2, 2, 3);
  *res = 0;
}

void f4(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(-1, -1, 2, 2);
  *v = segment(3, 3, 5, 5);
  *res = 0;
}

void f5(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,0,1,1);
  *v = segment(2,0,0.5,2);
  *res = 0;
}

void f6(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(1,1,4,1);
  *v = segment(2,2,3,2);
  *res = 0;
}

void f7(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,5,6,0);
  *v = segment(2,1,2,2);
  *res = 0;
}

void f8(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,-2,0,2);
  *v = segment(-2,0,2,0);
  *res = 0;
}

void t1(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(-4,0,4,0);
  *v = segment(0,-4,0,4);
  *res = 1;
  pt->x = 0; pt->y = 0;
}

void t2(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(5,5,0,0);
  *v = segment(1,1,8,2);
  *res = 1;
  pt->x = 1; pt->y = 1;
}

void t3(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(-1,0,0,0);
  *v = segment(-1,-1,-1,1);
  *res = 1;
  pt->x = -1; pt->y = 0;
}

void t4(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,2,2,2);
  *v = segment(2,0,2,4);
  *res = 1;
  pt->x = 2; pt->y = 2;
}

void t5(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,0,5,5);
  *v = segment(1,1,3,3);
  *res = 2;
}

void test(Segment2D u, Segment2D v, int exp, Point2D pt) {
  Point2D a,b;
  int ret = intersect2D_2Segments(u,v,&a,&b);
  assert(ret == exp);
  if( ret == 1 )
    assert(a.x == pt.x && a.y == pt.y);
}

int main() {
  Segment2D u, v;  
  int res;
  Point2D pt;
  f1(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f2(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f3(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f4(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f5(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f6(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f7(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f8(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t1(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t2(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t3(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t4(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t5(&u, &v, &res, &pt);
  test(u, v, res, pt);
  return 0;
}
