// main partie obligatoire
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("texte.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
	return (0);
}

// main partie bonus 
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