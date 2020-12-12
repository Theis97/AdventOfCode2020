#include <iostream>
#include <fstream>
#include <string>
#include <set>

// This is a bit of a mess.
// Maybe one day I'll polish it up.

std::string Extract(std::string str, int startIdx) {
    int endIdx = str.find(' ', startIdx);
    return str.substr(startIdx, endIdx - startIdx);
}

bool ValidateYear(std::string str, int startIdx, int low, int high) {
    int endIdx = str.find(' ', startIdx);
    std::string yearStr = str.substr(startIdx, endIdx - startIdx);
    int year = std::stoi(yearStr);
    if (yearStr.length() != 4 || year < low || year > high) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    bool useStrictValidation = false;

    if (argc > 1) {
        useStrictValidation = true;
    }

    std::ifstream inputFile;
    inputFile.open("day4.txt");
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened.\n";
        return 0;
    }

    std::string requiredFields[7] = { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };
    bool fieldsFound[7] = { false };
    bool fieldsValidated[7] = { false };
    std::set<std::string> eyeColors { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    
    std::string line;
    int validCount = 0;
    int stricterValidCount = 0;
    while (std::getline(inputFile, line)) {
        if (line.compare("") == 0) {
            bool isValid = true;
            bool isValidStrict = true;
            for (int i = 0; i < 7; i++) {
                if (!fieldsFound[i]) {
                    isValid = false;
                }
                if (!fieldsValidated[i]) {
                    isValidStrict = false;
                }
            }
            if (isValid) {
                validCount++;
            }
            if (isValidStrict) {
                stricterValidCount++;
            }
            for (int i = 0; i < 7; i++) {
                fieldsFound[i] = false;
                fieldsValidated[i] = false;
            }
        }
        else {
            for (int i = 0; i < 7; i++) {
                int fieldIdx = line.find(requiredFields[i]);
                if (fieldIdx != std::string::npos) {
                    fieldsFound[i] = true;
                    if (useStrictValidation) {
                        // all ranges are inclusive
                        switch (i) {
                        case 0: // byr
                        {
                            // 4 digits, between 1920-2002
                            fieldsValidated[0] = ValidateYear(line, fieldIdx + 4, 1920, 2002);
                            break;
                        }
                        case 1: // iyr
                        {
                            // 4 digits, between 2010-2020
                            fieldsValidated[1] = ValidateYear(line, fieldIdx + 4, 2010, 2020);
                            break;
                        }
                        case 2: // eyr
                        {
                            // 4 digits, between 2020-2030
                            fieldsValidated[2] = ValidateYear(line, fieldIdx + 4, 2020, 2030);
                            break;
                        }
                        case 3: // hgt
                        {
                            // if cm: between 120-193
                            // if in: between 59-76
                            std::string hgt = Extract(line, fieldIdx + 4);
                            int heightVal = std::stoi(hgt);
                            if (hgt.find("cm") != std::string::npos) {
                                fieldsValidated[3] = heightVal >= 120 && heightVal <= 193;
                            }
                            else if (hgt.find("in") != std::string::npos) {
                                fieldsValidated[3] = heightVal >= 59 && heightVal <= 76;
                            }
                            break;
                        }
                        case 4: // hcl
                        {
                            // hex code ('#' followed by 6 characters 0-9 or a-f)
                            if (line[fieldIdx + 4] != '#') {
                                break;
                            }
                            std::string hcl = Extract(line, fieldIdx + 5);
                            bool validHex = true;
                            if (hcl.length() != 6) {
                                validHex = false;
                            }
                            for (auto c : hcl) {
                                if (c < 48 || c > 102 || (c > 57 && c < 97)) {
                                    validHex = false;
                                }
                            }
                            if (validHex) {
                                fieldsValidated[4] = true;
                            }
                            break;
                        }
                        case 5: // ecl
                        {
                            // exactly one of {amb, blu, brn, gry, grn, hzl, oth}
                            std::string ecl = Extract(line, fieldIdx + 4);
                            if (eyeColors.find(ecl) != eyeColors.end()) {
                                fieldsValidated[5] = true;
                            }
                            break;
                        }
                        case 6: // pid
                        {
                            // 9 digits including leading zeros
                            std::string pid = Extract(line, fieldIdx + 4);
                            fieldsValidated[6] = pid.length() == 9;
                            break;
                        }
                        }
                    }
                }
                
            }
        }
    }
    bool isValid = true;
    bool isValidStrict = true;
    for (int i = 0; i < 7; i++) {
        if (!fieldsFound[i]) {
            isValid = false;
        }
        if (!fieldsValidated[i]) {
            isValidStrict = false;
        }
    }
    if (isValid) {
        validCount++;
    }
    if (isValidStrict) {
        stricterValidCount++;
    }

    int finalCount;
    if (useStrictValidation) {
        finalCount = stricterValidCount;
    }
    else {
        finalCount = validCount;
    }
    std::cout << "Stricter validation: " << useStrictValidation << "\n";
    std::cout << "# \"Valid\" passports: " << finalCount << "\n";
}