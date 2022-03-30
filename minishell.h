/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:30:57 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 22:30:57 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define CMD_NOT_FOUND 127
# define CMD_CAN_NOT_EXEC 126
# define SYNTAX_ERROR 258
# define MALLOC_ERROR 333

# define ALL_GOOD 400
# define NOT_VALID 401
# define SAME_KEY 402

typedef struct s_minish	t_minish;
typedef struct s_cmd	t_cmd;

extern int				g_status;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

struct s_cmd
{
	char		*cmd;
	char		**cmd_splited;
	int			rd_fds[2];
	pid_t		pid;
	int			fd_in;
	int			fd_out;
};

struct s_minish
{
	char	*line;
	char	**env;
	t_list	*cmdlst;
};

// util/utils.c
void	*chmllc(void *ptr);
void	set_free(void **var, void *new);
t_list	*create_node(char *cmd, char **cmd_splited);
void	destroy_node(void *content);

// util/cvenkman/cvenkman.c
void	free_arr(char **arr);

// util/cvenkman/change_shell_lvl.c
void	change_shell_lvl(t_minish *minish);

// util/errors.c
int		cmd_not_found(char *cmd, char *str, char *str2);
int		error_builtin(char *str, int fd);
int		command_exit(char *cmd, char *str, int exit_code);
void	perror_exit_bash(char *str);
int		print_sintaxerr(char err_chr);

// util/strarr_utils.c
int		arr_len(char **cmd_splited);
char	**strarr_add(char **arr, size_t arrlen, char *new);
char	**copystr_array(char **arr);

// builtins_and_cmd
int		distribution(t_minish *minish, char **cmd, bool flag_is_pipe);
int		ft_pwd(char **cmd_splited, t_minish *minish);
int		ft_env(char **cmd_splited, char **env, t_minish *minish);
int		run_cmd(char **cmd, char **env);
void	ft_pipes(t_minish *minish, char **env);
int		echo(char **cmd_splited, t_minish *minish);
int		cd(char **cmd_splited, char **env);
int		ft_exit(char **cmd);

// builtins_and_cmd/command.c
void	change_fd_if_redirect(int redirect_fds[2]);
int		ft_command(char **cmd, char **env, t_minish *minish);

// builtins_and_cmd/export_and_unset
int		ft_export(char **cmd_splited, char **env, t_minish *minish);
void	print_export(char **export, t_minish *minish);
int		unset(char **cmd_splited, char **env, t_minish *minish);

// builtins_and_cmd/export_and_unset/export_utils.c
void	not_valid_export(char *cmd, char *str);
void	*return_flag(int *ret);
int		copy_str_for_norminette(char *str, char **export, int *i);

// builtins_and_cmd/export_and_unset/check_valid.c
int		check_valid(char *str, int *ret, char **env);
int		valid_export_len(char **cmd_splited, char **env);
int		all_not_valid(char **cmd_splited, char **env);

int		ft_env_key_len(char *env);

// parser/read_env
int		get_envi(char **env, const char *key);
void	main_signals(void);
void	ctrl_ign(void);
void	signal_pipes_cmd(void);

int		parser(t_minish *minish);
char	*replace_substr(char *str, char *substr, char *replacement, int pos);
char	*shrink_chs_one(char *str, int pos, char ch);
int		read_env(char **str, int pos, char **env);
char	*skip_untill_chr(char *str, char chr);
char	*ft_strchrs(const char *str, const char *chrs);
int		parse_redirect(char **line, int i, t_cmd *cmd, char **env);
int		parse_quotes(char **str, int i, char **env);
char	*substr_till_chr(char *str, char chr, int start);
char	*ft_strldup(const char *str, int len);
char	*chrdup(char ch, unsigned int len);
char	*chstr(char c);
int		parse_heredoc(char *stop_w, char **env);
char	**get_cmd_splited(char *line, t_cmd *cmd,
			char **env, char **cmd_splited);
bool	is_control_chr(char c);
void	divide_by_pipe(t_minish *msh);
int		parse_file_name(char **cmd, int fname_start, char **dst);

#endif
