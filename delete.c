#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <offset> <byte_count> <filename>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    int byte_count = atoi(argv[2]);
    char *filename = argv[3];

    if (byte_count == 0) {
        printf("바이트 수가 0 이므로 삭제할 필요가 없습니다.\n");
        return 0;
    }

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }

    // 파일 크기 구하기
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("파일 정보 가져오기 실패");
        close(fd);
        return 1;
    }
    long file_size = st.st_size;

    if (offset < 0 || offset > file_size) {
        printf("offset이 음수이거나 파일 크기를 초과했습니다.\n");
        close(fd);
        return 0;
    }

    // 삭제할 바이트가 전체 파일 크기를 초과하지 않도록 조정
    long deletion_length = (offset + byte_count > file_size) ? file_size - offset : byte_count;
    long remaining_size = file_size - (offset + deletion_length);

    if (remaining_size > 0) {
        char buffer[4096];  // 버퍼 크기 (4096 바이트씩 이동)
        long read_pos = offset + deletion_length;
        long write_pos = offset;
        ssize_t bytes_read;

        while ((bytes_read = pread(fd, buffer, sizeof(buffer), read_pos)) > 0) {
            if (pwrite(fd, buffer, bytes_read, write_pos) != bytes_read) {
                perror("파일 이동 중 쓰기 실패");
                close(fd);
                return 1;
            }
            read_pos += bytes_read;
            write_pos += bytes_read;
        }

        if (bytes_read == -1) {
            perror("파일 이동 중 읽기 실패");
            close(fd);
            return 1;
        }
    }

    // 파일 크기를 줄임
    if (ftruncate(fd, file_size - deletion_length) == -1) {
        perror("파일 크기 조정 실패");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}