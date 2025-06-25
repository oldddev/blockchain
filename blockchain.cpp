#include "blockchain.h"
#include <iostream>
#include <algorithm>

#define SATOSHI "ae4afa1b7a019375f5ca3d30085ddc484df42b63deddabb7d357c568c36848f4"

Blockchain::Blockchain(unsigned int difficulty) : difficulty(difficulty) {
	create_genesis_block();
}

void Blockchain::create_genesis_block() {

	std::vector<TX_IN> inputs;
	std::vector<TX_OUT> outputs;

	outputs.push_back({ std::make_pair("SHAIKALI", 1000) });
	Transaction coinbase_tx(inputs, outputs);

	std::vector<Transaction> dummy_txs;
	dummy_txs.push_back(coinbase_tx);

	Block genesis_block("00000000", dummy_txs);

	uint64_t nonce = 0;

	std::string block_header = genesis_block.get_block_header();
	std::string hash;

	while (true) {
		hash = compute_hash(block_header + std::to_string(nonce));
		if (hash.substr(0, difficulty) == std::string(difficulty, '0')) break;
		nonce++;
	}

	genesis_block.set_hash(hash);
	genesis_block.set_nonce(nonce);

	blocks.push_back(genesis_block);

	update_utxo();

	std::cout << "Mined genesis block: " << "\n          Hash: " << hash << "\n          Nonce: " << nonce << "\n          Time: " << genesis_block.get_time() << "\n";

}

bool Blockchain::verify_transaction(const Transaction& tx, size_t index) {

	if (tx.get_inputs().size() == 0 && index == 0) {
		std::cout << "WAS A COINBASE TRANSACTION\n";
		return true; // COINBASE_CONDITION
	}

	uint64_t input_sum = 0;
	uint64_t output_sum = 0;

	for (const TX_IN& in : tx.get_inputs()) { // KEEP EYE ON THIS LOGIC
		std::string unspent_key = in.input.first + ":" + std::to_string(in.input.second);
		if (utxo.find(unspent_key) == utxo.end()) continue;
		auto& it = utxo[unspent_key];
		input_sum += it.output.second;
	}

	for (const TX_OUT& out : tx.get_outputs()) {
		output_sum += out.output.second;
	}

	if (input_sum < output_sum) {
		return false; // BUSTED
		std::cout << "[DEBUG] Transaction rejected for overspending!" << "\n";
	}

	return true;

}

std::vector<std::string> Blockchain::find_unspents(const std::string& addr) {

	std::vector<std::string> unspents;
	for (auto& it : utxo) {
		if (it.second.output.first == addr) {
			unspents.push_back(it.first);
		}
	}
	return unspents;
}

void Blockchain::initiate_transaction(const std::string& sender, const std::string& receiver, uint64_t amount) {

	std::vector<TX_IN> inputs;
	std::vector<TX_OUT> outputs;
	uint64_t total = 0;

	std::vector<std::string> unspents = find_unspents(sender);

	if (!unspents.size()) return;

	for (auto& in : unspents) {

		size_t colon = in.find(":");

		std::string tx_id = in.substr(0, colon);
		unsigned int output_index = stoi(in.substr(colon + 1));

		total += utxo[in].output.second;

		inputs.push_back(TX_IN(std::make_pair(tx_id, output_index)));

	}

	TX_OUT reciepent{ std::make_pair(receiver, amount) };
	outputs.push_back(reciepent);

	if (total > amount) {
		TX_OUT pay_back{ std::make_pair(sender, total - amount) };
		outputs.push_back(pay_back);
	}

	Transaction tx(inputs, outputs);

	pending_transactions.push_back(tx); //Finally, Yahooooooooo!

}


void Blockchain::mine() {

	int take = std::min(10,(int)pending_transactions.size());
	std::cout << "TAKEN: " << take << "\n";

	std::vector<TX_IN> inputs;
	std::vector<TX_OUT> outputs;

	outputs.push_back({ std::make_pair("SHAIKALI", 5) });

	Transaction my_coinbase(inputs, outputs);
	std::vector<Transaction> include_tx;
	include_tx.push_back(my_coinbase);

	for (size_t i = 0; i < take; i++) {
		include_tx.push_back(pending_transactions[i]);
	}

	for (size_t i = 0; i < include_tx.size(); i++) {
		if (!verify_transaction(include_tx[i], i)) {
			std::cout << "[DEBUG] Transaction rejected.\n";
		}
	}

	Block block_to_mine(blocks.back().get_hash(), include_tx);
	std::string base = block_to_mine.get_block_header();

	std::string hash;
	uint64_t nonce = 0;

	while (true) {
		hash = compute_hash(base + std::to_string(nonce));
		if (hash.substr(0, difficulty) == std::string(difficulty, '0')) break;
		nonce++;
	}

	block_to_mine.set_hash(hash);
	block_to_mine.set_nonce(nonce);

	blocks.push_back(block_to_mine);
	update_utxo();
	pending_transactions.clear();

	std::cout << "Mined new block: " << "\n          Hash: " << hash << "\n          Nonce: " << nonce << "\n          Time: " << block_to_mine.get_time() << "\n";

}

void Blockchain::update_utxo() {
	for (const Block& b : blocks) {
		for (const Transaction& tx : b.get_transactions()) {
			for (const TX_IN& in : tx.get_inputs()) {
				utxo.erase(in.input.first + ":" + std::to_string(in.input.second));
			}
			for (size_t i = 0; i < tx.get_outputs().size(); i++) {
				utxo[tx.get_transaction_id() + ":" + std::to_string(i)] = tx.get_outputs()[i];
			}
		}
	}
}

void Blockchain::show_utxo() const {
	for (auto& it : utxo) {
		std::cout << it.second.output.first << " has " << it.second.output.second << "\n";
	}
}