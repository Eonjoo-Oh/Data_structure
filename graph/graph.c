#include <stdio.h>

#define AREA_NUM 30
#define MAX_FAVORITE 20

typedef struct s_vertex {
	char			name[20][MAX_FAVORITE];
	struct t_vertex	*nearest;
	int				area_num;
	int				cnt;
} t_vertex;

typedef struct s_graph {
	t_vertex **vertex;
} t_graph;

t_vertex	*init_vertex()
{
	t_vertex **vertex;

	vertex = (t_vertex **)malloc(sizeof(t_vertex *) * (AREA_NUM));
	for(int i = 0; i < AREA_NUM; i++)
	{
		for(int j = 0; j < MAX_FAVORITE; j++)
		{
			strcpy(vertex[i]->name[j], "");
		}
		vertex[i]->area_num = i;
		vertex[i]->cnt = 0;
		vertex[i]->nearest = NULL;
	}
}

t_graph	*init_graph()
{
	t_graph	*graph;

	graph = (t_graph *)malloc(sizeof(graph) * 1);
	graph->vertex = (t_vertex **)malloc(sizeof(t_vertex *) * (AREA_NUM));
	for(int i = 0; i < AREA_NUM; i++)
	{
		graph->vertex[i] = NULL;
	}
	return (graph);
}

void	update_nearest(t_graph *graph, int area)
{
	t_vertex	*vertex;
	int	current;
	int	up;
	int	down;

	vertex = graph->vertex[area];
	if (graph->vertex[area]->nearest == NULL)
	{
		current = -1;
	}
	else
		current = vertex->nearest->area_num;
	up = area + 1;
	down = area - 1;

	while (up < AREA_NUM || down >= 0)
	{
		if (up < AREA_NUM)
		{
			if ()
		}
		
	}
}

void	add_favorite(t_graph *graph)
{
	int			i;
	int			num;
	t_vertex	*vertex;
	char		*name;

	i = 0;
	printf("등록하려는 가게의 지역 번호를 입력하세요\n");
	scanf("%d", &num);
	vertex = graph->vertex[num];

	printf("가게의 이름을 입력하세요\n");
	scanf("%s", name);
	while (vertex->name[i][0] != '\0')
	{
		i++;
	}
	strcpy(vertex->name[i], name);

	vertex->cnt++;

	update_nearest(graph, num);

	printf("등록되었습니다!");
}

int	main()
{
	t_graph	*graph;

	graph = init_graph();
	add_favorite(graph);

}