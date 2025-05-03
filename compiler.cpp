#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <cassert>
#include <vector>

enum class TokenType {
	int_lit = 1,
	assignment,
	num,
	_return
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
};


void printToken(const Token& token) {
	std::cout << "Token = ";
	switch (token.type) {
		case TokenType::int_lit:
			std::cout << "int_lit";
			break;
		case TokenType::assignment:
			std::cout << "assignment";
			break;
		case TokenType::num:
			std::cout << "num , ";
			if (token.value.has_value()) {
				std::cout << token.value.value();
			} else {
				std::cout << "no value for token";
				exit(1);
			}
			break;
		case TokenType::_return:
			std::cout << "return";
			break;
		default:
			std::cerr << "No token found...have you added to TokenType?" << std::endl;
	}
	std::cout << std::endl;

}

Token convertStringToToken(const std::string& tokenString) {
	Token tempToken;
	if (tokenString == "cookie") {
		tempToken.type = TokenType::int_lit;
	} else if (tokenString == "is") {
		tempToken.type = TokenType::assignment;
	} else if (std::isdigit(tokenString.at(0))) {
		tempToken.type = TokenType::num; 
		tempToken.value = tokenString;
	} else if (tokenString == "gives") {
		tempToken.type = TokenType::_return;	
	} else {
		std::cerr << "Cannot match " << tokenString << " to any tokens" << std::endl;					
		exit(1);
	}
	
	return tempToken;
}

std::vector<Token> tokenize(const std::string& str) {
	int i = 0;
	std::vector<std::string> tokens = {};

	while (i < str.length() && str.at(i) != '\n') {	
		char currentChar = str.at(i);
		std::string newStr = "";
		while(!std::isspace(currentChar)) {
			std::cout << i << " | " << currentChar << std::endl;
			newStr.push_back(currentChar);
			i++;
			currentChar = str.at(i);
		}

		std::cout << "Token to add = " << newStr << std::endl;

		tokens.push_back(newStr);
						
		i++;
	}

	std::vector<Token> newTokens = {};
	for (std::string token : tokens) {
		newTokens.push_back(convertStringToToken(token));		
	}

	for (Token token : newTokens) {
		printToken(token);
	}

	return newTokens;
}

int openFile(std::string fileName) {
	std::cout << "File to be compiled: " << fileName << std::endl;
	std::fstream fs(fileName, std::ios::in);
	if (fs.is_open()) {
		std::cout << "File opend successfully." << std::endl;
		
		std::string contents;
		std::stringstream contents_stream;
		contents_stream << fs.rdbuf();
		contents = contents_stream.str();

		std::cout << contents << std::endl;

		std::vector<Token> tokens = tokenize(contents);

		fs.close();
	} else {
		std::cerr << "error opening file" << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Please enter file name to be compiled" << std::endl;
		return 1;
	} else {
		return openFile(argv[1]);
	}
}
