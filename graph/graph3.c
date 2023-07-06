#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX 425
#define MAX_NAME 20

typedef struct s_store {
	char			*name;
	struct s_store	*next;
	int				nearest;
}	t_store;

typedef struct s_graph {
	int		map[MAX_VERTEX][MAX_VERTEX];
	t_store	**store;
}	t_graph;

t_store *init_inner_store()
{
	t_store	*store;

	store = (t_store *)malloc(sizeof(t_store) * 1);
	store->name = (char *)malloc(sizeof(char) * (MAX_NAME + 1));
	store->name[0] = '\0';
	store->next = NULL;
	store->nearest = -1;

	return (store);
}

t_store	**init_store(void)
{
	t_store	**store;

	store = (t_store **)malloc(sizeof(t_store *) * MAX_VERTEX);
	for(int i = 0; i < MAX_VERTEX; i++)
	{
		store[i] = init_inner_store();
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
	graph->store = init_store();
}

int		update_near(t_graph *graph, int num)
{
	int	i;
	int	near;
	int	old_near;
	int	new_near;

	i = 0;
	near = graph->store[num]->nearest;
	while (i < MAX_VERTEX)
	{
		if (i == num)
		{
			i++;
			continue ;
		}
		if (graph->map[i][i] > 0)
		{
			if (near == -1)
				near = i;
			else if (near == i)
			{
				i++;
				continue;
			}
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

void	update_nearest(t_graph *graph, int num)
{
	int	near;
	int	old_near;

	near = update_near(graph, num);
	old_near = graph->store[num]->nearest;
	if (near == -1)
		return;
	if (old_near == near)
		return ;
	else
	{
		graph->map[old_near][num] = 0;
		graph->map[num][old_near] = 0;
		graph->map[near][num] = 1;
		graph->map[num][near] = 1;
		graph->store[num]->nearest = near;
		graph->store[near]->nearest = num;
	}
}//가장 가까운 지점을 찾아서 update해주는 함수

void	add_store(t_graph	*graph)
{
	int		num;
	char	str[20];
	t_store	*store;

	printf("\n************  최애 가게 등록하기!  *************\n\n");
	printf("추가하려는 <지역 번호>를 입력하세요\n");
	scanf("%d", &num);
	store = graph->store[num];

	printf("\n추가하려는 <가게 이름>을 입력하세요\n");
	scanf("%s", str);
	if (store->name[0] == '\0')
		strcpy(store->name, str);
	else
	{
		while (store->next != NULL)
		{
			store = store->next;
		}
		store->next = init_inner_store();
		store = store->next;
		strcpy(store->name, str);
	}
	graph->map[num][num]++; //자기 자신과 이어진 것은 자신이 가지고 있는 가게의 개수를 의미함
	update_nearest(graph, num);
}

void	find_nearest(t_graph *graph)
{
	int		num;
	int		near;
	t_store	*store;

	printf("\n*********  내 주변 최애 가게 찾기!  **********\n\n");
	printf("당신이 있는 지역을 입력하세요\n\n");
	scanf("%d", &num);

	printf("당신의 지역에 있는 가게는\n\n");
	if (graph->store[num]->name[0] == '\0')
		printf("\n없습니다!\n\n");
	else
	{
		store = graph->store[num];
		while (store != NULL)
		{
			printf("%s\n", store->name);
			store = store->next;
		}
		printf("입니다\n");
	}

	printf("\n가장 가까운 다른 동네번호는 \n");
	if (graph->store[num]->nearest == -1)
		update_nearest(graph, num);
	if (graph->store[num]->nearest == -1)
	printf("없습니다!\n\n");
	else
	{
		near = graph->store[num]->nearest;
		printf("%d번 입니다\n", near);
		printf("이 지역에 있는 가게는 \n");
		store = graph->store[near];
		if (store->name == NULL)
		{
			printf("없습니다!\n\n");
			return ;
		}
		while (store != NULL)
		{
			printf("%s\n", store->name);
			store = store->next;
		}
		printf("입니다\n");
	}
}

int	main(void)
{
	t_graph	graph;
	int		num;

	printf("\n안녕하세요 어떤 서비스를 이용하시겠습니까?\n\n");
	printf("1. 최애 가게 등록하기\n\n2. 내 주변 최애 가게 보기\n\n3.Exit\n\n");
	scanf("%d", &num);
	init_graph(&graph);
	while (1)
	{
		if (num == 1)
			add_store(&graph);

		else if (num == 2)
			find_nearest(&graph);
		else if (num == 3)
		{
			printf("bye bye\n");
			exit(0);
		}
		else
			printf("잘못입력하셨습니다. 다시 입력해주세요\n\n");
		printf("\n\n********************완료!*********************\n");
		printf("\n\n어떤 서비스를 이용하시겠습니까?\n");
		printf("1. 최애 가게 등록하기\n2. 내 주변 최애 가게 보기\n3.Exit\n\n");
		scanf("%d", &num);
	}
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