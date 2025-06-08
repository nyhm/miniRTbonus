/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:49:40 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/08 10:58:16 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

void	hit_cone_side(t_cone_hit *hit)
{
	t_vec3	co;
	t_vec3	d;
	t_vec3	v;
	double	k;
	double	k2;
	double	dv;
	double	cov;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_d;
	double	t1;
	double	t2;
	t_vec3	p;
	double	h;
	double	radius;

	radius = tan(hit->cone->angle) * hit->cone->height;
	co = vec_sub(hit->ray.origin, hit->cone->apex);
	d = hit->ray.direction;
	v = hit->cone->direction;
	k =radius / hit->cone->height;
	k2 = k * k;
	dv = vec_dot(d, v);
	cov = vec_dot(co, v);
	a = vec_dot(d, d) - (1 + k2) * dv * dv;
	b = 2 * (vec_dot(d, co) - (1 + k2) * dv * cov);
	c = vec_dot(co, co) - (1 + k2) * cov * cov;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	sqrt_d = sqrt(discriminant);
	t1 = (-b - sqrt_d) / (2 * a);
	t2 = (-b + sqrt_d) / (2 * a);
	if (t1 > 0)
	{
		p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, t1));
		h = vec_dot(vec_sub(p, hit->cone->apex), hit->cone->direction);
		if (h > 0 && h < hit->cone->height)
			hit->t_candidates[hit->count++] = t1;
	}
	if (t2 > 0)
	{
		p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, t2));
		h = vec_dot(vec_sub(p, hit->cone->apex), hit->cone->direction);
		if (h > 0 && h < hit->cone->height)
			hit->t_candidates[hit->count++] = t2;
	}
}

void	hit_cone_cap(t_cone_hit *hit)
{
	t_vec3	base_center;
	double	denom;
	double	t;
	t_vec3	p;
	double	dist2;
	double	radius;

	radius = tan(hit->cone->angle) * hit->cone->height;
	base_center = vec_add(hit->cone->apex, vec_mul(hit->cone->direction,
				hit->cone->height));
	denom = vec_dot(hit->ray.direction, hit->cone->direction);
	if (fabs(denom) < 1e-6)
		return ;
	t = vec_dot(vec_sub(base_center, hit->ray.origin), hit->cone->direction)
		/ denom;
	if (t <= 0)
		return ;
	p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, t));
	dist2 = vec_len2(vec_sub(p, base_center));
	if (dist2 <= radius * radius)
		hit->t_candidates[hit->count++] = t;
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
