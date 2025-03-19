#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //open, read, write, close 함수
#include <fcntl.h> //O_RDONLY 같은 옵션들

#define READ_SIZE 1024

int main(int argc, char *argv[]) {
    int fd_dest, fd1, fd2;
    char f_addr[READ_SIZE];
    int bytes_read, bytes_written;

    if (argc != 4) {
        printf("Usage: a.out <destination file> <source file1> <source file2>\n";)
        exit(1);
    }
    
    /* 대상 파일 열기: 쓰기 전용, 이미 존재하면 내용 삭제, 없으면 새로 생성 */
    fd_dest = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_dest < 0) {
        perror("대상 파일 열기 실패");
        exit(1);
    }
    
    /* 첫번째 소스 파일 열기: 읽기 전용 */
    fd1 = open(argv[2], O_RDONLY);
    if (fd1 < 0) {
        printf("첫번째 소스 파일 열기 실패");
        close(fd_dest);
        exit(1);
    }
    
    /* 두번째 소스 파일 열기: 읽기 전용 */
    fd2 = open(argv[3], O_RDONLY);
    if (fd2 < 0) {
        printf("두번째 소스 파일 열기 실패");
        close(fd_dest);
        close(fd1);
        exit(1);
    }
    
    /* 첫번째 소스 파일의 데이터를 대상 파일에 복사 */
    while ((bytes_read = read(fd1, f_addr, READ_SIZE)) > 0) {
        int remaining = bytes_read;
        char *ptr = f_addr;
        while (remaining > 0) {
            bytes_written = write(fd_dest, ptr, remaining);
            if (bytes_written <= 0) {
                perror("대상 파일에 쓰기 실패");
                close(fd_dest);
                close(fd1);
                close(fd2);
                exit(1);
            }
            remaining -= bytes_written;
            ptr += bytes_written;
        }
    }
    if (bytes_read < 0) {
        perror("첫번째 소스 파일 읽기 실패");
        close(fd_dest);
        close(fd1);
        close(fd2);
        exit(1);
    }
    
    /* 두번째 소스 파일의 데이터를 대상 파일에 복사 */
    while ((bytes_read = read(fd2, f_addr, READ_SIZE)) > 0) {
        int remaining = bytes_read;
        char *ptr = f_addr;
        while (remaining > 0) {
            bytes_written = write(fd_dest, ptr, remaining);
            if (bytes_written <= 0) {
                perror("대상 파일에 쓰기 실패");
                close(fd_dest);
                close(fd1);
                close(fd2);
                exit(1);
            }
            remaining -= bytes_written;
            ptr += bytes_written;
        }
    }
    if (bytes_read < 0) {
        perror("두번째 소스 파일 읽기 실패");
        close(fd_dest);
        close(fd1);
        close(fd2);
        exit(1);
    }
    
    close(fd_dest);
    close(fd1);
    close(fd2);
    
    return 0;
}