/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavas <tyavas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:36:49 by tyavas            #+#    #+#             */
/*   Updated: 2022/12/18 22:36:49 by tyavas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static	int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (*nptr == '\0')
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	if (res > LONG_MAX && sign == -1)
		return (0);
	if (res > LONG_MAX && sign == 1)
		return (-1);
	return (res * sign);
}

static	unsigned	long	ft_strlen(char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static	void	ft_convert(int c, char *str, int my_index)
{
	int	i;

	i = my_index + 7;
	while (c > 0)
	{
		str[i--] = (char)((c % 2) + 48);
		c /= 2;
	}
	while (i >= my_index)
		str[i--] = '0';
}

static	void	ft_send_signal(char *str, int my_index, int pid)
{
	int	i;

	i = 0;
	while (i <= my_index)
	{
		if (str[i] == '1')
			kill (pid, SIGUSR1);
		if (str[i] == '0')
			kill (pid, SIGUSR2);
		i++;
		usleep(500);
	}
}

int	main(int ac, char *argv[])
{
	int			pid;
	char		*str;
	int			i;
	int			my_index;
	long long	len;

	my_index = 0;
	if (ac == 3)
	{
		pid = ft_atoi(argv[1]);
		len = ft_strlen(argv[2]);
		str = malloc ((len * 8) * sizeof(char));
		if (!str)
			return (-1);
		i = 0;
		while (argv[2][i])
		{
			ft_convert((int)argv[2][i++], str, my_index);
			my_index += 8;
		}
		ft_send_signal(str, my_index + 8, pid);
		free(str);
	}
	return (0);
}
