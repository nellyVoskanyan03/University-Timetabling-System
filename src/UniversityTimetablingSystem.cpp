#include <iostream>
#include <vector>
#include "../include/University.h"

void interaction() {
	University uni;
	std::string path;
	std::cout << "Enter full path of the json file of university state: ";
	std::cin >> path;
	std::cout << "Timetable will be generated in file timetable.txt in the same folder with your provided folder";
	uni.loadState(path);
	uni.schedule();
	uni.saveState(path);


}

int main(int argc, char* argv[])
{
	
	interaction();
	return 0;
}
