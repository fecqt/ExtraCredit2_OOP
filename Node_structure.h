//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#ifndef EXTRACREDITOOP_2_NODE_STRUCTURE_H
#define EXTRACREDITOOP_2_NODE_STRUCTURE_H
#include <cstdint>

class Node_structure {
private:
    uint8_t symbol;
    uint64_t frequency;
    Node_structure *left;
    Node_structure *right;

public:
    Node_structure(uint8_t s, uint64_t f);

    uint8_t get_symbol();

    uint64_t get_frequency();

    Node_structure *get_left();

    Node_structure *get_right();

    void set_left_node(Node_structure *n);

    void set_right_node(Node_structure *n);

    ~Node_structure();
};


#endif //EXTRACREDITOOP_2_NODE_STRUCTURE_H
