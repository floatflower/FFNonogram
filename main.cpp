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
    Nonogram n;
    while(reader.hasNext()) {
        n.initPlayGround();
        n.setOption(reader.next());
        n.run();
    }

   	/*LineSolver s;
   	s.init();
   	std::vector<short> options;
   	options.push_back(2);
   	s.setOptions(options);
   	unsigned int a = 0x80000000;
   	unsigned int b = 0x80000000;
	s.printLine(a, b);
   	s.sovle(a, b);
   	s.printLine(a, b);*/
}
