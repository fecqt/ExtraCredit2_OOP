//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#include "encoding_huffman.h"
#include <queue>

void build_histogram(FILE *infile, uint64_t histogram[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        histogram[i] = 0;
    }
    int character;
    while ((character = fgetc(infile)) != EOF) {
        histogram[character]++;
    }
    histogram[0]++;
    histogram[255]++;
    rewind(infile);
}

Node_structure *construct_huffman_tree(const uint64_t *histogram) {
    auto compare = [](Node_structure *left, Node_structure *right) {
        return left->get_frequency() > right->get_frequency();
    };
    std::priority_queue<Node_structure *, std::vector<Node_structure *>, decltype(compare)> pq(compare);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (histogram[i] > 0) {
            Node_structure *Node = new Node_structure(i, histogram[i]);
            pq.push(Node);
        }
    }
    while (pq.size() > 1) {
        Node_structure *left_node = pq.top();
        pq.pop();
        Node_structure *right_node = pq.top();
        pq.pop();
        Node_structure *parent_node = new Node_structure(0, left_node->get_frequency() + right_node->get_frequency());
        parent_node->set_left_node(left_node);
        parent_node->set_right_node(right_node);
        pq.push(parent_node);
    }
    if (pq.empty()) {
        return nullptr;
    }
    Node_structure *root = pq.top();
    pq.pop();
    return root;
}

void construct_code_table(Node_structure *root_node, code &current_code, code *code_table) {
    if (root_node == nullptr) {
        return;
    }
    if (root_node->get_left() == nullptr && root_node->get_right() == nullptr) {
        code_table[root_node->get_symbol()] = current_code;
        return;
    }
    uint8_t dummy;
    current_code.push_bit(0);
    construct_code_table(root_node->get_left(), current_code, code_table);
    current_code.pop_bit(&dummy);
    current_code.push_bit(1);
    construct_code_table(root_node->get_right(), current_code, code_table);
    current_code.pop_bit(&dummy);
}

void write_tree_to_file(Node_structure *root_node, FILE *outfile) {
    if (root_node == nullptr) {
        return;
    }
    write_tree_to_file(root_node->get_left(), outfile);
    write_tree_to_file(root_node->get_right(), outfile);
    if (root_node->get_right() == nullptr && root_node->get_left() == nullptr) {
        fputc('L', outfile);
        fputc(root_node->get_symbol(), outfile);
    } else {
        fputc('I', outfile);
    }
}

void compress_file(FILE *infile, FILE *outfile, code *code_table) {
    rewind(infile);
    uint8_t buffer = 0;
    int bit_count = 0;
    int character;
    while ((character = fgetc(infile)) != EOF) {
        code &current_code = code_table[character];
        for (uint32_t i = 0; i < current_code.size(); ++i) {
            uint8_t bit = current_code.get_bit(i);
            if (bit == 1) {
                buffer |= (1 << bit_count);
            }
            bit_count++;
            if (bit_count == 8) {
                bit_count = 0;
                fputc(buffer, outfile);
                buffer = 0;
            }
        }
    }
    if (bit_count > 0) {
        fputc(buffer, outfile);
    }
}
