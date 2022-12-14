#include "main.h"
#include <string.h>
#define MAX_TOKENS 10

/**
  * tokenise - breaks a string into tokens using provided delimiters
  * @BUFFER_STR: the string to tokenise.
  * @delims: an array of delimiters
  *
  * Description: the function uses a custom strtok() to break a string into
  *              an array of tokens.
  * Return: a pointer to the array of tokens
  */
char **tokenise(char *BUFFER_STR, const char *delims)
{
  /* allocate memory for array of tokens*/
  char **tokens = malloc(sizeof(char *) * MAX_TOKENS);
  
  /* we create a copy of buffer str that we can modify*/
  char *buff_copy = strdup(BUFFER_STR);
  
  /* now we tokenise the string using the specified delimiter*/
  char *token = _strtok(buff_copy, delims);
  
  int i = 0;
  
  while (token != NULL &&  i < MAX_TOKENS)
  {
    /* save tokens in an array */
    token[i] = token;
    i++;
    
    /* next token */
    token = _strtok(NULL, delims)
  }

  return (tokens);
}
