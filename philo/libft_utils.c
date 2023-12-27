/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 18:07:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/27 13:51:38 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param c int to be checked
 * @brief checks characters for numeric characters
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * @param c character to be checked
 * @brief checks characters for whitespaces
*/
int	ft_iswhitespace(char c)
{
	return (c == ' ' || ((c >= 9 && c <= 13)));
}

/**
 * @param str string to be converted to integer
 * @brief converting numeric characters to integers
*/
long int	ft_atoi(const char *str)
{
	long	i;
	long	sign;
	long	number;

	number = 0;
	sign = 1;
	i = 0;
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i] -48;
		i++;
	}
	return (number * sign);
}

/**
 * @param b variable to be converted to unsigned char
 * @param c	integer to be converted to unsigned char
 * @param len lenght of variable to be set
 * @brief setting the memory of x number variables
*/
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*charb;
	size_t			i;

	i = 0;
	charb = b;
	while (i < len)
	{
		*charb = (unsigned char)c;
		charb++;
		i++;
	}
	return (b);
}

/**
 * @param s variable to be set to '\0'
 * @param n	lenght of memory needed to be set to '\0'
 * @brief setting the memory of x number variables to '\0'
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/**
 * @param count size of the variable(s) to be malloced
 * @param size amount of the variable(s) to be malloced
 * @brief allocating memory on the heap and seting it to '\0'
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*aloc_mem;

	aloc_mem = malloc(count * size);
	if (aloc_mem == NULL)
	{
		return (NULL);
	}
	ft_bzero(aloc_mem, (count * size));
	return (aloc_mem);
}


/**
 * @param s1 string to be compared
 * @param s2 string to compare with
 * @brief compares strings
 * @return returns 0 if strings are identical, returns non 0
 * if not identical
*/
int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}