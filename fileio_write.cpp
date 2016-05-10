
#include <iostream>
#include <string>
#include <fstream>

int main() {

  // open the text file as output file stream
  std::ofstream data("data.txt");

  for (int i=0; i<3; i++) {
    // temporary vars for reading from console
    int id; // no error handling in the case the id is not a number
    std::string name;
    bool alive;

    // request and read data from the console, store in vars
    std::cout << "ID= "; std::cin >> id;
    std::cout << "Name= "; std::cin >> name; 
    std::cout << "alive= "; std::cin >> alive; 
    std::cout << std::endl;

    // write line to file
    data << std::to_string(id) << " " << name << " " << alive << std::endl;
  }
  
  // close the file
  data.close();

  return 0;
}
