/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazaouya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:19:28 by hazaouya          #+#    #+#             */
/*   Updated: 2021/11/22 15:07:24 by hazaouya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philosopher	*lstlast(t_philosopher *lst)
{
	t_philosopher	*last;

	if (lst == NULL)
		return (lst);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher	*last;

	if (lst == NULL)
		return ;
	if (*lst)
	{
		last = lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
