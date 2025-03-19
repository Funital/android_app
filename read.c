#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        dprintf(STDERR_FILENO, "Usage: %s <offset> <byte_count> <filename>\n", argv[0]);
        exit(1);
    }

    int offset = atoi(argv[1]);
    int byte_count = atoi(argv[2]);

    if (byte_count == 0) {
        printf("바이트 수가 0 이므로 데이터를 읽지 않습니다.\n");
        exit(0);
    }

    // 파일을 읽기 전용 모드로 오픈 (system call)
    int fd = open(argv[3], O_RDONLY);
    if (fd < 0) {
        perror("파일 열기 실패");
        exit(1);
    }

    // lseek를 사용하여 파일 크기 측정
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("파일 크기 측정 실패");
        close(fd);
        exit(1);
    }

    if (offset >= file_size) {
        printf("오프셋이 파일 크기를 초과합니다. 출력할 데이터가 없습니다.\n");
        close(fd);
        exit(0);
    }

    // 파일 오프셋을 지정 위치로 이동
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
        perror("오프셋 이동 실패");
        close(fd);
        exit(1);
    }

    // 읽어야 할 바이트 수 결정 (남은 파일 크기보다 크면 남은 만큼만 읽음)
    int to_read = byte_count;
    if (file_size - offset < byte_count) {
        to_read = file_size - offset;
    }

    // 데이터를 저장할 버퍼 할당 (+1은 널 종료문자 공간)
    char *buffer = (char *)malloc(to_read + 1);
    if (buffer == NULL) {
        perror("메모리 할당 실패");
        close(fd);
        exit(1);
    }

    // 파일에서 데이터 읽기 (system call)
    ssize_t nread = read(fd, buffer, to_read);
    if (nread < 0) {
        perror("파일 읽기 실패");
        free(buffer);
        close(fd);
        exit(1);
    }
    buffer[nread] = '\0';  // 문자열 종료

    printf("%s\n", buffer);

    free(buffer);
    close(fd);
    return 0;
}