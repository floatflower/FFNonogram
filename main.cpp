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
    
    int questionNumber = 1;
    while(reader.hasNext()) {  
      
      n.initPlayGround();
      n.setOption(reader.next());
      n.run(questionNumber);
      questionNumber ++;

    }
}
