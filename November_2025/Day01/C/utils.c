//
// Created by Léhane Payet on 21/11/2025.
//
#include "data.h"

int	ft_atoi(const char *str)
{
    int	i;
    int	result;
    int	sign;

    i = 0;
    result = 0;
    sign = 1;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - 48);
        i++;
    }
    return (result * sign);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t	i;

    i = 0;
    if (dstsize == 0)
    {
        while (src[i])
            i++;
        return (i);
    }
    while (i < dstsize - 1 && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    if (i < dstsize)
        dst[i] = '\0';
    while (src[i])
        i++;
    return (i);
}

char	*ft_strdup(const char *src)
{
    char	*dst;
    char	*start;

    dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
    if (!dst)
        return (NULL);
    start = dst;
    while (*src)
        *dst++ = *src++;
    *dst = '\0';
    return (start);
}

size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

void trim_newline(char *s)
{
    if(!s)
        return;
    size_t len = ft_strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
    {
        s[len - 1] = '\0';
        len--;
    }
}

