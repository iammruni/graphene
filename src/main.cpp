#include <iostream>
#include <fstream>
#include <sstream>

// Function: main
// Description: Entry point of the compiler.
// Parameters:
//   argc (int): Number of command-line arguments.
//   argv (char*[]): Array of command-line arguments.
// Returns:
//   int: Exit status.
int main(int argc, char* argv []) {
    // Check if exactly one command-line argument (input file name) is provided.
    if (argc != 2) {
        std::cerr << "Error: No input file specified." << std::endl;
        std::cerr << "Usage: graphene <input_file>.grf" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::cout << contents << std::endl;

    return EXIT_SUCCESS;
}
