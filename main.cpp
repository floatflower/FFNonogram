#include <iostream>
#include <vector>

#include "nonogram.h"
#include "inputreader.h"
#include "linesolver.h"

int main(int argc, char **argv) {
    std::string inputFileName(argv[1]);
    InputReader reader(inputFileName);
    reader.readData();
    Nonogram n;
    while(reader.hasNext()) {
        n.initPlayGround();
        n.setOption(reader.next());
        n.run();
    }
}
