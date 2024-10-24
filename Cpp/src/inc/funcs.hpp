#ifndef FUNCS_H
#define FUNCS_H

#include <string>

namespace project {
	
	void WriteLine(std::string Text);
	void Write(std::string Text);

	int ReadInteger(std::string Message);
	std::string ReadString(std::string Message);
}

#endif