#include "segSegIsect.hpp"
#include <cstdio>
#include <cassert>
#include <Kokkos_Core.hpp>

FILE* outfile;
void draw(Segment2D u, Segment2D v, int ret) {
  fprintf(outfile,"%.3f %.3f %.3f %.3f\n",
      u.P0[0], u.P0[1], u.P1[0], u.P1[1]);
  fprintf(outfile,"%.3f %.3f %.3f %.3f\n\n\n",
      v.P0[0], v.P0[1], v.P1[0], v.P1[1]);
}

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
  *u = segment(0,1,0,1);
  *v = segment(0,0,0,0);
  *res = 0;
}

void f9(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(1,1,2,2);
  *v = segment(0,0,0,0);
  *res = 0;
}

void f10(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,0,0,0);
  *v = segment(1,1,2,2);
  *res = 0;
}

void f11(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(2,6,2,6);
  *v = segment(2,-1,2,5);
  *res = 0;
}

void t0(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(2,4,2,4);
  *v = segment(2,-1,2,5);
  *res = 1;
  pt->x = 2; pt->y = 4;
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

void t6(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,0,0,0);
  *v = segment(0,0,0,0);
  *res = 1;
  pt->x = 0; pt->y = 0;
}

void t7(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,0,1,1);
  *v = segment(.5,.5,.5,.5);
  *res = 1;
  pt->x = .5; pt->y = .5;
}

void t8(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(.5,.5,.5,.5);
  *v = segment(0,0,1,1);
  *res = 1;
  pt->x = .5; pt->y = .5;
}

void t9(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,1,0,2);
  *v = segment(0,0,0,4);
  *res = 2;
}

void t10(Segment2D* u, Segment2D* v, int* res, Point2D* pt) {
  *u = segment(0,-4,0,4);
  *v = segment(-4,0,4,0);
  *res = 1;
  pt->x = 0; pt->y = 0;
}

void test(Segment2D u, Segment2D v, int exp, Point2D pt) {
  Point2D a,b;
  int ret = intersect2D_2Segments(u,v,&a,&b);
  assert(ret == exp);
  if( ret == 1 )
    assert(a.x == pt.x && a.y == pt.y);
  draw(u,v,ret);
}

typedef Kokkos::View<Real*, Kokkos::HostSpace> Reals_h;
typedef Kokkos::View<Real*> Reals_d;
typedef Kokkos::View<int*, Kokkos::HostSpace> Ints_h;
typedef Kokkos::View<int*> Ints_d;

typedef struct {
  Reals_h x1;
  Reals_h x2;
  Reals_h y1;
  Reals_h y2;
  Reals_h xpt;
  Reals_h ypt;
  Ints_h res;
} TestViews;

int addTest(Segment2D u, Segment2D v, Point2D pt, int r,
    int testIdx, TestViews& tv) {
  tv.x1(testIdx) = u.P0[0];
  tv.y1(testIdx) = u.P0[1];
  tv.x2(testIdx) = u.P1[0];
  tv.y2(testIdx) = u.P1[1];
  tv.x1(testIdx+1) = v.P0[0];
  tv.y1(testIdx+1) = v.P0[1];
  tv.x2(testIdx+1) = v.P1[0];
  tv.y2(testIdx+1) = v.P1[1];
  tv.res(testIdx) = r;
  if( r == 1 ) {
    tv.xpt(testIdx) = pt.x;
    tv.ypt(testIdx) = pt.y;
  }
  return ++testIdx;
}

void runTests(TestViews& tv, int numTests) {
  auto x1 = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.x1);
  auto x2 = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.x2);
  auto y1 = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.y1);
  auto y2 = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.y2);
  auto xpt = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.xpt);
  auto ypt = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.ypt);
  auto res = Kokkos::create_mirror_view_and_copy(Kokkos::CudaSpace(), tv.res);
  Kokkos::parallel_for("kktest", numTests, KOKKOS_LAMBDA(const int i) {
    Segment2D u,v;
    u.P0[0] = x1(i);
    u.P0[1] = y1(i);
    u.P1[0] = x2(i);
    u.P1[1] = y2(i);
    v.P0[0] = x1(i+1);
    v.P0[1] = y1(i+1);
    v.P1[0] = x2(i+1);
    v.P1[1] = y2(i+1);
    Point2D pt;
    pt.x = xpt(i);
    pt.y = ypt(i);
    const int exp = res(i);
    Point2D a,b;
    int ret = intersect2D_2Segments(u,v,&a,&b);
    if(ret != exp)
      printf("test %d failed\n", i);
    assert(ret == exp);
    if( ret == 1 )
      assert(a.x == pt.x && a.y == pt.y);
  });
}

void kkTests() {
  auto numTests = 22;
  TestViews tv;
  tv.x1 = Reals_h("x1", numTests*2);
  tv.x2 = Reals_h("x2", numTests*2);
  tv.y1 = Reals_h("y1", numTests*2);
  tv.y2 = Reals_h("y2", numTests*2);
  tv.xpt = Reals_h("xpt", numTests);
  tv.ypt = Reals_h("ypt", numTests);
  tv.res = Ints_h("res", numTests);
  Segment2D u, v;
  Point2D pt;
  int res;
  int testIdx = 0;
  f1(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f2(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f3(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f4(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f5(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f6(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f7(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f8(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f9(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f10(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  f11(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);

  t0(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t1(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t2(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t3(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t4(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t5(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t6(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t7(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t8(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t9(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);
  t10(&u, &v, &res, &pt);
  testIdx = addTest(u,v,pt,res,testIdx,tv);

  assert(testIdx == numTests);
  runTests(tv, numTests);
}

int main(int argc, char** argv) {
  Kokkos::initialize( argc, argv );

  kkTests();

  outfile = fopen("points.gp","w");
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
  f9(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f10(&u, &v, &res, &pt);
  test(u, v, res, pt);
  f11(&u, &v, &res, &pt);
  test(u, v, res, pt);

  t0(&u, &v, &res, &pt);
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
  t6(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t7(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t8(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t9(&u, &v, &res, &pt);
  test(u, v, res, pt);
  t10(&u, &v, &res, &pt);
  test(u, v, res, pt);
  fclose(outfile);
  Kokkos::finalize();
  return 0;
}
