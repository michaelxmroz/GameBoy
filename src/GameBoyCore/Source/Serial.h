#pragma once
#include "Memory.h"

//Loopback serial connector
class Serial
{
public:
	Serial();
	void Init(Memory& memory);
	void Update(Memory& memory, uint32_t mCycles);
private:

	static void ResetClock(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData);
	void TransferNextBit(Memory& memory);

	uint32_t m_accumulatedCycles;
	uint32_t m_bitsTransferred;
};

