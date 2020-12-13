#include "StringUtils.h"
#include <iostream>

std::string SubstrByEndpoint(std::string str, int startIndex, int endIndex) {
	return str.substr(startIndex, endIndex - startIndex);
}

std::vector<std::string> TokenizeString(std::string str, char delim) {
	std::vector<std::string> result;
	int splitPoint = 0;
	int tokenStart = 0;

	while (true) {
		splitPoint = str.find(delim, splitPoint);
		if (splitPoint == std::string::npos) {
			result.push_back(str.substr(str.rfind(delim) + 1));
			break;
		}
		result.push_back(SubstrByEndpoint(str, tokenStart, splitPoint));
		splitPoint++;
		tokenStart = splitPoint;
	}
	return result;
}