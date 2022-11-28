// Create a word scramble game that connects to a server and sends the scrambled word and the user's guess to the server. The server will then return the result of the guess.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace std;

// Function to scramble a word
string scramble(string word) {
    string scrambled = word;
    random_shuffle(scrambled.begin(), scrambled.end());
    return scrambled;
}

// Function to get a random word from a file
string getWord(string filename) {
    ifstream file(filename);
    string word;
    vector<string> words;
    while (file >> word) {
        words.push_back(word);
    }
    return words[rand() % words.size()];
}

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <host> <port>" << endl;
        return 1;
    }

    // Get the host and port from the command line arguments
    string host = argv[1];
    string port = argv[2];

    // Seed the random number generator
    srand(time(NULL));

    // Get a random word from the file
    string word = getWord("words.txt");

    // Scramble the word
    string scrambled = scramble(word);

    // Connect to the server
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    // Send the scrambled word to the server
    boost::asio::write(socket, boost::asio::buffer(scrambled));

    // Get the user's guess
    string guess;
    cout << "Guess the word: " << scrambled << endl;
    cin >> guess;

    // Send the user's guess to the server
    boost::asio::write(socket, boost::asio::buffer(guess));

    // Get the result from the server
    boost::array<char, 128> buf;
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(buf), error);

    // Print the result
    cout << string(buf.data(), len) << endl;

    return 0;
}


