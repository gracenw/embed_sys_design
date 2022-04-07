#include "mbed.h"
#include "EthernetInterface.h"

extern "C" void mbed_mac_address(char *s);
//prints MAC address - handy if MAC is needed for ethernet network setup 
Serial pc(USBTX,USBRX);
void print_mac() {
    char mac[6];
    mbed_mac_address(mac);
    pc.printf("mbed MAC address is %02x:%02x:%02x:%02x:%02x:%02x\n\r", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); 
}

// Network interface
EthernetInterface net;

// Socket demo
int main() {
    // Show MAC in case it is needed to enable DHCP on a secure network
    char mac[6];
    mbed_mac_address(mac);
    printf("\r\rmbed's MAC address is %02x:%02x:%02x:%02x:%02x:%02x\n\r", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); 
    // Bring up the ethernet interface
    printf("Waiting for IP address from DHCP Server\n\r");
    wait(1.0);
    net.connect();
    printf("\n\rEthernet socket example\n\r");

    // Show the network address
    const char *ip = net.get_ip_address();
    printf("IP address is: %s\n\r", ip ? ip : "Timeout - No IP obtained");

    // Open a socket on the network interface, and create a TCP connection to mbed.org
    TCPSocket socket;
    socket.open(&net);
    socket.connect("hamblen.ece.gatech.edu", 80);

    // Send a simple http request
    char sbuffer[] = "GET /hello.txt HTTP/1.1\r\nHost: hamblen.ece.gatech.edu\r\n\r\n";
    int scount = socket.send(sbuffer, sizeof sbuffer);
    //print out packet
    printf("sent %d [%.*s]\n\r", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);

    // Recieve a simple http response and print out the response line and text
    char rbuffer[400]; //enough for a very short text page - almost out of RAM!
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    rbuffer[rcount] = 0; //terminate to print as a C string;
    printf("recv %d [%.*s]\n\r", rcount, strstr(rbuffer, "\r\n"), rbuffer);

    // Close the socket to return its memory and bring down the network interface
    socket.close();

    // Bring down the ethernet interface
    net.disconnect();
    printf("Done\n\r");
}
