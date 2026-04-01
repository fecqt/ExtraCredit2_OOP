//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#include "header.h"
#include <cstdio>
#include <cstdint>
#include "defines.h"

uint16_t unique_symbols_count(const uint64_t *histogram) {
    uint16_t count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (histogram[i] > 0) {
            count++;
        }
    }
    return count;
}

void write_header(FILE *infile, FILE *outfile, uint16_t unique_symbols) {
    Header h;
    h.signature = MAGIC;
    h.tree_size = 3 * unique_symbols - 1;
    fseek(infile, 0, SEEK_END);
    h.file_size = ftell(infile);
    rewind(infile);
    fwrite(&h, sizeof(Header), 1, outfile);
}
