gcc CS19B074_01.c -o test1 -O3
sudo perf stat -B -r 10 -e cpu-cycles,instructions,branch-instructions,cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses,dTLB-loads,dTLB-load-misses,LLC-loads,LLC-load-misses,duration_time,cpu-clock,task-clock ./test1 > outputf1.txt
gcc CS19B074_02.c -o test2 -O3
sudo perf stat -B -r 10 -e cpu-cycles,instructions,branch-instructions,cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses,dTLB-loads,dTLB-load-misses,LLC-loads,LLC-load-misses,duration_time,cpu-clock,task-clock ./test2 > outputf2.txt
