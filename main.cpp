#include "blockchain.h"

int main() {
	Blockchain blockchain(2);
	blockchain.initiate_transaction("SHAIKALI", "RASHED", 25);
	for (int i = 0; i < 10; i++) {
		blockchain.mine();
	}
	blockchain.show_utxo();
	return 0;
}