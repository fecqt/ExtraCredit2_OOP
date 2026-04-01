//
// Created by Ceangar Alexandru Iulian on 23.03.2026.
//

#ifndef EXTRACREDITOOP_2_DECODING_HUFFMAN_H
#define EXTRACREDITOOP_2_DECODING_HUFFMAN_H
#include <cstdio>
#include "Node_structure.h";
#pragma once

void decode_file(FILE* infile, FILE* outfile);
Node_structure* rebuild_tree(FILE* infile, uint8_t tree_size);
void tree_navigation(FILE* infile, FILE* outfile, Node_structure* root, uint64_t original_size);

#endif //EXTRACREDITOOP_2_DECODING_HUFFMAN_H