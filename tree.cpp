#include "main.hpp"
#include <map>

int main() {

	ft::map<int, int>			mymap;
	//ft::RBTree<int, ft::pair<int, int> >		tree;

	mymap.insert(ft::pair<int, int>(10, 434));
	mymap.insert(ft::pair<int, int>(3, 21));
	mymap.insert(ft::pair<int, int>(35, 61));
	mymap.insert(ft::pair<int, int>(2, 84));
	mymap.insert(ft::pair<int, int>(12, 81));
	mymap.insert(ft::pair<int, int>(7, 55));

	ft::map<int,int>::iterator ttt = mymap.lower_bound(12);

	mymap.insert(mymap.begin(), ft::pair<int, int>(1, 101));



	std::cout << "-----------ITERATOR-------------" << std::endl;
	
	//itt->second = 2222222;
	for (ft::map<int, int>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;

	mymap.printTree();

	std::cout << "-----------ERASE-------------" << std::endl;

	mymap.erase(ttt);

	for (ft::map<int, int>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;

	mymap.printTree();

	/* std::cout << "find(35): " << mymap.find(35)->second << "\ncount(3): " << mymap.count(3) << std::endl;
	
	ft::map<int, int>::iterator	kek = mymap.end();
	--kek;
	std::cout << "--end(): " << kek->first << ' ' << kek->second << std::endl;

	ft::map<int, int>::const_iterator	low_b = mymap.lower_bound(12);

	std::cout << "lower bound(12): " << low_b->second << std::endl;

	ft::map<int, int>::const_iterator	up_b = mymap.upper_bound(12);

	std::cout << "upper bound(12): " << up_b->second << std::endl; */

	//tree.iterator_test();
	
	std::cout << "-----------MAP-------------" << std::endl;

	std::map<int, int>	mmap;

	mmap.insert(std::pair<int, int>(1, 10));
	mmap.insert(std::pair<int, int>(2, 20));
	mmap.insert(std::pair<int, int>(3, 30));
	mmap.insert(std::pair<int, int>(4, 40));
	mmap.insert(std::pair<int, int>(5, 50));
	mmap.insert(std::pair<int, int>(5, 5120));

	std::map<int, int>::iterator it = mmap.begin();
	for (; it != mmap.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;

	std::map<int, int>::iterator lb = mmap.lower_bound(3);

	std::cout << "lower bound(3): " << lb->second << std::endl;

	std::map<int, int>::iterator ub = mmap.upper_bound(3);

	std::cout << "upper bound(3): " << ub->second << std::endl;

	return 0;
}
