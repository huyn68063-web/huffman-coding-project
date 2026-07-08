#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include "huffman.h"

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    (void)color;
#endif
}

#define RESET 7
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define CYAN 3
#define WHITE 7
#define PURPLE 5

void printHeader() {
    setColor(CYAN);
    cout << "\n============================================================\n";
    cout << "   HUFFMAN CODING - CHUONG TRINH NEN DU LIEU\n";
    cout << "============================================================\n";
    setColor(RESET);
}

void printMenu() {
    setColor(YELLOW);
    cout << "\n[1] Nhap chuoi tu ban phim\n";
    cout << "[2] Doc du lieu tu file .txt\n";
    cout << "[3] Chay bo du lieu mau\n";
    setColor(RED);
    cout << "[0] Thoat chuong trinh\n";
    setColor(RESET);
    cout << "\nLua chon cua ban: ";
}

void printTable(HuffmanCoding& huff) {
    setColor(YELLOW);
    cout << "\n+----------------+------------+------------------+\n";
    cout << "| Ky tu          | Tan suat   | Ma Huffman       |\n";
    cout << "+----------------+------------+------------------+\n";
    setColor(RESET);

    const unordered_map<char, string>& codeMap = huff.getCodes();
    const unordered_map<char, int>& freqMap = huff.getFrequencyMap();

    for (unordered_map<char, string>::const_iterator it = codeMap.begin(); it != codeMap.end(); ++it) {
        char c = it->first;
        string display;
        if (c == ' ') display = "[space]";
        else if (c == '\n') display = "[newline]";
        else if (c == '\r') display = "[CR]";
        else display = string(1, c);

        setColor(WHITE);
        cout << "| " << left << setw(15) << display;
        setColor(GREEN);
        cout << "| " << setw(11) << freqMap.at(c);
        setColor(CYAN);
        cout << "| " << setw(17) << it->second << "|\n";
        setColor(RESET);
    }
    setColor(YELLOW);
    cout << "+----------------+------------+------------------+\n";
    setColor(RESET);
}

void printResult(const string& original, const string& encoded, const string& decoded, double ratio) {
    setColor(GREEN);
    cout << "\nKiem tra giai ma: ";
    if (decoded == original) {
        setColor(GREEN);
        cout << "dung khop voi ban goc\n";
    } else {
        setColor(RED);
        cout << "sai lech!\n";
    }

    setColor(YELLOW);
    cout << "\nKich thuoc goc      : ";
    setColor(WHITE);
    cout << (original.size() * 8) << " bit\n";

    setColor(YELLOW);
    cout << "Sau khi nen         : ";
    setColor(WHITE);
    cout << encoded.size() << " bit\n";

    setColor(YELLOW);
    cout << "Ty le nen           : ";
    setColor(GREEN);
    cout << fixed << setprecision(2) << ratio << "%\n";

    setColor(RESET);
}

void runOnText(const string& text) {
    if (text.empty()) {
        setColor(RED);
        cout << "\n[!] Du lieu rong!\n";
        setColor(RESET);
        return;
    }

    HuffmanCoding huff;
    huff.buildFrequencyTable(text);
    huff.buildTree();
    huff.generateCodes();

    printTable(huff);

    string encoded = huff.encode(text);
    string decoded = huff.decode(encoded);
    double ratio = huff.calculateCompressionRatio(text, encoded);

    printResult(text, encoded, decoded, ratio);
}

// Cho nguoi dung nhan Enter de tiep tuc.
// QUAN TRONG: neu cin da het du lieu dau vao that su (EOF), tra ve false
// de main() thoat chuong trinh an toan thay vi lap vo han.
bool waitForEnter() {
    setColor(WHITE);
    cout << "\nNhan Enter de tiep tuc...";
    setColor(RESET);
    cin.get();
    if (cin.fail() || cin.eof()) return false;
    return true;
}

int main() {
    int choice;
    bool running = true;

    while (running) {
        printHeader();
        printMenu();

        if (!(cin >> choice)) {
            // Het du lieu dau vao hoac loi nhap -> thoat an toan
            break;
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                setColor(WHITE);
                cout << "\nNhap chuoi can nen: ";
                string text;
                getline(cin, text);
                cout << "\n";
                runOnText(text);
                if (!waitForEnter()) running = false;
                break;
            }
            case 2: {
                setColor(WHITE);
                cout << "\nNhap ten file (vd: data1.txt): ";
                string filename;
                getline(cin, filename);

                ifstream file(filename);
                if (!file) {
                    setColor(RED);
                    cout << "\n[!] Khong tim thay file!\n";
                    setColor(RESET);
                } else {
                    stringstream buffer;
                    buffer << file.rdbuf();
                    string content = buffer.str();
                    file.close();

                    setColor(GREEN);
                    cout << "\n[OK] Da doc file thanh cong! (" << content.size() << " ky tu)\n";
                    setColor(RESET);
                    runOnText(content);
                }
                if (!waitForEnter()) running = false;
                break;
            }
            case 3: {
                setColor(YELLOW);
                cout << "\n\n>>> Bo du lieu 1 - Chuoi lap lai nhieu ky tu\n";
                cout << "============================================================\n";
                setColor(RESET);
                runOnText("aaaaaaaaaabbbbbbcccdd");

                setColor(YELLOW);
                cout << "\n\n>>> Bo du lieu 2 - Chuoi khong lap ky tu\n";
                cout << "============================================================\n";
                setColor(RESET);
                runOnText("abcdefghijklmnopqrstuvwxyz");

                setColor(YELLOW);
                cout << "\n\n>>> Bo du lieu 3 - Cau tieng Anh mau\n";
                cout << "============================================================\n";
                setColor(RESET);
                runOnText("this is an example of a huffman tree");

                setColor(YELLOW);
                cout << "\n\n>>> Bo du lieu 4 - Truong hop bien: 500 ky tu lap lai\n";
                cout << "============================================================\n";
                setColor(RESET);
                runOnText(string(500, 'a'));

                if (!waitForEnter()) running = false;
                break;
            }
            case 0: {
                setColor(CYAN);
                cout << "\n============================================================\n";
                cout << "   CAM ON BAN DA SU DUNG CHUONG TRINH!\n";
                cout << "============================================================\n";
                setColor(RESET);
                running = false;
                break;
            }
            default:
                setColor(RED);
                cout << "\n[!] Lua chon khong hop le!\n";
                setColor(RESET);
                if (!waitForEnter()) running = false;
        }
    }

    return 0;
}