/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:49:40 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 16:12:42 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

static void	check_cone_t_candidate(t_cone_hit *hit, double t);
void		hit_cone_side(t_cone_hit *hit);
void		hit_cone_cap(t_cone_hit *hit);
int			hit_cone(t_cone *cone, t_ray ray, double *t_hit);

static void	check_cone_t_candidate(t_cone_hit *hit, double t)
{
	t_vec3	p;
	double	h;

	if (t <= 0)
		return ;
	p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, t));
	h = vec_dot(vec_sub(p, hit->cone->apex), hit->cone->direction);
	if (h > 0 && h < hit->cone->height)
		hit->t_candidates[hit->count++] = t;
}

void	hit_cone_side(t_cone_hit *hit)
{
	t_cone_side_hit_vars	vars;

	vars.radius = tan(hit->cone->angle) * hit->cone->height;
	vars.co = vec_sub(hit->ray.origin, hit->cone->apex);
	vars.d = hit->ray.direction;
	vars.v = hit->cone->direction;
	vars.k = vars.radius / hit->cone->height;
	vars.k2 = vars.k * vars.k;
	vars.dv = vec_dot(vars.d, vars.v);
	vars.cov = vec_dot(vars.co, vars.v);
	vars.a = vec_dot(vars.d, vars.d) - (1 + vars.k2) * vars.dv * vars.dv;
	vars.b = 2 * (vec_dot(vars.d, vars.co) - (1 + vars.k2) * vars.dv \
			* vars.cov);
	vars.c = vec_dot(vars.co, vars.co) - (1 + vars.k2) * vars.cov * vars.cov;
	vars.discriminant = vars.b * vars.b - 4 * vars.a * vars.c;
	if (vars.discriminant < 0)
		return ;
	vars.sqrt_d = sqrt(vars.discriminant);
	vars.t1 = (-vars.b - vars.sqrt_d) / (2 * vars.a);
	vars.t2 = (-vars.b + vars.sqrt_d) / (2 * vars.a);
	check_cone_t_candidate(hit, vars.t1);
	check_cone_t_candidate(hit, vars.t2);
}

void	hit_cone_cap(t_cone_hit *hit)
{
	t_cone_cap_hit_vars	vars;

	vars.radius = tan(hit->cone->angle) * hit->cone->height;
	vars.base_center = vec_add(hit->cone->apex, vec_mul(hit->cone->direction, \
				hit->cone->height));
	vars.denom = vec_dot(hit->ray.direction, hit->cone->direction);
	if (fabs(vars.denom) < 1e-6)
		return ;
	vars.t = vec_dot(vec_sub(vars.base_center, hit->ray.origin), \
			hit->cone->direction) / vars.denom;
	if (vars.t <= 0)
		return ;
	vars.p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, vars.t));
	vars.dist2 = vec_len2(vec_sub(vars.p, vars.base_center));
	if (vars.dist2 <= vars.radius * vars.radius)
		hit->t_candidates[hit->count++] = vars.t;
}

int	hit_cone(t_cone *cone, t_ray ray, double *t_hit)
{
	t_cone_hit	hit;
	double		tmp_candidates[4];
	int			i;

	i = 0;
	while (i < 4)
		tmp_candidates[i++] = 0;
	hit.cone = cone;
	hit.ray = ray;
	hit.count = 0;
	hit.t_candidates = tmp_candidates;
	hit_cone_side(&hit);
	hit_cone_cap(&hit);
	return (select_closest_hit(hit.t_candidates, hit.count, t_hit));
}
