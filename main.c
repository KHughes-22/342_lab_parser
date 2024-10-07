/* A lexical analyzer system for simple
arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
/* Global declarations */
/* Variables */

int charClass;
char lexeme [100];
char nextChar;

int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
/******************************************************/
/* main driver */
int main(void) {
      /* Open the input data file and process its contents */
      // if ((in_fp = fopen("test1.txt", "r")) == NULL)
      //       printf("ERROR - cannot open front.in \n");
      // else {
      //       getchar();
      //       do {
      //             lex();
      //       } while (nextToken != EOF);
      // }

      //for the parser main
      printf("hello----------------------------------------------------");
      if ((in_fp = fopen("test1.txt", "r")) == NULL){
            printf("ERROR - cannot open front.in \n");
      }
      else {
        lex();
        void expr();
      }
      return 0;
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
      switch (ch) {
      case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
      case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
      //YOUR CODE
      case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
      case '+':
            addChar();
            nextToken = ADD_OP;
            break;
      case '-':
            addChar();
            nextToken = SUB_OP;
            break;
      case '*':
            addChar();
            nextToken = MULT_OP;
            break;
      case '/':
            addChar();
            nextToken = DIV_OP;
            break;
      }
      return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
      if (lexLen <= 98) {
      //YOUR CODE
      lexeme[lexLen] = nextChar;
      lexeme[lexLen + 1] = 0;
      lexLen++;
      //printf("lexeme at position %i: %c",lexLen, lexeme[lexLen]);
      }
      else
      printf("Error - lexeme is too long \n");
}

/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
      if ((nextChar = getc(in_fp)) != EOF) 
      {
            if (isalpha(nextChar))
            {
            charClass = LETTER;
            }
            else if (isdigit(nextChar))
            charClass = DIGIT;
            else 
            {     
            // YOUR CODE;
            charClass = UNKNOWN;
            }
      }
//end of file
      else
            charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
      while (isspace(nextChar))
      { 
            getChar();
      }
}
/*
*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
      //if the nextchar is null(start of a line) then get the next char.
      if (nextChar == 0){
            getChar();
      }
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
                  nextToken = IDENT;
                  //lexeme[lexLen] = 0;
                  break;
            /* Parse integer literals */
            //YOUR CODE
            case DIGIT:
                  addChar();
                  getChar();
                  while (charClass == DIGIT){
                        addChar();
                        getChar();
                  }
                  nextToken = INT_LIT;
                  break;
            /* Parentheses and operators */
            case UNKNOWN:
                  //lookup will add the nextchar to the Lexeme
                  nextToken = lookup(nextChar);
                  getChar();
                  break;
            /* EOF */
            case EOF:
                  nextToken = EOF;
                  lexeme[0] = 'E';
                  lexeme[1] = 'O';
                  lexeme[2] = 'F';
                  lexeme[3] = 0;
                  break;
      } /* End of switch */
      printf("Next token is: %d, Next lexeme is %s\n",
      nextToken, lexeme);
      return nextToken;
} /* End of function lex */

void expr(void){
      printf("Enter <expr>\n");

      void term();

      while(nextToken == 21 || nextToken == 22){
            lex();
            term();
      }

      printf("Exit <expr>\n");
      return;
}

void term(void){
      printf("Enter <term>\n");
      void factor();
      while(nextToken == 23 || nextToken == 24){
            nextToken = lex();
            factor();
      }

      printf("Exit <term>\n");
      return;
}

void factor(void){
      printf("enter <factor>\n");
      
      if(nextToken == 10 || nextToken == 11){
            lex();
      }

      else if(nextToken == 25){
            lex();
            void expr();

            if(nextToken == 26){
                  lex();
            }
            else{
                  printf("Syntax Error");
            }
      }
      else{
            printf("Syntax Error");
      }

      printf("Exit<factor>\n");
      return;
}

