#pragma once

#include <string>
#include <vector>
#include "picosha2.h"

std::string compute_hash(const std::string& input);
std::string compute_merkle_root(const std::vector<std::string>& inputs);