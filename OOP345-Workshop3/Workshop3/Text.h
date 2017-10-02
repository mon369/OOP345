#pragma once
#include <iostream>


namespace w3 {
	const char r = '\r';
	class Text {
	private:
		std::string* line;
		size_t lines;

	public:
		Text();
		Text(const char*);
		Text(Text&);
		Text(Text&&);

		Text& operator=(Text&);
		Text&& operator=(Text&&);

		size_t size() const;
		~Text();

	};

}
