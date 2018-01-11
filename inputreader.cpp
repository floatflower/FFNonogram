#include "inputreader.h"

#include <fstream>
#include <string>
#include <iostream>

#include "macro.h"

InputReader::InputReader(std::string inputFile)
    : m_inputFileName(inputFile)
    , m_currentQuestion(0)
    , m_inputFileSize(0)
{

}

InputReader::~InputReader()
{

}

std::vector<std::vector<short>> InputReader::next()
{
    int current = m_currentQuestion;
    m_currentQuestion ++;
    return m_inputFileContent.at(current);
}

void InputReader::setInputFileName(std::string inputFile)
{
    m_inputFileName = inputFile;
}

void InputReader::readData()
{
    std::ifstream inputFile(m_inputFileName);
    std::string line;
    if (inputFile.is_open()) {

        while(!inputFile.eof()) {
            // get question number

            getline(inputFile, line);
            std::vector<std::vector<short>> currentQuestion;
            // get question data
            for (int i = 0; i < INPUTDATA_ROWS; i ++) {
                getline(inputFile, line);
                short currentRead = 0;
                std::vector<short> currentRow;
                for (std::string::iterator it_line = line.begin();
                     it_line != line.end();
                     it_line ++) {
                    if ((*it_line) != '\t') {
                        currentRead *= 10;
                        currentRead += (*it_line) - 48;
                    }
                    else {
                        currentRow.push_back(currentRead);
                        currentRead = 0;
                    }
                }
                currentRow.push_back(currentRead);
                currentRead = 0;
                currentQuestion.push_back(currentRow);
            }
            m_inputFileContent.push_back(currentQuestion);
        }
        inputFile.close();
        m_inputFileSize = m_inputFileContent.size();
    }
}

bool InputReader::hasNext()
{
    return m_currentQuestion < m_inputFileSize;
}
