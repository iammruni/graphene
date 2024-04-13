#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

// Assumption is that everything is in ASCII
std::vector<Token> tokenise(const std::string& str) {

    std::vector<Token> tokens;

    std::string buf;
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while(std::isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            if (buf == "return"){
                tokens.push_back({.type = TokenType::_return});
                buf.clear();
                continue;
            } else {
                std::cerr << "Error: No return statement found" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isdigit(c)) {
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i))) {
                buf.push_back((str.at(i)));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
        }
        else if (c == ';') {
            tokens.push_back({.type = TokenType::semi});
        }
        else if (std::isspace(c)) {
            continue;
        } else {
            std::cerr << "Error: Tokenisation Failed" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}




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
        std::cerr << "Error: No input file specified" << std::endl;
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

    std::vector<Token> thing = tokenise(contents);


    return EXIT_SUCCESS;
}
