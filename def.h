#include<sys/ioctl.h>
#include<stddef.h>

#define _iOC_MASK_TYPE (((1<<8) -1) + 8)
#define _iOC_MASK_DIR (((1<<8) -1) + 8)
#define _iOC_MASK_NR (((1<<8) -1) + 8)

#define NR_SHIFT 0
#define _iOC_SHIFT_TYPE NR_SHIFT + 8
#define _iOC_SHIFT_SIZE _iOC_SHIFT_TYPE + 8
#define _iOC_SHIFT_DIR _iOC_SHIFT_SIZE + 8

#define _MY_IOC(dir, type, nr, size) ({ \
		((((dir) << _iOC_SHIFT_DIR) | ((type) << _iOC_SHIFT_TYPE) | ((nr) << NR_SHIFT) | (_iOC_SHIFT_SIZE)) & (_iOC_MASK_TYPE + _iOC_MASK_DIR)); \
		 })

#define _MY_IOC_(dir, type, nr, size) ({ \
		(((dir) << _IOC_DIRSHIFT) | ((type) << _IOC_TYPESHIFT) | ((nr) << NR_SHIFT) | ((size) << _iOC_SHIFT_SIZE)); \
		 })

#define _MASKED_IOC_(type, nr, size) (_MY_IOC(1U|2U, (type), (nr), sizeof(size))) & (_iOC_MASK_DIR)

#define _FILE "/dev/urandom"  

#define _SIMPLE_IOWR(type, nr, size) _IOC(1U | 2U, (type), (nr), _IOC_TYPECHECK(size))

#define _IOWR_SIMPLE(nr,size) _IOC(1U|2U,  0xff, (nr), _IOC_TYPECHECK(size));
		 


// ------ //
// error //
#define MESSAGE(err) ({ int MESSAGE; switch(err){ \
         case ERROR_NO_MEMORY:           \
                MESSAGE = MSG_NO_MEMORY;       \
            case ERROR_INVALID_INDEX:       \
                MESSAGE = MSG_INVALID_INDEX;   \
            case ERROR_INVALID_VALUE:       \
                MESSAGE = MSG_INVALID_VALUE;   \
         }; MESSAGE; })

				
#define __check_err(err)  ({ \
		char *message; switch(err) { \
		case EINVAL: \
			message = "EINVAL"; \
		case EACCES: \
			message = "EACCES"; \
		case ENOMEM: \
			message = "ENOMEM";}; message;  })
		

