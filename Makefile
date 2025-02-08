# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 08:12:50 by abonneau          #+#    #+#              #
#    Updated: 2025/02/08 01:09:51 by abonneau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINILIBX_FLAGS = -L $(MINILIBX_FOLDER) -lmlx -lXext -lX11 -lm -fastno-math -o3 -march=native