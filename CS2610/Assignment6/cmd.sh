#g++ trace_gen.cpp -o trace_gen
#./trace_gen
g++ code.cpp Cache.cpp CacheLRU.cpp CacheLRUP.cpp -g
./a.out < inputr.txt > output.txt
./a.out < inputl.txt >> output.txt
./a.out < inputp.txt >> output.txt
rm a.out 
#rm trace_gen