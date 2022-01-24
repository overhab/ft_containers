#include "main.hpp"

#define NAMESPACE	ft
#define FIRST_TYPE	int
#define SECOND_TYPE std::string
#define T4 			std::pair<const FIRST_TYPE, SECOND_TYPE>
#define PR_TYPE		ft::pair<std::vector<FIRST_TYPE>, ft::vector<FIRST_TYPE> >

class Testing {
	public:
		typedef PR_TYPE	pair_type;
	private:
		SECOND_TYPE		string;
		pair_type		cheeky_pair;
	public:
		Testing() : string("Default"), cheeky_pair() {}
		Testing(const SECOND_TYPE & __str, const pair_type & __pr) : string(__str), cheeky_pair(__pr) {}
		~Testing() {}
		const SECOND_TYPE & getString() { return this->string; }
		void				setString(const SECOND_TYPE & __str) { this->string = __str; }
};

bool	file_diff( void ) {
	bool flag = true;
	std::ifstream ftfile("ft_output.txt");
	std::ifstream stdfile("std_output.txt");

	std::string file1, file2;
	while (ftfile.good() && stdfile.good()) {
		std::getline(ftfile, file1);
		std::getline(stdfile, file2);
		if (file1 != file2) {
			flag = false;
			break ;
		}
	}
	ftfile.close();
	stdfile.close();
	return flag;
}

double	calculate_time(struct timeval __end, struct timeval __begin) {
	long seconds = __end.tv_sec - __begin.tv_sec;
	long microseconds  = __end.tv_usec - __begin.tv_usec;
	double time_taken = ((seconds * 1e6) + microseconds) * 1e-6;

	return time_taken;
}

template <class T>
void printVector(NAMESPACE::vector<T> const &  containter, bool print = true, const std::string &prefix = "NULL") {
	std::cout << prefix << ": size = [" << containter.size() << "]\tcapacity = [" << containter.capacity() << "]" << std::endl;
	if (print) {
		for (typename NAMESPACE::vector<T>::const_iterator it = containter.begin(); it != containter.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

template <class T>
void s_printVector(std::vector<T> const &  containter, bool print = true, const std::string &prefix = "NULL") {
	std::cout << prefix << ": size = [" << containter.size() << "]\tcapacity = [" << containter.capacity() << "]" << std::endl;
	if (print) {
		for (typename std::vector<T>::const_iterator it = containter.begin(); it != containter.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
}

template <class T, class W>
void printMap(NAMESPACE::map<T, W> const &  containter, bool print = true, const std::string &prefix = "NULL") {
	std::cout << prefix << ": size = [" << containter.size() << "]" << std::endl;
	if (print) {
		typename NAMESPACE::map<T, W>::const_iterator it = containter.begin(), ite =	 containter.end();
		for (; it != ite; ++it)
			std::cout << it->first << " " << it->second << "\n";
	}	
}

template <class T, class W>
void s_printMap(std::map<T, W> const &  containter, bool print = true, const std::string &prefix = "NULL") {
	std::cout << prefix << ": size = [" << containter.size() << "]" << std::endl;
	if (print) {
		typename std::map<T, W>::const_iterator it = containter.begin(), ite =	 containter.end();
		for (; it != ite; ++it)
			std::cout << it->first << " " << it->second << "\n";
	}	
}

void	stack_Tests( std::size_t _cap = 2) {
	const std::size_t __size = 1000 * _cap;
	NAMESPACE::vector<FIRST_TYPE> vec_test1;
	vec_test1.reserve(100);
	std::cout << GREEN << "======FT::STACK TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::ofstream ftfile;
	ftfile.open("ft_output.txt");
	struct timeval	ft_begin, ft_end;
	gettimeofday(&ft_begin, 0);
	NAMESPACE::stack<FIRST_TYPE> ftstack(vec_test1);
	for (std::size_t i = 0; i < __size; i++)
		ftstack.push((i + 1) * 32);
	for (std::size_t i = 0; i < __size / 2; i++) {
		ftfile << ftstack.top() << " ";
		ftstack.pop();
	}
	ftfile.close();
	std::cout << "FT STACK SIZE = " << ftstack.size() << std::endl;
	if (!ftstack.empty()) {
		while (ftstack.size() != 0)
			ftstack.pop();
	}
	std::cout << "FT STACK SIZE = " << ftstack.size() << std::endl;
	gettimeofday(&ft_end, 0);
	std::cout << "FT STACK TIME: " << YELLOW << std::fixed << calculate_time(ft_end, ft_begin) << RESET << std::setprecision(6) << std::endl;

	std::cout << GREEN << "======STD::STACK TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::vector<FIRST_TYPE> vec_test2;
	vec_test2.reserve(100);
	std::ofstream stdfile;
	stdfile.open("std_output.txt");
	struct timeval	std_begin, std_end;
	gettimeofday(&std_begin, 0);
	std::stack<FIRST_TYPE, std::vector<FIRST_TYPE> > stdstack(vec_test2);
	for (std::size_t i = 0; i < __size; i++)
		stdstack.push((i + 1) * 32);
	for (std::size_t i = 0; i < __size / 2; i++) {
		stdfile << stdstack.top() << " ";
		stdstack.pop();
	}
	stdfile.close();
	std::cout << "STD STACK SIZE = " << stdstack.size() << std::endl;
	if (!stdstack.empty()) {
		while (stdstack.size() != 0)
			stdstack.pop();
	}
	std::cout << "STD STACK SIZE = " << stdstack.size() << std::endl;
	gettimeofday(&std_end, 0);
	std::cout << "STD STACK TIME: " << std::fixed << YELLOW << calculate_time(std_end, std_begin) << RESET << std::setprecision(6) <<  std::endl;
	if (file_diff()) {
		std::cout << "OK";
	} else {
		std::cout << "FAIL";
	}
	std::cout << std::endl;	
	system("rm std_output.txt ft_output.txt");
}

void	vector_Tests( std::size_t _cap = 2, bool _nspace = false ) {
	std::string __prefix("ft");
	if (_nspace) {
		__prefix = "std";
	}
	const std::size_t __size = 1000 * _cap;
	std::cout << GREEN << "======" << __prefix << "::VECTOR TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::ofstream ftfile;
	std::string filename = __prefix + "_output.txt";
	ftfile.open(filename.c_str());
	struct timeval	ft_begin, ft_end;
	gettimeofday(&ft_begin, 0);

	NAMESPACE::vector<FIRST_TYPE> ft_cont;
	ft_cont.reserve(__size / 2);
	printVector(ft_cont, false, __prefix + "_CONT");
	for (std::size_t i = 0; i < __size / 2; i++)
		ft_cont[i] = 995;
	ft_cont.insert(ft_cont.begin(), __size, 42);
	for (std::size_t i = 0; i < __size / 2; i++) {
		ftfile << ft_cont[i] << " ";
		ft_cont.pop_back();
	}
	printVector(ft_cont, false, __prefix + "_CONT");
	NAMESPACE::vector<FIRST_TYPE>		copy_test(ft_cont.begin(), ft_cont.end());
	printVector(copy_test, false, "COPY");
	for (unsigned long i = 0; i < copy_test.size(); i++) {
		ftfile << copy_test.at(i) << " ";
	}
	ftfile.close();
	ft_cont.assign(10, 101);
	printVector(ft_cont, true, __prefix + "_CONT AFTER ASSIGN");
	printVector(copy_test, false, "COPY PRE ASSIGNMENT");
	copy_test = ft_cont;
	printVector(copy_test, true, "COPY AFTER ASSIGNMENT");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	try {
		ft_cont.at(ft_cont.size()) = 123;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	ft_cont.clear();
	copy_test.clear();
	printVector(ft_cont, false, __prefix + "_CONT CLEAN");
	printVector(copy_test, false, "COPY CLEAN");

	gettimeofday(&ft_end, 0);
	std::cout << __prefix << " VECTOR TIME: " << YELLOW << std::fixed << calculate_time(ft_end, ft_begin) << RESET <<  std::endl;

	if (_nspace) {
		if (file_diff()) {
			std::cout << GREEN << "OK";
		} else {
			std::cout << RED << "FAIL";
		}
		std::cout << RESET << std::endl;	
		system("rm std_output.txt ft_output.txt");
	}
}

void	s_vector_Tests( std::size_t _cap = 2, bool _nspace = false ) {
	std::string __prefix("ft");
	if (_nspace) {
		__prefix = "std";
	}
	const std::size_t __size = 1000 * _cap;
	std::cout << GREEN << "======" << __prefix << "::VECTOR TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::ofstream ftfile;
	std::string filename = __prefix + "_output.txt";
	ftfile.open(filename.c_str());
	struct timeval	ft_begin, ft_end;
	gettimeofday(&ft_begin, 0);

	std::vector<FIRST_TYPE> ft_cont;
	ft_cont.reserve(__size / 2);
	s_printVector(ft_cont, false, __prefix + "_CONT");
	for (std::size_t i = 0; i < __size / 2; i++)
		ft_cont[i] = 995;
	ft_cont.insert(ft_cont.begin(), __size, 42);
	for (std::size_t i = 0; i < __size / 2; i++) {
		ftfile << ft_cont[i] << " ";
		ft_cont.pop_back();
	}
	s_printVector(ft_cont, false, __prefix + "_CONT");
	std::vector<FIRST_TYPE>		copy_test(ft_cont.begin(), ft_cont.end());
	s_printVector(copy_test, false, "COPY");
	for (unsigned long i = 0; i < copy_test.size(); i++) {
		ftfile << copy_test.at(i) << " ";
	}
	ftfile.close();
	ft_cont.assign(10, 101);
	s_printVector(ft_cont, true, __prefix + "_CONT AFTER ASSIGN");
	s_printVector(copy_test, false, "COPY PRE ASSIGNMENT");
	copy_test = ft_cont;
	s_printVector(copy_test, true, "COPY AFTER ASSIGNMENT");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	try {
		ft_cont.at(ft_cont.size()) = 123;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	ft_cont.clear();
	copy_test.clear();
	s_printVector(ft_cont, false, __prefix + "_CONT CLEAN");
	s_printVector(copy_test, false, "COPY CLEAN");

	gettimeofday(&ft_end, 0);
	std::cout << __prefix << " VECTOR TIME: " << YELLOW << std::fixed << calculate_time(ft_end, ft_begin) << RESET <<  std::endl;

	if (_nspace) {
		if (file_diff()) {
			std::cout << GREEN << "OK";
		} else {
			std::cout << RED << "FAIL";
		}
		std::cout << RESET << std::endl;	
		system("rm std_output.txt ft_output.txt");
	}
}

void	map_Tests( std::size_t _cap = 2, bool _nspace = false ) {
	typedef NAMESPACE::map<FIRST_TYPE, SECOND_TYPE>::value_type T3;
	typedef NAMESPACE::map<FIRST_TYPE, SECOND_TYPE>::const_iterator it_type;

	std::string __prefix("ft");
	if (_nspace) {
		__prefix = "std";
	}
	const std::size_t __size = 100 * _cap;
	std::cout << GREEN << "======" << __prefix << "::MAP TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::ofstream ftfile;
	std::string filename = __prefix + "_output.txt";
	ftfile.open(filename.c_str());
	struct timeval	ft_begin, ft_end;
	gettimeofday(&ft_begin, 0);

	NAMESPACE::map<FIRST_TYPE, SECOND_TYPE> ft_cont;
	printMap(ft_cont, false, __prefix + "_CONT");
	std::list<T3> lst;

	for (std::size_t i = 0; i < __size; i++) {
		lst.push_back(T3(i, "qwerty"));
	}
	ft_cont.insert(lst.begin(), lst.end());

	for(std::size_t i = 0; i < __size / 2; i++) {
		it_type it = ft_cont.find(i);
		ftfile << it->first << " " << it->second << " ";
		ft_cont.erase(it->first);
	}
	printMap(ft_cont, false, __prefix + "_CONT AFTER ERASE (should be half)");
	NAMESPACE::map<FIRST_TYPE, SECOND_TYPE> copy_test(ft_cont);
	printMap(copy_test, false, __prefix + "COPY");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	ft_cont.clear();
	ft_cont.insert(T3(12, "kek"));
	ft_cont.insert(T3(19, "lol"));
	ft_cont.insert(T3(-7, "negative"));
	ft_cont.insert(T3(12, "already exists"));
	ft_cont.insert(T3(884, "try me"));
	printMap(ft_cont, true, __prefix + "_CONT PRE ASSIGNMENT");
	copy_test = ft_cont;
	printMap(copy_test, true, __prefix + "COPY AFTER ASSIGNMENT");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	ft_cont.clear();
	copy_test.clear();
	printMap(ft_cont, false, __prefix + "_CONT CLEAN");
	printMap(copy_test, false, "COPY CLEAN");

	ftfile.close();
	gettimeofday(&ft_end, 0);
	std::cout << __prefix << " MAP TIME: " << YELLOW << std::fixed << calculate_time(ft_end, ft_begin) << RESET <<  std::endl;

	if (_nspace) {
		if (file_diff()) {
			std::cout << GREEN << "OK";
		} else {
			std::cout << RED << "FAIL";
		}
		std::cout << RESET << std::endl;		
		system("rm std_output.txt ft_output.txt");
	}
}

void	s_map_Tests( std::size_t _cap = 2, bool _nspace = false ) {
	typedef std::map<FIRST_TYPE, SECOND_TYPE>::value_type T3;
	typedef std::map<FIRST_TYPE, SECOND_TYPE>::const_iterator it_type;

	std::string __prefix("ft");
	if (_nspace) {
		__prefix = "std";
	}
	const std::size_t __size = 100 * _cap;
	std::cout << GREEN << "======" << __prefix << "::MAP TESTS OF SIZE = [" << CYAN << __size << GREEN <<"]======"<< RESET << std::endl;
	std::ofstream ftfile;
	std::string filename = __prefix + "_output.txt";
	ftfile.open(filename.c_str());
	struct timeval	ft_begin, ft_end;
	gettimeofday(&ft_begin, 0);

	std::map<FIRST_TYPE, SECOND_TYPE> ft_cont;
	s_printMap(ft_cont, false, __prefix + "_CONT");
	std::list<T3> lst;

	for (std::size_t i = 0; i < __size; i++) {
		lst.push_back(T3(i, "qwerty"));
	}
	ft_cont.insert(lst.begin(), lst.end());

	for(std::size_t i = 0; i < __size / 2; i++) {
		it_type it = ft_cont.find(i);
		ftfile << it->first << " " << it->second << " ";
		ft_cont.erase(it->first);
	}
	s_printMap(ft_cont, false, __prefix + "_CONT AFTER ERASE (should be half)");
	std::map<FIRST_TYPE, SECOND_TYPE> copy_test(ft_cont);
	s_printMap(copy_test, false, __prefix + "COPY");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	ft_cont.clear();
	ft_cont.insert(T3(12, "kek"));
	ft_cont.insert(T3(19, "lol"));
	ft_cont.insert(T3(-7, "negative"));
	ft_cont.insert(T3(12, "already exists"));
	ft_cont.insert(T3(884, "try me"));
	s_printMap(ft_cont, true, __prefix + "_CONT PRE ASSIGNMENT");
	copy_test = ft_cont;
	s_printMap(copy_test, true, __prefix + "COPY AFTER ASSIGNMENT");
	if (ft_cont == copy_test) {
		std::cout << GREEN << "EQUAL";
	} else std::cout << RED << "NOT EQUAL";
	std::cout << RESET << std::endl;
	ft_cont.clear();
	copy_test.clear();
	s_printMap(ft_cont, false, __prefix + "_CONT CLEAN");
	s_printMap(copy_test, false, "COPY CLEAN");

	ftfile.close();
	gettimeofday(&ft_end, 0);
	std::cout << __prefix << " MAP TIME: " << YELLOW << std::fixed << calculate_time(ft_end, ft_begin) << RESET <<  std::endl;

	if (_nspace) {
		if (file_diff()) {
			std::cout << GREEN << "OK";
		} else {
			std::cout << RED << "FAIL";
		}
		std::cout << RESET << std::endl;		
		system("rm std_output.txt ft_output.txt");
	}
}

int main(void) {

	stack_Tests();
	stack_Tests(3);
	stack_Tests(50);
	vector_Tests();
	s_vector_Tests(2, true);
	vector_Tests(40);
	s_vector_Tests(40, true);
	vector_Tests(80);
	s_vector_Tests(80, true);
	map_Tests();
	s_map_Tests(2, true);
	map_Tests(4);
	s_map_Tests(4, true);
	map_Tests(20);
	s_map_Tests(20, true);

	return 0;
}
