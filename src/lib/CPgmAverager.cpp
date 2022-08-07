#include "CPgmAverager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace TestAufgabe {

CPgmAverager::CPgmAverager()
    : m_initialized{false}
    , m_buffer{nullptr}
    , m_count{0}
    , m_numRow{0}
    , m_numCol{0}
    , m_maxGrayValue{0}
{
}

CPgmAverager::~CPgmAverager()
{
    delete[] m_buffer;
}

void CPgmAverager::addSource(const std::string& inputFilename)
{
    
    if (m_count > MAX_COUNT) {
        std::cerr << "Opps. The capable limit on the max number of .pgm files exceed." << std::endl;
        throw std::runtime_error("Add source failed. Not capable to add new source");
    }

    using Err = CPgmAverager::ParseErrorStatus;
    switch (parsePgmFile(inputFilename)) {
        case(Err::bufferInitBadAllocErr):
            throw std::runtime_error("Parse Pgm failed. Buffer bad alloc by the first source. " + inputFilename);

        case(Err::pgmFormatNotSupportedErr):
            throw std::runtime_error("Parse Pgm failed. Format not supported. " + inputFilename);

        case(Err::sourceSizeInconsistErr):
            throw std::runtime_error("Parse Pgm failed. Size is different in the first source. " + inputFilename);

        case(Err::maxGrayValueInconsistErr):
            throw std::runtime_error("Parse Pgm failed. Max grayvalue is different in the first source. " + inputFilename);
        
        case(Err::noErr):
            m_count++;
            break;
        
        default:
            throw std::runtime_error("Parse Pgm failed. Unexpected result. " + inputFilename);
    }
}

void CPgmAverager::produce(const std::string& outputFilename)
{
    if (m_initialized) {
        generatePgmFile(outputFilename);
        std::cout << outputFilename << " is generated. " << std::endl;
    } else {
        throw std::logic_error("Not initialized");
    }
}

void CPgmAverager::reset()
{
    m_initialized = false;
    delete[] m_buffer;
}

CPgmAverager::ParseErrorStatus CPgmAverager::parsePgmFile(const std::string& filename)
{
    using Err = CPgmAverager::ParseErrorStatus;
    std::ifstream infile(filename);
    std::string inputLine{""};
    std::stringstream ss;
    size_t width = 0;
    size_t height = 0;

   
    // first line PGM version
    getline(infile, inputLine);
    if (inputLine.compare("P2") != 0) {
        std::cerr << "Opps. PGM version is NOT P2" << std::endl;
        return Err::pgmFormatNotSupportedErr;
    }

    // second line: size of source image
    ss << infile.rdbuf();
    ss >> width >> height;
    // std::cout << numCol << " " << numRow << std::endl;
    if (m_initialized) {
        if ((m_numRow != height) || (m_numCol != width)) {
            std::cerr << "Opps. Input .pgm file has different size than previous .pgm."
                      << std::endl;
            return Err::sourceSizeInconsistErr;
        }

    } else { // it is the very first input pgm file

        // allocate buffer dynamically
        try {
            m_buffer = new u_int32_t[height * width];
            std::fill(m_buffer, m_buffer + height * width, 0);
        } catch (std::bad_alloc& ex) {
            std::cerr << ex.what() << std::endl;
            return Err::bufferInitBadAllocErr;
        }

        m_numRow = height;
        m_numCol = width;
    }

    // third line: max value of gray pixel in current pgm file
    u_int16_t maxGrayValue;
    ss >> maxGrayValue;

    // std::cout << "maxGrayValue = " << maxGrayValue << std::endl;
    if (m_initialized) {
        if (m_maxGrayValue != maxGrayValue) {
            std::cerr << "Opps. Input .pgm file has different size than previous .pgm." << std::endl;
            return Err::maxGrayValueInconsistErr;
        }
    } else {
        m_maxGrayValue = maxGrayValue;
        m_initialized = true; // mark that initialization done
    }

    // sum up pixel value at every coordinate. Result saved to buffer
    for (size_t r = 0; r < m_numRow; ++r) {
        for (size_t c = 0; c < m_numCol; ++c) {
            u_int16_t pixelValue = 0;
            ss >> pixelValue;
            m_buffer[r * m_numCol + c] += pixelValue;
        }
    }

    return Err::noErr;
}

void CPgmAverager::generatePgmFile(const std::string& filename)
{
    std::ofstream outfile(filename, std::ios_base::out);

    // write meta info to the output file
    outfile << "P2\n" << m_numCol << " " << m_numRow << "\n" << m_maxGrayValue << "\n";

    // at every pixsel coordinate, calculate the average value and write to the output file
    for (size_t r = 0; r < m_numRow; ++r) {
        for (size_t c = 0; c < m_numCol; ++c) {
            u_int16_t avgPixelValue = m_buffer[r * m_numCol + c] / m_count;
            outfile << avgPixelValue << " ";
        }
        outfile << "\n";
    }

    outfile.close();
}

} // namespace TestAufgabe