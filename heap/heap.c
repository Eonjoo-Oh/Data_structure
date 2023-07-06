#include <stdio.h>

#define MAX_TITLE 100
#define MAX_CONTENT 500
#define MAX_LEAF 100

typedef struct s_leaf {
	char	title[MAX_TITLE];
	char	content[MAX_CONTENT];
	int		priority;
	int		required_day;
}	t_leaf;

typedef struct s_heap {
	struct	s_leaf	*issue;
	int	size;
} t_heap;

t_heap	*init_heap()
{
	t_heap	*heap;
	t_leaf	*leaf;

	heap = (t_heap *)malloc(sizeof(t_heap) * 1);
	leaf = (t_leaf *)malloc(sizeof(t_leaf) * MAX_LEAF);

	heap->issue = leaf;
	heap->size = 1;
	return (heap);
}

void	max_heapify(t_heap *heap)
{
	int	i;
	t_leaf	target;

	i = heap->size;
	target = heap->issue[i];
	
	while (i > 1 || target.priority > heap->issue[i / 2].priority)
	{
		heap->issue[i] = heap->issue[i / 2];
		i /= 2;
	}
	heap->issue[i] = target;
}

void	add_issue(t_heap *heap)
{
	int	i;

	i = ++(heap->size);

	printf("제목을 입력하세요 : ");
	scanf("%s\n", heap->issue[i].title);
	printf("내용을 입력하세요 : ");
	scanf("%s\n", heap->issue[i].content);
	printf("1 ~ 5사이 중요도를 입력하세요(1: 낮음, 5: 높음) : ");
	scanf("%d\n", heap->issue[i].priority);
	printf("작업에 소요되는 기간을 입력하세요(단위: 일) : ");
	scanf("%d\n", heap->issue[i].required_day);
	max_heapsort(heap);
}

t_leaf	pop_issue(t_heap *heap)
{
	t_leaf	target;
	t_leaf	temp;
	int		i;
	int		j;

	i = 2;
	j = 1;
	if (heap->size == 0)
	{
		printf("삭제할 이슈가 없습니다.\n");
		return ;
	}
	target = heap->issue[1];
	temp = heap->issue[heap->size];
	heap->size--;
	heap->issue[1] = temp;
	while (i <= heap->size)
	{
		if (i < heap->size && heap->issue[i].priority < heap->issue[i + 1].priority)
			i++;
		if (temp.priority >= heap->issue[i].priority)
			break;
		heap->issue[j] = heap->issue[i];
		j = i;
		i *= 2;
	}
	heap->issue[j] = temp;
	return (target);
}

void	now_issue(t_heap *heap)
{
	printf("제목: \n", heap->issue[1].title);
	printf("내용: \n", heap->issue[1].content);
	printf("중요도: \n", heap->issue[1].priority);
	printf("예상 소요기간: \n", heap->issue[1].required_day);
}

int	main()
{
	t_heap	*heap;
	int		num;

	heap = init_heap();

	printf("안녕하세요 어떤 서비스를 이용하시겠습니까?\n");
	printf("1. 이슈 등록하기\n2. 완료 처리하기\n3. 현재 해결 중인 이슈\n 4.Exit\n");
	scanf("%d", &num);
	while (1)
	{
		if (num == 1)
			add_issue(heap);
		else if (num == 2)
			pop_issue(heap);
		else if (num == 3)
			now_issue(heap);
		else if (num == 4)
		{
			printf("bye bye\n");
			exit(0);
		}
		else
			printf("잘못입력하셨습니다. 다시 입력해주세요\n");
		printf("1. 이슈 등록하기\n2. 완료 처리하기\n3. 현재 해결 중인 이슈\n 4.Exit\n");
		scanf("%d", &num);
	}
}
