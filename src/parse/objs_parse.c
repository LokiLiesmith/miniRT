/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:23:17 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 21:10:40 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// identifier: sp
// x, y, z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in the range [0-255]: 10, 0, 255
int	parse_sp(char **strs, t_object *objects)
{
    
}

// identifier: pl
// x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
// 3D normalized normal vector, in the range [-1,1] for each x, y, z axis:
// 0.0,1.0,0.0
// R,G,B colors in the range [0-255]: 0,0,225
int	parse_pl(char **strs, t_object *objects)
{
}

// identifier: cy
// x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y,
// z axis: 0.0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R, G, B colors in the range [0,255]: 10, 0, 255
int	parse_cy(char **strs, t_object *objects)
{
}
