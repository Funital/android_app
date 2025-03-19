#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "Usage: %s <offset> <data> <filename>\n", argv[0]);
        return 1;
    }
    
    int offset = atoi(argv[1]);
    char *insert_data = argv[2];
    char *filename = argv[3];
    
    FILE *fp = fopen(filename, "r+");
    if(fp == NULL){
        perror("파일 열기 실패");
        return 1;
    }
    
    // 파일 크기 계산
    if(fseek(fp, 0, SEEK_END) != 0){
        perror("fseek 실패");
        fclose(fp);
        return 1;
    }
    long size = ftell(fp);
    
    // offset이 음수이거나 파일 크기를 초과하면 종료
    if(offset < 0 || offset > size){
        printf("offset이 음수이거나 읽을 수 있는 파일 크기를 초과했습니다.\n");
        fclose(fp);
        return 0;
    }
    
    // 만약 offset이 파일의 맨마지막(EOF 제외)라면 append 처리
    if(offset == size - 1 || offset == size){
        if(fseek(fp, 0, SEEK_END) != 0){
            perror("fseek 실패");
            fclose(fp);
            return 1;
        }
        fwrite(insert_data, sizeof(char), strlen(insert_data), fp);
        fclose(fp);
        return 0;
    }
    
    // 삽입일 경우 : offset+1부터 파일의 끝까지의 내용을 임시로 저장
    long tail_size = size - (offset + 1);
    char *buffer = malloc(tail_size + 1); // 널 종료를 위해 +1
    if(buffer == NULL){
        perror("메모리 할당 실패");
        fclose(fp);
        return 1;
    }
    
    // offset+1 위치로 이동하여 tail 데이터를 읽어옴
    if(fseek(fp, offset + 1, SEEK_SET) != 0){
        perror("fseek 실패");
        free(buffer);
        fclose(fp);
        return 1;
    }
    size_t read_bytes = fread(buffer, sizeof(char), tail_size, fp);
    buffer[read_bytes] = '\0';
    
    // 다시 offset+1 위치로 이동하여 삽입 데이터 기록
    if(fseek(fp, offset + 1, SEEK_SET) != 0){
        perror("fseek 실패");
        free(buffer);
        fclose(fp);
        return 1;
    }
    
    // 삽입할 데이터 쓰기
    size_t insert_len = strlen(insert_data);
    fwrite(insert_data, sizeof(char), insert_len, fp);
    
    // 미리 저장해둔 tail 데이터를 이어서 쓰기
    fwrite(buffer, sizeof(char), read_bytes, fp);
    
    free(buffer);
    fclose(fp);
    
    return 0;
}