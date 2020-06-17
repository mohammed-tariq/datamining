#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

struct supcount {				
	char index;
	int count;
	int b;
	struct supcount* next;
};

struct rareitem {
	char data;
	struct rareitem* next;
};

struct rareTrans {
	struct rareitem* head;
	struct rareTrans* down;
};

struct H_struct {
	char itemID;
	int sup_count;
	struct rareQueue* hyperLink;
	struct H_struct* next;
};

struct rareQueue {
	char data;
	struct rareQueue* next;
	struct rareQueue* hLink;
};

int min, max;
struct supcount* suproot = NULL;			
struct rareitem* rareroot = NULL;

struct rareitem* create_node(char data) {
	struct rareitem* new_node = (struct rareitem*)malloc(sizeof(struct rareitem));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

struct rareitem *insert_data(struct rareitem *root, char data)
{
	if (root == NULL)
	{
		root = create_node(data);
		return root;
	}
	else
	{
		struct rareitem* temp = root;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = create_node(data);
		return root;
	}
}

void print_data(struct rareitem *root) {
	struct rareitem* temp = root;
	while (temp != NULL) {
		printf("\t%c", temp->data);
		temp = temp->next;
	}
}

void print_data_transaction(struct rareTrans *root) {
	struct rareTrans* temp = root;
	if (temp == NULL)
	{
		printf("list is empty\n");
	}
	else
	{
		while (temp != NULL) {
			print_data(temp->head);
			printf("\n");
			temp = temp->down;
		}
	}
}

struct rareitem* createRareItem(struct rareTrans* root, char str[30])
{
	struct rareitem* new_item_next = (struct rareitem*)malloc(sizeof(struct rareitem));
	char c;
	int i = 0;
	c = str[i++];
	while (c != NULL && c != ',') {
		if (root->head == NULL) {
			struct rareitem* new_item = (struct rareitem*)malloc(sizeof(struct rareitem));
			new_item->data = c;
			new_item->next = NULL;
			root->head = new_item;
			new_item_next = new_item;

		}
		else {
			while (new_item_next->next != NULL)
				new_item_next = new_item_next->next;
			struct rareitem* new_item = (struct rareitem*)malloc(sizeof(struct rareitem));
			new_item->data = c;
			new_item->next = NULL;
			new_item_next->next = new_item;
			if (str[i] == NULL)
				break;
		}
		i++;
		c = str[i++];
	}
	return root->head;
}

struct rareTrans* createRareTransactionNode()
{
	struct rareTrans* new_trans_node = (struct rareTrans*)malloc(sizeof(struct rareTrans));
	new_trans_node->head = NULL;
	new_trans_node->down = NULL;
	return new_trans_node;
}

struct rareTrans* createRareTransaction(struct rareTrans* root, char str[30])
{
	struct rareTrans* new_trans = (struct rareTrans*)malloc(sizeof(struct rareTrans));
	if (root == NULL) {
		root = createRareTransactionNode();
		new_trans = root;
	}
	else {
		new_trans = root;
		while (new_trans->down != NULL)
			new_trans = new_trans->down;
		new_trans->down = createRareTransactionNode();
		new_trans = new_trans->down;
	}
	if (new_trans->head == NULL)
	{
		new_trans->head = createRareItem(new_trans, str);
	}

	return root;
}

void DisplayCount()
{
	struct supcount* temp = suproot;
	while (temp != NULL) {
		printf("%c\t", temp->index);
		printf("%d\t", temp->count);
		printf("%d\n", temp->b);
		temp = temp->next;
	}
}
struct supcount* create_newSup(char *c)
{
	struct supcount* new_node = (struct supcount*)malloc(sizeof(struct supcount));
	new_node->index = *c;
	new_node->count = 1;
	new_node->b = 0;
	new_node->next = NULL;
	return new_node;
}

//support count function
void sup(char* c)
{
	int flag = 0;
	if (suproot == NULL)
	{
		suproot = create_newSup(c);
	}
	else
	{
		struct supcount* temp = suproot;
		while (temp->next != NULL)
		{
			if (temp->index == *c)
			{
				temp->count++;
				if ((temp->count) > min && (temp->count) < max)
					temp->b = 1;
				else
					temp->b = 2;
				flag = 1;
			}
			temp = temp->next;
		}
		if(temp->next == NULL && temp->index == *c)
		{
			temp->count++;
			if (temp->count > min && temp->count < max)
				temp->b = 1;
			else
				temp->b = 2;

		}
		else if (flag == 0)
		{
			temp->next = create_newSup(c);
			if ((temp->next)->count > min && (temp->next)->count < max)
			{
				(temp->next)->b = 1;
			}
		}
	}
}
struct H_struct* create_Hstruct_node(struct supcount* s_temp)
{
	struct H_struct* h_temp = (struct H_struct*)malloc(sizeof(struct H_struct));
	h_temp->itemID = s_temp->index;
	h_temp->sup_count = s_temp->count;
	h_temp->hyperLink = NULL;
	h_temp->next = NULL;
	return h_temp;
}
// copy support to HStruct
struct H_struct* copy_sup_Hstruct(struct H_struct* h_Head, struct supcount* s_Head)
{
	struct H_struct* h_temp = (struct H_struct*)malloc(sizeof(struct H_struct));
	h_temp = h_Head;
	struct supcount* s_temp = (struct supcount*)malloc(sizeof(struct supcount));
	s_temp = s_Head;
	while (s_temp != NULL)
	{
		if (s_temp->count > min && s_temp->count < max)
		{
			if (h_temp == NULL)
			{
				h_Head = create_Hstruct_node(s_temp);
				h_temp = h_Head;
			}
			else
			{
				h_temp->next = create_Hstruct_node(s_temp);
				h_temp = h_temp->next;
			}
		}
		s_temp = s_temp->next;
	}
	return h_Head;
}
struct rareQueue* createQueueNode(char c)
{
	struct rareQueue* queue_node = (struct rareQueue*)malloc(sizeof(struct rareQueue));
	queue_node->data = c;
	queue_node->next = NULL;
	queue_node->hLink = NULL;
	return queue_node;
}
struct rareQueue* createQueueList(struct rareitem* r_list)
{
	struct rareQueue* queue_head = (struct rareQueue*)malloc(sizeof(struct rareQueue));
	struct rareQueue* queue_temp = (struct rareQueue*)malloc(sizeof(struct rareQueue));
	queue_head = queue_temp = NULL;
	while (r_list != NULL) {
		if (queue_head == NULL) {
			queue_head = createQueueNode(r_list->data);
			queue_temp = queue_head;
		}
		else {
			queue_temp->next = createQueueNode(r_list->data);
			queue_temp = queue_temp->next;
		}
		r_list = r_list->next;
	}
	return queue_head;
}

struct H_struct* connect_Queue(struct H_struct* h_Head, struct rareTrans* root)
{
	struct H_struct* h_temp = (struct H_struct*)malloc(sizeof(struct H_struct));
	struct rareTrans* r_temp = (struct rareTrans*)malloc(sizeof(struct rareTrans));
	struct rareQueue* queue_hyperlink = (struct rareQueue*)malloc(sizeof(struct rareQueue));
	h_temp = h_Head;
	int flag = 0;
	int c = 1;
	if (h_temp == NULL) {
		return NULL;
	}
	else {
		while (h_temp != NULL) {
			flag = 0;
			r_temp = root;
			while (r_temp != NULL) {
				if (h_temp->itemID == r_temp->head->data) {
					if (h_temp->hyperLink == NULL) {
						h_temp->hyperLink = createQueueList(r_temp->head);
						queue_hyperlink = h_temp->hyperLink;
						printf("\n There is a transaction which starts with item  %c\n", queue_hyperlink->data);

						flag = 1;
					}
					else {
						queue_hyperlink->hLink = createQueueList(r_temp->head);
						queue_hyperlink = queue_hyperlink->hLink;
						queue_hyperlink->hLink = NULL;
						printf(" linked with %d line\n", c);
					}
				}
				c++;
				r_temp = r_temp->down;
			}
			if (flag == 0)
			{
				printf("\n No such transaction which starts with item  %c\n", h_temp->itemID);
				h_temp->hyperLink = NULL;
			}
			c = 1;
			h_temp = h_temp->next;
		}
	}
	return h_Head;
}





//main function starts
int main()
{
	printf("\nenter min and max value(Rare Item range)\n");
	scanf("%d%d", &min, &max);
	double tot_time;
	clock_t start, end;
	start = clock();
	char buf[500];
	char *record, *line;
	

	//-------------------------first scan-------------------------//
	printf("\n-------First scan---------\n");
	FILE *fp = fopen("CSVdemo.csv", "r");
	if (fp == NULL) {
		printf("\n file opening failed ");
		return -1;
	}
	while ((line = fgets(buf, sizeof(buf), fp)) != NULL)
	{
		record = strtok(line, ", \n ");
		printf("\nrecord:\n");

		while (record != NULL)
		{
			printf("\t%s", record);
			sup(record);
			record = strtok(NULL, ", \n ");
		}
		
		printf("\n");
	}
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\n\n");
	printf("Item ID count  R/F\n");
	DisplayCount();
	printf("\n--------------------------------------------------------------------------------------------");


	//gererate rare items
	struct supcount* temp = suproot;
	while (temp != NULL)
	{
		if (temp->b == 1)
		{
			rareroot = insert_data(rareroot, temp->index);
			temp = temp->next;
		}
		else
		{
			temp = temp->next;
		}
	}




	printf("\nRare Items -->\t");
	print_data(rareroot);
	printf("\n--------------------------------------------------------------------------------------------");

	printf("\n\n");
	//-------------------------second scan-------------------------//
	printf("-------------------------Second scan-------------------------\n");
	int q = 0;
	char buf2[500];
	char *record2, *line2;
	fp = fopen("CSVdemo.csv", "r");
	if (fp == NULL) {
		printf("\n file opening failed ");
		return -1;
	}
	//-----------------------------------------------struct rareQueue* rq=rareQueueHead;
	int flag = 0;
	printf("\nRare Item Transactions are..\n");
	int t = 1;
	struct rareTrans* root = (struct rareTrans*)malloc(sizeof(struct rareTrans));
	root = NULL;
	while ((line2 = fgets(buf2, sizeof(buf2), fp)) != NULL)
	{
		char str[30];
		strcpy(str, line2);
		record2 = strtok(line2, ", \n ");
		flag = 0;
		while (record2 != NULL && strcmp(record2, ","))
		{
			flag = 0;
			//printf("\t%s", record3);
			struct rareitem* temp2 = rareroot;
			while (temp2 != NULL)
			{
				if (*record2 == temp2->data)
					flag = 1;
				temp2 = temp2->next;
			}
			record2 = strtok(NULL, ", \n ");
			if (flag == 1) {
				root = createRareTransaction(root, str);
				break;
			}
		}
	}

	printf("\n");
	print_data_transaction(root);
	printf("\n");
	fclose(fp);


	//------------------------------create Hstruct----------------------------//
	struct H_struct* h_Head = NULL;
	struct H_struct* h_Headlink = NULL;
	struct supcount* s_Head = suproot;
	h_Headlink = copy_sup_Hstruct(h_Head, s_Head);
	struct H_struct* h_Headlinkcopy = h_Headlink;

	printf("\n Hstruct--> storing items of transaction(T) with three fields  \n");
	while (h_Headlink != NULL)
	{
		printf("\n %c=%d and %c", h_Headlink->itemID, h_Headlink->sup_count, h_Headlink->hyperLink);
		h_Headlink = h_Headlink->next;
	}
	//------------------------------create queue and link to Hstruct ----------------------------//
	printf("\n--------------------------------------------------------------------------------------------");
	struct H_struct* h_HeadlinkQueue = connect_Queue(h_Headlinkcopy, root);
	printf("\n--------------------------------------------------------------------------------------------");
	printf("\n Printing the linked transactions\n");
	struct rareQueue* queue_head = h_HeadlinkQueue->hyperLink;
	while (h_HeadlinkQueue != NULL)
	{
		queue_head = h_HeadlinkQueue->hyperLink;
		printf("\n %c=%d ", h_HeadlinkQueue->itemID, h_HeadlinkQueue->sup_count);
		if (h_HeadlinkQueue->hyperLink != NULL)
			while (queue_head->hLink != NULL)
			{
				printf("---> %c ", queue_head->data);
				queue_head = queue_head->hLink;
			}
		h_HeadlinkQueue = h_HeadlinkQueue->next;
	}

	end = clock();
	tot_time=((double)(end - start)) / CLK_TCK;
	printf("\nTime taken by proposed algorithm  is: %f\n", tot_time);
	return 0;
}