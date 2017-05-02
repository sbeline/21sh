/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:04:58 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/02 09:56:00 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/Includes/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# define NB_BUILT 8

# define SUCCESS 0
# define SWITCH_MODE 262144
# define SHELL_CODE 262145
# define QUOTE_CODE 262146
# define D_QUOTE_CODE 262147
# define BACKQUOTE_CODE 262148
# define HEREDOC_CODE 262149
# define MACREALLOC(ret, name, size) (ret = ft_realloc(name, size));

t_llist				*g_env;

typedef	enum		s_mode
{
	SHELL,
	HEREDOC,
	QUOTE,
	D_QUOTE,
	BACKQUOTE,
	ERROR,
}					t_mode;

typedef struct		s_memory
{
	char			*history_path;
	int				fd_history;
	int				code_history;
	char			*line;
	char			*key_ctrl;
	char			key;
	t_llist			*var;
	char			*line_mode;
	char			*line_mode_tmp;
	t_mode			mode;
	int				launch;
	int				line_lenght;
}					t_memory;

t_memory			g_memory;

/*error gestion*/

/*exec_cmd*/
int					prompt();
void				print_ascii(void);
/*data*/

/*env*/
t_llist				*build_env(char **environ);
int					count_env(t_llist *env);
char				*search_env(t_llist *env, const char *value);
char				**copy_env(void);
void				clear_env(t_llist **env, const char *value);
void				set_env(t_llist **env, t_llist *new);

/*parser and lexer*/
t_mode 				lexer_parser(t_memory *memory);
char				**init_option(char *opt, char **save, int index);
int					operator_filters(char *line);
int					ctrl_var(char *line);
int					my_ctrl(int test);
int					is_bulltin(char *cmd);
int					operator_ctrl(int test);
int					find_str(char *line);
int					ctrl_mode(char *line, t_memory *memory);
int					ctrl_quot(int first, int second);

/*builltin*/
t_llist				*my_setenv();
char				**my_env(t_llist *env);
int					unenv(char *unset, t_llist *env);
int					env_collapse(t_llist *env, const char *value);

/*memory gestion*/
void 				init_memory(void);
void				push_history(void);
void 				end_memory(void);
void				history_path(void);
char				**convert_history(char *path_memory, int lenght);

/*free gestion*/
void				*ft_realloc(void *mem, size_t size);
void				free_d(char **dtab);

/*tools*/
char				*get_pwd(void);
int					reset_fd(int fd, char *new_fd);

#endif
