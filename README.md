# Lexical-Analyzer
Identify the lexemes and tokens provided by the source files and once the analyzer identifies the lexeme in the language and matches them to the correct token it will print out the lexeme and token. 

f IDENT
= ASSIGN_OP
15 INT_LIT
; SEMICOLON
i IDENT
= ASSIGN_OP
11 INT_LIT
; SEMICOLON
read KEY_READ
( LEFT_PAREN
n IDENT
) RIGHT_PAREN
; SEMICOLON
do KEY_DO
{ LEFT_CBRACE
n IDENT
= ASSIGN_OP
i IDENT
+ ADD_OP
f IDENT
; SEMICOLON
f IDENT
-- DEC_OP
; SEMICOLON
i IDENT
++ INC_OP
} RIGHT_CBRACE
while KEY_WHILE
( LEFT_PAREN
f IDENT
== EQUAL_OP
i IDENT
) RIGHT_PAREN
