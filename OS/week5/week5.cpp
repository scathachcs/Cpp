#include <stdio.h>

#define MEM_SIZE 128
static char mem[MEM_SIZE];

#define MINBLK 16
struct block {
	struct block * next;
	size_t length;
	char data[0];
};

static struct block * free_list = NULL;

void malloc_init(void)
{
	free_list = (struct block *)mem;
	free_list->next = NULL;
	free_list->length = MEM_SIZE - sizeof(struct block);
}

void * malloc(size_t size)
{
	size = (size + 7) & ~7;

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;

	while (cur != NULL) {
		if (cur->length >= size) break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return NULL;

	if ((cur->length - size) >= MINBLK) {
		struct block * temp = (struct block *)(cur->data + size);
		temp->next = cur->next;
		temp->length = cur->length - size - sizeof(struct block);
		prev->next = temp;
		cur->length = size;
	} else {
		prev->next = cur->next;
	}

	return cur->data;
}

void free(void * ptr)
{
	if (ptr == NULL)
		return;

	struct block * temp = (struct block *)((char *)ptr - sizeof(struct block));
	char * tempn = (char *)ptr + temp->length; // 和temp物理上相邻的下一个block的地址

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;
	char * prevn; // 和prev物理上相邻的下一个block的地址
    while(cur<temp&&cur!=NULL){//将cur指向temp后的第一个空闲块
        prev=cur;
        cur=cur->next;
    }

    prevn=(char *)prev+sizeof(struct block)+prev->length;
    if((char *)cur==tempn&&(char *)temp==prevn){//当temp前后均有空闲块时
        prev->next=cur->next;
        prev->length+=temp->length+cur->length+2*sizeof(struct block);
    } 
    else if((char *)cur==tempn){//当temp后有空闲块，temp前未有时
        prev->next=temp;
        temp->next=cur->next;
        temp->length+=sizeof(struct block)+cur->length;
    }
    else if((char *)temp==prevn){//当temp前有空闲块，temp后未有时
        prev->length+=sizeof(struct block)+temp->length;
    }
    else{//当temp前后均未有时
        prev->next=temp;
        temp->next=cur;
    }

}

void malloc_state(void)
{
	printf("free blocks:\n");
	struct block * ptr;
	for (ptr = free_list; ptr != NULL; ptr = ptr->next) {
		int i;
		printf("%p:", ptr);
		for (i = 0; i < ptr->length; i++) {
			printf("=");
		}
		printf(" ");
	}
	printf("\n");
}

void malloc_test(void)
{   
    char* a;
    char* b;
    char* c;
    malloc_state();//未分配时

    printf("1:\n");
    a=(char *)malloc(112);//分配完全部空间,即前后均未有空闲块
    malloc_state();
    free(a);//释放全部空间
    malloc_state();

    printf("2:\n");
    a=(char *)malloc(10);
    b=(char *)malloc(2);
    free(a);
    malloc_state();
    free(b);//释放时前后均有空闲块，展示合并
    malloc_state();

    printf("3:\n");
    a=(char *)malloc(10);
    malloc_state();
    free(a);//释放时后有空闲块，展示合并
    malloc_state();

    printf("4:\n");
    a=(char *)malloc(10);
    b=(char *)malloc(10);
    c=(char *)malloc(10);
    free(a);
    malloc_state();
    free(b);//释放时前有空闲块，展示合并
    malloc_state();
}

int main(int argc, const char *argv[])
{
	malloc_init();

	malloc_test();

	return 0;
}