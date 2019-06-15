#include <cstdint> 
#include "big_int.h"
#include "functions.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;



int main(int argc, char *argv[])
{
    po::options_description desc("Options");
    desc.add_options()
            ("help,h", "help, length of seq")
            ("length,l", po::value<uint64_t>()->default_value(2048), "length of generated seq");

    po::variables_map opts;
    try {

        po::store(po::parse_command_line(argc, argv, desc), opts);

        if (opts.count("help")) {
            desc.print(std::cout);
            return 1;
        }

    } catch (const std::exception& ce) {
        std::cout << "Exception occured while parsing commanf line arguments: "
                  << typeid (ce).name() << " " << ce.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown exception occured while parsing commanf line arguments" << std::endl;
    }

    auto len = opts["length"].as<uint64_t>();


    auto seq = generateBM(len);
    for (int i = 0; i < len / 32; ++i) {
        std::cout << std::hex << seq[i] << " ";
    }
}
