#pragma once
#include "../Include/Emulator.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Clock.h"
#include "PPU.h"
#include "Joypad.h"
#include "Serial.h"
#include "APU.h"

class VirtualMachine : public Emulator
{
public:
	VirtualMachine();
	virtual ~VirtualMachine() override;

	virtual void Load(const char* romName, const char* rom, uint32_t size) override;
	virtual void Load(const char* romName, const char* rom, uint32_t size, const char* bootrom, uint32_t bootromSize) override;

	virtual void LoadPersistentMemory(const char* ram, uint32_t size) override;
	virtual void SetPersistentMemoryCallback(PersistentMemoryCallback callback) override;

	void SetAudioBuffer(float* buffer, uint32_t size, uint32_t sampleRate, uint32_t* startOffset) override;

	virtual void Step(EmulatorInputs::InputState, double deltaMs) override;
	virtual const void* GetFrameBuffer() override;
	uint32_t GetNumberOfGeneratedSamples() override;

	virtual void SetLoggerCallback(LoggerCallback callback) override;

	virtual std::vector<uint8_t> Serialize() const override;
	virtual void Deserialize(const uint8_t* buffer, const uint32_t size) override;

#if _DEBUG
	void StopOnInstruction(uint8_t instr);
	bool HasReachedInstruction();
	Registers& GetRegisters();
#endif
private:
	Serializer m_serializer;
	Memory m_memory;
	CPU m_cpu;
	Clock m_clock;
	PPU m_ppu;
	APU m_apu;
	Joypad m_joypad;
	Serial m_serial;

	std::string m_romName;
	uint64_t m_totalCycles;
	uint32_t m_samplesGenerated;
	bool m_frameRendered;
	double m_stepDuration;

};

