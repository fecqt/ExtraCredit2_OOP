Huffman File Compressor & Decompressor
A high-performance C++ implementation of the Huffman Coding algorithm. This utility provides lossless data compression by assigning variable-length binary codes to characters based on their frequency in the input text.

 Purpose
The goal of this project is to reduce the storage footprint of text files without losing a single bit of information. By replacing standard fixed-length 8-bit ASCII encoding with custom-generated bit-sequences, we can achieve significant space savings on redundant data.

 How It Works
The Compression Process (Encoding)

Frequency Analysis: The program scans the input file and builds a histogram of every character's occurrence.

Priority Queue & Tree Construction: Each unique character becomes a leaf node. These nodes are combined into a Binary Tree using a min-priority queue, ensuring that the most frequent characters stay closest to the root.

Code Table Generation: The tree is traversed to assign unique bit-paths to each character (e.g., 'e' might become 10, while 'z' becomes 1110101).

Bit-Packing: These variable-length codes are packed into 8-bit buffers and written to a binary .huff file.

Serialization: The Huffman tree structure and the original file size are saved in a custom header so the file can be reconstructed later.

The Decompression Process (Decoding)

Header Verification: Validates the 0xDEADEAEF magic number to ensure file integrity.

Tree Reconstruction: Uses a Stack to rebuild the Huffman tree from the serialized post-order traversal found in the header.

Bit-Navigation: Reads the compressed data one bit at a time, "walking" the tree (0 for Left, 1 for Right) until a leaf node is reached, at which point the original character is recovered.

 Algorithm Analysis:
Advantages & Best Use Cases

Lossless Compression: Ideal for source code, configuration files, and text documents where every character is vital.

High Entropy Efficiency: Works best on files with high redundancy (e.g., a book where 'e', 't', and 'a' appear much more often than 'q' or 'z').

Small Alphabets: Extremely effective for data types with limited variety, such as DNA sequences (A, C, G, T) or simple log files.

 Disadvantages & Constraints

Two-Pass Overhead: The encoder must read the file twice (once for the histogram and once to compress), which can be slow for massive files.

Negative Compression: For very small files, the metadata (Header + Tree Map) might take up more space than the actual data saved.

Uniform Distribution: If every character appears the same number of times, the compression ratio will be near 0%.

Incompressibility: Files that are already compressed (like .zip, .png, or .mp3) cannot be significantly reduced further by Huffman alone.

Usage:
g++ -o huffman *.cpp
./huffman -i input.txt -o compressed.huff -> for encoding
./huffman -i compressed.huff -o restored.txt -> for decoding

The compressed .huff file follows a strict binary structure:

Magic Number (4 bytes): 0xDEADEAEF

Tree Size (2 bytes): Number of bytes used to store the serialized tree.

Original Size (8 bytes): Total characters in the uncompressed file.

Tree Dump: Post-order traversal of the Huffman tree.

Data: The actual compressed bits.
