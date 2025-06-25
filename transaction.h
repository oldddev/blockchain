#pragma once

#include <utility>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "helper.h"

struct TX_IN {
	std::pair<std::string, unsigned int> input;
	TX_IN(std::pair<std::string, unsigned int> input) :input(input){}
};

struct TX_OUT {
	std::pair<std::string, uint64_t> output;
};

class Transaction {

	std::vector<TX_IN> inputs;
	std::vector<TX_OUT> outputs;
	std::string transaction_id;
	uint64_t time;

	public:

	Transaction(std::vector<TX_IN> inputs, std::vector<TX_OUT> outputs);

	std::string get_transaction_id() const;
	std::vector<TX_OUT> get_outputs() const;
	std::vector<TX_IN> get_inputs() const;

};