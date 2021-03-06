#include "uglifier.h"
#include "stringStuffs.h"
#include <algorithm>

bool isLetter(char let){
	return let >= 'a' && let <= 'z' || let >= 'A' && let <= 'Z' || let == '_' || let==':';
}

static constexpr char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
void uglifier::uglify() {
	m_removeExcessSpaces();
	m_addFiveSpaces();
	size_t current = 0;
	while(current<m_code.size() - 5){
		if(m_code[current] == '#'||m_code[current] == '/' && m_code[current+1] == '/'){//macros and comments
			current = m_code.find('\n', current) + 1;
		}else if(isLetter(m_code[current])){
			size_t next = find_first_if_not(m_code, current, isLetter);
			std::string_view word(&m_code[current], next - current);
			if(word=="const"||word=="constexpr"||word=="static"||word=="inline"||word=="virtual"||word=="override"){
				current = next;
				continue;
			}else if(word=="class"||word=="struct"||word=="namespace"){
				size_t next_thingy = find_first_if_not(m_code, next+1, isLetter);
				std::string_view nextWord(&m_code[next + 1], next_thingy - next - 1);
				m_code.replace(next + 1, next_thingy - next - 1, getBarCodeFor(nextWord));
				current = m_code.find_first_not_of("1Il", next + 1);
			}else if(isDefined(word)){
				m_code.replace(current, next - current, getBarCodeFor(word));
				current = m_code.find_first_not_of("1Il", next + 1);
			}else if(word=="return"){
				current = next;
			}else{
				size_t next_thingy = find_first_if_not(m_code, next + 1, isLetter);
				std::string_view nextWord(&m_code[next + 1], next_thingy - next - 1);
				m_code.replace(next + 1, next_thingy - next - 1, getBarCodeFor(nextWord));
				current = m_code.find_first_not_of("1Il", next + 1);
				//current = next;
			}
		}else if(m_code[current] == '*'){//pointer or multiply
			++current;
		}else if (m_code[current] == '{') {
			addBracket();
			++current;
		}else if (m_code[current] == '}') {
			removeBracket();
			++current;
		}else if(m_code[current] == '\n'||m_code[current] == ' '){
			++current;
		}else if(m_code[current]=='/'&&m_code[current+1]=='*'){
			current = m_code.find("*/", current) + 2;
		}else{
			++current;
		}
	}std::cout << m_code << std::endl;
}

void uglifier::addBracket(){
	m_endBits.push_back(m_userDefinedThings.size());
	//m_userDefinedThings.push_back({ "","" });
}

void uglifier::removeBracket(){
	m_userDefinedThings.erase(m_userDefinedThings.begin() + m_endBits.back(), m_userDefinedThings.end());
}

void uglifier::m_removeExcessSpaces() {
	for (auto& i : m_code) {
		if (i == '\t')
			i = ' ';
	}
	for (int i = 1; i < m_code.size()-1; ++i){
		if (m_code[i] == ' ' || m_code[i] == '\n') {
			if (m_code[i + 1] == ' ' || m_code[i + 1] == '\n') {
				m_code.erase(i, 1);
				--i;
			}
		}
	}
}

void uglifier::m_addFiveSpaces(){
	m_code.insert(m_code.size(),"     "s);
}

void uglifier::addUserDefThing(std::string_view word){
	m_userDefinedThings.emplace_back(std::string(word), getRandomBarCode());
}

bool uglifier::isDefined(std::string_view word){
	return std::find_if(m_userDefinedThings.begin(), m_userDefinedThings.end(), [&](const std::pair<std::string, std::string>& pairy) {
		return word == pairy.first; 
	}) == m_userDefinedThings.end() ? 0 : 1;
}

std::string uglifier::getBarCodeFor(std::string_view word){
	if(auto it = std::find_if(m_userDefinedThings.begin(), m_userDefinedThings.end(), [&](const std::pair<std::string, std::string>& pairy) {
		return word == pairy.first;
	});it == m_userDefinedThings.end()) {
		return m_userDefinedThings.emplace_back(std::string(word), getRandomBarCode()).second;
	}else {
		return it->second;
	}
}
