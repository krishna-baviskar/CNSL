#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int MAX_SEQ = 7;
const int WINDOW_SIZE = 4;
const int TOTAL_PACKETS = 10;

double LOSS_PROB = 0.3;

bool send_packet(int seq_num) {
    double r = ((double) rand() / RAND_MAX);
    if (r < LOSS_PROB) {
        cout << "Packet " << seq_num << " lost during transmission.\n";
        return false;
    }
    cout << "Packet " << seq_num << " successfully received.\n";
    return true;
}

bool send_ack(int seq_num) {
    double r = ((double) rand() / RAND_MAX);
    if (r < LOSS_PROB) {
        cout << "ACK for packet " << seq_num << " lost.\n";
        return false;
    }
    cout << "ACK for packet " << seq_num << " received.\n";
    return true;
}

int main() {
    srand(time(0));

    int base = 0;
    int next_seq_num = 0;

    while (base < TOTAL_PACKETS) {
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
            cout << "Sender sending packet " << next_seq_num << endl;
            bool received = send_packet(next_seq_num);
            if (!received) {
                cout << "Packet loss detected. Go back to packet " << base << endl;
                next_seq_num = base;
                break;
            } else {
                bool ack_received = send_ack(next_seq_num);
                if (ack_received) {
                    cout << "ACK received for packet " << next_seq_num << endl;
                    if (next_seq_num == base) {
                        base++;
                        while (base < next_seq_num && base < TOTAL_PACKETS) {
                            base++;
                        }
                    }
                    next_seq_num++;
                } else {
                    cout << "ACK loss detected. Go back to packet " << base << endl;
                    next_seq_num = base;
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }

    cout << "All packets sent and acknowledged successfully." << endl;
    return 0;
}

