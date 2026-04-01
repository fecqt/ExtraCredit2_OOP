//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#ifndef EXTRACREDITOOP_2_HEADER_H
#define EXTRACREDITOOP_2_HEADER_H

#pragma once
#include <cstdint>
#include <cstdio>
struct Header {
    uint64_t signature;
    uint16_t tree_size;
    uint64_t file_size;
};

void write_header(FILE *infile, FILE *outfile, uint16_t unique_symbols);
uint16_t unique_symbols_count(const uint64_t *histogram);

#endif //EXTRACREDITOOP_2_HEADER_H
