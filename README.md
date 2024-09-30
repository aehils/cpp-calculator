# cpp-calculator
### Numeric Calculator in C++

This program computes basic arithmetic using common operators: `+`, `-`, `*`, and `/`. Now with functionality to next backets in curly braces `{ }`.

Calculator obeys mathimatical principle that prioritises brackets, then multiplication and divison before addition and subtraction. For example, 2+8*4 = 34 != 40. This is governed by grammar rules that define expressions, terms, and primaries. The grammar is given by:

Expressions:
- Term
- Expression + Term
- Expression - Term

Terms:
- Primary
- Term * Primary
- Term / Primary

Primaries:
- a number (floating point literal in this case)
- ( expression ) **== an expression bound by brackets**

_Inspired by Chapters 6 and 7 in Bjarne Stroustrup's Programming Principles and Practices using C++_
