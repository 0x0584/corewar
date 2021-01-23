/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmtypes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:12:50 by archid-           #+#    #+#             */
/*   Updated: 2021/01/23 11:01:13 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMTYPES_H
# define VMTYPES_H

#include "libft.h"
#include "hash.h"
#include "lst.h"
#include "op.h"

/**
** \brief return status of all vm routines
*/
typedef enum	e_state
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
}				t_st;

/**
** \brief a Byte is 8-bits
*/
typedef t_u8	t_byte;

/**
** \brief memory is circular
**
** long operations access memory via a `MEM_SIZE` mod
** while regular operations use `IDX_MODE` mod
*/
typedef t_byte	t_memory[MEM_SIZE];

/**
** \brief a core file is a blob
*/
typedef t_byte	t_cor[CHAMP_MAX_SIZE];

/**
** \brief an address is a pointer on a byte in the memory
*/
typedef t_byte	*t_addr;

#endif
