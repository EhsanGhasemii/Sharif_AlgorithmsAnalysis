#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// define Passenger data structure
struct Passenger {
	std::string airline; 
	std::string name; 
	std::string sex; 
	std::string age; 
	std::string marriage; 
	std::string origin; 
	std::string destination; 
}; 


// define Airline data structures
struct Airline {
	std::string name; 
	std::string safety; 
	std::string international; 
	std::string satisfaction; 
	std::string plane; 
	std::string discount; 
	std::string first_class; 
	std::string age; 
	std::string employee;
	std::vector<int> ways; 
	std::vector<Passenger> passengers; 
}; 


// define our functions
void addPassenger(std::string file_name, std::vector<Airline> airlines); 
void removePassenger(std::string file_name); 
void search(std::vector<Airline> airlines, std::string file_name); 
void sort(std::string file_name, std::vector<Airline> airlines); 
std::vector<Airline> updateAirlines(std::string file_name);
void updatePassengers(std::string file_name, std::vector<Airline>& airlines); 


int main() { 

	// define requierment variables
	std::string user_choise = "0";
	std::vector<Airline> airlines;

	while(user_choise != "5") { 
		
		// Update airlines list in each step 
		airlines = updateAirlines("Airlines.txt"); 

		// Update airlines passengers list in each step
		updatePassengers("Passengers.txt", airlines);

		// initial message to user
		std::cout << "I would be happy to know what I can do for you?" << std::endl; 
		std::cout << "1. Add passenger" << std::endl; 
		std::cout << "2. Remove passenger" << std::endl; 
		std::cout << "3. Search" << std::endl; 
		std::cout << "4. Sort" << std::endl; 
		std::cout << "5. Exit" << std::endl; 
		std::cout << "Your choise: "; 
		std::getline(std::cin, user_choise);

		// add passenger
		if (user_choise == "1") { 
			addPassenger("Passengers.txt", airlines);
		}

		// remove passenger
		else if (user_choise == "2") {
			removePassenger("Passengers.txt");
		}

		// search among airlines or passengers
		else if (user_choise == "3") {
			search(airlines, "Passengers.txt"); 
		}

		// sort airlines or passengers
		else if (user_choise == "4") {
			sort("Passengers.txt", airlines); 
		}
		
		// end of each process
		std::cout << "======================================" << std::endl;

	} // end of while(user_choise != "5")


	return 0; 
}



// Specify our functions 
void addPassenger(std::string file_name, std::vector<Airline> airlines) {

	std::cout << "In which airline do you want to register the passenger?" << std::endl; 
	
	std::string passenger_airline; 
	std::getline(std::cin, passenger_airline); 
	std::cout << "Sure, please complete the following information about the passenger:" << std::endl;
	std::cout << "Full Name: "; 
	std::string passenger_name; 
	std::getline(std::cin, passenger_name); 

	std::string passenger_sex; 
	std::cout << "Sex: "; 
	std::getline(std::cin, passenger_sex); 

	std::string passenger_age; 
	std::cout << "Age: "; 
	std::getline(std::cin, passenger_age); 

	std::string passenger_marriage; 
	std::cout << "Marriage: "; 
	std::getline(std::cin, passenger_marriage); 

	std::string passenger_origin; 
	std::cout << "Origin: "; 
	std::getline(std::cin, passenger_origin); 

	std::string passenger_destination; 
	std::cout << "Destination: "; 
	std::getline(std::cin, passenger_destination); 

	// loop over the airlines to find the target one
	for (int i = 0; i < airlines.size(); ++i) { 

		// check to find target airline
		if (airlines[i].name == passenger_airline) {

			// set error flag to 0
			int error_flag = 0; 

			// loop over passengers of target airline
			for (int j = 0; j < airlines[i].passengers.size(); ++j) {

				// error num 1)
				if (airlines[i].name == passenger_airline &&
					airlines[i].passengers[j].name == passenger_name &&
					airlines[i].passengers[j].sex == passenger_sex && 
					airlines[i].passengers[j].age == passenger_age &&
					airlines[i].passengers[j].marriage == passenger_marriage &&
					airlines[i].passengers[j].origin == passenger_origin &&
					airlines[i].passengers[j].destination == passenger_destination) {
					std::cout << "Error 1) This passenger is exist in the airline" << std::endl; 
					error_flag = 1; 
					break; 
				} // end of error num 1)
	
			} // end of loop over passengers of target airline

			// error num 2)
			int pass_org; 
			int pass_des;

			if (passenger_destination == "Emirates") {
				pass_des = 0; 
			}
			else if (passenger_destination == "America") {
				pass_des = 1; 
			}
			else if (passenger_destination == "Germany") {
				pass_des = 2; 
			}
			else if (passenger_destination == "Canada") {
				pass_des = 3; 
			}
			else {
				pass_des = 4; 
			}

			if (passenger_origin == "Emirates") {
				pass_org = 0; 
			}
			else if (passenger_origin == "America") {
				pass_org = 1; 
			}
			else if (passenger_origin == "Germany") {
				pass_org = 2; 
			}
			else if (passenger_origin == "Canada") {
				pass_org = 3; 
			}
			else {
				pass_org = 4;
			}



			if (pass_des > 3 || pass_org > 3 || airlines[i].ways[pass_org * 4 + pass_des] == 0) {
				std::cout << "Error 2) There are no flights from the source to the destination" << std::endl; 
				error_flag = 1; 
			}

			// error num 3)
			for (int i = 0; i < passenger_age.size(); ++i) { 
				if (passenger_age[i] < 48 || passenger_age[i] > 57) {
					std::cout << "Error 3) Invalid input information.(age is not a positive integer)" << std::endl; 
					error_flag = 1; 
					break; 
				}
			}

			if (passenger_sex != "Male" && passenger_sex !="Female") {
				std::cout << "Error 3) Invalid input information.(sex is not Male/Female)" << std::endl; 
				error_flag = 1; 
			}

			if (passenger_marriage != "Single" && passenger_marriage != "Married") {
				std::cout << "Error 3) Invalid input infomration.(marriage is not Single/Married)" << std::endl; 
				error_flag = 1; 
			}

			// add the passenger to the database
			if (!error_flag) { 
				std::string passenger_information =  
													passenger_airline + "," + 
													passenger_name + "," + 
													passenger_sex + "," + 
													passenger_age + "," + 
													passenger_marriage + "," + 
													passenger_origin + "," + 
													passenger_destination + "\n"; 

				
				std::ofstream passengerFile(file_name, std::ios_base::app); 
				passengerFile << passenger_information; 
				passengerFile.close();
				std::cout << passenger_name << " has been added to " << passenger_airline << " successfuly." << std::endl; 
			}


		} // end of check to find target airline

	} // end of loop over the airlines to find target one

} // end of the function

void removePassenger(std::string file_name) {
	std::cout << "In which airline do you want to remove the passenger? "; 
	std::string passenger_airline; 
	std::getline(std::cin, passenger_airline);

	std::cout << "Sure, please enter the passenger's name: "; 
	std::string passenger_name; 
	std::getline(std::cin, passenger_name); 

	std::vector<std::string> file_lines; 
	std::string file_line; 
	std::ifstream file(file_name);

	int error_flag = 1; 

	// reading input file
	while (std::getline(file, file_line)) {
		
		// check if the passenger is in the airline
		std::istringstream line_stream(file_line);

		std::string file_passenger_airline; 
		std::getline(line_stream, file_passenger_airline, ','); 

		std::string file_passenger_name; 
		std::getline(line_stream, file_passenger_name, ',');

		// dont store the passenger name in the airline
		if (file_passenger_airline != passenger_airline || file_passenger_name != passenger_name) {
			file_lines.push_back(file_line); 
		}
		else {
			error_flag = 0; 
		}
	} // end of reading input file

	file.close();

	std::ofstream file2(file_name); 

	// storing lines in the file
	for (int i = 0; i < file_lines.size(); ++i) { 
		file2 << file_lines[i] << std::endl; 
	} // end of storing lines in the file

	if (error_flag) {
		std::cout << "Error 4) This passenger is not exist in the airline." << std::endl; 
	}
	else {
		std::cout << "THe passenger has been removed sucessfuly." << std::endl; 
	}

	file2.close(); 

}

void search(std::vector<Airline> airlines, std::string file_name) {
	std::cout << "In which section do you want to serach? " << std::endl;
	std::cout << "1. Airlines" << std::endl; 
	std::cout << "2. Passengers" << std::endl; 

	std::string search_option; 
	std::getline(std::cin, search_option); 

	// search over targer airline
	if (search_option == "1") {
		
		std::cout << "Sure, please enter the name of the airline: "; 
		std::string search_airline; 
		std::getline(std::cin, search_airline); 

		// loop over airlines to find target one
		for (int i = 0; i < airlines.size(); ++i) {
			
			// check to find target ailine
			if (airlines[i].name == search_airline) {
				std::cout << "Safety: " << airlines[i].safety << "%" << std::endl;
				std::cout << "Internationnal: " << airlines[i].international << std::endl; 
				std::cout << "Satisfaction: " << airlines[i].satisfaction << std::endl; 
				std::cout << "Plane: " << airlines[i].plane << std::endl; 
				std::cout << "Discount: " << airlines[i].discount << std::endl; 
				std::cout << "First-Class: " << airlines[i].first_class << std::endl; 
				std::cout << "Age: " << airlines[i].age << std::endl; 
				std::cout << "Employee: " << airlines[i].employee << std::endl; 
				std::cout << "Number of passengers: " << airlines[i].passengers.size() << std::endl; 

			}
		} // end of loop over airlines to find target one
	}

	// search over target passenger
	else if (search_option == "2") {
		std::cout << "Sure, please enter the name of the passenger: ";
		std::string search_passenger; 
		std::getline(std::cin, search_passenger); 

		std::ifstream file(file_name); 
		std::string line; 

		std::string passenger_airline; 
		std::string passenger_name; 
		std::string passenger_sex; 
		std::string passenger_age; 
		std::string passenger_marriage; 
		std::string passenger_origin; 
		std::string passenger_destination; 


		while (std::getline(file, line)) {
			std::istringstream line_stream(line);

			std::getline(line_stream, passenger_airline, ','); 
			std::getline(line_stream, passenger_name, ','); 
			std::getline(line_stream, passenger_sex, ','); 
			std::getline(line_stream, passenger_age, ','); 
			std::getline(line_stream, passenger_marriage, ','); 
			std::getline(line_stream, passenger_origin, ','); 
			std::getline(line_stream, passenger_destination, ','); 

			// print the passenger if it is matched
			if (search_passenger == passenger_name) { 
				std::cout << "Name: " << passenger_name << std::endl; 
				std::cout << "Sex: " << passenger_sex << std::endl; 
				std::cout << "Age: " << passenger_age << std::endl;
				std::cout << "Marriage: " << passenger_marriage << std::endl; 
				std::cout << "Origin: " << passenger_origin << std::endl; 
				std::cout << "Destination: " << passenger_destination << std::endl; 
				std::cout << "Airline: " << passenger_airline << std::endl; 
			}

		}

		file.close(); 
	}
	else {
		std::cout << "Invalid option." << std::endl; 
	}
}

void sort(std::string file_name, std::vector<Airline> airlines) { 
	std::cout << "In which section do you want to sort?" << std::endl;
	std::cout << "1. Airlines" << std::endl; 
	std::cout << "2. Passengers" << std::endl; 

	std::string sort_option; 
	std::getline(std::cin, sort_option); 

	// sorting base of airlines satisfaction
	if (sort_option == "1") { 
		
		std::vector<int> airlines_satisfaction; 

		// loop over airlines to store all satisfaction numbers
		for (int i = 0; i < airlines.size(); ++i) {
			airlines_satisfaction.push_back(std::stoi(airlines[i].satisfaction));
		} // end of loop over airlines to store all satisfaction numbers

		// sor vector of satisfaction
		std::sort(airlines_satisfaction.begin(), airlines_satisfaction.end(), std::greater<int>()); 

		// loop over vector of satisfaction
		for (int i = 0; i < airlines_satisfaction.size(); ++i) { 

			// loop over vector of airlines
			for (int j = 0; j < airlines.size(); ++j) { 

				// check to find a match 
				if (airlines_satisfaction[i] == std::stoi(airlines[j].satisfaction)) { 
					std::cout << airlines[j].name << " " << airlines[j].satisfaction << std::endl;
				}
			} // end of loop over vector of airlines
		} // end of loop over vector of satisfaction
	} // end of sorting base of airlines satisfaction


	// sorting base of the passengers name 
	else if (sort_option == "2") { 

		std::ifstream file(file_name);
		std::string sort_line; 
		std::vector<std::string> passengers; 

		// reading lines of the file
		while (std::getline(file, sort_line)) {

			std::istringstream line_stream(sort_line);
			std::string passenger_name; 
			std::getline(line_stream, passenger_name, ',');
			std::getline(line_stream, passenger_name, ','); 

			passengers.push_back(passenger_name); 
		} // end of reading lines of the file

		std::sort(passengers.begin(), passengers.end()); 

		for (int i = 0; i < passengers.size(); ++i) { 
			std::cout << passengers[i] << std::endl; 

		}

	}

	// invalid input option
	else {
		std::cout << "Invalid option." << std::endl; 
	}
}


// function 5) update airlines list
std::vector<Airline> updateAirlines (std::string file_name){ 
	
	std::string file_line; 

	// read the file
	std::ifstream file(file_name);

	// create output vector 
	std::vector<Airline> airlines; 

	while (std::getline(file, file_line)) {

		Airline airline; 

		std::istringstream line_stream(file_line);
	
		std::getline(line_stream, airline.name, ','); 
		std::getline(line_stream, airline.safety, ','); 
		std::getline(line_stream, airline.international, ',');
		std::getline(line_stream, airline.satisfaction, ','); 
		std::getline(line_stream, airline.plane, ','); 
		std::getline(line_stream, airline.discount, ','); 
		std::getline(line_stream, airline.first_class, ',');
		std::getline(line_stream, airline.age, ','); 
		std::getline(line_stream, airline.employee, ','); 

		// create ways matrix
		if (airline.name == "Delta") { 
			airline.ways = {0, 0, 1, 0, 
							1, 0, 1, 1, 
							0, 1, 0, 1, 
							1, 1, 0, 0};

			// store each airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "American") { 
			airline.ways = {0, 1, 0, 0, 
							1, 0, 1, 0, 
							0, 1, 0, 1, 
							0, 0, 1, 0};

			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Turkish") { 
			airline.ways = {0, 1, 0, 1, 
							1, 0, 1, 0, 
							0, 1, 0, 1, 
							1, 0, 1, 0}; 
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Indiana") { 
			airline.ways = {0, 1, 0, 0, 
							1, 0, 1, 1, 
							0, 1, 0, 0, 
							0, 1, 0, 0}; 
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Emirates") {
			airline.ways = {0, 1, 1, 1, 
							1, 0, 1, 0, 
							1, 1, 0, 1, 
							1, 0, 1, 0}; 
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Lufthansa") { 
			airline.ways = {0, 1, 0, 1, 
							1, 0, 0, 1, 
							0, 0, 0, 0, 
							1, 1, 0, 0};
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Air France") { 
			airline.ways = {0, 1, 0, 0, 
							1, 0, 0, 1, 
							0, 0, 0, 1, 
							0, 1, 1, 0}; 
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Qantas") { 
			airline.ways = {0, 1, 0, 0, 
							1, 0, 0, 0, 
							0, 0, 0, 1, 
							0, 0, 1, 0};
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "Singapore") { 
			airline.ways = {0, 1, 1, 0, 
							1, 0, 0, 1, 
							1, 0, 0, 0, 
							0, 1, 0, 0};
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
		else if(airline.name == "British Airways") { 
			airline.ways = {0, 1, 0, 0, 
							1, 0, 1, 1, 
							0, 1, 0, 1, 
							0, 1, 1, 0}; 
			
			// store the airline in a vector
			airlines.push_back(airline); 
		}
	}
	return airlines; 
}

// function 6) Update passengers
void updatePassengers(std::string file_name, std::vector<Airline>& airlines) {

	std::ifstream file(file_name); 
	std::string file_line; 

	while (std::getline(file, file_line)) { 
		Passenger passenger; 

		std::istringstream line_stream(file_line); 
		std::getline(line_stream, passenger.airline, ','); 
		std::getline(line_stream, passenger.name, ',');
		std::getline(line_stream, passenger.sex, ','); 
		std::getline(line_stream, passenger.age, ','); 
		std::getline(line_stream, passenger.marriage, ','); 
		std::getline(line_stream, passenger.origin, ','); 
		std::getline(line_stream, passenger.destination, ',');

		for (int i = 0; i < airlines.size(); ++i) { 
			if (passenger.airline == airlines[i].name) { 
				airlines[i].passengers.push_back(passenger); 
			}
		}
	}
}










