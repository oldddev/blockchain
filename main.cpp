#include "blockchain.h"

int main() {
	Blockchain blockchain(1);
	while (true) {
		blockchain.mine();
	}
	return 0;
}