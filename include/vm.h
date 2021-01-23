/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:27 by archid-           #+#    #+#             */
/*   Updated: 2021/01/23 17:36:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <assert.h>
# include "player.h"

/**
** \brief at most we have `MAX_PLAYERS`
** \see op.h
*/
typedef t_player	t_players[MAX_PLAYERS];

/**
** \brief output the usage of the program to stdout
**
** \return -1 always
*/
int		        	print_usage(void);

/**
** \brief  parse command-line arguments and initialize VM's global variables
**
** \param ac argument counter
** \param av arguments vector
**
** \return `true` if the arguments are correct, `false` otherwise.
*/
bool	        	parse_arguments(int ac, char *av[]);

/**
** \brief this is the instruction cycle for all running processes. it fetches,
** decodes and execute instructions of each process sequentially in
** reverse `t_proc::num` order.
**
** \return `st_succ` in case the game is terminated, `st_error` otherwise.
*/
t_st				vm_loop(void);

/*
** Memory
*/

/**
** \brief load the players into memory from `g_gladiators` and set
** them evenly spaced
**
** \see memory.c
*/
t_st				mem_load(void);

/*
** Clock
*/

/**
** \brief the clock synchronise the running processes based on
** their `t_proc::num`
**
** \return `st_error` in case fetch is not successful. Otherwise`st_succ`
** in case all process have fetched or `st_fail` if they haven't
**
** \see clock.c
*/
t_st				clock_tick(void);

/*
** Global Variables
*/

/**
** \brief the VM's random access memory space
*/
extern t_memory		g_arena;

/**
** \brief number of player read via command line args
*/
extern t_u8			g_nplayers;

/**
** \brief players read via command line arguments
*/
extern t_players	g_gladiators;

/**
** \brief Memory colors
** \see draw.h
*/
extern t_u8			g_memcolors[MEM_SIZE];

/*
** Drawing the memory using ncurses
*/

# include <ncurses.h>

# define DRAW_BUFF_SIZE									0X0F
# define DRAW_LINE_SIZE									0x40
# define DRAW_LINE_WIDTH								0XC0 // SIZE * 3 characters `ff `

/**
** \brief colors used for the drawing where the first variant indicat the player
** move and othe reversed variant indicated that he wrote over some other
** player's memory. it is used for visualizing the war.
**
** Each cell have
**
**		(color of write over) >> [0000][0000] << (owner's color)
**
** using a Byte to represent colors, each memory cell in `g_arena` has a
** correponding color in `g_memcolors` where the first 4 bytes indicate the
** player who has set the memory. at first all memory cells are fresh and
** initialized to `0`.
**
** At first, a player owns the cell by setting his color in the first 4-bits,
** then if another player is to set the cell, if the cell has no owner, then the
** player becomes the owner, else we keep the old owner and add a write over color
** of the player in the next 4-bits.
**
** \see memory.c
*/
enum				e_colors
{
	/* default color */
    color_black_on_white,

	/* player colors */
    color_black_on_red,
    color_blue_on_green,
    color_cyan_on_magenta,
    color_white_on_yellow,

	color_count = color_white_on_yellow,

	/* effects */
    color_red_on_black,
    color_green_on_blue,
    color_magenta_on_cyan,
    color_yellow_on_white,
};

void			    draw_memory(void);
t_u8				color_owner(t_u16 at);
t_u8				color_writer(t_u16 at);

#endif
