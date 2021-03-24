#g++ trace_gen.cpp -o trace_gen
#./trace_gen
g++ code.cpp
./a.out < inputr.txt > output.txt
./a.out < inputl.txt >> output.txt
./a.out < inputp.txt >> output.txt
#rm a.out trace_gen