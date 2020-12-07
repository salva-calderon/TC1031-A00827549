// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#ifndef HashT_h
#define HashT_h

class HashT {
	std::vector<std::string> key;
	std::vector<int> value;
	int size;

	// O(n)
	int hashing(const std::string &str) {
		int ans = 0;
		for (auto &c : str) {
			ans += c;
		}
		return ans % size;
	}
public:
	// O(1)
	HashT() {
		size = 0;
		key.assign(0, std::string());
		value.assign(0, 0);
	}

	// O(1)
	HashT(const int &num) {
		size = num;
		key.assign(num, std::string());
		value.assign(num, 0);
	}

	// O(n)
	void print() {
		for (int i = 0; i < size; ++i) {
			std::cout << "Posicion \"" << i << '\"'
				<< "\tLlave: \"" << key[i] << '\"' << std::endl;
		}
	}

	// O(n)
	void insert(const std::string &str) {
		int pos = hashing(str), i = 0;
		bool finished = false;
		while (!finished) {
			if (i > size) {
				finished = true;
				std::cout << "HashTable Llena" << std::endl;
			}
			if (value[pos] == 0 || value[pos] == 2) {
				key[pos] = str;
				value[pos] = 1;
				finished = true;
			}
			++pos;
			pos %= size;
			++i;
		}
	}

	// O(n)
	void erase(const std::string &str) {
		int pos = hashing(str), i = 0;
		bool finished = false;
		while (!finished) {
			if (i > size) {
				finished = true;
			}
			if (key[pos] == str) {
				key[pos] = std::string();
				value[pos] = 2;
				finished = true;
			} else if (value[pos] == 0) {
				finished = true;
			}
			++pos;
			pos %= size;
			++i;
		}
	}

	// O(n)
	int find(const std::string &str) {
		int pos = hashing(str), i = 0;
		bool finished = false;
		while (!finished) {
			if (i > size) {
				finished = true;
				return -1;
			}
			if (key[pos] == str) {
				value[pos] = 1;
				finished = true;
				return pos;
			} else if (value[pos] == 0) {
				finished = true;
				return -1;
			}
			++pos;
			pos %= size;
			++i;
		}
		return -1;
	}

	// O(1)
	std::string& operator[](const int &idx) {
		return key[idx];
	}
};

#endif /* HashT_h */