#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4){
        fprintf(stderr, "Usage: %s <offset> <data> <filename>\n", argv[0]);
        return 1;
    }

    int offset = atoi(argv[1]);
    if(offset < 0){
        fprintf(stderr, "오프셋은 음수가 될 수 없습니다.\n");
        return 1;
    }

    FILE *fp = fopen(argv[3], "r+");
    if(fp == NULL){
        perror("파일 열기 실패");
        return 1;
    }

    // 지정한 오프셋으로 이동 (EOF를 만나더라도 위치 지정에 문제 없음)
    if(fseek(fp, offset, SEEK_SET) != 0){
        perror("fseek 실패");
        fclose(fp);
        return 1;
    }

    // argv[2]의 데이터를 덮어쓰기 진행 (EOF에 도달해도 계속 써서 파일이 확장됨)
    if(fputs(argv[2], fp) == EOF){
        perror("쓰기 실패");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}