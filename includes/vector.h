/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:21:29 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/07 14:22:29 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_dvector{
    double x;
    double y;
}   t_dvector;

typedef struct s_fvector{
    float x;
    float y;
}   t_fvector;

typedef struct s_vector{
    unsigned int x;
    unsigned int y;
}   t_vector;

#endif