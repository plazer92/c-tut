#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include <numeric>
#include <iterator>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

int main() {
	std::vector<int> sequence1 = {1,2,3,4,5,6,7,8,9,10};

	int input;

	while ((std::cin >> input) && input != 12)
    	sequence1.push_back(input);

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(sequence1.begin(), sequence1.end(), g);

   	std::set<int> s(sequence1.begin(), sequence1.end() );
	sequence1.assign(s.begin(), s.end() );

	int count = 0;

    for(auto i: sequence1){
    	if (i % 2 == 1)
    		count++;
    }

    std::cout << count << std::endl;

    std::vector<int>::iterator min = std::min_element(sequence1.begin(), sequence1.end());

    std::vector<int>::iterator max = std::max_element(sequence1.begin(), sequence1.end());

    int count2 = 0;

    for(auto i: sequence1)
        if(i % 2 == 0)
            if(i == 2) {
                count2++;
                break;
            }

    std::transform(sequence1.cbegin(), sequence1.cend(), sequence1.cbegin(),
                   sequence1.begin(), std::multiplies<>{});

    std::vector<int> sequence2;
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

    for(int i = 0; i < sequence1.size(); ++i)
        sequence2.push_back(dist(g));        

    std::accumulate(sequence2.begin(), sequence2.end(), 0);

    sequence2.assign(4, 1);

    std::vector<int> sequence3;

    std::set_difference(sequence1.begin(), sequence1.end(), sequence2.begin(), sequence2.end(),
        std::inserter(sequence3, sequence3.begin()));

    for(auto i: sequence3) {
        if(i < 0)
            i = 0;
    }

    sequence3.erase(std::remove(sequence3.begin(), sequence3.end(), 0),sequence3.end());
    sequence3.shrink_to_fit();

    std::reverse(sequence3.begin(), sequence3.end());

    std::partial_sort(sequence3.begin(), sequence3.begin() + 3, sequence3.end(), std::greater<int>());

    std::sort (sequence1.begin(), sequence1.end());  
    std::sort (sequence2.begin(), sequence2.end());  

    std::vector<int> sequence4;

    sequence4.resize(sequence1.size() + sequence2.size());
    std::move(sequence1.begin(), sequence1.end(), sequence4.begin());
    std::move(sequence2.begin(), sequence2.end(), sequence4.begin() + sequence1.size());

    std::cout << sequence1 << std::endl;
    std::cout << sequence2 << std::endl;
    std::cout << sequence3 << std::endl;
    std::cout << sequence4 << std::endl;

	return 0;
}
