/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagashi <hnagashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:46:52 by hnagashi          #+#    #+#             */
/*   Updated: 2025/06/07 19:30:28 by hnagashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_color	parse_color(char *str);
int		is_empty_or_comment(char *line);
void	dispatch_parse(t_scene *scene, char **tokens);
void	parse_rt_file(const char *filename, t_scene *scene);

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
		ft_error("Error: color values must be between 0 and 255");
	}
	free_split(rgb_tokens);
	return (color);
}

int	is_empty_or_comment(char *line)
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

void	dispatch_parse(t_scene *scene, char **tokens)
{
	size_t	count_tokens;

	count_tokens = count_array(tokens);
	while (*tokens)
	{
		if (ft_strcmp(tokens[0], "A") == 0)
			ambient_token(scene, &tokens, count_tokens);
		else if (ft_strcmp(tokens[0], "C") == 0)
			camera_token(scene, &tokens, count_tokens);
		else if (ft_strcmp(tokens[0], "L") == 0)
			light_token(scene, &tokens, count_tokens);
		else if (ft_strcmp(tokens[0], "sp") == 0)
			sp_token(scene, &tokens, count_tokens);
		else if (ft_strcmp(tokens[0], "pl") == 0)
			plane_token(scene, &tokens, count_tokens);
		else if (ft_strcmp(tokens[0], "cy") == 0)
			cy_token(scene, &tokens, count_tokens);
		else
			tokens++;
	}
}

void	parse_line(char *line, t_scene *scene)
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
	int		has_read;

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
