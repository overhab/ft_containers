#include "main.hpp"
#include <list>
#include <map>
#include <vector>

#define FIRST_TYPE int
#define SECOND_TYPE std::string
#define T3 ft::pair<const FIRST_TYPE, SECOND_TYPE>
#define T4 std::pair<const FIRST_TYPE, SECOND_TYPE>

int main() {


	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));

	std::list<T4> lst2;
	unsigned int lst2_size = 10;
	for (unsigned int i = 0; i < lst2_size; ++i)
		lst2.push_back(T4(i, std::string((lst2_size - i), i + 65)));

	ft::map<FIRST_TYPE, SECOND_TYPE>			mymap(lst.begin(), lst.end());
	std::map<FIRST_TYPE, SECOND_TYPE>			maaap(lst2.begin(), lst2.end());


	//std::cout << "max_size = " << mymap.max_size() << std::endl;

	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(10, "434"));
	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;
	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(3, "21"));
	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(35, "61"));
	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(2, "84"));
	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(12, "81"));
	mymap.insert(ft::pair<FIRST_TYPE, SECOND_TYPE>(7, "55"));

	ft::map<FIRST_TYPE,SECOND_TYPE>::iterator ttt = mymap.lower_bound(12);

	mymap.insert(mymap.begin(), ft::pair<FIRST_TYPE, SECOND_TYPE>(1, "101"));




	std::cout << "-----------ITERATOR-------------" << std::endl;
	
	//itt->second = 2222222;
	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;

	//mymap.printTree();
	std::cout << "mymap[3] = " << mymap[3] << std::endl;

	std::cout << "size before erase = " << mymap.size() << std::endl;
	ft::map<FIRST_TYPE, SECOND_TYPE>::iterator loa = mymap.lower_bound(1);

	std::cout << "lower_bound(1): " << loa->first << " " << loa->second << std::endl;



	std::cout << "size before erase = " << mymap.size() << std::endl;
	mymap.erase(++mymap.begin());
	mymap.erase(mymap.begin());
	mymap.erase(--mymap.end());
	mymap.erase(mymap.begin(), ++(++(++mymap.begin())));
	mymap.erase(--(--(--mymap.end())), --mymap.end());
	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;

	/* std::cout << "-----------MAP-------------" << std::endl;
	std::cout << "size before erase = " << maaap.size() << std::endl;
	maaap.erase(++maaap.begin());
	maaap.erase(maaap.begin());
	maaap.erase(--maaap.end());
	maaap.erase(maaap.begin(), ++(++(++maaap.begin())));
	maaap.erase(--(--(--maaap.end())), --maaap.end());
	for (std::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = maaap.begin(); itt != maaap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl; */




	/* mymap.erase(mymap.begin());
	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl;
	mymap.erase(--mymap.end());
	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl; */


	/* std::cout << "size after erase = " << mymap.size() << std::endl;

	for (ft::map<FIRST_TYPE, SECOND_TYPE>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl; */

	//mymap.clear();


	/* std::cout << "-----------ERASE-------------" << std::endl;

	mymap.erase(ttt);

	for (ft::map<int, int>::iterator itt = mymap.begin(); itt != mymap.end(); ++itt)
		std::cout << itt->first << ' ' << itt->second << std::endl; */


	//mymap.printTree();


	/* std::cout << "find(35): " << mymap.find(35)->second << "\ncount(3): " << mymap.count(3) << std::endl;
	
	ft::map<int, int>::iterator	kek = mymap.end();
	--kek;
	std::cout << "--end(): " << kek->first << ' ' << kek->second << std::endl;

	ft::map<int, int>::const_iterator	low_b = mymap.lower_bound(12);

	std::cout << "lower bound(12): " << low_b->second << std::endl;

	ft::map<int, int>::const_iterator	up_b = mymap.upper_bound(12);

	std::cout << "upper bound(12): " << up_b->second << std::endl; */

	//tree.iterator_test();
	
	/* std::cout << "-----------MAP-------------" << std::endl;

	std::map<int, int>	mmap;
	std::cout << "max_size = " << mmap.max_size() << std::endl;

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

	std::cout << "upper bound(3): " << ub->second << std::endl; */


	/* ft::map<int, int>  const const_map;
	ft::map<int, int>::iterator it = const_map.begin();
	
	(void)it; */

	return 0;
}
