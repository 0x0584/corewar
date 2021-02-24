/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:58:40 by archid-           #+#    #+#             */
/*   Updated: 2021/02/24 10:58:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "op_impl.h"
# include "champ.h"

# define MAX_OP_NAME						5

t_st			skip_whitespace(const char **ptr);
t_st			match_name(const char *line);
t_st			match_comment(const char *line);

t_st			parse_line(char **line);
t_st			parse_arg_value(t_op *op, t_arg arg, const char **arg_line);
t_st			parse_op(t_op *op, const char *buff);
t_lst			parse_ops(t_lst lines);

extern t_hash	g_op_lookup;
extern t_champ	g_champ;
extern int		g_header_status;
extern t_u8		g_name[PROG_NAME_LENGTH + 1];

#endif
