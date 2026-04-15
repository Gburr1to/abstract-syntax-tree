# AST Expression Generator & Parser

A tool for constructing Abstract Syntax Trees (AST) of mathematical and bitwise expressions, generating infix notation code from them, and validating that code using a recursive descent parser.

## Features
- **Abstract Syntax Tree (AST)**: Classes for representing expressions as hierarchical trees.
    - **Terminals**: Integers, Hexadecimal literals (`#F1`), and Variables (`abc`).
    - **Binary Operations**: Addition (`+`), Subtraction (`-`), Multiplication (`*`), Division (`/`), Modulo (`%`), Bitwise AND (`&`), and Bitwise OR (`|`).
- **Code Generation**: Each AST node can generate its corresponding infix expression string using the `toString()` method, automatically handling parentheses for correct precedence.
- **Recursive Descent Parser**: A grammar-based parser that validates the syntax of generated expressions, supporting operator precedence (Primary > Unary > Multiplicative > Additive > Bitwise).
- **Lexical Analysis**: Custom DFA-based scanner for tokenizing expressions.

## Building the Application
To build the project using CMake:
```bash
mkdir build && cd build
cmake ..
make
```

## Running the Tests
The current implementation in `main.cpp` runs a suite of automated tests that:
1. Construct complex AST structures manually.
2. Generate infix code from the trees.
3. Pass the generated code through the Scanner and Parser to verify correctness.

Run the executable:
```bash
./parser
```

## Documentation
Generate source code documentation using Doxygen:
```bash
doxygen Doxyfile
```
The output will be available in the `docs/` directory.
