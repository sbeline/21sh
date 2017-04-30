#include "../../includes/shell.h"

char			**convert_history(char *path_memory, int lenght)
{
	char		**str;
	char		*buf;
	int			fd;

	buf = NULL;
	fd = open(path_memory, O_RDWR | O_CREAT | O_APPEND, 0666);
	str = (char**)ft_memalloc(sizeof(char*) * lenght);
	while ((get_next_line(fd, &buf)) > 0)
	{
		str[lenght] = ft_strdup(buf);
		lenght--;
	}
	close(fd);
	return (str);
}