# The problem statement

#### Create a class matrix whose purpose is to store a square matrix and deal with matrix operations.
The class matrix should implement the following operations:

**(SPSUM) Special Sum '+' :** This is defined on one matrix. Add row index(i) and column index(j) of each element of the matrix. If this sum is odd, swap the element A[i][j] with A[j][i].Now, print the sum of each row of this new matrix. Perform this operation on the 1st matrix provided as input.

**(MOD) Mod Multiplication '&':** This defined on one matrix. If row index(i) is divisible by 3, find the max element of that row. If i gives 1 on division by 3, then find the minimum element of that row. Otherwise, find the floor of average of that row. Print the product of these elements. Perform this operation on the 1st matrix provided as input.

**(MRS) Matrix Right Shift '>>' :** This is defined on 2 matrices of same size. You will be given 'k' as input. Perform right shift operation on both the matrices(k times). Print the sum of these shifted matrices.(eg In a 3X3 matrix, if k=2 , then element at position [0][0] moves to position [0][2] followed by all other elements such that last element at [2][2] moves to position [0][1])

**(MADD) special Matrix Addition '+' :** This is also defined on 2 matrices of same size. Given 'x', If x = 1, then perform a transformation on the elements of 1st matrix such that A[i][j] gets swapped with A[j][i]. Then, add it to the 2nd matrix B and print the resulting matrix. If x = 2, then perform the transformation on the 2nd matrix such that B[i][j] gets swapped with B[j][i]. Then, add it to the 1st matrix A and print the resulting matrix.

Write a main function which reads a value Q, matrix dimension n, a n*n matrix A then accepts Q operations as given by the input. The output should be the outcome of each of the operations.

Note: All the operations needed to be implemented are NOT in-place operations. The original matrices should not be altered after each operation. We have designed test cases in this way. So please make a note of this point.

#### Input Format

First line would be Q, Number of queries.

Second line will be n, Number of rows/columns of the square matrix.

Next 2n lines have row elements of the two matrices(space separated). [First n lines are rows of first matrix, next n lines are rows of second matrix]

Next Q lines, query operation operations to be performed [single query in each new line].

#### Constraints

1<=Q<=8

1<=n<=50

1<=x<=2

0<=k<=50

-1000 <=M[i][j]< 1000

#### Output Format

SPSUM : n numbers which comma-separated, all in the same line.

MOD : An integer in a single line.

MRS & MADD: Matrix should be printed in the following n lines.

# HOW TO USE THE PROGRAM

**input.txt:** The text file where input can be placed

**output.txt:** The text file where output will be printed

**solution:** A binary file that will be generated during the process

#### How to run the program

Place your input in input.txt file according to the format shown above

Open Linux command shell

Run the following command in the same folder :

~$ ./cmd.sh

Look for your output in the file output.txt