#include <stdio.h>

#define MEM_SIZE 32

#define RAM_SIZE  16
#define SWAP_SIZE 32

static int first = -1;
static int last = -1;

struct page_item {
	int ram_addr;
	int swap_addr;
	int access;
	bool present;
	bool modified;
};

static char ram[RAM_SIZE];
static char swap[SWAP_SIZE];
static struct page_item page_table[MEM_SIZE];

//更新链表
static int algo_swap(int laddr)
{
	
	if (laddr == first) {//更行laddr处链表
		first = page_table[first].access;
	}
	else {
		int x = first;
		for (; page_table[x].access != laddr;) {
			x = page_table[x].access;
		}
		page_table[x].access = page_table[laddr].access;
	}
	
	page_table[last].access = laddr;//更新链表末端
	last = laddr;
	page_table[last].access = -1;
	return page_table[laddr].ram_addr;
}

// 逻辑地址laddr转换为物理地址paddr
static int mem_access(int laddr)
{
	if (page_table[laddr].present) {
		return algo_swap(laddr);
	}

	// 缺页处理

	// 换出链表第一项
	int out = first;
	first = page_table[first].access;

	// 换出
	if (page_table[out].modified) { // 写回
		int data = ram[page_table[out].ram_addr];
		swap[page_table[out].swap_addr] = data;
	}
	page_table[out].present = false;

	// 替换
	int paddr = page_table[out].ram_addr;
	page_table[laddr].ram_addr = paddr;

	ram[paddr] = swap[page_table[laddr].swap_addr];

	page_table[laddr].modified = false;
	page_table[laddr].present = true;

	page_table[last].access = laddr;//增加到链表尾部
	last = laddr;
	page_table[last].access = -1;
	return paddr;
}

int mem_read(int addr, char* buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	*buf = ram[paddr];

	return 0;
}

int mem_write(int addr, char buf)
{
	if (addr < 0 || addr > MEM_SIZE)
		return -1;

	int paddr = mem_access(addr);
	ram[paddr] = buf;
	page_table[addr].modified = true;

	return 0;
}

void mem_init(void)
{
	first = 0;
	// 全部加载到交换空间
	for (int i = 0; i < MEM_SIZE; i++) {
		page_table[i].swap_addr = i;
		page_table[i].present = false;
		page_table[i].modified = false;
	}
	// 部分加载到内存
	for (int i = 0; i < RAM_SIZE; i++) {
		page_table[i].ram_addr = i;
		page_table[i].present = true;
		page_table[i].access = i+1;
		last = i;
	}
	page_table[last].access = -1;
}

void mem_state(void)
{
	printf("ram state:\t");
	for (int i = 0; i < RAM_SIZE; i++) {
		printf("%02x ", ram[i]);
	}
	printf("\nswap state:\t");
	for (int i = 0; i < SWAP_SIZE; i++) {
		printf("%02x ", swap[i]);
	}
	printf("\nlinklist of ram:\t");
	for (int i = first; i != -1; i = page_table[i].access) {
		printf("%02x ", i);
	}
	printf("\n\n");
}

void mem_test(void)
{
	mem_state();

	printf("0~31为地址，在其中依次写入0~31，则前16个将会被置换\n");

	for (int i = 0; i < 32; i++) {

		mem_write(i, i);

	}

	mem_state();
	

	printf("\n访问22号单元，22→链表末段 \n ");

	mem_write(22, 22);

	mem_state();

	printf("\n访问11单元， 11 →链表末段，16→replace:\n ");

	mem_write(11, 11);

	mem_state();
}

int main(int argc, const char* argv[])
{
	mem_init();

	mem_test();

	return 0;
}
