#include <stdio.h>
#include <string.h>

#define MAX_VERTEX 425
#define MAX_NAME 20

typedef struct s_store {
	char			name[MAX_NAME];
	struct s_store	*next;
	int				nearest;
}	t_store;

typedef struct s_graph {
	int		map[MAX_VERTEX][MAX_VERTEX];
	t_store	**store;
}	t_graph;

t_store	**init_store(void)
{
	t_store	**store;

	store = (t_store **)malloc(sizeof(t_store *) * MAX_VERTEX);
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		store[i]->name[0] = '\0';
		store[i]->next = NULL;
		store[i]->nearest = -1;
	}
	return (store);
}

void	init_graph(t_graph *graph)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAX_VERTEX)
	{
		j = 0;
		while (j < MAX_VERTEX)
		{
			graph->map[i][j] = 0;
			j++;
		}
		i++;
	}
	graph->store = init_store;
}

int		update_near(t_graph *graph, int num)
{
	int	i;
	int	near;
	int	old_near;
	int	new_near;

	i = 0;
	near = -1;
	while (i < MAX_VERTEX)
	{
		if (i == num)
			continue ;
		if (graph->map[i][i] > 0)
		{
			if (near == -1)
				near = i;
			else
			{
				old_near = num - near;
				new_near = num - i;
				if (old_near < 0)
					old_near *= -1;
				if (new_near < 0)
					new_near *= -1;
				if (old_near > new_near)
					near = new_near;
			}
		}
		i++;
	}
	return (near);
}

int	get_old_near(t_graph *graph, int num)
{
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		if (i == num)
			continue;
		if (graph->map[num][i] == 1)
			return (i);
	}
}
void	update_nearest(t_graph *graph, int num)
{
	int	near;
	int	old_near;

	near = update_near;
	if (near == -1)
		return;
	old_near = get_old_near;
	if (near == old_near)
		return ;
	graph->map[old_near][num] = 0;
	graph->map[num][old_near] = 0;
	graph->map[near][num] = 1;
	graph->map[num][near] = 1;
	graph->store[num]->nearest = near;
	graph->store[near]->nearest = num;
}

void	add_store(t_graph	*graph)
{
	int		num;
	char	str[20];
	t_store	*store;

	printf("추가하려는 지역 번호를 입력하세요\n");
	scanf("%d", &num);

	printf("추가하려는 가게 이름을 입력하세요\n");
	scanf("%s", str);
	store = graph->store[num];
	while (store->name[0] != '\0')
	{
		store = store->next;
	}
	strcpy(store, str);
	graph->map[num][num]++;
	//자기자신과 연결되는 경우는 없으니 안에 몇개가 들었는지 flag로 씀
	update_nearest(graph, num);
}

void	find_nearest(t_graph *graph)
{
	int		num;
	int		near;
	t_store	*store;

	printf("당신이 있는 지역을 입력하세요\n");
	scanf("%d", &num);

	printf("당신의 지역에 있는 가게는\n");
	if (graph->store[num]->name[0] == '\0')
		printf("없습니다!\n");
	else
	{
		store = graph->store[num];
		while (store->name[0] != '\0')
		{
			printf("%s\n", store->name);
			store = store->next;
		}
		printf("입니다\n\n");
	}

	printf("가장 가까운 다른 동네번호는 ");
	if (graph->store[num]->nearest == -1)
		printf("없습니다!\n");
	else
	{
		near = graph->store[num]->nearest;
		printf("%d번 입니다\n", near);
		printf("이 지역에 있는 가게는 \n");
		store = graph->store[near];
		while (store->name[0] != '\0')
		{
			printf("%s\n", store->name);
			store = store->next;
		}
		printf("입니다\n\n");
	}
}

int	main(void)
{
	t_graph	graph;

	init_graph(&graph);
	add_store(&graph);
	find_nearest(&graph);
}

/*int	get_near(t_graph *graph, int num)
{
	int	near;

	near = -1;
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		if (i == num)
			continue;
		if (graph->map[num][i] == 1)
		{
			near = i;
			break;
		}
	}
	return (near);
}*/