/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2021/01/27 14:24:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef OP_H
#define OP_H

# include "types.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

typedef char		t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
  t_u32		magic;
  t_u8		prog_name[PROG_NAME_LENGTH + 1];
  t_u32		prog_size;
  t_u8		comment[COMMENT_LENGTH + 1];
}					t_header;

# define OP_LIVE 0x01
# define OP_LOAD 0x02
# define OP_STORE 0x03

# define OP_ADD 0x04
# define OP_SUB 0x05
# define OP_AND 0x06

# define OP_OR 0x07
# define OP_XOR 0x08
# define OP_ZJMP 0x09

# define OP_LOAD_INDEX 0x0a
# define OP_STORE_INDEX 0x0b
# define OP_FORK 0x0c

# define OP_LONG_LOAD 0x0d
# define OP_LONG_LOAD_INDEX 0x0e

# define OP_LONG_FORK 0x0f
# define OP_AFF 0x10

/**
** \brief union to retrieve the argument encoding from the encoding byte
*/
typedef union	u_args_encoding
{
	/**
	** \brief the encoding byte is big endian
	*/
	t_u8	encoding;

	/**
	** \brief arguments encoding is reverse because the encoding byte
	** is big endian
	*/
	struct		s_args
	{
		t_u8		arg_padding:2;
		t_u8		arg_3:2;
		t_u8		arg_2:2;
		t_u8		arg_1:2;
	}		arg_encoding;
}				t_args_encoding;

#endif
