// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

typedef double Real;

typedef struct {
  Real x,y;
} Point2D;

typedef struct {
  Real P0[2];
  Real P1[2];
} Segment2D;

typedef struct {
  Real x,y;
} Vector2D;

Vector2D sub(Real a[2], Real b[2]) {
  Vector2D v;
  v.x = a[0] - b[0];
  v.y = a[1] - b[1];
  return v;
};

Vector2D sub(Vector2D u, Vector2D v) {
  Vector2D w;
  w.x = u.x - v.x;
  w.y = u.y - v.y;
  return w;
}

Vector2D add(Vector2D u, Vector2D v) {
  Vector2D w;
  w.x = u.x + v.x;
  w.y = u.y + v.y;
  return w;
}

Vector2D add(Vector2D u, Real v[2]) {
  Vector2D w;
  w.x = u.x + v[0];
  w.y = u.y + v[1];
  return w;
}

Vector2D mult(Vector2D u, Real s) {
  Vector2D w;
  w.x = u.x * s;
  w.y = u.y * s;
  return w;
}

Real dot(Vector2D u, Vector2D v) {
  Real d = (u.x * v.x) + (u.y * v.y);
  return d;
};

Real perp(Vector2D u, Vector2D v) {
  Real p = (u.x * v.y) - (u.y * v.x);
  return p;
};

#define SMALL_NUM   0.00000001 // anything that avoids division overflow

// intersect2D_2Segments(): find the 2D intersection of 2 finite segments
//    Input:  two finite segments S1 and S2
//    Output: *I0 = intersect point (when it exists)
//            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
//    Return: 0=disjoint (no intersect)
//            1=intersect  in unique point I0
//            2=overlap  in segment from I0 to I1
int
intersect2D_2Segments( Segment S1, Segment S2, Real* I0, Real* I1 )
{
    Vector2D u = sub(S1.P1,S1.P0);
    Vector2D v = sub(S2.P1,S2.P0);
    Vector2D w = sub(S1.P0,S2.P0);
    Real     D = perp(u,v);

    // test if  they are parallel (includes either being a point)
    if (D < SMALL_NUM) {           // S1 and S2 are parallel
        if (perp(u,w) != 0 || perp(v,w) != 0)  {
            return 0;                    // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if they are degenerate  points
        Real du = dot(u,u);
        Real dv = dot(v,v);
        if (du==0 && dv==0) {            // both segments are points
            if (S1.P0 !=  S2.P0)         // they are distinct  points
                 return 0;
            set(*I0,S1.P0);                 // they are the same point
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if  (inSegment(S1.P0, S2) == 0)  // but is not in S2
                 return 0;
            set(*I0,S1.P0);                 // they are the same point
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(S2.P0, S1) == 0)  // but is not in S1
                 return 0;
            set(*I0,S2.P0);                 // they are the same point
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        Real t0, t1;                    // endpoints of S1 in eqn for S2
        Vector w2 = sub(S1.P1,S2.P0);
        if (v.x != 0) {
                 t0 = w.x / v.x;
                 t1 = w2.x / v.x;
        }
        else {
                 t0 = w.y / v.y;
                 t1 = w2.y / v.y;
        }
        if (t0 > t1) {                   // must have t0 smaller than t1
                 Real t=t0; t0=t1; t1=t;    // swap if not
        }
        if (t0 > 1 || t1 < 0) {
            return 0;      // NO overlap
        }
        t0 = t0<0? 0 : t0;               // clip to min 0
        t1 = t1>1? 1 : t1;               // clip to max 1
        if (t0 == t1) {                  // intersect is a point
            *I0 = add(S2.P0,mult(t0,v));
            return 1;
        }

        // they overlap in a valid subsegment
        *I0 = S2.P0 + t0 * v;
        *I1 = S2.P0 + t1 * v;
        return 2;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    Real sI = perp(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return 0;

    // get the intersect parameter for S2
    float tI = perp(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return 0;

    *I0 = S1.P0 + sI * u;                // compute S1 intersect point
    return 1;
}
//===================================================================
