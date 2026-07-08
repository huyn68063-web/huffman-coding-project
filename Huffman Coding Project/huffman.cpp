#include "huffman.h"
#include <queue>
#include <vector>

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

HuffmanCoding::~HuffmanCoding() {
    freeTree(root);
}

void HuffmanCoding::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

void HuffmanCoding::reset() {
    freeTree(root);
    root = nullptr;
    codes.clear();
    freqMap.clear();
}

void HuffmanCoding::buildFrequencyTable(const std::string& text) {
    for (char c : text) freqMap[c]++;
}

void HuffmanCoding::buildTree() {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (auto& p : freqMap) pq.push(new Node(p.first, p.second));
    if (pq.empty()) return;

    if (pq.size() == 1) {
        Node* only = pq.top(); pq.pop();
        root = new Node('\0', only->freq, only, nullptr);
        return;
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq, left, right);
        pq.push(merged);
    }
    root = pq.top();
}

void HuffmanCoding::generateCodesRecursive(Node* node, std::string code) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->ch] = code.empty() ? "0" : code;
        return;
    }
    generateCodesRecursive(node->left, code + "0");
    generateCodesRecursive(node->right, code + "1");
}

void HuffmanCoding::generateCodes() {
    generateCodesRecursive(root, "");
}

std::string HuffmanCoding::encode(const std::string& text) {
    std::string encoded = "";
    for (char c : text) encoded += codes[c];
    return encoded;
}

std::string HuffmanCoding::decode(const std::string& encoded) {
    std::string decoded = "";
    Node* current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

const std::unordered_map<char, int>& HuffmanCoding::getFrequencyMap() const {
    return freqMap;
}

const std::unordered_map<char, std::string>& HuffmanCoding::getCodes() const {
    return codes;
}

double HuffmanCoding::calculateCompressionRatio(const std::string& original, const std::string& encoded) const {
    long long originalBits = (long long)original.size() * 8;
    long long compressedBits = (long long)encoded.size();
    if (originalBits == 0) return 0.0;
    return 100.0 * (1.0 - (double)compressedBits / originalBits);
}