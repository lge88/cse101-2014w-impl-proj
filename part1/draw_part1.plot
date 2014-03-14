set style line 1 lc rgb 'red' lt 1 lw 2 pt 7 ps 0.5
set style line 2 lc rgb 'black' lt 1 lw 2 pt 7 ps 0.5
set style line 3 lc rgb 'cyan' lt 1 lw 2 pt 7 ps 0.5
set style line 4 lc rgb 'orange' lt 1 lw 4 pt 7 ps 0.5 


set terminal jpeg
set output "results/1A-1.jpg"
set title "1A-1"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set ytics 50
set xrange [0:1]
set yrange [0:1000]

plot 'results/n_1000_k_300.txt' using 3:4 with linespoints ls 4 title 'n = 1000',\
'results/n_500_k_300.txt' using 3:4 with linespoints ls 3 title 'n = 500',\
'results/n_100_k_300.txt' using 3:4 with linespoints ls 2 title 'n = 100',\
'results/n_20_k_300.txt' using 3:4 with linespoints ls 1 title 'n = 20'



set terminal jpeg
set output "results/1A-2.jpg"
set title "1A-2"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set ytics 0.5
set xrange [0:1]
set yrange [0:5]

plot 'results/n_1000_k_300.txt' using 3:5 with linespoints ls 4 title 'n = 1000',\
'results/n_500_k_300.txt' using 3:5 with linespoints ls 3 title 'n = 500',\
'results/n_100_k_300.txt' using 3:5 with linespoints ls 2 title 'n = 100',\
'results/n_20_k_300.txt' using 3:5 with linespoints ls 1 title 'n = 20'



set terminal jpeg
set output "results/1B-1.jpg"
set title "1B-1"
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set ytics 5
set xrange [0:1]
set yrange [0:65]

plot 'results/n_1000_k_300.txt' using 3:6 with linespoints ls 4 title 'n = 1000',\
'results/n_500_k_300.txt' using 3:6 with linespoints ls 3 title 'n = 500',\
'results/n_100_k_300.txt' using 3:6 with linespoints ls 2 title 'n = 100',\
'results/n_20_k_300.txt' using 3:6 with linespoints ls 1 title 'n = 20'


set terminal jpeg
set output "results/1C-1.jpg"
set title "1C-1"
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set ytics 10
set xrange [0:1]
set yrange [0:70]

plot 'results/n_1000_k_300.txt' using 3:7 with linespoints ls 4 title 'n = 1000',\
'results/n_500_k_300.txt' using 3:7 with linespoints ls 3 title 'n = 500',\
'results/n_100_k_300.txt' using 3:7 with linespoints ls 2 title 'n = 100',\
'results/n_20_k_300.txt' using 3:7 with linespoints ls 1 title 'n = 20'




