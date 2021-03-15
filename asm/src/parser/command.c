/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:22:24 by archid-           #+#    #+#             */
/*   Updated: 2021/03/15 12:04:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_st		match_cmd(t_u8 *buff, size_t length, const char *cmd, const char *line)
{
	size_t			len;
	size_t			i;

	len = ft_strlen(cmd);
	if (ft_strncmp(line, cmd, len))
		return (st_fail);
	line += len;
	if (!ft_isspace(*line++))
	{
		ft_dprintf(2, "%{red_fg}no space after command%{reset}\n");
		return (st_error);
	}
	while (ft_isspace(*line))
		line++;
	if (!*line)
	{
		ft_dprintf(2, "%{red_fg}end of line before command arg%{reset}\n");
		return (st_error);
	}
	else if (*line++ == '\"')
	{
		i = 0;
		while (i < length && line[i] && line[i] != '\"')
		{
			buff[i] = line[i];
			i++;
		}
		if (i == length)
		{
			ft_dprintf(2, "%{red_fg}exceeding the maximum length %d of %s%{reset}\n", length, cmd);
			return (st_error);
		}
		else if (!line[i])
		{
			ft_dprintf(2, "%{red_fg}unknown delimiter%{reset}\n");
			return (st_error);
		}
		else
		{
			g_header_status++;
			return (st_succ);
		}
	}
	else
	{
		ft_dprintf(2, "%{red_fg}wrong delimiter%{reset}\n");
		return (st_error);
	}
}

t_st		match_name(const char *line)
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

t_st		match_comment(const char *line)
{
	t_st			st;

	if ((st = match_cmd(g_champ.comment, COMMENT_LENGTH, COMMENT_CMD_STRING, line)))
		return (st);
	else if (st == st_succ)
	{
		if (g_header_status != 2)
		{
			ft_dprintf(2, "%{red_fg}comment command appeared twice%{reset}\n");
			return (st_error);
		}
		else
			return (st_succ);
	}
	else
		return (st_fail);
}
