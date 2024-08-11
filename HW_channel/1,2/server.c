#include <stdio.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <string.h>  
  
int main() {  
    const char *fifoPath = "/tmp/myfifo";  
  
    // Удаляем старый FIFO, если он существует  
    if (unlink(fifoPath) == -1) {  
        perror("unlink");  
    } else {  
        printf("Server: Old FIFO removed.\n");  
    }  
  
    // Создание именованного канала (FIFO)  
    printf("Server: Creating FIFO...\n");  
    if (mkfifo(fifoPath, 0666) == -1) {  
        perror("mkfifo");  
        return 1;  
    }  
    printf("Server: FIFO created.\n");  
  
    // Открытие FIFO на запись (убран флаг O_NONBLOCK) 
    printf("Server: Opening FIFO for writing...\n");  
    int fd = open(fifoPath, O_WRONLY); 
    if (fd == -1) {  
        perror("open");  
        return 1;  
    }  
    printf("Server: FIFO opened for writing.\n");  
  
    // Запись строки в FIFO  
    const char *message = "Hi!\n";  
    printf("Server: Writing to FIFO...\n");  
    if (write(fd, message, strlen(message)) == -1) {  
        perror("write");  
        return 1;  
    }  
    printf("Server: Message written to FIFO.\n");  
  
    close(fd); // Закрываем дескриптор  
    printf("Server: FIFO closed.\n");  
  
    return 0;  
}
