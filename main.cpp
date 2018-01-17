#include <iostream>
#include <vector>

#include "nonogram.h"
#include "inputreader.h"
#include "linesolver.h"
#include "worklist.h"

#include <ctime>

int main(int argc, char **argv) {
    std::string inputFileName(argv[1]);
    InputReader reader(inputFileName);
    reader.readData();
    Nonogram n; 
    time_t start;
    time_t end;
    while(reader.hasNext()) {  

      start = time(NULL);

      n.initPlayGround();
      n.setOption(reader.next());
      n.run();
      end = time(NULL);
      std::cout << "Time: " << end - start << std::endl;
    }
}
