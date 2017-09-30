#pragma once

template<typename string,typename pred>
size_t find_first_if_not(const string& str,size_t off,pred fn){
	for (; off < str.size(); ++off) 		
		if (!fn(str[off]))
			return off;
	return -1;
}