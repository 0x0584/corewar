/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmtypes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:12:50 by archid-           #+#    #+#             */
/*   Updated: 2021/01/21 17:47:19 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMTYPES_H
# define VMTYPES_H

#include "libft.h"
#include "hash.h"
#include "lst.h"
#include "op.h"

typedef enum	e_state
{
	st_error = -1,
	st_succ,
	st_fail
}				t_st;

typedef t_u8	t_byte;
typedef t_byte	t_memory[MEM_SIZE];
typedef t_byte	*t_cor;
typedef t_byte	*t_addr;


#endif
