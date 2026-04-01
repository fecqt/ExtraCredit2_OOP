#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include "encoding_huffman.h"
#include "decoding_huffman.h" // Your new file!
#include "arguments_parsing_partA.h"
#include "defines.h"
#include "header.h"
int main(int argc, char *argv[]) {
    try {
        std::string in_name = "";
        std::string out_name = "";
        bool decompress = false;
        int opt;

        while ((opt = getopt(argc, argv, "i:o:hd")) != -1) {
            switch (opt) {
                case 'i': in_name = optarg; break;
                case 'o': out_name = optarg; break;
                case 'd': decompress = true; break;
                case 'h': print_help(); return 0;
                default:  return 1;
            }
        }

        if (in_name.empty() || out_name.empty()) {
            throw std::runtime_error("Usage: ./huffman -i <input> -o <output> [-d for decompress]");
        }

        // Open files in Binary Mode
        FILE *infile = fopen(in_name.c_str(), "rb");
        if (!infile) throw std::runtime_error("Could not open input file: " + in_name);

        FILE *outfile = fopen(out_name.c_str(), "wb");
        if (!outfile) {
            fclose(infile);
            throw std::runtime_error("Could not open output file: " + out_name);
        }

        if (decompress) {
            std::cout << "Starting decompression..." << std::endl;
            decode_file(infile, outfile);
            std::cout << "Decompression complete!" << std::endl;
        } else {
            std::cout << "Starting compression..." << std::endl;

            // 1. Histogram
            uint64_t histogram[ALPHABET_SIZE];
            build_histogram(infile, histogram);

            // 2. Tree
            Node_structure *root = construct_huffman_tree(histogram);
            if (!root) throw std::runtime_error("Empty file or tree build failed.");

            // 3. Codes
            code code_table[ALPHABET_SIZE];
            code current_code;
            construct_code_table(root, current_code, code_table);

            // 4. Header & Write
            uint16_t unique = unique_symbols_count(histogram);
            write_header(infile, outfile, unique);
            write_tree_to_file(root, outfile);
            compress_file(infile, outfile, code_table);

            delete root;
            std::cout << "Compression complete!" << std::endl;
        }

        fclose(infile);
        fclose(outfile);

    } catch (const std::exception &e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}