/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:38 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/06 22:37:06 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

int	hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit);
int	hit_plane(t_plane *pl, t_ray ray, double *t_hit);
int	calc_sphere_quadratic(t_sphere_hit *hit);
int	hit_sphere(t_sphere *sphere, t_ray ray, double *t_hit);
int	hit_cylinder_caps(t_cylinder_hit *hit);

int	hit_cylinder_caps(t_cylinder_hit *hit)
{
	t_cap_hit	info;

	info.ray = hit->ray;
	info.t_candidates = hit->t_candidates;
	info.count = hit->count;
	info.radius = hit->cy->radius;
	info.normal = hit->cy->direction;
	info.center = hit->cy->center;
	info.count = check_cap_hit(&info);
	info.center = vec_add(hit->cy->center, vec_mul(hit->cy->direction,
				hit->cy->height));
	info.count = check_cap_hit(&info);
	hit->count = info.count;
	return (hit->count);
}

int	hit_cylinder(t_cylinder *cy, t_ray ray, double *t_hit)
{
	t_cylinder_hit	hit;
	double			tmp_candidates[4];
	int				i;

	i = 0;
	while (i < 4)
	{
		tmp_candidates[i] = 0;
		i++;
	}
	hit.cy = cy;
	hit.ray = ray;
	hit.count = 0;
	hit.t_candidates = tmp_candidates;
	hit_cylinder_side(&hit);
	hit_cylinder_caps(&hit);
	return (select_closest_hit(hit.t_candidates, hit.count, t_hit));
}

int	calc_sphere_quadratic(t_sphere_hit *hit)
{
	t_vec3	oc;

	oc = vec_sub(hit->ray.origin, hit->sphere->center);
	hit->a = vec_dot(hit->ray.direction, hit->ray.direction);
	hit->b = 2.0 * vec_dot(oc, hit->ray.direction);
	hit->c = vec_dot(oc, oc) - hit->sphere->radius * hit->sphere->radius;
	hit->discriminant = hit->b * hit->b - 4 * hit->a * hit->c;
	return (hit->discriminant >= 0);
}

int	hit_sphere(t_sphere *sphere, t_ray ray, double *t_hit)
{
	t_sphere_hit	hit;

	hit.sphere = sphere;
	hit.ray = ray;
	if (!calc_sphere_quadratic(&hit))
		return (0);
	hit.t1 = (-hit.b - sqrt(hit.discriminant)) / (2 * hit.a);
	hit.t2 = (-hit.b + sqrt(hit.discriminant)) / (2 * hit.a);
	if (hit.t1 > 0.001)
	{
		*t_hit = hit.t1;
		return (1);
	}
	if (hit.t2 > 0.001)
	{
		*t_hit = hit.t2;
		return (1);
	}
	return (0);
}

int	hit_plane(t_plane *pl, t_ray ray, double *t_hit)
{
	double	denom;
	double	t;

	denom = vec_dot(pl->normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(pl->point, ray.origin), pl->normal) / denom;
		if (t >= 0.001)
		{
			*t_hit = t;
			return (1);
		}
	}
	return (0);
}
