#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <iostream>
#include <vector>

class InputReader
{
public:
    InputReader(std::string inputFile);
    ~InputReader();
    /**
    * All input data options is managed by InputReader,
    * After solving a question, call next() function to get the next question.
    *
    * Inspired by Lexer.
    *
    * @return std::vector<short>
    */
    std::vector<std::vector<short>> next();

    /**
    * Set input file name
    *
    * @param std::string inputFile
    */
    void setInputFileName(std::string inputFile);

    /**
    * Call the function to start reading data.
    * All data read will be stored into m_inputFileContent;
    */
    void readData();

    /**
    * call hasNext() function to get next question.
    *
    * @return bool
    */
    bool hasNext();

private:
    std::string m_inputFileName;
    std::vector<std::vector<std::vector<short>>> m_inputFileContent;
    int m_currentQuestion;
    int m_inputFileSize;
};

#endif // INPUTREADER_H
