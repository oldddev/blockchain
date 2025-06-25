#include "transaction.h"

Transaction::Transaction(std::vector<TX_IN> inputs, std::vector<TX_OUT> outputs) : inputs(inputs), outputs(outputs) {

    auto now = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

    std::stringstream ss;

    for (const auto& in : inputs) ss << in.input.first << in.input.second;
    for (const auto& out : outputs) ss << out.output.first << out.output.second << time;

    transaction_id = compute_hash(compute_hash(ss.str()));

}

std::string Transaction::get_transaction_id() const {
    return transaction_id;
}

std::vector<TX_IN> Transaction::get_inputs() const {
    return inputs;
}

std::vector<TX_OUT> Transaction::get_outputs() const {
    return outputs;
}