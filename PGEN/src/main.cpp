
#include "PGEN.hpp"

namespace IO
{
    template <typename CharT, typename T = std::char_traits<CharT>>
    std::basic_ostream<CharT, T>&
    endl(std::basic_ostream<CharT, T>& outputStream)
    {
        return outputStream << outputStream.widen('\n');
    }
} // namespace IO

namespace Options = boost::program_options;

int main(int argc, char *argv[])
{
    /** Program Defaults
     *
     */
    const auto  DefaultPasswordsToCreate = 1;
    const auto  DefaultPasswordLength    = 16;

    const std::string DefaultSymbolList  = "!@#$`~|\\%^&*()[]-_=+{}';:,<.>/?";
    const std::string SimplerSymbolList  = "!@#$&?";

    /** Program Options
     *
     */
    bool verbose = false;

    /** Password parameters:
     *
     */
    int N              = DefaultPasswordsToCreate;
    int PasswordLength = DefaultPasswordLength;
    
    std::string AlphabetUpper   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string AlphabetLower   = "abcdefghijklmnopqrstuvwxyz";
    std::string AlphabetNumeric = "0123456789";
    std::string AlphabetSymbols = DefaultSymbolList;

    Options::options_description OptionsDescription("Program Options");
    OptionsDescription.add_options()
        ("help,h", "Display this help message and exit.")
        ("version", "Print program version information.")
        ("passwords,n", Options::value<int>(&N)->default_value(DefaultPasswordsToCreate), "Number of passwords to generate.")
        ("length,l", Options::value<int>(&PasswordLength)->default_value(DefaultPasswordLength), "Length of passwords to generate.")
        ("symbols", Options::value<std::string>(&AlphabetSymbols)->default_value(DefaultSymbolList), "Pass in custom legal symbols list.")
        ("simple-symbols", "Use simpler symbol list.")
        ("verbose,v", "Log additional info to stdout during execution.")
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

    if (ArgsInput.count("verbose"))
    {
        verbose = true;
    }

    if (ArgsInput.count("symbols"))
    {
        // TODO: Validate symbol list input.

        if (verbose) {
            std::cout << "Legal Symbols: " << AlphabetSymbols << std::endl;
        }
    }

    if (ArgsInput.count("simple-symbols"))
    {
        AlphabetSymbols = SimplerSymbolList;

        if (verbose) {
            std::cout << "Legal Symbols: " << AlphabetSymbols << std::endl;
        }
    }

    // TODO: Refactor to idiomatic C++.
    const auto AlphabetSize = 62 + strlen(AlphabetSymbols.c_str());
    char* Alphabet = static_cast<char *>(malloc(sizeof(char) * AlphabetSize));
    sprintf(Alphabet, "%s%s%s%s", AlphabetUpper.c_str(), AlphabetLower.c_str(), AlphabetNumeric.c_str(), AlphabetSymbols.c_str());

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, AlphabetSize);

    for (auto i = 0; i < N; ++i) {
        for (auto n = 0; n < PasswordLength; ++n) {
            const auto r = dist(rd);
            std::cout << Alphabet[r];
        }
        
        std::cout << IO::endl;
    }

    return EXIT_SUCCESS;
}
