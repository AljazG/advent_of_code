#include <list>
#include "../common/input_utils.h"
#include "../common/string_utils.h"
#include "../common/grid_utils.h"

struct Packet {
    int value{};
    bool hasValue = false;
    bool divider = false;
    vector<Packet *> packets;
};

Packet *createPacket(const string &line, int &i) {
    auto *p = new Packet();
    ++i;
    while (i < line.length()) {
        if (line[i] == ']') {
            break;
        } else if (line[i] == '[') {
            p->packets.push_back(createPacket(line, i));
        } else if (line[i] != ',') {
            string num;
            int j = i;
            while (j < line.length() && line[j] >= '0' && line[j] <= '9') {
                num += line[j];
                ++j;
            }
            i = j - 1;
            auto *valuePacket = new Packet;
            valuePacket->hasValue = true;
            valuePacket->value = stoi(num);
            p->packets.push_back(valuePacket);
        }
        ++i;
    }
    return p;
}

Packet *createPacket(const string &line) {
    int i = 0;
    return createPacket(line, i);
}

Packet *turnValuePacketIntoListPacket(Packet *packet) {
    auto *pNewParent = new Packet;
    auto *pNewChild = new Packet;
    pNewChild->hasValue = true;
    pNewChild->value = packet->value;
    pNewParent->hasValue = false;
    pNewParent->value = 0;
    pNewParent->packets.push_back(pNewChild);
    return pNewParent;
}

int comparePackets(Packet *left, Packet *right) {
    if (left->hasValue && right->hasValue) {
        if (left->value < right->value) {
            return 1;
        }
        if (left->value > right->value) {
            return -1;
        }
    }
    if (!left->hasValue && !right->hasValue) {
        for (int i = 0; i < min(left->packets.size(), right->packets.size()); i++) {
            int comparison = comparePackets(left->packets.at(i), right->packets.at(i));
            if (comparison == 1 || comparison == -1) {
                return comparison;
            }
        }
        if (left->packets.size() < right->packets.size()) {
            return 1;
        }
        if (left->packets.size() > right->packets.size()) {
            return -1;
        }
    }

    if (!left->hasValue && right->hasValue) {
        Packet *newPacket = turnValuePacketIntoListPacket(right);
        int result = comparePackets(left, newPacket);
        delete newPacket->packets.at(0);
        delete newPacket;
        return result;
    }

    if (!right->hasValue && left->hasValue) {
        Packet *newPacket = turnValuePacketIntoListPacket(left);
        int result = comparePackets(newPacket, right);
        delete newPacket->packets.at(0);
        delete newPacket;
        return result;
    }

    return 0;
}

bool funComparator(Packet *x1, Packet *x2) {
    return comparePackets(x1, x2) == 1;
}


int main() {

    vector<string> input = input_utils::readLines("../data/day13/input.txt");
    list<pair<Packet *, Packet *>> packetPairs;
    list<Packet *> packets;

    Packet *divider1 = createPacket("[[2]]");
    divider1->divider = true;
    Packet *divider2 = createPacket("[[6]]");
    divider2->divider = true;

    packets.push_back(divider1);
    packets.push_back(divider2);

    int i = 0;

    while (i < input.size()) {
        Packet *packet1 = createPacket(input[i]);
        Packet *packet2 = createPacket(input[i + 1]);

        packetPairs.emplace_back(packet1, packet2);

        packets.push_back(packet1);
        packets.push_back(packet2);
        i = i + 3;
    }

    int sum = 0;
    i = 0;

    for (auto &packetPair: packetPairs) {
        ++i;
        if (comparePackets(packetPair.first, packetPair.second) == 1) {
            sum += i;
        }
    }

    packets.sort(funComparator);

    i = 0;
    int dividerMultiplied = 1;
    for (auto *packet: packets) {
        ++i;
        if (packet->divider) {
            dividerMultiplied *= i;
        }
    }

    cout << sum << "\n";
    cout << dividerMultiplied;

    return 0;
}