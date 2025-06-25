#pragma once

#include "block.h"
#include <unordered_map>

class Blockchain {

	unsigned int difficulty;
	std::vector<Block> blocks;
	std::unordered_map<std::string, TX_OUT> utxo;
	std::vector<Transaction> pending_transactions;

	public:

	Blockchain(unsigned int difficulty);
	void create_genesis_block();
	bool verify_transaction(const Transaction& tx, size_t index);
	std::vector<std::string> find_unspents(const std::string& addr);
	void mine();
	void initiate_transaction(const std::string& sender, const std::string& receiver, uint64_t amount);
	void update_utxo();
	void show_utxo() const;
	bool validate_miner_block();

};