#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>
#include <any>

class MyTest
{
	std::string title;

	// Test functions return a pair<bool,string> where the bool variable store
	// the fact that the test did or did not pass and the string store the
	// message when the test didn't pass.
	std::vector<std::function<std::pair<bool, std::string>()>> vector_of_tests;

	std::vector<std::pair<bool, std::string>> tests_results;
	int number_of_failed_tests = 0;

public:
	//CONSTRUCTOR
	MyTest(std::string);


	//Set up to be run every time a test is tested.
	std::function<void()> set_up;

	template <typename Function> void add_test(Function&& function, ...) {
		set_up();
		this->vector_of_tests.push_back(std::forward<Function>(function));
	}

	void check_number_of_passed_tests();

	void display_failed_tests();

	void run_all_tests();

	void run();

	std::function<std::pair<bool, std::string>()> assert_true(std::string title, std::string err_msg, std::function<bool ()> assert);

	std::function<std::pair<bool, std::string>()> assert_false(std::string title, std::string err_msg, std::function<bool()> assert);


	//Useful functions
	void printTitle();
	std::string wrapTitle();
};

