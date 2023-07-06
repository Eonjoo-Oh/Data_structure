#include <stdio.h>
#include <stdlib.h>

typedef struct s_order {
	char	*product;
	char	*customer;
	int		bag;
} t_order;

typedef struct s_queue {
	struct s_order *order;
	int	front;
	int	rear;
} t_queue;

void	dequeue(t_queue *queue)
{
	if (queue->front == queue->rear)
	{
		printf("no orders now\n");
		return ;
	}
	queue->front++;
}

void	enqueue(t_queue *queue)
{
	char	*product;
	char	*customer;
	int		bag;

	if (queue->rear == 999)
	{
		printf("queue is full\n");
		return ;
	}
	queue->rear++;
	printf("enter the product name\n");
	//scanf("%s", product);
	printf("enter the customer's name\n");
	//scanf("%s", customer);
	printf("if the customer need paper bag press '1' else '0'\n");
	//scanf("%d", &bag);
	queue->order[queue->rear].product = "product";
	queue->order[queue->rear].customer = "customer";
	queue->order[queue->rear].bag = 1;
}

void	print_list(t_queue * queue)
{
	int	i;
	if (queue->front == queue->rear)
	{
		printf("no orders now\n");
		return ;
	}
	i = queue->front + 1;
	while (i < queue->rear)
	{
		printf("product : %s\n", queue->order[i].product);
		printf("customer's name : %s\n", queue->order[i].customer);
		if (queue->order[i].bag == 0)
			printf("paper bag : NO\n");
		else
			printf("paper bag : YES\n");
		printf("\n----------------------------------\n");
		i++;
	}
}

void	print_prev_order(t_queue *queue)
{
		if (queue->front == queue->rear)
		{
			printf("no orders now\n");
			return ;
		}
		printf("product : %s\n", queue->order[queue->front].product);
		printf("customer's name : %s\n", queue->order[queue->front].customer);
		if (queue->order[queue->front].bag == 0)
			printf("paper bag : NO\n");
		else
			printf("paper bag : YES\n");
}

void	add_order(t_queue *queue)
{
	char	*product;
	char	*customer;
	int		bag;
	if (queue->rear == 999)
	{
		printf("queue is full!\n");
		return ;
	}
	enqueue(queue);
}

t_queue *init_order()
{
	t_queue	*queue;
	t_order	*order;

	queue = (t_queue *)malloc(sizeof(t_queue));
	order = (t_order *)malloc(sizeof(t_order) * 1000);

	queue->order = order;
	queue->front = -1;
	queue->rear = -1;
	return (queue);
}

void	order_now(t_queue *queue)
{
	int	accept;
	if (queue->front == queue->rear)
	{
		printf("no orders now\n");
		return ;
	}

	printf("product : %s\n", queue->order[queue->front + 1].product);
	printf("customer name : %s\n", queue->order[queue->front + 1].customer);
	if (queue->order[queue->front + 1].bag == 0)
		printf("paper bag : NO\n");
	else
		printf("paper bag : YES\n\n");

	printf("if you press '1' this order will be assigned to you\n");
	printf("1. Processing this order\n2. Not now\n");
	scanf("%d\n", &accept);
	if (accept == 1)
		dequeue(queue);
}

int main() 
{
	t_queue	*queue;
	int		num;

	queue = init_order();
	printf("hello!\n What service would you like to use?\n");
	printf("1. Order to be processed now\n2. Add order\n3. List of order\n4. Previous order\n 5.Exit\n");
	scanf("%d", &num);
	while (1)
	{
		if (num == 1)
			order_now(queue);
		else if (num == 2)
			add_order(queue);
		else if (num == 3)
			print_list(queue);
		else if (num == 4)
			print_prev_order(queue);
		else if (num == 5)
		{
			printf("bye bye\n");
			exit(0);
		}
		else
			printf("wrong number! Try again\n");
		printf("\nTo continue press the number\n");
		printf("1. Order to be processed now\n2. Add order\n3. List of order\n4. Previous order\n 5.Exit\n");
		scanf("%d", &num);
	}
}