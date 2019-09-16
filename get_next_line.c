#include "get_next_line.h"

char	*spool(char *buf, char *temp)
{
	char *ptr;

	ptr = buf;
	buf = (!buf) ? ft_strdup(temp) : ft_strjoin(buf, temp);
	free(ptr);
	return (buf);
}

char	*buf_surgery1(char *buf)
{	
	char *ptr;
	char *out;

	ptr = ft_strchr(buf, '\n');
	if (ptr - buf == 0)
	{
		out = ft_strnew(0);
		return (out);
	}
	else if (ptr == NULL)
		return (NULL);
	else
		out = ft_strsub(buf, 0 , ptr - buf);
	return (out);
}

char	*buf_surgery2(char *buf)
{
	char *ptr;
	char *out;

	if (buf[0] == '\0')
	{
		free(buf);
		return (NULL);
	}
	ptr = (ft_strchr(buf, '\n')) ? (ft_strchr(buf, '\n') + 1) : NULL;
	out = (ptr) ? ft_strdup(ptr) : NULL;
	free(buf);
	return (out);
}

int get_next_line(const int fd, char **line)
{
	static char *buf[MAX_FD];
	int bytes_read;
	char temp[BUFF_SIZE + 1];

	while ((bytes_read = read(fd, temp, BUFF_SIZE)) > 0)
	{
		temp[bytes_read] = '\0';
		buf[fd] = spool(buf[fd], temp);
	}
	if (bytes_read < 0)
		return (-1);
	*line = buf_surgery1(buf[fd]);
	buf[fd] = buf_surgery2(buf[fd]);	
	if (!*line && !buf[fd])
		return (0);
	else
		return (1);
}

int	main()
{
	char *line;
	int fd;
	int read;

/*	if (argc < 2)
	{
		write(1, "error\n", 6);
		return (1);
	}
*/
	fd = open("./test_file_nonewline", O_RDONLY);
	
	while((read = get_next_line(fd, &line)))
	{
		printf ("%s\n", line);
		free(line);
	}
	return (0);
}
