/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faozturk <faozturk@42kocaeli.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:10:51 by faozturk          #+#    #+#             */
/*   Updated: 2022/04/07 12:47:55 by faozturk         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

void	ft_action(int signum, siginfo_t *info, void *context)
{
	static char		c = 0;
	static pid_t	client_id = 0;
	static int		i = 0;

	(void)context;
	client_id = info->si_pid;
	c |= (signum == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			ft_putchar_fd('\n', 1);
			kill(client_id, SIGUSR1);
			client_id = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = ft_action;
	act.sa_flags = SA_SIGINFO;
	ft_putstr_fd("server pid : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
	{
		pause();
	}
	return (0);
}
