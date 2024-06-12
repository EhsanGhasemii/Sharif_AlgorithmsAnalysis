#include <iostream>
#include <vector>
#include <sstream>

int main() { 


	// define the requierments variables
	int m; 
	int n; 
	std::string my_line; 

	// get number of rows and columns from user
	std::getline(std::cin, my_line); 
	std::stringstream my_line_stream(my_line); 
	my_line_stream >> m >> n; 

	// define our map vector
	std::vector<std::string> my_map; 

	// get and stroe the map from user
	for (int i = 0; i < n; ++i) { 
		std::getline(std::cin, my_line);
		my_map.push_back(my_line); 
	} // enf of loop over rows

	// process over the map
	for (int i = 0; i < n; ++i) { 
		
		for (int j = 0; j < m; ++j) {

			// process over margins
			if (i == 0 && j == 0 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i][j+1] == '*') +
												 (my_map[i+1][j+1] == '*') +
												 (my_map[i+1][j] == '*') + '0'); 
			} 

			else if (i == 0 && j == m -1 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i][j-1] == '*') +
												 (my_map[i+1][j-1] == '*') +
												 (my_map[i+1][j] == '*') + '0'); 
			} 

			else if (i == n-1 && j == 0 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i-1][j] == '*') +
												 (my_map[i-1][j+1] == '*') +
												 (my_map[i][j+1] == '*') + '0'); 
			} 

			else if (i == n-1 && j == m-1 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i-1][j] == '*') +
												 (my_map[i-1][j-1] == '*') +
												 (my_map[i][j-1] == '*') + '0'); 
			}

			else if (i == 0 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i][j-1] == '*') +
												 (my_map[i][j+1] == '*') +
												 (my_map[i+1][j] == '*') + '0'); 
			}

			else if (i == n-1 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i][j-1] == '*') +
												 (my_map[i][j+1] == '*') +
												 (my_map[i-1][j] == '*') + '0'); 
			}

			else if (j == 0 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i-1][j] == '*') +
												 (my_map[i+1][j] == '*') +
												 (my_map[i][j+1] == '*') + '0'); 
			}

			else if (j == m-1 && my_map[i][j] != '*') {
				my_map[i][j] = static_cast<char>((my_map[i-1][j] == '*') +
												 (my_map[i+1][j] == '*') +
												 (my_map[i][j-1] == '*') + '0'); 
			}

			else if (my_map[i][j] != '*'){
				my_map[i][j] = static_cast<char>((my_map[i][j-1] == '*') +
												 (my_map[i][j+1] == '*') +
												 (my_map[i-1][j] == '*') +
												 (my_map[i+1][j] == '*') + '0'); 
			}
			
		}
	}

	// print the map
	for (int i = 0; i < n; ++i) { 
		for (int j = 0; j < m; ++j) {
			std::cout << my_map[i][j]; 
		}
		std::cout << std::endl; 
	}

	return 0; 
}
