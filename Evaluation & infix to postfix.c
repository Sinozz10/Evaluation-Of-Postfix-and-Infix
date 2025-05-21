/*
This program converts an infix expression to postfix and evaluates the postfix expression.
It uses a stack to manage operators and operands during the conversion and evaluation process.
It's made to handle basic arithmetic operations: +, -, *, /, %, and ^.
It also handles parentheses and unary minus for negative numbers.
This Program is made by Yassin Khaled. ID:9610 Group: 1
This Program is made by Jana Ahmed. ID:9549 Group: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define SIZE 1000

typedef struct Node
{
    float data;  
    struct Node *next;
} Node;
typedef struct 
{
    Node *top;
} Stack;

// Function prototypes
Stack* initialize();
float pop(Stack * );
void push(Stack *, float );
int isEmpty(Stack * );
float peek(Stack * );
Node *createNode(float );
char *infixTopostfix(char * );
float evaluatePostfix(char * );
float evaluate(float , float , char );
int precedence(char );
int isNumber(char * );

int main(void)
{
    int choice;
    printf(">>>>>>>>>>>>>>>>>>--Assignment 4--<<<<<<<<<<<<<<<<\n");
    do {
        printf("1.Infix and Postfix .. Evaluation\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); 
        switch (choice)
        {
            
            case 1:
                printf(">>>>>>>>>>>>>>>>>>--Infix to Postfix to Evaluation--<<<<<<<<<<<<<<<<\n");
                char infix[SIZE];
                printf("Enter infix expression: ");
                fgets(infix, SIZE, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                char *postfix_result = infixTopostfix(infix);
                printf("Postfix expression: %s\n", postfix_result);
                printf("Evaluating postfix expression...\n");
                float result = evaluatePostfix(postfix_result);
                printf("Result: %.3f\n", result);
                free(postfix_result);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
    } while (choice != 3);
}

Stack* initialize(){
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

float pop(Stack *s){
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    Node *temp = s->top;
    float value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

Node* createNode(float value){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(Stack *s){
    return (s->top == NULL);
}

void push(Stack *s, float value){
    Node *newNode = createNode(value);
    newNode->next = s->top;
    s->top = newNode;
}

float peek(Stack *s){
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->top->data;
}

int precedence(char operator){
    switch (operator)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isNumber(char* token){
    if (token[0] == '-' && strlen(token) > 1) 
    {
        if (isdigit(token[1]) || token[1] == '.') 
        {
            return 1;  
        }
        return 0; // Not a number
    }
    if (isdigit(token[0]) || token[0] == '.') 
    {
        return 1;
    }
    return 0;
}

char* infixTopostfix(char *infix){
    Stack *s = initialize();
    char* postfix = (char*)malloc(sizeof(char) * (2 * strlen(infix) + 1));
    if (postfix == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    char infix_copy[SIZE];
    strcpy(infix_copy, infix);
    postfix[0] = '\0';
    char* token;
    token = strtok(infix_copy, " ");
    char prev_token_type = 'o'; // 'o' for operator, 'n' for number, 'p' for parenthesis 
    while (token != NULL) {
        // Check if token is a number
        if (isNumber(token)) {
            strcat(postfix, token);
            strcat(postfix, " ");
            prev_token_type = 'n';
        }
        else if (token[0] == '(') {
            push(s, '(');
            prev_token_type = 'p';
        }
        else if (token[0] == ')') {
            while (!isEmpty(s) && peek(s) != '(') {
                char op = (char)pop(s);
                char op_str[2] = {op, '\0'};
                strcat(postfix, op_str);
                strcat(postfix, " ");
            }
            if (!isEmpty(s) && peek(s) == '(') {
                pop(s);
            } else {
                printf("Mismatched parentheses\n");
                free(postfix);
                exit(1);
            }
            prev_token_type = 'p'; // Mark previous token as parenthesis
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || 
                 token[0] == '/' || token[0] == '%' || token[0] == '^') {
            // Handle unary minus (negative number)
            if (token[0] == '-' && (prev_token_type == 'o' || prev_token_type == 'p' || prev_token_type == '\0')) {
                // Handle negative number in next token
                char* next_token = strtok(NULL, " ");
                if (next_token != NULL && isNumber(next_token)) {
                    char negative_num[SIZE];
                    strcpy(negative_num, "-");
                    strcat(negative_num, next_token);
                    strcat(postfix, negative_num);
                    strcat(postfix, " ");
                    prev_token_type = 'n';
                }
            } else {
                while (!isEmpty(s) && peek(s) != '(' && 
                      ((token[0] != '^' && precedence(peek(s)) >= precedence(token[0])) ||
                       (token[0] == '^' && precedence(peek(s)) > precedence(token[0])))) {
                    
                    char op = (char)pop(s);
                    char op_str[2] = {op, '\0'};
                    strcat(postfix, op_str);
                    strcat(postfix, " ");
                }
                push(s, token[0]);
                prev_token_type = 'o';  // Mark previous token as operator
            }
        }
        token = strtok(NULL," ");
    }
    while (!isEmpty(s)){
        if (peek(s) == '(') {
            printf("Mismatched parentheses\n");
            free(postfix);
            exit(1);
        }
        char op = (char)pop(s);
        char op_str[2] = {op, '\0'};
        strcat(postfix, op_str);
        strcat(postfix, " ");
    }
    int len = strlen(postfix);
    if (len > 0 && postfix[len-1] == ' '){
        postfix[len-1] = '\0';
    }
    
    free(s);
    return postfix;
}

float evaluate(float val1, float val2, char operator){
    float value = 0;
    switch (operator)
    {
        case '+':
            value = val2 + val1;
            break;
        case '-':
            value = val2 - val1;
            break;
        case '*':
            value = val2 * val1;
            break;
        case '/':
            if (val1 == 0) {
                printf("Division by zero\n");
                exit(1);
            }
            value = val2 / val1;
            break;
        case '%':
            value = fmod(val2, val1);
            break;
        case '^':
            value = pow(val2, val1);
            break;
        default:
            printf("Unknown operator: %c\n", operator);
            exit(1);
    }
    return value;
}

float evaluatePostfix(char *postfix){
    Stack *s = initialize();
    char postfix_copy[SIZE];
    strcpy(postfix_copy, postfix);
    char* token;
    token = strtok(postfix_copy, " ");
    while (token != NULL) {
        // Check if token is a number (including negative numbers and decimals)
        if (isNumber(token)) {
            float num = atof(token);
            push(s, num);
        }
        // Token is an operator
        else if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || 
                 token[0] == '/' || token[0] == '%' || token[0] == '^')) {
            
            if (isEmpty(s)) {
                printf("Invalid postfix expression\n");
                exit(1);
            }
            float val1 = pop(s);
            
            if (isEmpty(s)) {
                printf("Invalid postfix expression\n");
                exit(1);
            }
            float val2 = pop(s);
            
            float result = evaluate(val1, val2, token[0]);
            push(s, result);
        }
        token = strtok(NULL, " ");
    }
    if (isEmpty(s)) {
        printf("Invalid postfix expression\n");
        exit(1);
    }
    float result = pop(s);
    if (!isEmpty(s)) {
        printf("Invalid postfix expression\n");
        exit(1);
    }
    free(s);
    return result;
}