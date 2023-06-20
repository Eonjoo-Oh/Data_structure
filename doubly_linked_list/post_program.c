#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 20
#define MAX_content 500

typedef struct	s_post {
	char title[MAX_TITLE];
	char content[MAX_content];
	struct s_post *prev;
	struct s_post *next;
} t_post;

t_post *init_post()
{
  t_post *head;
  t_post *tail;

  head = (t_post *)malloc(sizeof(t_post) * 1);
  tail = (t_post *)malloc(sizeof(t_post) * 1);
  head->prev = NULL;
  head->next = tail;
  tail->prev = head;
  tail->next = NULL;
  return (head);
}

t_post *init_node()
{
  t_post *node;

  node = (t_post *)malloc(sizeof(t_post) * 1);
  node->prev = NULL;
  node->next = NULL; 

  return (node);
}

void	write_post(t_post *tail) {
	t_post	*new;
	t_post	*front;

	new = init_node();
	front = tail->prev;
	front->next = new;
	new->prev = front;
	new->next = tail;
	tail->prev = new;
	printf("\nplease enter the title\n");
	scanf("%s", new->title);
	printf("\nplease enter your content\n");
	scanf("%s", new->content);
	printf("\nPosted!\n");
}

void delete_post(t_post *head, t_post *tail)
{
	t_post	*target;
	char	title[MAX_TITLE];
	size_t	len;

	target = head->next;
	printf("\nPlease enter the title of content you want to delete\n");
	scanf("%s", title);
	len = strlen(title);

	while (target != tail)
	{
	  if (strncmp(target->title, title, len) == 0)
	  {
	  	target->prev->next = target->next;
		target->next->prev = target->prev;
		free(target);
		printf("\nDeleted!\n");
		return ;
	  }
	  target = target->next;
	}
	printf("\nSorry, we don't have that title\n");
}

void print_list_rev(t_post *head, t_post *tail)
{
	t_post *temp;

	if (tail->prev == head)
	{
		printf("There's no content!\n");
		return ;
	}
	temp = tail->prev;
	while (temp != head)
	{
		printf("\n<%s>\n", temp->title);
		printf("%s\n\n", temp->content);
		temp = temp->prev;
	}
}

void print_list(t_post *head, t_post *tail)
{
	t_post *temp;

	if (head->next == tail)
	{
		printf("\nThere's no content!\n");
		return ;
	}
	temp = head->next;
	while (temp != tail)
	{
		printf("\n<%s>\n", temp->title);
		printf("%s\n\n", temp->content);
		temp = temp->next;
	}
}

int main() 
{
	t_post	*head;
	t_post	*tail;
	int		num;

	head = init_post();
	tail = head->next;
	printf("hello!\n What service would you like to use?\n");
	printf("1. write post\n2. delete post\n3. Lookup in the latest order\n4. Lookup in old order\n5. Exit\n");
	scanf("%d", &num);
	while (1)
	{
		if (num == 1)
			write_post(tail);
		else if (num == 2)
			delete_post(head, tail);
		else if (num == 3)
			print_list(head, tail);
		else if (num == 4)
			print_list_rev(head, tail);
		else if (num == 5)
		{
			printf("bye bye\n");
			exit(0);
		}
		else
			printf("wrong number! Try again\n");
		printf("\nTo continue press the number\n");
		printf("1. write post\n2. delete post\n3. Lookup in the latest order\n4. Lookup in old order\n5. Exit\n");
		scanf("%d", &num);
	}
}