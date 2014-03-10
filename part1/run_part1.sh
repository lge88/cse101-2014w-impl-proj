#! /bin/sh
mkdir -p results
for i in 500; do
    ./part1 $i 300 | tee results/n_${i}_k_300.txt
done
