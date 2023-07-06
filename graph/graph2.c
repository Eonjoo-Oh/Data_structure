#include <stdio.h>
#include <string.h>

#define AREA_NUM 425
#define MAX_FAVORITE 100
#define NO_NEAR 1000
#define SAME_NEAR 2000

typedef struct s_vertex {
	struct t_vertex	*nearest;
	char			name[20][10];
	int				area_num;
	int				cnt;
} t_vertex;

typedef struct s_graph {
	t_vertex *vertex;
} t_graph;

t_graph	*init_graph()
{
	t_vertex	**vertex;
}//vertex의 이차원배열로 init

t_vertex	**init_vertex()
{
	t_vertex	**vertex;
	int			i;
	int			j;

	i = 0;
	vertex = (t_vertex **)malloc(sizeof(t_vertex *) * (AREA_NUM));
	while (i < AREA_NUM)
	{
		vertex[i] = (t_vertex *)malloc(sizeof(t_vertex) * 1);
		vertex[i]->nearest = NULL;
		j = 0;
		while(j < MAX_FAVORITE)
		{
			vertex[i]->name[j][0] = '\0';
			j++;
		}
		vertex[i]->area_num = i;
		vertex[i]->cnt = 0;
		i++;
	}
}

int	check_up(t_graph *graph, int num)
{
	int			up;
	t_vertex	*new_vertex;

	up = num + 1;
	while (up < AREA_NUM)
	{
		new_vertex = &(graph->vertex[up]);
		if (new_vertex->name[0][0] != '\0')
		{
			return (up);
		}
		up++;
	}
	return (NO_NEAR);
}

int	check_down(t_graph *graph, int num)
{
	int			down;
	t_vertex	*new_vertex;
	
	down = num - 1;
	while (down >= 0)
	{
		new_vertex = &(graph->vertex[down]);
		if (new_vertex->name[0][0] != '\0')
		{
			return (down * -1);
		}
		down--;
	}
	return (NO_NEAR);
}

int		compare_up_down(int up, int down, int num)
{
	if (up == NO_NEAR && down == NO_NEAR)
		return (NO_NEAR);
	if (up == NO_NEAR)
		return (down);
	if (down == NO_NEAR)
		return (up);
	down *= -1;
	if (up - num == num - down)
		return (SAME_NEAR);
	else if (up - num > num - down)
		return (down);
	else
		return (up);
}

void	update_nearest(t_graph *graph, int num)
{
	t_vertex	*vertex;
	t_vertex	*new_vertex;
	int			up;
	int			down;
	int			nearest;

	vertex = &(graph->vertex[num]);
	up = check_up(graph, num);
	down = check_down(graph, down);
	nearest = compare_up_down(up, down, num);
	if (nearest == NO_NEAR)
		return ;
	else if (nearest == SAME_NEAR)
	{
		vertex->nearest = new_vertex;
		while (new_vertex != NULL)
		{
			if (new_vertex->area_num == up)
				break;
			new_vertex = new_vertex->nearest;
		}
		new_vertex = &(graph->vertex[up]);
		vertex->nearest = new_vertex;
		while (new_vertex != NULL)
		{
			if (new_vertex->area_num == down)
				break;
			new_vertex = new_vertex->nearest;
		}
		new_vertex = &(graph->vertex[down]);
	}//same일때 더 간결하게 짤 수 있도록 생각해봐야겠음
	else
	{
		vertex->nearest = new_vertex;
		while (new_vertex != NULL)
		{
			if (new_vertex->area_num == nearest)
				break;
			new_vertex = new_vertex->nearest;
		}
		new_vertex = &(graph->vertex[nearest]);
		vertex = &(graph->vertex[nearest]);//무방향그래프니 둘 다 넣어준다.
				vertex->nearest = new_vertex;
		while (new_vertex != NULL)
		{
			if (new_vertex->area_num == nearest)
				break;
			new_vertex = new_vertex->nearest;
		}
		new_vertex = &(graph->vertex[nearest]);
	}
}

void	add_favorite(t_graph *graph)
{
	int			num;
	int			i;
	t_vertex	*vertex;
	char		name[20];

	i = 0;
	printf("추가하려는 지역 번호를 입력하세요\n");
	scanf("%d", &num);
	vertex = &(graph->vertex[num - 1]);

	printf("추가하려는 가게 이름을 입력하세요\n");
	scanf("%s", name);
	strcpy(vertex->name[vertex->cnt], name);
	vertex->cnt++;
	update_nearest(graph, num - 1);
}

int	find_near(graph);
{
	int			num;
	t_vertex	*vertex;

	printf("현재 계신 지역 번호를 입력하세요\n");
	scanf("%d", &num);

	vertex = graph->vertex[num];
	printf("당신이 계신 동에 있는 favorite 장소는\n");
	if (vertex[0][0] == '\0')
		printf("없습니다\n");
	else
		for(int i = 0; vertex[i][0] != '\0'; i++)
		{
			printf("%s\n")
		}
}

int main()
{
	t_graph		*graph;
	t_vertex	**vertex;

	graph = init_graph();
	vertex = init_vertex();
	add_favorite(graph);
	find_near(graph);
}