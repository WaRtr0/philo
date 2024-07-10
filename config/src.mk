# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 00:16:37 by mmorot            #+#    #+#              #
#    Updated: 2024/07/11 00:16:40 by mmorot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### / ###

SRCS += main.c

### /utils ###

SRCS += utils/ft_atoi.c
SRCS += utils/ft_put.c
# SRCS += utils/ft_str.c
SRCS += utils/ft_calloc.c
SRCS += utils/ft_get_time.c

### /philo ###

SRCS += philo/create.c
SRCS += philo/manipulate.c
SRCS += philo/usleep.c
SRCS += philo/routine.c
SRCS += philo/print_status.c

### / fork ###

SRCS += fork/manipulate.c
SRCS += fork/destroy.c