#include "main.h"

/**
  * _strtok- This is our custom implementation of the built in strtok()
  * function
  *
  * @BUFFER_STR: A pointer to the input string from stdin.
  * @delims: A pointer to the array of delimiters.
  *
  * Return: a pointer to the token identified.
  */
char *_strtok(char *str, const char *delim)
{
	char *start;
	char *end;
    static char *current_position = NULL;

    if (str != NULL)
    {
        current_position = str;
    }

    if (current_position == NULL || *current_position == '\0')
    {
        return NULL;
    }

    start = current_position;
    end = start;

    while (*end != '\0')
    {
        if (strchr(delim, *end))
        {
            *end = '\0';
            current_position = end + 1;
            return start;
        }

        end++;
    }

    current_position = NULL;
    return start;
}
