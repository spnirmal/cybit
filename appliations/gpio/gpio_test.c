#include <stdio.h>
#include <fcntl.h>
#include <n
int main(){
    fd = open("/dev/mem",O_RDWR|O_SYNC);
    if(fd < 0){
        perror("open");
    }
    
    printf("hello world\r\n");
    return 0;
}
