# CS2610 Lab 2

**Name : Vedant Saboo**
**Roll Number : CS19B074**
**Submission Deadline : 11:55 PM 2/25/2021**


## The problem statement

Write an assembly language program to encrypt digits as shown below:
Input digit     0 1 2 3 4 5 6 7 8 9
Encrypted digit 5 6 7 8 9 0 1 2 3 4
Your program should accept a string consisting of digit and non-digit characters. The encrypted string should be displayed in which only the digits are affected. Then the user should
be queried whether he or she wants to terminate the program. If the response is either y or Y
you should terminate the program; otherwise, you should request another input string from the
keyboard. You can assume that the input will not exceed 20 characters.

#### Sample Input

C5o2A3L4a1B

#### Constraints

string can be of maximum size 20

#### Sample Output

C0o7A8L9a6B

# HOW TO USE THE PROGRAM

Give the inputs one by one in the **STDIN**

Output will be displayed on the **STDOUT**

**CS19B074.o:** An object file that will be generated in the process
**CS19B074:** A binary file that will be generated during the process

#### How to run the code

Open Linux command shell

Run the following command in the same folder :

~$ ./commands.txt

If the binary file **CS19B074** is already present, you can simply run this command instead :

~$ ./CS19B074

#### Example

~$ ./commands.txt
Enter the string to be encrypted here :
C5o2A3L4a1B
Your encrypted string is:
C0o7A8L9a6B

Do you want to continue encrypting a new string? (Y/n)
Y
Enter the string to be encrypted here :
C5o2A3L4a1B
Your encrypted string is:
C0o7A8L9a6B

Do you want to continue encrypting a new string? (Y/n)
n
~$