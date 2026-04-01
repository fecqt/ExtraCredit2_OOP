//
// Created by Ceangar Alexandru Iulian on 22.03.2026.
//

#ifndef EXTRACREDITOOP_2_CODE_H
#define EXTRACREDITOOP_2_CODE_H
#include "defines.h"
#include <cstdint>
#pragma once

class code {
private:
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];

public:
    code();

    bool is_empty() const;

    bool is_full() const;

    uint32_t size() const;

    bool push_bit(uint8_t bit);

    bool pop_bit(uint8_t *bit);

    const uint8_t get_bit(uint32_t index) const;
};


#endif //EXTRACREDITOOP_2_CODE_H
