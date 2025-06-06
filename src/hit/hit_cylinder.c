/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 06:32:32 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/05 18:34:42 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int		select_closest_hit(double *t_candidates, int count, double *t_hit);
int		check_side_hit(t_cylinder_hit *hit, double t_side);
void	calc_cylinder_quadratic(t_cylinder_hit *hit, t_quadratic *q);
int		hit_cylinder_side(t_cylinder_hit *hit);
int		check_cap_hit(t_cap_hit *info);

int	check_side_hit(t_cylinder_hit *hit, double t_side)
{
	t_vec3	p;
	double	h;

	if (t_side > 0.001)
	{
		p = vec_add(hit->ray.origin, vec_mul(hit->ray.direction, t_side));
		h = vec_dot(vec_sub(p, hit->cy->center), hit->cy->direction);
		if (h >= 0 && h <= hit->cy->height)
			hit->t_candidates[hit->count++] = t_side;
	}
	return (hit->count);
}

int	select_closest_hit(double *t_candidates, int count, double *t_hit)
{
	int		i;
	double	closest;

	if (count <= 0)
		return (0);
	closest = -1;
	i = 0;
	while (i < count)
	{
		if (t_candidates[i] > 0.001)
		{
			if (closest < 0 || t_candidates[i] < closest)
				closest = t_candidates[i];
		}
		i++;
	}
	if (closest < 0)
		return (0);
	*t_hit = closest;
	return (1);
}

void	calc_cylinder_quadratic(t_cylinder_hit *hit, t_quadratic *q)
{
	t_vec3	ca;
	t_vec3	oc;
	t_vec3	dir_proj;
	t_vec3	oc_proj;

	ca = hit->cy->direction;
	oc = vec_sub(hit->ray.origin, hit->cy->center);
	dir_proj = vec_sub(hit->ray.direction, vec_mul(ca,
				vec_dot(hit->ray.direction, ca)));
	oc_proj = vec_sub(oc, vec_mul(ca, vec_dot(oc, ca)));
	q->a = vec_dot(dir_proj, dir_proj);
	q->b = 2.0 * vec_dot(dir_proj, oc_proj);
	q->c = vec_dot(oc_proj, oc_proj) - hit->cy->radius * hit->cy->radius;
	q->discriminant = q->b * q->b - 4.0 * q->a * q->c;
}

int	hit_cylinder_side(t_cylinder_hit *hit)
{
	t_quadratic	q;

	hit->count = 0;
	calc_cylinder_quadratic(hit, &q);
	if (q.discriminant >= 0 && q.a > 1e-12)
	{
		q.sqrt_discriminant = sqrt(q.discriminant);
		q.t0 = (-q.b - q.sqrt_discriminant) / (2.0 * q.a);
		q.t1 = (-q.b + q.sqrt_discriminant) / (2.0 * q.a);
		hit->count = check_side_hit(hit, q.t0);
		hit->count = check_side_hit(hit, q.t1);
	}
	return (hit->count);
}

int	check_cap_hit(t_cap_hit *info)
{
	double	denom;
	double	t_plane;
	t_vec3	p;
	t_vec3	v;
	double	dist2;

	denom = vec_dot(info->normal, info->ray.direction);
	if (fabs(denom) < 1e-6)
		return (info->count);
	t_plane = vec_dot(vec_sub(info->center, info->ray.origin), info->normal)
		/ denom;
	if (t_plane < 0.001)
		return (info->count);
	p = vec_add(info->ray.origin, vec_mul(info->ray.direction, t_plane));
	v = vec_sub(p, info->center);
	dist2 = vec_len2(vec_sub(v, vec_mul(info->normal, vec_dot(v,
						info->normal))));
	if (dist2 <= info->radius * info->radius)
		info->t_candidates[info->count++] = t_plane;
	return (info->count);
}
