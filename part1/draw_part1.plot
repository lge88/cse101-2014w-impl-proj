set terminal postscript eps
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Average Number of Connected Components"
set output "results/d1a1_n_100_k_300.eps"
plot "results/n_100_k_300.txt" using 3:4

set terminal postscript eps
set title "n = 100, k = 300"
set xlabel "p - Edge possibility"
set ylabel "Standard Deviation of Number of Connected Components"
set output "results/d1a2_n_100_k_300.eps"
plot "results/n_100_k_300.txt" using 3:5

set terminal postscript eps
set xlabel "p - Edge possibility"
set ylabel "Average Cost of MST"
set output "results/d1b_n_100_k_300.eps"
plot "results/n_100_k_300.txt" using 3:6

set terminal postscript eps
set xlabel "p - Edge possibility"
set ylabel "Average Diameter of MST"
set output "results/d1c_n_100_k_300.eps"
plot "results/n_100_k_300.txt" using 3:7
