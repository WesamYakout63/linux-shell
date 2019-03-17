#include <stdio.h>
#include <stdlib.h>

char **var_name, **var_val;
int length = 0;

void initalize()
{
    var_name = malloc(50 * sizeof(char));
    var_val = malloc(50 * sizeof(char));
}

const char* lookup_variable( const char* key )
{
    // you should implement this function
    int i;
    for(i = 0 ; i < length ; i++)
    {
        if(compare_string(key, var_name[i]))
            break;
    }
    return i >= length ? "" : var_val[i];
}

void set_variable( const char* key, const char* value )
{
    // you should implement this function
    var_name[length] = strdup(key);
    var_val[length] = strdup(value);
    length++;
}

void print_all_variables( void )
{
    // you should implement this function
}
