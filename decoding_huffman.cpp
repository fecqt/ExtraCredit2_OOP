//
// Created by Ceangar Alexandru Iulian on 23.03.2026.
//

#include "decoding_huffman.h"
#include "header.h"
#include <stdexcept>
#include "defines.h"
#include <stack>

Node_structure *rebuild_tree(FILE *infile, uint8_t tree_size) {
    uint8_t *tree_dump = new uint8_t[tree_size];
    fread(tree_dump, sizeof(uint8_t), tree_size, infile);
    std::stack<Node_structure *> tree;

    for (uint16_t i = 0; i < tree_size; i++) {
        if (tree_dump[i] == 'L') {
            if (i + 1 < tree_size) {
                uint8_t symbol = tree_dump[++i];
                tree.push(new Node_structure(symbol, 0));
            }
        } else if (tree_dump[i] == 'I') {
            if (tree.size() < 2) {
                delete[] tree_dump;
                throw std::runtime_error("Ah! What an anomaly of a tree.");
            }
            Node_structure *right_node = tree.top();
            tree.pop();
            Node_structure *left_node = tree.top();
            tree.pop();

            Node_structure *parent_node = new Node_structure(0, 0);
            parent_node->set_left_node(left_node);
            parent_node->set_right_node(right_node);
            tree.push(parent_node);
        }
    }
    Node_structure *root = tree.top();
    delete[] tree_dump;
    return root;
}

void tree_navigation(FILE *infile, FILE *outfile, Node_structure *root, uint64_t original_size) {
    Node_structure *current_node = root;
    uint64_t decoded_symbols = 0;
    int byte;
    while (decoded_symbols < original_size && (byte = fgetc(infile)) != EOF) {
        for (int i = 0; i < 8; i++) {
            if (byte & (1 << i)) {
                current_node = current_node->get_right();
            } else {
                current_node = current_node->get_left();
            }
            if (current_node->get_right() == nullptr && current_node->get_left() == nullptr) {
                fputc(current_node->get_symbol(), outfile);
                decoded_symbols++;
                current_node = root;
                if (decoded_symbols == original_size) {
                    break;
                }
            }
        }
    }
}

void decode_file(FILE *infile, FILE *outfile) {
    Header h;
    if (fread(&h, sizeof(Header), 1, infile) != 1) {
        throw std::runtime_error("Could not read ze header!");
    }
    if (h.signature != MAGIC) {
        throw std::runtime_error("Ah! Invalid file signature! Are you sure zis is a .huff file?");
    }
    Node_structure *root = rebuild_tree(infile, h.tree_size);
    try {
        tree_navigation(infile, outfile, root, h.file_size);
    } catch (std::runtime_error &e) {
        delete root;
        throw;
    }
    delete root;
}
