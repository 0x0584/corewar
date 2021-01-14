/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2021/01/14 09:39:36 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# include "types.h"

# define IND_SIZE				2
# define REG_SIZE				1
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4

/*
** MEM_SIZE = 1024 * 4
*/
# define MEM_SIZE				4096

/*
** MEM_SIZE / 8 = 512
*/
# define IDX_MOD				512

/*
** MEM_SIZE / 6 = 682
*/
# define CHAMP_MAX_SIZE			682

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR2		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char			t_arg_type;

/*
** 0b0001
*/
# define T_REG					1

/*
** 0b0010
*/
# define T_DIR					2

/*
** 0b0100
*/
# define T_IND					4

/*
** 0b1000
*/
# define T_LAB					8

typedef struct			s_header
{
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xEA83F3

	t_u32	magic;
	char	prog_name[PROG_NAME_LENGTH + 1];
	t_u32	prog_size;
	char	comment[COMMENT_LENGTH + 1];
}						t_header;


typedef struct			s_op
{
	union
	{
		enum
		{
			OP_LIVE = 1,	OP_LOAD,			OP_STORE,
			OP_ADD,			OP_SUB,				OP_AND,
			OP_OR,			OP_XOR,				OP_ZJMP,
			OP_LOAD_INDEX,	OP_STORE_INDEX,		OP_FORK,
			OP_LONG_LOAD,	OP_LONG_LOAD_INDEX,
			OP_LONG_FORK,	OP_AFF,

			OP_COUNT
		}		code;
		t_u8	opcode;
	};
	t_u8			decode_byte;
	union				u_argument
	{
		t_u16	u16;
		t_s16	i16;
		t_u32	u32;
		t_s32	i32;
	}				args[MAX_ARGS_NUMBER];
} t_op;

#endif
