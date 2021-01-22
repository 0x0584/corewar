/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:09:42 by archid-           #+#    #+#             */
/*   Updated: 2021/01/22 16:12:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vmtypes.h"
# include "address.h"


typedef struct s_process	t_proc;
typedef struct s_player		t_player;

struct						s_process
{
# define PROCESS_CLEANUP_AFTER 0x80 /* size after which re-allocate the hashtable */
    pid_t	pid;			   /* process id of the parent (player) */
    t_u8	num;			   /* player number */
    t_hash	children;		   /* stack of process */
};

struct						s_player
{
	t_header	hdr;			/* file header */
	t_cor		file;			/* the foo.cor */
	t_proc		prog;			/* process on which the player executes instructions */

	t_addr		pc;				/* program counter */
	t_addr		mar;			/* memory address register */
};

extern bool					g_player_debug;


t_st				player_read(const char *filename, t_player *p);
void				player_dump(t_player *p);
void				player_delete(t_player *p);

#endif
