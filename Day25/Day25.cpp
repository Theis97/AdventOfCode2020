#include <iostream>
#include <fstream>
#include <string>

const long long subjectNumber = 7;
const long long divisor = 20201227;

int main() {
	std::ifstream inputFile;
	inputFile.open("day25.txt");
	if (!inputFile.is_open()) {
		std::cout << "File could not be opened.\n";
		return 0;
	}

	std::string cardKeyStr;
	std::string doorKeyStr;
	std::getline(inputFile, cardKeyStr);
	std::getline(inputFile, doorKeyStr);
	long long cardKey = std::stoll(cardKeyStr);
	long long doorKey = std::stoll(doorKeyStr);

	long long cardLoopSize = 0;
	long long value = 1;
	while (value != cardKey) {
		cardLoopSize++;
		value *= subjectNumber;
		value = value % divisor;
	}
	std::cout << "Card loop size: " << cardLoopSize << "\n";

	long long doorLoopSize = 0;
	value = 1;
	while (value != doorKey) {
		doorLoopSize++;
		value *= subjectNumber;
		value = value % divisor;
	}
	std::cout << "Door loop size: " << doorLoopSize << "\n";

	long long encryptionKey = 1;
	for (long long i = 0; i < cardLoopSize; i++) {
		encryptionKey *= doorKey;
		encryptionKey = encryptionKey % divisor;
	}

	std::cout << "Encryption key (Card loop on door key): " << encryptionKey << "\n";

	encryptionKey = 1;
	for (long long i = 0; i < doorLoopSize; i++) {
		encryptionKey *= cardKey;
		encryptionKey = encryptionKey % divisor;
	}

	std::cout << "Encryption key (Door loop on card key): " << encryptionKey << "\n";
}