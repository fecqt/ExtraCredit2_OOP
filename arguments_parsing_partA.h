//
// Created by Ceangar Alexandru Iulian on 21.03.2026.
//

#ifndef EXTRACREDITOOP_2_ARGUMENTS_PARSING_PARTA_H
#define EXTRACREDITOOP_2_ARGUMENTS_PARSING_PARTA_H
#pragma once
#include <cstdio>
#include <string>

struct CompressionStats {
    long compressed_size, uncompressed_size;
};

void print_help(); // -h
FILE *input_file(const std::string &infile_name);; // -i
FILE *output_file(const std::string &outfile_name); //-o
void statistics(const CompressionStats &stats); //-s


#endif //EXTRACREDITOOP_2_ARGUMENTS_PARSING_PARTA_H
