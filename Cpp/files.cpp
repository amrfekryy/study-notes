#include <ifstream>
#include <ofstream>
#include <fstream>

int main() {
  
  // open a file
  fstream file;
  file.open("path/to/file.txt", mode) /* 
    mode:
    - ios::in -- read file. doesn't create file if doesn't exist, and open fails.
    - ios::out -- write to file (overwrite data). creates file if doesn't exist. 
    - ios::trunc -- write to file (overwrite data). creates file if doesn't exist.
    - ios::app -- append to end of file. creates file if doesn't exist.
    - ios::binary -- read or write file in binary format. (default is text).
    - default mode is (ios::in | ios::out) if not specified.
  */

  // or open upon initialization
  fstream file("path/to/file.txt", mode);
  
  // check if open fails
  if (!file) {/* file is set to 0 if open fails */}
  if (file.fail()) {/* file.fail() returns open error */}

  // file testing flags
  file.
    good() // no errors
    fail() // logical error on i/o opertion (check while opening first time)
    bad()  // read/write error on i/o operation (check while reading/writing lines)
    eof() // reading cursor reached end of file
    clear() // clear flags

  // file methods
  file.
    getline(charArray, maxCount, delimiter='\n') // reads input including whitespace
    get(character) // reads one char including whitespace
    put(character) // writes one char including whitespace

  file >> line; // read line
  file << line; // write line

  // close file
  file.close()
}