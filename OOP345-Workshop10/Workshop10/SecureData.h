// Workshop 10 - Multi-Threading
// SecureData.h

#include <iostream>
#include <vector>

namespace w10 {

	struct Partition {
		int begin = 0;
		int end = 0;
		Partition(int b, int e) : begin(b), end(e) {}
		~Partition() { begin = 0; end = 0; }
	};

	class Cryptor {
	public:
		char operator()(char in, char key) const { return in ^ key; }
	};

	class SecureData {
		char* text;
		int nbytes;
		bool encoded;
		void code(char);
		int threadCount = 0;
		std::vector<Partition> partition;
	public:
		SecureData(const char*, char);
		SecureData(const SecureData&) = delete;
		SecureData& operator=(const SecureData&) = delete;
		~SecureData();
		void display(std::ostream&) const;
		void backup(const char*);
		void restore(const char*, char);
		void createPartitions();
	};
	std::ostream& operator<<(std::ostream&, const SecureData&);
}