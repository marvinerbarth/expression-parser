Markdown
# Expression Parser (C++)

A simple arithmetic expression parser built to learn how compilers handle mathematical input. It tokenizes standard infix math strings, converts them using the Shunting Yard algorithm, and evaluates them via Reverse Polish Notation (RPN).

---

## Features

* **Tokenizer:** Handles multi-digit integers and ignores whitespace.
* **Precedence & Brackets:** Respects standard math rules (+ - * /) and handles `()` groups.
* **RPN Engine:** Converts infix expressions to postfix and computes the final result.

---

## Planned Updates

* **Abstract Syntax Tree (AST):** Move from a flat RPN stack to a proper tree structure for better expression tracking.
* **Unary Operators:** Add support for negative numbers (e.g., `-5 + 3`).
* **Error Handling:** Catch invalid syntax instead of letting the program crash.

---

## Limitations

* **Integers only:** No decimal/floating-point support yet.
* **No Validation:** Passing broken or malformed strings causes undefined behavior.
* **No Variables:** Limited to raw numbers (no variables or functions like `sin`/`cos`).

---

## Notes

This is my first project exploring compiler-style logic, stacks, and token streams in C++.
