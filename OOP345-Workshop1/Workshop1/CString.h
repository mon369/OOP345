#pragma once
#include <iostream>

namespace w1 {
	const int MAX_CHARS = 3;

	class CString {

	private:
		char arg[MAX_CHARS + 1];
	public:
		CString(const char*);
		std::ostream& display(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, CString&);
}
