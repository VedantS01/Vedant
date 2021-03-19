# CS2610 Lab 4

**Name : Vedant Saboo**

**Roll Number : CS19B074**

**Submission Deadline : 11:55 PM 3/11/2021**


## The problem statement

Given a sequence of integers(32-bit) and a search element. You have to find whether the search
element is present in the sequence. Use the binary search algorithm to perform the search. You
can use either the recursive or iterative approach. Print ’1’ to the screen if the element is found,
else ’0’.

The input will be given in the following order, size of the sequence(N), the sequence and the
search element. You can assume that the input sequence is already sorted. After displaying the
search result, query the user whether he wants to terminate or not; if the response is y or Y,
terminate. Otherwise, request for another search element.

# Sample program execution

~$ ./commands.txt

Enter the size of the array : 10

Please enter 10 each on a next line.

-11

-7

2

3

5

6

9

14

17

22

Enter the element to be searched : 6

Result of the binary search is : 1

The element was found.

Do you want to terminate the program (Y/n)

n

Enter the element to be searched : 7

Result of the binary search is : 0

The element was not found.

Do you want to terminate the program (Y/n)

Y

~$

# Remarks

1. A correct input will give a reliable output.

2. This is a space efficient procedure, takes up only O(1) extra space. This is because it lacks the recursive calling.

