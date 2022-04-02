#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>

int main() {
	std::vector<int> sequence = {1,2,3,4,5,6,7,8,9,10};

	int input;

	while ((std::cin >> input) && input != 12)
    	sequence.push_back(input);

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(sequence.begin(), sequence.end(), g);

   	std::set<int> s(sequence.begin(), sequence.end() );
	sequence.assign(s.begin(), s.end() );

	int count = 0;

    for(auto i: sequence){
    	if (i % 2 == 1)
    		count++;
    }

    std::cout << count;

    std::vector<int>::iterator min = std::min_element(sequence.begin(), sequence.end());

    std::vector<int>::iterator max = std::max_element(sequence.begin(), sequence.end());

	return 0;
}
