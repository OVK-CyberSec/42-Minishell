#include "../../includes/minishell.h"

int is_valid_id(const char *s)
{
    int i;

    if (!s || !s[0])
        return 0;

    if (!(ft_isalpha(s[0]) || s[0] == '_'))
        return 0;

    i = 1;
    while (s[i])
    {
        if (!(ft_isalnum(s[i]) || s[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}