set style line 1 lc rgb 'red' lt 1 lw 2 pt 7 ps 0.5
set style line 2 lc rgb 'black' lt 1 lw 2 pt 7 ps 0.5
set style line 3 lc rgb 'cyan' lt 1 lw 2 pt 7 ps 0.5
set style line 4 lc rgb 'orange' lt 1 lw 2 pt 7 ps 0.5 
set style line 5 lc rgb 'yellow' lt 1 lw 2 pt 7 ps 0.5
set style line 6 lc rgb 'green' lt 1 lw 2 pt 7 ps 0.5
set style line 7 lc rgb 'violet' lt 1 lw 2 pt 7 ps 0.5
set style line 8 lc rgb 'blue' lt 1 lw 2 pt 7 ps 0.5 
set style line 9 lc rgb 'pink' lt 1 lw 2 pt 7 ps 0.5 



set terminal jpeg
set output "2A-1.jpg"
set title "2A-1"
set xlabel "n - Number of Points"
set ylabel "Number of Iterations"
set ytics 10
set xrange [0:3000]
set yrange [0:100]

plot 'part2A_js.txt' using 1:4 with linespoints ls 8 title 'Number of Iterations'




set terminal jpeg
set output "3A-1.jpg"
set title "3A-1"
set xlabel "n - Number of Points"
set ylabel "Average Number of Iterations"
set ytics 10
set xrange [0:3000]
set yrange [0:100]

plot 'part2_js0.1.txt' using 1:4 with linespoints ls 1 title 'r = 0.1',\
'part2_js0.2.txt' using 1:4 with linespoints ls 2 title 'r = 0.2',\
'part2_js0.3.txt' using 1:4 with linespoints ls 3 title 'r = 0.3',\
'part2_js0.4.txt' using 1:4 with linespoints ls 4 title 'r = 0.4',\
'part2_js0.5.txt' using 1:4 with linespoints ls 5 title 'r = 0.5',\
'part2_js0.6.txt' using 1:4 with linespoints ls 6 title 'r = 0.6',\
'part2_js0.7.txt' using 1:4 with linespoints ls 7 title 'r = 0.7',\
'part2_js0.8.txt' using 1:4 with linespoints ls 8 title 'r = 0.8',\
'part2_js0.9.txt' using 1:4 with linespoints ls 9 title 'r = 0.9'



set terminal jpeg
set output "3A-2.jpg"
set title "3A-2"
set xlabel "n - Number of Points"
set ylabel "Standard Deviation of Number of Iterations"
set ytics 0.2
set xrange [0:3000]
set yrange [0:2]

plot 'part2_js0.1.txt' using 1:5 with linespoints ls 1 title 'r = 0.1',\
'part2_js0.2.txt' using 1:5 with linespoints ls 2 title 'r = 0.2',\
'part2_js0.3.txt' using 1:5 with linespoints ls 3 title 'r = 0.3',\
'part2_js0.4.txt' using 1:5 with linespoints ls 4 title 'r = 0.4',\
'part2_js0.5.txt' using 1:5 with linespoints ls 5 title 'r = 0.5',\
'part2_js0.6.txt' using 1:5 with linespoints ls 6 title 'r = 0.6',\
'part2_js0.7.txt' using 1:5 with linespoints ls 7 title 'r = 0.7',\
'part2_js0.8.txt' using 1:5 with linespoints ls 8 title 'r = 0.8',\
'part2_js0.9.txt' using 1:5 with linespoints ls 9 title 'r = 0.9'






