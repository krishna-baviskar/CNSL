#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int ipToInt(const string& ip) {
    int result = 0, octet = 0, count = 0;
    for (size_t i = 0; i <= ip.length(); ++i) {
        if (i == ip.length() || ip[i] == '.') {
            result = (result << 8) + octet;
            octet = 0;
            count++;
        } else {
            octet = octet * 10 + (ip[i] - '0');
        }
    }
    if (count != 4) return -1;
    return result;
}

string intToIp(int ip) {
    string result = "";
    for (int i = 3; i >= 0; --i) {
        int octet = (ip >> (i * 8)) & 0xFF;
        result += to_string(octet);
        if (i != 0) result += ".";
    }
    return result;
}

int countOnes(int mask) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if ((mask >> i) & 1) count++;
    }
    return count;
}

char detectClass(int maskBits) {
    if (maskBits <= 8) return 'A';
    else if (maskBits <= 16) return 'B';
    else return 'C';
}

int main() {
    int subnets, defaultMaskBits;
    string ip;

    cout << "Enter number of required subnets: ";
    cin >> subnets;
    cout << "Enter base IP address (e.g., 172.16.5.0): ";
    cin >> ip;
    cout << "Enter default mask bits (e.g., 8, 16, 24): ";
    cin >> defaultMaskBits;

    int ipInt = ipToInt(ip);
    if (ipInt == -1) {
        cout << "Invalid IP format.\n";
        return 1;
    }

    char ipClass = detectClass(defaultMaskBits);
    cout << "\nDetected IP Class: " << ipClass << "\n";

    int bitsToBorrow = 0;
    while ((1 << bitsToBorrow) < subnets) bitsToBorrow++;

    int newMaskBits = defaultMaskBits + bitsToBorrow;
    if (newMaskBits > 32) {
        cout << "Cannot borrow that many bits from host bits.\n";
        return 1;
    }

    int subnetMask = (~0) << (32 - newMaskBits);

    int hostBits = 32 - newMaskBits;
    int blockSize = (int)pow(2, hostBits);

    cout << "New subnet mask: " << intToIp(subnetMask)
         << " (/" << countOnes(subnetMask) << ")\n";
    cout << "Usable hosts per subnet: " << (blockSize > 2 ? blockSize - 2 : 0) << "\n";

    int baseNetwork = ipInt & ((~0) << (32 - defaultMaskBits));

    cout << "\nSubnet Table:\n";
    cout << "Subnet\tStarting Subnet\tEnding Subnet\n";

    for (int i = 0; i < (1 << bitsToBorrow); i++) {
        int network = baseNetwork + i * blockSize;
        int broadcast = network + blockSize - 1;

        cout << i + 1 << "\t"
             << intToIp(network) << "\t"
             << intToIp(broadcast) << "\n";
    }

    return 0;
}

