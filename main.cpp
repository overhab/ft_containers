#include "main.hpp"


#define TESTED_TYPE int

void printSize(ft::vector<TESTED_TYPE> const &  vec, bool print = true) {
	std::cout << "size = " << vec.size() << "\ncapacity = " << vec.capacity() << std::endl;
	if (print) {
		for (ft::vector<TESTED_TYPE>::const_iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

void printStd(std::vector<TESTED_TYPE> const &  vec, bool print = true) {
	std::cout << "size = " << vec.size() << "\ncapacity = " << vec.capacity() << std::endl;
	if (print) {
		for (std::vector<TESTED_TYPE>::const_iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

int main(void) {

/* 	std::cout << "======FT::STACK TESTS======" << std::endl;

	ft::stack<int> test;

	test.push(10);

	std::cout << test.top() << "\nempty() test = " << test.empty() << std::endl;
	test.pop();
	std::cout << "empty after pop() = " << test.empty() << std::endl;

	test.push(20);
	test.push(4442);
	std::cout << "4442 = " <<test.top() << std::endl;
	test.pop();
	std::cout << "20 = " <<test.top() << std::endl; */

	std::cout << "======STD::VECTOR TESTS======" << std::endl;

/* 	std::vector<int> vector(5, 12);
	vector.reserve(30);
	std::vector<int> vector2(8, 2020);

	std::cout << "SIZE = " << vector2.size() << " CAPACITY = " << vector2.capacity() << std::endl;
	vector2 = vector;
	std::cout << "SIZE = " << vector2.size() << " CAPACITY = " << vector2.capacity() << std::endl;

	for (std::vector<int>::const_iterator it = vector2.begin(); it != vector2.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << std::endl; */
/* 	int i2 = 0;

	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		*it = i2++;
	}
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << vector.size() << std::endl;

	vector.erase(vector.begin() + 3);
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << vector.size() << std::endl; */



	//vector.at(12);
/* 	int i = 0;

	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
		*it = i++;
	}

	for (std::vector<int>::reverse_iterator it = vector.rbegin(); it != vector.rend(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
	std::cout << "SIZE = " << vector.size() << " CAPACITY = " << vector.capacity() << std::endl; */

	////////////////////////////////////////////////////////////

	std::cout << "======FT::VECTOR TESTS======" << std::endl;


	ft::vector<int> myvec;

	myvec.insert(myvec.end(), 52);
	myvec.insert(myvec.begin(), 2, 42);

	printSize(myvec);



	return 0;
}
