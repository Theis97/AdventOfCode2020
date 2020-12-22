#pragma once
#include <vector>
#include <string>

std::string TrimStr(std::string str, char c);
std::string SubstrByEndpoint(std::string str, int startIndex, int endIndex);
std::vector<std::string> TokenizeString(std::string str, char delim);