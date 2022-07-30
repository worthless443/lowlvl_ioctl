#include<stdlib.h>
#include<sys/mman.h>
#include<stdio.h>
#include<stdarg.h>
#define base_address 0x00005555555551e7
//#define base_address 0xfffffffffffff001
//#define base_address 0x1000000

void *write_mem() {
	//int *addr = mmap((void*)base_address, sizeof(int), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, 0,0);
	//LONG INT i_addr __attribute__ ((aligned (16))) = base_address;
	int *a = (int*)malloc(100);
	int pageSize = 1<<12;
	//int i_addr = ((int)a  & ~(pageSize - 1));
	int *addr = (int*)base_address;
	//int *addr = mmap((int*)i_addr, sizeof(int), PROT_NONE, MAP_PRIVATE|MAP_ANON,0,0);
	int ret = mprotect(addr, sizeof(int)*100,PROT_READ|PROT_WRITE);
	*addr = 1;
	//*addr = 1;
	printf("%d\n", ret);
	return addr;

}

void apls(int n,...)  {
	va_list lst;
	va_start(lst, n);
	int a,i=0;
	while(a = va_arg(lst, int)) {
			if(a==1) break;
			if (a>-1 && a < 1000) i++;

	}
	printf("%d\n", i);
	va_end(lst);
}

int sum(int num_args, ...) {
   int val = 0;
   va_list ap;
   int i,count=0;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
      count+=1;
   }
   printf("%d\n", count);
   va_end(ap);

   return val;
}

int main() {
	apls(69,5,6,5);
	//write_mem();
	return 0;
}
