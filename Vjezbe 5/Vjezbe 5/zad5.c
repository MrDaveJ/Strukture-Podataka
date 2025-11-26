#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define ALOC -1             //Allocation Error 
#define FOP -2              //File opening Error
#define NOOP -3             //Not enough operands
#define DIV -4              //Division with zero
#define UNC -5              //Unknown character

typedef struct stack* pos;

typedef struct stack {
    double x;
    pos next;
} stack;

int push(double el, pos head);          //Function that stores element to stack (LIFO)
int pop(pos head, char operation);      //Function that pushes elements from stack
int solve(pos head);                    //Function that solves the postfix equation

int main() {
    stack head;
    head.next = NULL;

    double result = solve(&head);
    printf("Solution = %.2f\n", result);

    return 0;
}

int solve(pos head) {
    char str[100];
    double num, result;

    FILE* f = fopen("postfix.txt", "r");    //Opening the file and checking if the file is opened correctly
    if (f == NULL) {
        printf("File Error\n");
        return FOP;
    }

    while (fscanf(f, "%s", str) == 1) {                                //Solving the equation
        if (isdigit(str[0]) || (str[0] == '-' && isdigit(str[1]))) {   //Checking if the scanned character is a number
            num = atof(str);                                           //Parsing the string to a number
            push(num, head);                                           //Storing the scanned number
        }
        else {
            if (head->next == NULL || head->next->next == NULL) {      //Checking if there are enough operands
                printf("Not enough operands!\n");
                fclose(f);
                return NOOP;
            }
            pop(head, str[0]);                                         
        }
    }

    if (head->next == NULL) {                                          //Checking if the solution is in the stack
        printf("Error: Empty stack!\n");
        fclose(f);
        return 0;
    }

    result = head->next->x;                                            //Storing the solution in a variable

    head->next = NULL;                                                 //Freeing the memory that held the solution
    free(head->next); 

    fclose(f);                                                         //Closing the file

    return result;
}

int push(double el, pos head) {
    pos q = (pos)malloc(sizeof(stack));           //Allocating the memory and checking if it went successfuly
    if (q == NULL) {
        printf("Memory allocation error!\n");
        return ALOC;
    }

    q->x = el;                                            
    q->next = head->next;
    head->next = q;

    return 0;
}

int pop(pos head, char operation) {
    double a, b, res;
    pos first, second;

    first = head->next;
    second = first->next;

    a = second->x;   
    b = first->x;                  

    switch (operation) {                          //Checking which operation is sent
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break;
    case '/':
        if (b == 0) {                               //Checking the denominator
            printf("Error: Division by zero!\n");
            return DIV;
        }
        res = a / b;
        break;
    case  '^':
        res = pow(a,b);
        break;
    default:
        printf("Unknown operator: %c\n", operation);
        return UNC;
    }


    head->next = second->next;
    free(first);
    free(second);

    push(res, head);                               //Storing the result of the operation
    return 0;
}
