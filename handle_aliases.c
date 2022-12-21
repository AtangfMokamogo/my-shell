#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ARGS 10

typedef struct alias {
    char *name;
    char *value;
    struct alias *next;
} alias_t;

/*Linked list of aliases*/ 
alias_t *aliases = NULL;

void print_alias(alias_t *alias) {
    printf("%s='%s'\n", alias->name, alias->value);
}


char **parse_args(char *input, int *argc) {
    char **argv = malloc(sizeof(char *) * (MAX_ARGS + 1));
    if (!argv) {
        perror("malloc");
        return NULL;
    }

    char *token = strtok(input, " ");
    int i = 0;
    while (token) {
        if (i >= MAX_ARGS) {
            fprintf(stderr, "parse_args: too many arguments\n");
            break;
        }
        argv[i] = strdup(token);
        if (!argv[i]) {
            perror("strdup");
            break;
        }
        token = strtok(NULL, " ");
        i++;
    }
    argv[i] = NULL;
    *argc = i;

    return argv;
}




int set_alias(char *name, char *value) {
    alias_t *alias = malloc(sizeof(alias_t));
    if (!alias) {
        perror("malloc");
        return -1;
    }

    alias->name = strndup(name, strlen(name));
    if (!alias->name) {
        perror("strndup");
        free(alias);
        return -1;
    }

    alias->value = strndup(value, strlen(value));
    if (!alias->value) {
        perror("strndup");
        free(alias->name);
        free(alias);
        return -1;
    }

    /* Add the new alias to the front of the linked list */
    alias->next = aliases;
    aliases = alias;

    return 0;
}

int shellby_alias(char *input) {
    /* Parse the input string into a list of arguments */ 
    int argc;
    int i, ret = 0;
    char *value;
    char **argv = parse_args(input, &argc);
    if (!argv) {
        return -1;
    }

    if (!argv[0]) {
        /* Print all aliases */ 
        for (alias_t *alias = aliases; alias; alias = alias->next) {
            print_alias(alias);
        }
        return 0;
    }

    int i, ret = 0;
    char *value;
    for (i = 0; argv[i]; i++) {
        value = strchr(argv[i], '=');
        if (!value) {
            alias_t *alias;
            /* Print a specific alias */ 
            for (alias = aliases; alias; alias = alias->next) {
                if (strcmp(argv[i], alias->name) == 0) {
                    print_alias(alias);
                    break;
                }
            }
            if (!alias) {
                fprintf(stderr, "alias: %s: not found\n", argv[i]);
                ret = -1;
            }
        } else {
            /* Set an alias */ 
            if (set_alias(argv[i], value) < 0) {
                ret = -1;
            }
        }
    }

    /* Free the argument list */ 
    for (i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);

    return ret;
}
