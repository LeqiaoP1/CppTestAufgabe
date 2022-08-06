#include "CPgmAverager.hpp"

#include <filesystem>
#include <iostream>
#include <string_view>

namespace {
void printUsage()
{
    std::cout << "Usage: testCli -d <directory_path>"
                 "\n  where <directory_path>\tin which input .pgm images and the output "
                 "average.pgm are located"
                 "\n  example: testCli -d ./data"
              << std::endl;
}
} // namespace

int main(int argc, char** argv)
{
    using namespace std::literals;
    namespace fs = std::filesystem;

    if (argc != 3) {
        printUsage();
    } else if (argv[1] != "-d"sv) {
        std::cerr << "Given option " << argv[1] << " not supported." << std::endl;
        return EXIT_FAILURE;
    } else {
        fs::path imageDirPath{argv[2]};
        if (!fs::exists(imageDirPath)) {
            std::cerr << "Given directory path " << argv[2] << " does not exist." << std::endl;
            return EXIT_FAILURE;
        }

        TestAufgabe::CPgmAverager pgmAverager;

        // process every .pgm file in given directory
        for (auto const& dir_entry : fs::directory_iterator{imageDirPath}) {

            if (fs::path{dir_entry}.extension() == ".pgm") {
                std::cout << "process " << dir_entry << std::endl;
                try {
                    pgmAverager.addSource(dir_entry.path());
                } catch (std::exception& ex) {
                    std::cerr << ex.what() << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
        auto outputFile = imageDirPath / "average.pgm";

        // generate the average.pgm
        pgmAverager.produce(outputFile);
    }

    return EXIT_SUCCESS;
}