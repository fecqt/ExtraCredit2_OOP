cmake_minimum_required(VERSION 4.1)
project(ExtraCreditOOP_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExtraCreditOOP_2 main.cpp
        arguments_parsing_partA.cpp
        arguments_parsing_partA.h
        encoding_huffman.cpp
        encoding_huffman.h
        Node_structure.cpp
        Node_structure.h
        code.cpp
        code.h
        header.cpp
        header.h
        defines.h
        decoding_huffman.cpp
        decoding_huffman.h)
