#include <stdio.h>

typedef struct s_single{
	int data;
	t_single *next;
} t_single;

typedef struct s_double{
	int data;
	t_double *prev;
	t_double *next;
} t_double;

//single_list
t_single	*init_list(int num)
{
	t_single	*head;
	t_single	*tail;
	t_single	*node;

	head = (t_single *)malloc(sizeof(t_single));
	tail = (t_single *)malloc(sizeof(t_single));
	node = (t_single *)malloc(sizeof(t_single));

	head->next = node;
	node->next = tail;
	node->data = num;
	tail->next = NULL;

	return (head);
}

void	add_front_single(t_single *node, int data)
{

}

void	add_back_single(t_single *node, int data)
{

}

void	delete_data_single(t_single *node, int data)
{

}

//double_list
void	add_front_single(t_single *node)
{
	
}

void	add_back_double(t_double *node)
{

}

void	delete_data_double(t_double *node, int data)
{

}

//utils
void	print_data_single(t_single *node)
{
	while (node->next != NULL)
	{
		printf("%d\n", node->data);
		node = node->next;
	}
}

void	print_data_double(t_double *node)
{
	while (node->next != NULL)
	{
		printf("%d\n", node->data);
		node = node->next;
	}
}

int main(void)
{
	int	data[5] = {1, 2, 3, 4, 5};
	t_single *single_list;
	t_double *double_list;

	single_list = init_list(data[0]);
	double_list = init_list(data[0]);
	printf("init single list\n");
	print_data_single(single_list);
	printf("-----------------------------------------\n");
	printf("init double list\n");
	print_data_double(double_list);
	printf("-----------------------------------------\n");
}