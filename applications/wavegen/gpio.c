#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(){
    int fd;

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(fd < 0){
        perror("open");
        return -1;
    }

    void *gpio = mmap(
                    NULL,  // let kernel choose virtual address
                    4096,  //one page
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    fd,
                    0x3f200000 //gpio physical base
                    );
}

