/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:12:54 by fcecilie          #+#    #+#             */
/*   Updated: 2017/03/01 10:07:16 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_w(char const *s, char c)
{
	int		word;
	int		n;

	word = 0;
	n = 0;
	if (s[0] != c)
	{
		word++;
		n++;
	}
	while (s[n] != '\0')
	{
		if (s[n] != c && s[n - 1] == c)
			word++;
		n++;
	}
	return (word);
}

static int	ft_c(char const *s, char c, int word)
{
	int		n;
	int		carac;
	int		actual_word;

	n = 0;
	carac = 0;
	actual_word = 0;
	if (s[0] != c)
	{
		actual_word++;
		n++;
	}
	while (s[n] != '\0' && actual_word < word)
	{
		if (s[n] != c && s[n - 1] == c)
			actual_word++;
		n++;
	}
	n--;
	while (s[n] != c && s[n] != '\0')
	{
		carac++;
		n++;
	}
	return (carac);
}

static char	**ft_strsplit_annexe(char const *s, char c, int *w, int n)
{
	char	**tab;

	if ((tab = (char**)malloc(sizeof(char*) * (ft_w(s, c) + 1))) == NULL)
		return (NULL);
	while (s[n] != '\0')
	{
		while (s[n] == c && s[n] != '\0')
			n++;
		if (s[n] != c && s[n] != '\0')
		{
			tab[w[0]] = (char*)malloc(ft_c(s, c, w[0] + 1) + 1);
			while (s[n] != c && s[n] != '\0')
			{
				tab[w[0]][w[1]] = s[n];
				n++;
				w[1]++;
			}
			tab[w[0]][w[1]] = '\0';
			w[1] = 0;
			w[0]++;
		}
	}
	tab[w[0]] = NULL;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		n;
	int		w_c[2];

	n = 0;
	w_c[0] = 0;
	w_c[1] = 0;
	if (!s || !c)
		return (NULL);
	tab = ft_strsplit_annexe(s, c, w_c, n);
	if (tab == NULL)
		return (NULL);
	return (tab);
}
