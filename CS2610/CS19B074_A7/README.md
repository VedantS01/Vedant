# CS2610 Lab 3

**Name : Vedant Saboo**
**Roll Number : CS19B074**
**Submission Deadline : 11:55 PM 3/4/2021**


## The problem statement

In a Fibonacci sequence, a number is obtained by adding the preceding two numbers in the
sequence,

F(n) = F(n − 1) + F(n − 2)              ... (1)
F(0) = 0                                ... (2)
F(1) = 1                                ... (3)

Your task is to write a program which outputs the Nth fibonacci number when given N as the
input. You have to implement both the recursive and iterative versions of the problem. Observe
the time taken to compute the output for both the versions and give your insights on the reasons
behind the time difference. You can assume that the output fits in a 32-bit register i.e no input
will be given which results in a overflow of a 32-bit register. You can use a separate text file to
record your observations and insights.

# Sample program execution

~$ ./commands.txt
Enter a positive number greater than 1 : 7
Clock cycles taken in iterative process = 0102
By iterative process, the fibonacci number is : 13
Clock cycles taken in recursive process = 0748
By recursive process, the fibonacci number is : 13

# Some observations 

n = 7 fib = 13 
    clock cycles for iterative fibonacci = 102
    clock cycles for recursive fibonacci = 748

n = 15 fib = 610 
    clock cycles for iterative fibonacci = 160
    clock cycles for recursive fibonacci = 31548

n = 20 fib = 6765 
    clock cycles for iterative fibonacci = 134
    clock cycles for recursive fibonacci = 209158

n = 30 fib = 832040 
    clock cycles for iterative fibonacci = 186
    clock cycles for recursive fibonacci = 25620500

### Inference drawn : 

1. Iterative fibonacci execution time varies linearly with n and recursive fibonacci execution time varies exponentially with n

2. The clock cycles are not exactly the same for every execution, though the number is nearly in some range. This is because of occasional cache misses.

3. Recursive function requires a lot of stack space. In one observation with n = 100, stack space was exhausted, resulting in a segmentation fault. Iterative version has no space problem.

Overall, iterative version is much simpler and cheaper than recursive in all ways

