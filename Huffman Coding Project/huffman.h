#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

class HuffmanCoding {
private:
    Node* root = nullptr;
    std::unordered_map<char, std::string> codes;
    std::unordered_map<char, int> freqMap;

    void generateCodesRecursive(Node* node, std::string code);
    void freeTree(Node* node);

public:
    ~HuffmanCoding();

    
    void reset();

    //dem tan suat ky tu trong van ban
    void buildFrequencyTable(const std::string& text);

    //xay cay Huffman tu bang tan suat
    void buildTree();

    // sinh ma nhi phan cho tung ky tu
    void generateCodes();

    // Ma hoa mot chuoi van ban thanh chuoi bit 
    std::string encode(const std::string& text);

    // Giai ma tu chuoi bit ve lai van ban goc
    std::string decode(const std::string& encoded);

    // Lay bang tan suat 
    const std::unordered_map<char, int>& getFrequencyMap() const;

    // Lay bang ma Huffman 
    const std::unordered_map<char, std::string>& getCodes() const;

    // Tinh ty le nen
    double calculateCompressionRatio(const std::string& original, const std::string& encoded) const;
};

#endif