#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <cstdint>

void parsePartitionTable(const std::vector<uint8_t>& mbrData);

#endif // PARSING_H
