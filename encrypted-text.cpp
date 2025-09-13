#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <limits>
using namespace std;

// УТИЛИТЫ
string to_hex(const string& s) {
    ostringstream os;
    os << hex << setfill('0');
    for (unsigned char b : s) os << setw(2) << static_cast<int>(b) << ' ';
    return os.str();
}

// не мой код, но работает
// обратное шифрование to_hex
string hex_to_bytes(const string& hex) {
    auto hexval = [](char c) -> int {
        if ('0' <= c && c <= '9') return c - '0';
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        if ('a' <= c && c <= 'f') return 10 + (c - 'a');
        return -1;
    };

    string out;
    int hi = -1;
    for (char ch : hex) {
        int v = hexval(ch);
        if (v == -1) continue;            // пока хрен значет chat gpt
        if (hi < 0) hi = v;
        else {
            unsigned char b = static_cast<unsigned char>((hi << 4) | v);
            out.push_back(static_cast<char>(b));
            hi = -1;
        }
    }
    return out;
}

// Читаем файлик
string read_file_all(const string& path) {
    ifstream in(path);
    if (!in) return {};
    ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

// Шифровка/расшифровка
string xor_with_key(string data, unsigned int key) {
    key &= 0xFF;
    for (char& c : data) c = static_cast<char>(static_cast<unsigned char>(c) ^ key);
    return data;
}

// приложуние
int main() {
    int choice;

    do {
        cout << "-------------------------------\n"
             << "Encrypted Text Display Tool\n"
             << "------------------------------\n"
             << "Select an option:\n"
             << "1) Write encrypted text\n"
             << "2) Find decrypted text\n"
             << "0) Exit\n"
             << "Enter your choice (0-2): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string text;
                unsigned int key;

                cout << "Text: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Чат гпт сказал очистить буфер, ну ладно
                getline(cin, text);

                cout << "Key (0-255): ";
                cin >> key;

                string enc = xor_with_key(text, key);
                cout << "Encrypted (hex): " << to_hex(enc) << "\n\n";

                char saveChoice;
                cout << "Do you want to save encrypted text to file? (y/n): ";
                cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y') {
                    string filename;
                    cout << "Write the name of this file (without extension): ";
                    cin >> filename;

                    ofstream outFile(filename + ".txt", ios::app);
                    if (outFile) {
                        outFile << to_hex(enc) << "\n";
                        cout << "Encrypted text saved to " << filename << ".txt\n\n";
                    } else {
                        cout << "Error: could not open file for writing.\n\n";
                    }
                } else {
                    cout << "Encrypted text not saved.\n\n";
                }
                break;
            }

            case 2: {
                cout << "Decrypt source:\n"
                     << "1) Enter encrypted text manually (HEX)\n"
                     << "2) Load encrypted text from file (HEX)\n"
                     << "Enter your choice (1-2): ";
                int src;
                cin >> src;

                string hexInput;

                if (src == 1) {
                    cout << "Paste HEX string (example: 41 42 43 or 414243):\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // опять очистка буфера
                    getline(cin, hexInput);
                } else if (src == 2) {
                    string filename;
                    cout << "Enter file name (with or without .txt): ";
                    cin >> filename;
                    if (filename.size() < 4 || filename.substr(filename.size()-4) != ".txt")
                        filename += ".txt";

                    hexInput = read_file_all(filename);
                    if (hexInput.empty()) {
                        cout << "Error: could not read file or file is empty.\n\n";
                        break;
                    }
                } else {
                    cout << "Invalid choice.\n\n";
                    break;
                }

                // с hex в байты
                unsigned int key;
                cout << "Key (0-255): ";
                cin >> key;

                string cipherBytes = hex_to_bytes(hexInput);
                if (cipherBytes.empty()) {
                    cout << "Error: HEX input is empty or invalid.\n\n";
                    break;
                }

                string plain = xor_with_key(cipherBytes, key);
                cout << "Decrypted text: " << plain << "\n\n";

                // сохранение
                char saveChoice;
                cout << "Save decrypted text to file? (y/n): ";
                cin >> saveChoice;
                if (saveChoice == 'y' || saveChoice == 'Y') {
                    string filename;
                    cout << "Write the name of this file (without extension): ";
                    cin >> filename;
                    ofstream outFile(filename + ".txt", ios::app);
                    if (outFile) {
                        outFile << plain << "\n";
                        cout << "Decrypted text saved to " << filename << ".txt\n\n";
                    } else {
                        cout << "Error: could not open file for writing.\n\n";
                    }
                }
                break;
            }

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Error: invalid choice!\n\n";
        }
    } while (choice != 0);

    return 0;
}