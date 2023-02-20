#include "Client.h"
// #include "util.h"

using namespace std;
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

string Client::send(string destip, int destport, string message) {
//socket creation
    tcp::socket socket(io_service);

//connection
    cout<<"Starting connection..."<<endl;
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string(destip), destport));
    cout<<"Connection established!"<<endl;

//request message from client
    send_(socket, message);

//getting response from server
    string data = receive_(socket);
    
    return data;
}