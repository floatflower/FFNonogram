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

    /*unsigned int definedLine = 1073741824;
    unsigned int valueLine = 1073741824;
    std::vector<short> options;
    options.push_back(3);
    options.push_back(1);
    LineSolver solver;
    solver.setOptions(options);
    solver.sovle(definedLine, valueLine);
    solver.printLine(definedLine, valueLine);*/
}
