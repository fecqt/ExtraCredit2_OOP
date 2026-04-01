//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#include "Node_structure.h"

Node_structure::Node_structure(uint8_t s, uint64_t f) {
    this->symbol = s;
    this->frequency = f;
    this->left = nullptr;
    this->right = nullptr;
}
uint8_t Node_structure::get_symbol() {
    return this->symbol;
}

uint64_t Node_structure::get_frequency() {
    return this->frequency;
}
Node_structure* Node_structure::get_left() {
    return this->left;
}

Node_structure* Node_structure::get_right() {
    return this->right;
}

void Node_structure::set_left_node(Node_structure *n) {
    this->left = n;
}
void Node_structure::set_right_node(Node_structure *n) {
    this->right = n;
}

Node_structure::~Node_structure() {
    delete this->left;
    delete this->right;
    this->left = nullptr;
    this->right = nullptr;
    this->frequency = -1;
    this->symbol = -1;
}
