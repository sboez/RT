/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:05:52 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/23 10:13:34 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(char *prog, char *err)
{
	ft_putstr_fd(prog, 2);
	perror(err);
	exit(1);
}

void	exit_custom_error(char *prog, char *err)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(1);
}
