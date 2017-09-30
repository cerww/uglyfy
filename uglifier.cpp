#include "uglifier.h"
#include "stringStuffs.h"

bool isLetter(char let){
	return let >= 'a' && let <= 'z' || let >= 'A' && let <= 'Z'||let=='_';
}

static constexpr char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
void uglifier::uglify() {
	m_removeExcessSpaces();
	m_addFiveSpaces();
	size_t current = 0;
	while(current<m_code.size() - 5){
		if(m_code[current] == '#'||m_code[current] == '/' && m_code[current] == '/'){//macros and comments
			current = m_code.find('\n', current) + 1;
		}else if(isLetter(m_code[current])){
			size_t next = find_first_if_not(m_code, current, isLetter);
			std::string_view word(&m_code[next], next - current);
			if(word=="const"||word=="constexpr"||word=="static"){
				current = next;
				continue;
			}else if(word=="class"||word=="struct"||word=="namespace"){
				size_t next_thingy = find_first_if_not(m_code, next, isLetter);
			}
		}else if(m_code[current] == '*'){//pointer or multiply
			++current;
		}else if (m_code[current] == '{') {
			addBracket();
			++current;
		}else if (m_code[current] == '}') {
			removeBracket();
		}else if(m_code[current] == '\n'||m_code[current] == ' '){
			++current;
		}
	}
}

void uglifier::addBracket(){
	m_endBits.push_back(m_userDefinedThings.size());
	m_userDefinedThings.push_back({ "","" });
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
	m_userDefinedThings.push_back(std::make_pair(std::string(word), getRandomBarCode()));
}
