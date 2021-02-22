/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:21:08 by archid-           #+#    #+#             */
/*   Updated: 2021/02/19 16:58:42 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELIMITER_H
# define DELIMITER_H

#include "op.h"

typedef enum	e_op_delimiters
{
	deli_eol			= '\0',

	deli_comment		= COMMENT_CHAR,
	deli_asm_comment	= ';',

	deli_comma			= SEPARATOR_CHAR,
	deli_label	 		= LABEL_CHAR,
	deli_dir	 		= DIRECT_CHAR,
	deli_reg			= 'r',

	deli_bin	 		= 'b',
	deli_octa	 		= '0',
	deli_hexa	 		= 'x',

	deli_unknown		= -1,
}				t_deli;

bool			delimiter(t_deli d);

bool			is_comment_char(t_deli d);

#endif
