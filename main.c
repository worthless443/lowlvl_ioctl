#include<sys/ioctl.h>
#include<linux/random.h>
#include<def.h>

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<fcntl.h>
#include<signal.h>
#include<stdarg.h>

#include<linux/securebits.h>
#include<sys/mman.h>

//#define base_adddress 0x00007ffff
#define base_address 0x00005555555551e7

struct _stat {
	int a,b;
	unsigned char buf[1<<4];
};

#define BUFSIZE 256
/* WARNING - this struct must match random.h's struct rand_pool_info */
typedef struct {
    int bit_count;               /* number of bits of entropy in data */
    int byte_count;              /* number of bytes of data in array */
    unsigned char buf[BUFSIZ];
} entropy_t;

struct my_rand_pool_info {
                  int    entropy_count;
                  int    buf_size;
                  unsigned char  buf[0];
              };

enum checker {
	_type = ((0x4e >> _iOC_SHIFT_TYPE) | _iOC_MASK_TYPE),
	_nr = ((0x4e >> NR_SHIFT) | _iOC_MASK_NR)
};
int *write_memeory(int flag, ...) { // takes at most 3 arguments
	va_list lst;
	va_start(lst, flag);
	int a, arr[4], i=0;
	while(a = va_arg(lst, int)) {
		if(a==1) break;
		if (a>-1 && a < 1000) {
			arr[i] = a;
			i++;
		}
	}
	va_end(lst);
	assert(i<3);
	struct _stat st;
	void* _mask_my_iotl = (void*)(_MASKED_IOC_(0xff, 0xff, st));
	int *ref = ((int*)base_address + (int)(void*)_mask_my_iotl);
	ref  = mmap(ref, sizeof(int), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON,0,0);
	int ret = mprotect(ref, 120, PROT_READ|PROT_WRITE);
	assert(ret==0);
	return ref;
}

void apls(int n,...)  {
	va_list lst;
	va_start(lst, n);
	int a=0;
	while(a=va_arg(lst,int)!=0) {
		printf("%d\n", a);
	}
	va_end(lst);
}

int main() {
	//write_memeory(1,2,3);
	write_memeory(2,45,10);
	return 1;
	int fd = open(_FILE,O_RDWR|O_CLOEXEC);
	struct _stat st;
	int fd_w_noblock = open(_FILE,O_NONBLOCK);
	if(!fd) raise(SIGTERM);
	struct my_rand_pool_info rnpl;
	struct rand_pool_info rnpl_;
	int _my_iotl = _MY_IOC_(1U, _type, _nr, sizeof(st));
	int _iotl= _IOWR(_IOC_TYPE(0xf), _IOC_NR(0x4), st);
	/// *deref = 69; //adress is not writable
	//printf("%d\n", *deref);
	//printf("%d | %d | %d\n", _my_iotl , _iotl, deref);
	//int ret = ioctl(fd, _iotl, &st);
	int ret1 = ioctl(fd, _IOWR(_IOC_DIR(_IOC_READ | _IOC_WRITE), _IOC_TYPE(RNDADDENTROPY), _IOC_SIZE(sizeof(rnpl_))),&rnpl_);
	int ret2 = ioctl(fd_w_noblock, _IOWR(_IOC_TYPE(RNDADDENTROPY), _IOC_NR(RNDADDENTROPY), rnpl_), &rnpl_);
	int x=0;
	entropy_t ent;
	//int ret3 = ioctl(fd_w_noblock,_IOR(_IOC_TYPE(RNDADDENTROPY), _IOC_NR(RNDADDENTROPY), ent), &ent);
	int ret3 = ioctl(fd, _SIMPLE_IOWR(_IOC_READ|_IOC_WRITE, RNDADDENTROPY, ent), &rnpl_);
	if(ret1!=0) { printf("%d\n", ret2);}
	if(ret2!=0) { printf("%d\n", ret2);}
	printf("%d\n", x);
}
