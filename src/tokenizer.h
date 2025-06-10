#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>
#include<optional>
#include <iostream>

enum class TokenType {
	int_lit = 1,
	assignment,
	num,
	_return,
	op_add,
	op_sub
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
};

std::vector<Token> tokenize(const std::string& str);

void printToken(const Token& token);

#endif
