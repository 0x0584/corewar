/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:52:32 by archid-           #+#    #+#             */
/*   Updated: 2021/02/15 11:52:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "vm.h"

/**
** \brief load the players into memory from `t_vm::gladiators` and set
** them evenly spaced, also create a process for each loaded player
**
** \return if succeeded, `st_succ` is return, otherwise `st_error`
**
** \see process.h
*/
void				mem_load(t_u8 player_num, t_player *p, const t_champ *champ);

t_st				handle_chunk(t_proc p, t_arg arg, t_pc *offset);

/**
** \brief write the chunk into the VM's memory realtive to op's meta
**
** \param pc program counter from which we shall start writting
** \param chnk a memory chunk
** \param op operation holding meta data
**
** \see op.h
*/
void				mem_write_chunk(const t_proc p, const union u_chunk *chnk,
									t_pc offset);

/**
 * \brief read from pc relative to offset into operation arg
 *
 * if arg if T_DIR and the operation label is not a short chunk
 * we read T_DIR else we read T_IND
 */
void				mem_read_chunk(const t_proc p, union u_chunk *chnk,
								   bool read_reg_size, t_pc offset);

/**
** \brief read arguments of an operation held by process `p`
** sets tjhe offset of the chunk
**
** \param p process of operation
** \param offset out reference of the chunk offset
**
** \return
**
**   - `st_succ`
*/
t_st				read_arg_chunk(t_proc p, t_pc *offset);

/**
** \brief reads a `chuck_size` relative to the process's program counter
**
**   except registers, which have a `chunk_size` of `REG_SIZE`.
**   It is deduced from the encoding and whether the operation
**   have an `IDX_MOD`
**
**  \param p a reading process holding the program counter
**  \param value a reference to where to write the content
**  \param offset out refernce of program counter offset
*/
void				mem_chunk(t_proc p, t_arg arg, t_pc *offset);

/*
** Accessors
*/

/**
** \brief get the value of the memory address on which the
** program counter is pointing
**
** \param p process holding the program counter
** \param offset from which we shall be reading
**
** \return a byte
*/
t_u8				mem_deref(t_proc p, t_pc offset);

/**
** \brief get the value of the memory address on which the
** program counter is pointing
**
** \param p process holding the program counter
**
** \return a byte
*/
t_u8				mem_at(t_proc p);

t_u8				at_mem(t_pc p);

/*
** Encoding
*/

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
/* t_arg				op_encoding(t_proc p, t_arg which); */

/* t_arg				op_meta_encoding(t_proc p, t_arg which); */

t_arg				encoded(t_u8 arg_code);

t_dir				arg_value(t_proc proc, t_arg arg, bool deref);

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
