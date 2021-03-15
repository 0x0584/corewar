/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:24 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 14:43:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_st		handle_cmd(t_u8 *buff, size_t length,
							const char *cmd, const char *line)
{
	size_t			i;

	i = 0;
	while (i < length && line[i] && line[i] != '\"')
	{
		buff[i] = line[i];
		i++;
	}
	if (i == length)
		return (st_log(st_error, 2, "exceeding the maximum length %d of %s",
					length, cmd));
	else if (!line[i])
		return (st_log(st_error, 2, "unknown delimiter"));
	else
	{
		g_header_status++;
		return (st_succ);
	}
}

static t_st		match_cmd(t_u8 *buff, size_t length,
							const char *cmd, const char *line)
{
	size_t			len;

	len = ft_strlen(cmd);
	if (ft_strncmp(line, cmd, len))
		return (st_fail);
	line += len;
	if (!ft_isspace(*line++))
		return (st_log(st_error, 2, "no space after command"));
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (st_log(st_error, 2, "end of line before command arg"));
	else if (*line++ == '\"')
	{
		return (handle_cmd(buff, length, cmd, line));
	}
	else
	{
		ft_dprintf(2, "%{red_fg}wrong delimiter%{reset}\n");
		return (st_error);
	}
}

t_st			match_name(const char *line)
{
	t_st			st;

	if ((st = match_cmd(g_name, PROG_NAME_LENGTH, NAME_CMD_STRING, line)))
		return (st);
	else if (st == st_succ)
	{
		if (g_header_status != 1)
		{
			ft_dprintf(2, "%{red_fg}name command appeared twice%{reset}\n");
			return (st_error);
		}
		else
			return (st_succ);
	}
	else
		return (st_fail);
}

t_st			match_comment(const char *line)
{
	t_st			st;

	if ((st = match_cmd(g_champ.comment, COMMENT_LENGTH,
							COMMENT_CMD_STRING, line)))
		return (st);
	else if (st == st_succ)
	{
		if (g_header_status != 2)
			return (st_log(st_error, 2, "comment command appeared twice"));
		else
			return (st_succ);
	}
	else
		return (st_fail);
}
