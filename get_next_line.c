/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:34:42 by nsartral          #+#    #+#             */
/*   Updated: 2022/05/09 10:00:05 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s)
{
	char			*ptr;
	int				i;

	ptr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			ptr = (char *)(s + i + 1);
			return (ptr);
		}
		i++;
	}
	return (ptr);
}

char	*get_the_line(char *tmp)
{
	char *line;
	int n;
	
	n = 0;
	if (!tmp)
		return (NULL);
	while (tmp[n] && tmp[n] != '\n')
		n++;
	if (tmp[n] == '\n')
		n++;
	line = (char *)malloc(sizeof(char) * (n + 1));
	if (!line)
		return (NULL);
	line[n--] = '\0';
	while (n >= 0)
	{
		line[n] = tmp[n];
		n--;
	}
	return(line);
}

char *new_buffer(char *tmp)
{
	int i;
	int j;
	i = 0;
	j = 0;
	char *tmp2;
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	if (tmp[i])
	{
		while (tmp[i + j])
			j++;
	}
	tmp2 = (char*)malloc(sizeof(char) * (j + 1));
	if (!tmp2)
		return (NULL);
	tmp2[j--] = '\0';
	while (j >= 0)
	{
		tmp2[j] = tmp[i+j];
		j--;
	}
	return (tmp2);
}

char *get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	static char *tmp = NULL;
	char *tmp2;
	char *line;
	int size;
	int n_read;
	
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	size = ft_strlen(tmp);
	if (size == 0)
	{
		n_read = read(fd, buffer, BUFFER_SIZE);
		if (n_read < 0)
			return (NULL);
		buffer[n_read] = '\0';
		tmp = ft_strdup(buffer);
		if (tmp == NULL)
			return (NULL);
	}
	if (size > 0)
	{
		n_read = read(fd, buffer, BUFFER_SIZE);
		buffer[n_read] = '\0';
		if (n_read > 0)
			tmp = ft_strjoin(tmp, buffer);
		if (tmp == NULL)
			return (NULL);
	}
	line = get_the_line(tmp);
	tmp2 = new_buffer(tmp);
	if (tmp)
		free(tmp);
	if (tmp2)
	{
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	//printf("\nTMP2%s\n", tmp2);
	//printf("\nBUFFER%s\n", buffer);
	//printf("\nLINE%s\n", line);
	//printf("\nTMP%s\n", tmp);
	return (line);
}
/*
int     main(void)
{
	int fd;
	char *buffer;
	int i;
	
	fd = open("plaidoiries.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < 5)
	{
		buffer = get_next_line(fd);
		printf("\n\nresult%i%s\n\n", i, buffer);
		if (buffer != NULL)
			free(buffer);
		i++;
	}
	return (0);
}
*/