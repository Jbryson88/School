// John Bryson
// Network Programming
// Due October 3, 2022
// Dr. Zhao

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bitset>

using namespace std;

int main() {
    string ip;
    while (true) {
        cout << "Enter an IP address: ";
        cin >> ip;
        if (ip == "q") {
            break;
        }
        vector<string> octets;
        stringstream ss(ip);
        string octet;
        while (getline(ss, octet, '.')) {
            octets.push_back(octet);
        }
        reverse(octets.begin(), octets.end());
        string binary;
        for (auto octet : octets) {
            binary += bitset<8>(stoi(octet)).to_string();
        }
        cout << "Binary: " << binary << endl;
        cout << "Decimal: " << bitset<32>(binary).to_ulong() << endl;
    }
    return 0;
}