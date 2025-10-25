/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:53:18 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/25 21:15:42 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// If any misconfiguration of any kind is encountered in the file,
// the program must exit
// properly and return "Error\n" followed by an explicit error message of your choice.

// Your program must take as its first argument a scene description file with the .rt
// extension.
// ◦ Each type of element can be separated by one or more line breaks.
// ◦ Each type of information from an element can be separated by one or more
// spaces.
// ◦ Each type of element can be set in any order in the file.
// ◦ Elements defined by a capital letter can only be declared once in the scene.


// handle comments in the .rt file
// check values (within limits or not)
typedef struct s_found_elements
{
	int	ambient;
	int	camera;
	int	light;
	int	sp_count;
	int	pl_count;
	int	cy_count;
}		t_found_elements;

int	is_line_empty_or_whitespace(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0); // not empty
		line++;
	}
	return (1); // only whitespace
}

int	check_type_identifier(char *line, t_found_elements *found)
{
	// Single character identifiers
	if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
	{
		// Check for duplicates
		if (line[0] == 'A' && found->ambient)
			return (printf("Error\nDuplicate Ambient element\n"), 1);
		if (line[0] == 'C' && found->camera)
			return (printf("Error\nDuplicate Camera element\n"), 1);
		if (line[0] == 'L' && found->light)
			return (printf("Error\nDuplicate Light element\n"), 1);
		// Mark as found
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

void	free_split(char **split_strs, int count)
{
	if (!split_strs)
		return ;
	while (count--)
		free(split_strs[count]);
	free(split_strs);
}

int	count_split(char **split_strs)
{
	int	count;

	if (!split_strs)
		return (-1);
	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

int	validate_line_format(char *line, t_found_elements *found)
{
	int		count;
	char	**split_strs;
	int		valid;

	split_strs = ft_split(line.' ');
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

int	parse_scene_file(const char *filename)
{
	int					fd;
	char				*line;
	int					found_valid_line;
	t_found_elements	found;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	found = (t_found_elements){0, 0, 0, 0, 0, 0};
	found_valid_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_line_empty_or_whitespace(line))
		{
			if (check_type_identifier(line, &found) != 0)
			{
				free(line);
				close(fd);
				return (1);
			}
			if (validate_line_format(line, &found) != 0)
			{
				free(line);
				close(fd);
				return (1);
			}
			// TODO: Add actual parsing of values here
			found_valid_line = 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!found_valid_line)
		return (printf("Error\nFile is empty or contains only whitespace\n"),
			1);
	// Check if mandatory elements are present
	if (!found.ambient)
		return (printf("Error\nMissing Ambient element\n"), 1);
	if (!found.camera)
		return (printf("Error\nMissing Camera element\n"), 1);
	if (!found.light)
		return (printf("Error\nMissing Light element\n"), 1);
	return (0);
}

int	check_input(int ac, char **av)
{
	int		file_len;
	char	*temp;

	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	file_len = ft_strlen(av[1]);
	if (file_len < 4)
		return (printf("Error\nInvalid filename\n"), 1);
	// Check if extension is correct
	temp = ft_substr(av[1], file_len - 3, 3);
	if (!temp)
		return (printf("Error\nMemory allocation failed\n"), 1);
	if (ft_strncmp(temp, ".rt", 3) != 0)
	{
		free(temp);
		return (printf("Error\nInvalid file extension\n"), 1);
	}
	free(temp);
	if (parse_scene_file(av[1]) != 0)
		return (1);
	return (0);
}
