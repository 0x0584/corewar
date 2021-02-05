/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 08:33:56 by archid-           #+#    #+#             */
/*   Updated: 2021/02/05 16:57:41 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# include <assert.h>

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

/* # define DEBUG */
/* # ifdef DEBUG */
/* #  define LOGGER(st, fmt, ...)					\ */
/* 	ft_dprintf(2, fmt, #__VA_ARGS__), st */
/* # else */
/* #  define LOGGER(st, fmt, ...)					\ */
/* 	st */
/* # endif */

#  define LOGGER(st, fmt, ...)					\
	ft_dprintf(2, fmt, __VA_ARGS__), st
#endif
