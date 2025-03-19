#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //open, read, write, close 함수
#include <fcntl.h> //O_RDONLY 같은 옵션들

#define READ_SIZE 10

int main(int argc, char *argv[])
{
		//파일 디스크립터를 저장할 변수 생성.
    int fd1 = 0, fd2 = 0;
    
    //read 함수의 반환 걊을 저장할 변수(읽어들인 byte수)
    int read_cnt = 0;
    
    //파일에서 읽어들인 문자열을 저장할 배열을 생성
    char f_addr[READ_SIZE];

		 /*
      *  프로그램 실행시 원본 파일과 사본 파일명을 적지 않을 경우 예외 처리
      */
    if(argc != 3)
    {
        printf("./a.out <원본파일명> <복사본파일명>\n");
        exit(1);
    }

    /* 원본 파일을 읽기 전용으로 오픈 */
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 < 0)
    {
        printf("원본 파일 열기 실패");
        exit(1);
    }

    /* 복사본 파일을 쓰기 전용, 존재하면 내용 삭제, 없으면 생성 */
    // fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd2 < 0)
    {
        printf("복사본 파일 열기 실패");
        close(fd1);
        exit(1);
    }

    /* 10바이트 단위로 원본 파일을 읽어 복사본 파일에 기록 */
    while((read_cnt = read(fd1, f_addr, READ_SIZE)) > 0)
    {
        if(write(fd2, f_addr, read_cnt) != read_cnt)
        {
            printf("쓰기 실패");
            close(fd1);
            close(fd2);
            exit(1);
        }
    }

    if(read_cnt < 0)
    {
        printf("읽기 실패");
    }

    close(fd1);
    close(fd2);
    return 0;
}