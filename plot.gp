set terminal png size 1920,1920 enhanced font 'Verdana,16'
set output 'tests.png'

stats 'points.gp' u 1:2 nooutput
blocks = STATS_blocks
print blocks

set multiplot layout 5,5 rowsfirst
set key off
unset border
do for [v=0:blocks-1] {
  print v
  set title sprintf("t %d", v)
  plot 'points.gp' index v u 1:2:($3-$1):($4-$2) w vectors lw 3 nohead, \
       'points.gp' index v u 1:2 w points pointtype 5, \
       'points.gp' index v u 3:4 w points pointtype 5
}
