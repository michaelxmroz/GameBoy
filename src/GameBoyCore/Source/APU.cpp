#include "Helpers.h"
#include "APU.h"
#include "Logging.h"
#include "AudioChannel.h"

#define APU_REGISTERS_BEGIN 0xFF10
#define APU_REGISTERS_END 0xFF2F

#define CHANNEL1_MASTER_CONTROL_ON_OFF_BIT 0x01
#define CHANNEL1_SWEEP_REGISTER 0xFF10
#define CHANNEL1_LENGTH_DUTY_REGISTER 0xFF11
#define CHANNEL1_ENVELOPE_REGISTER 0xFF12
#define CHANNEL1_FREQUENCY_LOW_REGISTER 0xFF13
#define CHANNEL1_CONTROL_FREQ_HIGH_REGISTER 0xFF14

#define CHANNEL2_MASTER_CONTROL_ON_OFF_BIT 0x02
#define CHANNEL2_UNUSED_REGISTER 0xFF15
#define CHANNEL2_LENGTH_DUTY_REGISTER 0xFF16
#define CHANNEL2_ENVELOPE_REGISTER 0xFF17
#define CHANNEL2_FREQUENCY_LOW_REGISTER 0xFF18
#define CHANNEL2_CONTROL_FREQ_HIGH_REGISTER 0xFF19

#define CHANNEL3_MASTER_CONTROL_ON_OFF_BIT 0x04
#define CHANNEL3_ON_OFF_REGISTER 0xFF1A
#define CHANNEL3_LENGTH_REGISTER 0xFF1B
#define CHANNEL3_VOLUME_REGISTER 0xFF1C
#define CHANNEL3_FREQUENCY_LOW_REGISTER 0xFF1D
#define CHANNEL3_CONTROL_FREQ_HIGH_REGISTER 0xFF1E

#define CHANNEL4_MASTER_CONTROL_ON_OFF_BIT 0x08
#define CHANNEL4_UNUSED_REGISTER 0xFF1F
#define CHANNEL4_LENGTH_REGISTER 0xFF20
#define CHANNEL4_ENVELOPE_REGISTER 0xFF21
#define CHANNEL4_FREQUENCY_CLOCK_REGISTER 0xFF22
#define CHANNEL4_CONTROL_REGISTER 0xFF23

#define MASTER_VOLUME_REGISTER 0xFF24
#define SOUND_PANNING_REGISTER 0xFF25
#define AUDIO_MASTER_CONTROL_REGISTER 0xFF26

#define DIVIDER_REGISTER 0xFF04

#define MASTER_VOLUME_RIGHT_BITS 0x07
#define MASTER_VOLUME_LEFT_BITS 0x70
#define MASTER_VOLUME_LEFT_SHIFT 4
#define MASTER_VOLUME_MAX 8

#define APU_ON_OFF_BIT 0x80

#define FRAME_SEQUENCER_NO_TICK 9

using namespace AudioProcessors;

typedef AudioChannel<Sweep, PulseFrequency, Length, Envelope, PulseAmplitude> Channel1;
typedef AudioChannel<NoSweep, PulseFrequency, Length, Envelope, PulseAmplitude> Channel2;
typedef AudioChannel<NoSweep, WaveFrequency, Length, NoEnvelope, WaveAmplitude> Channel3;
typedef AudioChannel<NoSweep, NoiseFrequency, Length, Envelope, NoiseAmplitude> Channel4;

namespace APU_Internal
{

	void SetupRegisterBitsOverrides(Memory& memory)
	{
		memory.AddIOUnusedBitsOverride(CHANNEL1_SWEEP_REGISTER, 0b10000000);
		memory.AddIOUnusedBitsOverride(CHANNEL1_CONTROL_FREQ_HIGH_REGISTER, 0b00111000);

		memory.AddIOUnusedBitsOverride(CHANNEL2_UNUSED_REGISTER, 0b11111111);
		memory.AddIOUnusedBitsOverride(CHANNEL2_CONTROL_FREQ_HIGH_REGISTER, 0b00111000);

		memory.AddIOUnusedBitsOverride(CHANNEL3_ON_OFF_REGISTER, 0b01111111);
		memory.AddIOUnusedBitsOverride(CHANNEL3_VOLUME_REGISTER, 0b10011111);
		memory.AddIOUnusedBitsOverride(CHANNEL3_CONTROL_FREQ_HIGH_REGISTER, 0b00111000);

		memory.AddIOUnusedBitsOverride(CHANNEL4_UNUSED_REGISTER, 0b11111111);
		memory.AddIOUnusedBitsOverride(CHANNEL4_LENGTH_REGISTER, 0b11000000);
		memory.AddIOUnusedBitsOverride(CHANNEL4_CONTROL_REGISTER, 0b00111111);

		memory.AddIOUnusedBitsOverride(AUDIO_MASTER_CONTROL_REGISTER, 0b01110000);
		//Unused IO registers
		memory.AddIOUnusedBitsOverride(0xFF27, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF28, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF29, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2A, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2B, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2C, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2D, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2E, 0b11111111);
		memory.AddIOUnusedBitsOverride(0xFF2F, 0b11111111);


		memory.AddIOWriteOnlyBitsOverride(CHANNEL1_LENGTH_DUTY_REGISTER, 0b00111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL1_FREQUENCY_LOW_REGISTER, 0b11111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL1_CONTROL_FREQ_HIGH_REGISTER, 0b10000111);

		memory.AddIOWriteOnlyBitsOverride(CHANNEL2_LENGTH_DUTY_REGISTER, 0b00111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL2_FREQUENCY_LOW_REGISTER, 0b11111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL2_CONTROL_FREQ_HIGH_REGISTER, 0b10000111);

		memory.AddIOWriteOnlyBitsOverride(CHANNEL3_LENGTH_REGISTER, 0b11111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL3_FREQUENCY_LOW_REGISTER, 0b11111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL3_CONTROL_FREQ_HIGH_REGISTER, 0b10000111);

		memory.AddIOWriteOnlyBitsOverride(CHANNEL4_LENGTH_REGISTER, 0b00111111);
		memory.AddIOWriteOnlyBitsOverride(CHANNEL4_CONTROL_REGISTER, 0b10000000);


		memory.AddIOReadOnlyBitsOverride(AUDIO_MASTER_CONTROL_REGISTER, 0b00001111);

		//TODO wave ram read/write blocking while channel is playing
	}

	void ResetAudioRegistersToBootValues(Memory& memory)
	{
		memory.WriteIO(AUDIO_MASTER_CONTROL_REGISTER, 0xF1);
		memory.WriteIO(MASTER_VOLUME_REGISTER, 0x77);
		memory.WriteIO(SOUND_PANNING_REGISTER, 0xF3);

		memory.WriteIO(CHANNEL1_SWEEP_REGISTER, 0x80);
		memory.WriteIO(CHANNEL1_LENGTH_DUTY_REGISTER, 0xBF);
		memory.WriteIO(CHANNEL1_ENVELOPE_REGISTER, 0xF3);
		memory.WriteIO(CHANNEL1_FREQUENCY_LOW_REGISTER, 0xFF);
		memory.WriteIO(CHANNEL1_CONTROL_FREQ_HIGH_REGISTER, 0xBF);

		memory.WriteIO(CHANNEL2_LENGTH_DUTY_REGISTER, 0x3F);
		memory.WriteIO(CHANNEL2_ENVELOPE_REGISTER, 0x00);
		memory.WriteIO(CHANNEL2_FREQUENCY_LOW_REGISTER, 0xFF);
		memory.WriteIO(CHANNEL2_CONTROL_FREQ_HIGH_REGISTER, 0xBF);

		memory.WriteIO(CHANNEL3_ON_OFF_REGISTER, 0x7F);
		memory.WriteIO(CHANNEL3_LENGTH_REGISTER, 0xFF);
		memory.WriteIO(CHANNEL3_VOLUME_REGISTER, 0x9F);
		memory.WriteIO(CHANNEL3_FREQUENCY_LOW_REGISTER, 0xFF);
		memory.WriteIO(CHANNEL3_CONTROL_FREQ_HIGH_REGISTER, 0xBF);

		memory.WriteIO(CHANNEL4_LENGTH_REGISTER, 0xFF);
		memory.WriteIO(CHANNEL4_ENVELOPE_REGISTER, 0x00);
		memory.WriteIO(CHANNEL4_FREQUENCY_CLOCK_REGISTER, 0x00);
		memory.WriteIO(CHANNEL4_CONTROL_REGISTER, 0xBF);
	}

	void UpdateMasterVolume(Memory& memory, Sample& sample)
	{
		uint8_t rawMasterVolume = memory.ReadIO(MASTER_VOLUME_REGISTER);
		uint8_t volRight = rawMasterVolume & MASTER_VOLUME_RIGHT_BITS;
		uint8_t volLeft = (rawMasterVolume & MASTER_VOLUME_LEFT_BITS) >> MASTER_VOLUME_LEFT_SHIFT;
		volRight += 1;
		volLeft += 1;
		float finalVolRight = static_cast<float>(volRight) / MASTER_VOLUME_MAX;
		float finalVolLeft = static_cast<float>(volLeft) / MASTER_VOLUME_MAX;

		sample.m_left *= finalVolLeft;
		sample.m_right *= finalVolRight;
	}
}

APU::APU(Serializer* serializer) : ISerializable(serializer)
	, m_channels{
		ChannelData(0, 64, 4, 7, 0x3F, CHANNEL1_MASTER_CONTROL_ON_OFF_BIT, CHANNEL1_CONTROL_FREQ_HIGH_REGISTER, CHANNEL1_LENGTH_DUTY_REGISTER, CHANNEL1_ENVELOPE_REGISTER,CHANNEL1_FREQUENCY_LOW_REGISTER, CHANNEL1_SWEEP_REGISTER),
		ChannelData(1, 64, 4, 7, 0x3F, CHANNEL2_MASTER_CONTROL_ON_OFF_BIT, CHANNEL2_CONTROL_FREQ_HIGH_REGISTER, CHANNEL2_LENGTH_DUTY_REGISTER, CHANNEL2_ENVELOPE_REGISTER, CHANNEL2_FREQUENCY_LOW_REGISTER, 0x0),
		ChannelData(2, 256, 2, 31, 0xFF, CHANNEL3_MASTER_CONTROL_ON_OFF_BIT, CHANNEL3_CONTROL_FREQ_HIGH_REGISTER, CHANNEL3_LENGTH_REGISTER, CHANNEL3_VOLUME_REGISTER, CHANNEL3_FREQUENCY_LOW_REGISTER, CHANNEL3_ON_OFF_REGISTER),
		ChannelData(3, 64, 4, 7, 0x3F, CHANNEL4_MASTER_CONTROL_ON_OFF_BIT, CHANNEL4_CONTROL_REGISTER, CHANNEL4_LENGTH_REGISTER, CHANNEL4_ENVELOPE_REGISTER, CHANNEL4_FREQUENCY_CLOCK_REGISTER, 0x0)
	}
	, m_previousFrameSequencerStep(FRAME_SEQUENCER_NO_TICK)
{
	m_externalAudioBuffer.buffer = nullptr;
	m_externalAudioBuffer.size = 0;
	m_externalAudioBuffer.sampleRate = 0;
	m_externalAudioBuffer.currentPosition = 0;
	m_externalAudioBuffer.resampleRate = 0.0f;
	m_externalAudioBuffer.samplesToGenerate = 0.0f;

}

void APU::Init(Memory& memory)
{
	APU_Internal::SetupRegisterBitsOverrides(memory);

	memory.RegisterCallback(AUDIO_MASTER_CONTROL_REGISTER, CheckForReset, this);
	memory.RegisterCallback(CHANNEL1_LENGTH_DUTY_REGISTER, AdjustTimer, this);
	memory.RegisterCallback(CHANNEL2_LENGTH_DUTY_REGISTER, AdjustTimer, this);
	memory.RegisterCallback(CHANNEL3_LENGTH_REGISTER, AdjustTimer, this);
	memory.RegisterCallback(CHANNEL4_LENGTH_REGISTER, AdjustTimer, this);

	memory.RegisterCallback(CHANNEL1_ENVELOPE_REGISTER, SetChannelsDACActive, this);
	memory.RegisterCallback(CHANNEL2_ENVELOPE_REGISTER, SetChannelsDACActive, this);
	memory.RegisterCallback(CHANNEL4_ENVELOPE_REGISTER, SetChannelsDACActive, this);

	APU_Internal::ResetAudioRegistersToBootValues(memory);

	memory.RegisterCallback(CHANNEL1_CONTROL_FREQ_HIGH_REGISTER, IsChannelTriggered, this);
	memory.RegisterCallback(CHANNEL2_CONTROL_FREQ_HIGH_REGISTER, IsChannelTriggered, this);
	memory.RegisterCallback(CHANNEL3_CONTROL_FREQ_HIGH_REGISTER, IsChannelTriggered, this);
	memory.RegisterCallback(CHANNEL4_CONTROL_REGISTER, IsChannelTriggered, this);

	memory.RegisterCallback(CHANNEL3_ON_OFF_REGISTER, SetChannel3DACActive, this);


	m_previousFrameSequencerStep = FRAME_SEQUENCER_NO_TICK;
	m_accumulatedCycles = 0;
}

void APU::SetExternalAudioBuffer(float* buffer, uint32_t size, uint32_t sampleRate, uint32_t* startOffset)
{
	m_externalAudioBuffer.buffer = buffer;
	m_externalAudioBuffer.size = size;
	m_externalAudioBuffer.sampleRate = sampleRate;
	m_externalAudioBuffer.currentPosition = startOffset;

	m_HPFLeft.SetParams(1000.0f, static_cast<float>(sampleRate));
	m_HPFRight.SetParams(1000.0f, static_cast<float>(sampleRate));

	m_externalAudioBuffer.resampleRate = static_cast<double>(m_externalAudioBuffer.sampleRate) / CPU_FREQUENCY;
}

uint32_t APU::Update(Memory& memory, uint32_t cyclesPassed, float turboSpeed)
{
	uint32_t cyclesToStep = cyclesPassed * MCYCLES_TO_CYCLES;

	m_externalAudioBuffer.samplesToGenerate += (static_cast<double>(cyclesToStep) * m_externalAudioBuffer.resampleRate) * (1.0 / static_cast<double>(turboSpeed));
	
	m_accumulatedCycles += cyclesToStep;
	
	uint32_t samplesgenerated = static_cast<uint32_t>(m_externalAudioBuffer.samplesToGenerate);

	if (m_externalAudioBuffer.samplesToGenerate < 1.0f)
	{
		return samplesgenerated;
	}

	Sample sample;
	if ((memory.ReadIO(AUDIO_MASTER_CONTROL_REGISTER) & APU_ON_OFF_BIT) == 0)
	{
		m_accumulatedCycles = 0;
		GenerateSamples(m_externalAudioBuffer, sample, m_HPFLeft, m_HPFRight);
		return samplesgenerated;
	}

	uint8_t frameSequencerStep = (memory.ReadIO(DIVIDER_REGISTER) / 32) % 8;
	uint32_t frameSequencerStepTmp = frameSequencerStep;
	frameSequencerStep = frameSequencerStep != m_previousFrameSequencerStep ? frameSequencerStep : FRAME_SEQUENCER_NO_TICK;
	m_previousFrameSequencerStep = frameSequencerStepTmp;
	
	Channel1::Synthesize(m_channels[0], memory, m_accumulatedCycles, frameSequencerStep, sample);
	Channel2::Synthesize(m_channels[1], memory, m_accumulatedCycles, frameSequencerStep, sample);
	Channel3::Synthesize(m_channels[2], memory, m_accumulatedCycles, frameSequencerStep, sample);
	Channel4::Synthesize(m_channels[3], memory, m_accumulatedCycles, frameSequencerStep, sample);

	m_accumulatedCycles = 0;

	//TODO is this necessary when we have a HPF?
	if (sample.m_activeChannels != 0)
	{
		sample.m_left /= sample.m_activeChannels;
		sample.m_right /= sample.m_activeChannels;
	}
	
	APU_Internal::UpdateMasterVolume(memory, sample);

	GenerateSamples(m_externalAudioBuffer, sample, m_HPFLeft, m_HPFRight);

	return samplesgenerated;
}

void APU::GenerateSamples(ExternalAudioBuffer& externalAudioBuffer, const Sample& sample, HighPassFilter& hpfLeft, HighPassFilter& hpfRight)
{
	while (externalAudioBuffer.samplesToGenerate >= 1.0f)
	{
		float processedLeft = hpfLeft.ProcessSample(sample.m_left);
		float processedRight = hpfRight.ProcessSample(sample.m_right);
		WriteToAudioBuffer(&externalAudioBuffer, processedLeft, processedRight);

		if (*externalAudioBuffer.currentPosition >= externalAudioBuffer.size)
		{
			*externalAudioBuffer.currentPosition = 0;
		}

		externalAudioBuffer.samplesToGenerate--;
	}
}

void APU::WriteToAudioBuffer(ExternalAudioBuffer* buffer, float leftSample, float rightSample)
{
	float* left = buffer->buffer + (*buffer->currentPosition)++;
	float* right = buffer->buffer + (*buffer->currentPosition)++;
	*left = leftSample;
	*right = rightSample;
}

void APU::CheckForReset(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData)
{
	if ((prevValue & APU_ON_OFF_BIT) != 0 && (newValue & APU_ON_OFF_BIT) == 0)
	{
		APU* apu = static_cast<APU*>(userData);

		for (uint32_t i = 0; i < 4; ++i)
		{
			AudioProcessors::SetChannelActive(*memory, apu->m_channels[i], false);
		}
		memory->ClearRange(APU_REGISTERS_BEGIN, APU_REGISTERS_END);
		memory->AddIOReadOnlyRange(APU_REGISTERS_BEGIN, APU_REGISTERS_END);
		memory->AddIOReadOnlyBitsOverride(AUDIO_MASTER_CONTROL_REGISTER, 0b00001111);
	}
	else if ((prevValue & APU_ON_OFF_BIT) == 0 && (newValue & APU_ON_OFF_BIT) != 0)
	{
		memory->RemoveIOReadOnlyRange(APU_REGISTERS_BEGIN, APU_REGISTERS_END);
		memory->AddIOReadOnlyBitsOverride(AUDIO_MASTER_CONTROL_REGISTER, 0b00001111);
	}
}

void APU::AdjustTimer(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData)
{
	APU* apu = static_cast<APU*>(userData);

	for (uint32_t i = 0; i < CHANNEL_COUNT; ++i)
	{
		ChannelData& channel = apu->m_channels[i];
		if (channel.m_timerRegister == addr)
		{
			channel.m_lengthCounter = channel.m_initialLength - (newValue & channel.m_lengthTimerBits);
		}
	}
}

void APU::SetChannelsDACActive(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData)
{
	const uint8_t DAC_ENABLED_BITS = 0xF8;
	APU* apu = static_cast<APU*>(userData);

	for (uint32_t i = 0; i < CHANNEL_COUNT; ++i)
	{
		ChannelData& channel = apu->m_channels[i];
		if (channel.m_volumeEnvelopeRegister != addr)
		{
			continue;
		}

		channel.m_DACEnabled = (newValue & DAC_ENABLED_BITS) != 0;
		if (!channel.m_DACEnabled)
		{
			SetChannelActive(*memory, channel, false);
		}
		break;
	}
}

void APU::SetChannel3DACActive(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData)
{
	APU* apu = static_cast<APU*>(userData);
	ChannelData& channel = apu->m_channels[2];
	channel.m_DACEnabled = newValue != 0;
	if (!channel.m_DACEnabled)
	{
		SetChannelActive(*memory, channel, false);
	}
}

void APU::IsChannelTriggered(Memory* memory, uint16_t addr, uint8_t prevValue, uint8_t newValue, void* userData)
{
	const uint8_t CONTROL_REGISTER_TRIGGER_BIT = 0x80;
	APU* apu = static_cast<APU*>(userData);

	for (uint32_t i = 0; i < CHANNEL_COUNT; ++i)
	{
		ChannelData& channel = apu->m_channels[i];
		if (channel.m_controlRegister != addr)
		{
			continue;
		}

		channel.m_triggered |= (newValue & CONTROL_REGISTER_TRIGGER_BIT) != 0;
		break;
	}
}

void APU::Serialize(std::vector<Chunk>& chunks, std::vector<uint8_t>& data)
{
	uint32_t dataSize = sizeof(ChannelData) * 4 + sizeof(HighPassFilter) * 2 + sizeof(uint32_t);
	uint8_t* rawData = CreateChunkAndGetDataPtr(chunks, data, dataSize, ChunkId::APU);

	for (uint32_t i = 0; i < CHANNEL_COUNT; ++i)
	{
		WriteAndMove(rawData, m_channels + i, sizeof(ChannelData));
	}

	WriteAndMove(rawData, &m_HPFLeft, sizeof(HighPassFilter));
	WriteAndMove(rawData, &m_HPFRight, sizeof(HighPassFilter));
	WriteAndMove(rawData, &m_previousFrameSequencerStep, sizeof(uint32_t));
	WriteAndMove(rawData, &m_accumulatedCycles, sizeof(uint32_t));
}

void APU::Deserialize(const Chunk* chunks, const uint32_t& chunkCount, const uint8_t* data, const uint32_t& dataSize)
{
	const Chunk* myChunk = FindChunk(chunks, chunkCount, ChunkId::APU);
	if (myChunk == nullptr)
	{
		return;
	}

	data += myChunk->m_offset;

	for (uint32_t i = 0; i < CHANNEL_COUNT; ++i)
	{
		ReadAndMove(data, m_channels + i, sizeof(ChannelData));
	}

	ReadAndMove(data, &m_HPFLeft, sizeof(HighPassFilter));
	ReadAndMove(data, &m_HPFRight, sizeof(HighPassFilter));
	ReadAndMove(data, &m_previousFrameSequencerStep, sizeof(uint32_t));
	ReadAndMove(data, &m_accumulatedCycles, sizeof(uint32_t));
}

APU::HighPassFilter::HighPassFilter() :
	m_alpha(0.0f)
	, m_prevOutput(0.0f)
	, m_prevInput(0.0f)
{
}

void APU::HighPassFilter::SetParams(float cutoff, float sampleRate)
{
	m_alpha = 1.0f / (1.0f + 2.0f * M_PI * cutoff / sampleRate);
}

float APU::HighPassFilter::ProcessSample(float inputSample)
{
	float output = m_alpha * (m_prevOutput + inputSample - m_prevInput);

	m_prevInput = inputSample;
	m_prevOutput = output;
	return output;
}
