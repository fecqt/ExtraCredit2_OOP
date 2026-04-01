//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#ifndef EXTRACREDITOOP_2_ENCODING_HUFFMAN_H
#define EXTRACREDITOOP_2_ENCODING_HUFFMAN_H
#include "defines.h"
#pragma once
#include <cstdio>
#include <cstdint>
#include "Node_structure.h"
#include "code.h"

void build_histogram(FILE *infile, uint64_t histogram[ALPHABET_SIZE]);

Node_structure *construct_huffman_tree(const uint64_t *histogram);

void construct_code_table(Node_structure *root_node, code &current_code, code *code_table);

void write_tree_to_file(Node_structure *root_node, FILE *outfile);

void compress_file(FILE *infile, FILE *outfile, code *code_table);

#endif //EXTRACREDITOOP_2_ENCODING_HUFFMAN_H
