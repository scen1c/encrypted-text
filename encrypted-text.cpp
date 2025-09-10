#include <iostream>
#include <string>
#include <sstream>  
#include <iomanip> 
using namespace std;
// Функция для преобразования строки в шестнадцатеричный формат(формат hex). Потому что шифрованный текст может содержать неотображаемые символы
string to_hex(const string& s) {
    ostringstream os;
    os << hex << setfill('0');
    for (unsigned char b : s) {
        os << setw(2) << static_cast<int>(b) << ' ';
    }
    return os.str();
}

int main() {
    string text;
    //Возьмем только младший байт ключа от 0-255
    unsigned int key;

    cout << "Text: ";
    getline(cin, text);

    cout << "Key (0-255): ";
    cin >> key;
    // Ограничиваем ключ одним байтом (0-255) ПОлучается что 0XFF = 255 в двочиной системе равен 11111111 значит все биты единицы
    key &= 0xFF;

    // Шифруем (XOR каждый символ с ключом)
    string enc = text;
    for (char& c : enc) {
    c = c ^ key;      
}
    cout << "Encrypted (hex): " << to_hex(enc) << "\n";

    // Расшифровываем тем же ключом (XOR обратим)
    string dec = enc;
    for (char& c : dec) {
        c = c ^ key;
    }
    cout << "Decrypted: " << dec << "\n";

    return 0;
}