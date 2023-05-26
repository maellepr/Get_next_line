/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_OLD.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:50:18 by mapoirie          #+#    #+#             */
/*   Updated: 2023/05/26 09:50:21 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	
	while (buffer[i] && buffer[i] != '\n')
		i++;	
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i = i + 1;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);//malloc ligne 80
	return (new_buffer);
}

char	*ft_cleanline(char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	new_line = ft_calloc(i + 2, sizeof(char));// free dans le main
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	if (line[i] && line[i] == '\n')
		new_line[i++] = '\n';
	return (new_line);
}

char	*ft_join_free(char *line_plus, char *buffer)
{
	char	*buffer_temp;
	
	buffer_temp = ft_strjoin(line_plus, buffer);
	free(line_plus);// free le malloc ligne 77
	return (buffer_temp);
}

char	*ft_read(int fd, char *line_plus)
{
	int		nb_read;
	char	*buffer;

	if (!line_plus)
		line_plus = calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));//free ligne 95 ou ligne 80
	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buffer);
			return(NULL);
		}
		buffer[nb_read] = '\0';
		line_plus = ft_join_free(line_plus, buffer);
		if (ft_strchr(line_plus, '\n'))
			break;
	}
	free(buffer); //malloc ligne 80
	return (line_plus);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 ||  read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_read(fd, buffer);// lit jusqu'a arriver a \n, englobe \n 
	if (!buffer)
		return (NULL);
	line = ft_cleanline(buffer);// a partir de ft_read, il efface ce qu'il y a apres le \n
	buffer = ft_clean(buffer);// il modifie le buffer pour que son debut soit juste apres \n
	return (line);//retourne la ligne lu + le retour a la ligne obtenu dans ft_cleanline
}

int	main()
{
	int	file;
	int	i;
	char *str;

	file = open("texte.txt", 0);
	i = 1;
	
	while (i <= 4)
	{
		str = get_next_line(file);
		printf("%dere ligne : %s\n", i, str);
		i++;
		free(str);// free le calloc ligne 49
	}
	
	close(file);
	//taille du buffer defini a la compilation
	//en compilant avec -D BUFFER_SIZE=n
}