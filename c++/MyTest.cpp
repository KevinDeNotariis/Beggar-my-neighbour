#include "MyTest.h"
#include <iostream>
#include <algorithm>

MyTest::MyTest(std::string _title) : title(_title) {}

void MyTest::check_number_of_passed_tests() {
	if (number_of_failed_tests != 0)
		std::cout << "\n" << "NUMBER OF TESTS PASSED: " << tests_results.size() - number_of_failed_tests << "/" << tests_results.size() << std::endl << std::endl;
	else
		std::cout << "\n" << "ALL TESTS PASSED!!!" << std::endl << std::endl;
}

void MyTest::display_failed_tests() {
	for (int i = 0; i < tests_results.size(); i++) {
		if (!tests_results.at(i).first) {
			number_of_failed_tests++;
			std::cout << "********* Test number " << i + 1 << " failed ********* " << std::endl;
			std::cout << "\t" << tests_results.at(i).second << std::endl;
			std::cout <<std::endl << "*************************************************" << std::endl;
		}
	}
}

void MyTest::run_all_tests() {
	std::cout << "Number of tests to run: " << vector_of_tests.size() << std::endl;
	for (int i = 0; i < vector_of_tests.size(); i++)
		tests_results.push_back(vector_of_tests.at(i)());
}


void MyTest::run() {
	printTitle();
	run_all_tests();
	display_failed_tests();
	check_number_of_passed_tests();
}

std::function<std::pair<bool, std::string>()> MyTest::assert_true(std::string title, std::string err_msg, std::function<bool ()> assert) {
	if (assert())
		return [] { return std::pair(true, std::string("")); };
	else
		return [err_msg] { return std::pair(false, err_msg); };
}

std::function<std::pair<bool, std::string>()> MyTest::assert_false(std::string title, std::string err_msg, std::function<bool ()> assert) {
	return assert_true(title, err_msg, [assert] {return !assert(); });
}


//Useful functions

std::string MyTest::wrapTitle() {
	std::string out = "";

	out += "*";
	for (int i = 0; i < (28 - title.length()) / 2; i++)
		out += " ";

	out += title;

	while (out.length() < 28)
		out += " ";

	out += "*";

	return out;
}

void MyTest::printTitle() {
	std::cout << "*****************************" << std::endl;
	std::cout << "*                           *" << std::endl;
	std::cout << wrapTitle() << std::endl;
	std::cout << "*                           *" << std::endl;
	std::cout << "*****************************" << std::endl;
}
