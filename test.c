#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
// required for statx() system call
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <stdio.h>
#define AT_STATX_SYNC_AS_STAT   0x0000  /* - Do whatever stat() does */

// There is no glibc statx() function, it must be called using syscall().

static inline ssize_t
_statx(int dfd, const char *filename, unsigned int flags, unsigned int mask, struct statx *buffer) {
    return syscall(__NR_statx, dfd, filename, flags, mask, buffer);
}

int main () {
	char *filename = "/bin/ls";
	struct statx statx_buffer = {0};
	ssize_t ret = _statx(AT_FDCWD, filename, AT_SYMLINK_NOFOLLOW | AT_STATX_SYNC_AS_STAT, STATX_ALL, &statx_buffer);
	if (ret == 0) {
      		printf("_statx succeeded: %ld, errno: %d\n", ret, errno );
	} else {
      		printf("_statx failed: %ld, errno: %d\n", ret, errno );
	}
   	return(ret);
}

