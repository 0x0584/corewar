/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:12:50 by archid-           #+#    #+#             */
/*   Updated: 2021/02/10 15:54:05 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "const.h"

# include "hash.h"
# include "lst.h"

/**
** \brief all information about the operation
**
**   the arguments and if it is encoded, chunk_size
*/
typedef union				u_op_meta
{
	/**
	** \brief the encoding used a 16-bit little endian integer
	**
	**   this is defined only in the code base and doesn't *not* relate to
	**   the actual binary (`.cor` file)
	*/
	t_u16		meta;

	/**
	** \brief meta data of the opeartion
    */
	struct					s_meta
	{
		/**
		** \brief expected type for the first argument
		**
		**	all operations hat least one argument
	    */
		t_u8		arg1_t:4;

		/**
		** \brief type of the second argument
		**
		**   some oprations have only two arguments
		**   the third is used along as a type extension
	    */
		t_u8		arg2_t:4;

		/**
		** \brief third argument type
		**
		**	all operations hat least one argument
	    */
		t_u8		arg3_t:4;

		/**
		** \brief some operations access a memory range with an `IDX_MOD`.
		** Long opeartions does't not.
	    */
	    bool		long_op:1;

		/**
	    ** \brief all operations have an encoding byte
		**
		**   *except* `op_zjmp`, `op_live`, `op_fork`, `op_lfork`
		*/
	    bool		encoded:1;

		/**
		** \brief some chunks read a short, some read `REG_SIZE`
		**
		**   `op_zjmp`, `op_live`, `op_fork`, `op_lfork` have a `SHORT_CHUNK`
	    */
	    bool		short_chunk:1;

		/**
		** \brief only certain opeartions modify the carry
		**
		**   namely ALU and read operations
	    */
		bool		carry:1;

		/**
		** \brief complete a full 16-bit word
	    */
		t_u8		padding:4;
	}			of;
}							t_op_meta;

/**
** \brief each opeartion have an expected type for each argument
** defined as `t_meta`, so `t_arg` is used to index individual
** arguments
**
** also arguments are stored as a `t_blob` and have a relative `t_encoding`
**
** \see op_impl.h
*/
typedef t_u8				t_arg;

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
**
** byte_1 of each argument has the `t_arg`
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
		** \brief argument value as a Big Endian 32-bit integer
		*/
		t_u32		u32;

		/**
		 ** \breif argument value as a Big Endian 16-bit integer
		 */
		t_u16		u16;

		/**
		** \brief arguments value is reversed because the encoding byte
		** is big endian
	    */
		struct				s_fragment
		{
			t_u8		byte_1;
			t_u8		byte_2;
			t_u8		byte_3;
			t_u8		byte_4;
		}			val;
	}			c[MAX_ARGS_NUMBER];
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

/**
** \brief handy hard-written utility to probe the encoding of a `t_op_encoding`
**
** \param op pointer an operation held by a process
** \param which argument to get encoding for
**
** \see op.h
** \see op_impl.h
**
** \return a Byte containing the encoding
*/
t_arg		op_encoding(t_proc p, t_arg which);

t_arg		op_meta_encoding(t_proc p, t_arg which);

t_arg		encoded(t_u8 arg);

t_u32		get_arg_value(t_proc proc, t_arg arg);

/**
** \brief reverse a word (32-bit) from little endian to big endian
**
** \param word little endian word
**
** \return big endian word
*/
t_u32				beword(t_u32 word);

/**
** \brief reverse a byte (8-bits) from little endian to big endian
**
** \param word little endian byte
**
** \return big endian byte
*/
t_u8				bebyte(t_u8 byte);

#endif
