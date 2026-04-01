//
// Created by Ceangar Alexandru Iulian on 21.03.2026.
//
#include <iostream>
#include <iomanip>
#include "arguments_parsing_partA.h"

void print_help() {
    std::cout << "Huffman Encoder Application\n"
            << "Usage: ./huffman [options]\n\n"
            << "Options:\n"
            << "  -h           Print zis help message and exit.\n"
            << "  -i <infile>  Specify input file to encode (default: stdin).\n"
            << "  -o <outfile> Specify output file for compressed input.\n"
            << "  -s           Print compression statistics.\n";
}

FILE *input_file(const std::string &infile_name) {
    if (infile_name.empty() || infile_name == "stdin") {
        return stdin;
    }
    FILE *f = fopen(infile_name.c_str(), "rb");
    if (!f) {
        std::cout << "Ah! Oh mai. Error opening ze file my dear.";
        exit(1);
    }
    return f;
}

FILE *output_file(const std::string &outfile_name) {
    FILE *f = fopen(outfile_name.c_str(), "wb");
    if (!f) {
        std::cout << "Ah! Oh mai. Error open ze file my dear.";
        exit(1);
    }
    return f;
}

void statistics(const CompressionStats &stats) {
    if (stats.uncompressed_size == 0) {
        return;
    }
    double space_saving = 100 * (1 - stats.compressed_size / stats.uncompressed_size);
    std::cout << "The uncompressed file size is: " << stats.uncompressed_size;
    std::cout << "The compressed file size is: " << stats.compressed_size;
    std::cout << "The space saving is: " << std::fixed << std::setprecision(2) << space_saving << "%";
}
