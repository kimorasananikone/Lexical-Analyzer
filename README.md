# Lexical-Analyzer
Identify the lexemes and tokens provided by the source files and once the analyzer identifies the lexeme in the language and matches them to the correct token it will print out the lexeme and token. 

Develop a lexical analyzer in C or C++ that can identify lexemes and tokens found in a source code file provided
by the user. Once the analyzer has identified the lexemes of the language and matched them to a token group,
the program should print each lexeme / token pair to the screen.
The source code file provided by the user will be written in a new programming language called “DCooke” and is
based upon the following grammar (in BNF):


P ::= S



S ::= V=E | read(V) | write(V) | do { S } while (C) | S;S



C ::= E < E | E > E | E == E | E != E | E <= E | E >= E



E ::= T | E + T | E - T



T ::= F | T * F | T / F



F ::= (E) | O | N | V



O ::= V++ | V--



V ::= a | b | … | y | z | aV | bV | … | yV | zV



N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N
