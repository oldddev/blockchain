#include "block.h"
#include <iostream>

Block::Block(const std::string& prev_hash, std::vector<Transaction>& transactions) : prev_hash(prev_hash), transactions(transactions), nonce(0) {

	auto now = std::chrono::high_resolution_clock::now();
	time = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

	std::vector<std::string> txids;

	for (const auto& tx : transactions) {
		txids.push_back(tx.get_transaction_id());
	}

	this->merkel_root = compute_merkle_root(txids);

}

std::string Block::get_hash() const {
	return hash;
}

std::string Block::get_prev_hash() const {
	return prev_hash;
}

std::vector<Transaction> Block::get_transactions() const {
	return transactions;
}

void Block::set_nonce(uint64_t nonce) {
	this->nonce = nonce;
}

void Block::set_hash(const std::string& hash) {
	this->hash = hash;
}

std::string Block::get_block_header() const {
	return prev_hash + merkel_root + std::to_string(time); // PREVIOUS_HASH -> MERKLE_ROOT -> TIME -> NONCE = BLOCK_HEADER
}
uint64_t Block::get_time() const {
	return time;
}
