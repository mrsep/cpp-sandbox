
#include <iostream>
#include <string>
#include <fstream>

int main() {

  // open the text file as input file stream
  std::ifstream data("data.txt");

  if (data) {
    // temporary vars for reading from the file
    int id;
    std::string name;
    bool alive;

    // read from the file stream line by line and print to console
    while (data >> id >> name >> alive) {
      std::cout << id << ":" << name << " alive: " << alive << std::endl;
    }

    // close the file
    data.close();
  }
  else {
    std::cout << "The file could not be found!" << std::endl;
  }
  return 0;
}
