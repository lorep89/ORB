#include <boost/tokenizer.hpp>
#include "util.h"

using namespace std;
using std::string;

string receive_(boost::asio::ip::tcp::socket & socket) {
       boost::asio::streambuf buf;
       boost::asio::read_until( socket, buf, "\n" );
       string data = boost::asio::buffer_cast<const char*>(buf.data());
       data.erase(std::remove(data.begin(), data.end(), '\n'), data.cend());
       cout<<"New message received: "<<data<<endl;
       return data;
}

void send_(boost::asio::ip::tcp::socket & socket, const string& message) {
       const string msg = message + "\n";
       // boost::asio::write(socket, boost::asio::buffer(message) );
       boost::system::error_code error;
       boost::asio::write( socket, boost::asio::buffer(msg), error );
       if( !error ) {
              cout << "Sent " << msg << endl;
       }
       else {
              cout << "Send failed: " << error.message() << endl;
       }
}

std::vector<string> splitMsg(string msg) {
       std::vector<string> ret;
       typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
       boost::char_separator<char> sep{"/"};
       tokenizer tok{msg, sep};
       for(tokenizer::iterator beg=tok.begin(); beg!=tok.end(); ++beg)
              ret.push_back(*beg);
       return ret;
}

