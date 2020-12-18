#include "StringUtils.h"
#include <iostream>

// Returns the substring spanning [startIndex, endIndex)
std::string SubstrByEndpoint(std::string str, int startIndex, int endIndex) {
	return str.substr(startIndex, endIndex - startIndex);
}

// Trims all characters c from the beginning and end of str
std::string TrimStr(std::string str, char c) {
	int front = 0;
	int back = str.length() - 1;
	while (front < back && (str[front] == c || str[back] == c)) {
		if (str[front] == c) {
			front++;
		}
		else {
			back--;
		}
	}

	if (front >= back) {
		return "";
	}
	else {
		return SubstrByEndpoint(str, front, back + 1);
	}
}

std::vector<std::string> TokenizeString(std::string str, char delim) {
	str = TrimStr(str, delim);
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