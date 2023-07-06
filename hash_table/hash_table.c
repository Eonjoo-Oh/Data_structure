#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ID 10
#define MAX_CUSTOMER 10000

typedef struct s_customer {
	char	id[MAX_ID];
	int		cnt;
} t_customer;

typedef struct s_hash_table{
	t_customer	*customer;
	int			size;
	int			capacity;
} t_hash_table;

unsigned int hash(char *id, int capacity)
{
	unsigned int	hash_value = 0;
	unsigned int	prime = 3;

	for (int i = 0; id[i] != '\0'; i++)
	{
		hash_value = (hash_value * prime + id[i]) % capacity;
	}

	return (hash_value);
}

t_hash_table	*init_system(void)
{
	t_hash_table	*hash_table;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	hash_table->customer = (t_customer *)malloc(sizeof(t_customer) * (MAX_CUSTOMER));
	hash_table->size = 0;
	hash_table->capacity = MAX_CUSTOMER;

	for (int i = 0; i < MAX_CUSTOMER; i++)
	{
		hash_table->customer[i].id[0] = '\0';
		hash_table->customer[i].cnt = 0;
	}
	return (hash_table);
}

void open_addressing(t_hash_table *hash_table, int index, char *id)
{
  if (hash_table->customer[index].id[0] == '\0')
  {
	strcpy(hash_table->customer[index].id, id);
	hash_table->size++;
  }
  else
   open_addressing(hash_table, index + 1, id);
}

void insert_customer(t_hash_table *hash_table)
{
	char id[MAX_ID];
	int  index;//index에 소수나 문자가 들어갈수있는가?	
	
	printf("id를 입력해주세요\n");
	scanf("%s", id); 
	index = hash(id, hash_table->capacity);
	open_addressing(hash_table, index, id);
}

void	check_purchase(t_hash_table *hash_table, char *id, int index)
{
	if (hash_table->customer[index].id[0] == '\0')
	{
	printf("등록되지 않은 아이디입니다\n");
	return ;
	}
	if (strncmp(hash_table->customer[index].id, id, strlen(id)) == 0)
	{
		printf("구매할 수 있는 개수는 %d개 입니다\n", 5 - hash_table->customer[index].cnt);
		return ;
	}
	else
		check_purchase(hash_table, id, index + 1);
}

void	purchase_snack(t_hash_table *hash_table, char *id, int index)
{
	int	num;

	if (hash_table->customer[index].id[0] == '\0')
	{
		printf("등록되지 않은 회원입니다\n");
		return ;
	}
	if (strncmp(hash_table->customer[index].id, id, strlen(id)) == 0)
	{
		if (hash_table->customer[index].cnt == 5)
		{
			printf("이미 5개를 구매하셨습니다!\n");
			return ;
		}
		else
		{
			printf("구매하실 수량을 입력해주세요\n");
			scanf("%d\n", &num);
			if (hash_table->customer[index].cnt + num > 5)
			{
				printf("1인당 구매개수는 5개로 제한되어있습니다\n");
				return ;
			}
			else
			{
				hash_table->customer[index].cnt += num;
				printf("구매완료! 감사합니다\n");
				return ;
			}
		}
	}
	else
		purchase_snack(hash_table, id, index + 1);
}

int main()
{
	t_hash_table	*hash_table;
	int				num;
	char			id[10];

	printf("안녕하세요 어떤 서비스를 이용하시겠습니까?\n");
	printf("1. 화제의 과자 '수수깡' 구입하기\n2. 남은 구매갯수 보기\n3. 회원 가입하기\n 4.Exit\n");
	scanf("%d", &num);
	hash_table = init_system();
	while (1)
	{
		if (num == 1)
		{
			printf("아이디를 입력하세요 : ");
			scanf("%s\n", id);
			purchase_snack(hash_table, id, hash(id, hash_table->capacity));
		}
		else if (num == 2)
		{
			printf("아이디를 입력하세요 : ");
			scanf("%s\n", id);
			check_purchase(hash_table, id, hash(id, hash_table->capacity));
		}
		else if (num == 3)
			insert_customer(hash_table);
		else if (num == 4)
		{
			printf("bye bye\n");
			exit(0);
		}
		else
			printf("잘못입력하셨습니다. 다시 입력해주세요\n");
		printf("1. 화제의 과자 '수수깡' 구입하기\n2. 남은 구매갯수 보기\n3. 회원 가입하기\n 4.Exit\n");
		scanf("%d", &num);
	}
}