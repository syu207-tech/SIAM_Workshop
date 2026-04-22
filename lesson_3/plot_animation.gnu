set terminal wxt size 1200,800
set title "Pseudo Cell Movement in 3D"
set xlabel "x"
set ylabel "y"
set zlabel "z"

set xrange [-2:12]
set yrange [-2:2]
set zrange [-1:1]

set size ratio -1
set view 60, 30
set grid
set border 4095
set ticslevel 0
unset key

Nsteps = 1000

do for [i=0:Nsteps-1] {
    splot \
        'membrane.dat' index i using 1:2:3 with points pt 7 ps 1.0 lc rgb "blue", \
        'interior.dat' index i using 1:2:3 with points pt 7 ps 0.6 lc rgb "red"

    pause 0.02
}