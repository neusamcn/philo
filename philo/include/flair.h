/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flair.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:27:47 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/07/16 23:38:16 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAIR_H
# define FLAIR_H

/* ANSI color codes */
// TODO: add color reset mode
# define HOT_PINK        "\x1b[38;2;255;105;180m"
# define DEEP_PINK       "\x1b[38;2;255;20;147m"
# define LIGHT_PINK      "\x1b[38;2;255;182;193m" // banner

/* PALE VIOLED READ */
# define ERR             "\x1b[38;2;219;112;147m"
# define ORCHID          "\x1b[38;2;218;112;214m"
# define MEDIUM_ORCHID   "\x1b[38;2;186;85;211m"
# define VIOLET          "\x1b[38;2;238;130;238m"
# define PLUM            "\x1b[38;2;221;160;221m"
# define MAGENTA         "\x1b[38;2;255;0;255m"
# define PURPLE          "\x1b[38;2;128;0;128m"
# define MEDIUM_PURPLE   "\x1b[38;2;147;112;219m"
# define BLUE_VIOLET     "\x1b[38;2;138;43;226m"
# define DARK_VIOLET     "\x1b[38;2;148;0;211m"
# define REBECCA_PURPLE  "\x1b[38;2;102;51;153m"
# define INDIGO          "\x1b[38;2;75;0;130m"
# define CLR_RST     "\x1b[0m"

# define BANNER          "\n\
                    __ \n\
         .,-;-;-,. /'_\\ \n\
       _/_/_/_|_\\_\\) / \n\
     '-<_><_><_><_>=/\\ \n\
       `/_/====/_/-'\\_\\ \n\
        \"\"     \"\"    \"\" \n\n"

#endif