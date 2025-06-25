#pragma once
#include <string>
#include <utility>
#include <vector>
#include "transaction.h"
#include "helper.h"

class Block {
	
	uint64_t time;
	uint64_t nonce;
	std::string hash;
	std::string prev_hash;
	std::string merkel_root;
	std::vector<Transaction> transactions;

	public:

	Block(const std::string& prev_hash, std::vector<Transaction>& transactions);

	void set_hash(const std::string& hash);
	void set_nonce(uint64_t nonce);

	uint64_t get_time() const;
	std::string get_hash() const;
	std::string get_prev_hash() const;
	std::string get_block_header() const;
	std::vector<Transaction> get_transactions() const;
};