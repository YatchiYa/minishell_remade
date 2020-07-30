#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		display_prompt_msg();
		signal(SIGINT, signal_handler);
	}
}

void	signal_handler2(int signo)
{
	signo = 0;
	
	ft_putstr("\n");
	ft_putstr("[1]    42983 quit       by ctr-\\\n");
	display_prompt_msg();
}

void	signal_handler3(int signo)
{
	signo = 0;
	
	ft_putstr("\n");
	ft_putstr("[1]    42983 quit       by ctr-Z\\n");
	exit(0);
}
