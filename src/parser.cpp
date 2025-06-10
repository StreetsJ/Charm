#include <iostream>
#include <vector>
#include <cctype>
#include <queue>

std::string toPostfix(std::string input) {
	std::string res = "";
	std::queue<char> ops;
	for(int i = 0; i < input.size(); i++) {
		char curr = input.at(i);
		if (isdigit(curr)) {
			res.push_back(curr);
		} else {
			if (!ops.empty()) {
				res.push_back(ops.front());
				ops.pop();
			}
			ops.push(curr);
		}
	}

	while (!ops.empty()) {
		res.push_back(ops.front());
		ops.pop();	
	}
	return res;
}	

int main(int argc, char** argv) {
	if (argc > 1) {
		std::string input = argv[1];
		std::cout << toPostfix(input) << std::endl;
	} else {
		std::cout << "Enter an input to test" << std::endl;
	}
	return 0;
}
