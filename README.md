# segSegIsect
2d segment segment intersection

# build

```
<your C++ compiler here> main.cpp
```

# run

```
./a.out
```

# check code coverage using GCC and GCOV

```
./cov.sh
```

# check for memory leaks and errors using Valgrind

```
./memcheck.sh
```

# test cases

![](tests.png | width=600)

This figure was generated by running `gnuplot plot.gp`.  The input to this
script is the `points.gp` file generated by running `./a.out`.

# credit

The segment-segment intersection code heavily borrows (as in 99% of it) from
here:
http://www.geomalgorithms.com/a05-_intersect-1.html#Line-Intersections

The test cases and the plots of them were inspired by:
https://martin-thoma.com/how-to-check-if-two-line-segments-intersect
https://github.com/MartinThoma/algorithms/tree/master/crossingLineCheck/Geometry/src
