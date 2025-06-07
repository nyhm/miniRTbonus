/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:52 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 19:30:40 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

// t_color		parse_color(char *str);
static int	is_empty_or_comment(char *line);
static void	dispatch_parse(t_scene *scene, char **tokens);
static void	parse_line(char *line, t_scene *scene);
// void		parse_rt_file(const char *filename, t_scene *scene);

t_color	parse_color(char *str)
{
	t_color	color;
	char	**rgb_tokens;

	color = (t_color){0, 0, 0};
	rgb_tokens = ft_split(str, ',');
	if (!rgb_tokens)
		return (color);
	if (!rgb_tokens[0] || !rgb_tokens[1] || !rgb_tokens[2])
	{
		free_split(rgb_tokens);
		ft_error("Error: color values (r, g, b) must be between 0 and 255\n");
	}
	color.r = ft_atoi(rgb_tokens[0]);
	color.g = ft_atoi(rgb_tokens[1]);
	color.b = ft_atoi(rgb_tokens[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		free_split(rgb_tokens);
		ft_error("Error: color values must be between 0 and 255\n");
	}
	free_split(rgb_tokens);
	return (color);
}

static int	is_empty_or_comment(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (1);
	if (line[i] == '#')
		return (1);
	if (line[i] == '\n')
		return (1);
	return (0);
}

static void	dispatch_parse(t_scene *scene, char **tokens)
{
	while (*tokens)
	{
		if (ft_strcmp(tokens[0], "A") == 0) // ft_strlen()も組み合わせないと危険！
			parse_ambient(scene, &tokens);
		else if (ft_strcmp(tokens[0], "C") == 0)
			parse_camera(scene, &tokens);
		else if (ft_strcmp(tokens[0], "L") == 0)
			parse_light(scene, &tokens);
		else if (ft_strcmp(tokens[0], "sp") == 0)
			parse_sphere(scene, &tokens);
		else if (ft_strcmp(tokens[0], "pl") == 0)
			parse_plane(scene, &tokens);
		else if (ft_strcmp(tokens[0], "cy") == 0)
			parse_cylinder(scene, &tokens);
		else
			tokens++;
	}
}

static void	parse_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (is_empty_or_comment(line))
		return ;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_split(tokens);
		return ;
	}
	dispatch_parse(scene, tokens);
	free_split(tokens);
}

void	parse_rt_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	int has_read; // bool?
	has_read = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		has_read = 1;
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!has_read)
		ft_error("Error: file is empty or not readable\n");
}
