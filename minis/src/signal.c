#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		if (ctrlc == 0)
			display_prompt_msg();		
		set_env_var("?", ft_itoa(130));
		ctrlc = 0;
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
	ft_putstr("minishell : [1]    42983 quit       by ctr-Z\\n");
	exit(0);
}
