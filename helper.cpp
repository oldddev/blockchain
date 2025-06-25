#include "helper.h"

std::string compute_hash(const std::string& input) {
	return picosha2::hash256_hex_string(input);
}

std::string compute_merkle_root(const std::vector<std::string>& inputs) {

	if (inputs.size() == 1) return compute_hash(inputs[0]);

	std::vector<std::string> txs;

	for (const auto& in : inputs) {
		txs.push_back(compute_hash(in));
	}

	while (txs.size() > 1) {

		std::vector<std::string> new_level;

		if (txs.size() % 2 != 0) txs.push_back(txs.back());


		for (size_t i = 0; i < txs.size(); i += 2) {
			std::stringstream base;
			base << txs[i] << txs[i + 1];
			new_level.push_back(compute_hash(base.str()));
		}

		txs = new_level;
	}
	return txs[0];

}