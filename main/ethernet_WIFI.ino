#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x00, 0x30, 0x4F, 0x6D, 0x9B, 0xC8 }; //I made one up here it should be listed on your ethernet shield box
byte server[] = { 64, 233, 187, 99 }; // Google
byte ip[] = { 192,168, 0, 99 };
byte dns_[] = { 192,168, 0, 1 };
byte gateway[] = { 192,168, 0, 1};

char serverResponse[100];
boolean polaczony=false;    

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
