/***************************************************************************************
 * Author: Luis Gonzalez
 * Date  : 9/24/2021
 * Class : CSCE 327 Linux Programming
 * Prof  : Aloia
 ***************************************************************************************
 * Program 1 - linked list implemenation in c -yuk
 * 
 ***************************************************************************************
*/
1. Program status (what works, what doesn't)

    1) int linked list
        - what works
            - initualizing the linked list
            - apending the list with init user input
            - insert at a location
            - remove at a location
            - convert to int *arr[]
            - printing the list
            - returning list size
            - checking if empty

        - what doesnt work 
            - scanf() doesnt work with digits 10 +
            - I havent had the change to test out all the test cases
            - when you insert it inserts a diff num ex insert 9 -> value changes to 57??

    2) char linked list
        - what works
            - initualizing the linked list
            - apending the list with init user input
            - insert at a location
            - remove at a location
            - convert to int *arr[]
            - printing the list
            - returning list size
            - checking if empty

        - what doesnt work
            - remove from location works, but didn't have the chance to error
                - check for expections

    3) float linked list
        - what works
            - initualizing the linked list
            - apending the list with init user input
            - insert at a location
            - remove at a location
            - convert to int *arr[]
            - printing the list
            - returning list size
            - checking if empty

        - what doesnt work
            - inserting to the right location works, but all floats are 0.00 when inserted
            - remove from location works, but didn't have the chance to error
                - check for expections

2. Do you have quality code? 
Note: See our coding guidelines, etc

    - decent coding guidlines
    - might need to do more comments on my funcs 


3. How to run your program

    - onces cloned, on UBUNTU run make all
    - then ./hello to run object program
    


4. Creative element

    - made a main menu and a sub menu for easy testing of linked list


5. Results 

    - Most of the data can be displayed on the terminal


6. Other notes

    - C is a tough language to get used to. I struggled a lot just to make the make file
    - Im very upset that I cannot figure out why my scanf will change the value
    - of an int if its >9 
    - the other issues i encountered are more easily fixable
    - for the float and chars i will need a to distingush their data type
    - in the remove_ at() and insert at () which i have an idea for but didnt have the time
    - inserting is the biggest bug. I cant figure out why values change after i insert it
    - i didnt know what to do with remove() remove at loc works just fine
    - wasnt sure what to do with that
