#pragma once
#include <string>
#include <fstream>
namespace cw {
	inline std::string getFileConts(const std::string& filePath) {
		std::string fileContents;
		std::ifstream file(filePath, std::ios::in);
		file.seekg(0, std::ios::end);
		int filesize = file.tellg();
		file.seekg(0, std::ios::beg);
		filesize -= file.tellg();
		fileContents.resize(filesize);
		file.read(&fileContents[0], filesize);
		file.close();
		return fileContents;
	}
}