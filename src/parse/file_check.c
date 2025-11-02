/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:53:18 by djanardh          #+#    #+#             */
/*   Updated: 2025/11/02 18:58:58 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// handle comments in the .rt file
// limits for cy height dia, sp dia, xyz coords? (dia & height - i check if > 0)

// free all the structs in the end? gc or ...?

int	is_line_empty_or_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

int	check_type_identifier(char *line, t_found_elements *found)
{
	if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
	{
		if (line[0] == 'A' && found->ambient)
			return (printf("Error\nDuplicate Ambient element\n"), 1);
		if (line[0] == 'C' && found->camera)
			return (printf("Error\nDuplicate Camera element\n"), 1);
		if (line[0] == 'L' && found->light)
			return (printf("Error\nDuplicate Light element\n"), 1);
		if (line[0] == 'A')
			found->ambient = 1;
		else if (line[0] == 'C')
			found->camera = 1;
		else if (line[0] == 'L')
			found->light = 1;
		return (0);
	}
	if (line[0] && line[1])
	{
		if (line[0] == 'p' && line[1] == 'l')
			return (found->pl_count++, 0);
		else if (line[0] == 's' && line[1] == 'p')
			return (found->sp_count++, 0);
		else if (line[0] == 'c' && line[1] == 'y')
			return (found->cy_count++, 0);
	}
	return (printf("Error\nInvalid type identifier: %.2s\n", line), 1);
}

int	check_line_format(char *line)
{
	int		count;
	char	**split_strs;
	int		valid;

	split_strs = ft_split(line, ' ');
	if (!split_strs)
		return (printf("Error\nMemory allocation for ft_split failed\n"), 1);
	count = count_split(split_strs);
	free_split(split_strs);
	if (count == -1)
		return (printf("Error counting params\n"), 1);
	valid = 0;
	if (line[0] == 'A' && count == 3)
		valid = 1;
	else if (line[0] == 'C' && count == 4)
		valid = 1;
	else if (line[0] == 'L' && count == 3)
		valid = 1;
	else if (line[0] == 's' && line[1] == 'p' && count == 4)
		valid = 1;
	else if (line[0] == 'p' && line[1] == 'l' && count == 4)
		valid = 1;
	else if (line[0] == 'c' && line[1] == 'y' && count == 6)
		valid = 1;
	if (!valid)
		return (printf("Error\nIncorrect no. of params for %.2s\n", line), 1);
	return (0);
}

void strip_newline(char *line)
{
	int i;
	
	if (!line)
		return;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
		{
			line[i] = '\0';
			break;
		}
		i++;
	}
}

int	parse_scene_file(const char *filename, t_scene *scene)
{
	int					fd;
	char				*line;
	int					found_valid_line;
	t_found_elements	found;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	ft_memset(&found, 0, sizeof(t_found_elements));
	found_valid_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (!is_line_empty_or_whitespace(line))
		{
			if (check_type_identifier(line, &found) != 0)
				return (free(line), close(fd), 1);
			if (check_line_format(line) != 0)
				return (free(line), close(fd), 1);
			if (parse_elements(line, scene) != 0)
			{
				free(line);
				close(fd);
				return (printf("Error\nParseElements prob in %.2s\n", line), 1);
			}
			found_valid_line = 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!found_valid_line)
		return (printf("Error\nFile is empty or contains only whitespace\n"),
			1);
	if (!found.ambient)
		return (printf("Error\nMissing Ambient element\n"), 1);
	if (!found.camera)
		return (printf("Error\nMissing Camera element\n"), 1);
	if (!found.light)
		return (printf("Error\nMissing Light element\n"), 1);
	return (0);
}

int	check_input(int ac, char **av, t_scene *scene)
{
	int		file_len;
	char	*temp;

	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	file_len = ft_strlen(av[1]);
	if (file_len < 4)
		return (printf("Error\nInvalid filename\n"), 1);
	temp = ft_substr(av[1], file_len - 3, 3);
	if (!temp)
		return (printf("Error\nMemory allocation failed\n"), 1);
	if (ft_strncmp(temp, ".rt", 3) != 0)
	{
		free(temp);
		return (printf("Error\nInvalid file extension\n"), 1);
	}
	free(temp);
	if (parse_scene_file(av[1], scene) != 0)
		return (1);
	return (0);
}
