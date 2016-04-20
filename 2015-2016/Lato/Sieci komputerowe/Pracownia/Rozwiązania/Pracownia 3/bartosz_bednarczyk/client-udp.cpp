// Bartosz Bednarczyk 273 479

#include "utils.h"
#include "MySocket.h"

int PORT, FILE_SIZE;
string OUTPUT_FILE_NAME;

bool isInputValid(int numberOfArguments, char **data) {
    assert(numberOfArguments == 4 && data != nullptr);
    PORT = stoi(data[1]);
    OUTPUT_FILE_NAME = string(data[2]);
    FILE_SIZE = stoi(data[3]);
    return (PORT >= 0 && PORT <= 65535);
}

void saveToFile(vector<string> &data) {
  ofstream out;
  out.open(OUTPUT_FILE_NAME);

  for(size_t packetNumber = 0; packetNumber < data.size(); packetNumber++) {
    out << data[packetNumber];
  }

  out.close();
}

string generateMessage(int packetNumber, int missing_bytes, int numberOfSegments) {
  int start = packetNumber * 500;
  int count = (packetNumber + 1 ==  numberOfSegments) ? missing_bytes : 500;
  return "GET " + to_string(start) + " " + to_string(count) + "\n";
}

int main(int argc, char **argv)
{
  try {
    if(!isInputValid(argc, argv)) {
      cerr << "Program terminated due to invalid input.\n";
      return -1;
    }

    MySocket s(PORT, "156.17.4.30");
    s.initializeSocket();
    int numberOfSegments = ceil( ( (double) FILE_SIZE ) / 500.0 );
    int missing_bytes = FILE_SIZE;
    vector<string> data(numberOfSegments, "");

    cout << "Downloading...\n";

    for(int packetNumber = 0; packetNumber < numberOfSegments; packetNumber++) {

      printf("%d percents done.\n", (int) floor((double) packetNumber / (double) numberOfSegments * 100));

      while(data[packetNumber] == "") {
        string message = generateMessage(packetNumber, missing_bytes, numberOfSegments);
        s.sendMessage(message);
        auto answer = s.getMessage();
        if(answer.first == packetNumber) data[packetNumber] = answer.second;
      }

      missing_bytes -= 500;
    }

    cout << "100 percents done.\nDone!\n";
    saveToFile(data);

  }
  catch(...) {
    cerr << "Program terminated due to exception.\n";
    return -1;
  }

  return 0;
}