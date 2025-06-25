# Simplified Blockchain in C++
![screenshot](https://raw.githubusercontent.com/oldddev/blockchain/refs/heads/master/Screenshot%20(4).png)
Built this mostly to mess around with C++ and get a better grip on how Bitcoin-style blockchains actually work under the hood. It's got a few core features like UTXOs and Proof-of-Work, not the most secure one or anything, I was way more interested in performance and just seeing things work. Yeah, that kinda breaks the whole "trustless secure system" idea but this one's just for learning, not real-world use.

Might turn it into something more complete later on — maybe throw in proper P2P networking for nodes, better hashing optimization, and all that good stuff. But for now, I’m shifting gears to work on performance-heavy backend stuff and game dev (my fav area right now).

## Back for the project

![screenshot](https://raw.githubusercontent.com/oldddev/blockchain/refs/heads/master/Screenshot%20(5).png)
Just download all the source and header files, compile them together, and in your main() function, do something like what's in the screenshot. The Blockchain class takes a difficulty value, higher difficulty = slower mining, but more secure (just like in real chains).
Also yeah, I wrapped blockchain.mine() inside a loop on purpose, so it just keeps mining blocks until you shut it down. That’s all.
