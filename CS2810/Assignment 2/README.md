# The problem statement

### Create a class Matrix to represent a (n x m) Matrix A, in which each row is sorted in ascending order. Implement the following methods in the class:

**binarySearch(x, k):** Search for element x in the kth row of the matrix using binary search. It should return the largest index j such that A[k][j] <= x. If no such index can be found, the method should return -1. (0 <= k <= n-1 , 0 <= j <= m-1)  

**matrixSearch(x):** Search for element x in the entire matrix. Return (i, j) such that A[k][j] == x. If the element is not present, return (-1,-1). If there are multiple elements x in the matrix, return the element which appears first in row major order of the matrix.

#### Note: Using STL library functions is not allowed. Also n*m will always be an odd number.

### Using the Matrix class you created previously as base class, create a derived class MatrixMedian. MatrixMedian class inherits the binarySearch() method from the parent class.

Implement the following method in the MatrixMedian class:

**upperBound(x, k):** This method should use the inherited binarySearch() method to find the smallest index i such that A[k][j] > x (smallest j such that the jth element in kth row is greater than x). If no such index is found, return -1.

**findMedian():** Find and return the overall median of the elements of the Matrix. The expected time complexity for findMedian() function is O(n * log m) and expected space complexity is O(1).

### Input Format

First line of the input contains two space-separated integers n and m denoting the number of rows and the number of columns respectively of the input matrix A.

Following n lines contain m space-separated integers each, describing the rows of the matrix.

Next line contains Q, the number of queries to be performed on the matrix.

Each of the next Q lines represents a single query of the format:

BS x k : Call binarySearch(x, k)

MS x : Call matrixSearch(x)

Median : Call findMedian()

### Constraints

-2^31 <= A[i][j] <= 2^31 - 1

1 <= n,m <= 10^5

1 <= n*m <= 10^6

-2^31 <= x <= 2^31 - 1

0 <= k <= n - 1

1 <= Q <= 100

#### Output Format

Print output of each query in a new line.

BS x k : Print Output of binarySearch(x,k) in a new line.

MS x : Print i j (space separated) on a new line if element is found, else print -1 -1

Median : Print median element on a new line

For more clarity, refer the sample output.

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