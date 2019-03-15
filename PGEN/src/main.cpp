
#include "PGEN.hpp"

namespace Options = boost::program_options;

int main(int argc, char *argv[])
{
    /** Password parameters:
     *
     */
    const int N = 8;
    const int PasswordLength = 12;

    Options::options_description OptionsDescription("Program Options");
    OptionsDescription.add_options()
        ("help,h", "Display this help message and exit.")
        ("version", "Print program version information and exit.")
    ;

    Options::variables_map ArgsInput;
    Options::store(Options::parse_command_line(argc, argv, OptionsDescription), ArgsInput);
    Options::notify(ArgsInput);

    if (ArgsInput.count("help"))
    {
        std::cout << OptionsDescription << std::endl;

        return EXIT_SUCCESS;
    }

    if (ArgsInput.count("version"))
    {
        std::cout << "[Program Version Information...]" << std::endl;

        return EXIT_SUCCESS;
    }

    std::cout << "Generating " << N << " Password(s)..." << std::endl;

    char Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 61);

    std::cout << std::endl;

    for (auto i = 0; i < N; ++i) {
        for (auto n = 0; n < PasswordLength; ++n) {
            const auto r = dist(rd);
            std::cout << Alphabet[r];
        }
        
        std::cout << std::endl;
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
