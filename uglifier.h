#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "fileStuff.h"
#include "flat_hash_map.hpp"
#include <unordered_map>
#include <random>
#include <string_view>

using namespace std::string_literals;
//takes a piece of c++ code and makes it ugly
inline std::string getRandomBarCode() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(10,18);
	std::uniform_int_distribution<int> dis(0, 3);
	int length = dist(mt);
	std::string returnVal = "";
	returnVal.resize(length);
	for (auto& i : returnVal) {
		auto temp = dis(mt);
		i = temp ? temp == 2 ? '1' : 'I' : 'l';
	}if (returnVal[0] == '1')
		returnVal[0] = 'I';
	return returnVal;
}
static const std::string_view keywords[] = { "int","char","class","const","static","constexpr" };
class uglifier {
public:
	uglifier(std::string a):m_code(a){};
	uglifier() = default;
	void uglify();
private:
	std::vector<std::pair<std::string, std::string>> m_userDefinedThings;//string of "","" is sentinal
	std::vector<size_t> m_endBits;
	void addBracket();
	void removeBracket();
	//void m_getVars();
	void m_removeExcessSpaces();
	std::string m_code = "#include <iostream>\nint main(){\nint uio = 0;\nreturn 0;}";
	std::string m_badCode = "";
	void m_addFiveSpaces();
	void addUserDefThing(std::string_view);
	bool isDefined(std::string_view);
	std::string getBarCodeFor(std::string_view);
};