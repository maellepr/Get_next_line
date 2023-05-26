/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:37:22 by mapoirie          #+#    #+#             */
/*   Updated: 2023/05/26 15:13:14 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;
	char		*line_final;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = ft_line_maker(fd, buf, storage[fd]);
	free(buf);
	if (!line)
		return (NULL);
	storage[fd] = ft_line_extract(line);
	line_final = ft_strdup(line);
	free (line);
	line = NULL;
	return (line_final);
}

char	*ft_line_maker(int fd, char *buf, char *storage)
{
	int		nb_read;
	char	*temp;

	nb_read = read(fd, buf, BUFFER_SIZE);
	while (nb_read > 0)
	{
		buf[nb_read] = '\0';
		if (!storage)
			storage = ft_strdup(buf);
		else
		{
			temp = storage;
			storage = ft_strjoin(storage, buf);
			free(temp);
		}
		if (!storage)
			return (NULL);
		if (ft_check(storage) != -1)
			return (storage);
		nb_read = read(fd, buf, BUFFER_SIZE);
	}
	return (storage);
}

int	ft_check(char *storage)
{
	int	i;

	i = 0;
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_line_extract(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
		return (0);
	temp = ft_strdup(line + i + 1);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (temp);
}

int	main(void)
{
	int		fd;
	int		fd2;
	int		fd3;
	int		fd4;
	char	*line;

	fd = open("texte.txt", O_RDONLY);
	fd2 = open("texte2.txt", O_RDONLY);
	fd3 = open("texte3.txt", O_RDONLY);
	fd4 = open("texte4.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	line = get_next_line(fd3);
	printf("%s", line);
	free(line);
	line = get_next_line(fd4);
	printf("%s", line);
	free(line);
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	line = get_next_line(fd4);
	printf("%s", line);
	free(line);
	
	close(fd);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}
