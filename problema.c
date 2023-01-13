#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"


int check_in_mtrx_bounds(uint8_t h, uint8_t w, uint8_t i, uint8_t j) {
    return i <= h && j <= w;
}

void new_matrix(FILE *matrix_file, uint8_t m, uint8_t n) {
    fseek(matrix_file, 0, SEEK_SET);
    uint8_t header[2];
    header[0] = m;
    header[1] = n;
    
    float zero_arr[1];
    zero_arr[0] = 0;

    fwrite(header, 1, 2, matrix_file);

    for(int i = 0; i < m*n; i++) {
        fwrite(zero_arr, sizeof(float), 1, matrix_file);
    }
}

float get_elem(FILE *matrix_file, uint8_t i, uint8_t j) {
    fseek(matrix_file, 0, SEEK_SET);
    
    uint8_t header[2];
    fread(header, 2, 1, matrix_file);
    
    if(!check_in_mtrx_bounds(header[0], header[1], i, j))
        fputs("Err: indici in afara dim matricei", stderr);

    fseek(matrix_file, 2 + ((uint16_t) header[1] * i + j), SEEK_SET);
    
    float elem_arr[1];
    fread(elem_arr, 1, sizeof(float), matrix_file);
    return elem_arr[0];
}

void set_elem(FILE *matrix_file, uint8_t i, uint8_t j, float val) {
    fseek(matrix_file, 0, SEEK_SET);
    
    uint8_t header[2];
    fread(header, 2, 1, matrix_file);
    
    if(!check_in_mtrx_bounds(header[0], header[1], i, j))
        fputs("Err: indici in afara dim matricei", stderr);

    fseek(matrix_file, 2 + ((uint16_t) header[1] * i + j), SEEK_SET);
    
    float elem_arr[1];
    fwrite(elem_arr, 1, sizeof(float), matrix_file);
}

int main(int argc, char* argv[]) {
    FILE *fp = fopen("matrix.bin", "rb+");
    new_matrix(fp, 10, 5);
    //set_elem(fp, 2, 3, 1.5);

    fclose(fp);
    return 0;
}
