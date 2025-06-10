# Infix to Postfix Converter & Evaluator

A C program that converts mathematical expressions from infix notation to postfix notation and evaluates the result using stack data structures.

## Authors
- **Yassin Khaled** - @Sinozz10
- **Jana Ahmed** - @Jana-Mehanna

## Features

- **Infix to Postfix Conversion**: Converts mathematical expressions from standard infix notation to postfix (Reverse Polish Notation)
- **Postfix Evaluation**: Evaluates postfix expressions and returns numerical results
- **Comprehensive Operator Support**: Handles basic arithmetic operations including:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`)
  - Modulus (`%`)
  - Exponentiation (`^`)
- **Advanced Features**:
  - Parentheses handling for operation precedence
  - Unary minus support for negative numbers
  - Decimal number support
  - Proper operator precedence handling
  - Error handling for invalid expressions

## Technical Implementation

### Data Structures
- **Stack**: Implemented using a linked list structure with dynamic memory allocation
- **Node**: Contains float data and pointer to next node

### Key Functions
- `infixTopostfix()`: Converts infix expression to postfix notation
- `evaluatePostfix()`: Evaluates postfix expression and returns result
- `precedence()`: Determines operator precedence
- `isNumber()`: Validates if a token is a valid number
- Stack operations: `push()`, `pop()`, `peek()`, `isEmpty()`

### Menu Options
1. **Infix and Postfix .. Evaluation**: Convert and evaluate expressions
2. **Exit**: Terminate the program


## Operator Precedence

The program follows standard mathematical operator precedence:

1. **Exponentiation (`^`)** - Highest precedence (right-associative)
2. **Multiplication (`*`), Division (`/`), Modulus (`%`)** - Medium precedence
3. **Addition (`+`), Subtraction (`-`)** - Lowest precedence
4. **Parentheses** override natural precedence

## Error Handling

The program includes comprehensive error handling for:
- **Memory allocation failures**
- **Division by zero**
- **Mismatched parentheses**
- **Invalid postfix expressions**
- **Stack underflow/overflow conditions**
- **Unknown operators**

## Technical Specifications

- **Maximum expression length**: 1000 characters
- **Number format**: Floating-point numbers with 3-decimal precision output
- **Memory management**: Dynamic allocation with proper cleanup
- **Input method**: Space-separated tokens via `fgets()`

## Algorithm Overview

### Infix to Postfix Conversion (Shunting Yard Algorithm)
1. Process tokens from left to right
2. Numbers go directly to output
3. Operators are pushed to stack based on precedence rules
4. Parentheses manage operation grouping
5. Handle unary minus as negative numbers

### Postfix Evaluation
1. Process tokens from left to right
2. Push operands onto stack
3. For operators: pop two operands, compute result, push back
4. Final stack contains the result

## Memory Management

- Dynamic memory allocation for stacks and strings
- Proper memory cleanup with `free()` calls
- Error handling for allocation failures

## Dependencies

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`, `ctype.h`
- Math library: `math.h` (requires `-lm` compiler flag)

## Limitations

- Tokens must be space-separated in input
- Maximum expression length is 1000 characters
- Only supports basic arithmetic operators
- Results displayed with 3-decimal precision
