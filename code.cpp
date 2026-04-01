//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#include "code.h"
#include <cstring>
#include <exception>

code::code() {
    this->top = 0;
    memset(this->bits, 0, sizeof(this->bits));
}

bool code::is_empty() const {
    return this->top == 0;
}

bool code::is_full() const {
    return this->top == MAX_CODE_SIZE;
}

uint32_t code::size() const {
    return this->top;
}

bool code::push_bit(uint8_t bit) {
    if (is_full()) {
        return false;
    }
    this->bits[this->top] = bit;
    this->top++;
    return true;
}

bool code::pop_bit(uint8_t *bit) {
    if (is_empty()) {
        return false;
    }
    this->top--;
    *bit = this->bits[this->top];
    return true;
}

const uint8_t code::get_bit(uint32_t index) const {
    if (index < this->top) {
        return this->bits[index];
    }
    else {
        throw std::exception();
    }
}
