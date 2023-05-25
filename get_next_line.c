/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapoirie <mapoirie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:25:53 by mapoirie          #+#    #+#             */
/*   Updated: 2023/05/25 14:27:08 by mapoirie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char *buffer)
{
	int		i;
	int		j;
	char	*new_module;

	i = 0;
	//j = 0;

	//len = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;	
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_module = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!new_module)
		return (NULL);
	new_module[ft_strlen(buffer) - i] = '\0';
	i = i + 1;
	j = 0;
	while (buffer[i])
	{
		new_module[j++] = buffer[i++];
		//printf("'%s'\n", buffer_temp);
	}
	free(buffer);
	return (new_module);
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
	new_line = malloc((i + 2) * sizeof(char)); // pas encore free
	if (!new_line)
		return (NULL);
	new_line[i + 1] = '\0';
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

char	*ft_freejoin(char *line_plus, char *buffer)
{
	char	*buffer_temp;
	
	buffer_temp = ft_strjoin(line_plus, buffer);
	free(line_plus);
	return (buffer_temp);
}

char	*ft_read(int fd, char *line_plus)
{
	//prototype de read :
	//read(int fd, void *buf, size_t n); essaie de lire n bytes dans l'obj reference par fd
									  // vers le buffer pointe par buf
									  // renvoie le nb de byte reussi a lire / renvoie 0 si 
									  // fin du fichier / renvoie -1 si erreur
	int		nb_read;
	char	*buffer;


	if (!line_plus)
	{
		line_plus = malloc(1);
		line_plus[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)// en cas d'erreur
		{
			free(buffer);
			return(NULL);
		}
		buffer[nb_read] = '\0';
		line_plus = ft_freejoin(line_plus, buffer);
		if (ft_strchr(line_plus, '\n'))
			break;
	}
	free(buffer); // free la malloc fait plus haut
	return (line_plus);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
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
		free(str);
	}
	//taille du buffer defini a la compilation
	//en compilant avec -D BUFFER_SIZE=n
}