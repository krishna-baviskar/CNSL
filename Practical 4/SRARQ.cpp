#include <iostream>
#include <vector>
#include <queue>
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


class Receiver {
    vector<bool> received;
    int expected_seq;

public:
    Receiver(int total) : received(total, false), expected_seq(0) {}

    bool receive(int seq_num) {
        if (seq_num < 0 || seq_num >= TOTAL_PACKETS) return false;
        cout << "Receiver got packet " << seq_num << "\n";
        received[seq_num] = true;
        
        while (expected_seq < TOTAL_PACKETS && received[expected_seq]) {
            expected_seq++;
        }
        return true;
    }

    int get_expected_seq() {
        return expected_seq;
    }
};


class Sender {
    int base;
    int next_seq_num;
    vector<bool> acked;
    Receiver &receiver;

public:
    Sender(Receiver &r) : base(0), next_seq_num(0), acked(TOTAL_PACKETS, false), receiver(r) {}

    void send() {
        while (base < TOTAL_PACKETS) {
           
            while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS) {
                cout << "Sender sending packet " << next_seq_num << "\n";
                bool received = send_packet(next_seq_num);
                if (received) {
                    
                    receiver.receive(next_seq_num);
                    acked[next_seq_num] = true;
                }
                else {
                    cout << "Sender will retransmit packet " << next_seq_num << " later\n";
                }
                next_seq_num++;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

            
            while (base < TOTAL_PACKETS && acked[base]) {
                cout << "Sender sliding window forward, base moves from " << base;
                base++;
                cout << " to " << base << "\n";
            }

         
            for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++) {
                if (!acked[i]) {
                    cout << "Sender retransmitting packet " << i << "\n";
                    bool received = send_packet(i);
                    if (received) {
                        receiver.receive(i);
                        acked[i] = true;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
            }
        }

        cout << "All packets sent and acknowledged successfully.\n";
    }
};

int main() {
    srand(time(0));
    Receiver receiver(TOTAL_PACKETS);
    Sender sender(receiver);

    sender.send();

    return 0;
}

