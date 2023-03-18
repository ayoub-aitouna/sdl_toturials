#include "./animation.h"

size_t	list_lenght(char **list)
{
	size_t	i;

	i = 0;
	if (list == NULL)
		return (1);
	while (list[i])
		i++;
	return (i);
}

char	**Append(char **holder, char *new)
{
	char	**new_holder;
	size_t	i;

	new_holder = malloc((list_lenght(holder) + 2) * sizeof(char *));
	i = 0;
	if (holder == NULL)
	{
		new_holder[i++] = new;
		new_holder[i] = NULL;
		return (new_holder);
	}
	while (holder[i])
	{
		new_holder[i] = holder[i];
		i++;
	}
	new_holder[i++] = new;
	new_holder[i] = NULL;
	free(holder);
	return (new_holder);
}

char	**get_map(void)
{
	char **map = NULL;
	char *line = NULL;
	int fd = open("map.config", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = Append(map, line);
	}
	return (map);
}