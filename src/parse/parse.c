/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:53:18 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/19 21:48:39 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int is_line_empty_or_whitespace(const char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
            return (0); // not empty
        line++;
    }
    return (1); // only whitespace
}

int parse_scene_file(const char *filename)
{
    int fd;
	fd = open(filename, O_RDONLY);
    if (fd < 0)
       return (perror("Error opening file"), 1);

    char *line;
    int found_valid_line = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!is_line_empty_or_whitespace(line))
        {
            // implement validation per line: Call your actual parser here to validate the line
            // e.g., parse_camera(), parse_sphere(), etc.

            found_valid_line = 1;
        }

        free(line);
    }
    close(fd);
    if (!found_valid_line)
		return (printf("Error: File is empty or contains only whitespace\n"), 1);
    return (0);
}

int	check_input(int ac, char **av)
{
	int		file_len;
	char	*temp;
	
	if (ac != 2)
		return (printf("Usage: './miniRT scene_file.rt'\n"), 1);
	file_len = ft_strlen(av[1]);
	// minimum one char for file name?
	if (file_len < 4)
		return (printf("Invalid filename\n"), 1);
	// check if extension is correct (assuming it is case-sensitive?)
	temp = ft_substr(av[1], file_len - 3, 3);
	if (ft_strncmp(temp, ".rt", 3) != 0)
		return (printf("Invalid file extension\n"), 1);
	free(temp);
    if (parse_scene_file(av[1]) != 0)
		return (1);
	return (0);
}
