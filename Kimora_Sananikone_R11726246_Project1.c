/* Kimora Sananikone R11726246 | Project 1: Lexical Analzyer | October 18, 2023
The Purpose of this program is to identify the lexemes and tokens provided by
source files and once the analyzer identifies the lexeme in the language and
matches them to the correct token it will print the lexeme and token.
*/
/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages.
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//#include "front.h"
//#include "parser.h"

/* Character Classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token Codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LEFT_CBRACE 27
#define RIGHT_CBRACE 28
#define LESSER_OP 29
#define GREATER_OP 30
#define EQUAL_OP 31
#define NEQUAL_OP 32
#define LEQUAL_OP 33
#define GEQUAL_OP 34
#define SEMICOLON 46
#define INC_OP 35
#define DEC_OP 36
#define KEY_READ 37
#define KEY_WRITE 38
#define KEY_WHILE 39
#define KEY_DO 40

/* Global Variable */
int nextToken;
char *token; // prints the name of the token associated with the lexeme

int lex();

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) {
  /* Open the input data file and process its contents */
  printf("DCooke Analyzer :: R11726246\n");
  if ((in_fp = fopen(argv[1], "r")) == NULL) {
    // Error Message for if the files cannot be opened
    printf("ERROR - cannot open front.in");
  } else {
    getChar();
    do {
      lex();
    } while (nextToken != EOF);
  }
  return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the
 * token */

/* My if else cases represent the lexemes that include another lexeme and so in order for it read it correctly I had to do if else and add ungetc into my cases 
*/
/* Ungetc - a function that I used so that way once it reads the lexemes such DEC_OP, INC_OP etc... it can read them and put the lexeme back into in the stream and read it again  */

/* In each case I wrote token = "TOKEN" because I created them as strings, and that way when it prints it'll read what the lexeme is
*/


static int lookup(char ch) {
  switch (ch) {
  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    token = "LEFT_PAREN";
    break;
  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    token = "RIGHT_PAREN";
    break;
  case '{':
    addChar();
    nextToken = LEFT_CBRACE;
    token = "LEFT_CBRACE";
    break;
  case '}':
    addChar();
    nextToken = RIGHT_CBRACE;
    token = "RIGHT_CBRACE";
    break;
  case '+':
    addChar();
    getChar();
    if (nextChar == '+') {
      addChar();
      //because the case is already '+' if the nextChar is '+' it'll add the character (lexeme) creating the token INC_OP
      nextToken = INC_OP;
      token = "INC_OP";
    } else {
      //Once INC_OP is read,it'll go back to ADD_OP because of ungetc
      nextToken = ADD_OP;
      token = "ADD_OP";
      ungetc(nextChar, in_fp);
    }
    break;
  case '-':
    addChar();
    getChar();
    if (nextChar == '-') {
      addChar();
      //because the case is already '-' if the nextChar is '-' it'll add the character (lexeme) creating the token DEC_OP
      nextToken = DEC_OP;
      token = "DEC_OP";
    } else {
      //Once DEC_OP is read,it'll go back to SUB_OP because of ungetc
      nextToken = SUB_OP;
      token = "SUB_OP";
      ungetc(nextChar, in_fp);
    }
    break;
  case '*':
    addChar();
    nextToken = MULT_OP;
    token = "MULT_OP";
    break;
  case '/':
    addChar();
    nextToken = DIV_OP;
    token = "DIV_OP";
    break;
  case '=':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      //because the case is already '-' if the nextChar is '-' it'll add the character (lexeme) creating the token DEC_OP
      nextToken = EQUAL_OP;
      token = "EQUAL_OP";
    } else {
      //Once EQUAL_OP is read,it'll go back to ASSIGN_OP because of ungetc
      nextToken = ASSIGN_OP;
      token = "ASSIGN_OP";
      ungetc(nextChar, in_fp);
    }
    break;
  case '<':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      //because the case is already '=' if the nextChar is '<' it'll add the character (lexeme) creating the token LEQUAL_OP
      nextToken = LEQUAL_OP;
      token = "LEQUAL_OP";
    } else {
      //Once LEQUAL_OP is read,it'll go back to LESSER_OP because of ungetc
      nextToken = LESSER_OP;
      token = "LESSER_OP";
      ungetc(nextChar, in_fp);
    }
    break;
  case '>':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      //because the case is already '=' if the nextChar is '>' it'll add the character (lexeme) creating the token GEQUAL_OP
      nextToken = GEQUAL_OP;
      token = "GEQUAL_OP";
    } else {
      //Once GEQUAL_OP is read,it'll go back to GREATER_OP because of ungetc
      nextToken = GREATER_OP;
      token = "GREATER_OP";
      ungetc(nextChar, in_fp);
    }
    break;
  case ';':
    addChar();
    nextToken = SEMICOLON;
    token = "SEMICOLON";
    break;
  case '!':
    addChar();
    getChar();
    if (nextChar == '=') {
      addChar();
      //because the case is already '!' if the nextChar is '=' it'll add the character (lexeme) creating the token NEQUAL_OP
      nextToken = NEQUAL_OP;
      token = "NEQUAL_OP";
    } else {
      //Once NEQUAL_OP gets read, it'll go back to ASSIGN_OP because of ungetc
      nextToken = ASSIGN_OP;
      token = "ASSIGN_OP";
      ungetc(nextChar, in_fp);
    }
    break;

  default:
    addChar();
    // If the lexeme isn't defined, then it gets recongized as UNKNOWN and print UNKNOWN
    nextToken = UNKNOWN;
    token = "UNKNOWN";
    break;
  }

  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  } else {
    printf("Error - lexeme is too long \n");
  }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
static void getChar() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else
      charClass = UNKNOWN;
  } else {
    charClass = EOF;
  }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
  lexLen = 0;
  getNonBlank();

  switch (charClass) {
  /* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT) {
      addChar();
      getChar();
    }
  //
    if (strcmp(lexeme, "read") == 0) {
      nextToken = KEY_READ;
      token = "KEY_READ";
    } else if (strcmp(lexeme, "write") == 0) {
      nextToken = KEY_WRITE;
      token = "KEY_WRITE";
    } else if (strcmp(lexeme, "while") == 0) {
      nextToken = KEY_WHILE;
      token = "KEY_WHILE";
    } else if (strcmp(lexeme, "do") == 0) {
      nextToken = KEY_DO;
      token = "KEY_DO";
    } else {
      nextToken = IDENT;
      token = "IDENT";
    }
    break;

  /* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    token = "INT_LIT";
    break;

  /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;

  /* EOF */
  case EOF:
    nextToken = EOF;
    token = "\n";
    lexeme[0] = 0;
    lexeme[1] = 0;
    lexeme[2] = 0;
    lexeme[3] = 0;
    break;
  } /* End of switch */

  // Prints the lexeme & the name of the token
  printf("%s %s\n", lexeme, token);

  return nextToken;
} /* End of function lex */
