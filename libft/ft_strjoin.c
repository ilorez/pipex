/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:43:27 by znajdaou          #+#    #+#             */
/*   Updated: 2024/12/31 11:56:29 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* ft_strjoin
 * this function is used to concatenate two strings
 * @param s1: the first string
 * @param s2: the second string
 * @return: the address of the concatenated string
 * @return: s1 if s2 is NULL and vice versa || if both are NULL return ""

	* @note: the funciton always return a new allocated string
  * or null that can always be freed
 **/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
	{
		return (ft_strdup(s2));
	}
	if (!s1 && !s2)
		return (ft_strdup(""));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = ft_calloc(sizeof(char), size);
	if (!dst)
		return (NULL);
	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
