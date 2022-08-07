#ifndef PGM_AVERAGER_HPP
#define PGM_AVERAGER_HPP

#include <string>

namespace TestAufgabe {

/* Note: this class can only deal with PGM P2 format */
class CPgmAverager {
public:
    CPgmAverager();

    virtual ~CPgmAverager();

    CPgmAverager(const CPgmAverager& other) = delete;
    CPgmAverager& operator=(const CPgmAverager& other) = delete;

    void addSource(const std::string& inputFilename);

    void produce(const std::string& outputFilename);

    void reset();

private:
    enum class ParseErrorStatus {
        noErr,
        pgmFormatNotSupportedErr,
        bufferInitBadAllocErr,
        sourceSizeInconsistErr,
        maxGrayValueInconsistErr
    };

    /* "filename" is absolute full path name of the innput .pgm file */
    ParseErrorStatus parsePgmFile(const std::string& filename);

    /* "filename" is absolute full path name of the output .pgm file */
    void generatePgmFile(const std::string& filename);

    bool m_initialized; // set to true after the first source pgm added successfully

    /* buffer holds the summation of pixel value of all provided pgm files.
       for this task. assume "u_int32_t" enough to deal with the summation of up to 2^16 = 65536 pgm
       files
     */
    u_int32_t* m_buffer;

    /* max possible count nummber. it is determined by the buffer depth (32bits) at every coordinate
     */
    static constexpr size_t MAX_COUNT = 1 << 16;

    size_t m_count; // number of source .pgm files which have been added successfully so far

    size_t m_numRow; // number of rows in provided .pgm files

    size_t m_numCol; // number of columns in provided .pgm files

    u_int16_t m_maxGrayValue; // the max possible gray value (16 bits enough for P2 PGM format)
};

} // namespace TestAufgabe

#endif