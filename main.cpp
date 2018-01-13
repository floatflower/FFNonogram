#include <iostream>
#include <vector>

#include "nonogram.h"
#include "inputreader.h"
#include "linesolver.h"
#include "worklist.h"

int main(int argc, char **argv) {
    std::string inputFileName(argv[1]);
    InputReader reader(inputFileName);
    reader.readData();

    while(reader.hasNext()) {
      Nonogram n;
      n.initPlayGround();
      n.setOption(reader.next());
      n.run();
      std::cout << std::endl;
    }
}
