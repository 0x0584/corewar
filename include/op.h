/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:12:50 by archid-           #+#    #+#             */
/*   Updated: 2021/02/01 19:31:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <assert.h>

# include "hash.h"
# include "lst.h"

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

# define T_PAD					0
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

/**
** \brief some chunks read a short, some read `REG_SIZE`
**
**   `op_zjmp`, `op_live`, `op_fork`, `op_lfork` have a `SHORT_CHUNK`
*/
# define SHORT_CHUNK			0x4000

/**
** \brief all operations have an encoding byte
**
**   *except* `op_zjmp`, `op_live`, `op_fork`, `op_lfork`
*/
# define ENCODED_OP				0x2000

/**
** \brief some operations access a memory range with an `IDX_MOD`.
** Long opeartions does't not.
*/
# define LONG_OP				0x1000

/**
** \brief return status of all vm routines
*/
typedef enum				e_state
{
    /**
    ** \brief in case of a fatal error, such as a failure of a syscall
    */
    st_error = -1,

    /**
    ** \brief in case of a success, such as the callee did what the caller
    ** expected
    */
    st_succ,

    /**
    ** \brief in case of an error, but not fatal. such as an illegal execute of
    ** an operation
    */
    st_fail
}							t_st;

/**
** \brief each `.cor` file must have a valid header
*/
typedef struct				s_header
{
	/**
	** \brief a 4-Bytes indicator
	*/
	t_u32		magic;

	/**
	** \brief a program name has at most `PROG_NAME_LENGTH`
	**
	**   padded with `\0` if less
	*/
	t_u8		prog_name[PROG_NAME_LENGTH + 1];

	/**
	** \brief 4-Bytes indicating the total program size
	**
	**   excluding `magic`, `prog_name` and `comment`
	*/
	t_u32		prog_size;

	/**
	 ** \brief program comment is at most `COMMENT_LENGTH`
	 **
	 **   also padded with `\0` if less
	 */
	t_u8		comment[COMMENT_LENGTH + 1];
}							t_header;

/**
** \brief all information about the operation
**
**   the arguments and if it is encoded, chunk_size
*/
typedef union				u_op_meta
{
	/**
	** \brief the encoding used a 16-bit big endian integer
	*/
	t_u16		meta;

	/**
	 ** \brief meta data
	 **    padding  chunk size  encoded  long           args
	 **    [00000]  [0]         [0]      [0]    [0000 | 0000 | 0000]
	 */
	struct					s_meta
	{
		t_u8		arg_t_1:4;
		t_u8		arg_t_2:4;
		t_u8		arg_t_3:4;
	    bool		long_op:1;
	    bool		encoded:1;
	    bool		short_chunk:1;
		t_u8		padding:4;
		bool		carry:1;
	}			of;
}							t_op_meta;

/**
** \brief arguments encoding is reversed because the encoding byte
** is big endian
*/
typedef union				u_op_encoding
{
	/**
	** \brief operation that takes one argument does *not* have an ecoding byte
	**
	**   except `aff`
	*/
	t_u8		encod;

	/**
	** \brief encoding byte has big endianess
	*/
	struct					s_op_encoding
	{
		t_u8		padding:2;
		t_u8		arg_3:2;
		t_u8		arg_2:2;
		t_u8		arg_1:2;
	}			args;
}							t_op_encoding;

/**
** \brief to represent direct and indirect values with a common structure.
** some operations have a `label_size`.
*/
typedef union				u_blob
{
	/**
	 ** \brief at most an argument of size `REG_SIZE` is read/written
	 */
	t_u32		v[MAX_ARGS_NUMBER];

	union				    u_chunk
	{
		/**
		** \brief argument value as a Big Endian integer
		*/
		t_u32		value;

		/**
		** \brief arguments value is reversed because the encoding byte
		** is big endian
	    */
		struct				s_fragment
		{
			t_u8		byte_4;
			t_u8		byte_3;
			t_u8		byte_2;
			t_u8		byte_1;
		}			val;
	}		    b[MAX_ARGS_NUMBER];
}							t_blob;

/**
** \brief each created process is a node of `g_pool`.
**
**   it carries an opeartion a if executed by vm_loop() after
**   waiting for a number of cycles
**
** \see process.h
*/
typedef struct s_process	*t_proc;

#endif
