#include "main.hpp"
#include <map>

int main() {


	ft::pair<int, int> pair(2, 24);

	ft::RBTree<int, ft::pair<int, int> >		tree;

	tree.insert(pair);
	tree.insert(ft::pair<int, int>(3, 434));

	//tree.printContent();

	//tree.deleteElement();

/* 	std::map<int, std::string>	map;
	std::string str("Hello");

	map.insert(str); */


	return 0;
}