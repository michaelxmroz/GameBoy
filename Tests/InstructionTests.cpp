#include "pch.h"
#include "CPU.h"

uint16_t u16(uint8_t lsb, uint8_t msb)
{
	return static_cast<uint16_t>(msb) << 8 | static_cast<uint16_t>(lsb);
}

TEST(Loads8Bit, Instructions)
{
	CPU cpu;
	//LD A to memory
	{
		uint8_t command[2] = { 0x02, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x5;
		cpu.GetRegisters().BC = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x5);
	}
	{
		uint8_t command[2] = { 0x12, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x5;
		cpu.GetRegisters().DE = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x5);
	}
	{
		uint8_t command[2] = { 0x22, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x5;
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x5);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x2);
	}
	{
		uint8_t command[2] = { 0x32, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x5;
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x5);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x0);
	}
	//LD immediate to register
	{
		uint8_t command[2] = { 0x06, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x5);
	}
	{
		uint8_t command[2] = { 0x16, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x5);
	}
	{
		uint8_t command[2] = { 0x26, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x5);
	}
	{
		uint8_t command[3] = { 0x36, 0x05, 0x0 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x2;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0x05);
	}
	{
		uint8_t command[2] = { 0x0E, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x5);
	}
	{
		uint8_t command[2] = { 0x1E, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x5);
	}
	{
		uint8_t command[2] = { 0x2E, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x5);
	}
	{
		uint8_t command[2] = { 0x3E, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x5);
	}
	//LD memory to A
	{
		uint8_t command[2] = { 0x0A, 0x17 };
		cpu.Reset();
		cpu.GetRegisters().BC = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x17);
	}
	{
		uint8_t command[2] = { 0x1A, 0x17 };
		cpu.Reset();
		cpu.GetRegisters().DE = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x17);
	}
	{
		uint8_t command[2] = { 0x2A, 0x17 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x17);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x2);
	}
	{
		uint8_t command[2] = { 0x3A, 0x17 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x17);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x0);
	}
	//LD reg to reg, reg to memory, memory to reg
	{
		uint8_t command[8] = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().B;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x41);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().C;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x49);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57 };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().D;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x51);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().E;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x59);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67 };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().H;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x61);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().L;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x69);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x77, 0x0 };
		cpu.Reset();

		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x7;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = command[7];

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x7);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x6);
	}
	{
		uint8_t command[8] = { 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F };
		cpu.Reset();

		cpu.GetRegisters().B = 0x0;
		cpu.GetRegisters().C = 0x1;
		cpu.GetRegisters().D = 0x2;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x4;
		cpu.GetRegisters().L = 0x5;
		cpu.GetRegisters().A = 0x6;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x5);

		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x79);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x79);
	}
	//LDH
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xE0;
		command[1] = 0x0;
		cpu.Reset();
		cpu.GetRegisters().A = 0x15;
		cpu.Step(command);
		EXPECT_EQ(command[0xFF00], 0x15);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xF0;
		command[1] = 0x1;
		command[0xFF01] = 0x15;
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x15);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xE2;
		cpu.Reset();
		cpu.GetRegisters().A = 0x15;
		cpu.GetRegisters().C = 0x01;
		cpu.Step(command);
		EXPECT_EQ(command[0xFF01], 0x15);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xF2;
		command[0xFF01] = 0x15;
		cpu.Reset();
		cpu.GetRegisters().C = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x15);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xF2;
		command[0xFF01] = 0x15;
		cpu.Reset();
		cpu.GetRegisters().C = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x15);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xEA;
		command[1] = 0xF1;
		command[2] = 0x01;
		cpu.Reset();
		cpu.GetRegisters().A = 0x05;
		cpu.Step(command);
		EXPECT_EQ(command[0x01F1], 0x05);
		delete[] command;
	}
	{
		uint8_t* command = new uint8_t[0xFFFF];
		command[0] = 0xFA;
		command[1] = 0xF1;
		command[2] = 0x01;
		command[0x01F1] = 0x05;
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x05);
		delete[] command;
	}
}

TEST(Loads16Bit, Instructions) 
{
	CPU cpu;
	//LD
	{
		uint8_t command[3] = { 0x01, 0x05 , 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().BC, 0x0105);
	}
	{
		uint8_t command[3] = { 0x11, 0x05 , 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().DE, 0x0105);
	}
	{
		uint8_t command[3] = { 0x21, 0x05 , 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x0105);
	}
	{
		uint8_t command[3] = { 0x31, 0x05 , 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x0105);
	}
	{
		uint8_t command[5] = { 0x08, 0x03, 0x00, 0x00, 0x00 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(u16(command[3], command[4]), cpu.GetRegisters().SP);
	}
	{
		uint8_t command[2] = { 0xF8, 0x05};
		cpu.Reset();
		cpu.GetRegisters().SP = 0x01FF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x0204);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0xF9 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x01FF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01FF);
	}
	//PUSH
	{
		uint8_t command[3] = { 0xF5, 0x00 , 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x03;
		cpu.GetRegisters().AF = 0x0203;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x03);
		EXPECT_EQ(command[2], 0x02);
	}
	{
		uint8_t command[3] = { 0xC5, 0x00 , 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x03;
		cpu.GetRegisters().BC = 0x0203;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x03);
		EXPECT_EQ(command[2], 0x02);
	}
	{
		uint8_t command[3] = { 0xD5, 0x00 , 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x03;
		cpu.GetRegisters().DE = 0x0203;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x03);
		EXPECT_EQ(command[2], 0x02);
	}
	{
		uint8_t command[3] = { 0xE5, 0x00 , 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x03;
		cpu.GetRegisters().HL = 0x0203;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x03);
		EXPECT_EQ(command[2], 0x02);
	}
	//POP
	{
		uint8_t command[3] = { 0xF1, 0x03 , 0x02 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().AF, 0x0203);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
	}
	{
		uint8_t command[3] = { 0xC1, 0x03 , 0x02 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().BC, 0x0203);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
	}
	{
		uint8_t command[3] = { 0xD1, 0x03 , 0x02 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().DE, 0x0203);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
	}
	{
		uint8_t command[3] = { 0xE1, 0x03 , 0x02 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x01;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x0203);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
	}
	
}

TEST(Arithmatic16Bit, Instructions)
{
	CPU cpu;
	//INC
	{
		uint8_t command[1] = { 0x03 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().BC, 0x1);
	}
	{
		uint8_t command[1] = { 0x13 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().DE, 0x1);
	}
	{
		uint8_t command[1] = { 0x23 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1);
	}
	{
		uint8_t command[1] = { 0x33 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0xFFFF);
	}
	//ADD
	{
		uint8_t command[1] = { 0x09 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x988;
		cpu.GetRegisters().BC = 0x980;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1308);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x19 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x988;
		cpu.GetRegisters().DE = 0x980;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1308);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x29 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x988;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1310);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x39 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x988;
		cpu.GetRegisters().SP = 0x980;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1308);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[2] = { 0xE8, 0xF };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x00F1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x100);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));

		cpu.Reset();
		cpu.GetRegisters().SP = 0xFFF1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		command[1] = 0xF1;
		cpu.Reset();
		cpu.GetRegisters().SP = 0xF1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0xE2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	//DEC
	{
		uint8_t command[1] = { 0x0B };
		cpu.Reset();
		cpu.GetRegisters().BC = 0x02;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().BC, 0x1);
	}
	{
		uint8_t command[1] = { 0x1B };
		cpu.Reset();
		cpu.GetRegisters().DE = 0x02;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().DE, 0x1);
	}
	{
		uint8_t command[1] = { 0x2B };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().HL, 0x1);
	}
	{
		uint8_t command[1] = { 0x3B };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x02;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x1);
	}
}

TEST(Arithmatic8Bit, Instructions)
{
	CPU cpu;
	//INC
	{
		uint8_t command[1] = { 0x04 };
		cpu.Reset();
		cpu.GetRegisters().B = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x14 };
		cpu.Reset();
		cpu.GetRegisters().D = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x24 };
		cpu.Reset();
		cpu.GetRegisters().H = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[2] = { 0x34, 0xFF };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x0C };
		cpu.Reset();
		cpu.GetRegisters().C = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x1C };
		cpu.Reset();
		cpu.GetRegisters().E = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x2C };
		cpu.Reset();
		cpu.GetRegisters().L = 0xFF;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x3C };
		cpu.Reset();
		cpu.GetRegisters().A = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x02);
	}
	//DEC
	{
		uint8_t command[1] = { 0x05 };
		cpu.Reset();
		cpu.GetRegisters().B = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x15 };
		cpu.Reset();
		cpu.GetRegisters().D = 0x0;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0xFF);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x25 };
		cpu.Reset();
		cpu.GetRegisters().H = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[2] = { 0x35, 0x1 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x1;
		cpu.Step(command);
		EXPECT_EQ(command[1], 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x0D };
		cpu.Reset();
		cpu.GetRegisters().C = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x1D };
		cpu.Reset();
		cpu.GetRegisters().E = 0x0;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0xFF);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x2D };
		cpu.Reset();
		cpu.GetRegisters().L = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	{
		uint8_t command[1] = { 0x3D };
		cpu.Reset();
		cpu.GetRegisters().A = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}
	//CPL
	{
		uint8_t command[1] = { 0x2F };
		cpu.Reset();
		cpu.GetRegisters().A = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0xFC);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	//ADD
	{
		uint8_t command[9] = { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x01 };
		cpu.Reset();
		cpu.GetRegisters().A = 0xFD;
		cpu.GetRegisters().B= 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFE);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x7);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x7);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x10);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x20);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

	}
	//ADC
	{
		uint8_t command[9] = { 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x01 };
		cpu.Reset();
		cpu.GetRegisters().A = 0xFD;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFE);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x4);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x8);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x8);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x10);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x11);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x22);
	}
	//SUB
	{
		uint8_t command[9] = { 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x3;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFD);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF9);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF9);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF1);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xEE);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

	}
	//SBC
	{
		uint8_t command[9] = { 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x3;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x2);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFD);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF8);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF8);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xED);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

	}
	//AND
	{
		uint8_t command[9] = { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xF0 };
		cpu.Reset();
		cpu.GetRegisters().A = 0xFF;
		cpu.GetRegisters().B = 0xF;
		cpu.GetRegisters().C = 0x7;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x1;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x7);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x3);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x1);

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));

		cpu.GetRegisters().A = 0x11;
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x10);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x10);
	}
	//XOR
	{
		uint8_t command[9] = { 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xF0 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x80;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x80;
		cpu.GetRegisters().E = 0x3;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x81);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x83);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x03);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x08);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xF8);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
	}

	//OR
	{
		uint8_t command[9] = { 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0x20 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x80;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x4;
		cpu.GetRegisters().E = 0x10;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x81);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x83);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x87);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x97);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x97);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x9F);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xBF);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0xBF);
	}
	//CP
	{
		uint8_t command[9] = { 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x3;
		cpu.GetRegisters().B = 0x1;
		cpu.GetRegisters().C = 0x2;
		cpu.GetRegisters().D = 0x3;
		cpu.GetRegisters().E = 0x4;
		cpu.GetRegisters().H = 0x0;
		cpu.GetRegisters().L = 0x8;

		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.GetRegisters().A = 0x2;
		cpu.Step(command);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.GetRegisters().A = 0x0;
		cpu.Step(command);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);
		cpu.Step(command);
		EXPECT_EQ(regVal, 0x0);

		cpu.GetRegisters().A = 0xF2;
		cpu.Step(command);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	//IMMEDIATE ADD, SUB, AND, OR, ADC, SBC, XOR, CP
	{
		uint8_t command[16] = { 0xC6, 0x03, 0xD6, 0x02, 0xE6, 0xFF, 0xF6, 0xFF, 0xCE, 0x01, 0xDE, 0x02, 0xEE, 0xFF, 0xFE, 0x02 };
		cpu.Reset();

		cpu.GetRegisters().A = 0xFF;
		uint8_t& regVal = cpu.GetRegisters().A;

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x02);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFF);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x00);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0xFD);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x02);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

		cpu.Step(command);
		EXPECT_EQ(regVal, 0x02);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::zf));
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));

	}
}

TEST(Shift8Bit, Instructions)
{
	CPU cpu;
	{
		uint8_t command[1] = { 0x07 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[1] = { 0x17 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[1] = { 0x0F };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[1] = { 0x1F };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	//CB RLC
	{
		uint8_t command[2] = { 0xCB, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().B = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x01 };
		cpu.Reset();
		cpu.GetRegisters().C = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x02 };
		cpu.Reset();
		cpu.GetRegisters().D = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().E = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x04 };
		cpu.Reset();
		cpu.GetRegisters().H = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x05 };
		cpu.Reset();
		cpu.GetRegisters().L = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[3] = { 0xCB, 0x06, 0x81 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0x03);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x07 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x3);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	//CB RRC
	{
		uint8_t command[2] = { 0xCB, 0x08 };
		cpu.Reset();
		cpu.GetRegisters().B = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x09 };
		cpu.Reset();
		cpu.GetRegisters().C = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x0A };
		cpu.Reset();
		cpu.GetRegisters().D = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x0B };
		cpu.Reset();
		cpu.GetRegisters().E = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x0C };
		cpu.Reset();
		cpu.GetRegisters().H = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x0D };
		cpu.Reset();
		cpu.GetRegisters().L = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[3] = { 0xCB, 0x0E, 0x81 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x0F };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0xC0);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	//CB RL
	{
		uint8_t command[2] = { 0xCB, 0x10 };
		cpu.Reset();
		cpu.GetRegisters().B = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x11 };
		cpu.Reset();
		cpu.GetRegisters().C = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x12 };
		cpu.Reset();
		cpu.GetRegisters().D = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x13 };
		cpu.Reset();

		cpu.GetRegisters().E = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x14 };
		cpu.Reset();

		cpu.GetRegisters().H = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x15 };
		cpu.Reset();

		cpu.GetRegisters().L = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[3] = { 0xCB, 0x16, 0x81 };
		cpu.Reset();

		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x17 };
		cpu.Reset();
		cpu.GetRegisters().A= 0x81;

		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	//CB RR
	{
		uint8_t command[2] = { 0xCB, 0x18 };
		cpu.Reset();

		cpu.GetRegisters().B = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x19 };
		cpu.Reset();

		cpu.GetRegisters().C = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x1A };
		cpu.Reset();

		cpu.GetRegisters().D = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x1B };
		cpu.Reset();

		cpu.GetRegisters().E = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x1C };
		cpu.Reset();

		cpu.GetRegisters().H = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x1D };
		cpu.Reset();

		cpu.GetRegisters().L = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[3] = { 0xCB, 0x1E, 0x81 };
		cpu.Reset();

		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x1F };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;

		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x40);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	/*
	//CB SLA
	{
		uint8_t command[2] = { 0xCB, 0x20 };
		cpu.Reset();
		cpu.GetRegisters().B = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().B, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x21 };
		cpu.Reset();
		cpu.GetRegisters().C = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().C, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x22 };
		cpu.Reset();
		cpu.GetRegisters().D = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().D, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x23 };
		cpu.Reset();
		cpu.GetRegisters().E = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().E, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x24 };
		cpu.Reset();
		cpu.GetRegisters().H = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().H, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x25 };
		cpu.Reset();
		cpu.GetRegisters().L = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().L, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[3] = { 0xCB, 0x26, 0x81 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x02;
		cpu.Step(command);
		EXPECT_EQ(command[2], 0x02);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	{
		uint8_t command[2] = { 0xCB, 0x27 };
		cpu.Reset();
		cpu.GetRegisters().A = 0x81;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().A, 0x2);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
	}
	*/
}

TEST(Control, Instructions)
{
	CPU cpu;
	// Carry set/toggle
	{
		uint8_t command[1] = { 0x37 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_TRUE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	{
		uint8_t command[1] = { 0x3F };
		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::cy));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::n));
		EXPECT_FALSE(cpu.GetRegisters().IsFlagSet(Registers::Flags::h));
	}
	//Jumps
	{
		uint8_t command[2] = { 0x20, 0xFF };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x01);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x02);
	}
	{
		uint8_t command[2] = { 0x30, 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x02);
	}
	{
		uint8_t command[2] = { 0x18, 0x05 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x07);
	}
	{
		uint8_t command[2] = { 0x28, 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x02);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[2] = { 0x38, 0x01 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x02);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[3] = { 0xC2, 0x02, 0x03  };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[3] = { 0xD2, 0x02, 0x03 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[3] = { 0xC3, 0x02, 0x03 };
		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
	}
	{
		uint8_t command[1] = { 0xE9 };
		cpu.Reset();
		cpu.GetRegisters().HL = 0x0302;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
	}
	{
		uint8_t command[3] = { 0xCA, 0x02, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);

		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[3] = { 0xDA, 0x02, 0x03 };
		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);

		cpu.Reset();
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	//CALL
	{
		uint8_t command[5] = { 0xC4, 0x02, 0x03, 0x00, 0x00 };
		cpu.Reset();
		
		cpu.GetRegisters().SP = 0x5;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
		EXPECT_EQ(command[3], 0x03);
		EXPECT_EQ(command[4], 0x00);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[5] = { 0xD4, 0x02, 0x03, 0x00, 0x00 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x5;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
		EXPECT_EQ(command[3], 0x03);
		EXPECT_EQ(command[4], 0x00);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[5] = { 0xCC, 0x02, 0x03, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.GetRegisters().SP = 0x5;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
		EXPECT_EQ(command[3], 0x03);
		EXPECT_EQ(command[4], 0x00);

		cpu.Reset();
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[5] = { 0xDC, 0x02, 0x03, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.GetRegisters().SP = 0x5;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
		EXPECT_EQ(command[3], 0x03);
		EXPECT_EQ(command[4], 0x00);

		cpu.Reset();
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x03);
	}
	{
		uint8_t command[5] = { 0xCD, 0x02, 0x03, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x5;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
		EXPECT_EQ(command[3], 0x03);
		EXPECT_EQ(command[4], 0x00);
	}
	//RST
	{
		uint8_t command[3] = { 0xC7, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x00);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xD7, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x10);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xE7, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x20);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xF7, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x30);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xCF, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x08);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xDF, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x18);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xEF, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x28);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	{
		uint8_t command[3] = { 0xFF, 0x00, 0x00 };
		cpu.Reset();
		cpu.GetRegisters().SP = 0x3;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x38);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x01);
		EXPECT_EQ(command[1], 0x01);
		EXPECT_EQ(command[2], 0x00);
	}
	//RET
	{
		uint8_t command[3] = { 0xC0, 0x02, 0x03 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x01);
	}
	{
		uint8_t command[3] = { 0xD0, 0x02, 0x03 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);

		cpu.Reset();
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x01);
	}
	{
		uint8_t command[3] = { 0xC8, 0x02, 0x03 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x1;
		cpu.GetRegisters().SetFlag(Registers::Flags::zf);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);

		cpu.Reset();
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x01);
	}
	{
		uint8_t command[3] = { 0xD8, 0x02, 0x03 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x1;
		cpu.GetRegisters().SetFlag(Registers::Flags::cy);
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);

		cpu.Reset();
		cpu.Step(command);

		EXPECT_EQ(cpu.GetRegisters().PC, 0x01);
	}
	{
		uint8_t command[3] = { 0xC9, 0x02, 0x03 };
		cpu.Reset();

		cpu.GetRegisters().SP = 0x1;
		cpu.Step(command);
		EXPECT_EQ(cpu.GetRegisters().PC, 0x0302);
		EXPECT_EQ(cpu.GetRegisters().SP, 0x03);
	}
}