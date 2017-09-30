#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "fileStuff.h"
#include "uglifier.h"

int main() {
	//auto fStuff = cw::getFileConts("");
	std::string fStuff = "#include <iostream>\nint main(){\nint uio = 0;\nreturn 0;}";
	/*first thing it'll do is remove any multiple spaces
	  then remove comments
	*/
	std::string newString = "";
	uglifier(cw::getFileConts("uglifier.cpp")).uglify();
	//newString.replace(1,);
	int qwaedas = 0;
	std::cin >> qwaedas;
	return 0;
}
