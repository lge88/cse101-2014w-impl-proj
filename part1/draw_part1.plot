set terminal jpeg
set title "n = 20, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set output "results/d1a1_n_20_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_20_k_300.txt" using 3:4 with linespoints ls 1 




set terminal jpeg
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set output "results/d1a1_n_100_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_100_k_300.txt" using 3:4  with linespoints ls 1

set terminal jpeg
set title "n = 500, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set output "results/d1a1_n_500_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_500_k_300.txt" using 3:4  with linespoints ls 1

set terminal jpeg
set title "n = 1000, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set output "results/d1a1_n_1000_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_1000_k_300.txt" using 3:4  with linespoints ls 1

set terminal jpeg
set title "n = 20, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
set output "results/d1a2_n_20_k_300.jpg"
plot "results/n_20_k_300.txt" using 3:5  with linespoints ls 1

set terminal jpeg
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
set output "results/d1a2_n_100_k_300.jpg"
plot "results/n_100_k_300.txt" using 3:5  with linespoints ls 1

set terminal jpeg
set title "n = 500, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
set output "results/d1a2_n_500_k_300.jpg"
plot "results/n_500_k_300.txt" using 3:5  with linespoints ls 1

set terminal jpeg
set title "n = 1000, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
set output "results/d1a2_n_1000_k_300.jpg"
plot "results/n_1000_k_300.txt" using 3:5  with linespoints ls 1


set terminal jpeg
set title "n = 20, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set output "results/d1b_n_20_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_20_k_300.txt" using 3:6  with linespoints ls 1

set terminal jpeg
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set output "results/d1b_n_100_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_100_k_300.txt" using 3:6  with linespoints ls 1

set terminal jpeg
set title "n = 500, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set output "results/d1b_n_500_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_500_k_300.txt" using 3:6  with linespoints ls 1


set terminal jpeg
set title "n = 1000, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set output "results/d1b_n_1000_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_1000_k_300.txt" using 3:6  with linespoints ls 1

set terminal jpeg
set title "n = 20, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set output "results/d1c_n_20_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_20_k_300.txt" using 3:7  with linespoints ls 1

set terminal jpeg
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set output "results/d1c_n_100_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_100_k_300.txt" using 3:7  with linespoints ls 1

set terminal jpeg
set title "n = 500, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set output "results/d1c_n_500_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_500_k_300.txt" using 3:7  with linespoints ls 1

set terminal jpeg
set title "n = 1000, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set output "results/d1c_n_1000_k_300.jpg"
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5   
plot "results/n_1000_k_300.txt" using 3:7  with linespoints ls 1
