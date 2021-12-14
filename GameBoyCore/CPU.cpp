#include "CPU.h"




CPU::CPU()  
	: m_registers()
	, m_instructions
{
	  { "NOP", 1, 1, &InstructionFunctions::NOP }
	, { "LD BC nn", 3, 3, &InstructionFunctions::LD_BC_nn }
	, { "LD (BC) A", 1, 2, &InstructionFunctions::LD_mBC_A }
	, { "INC BC", 1, 2, &InstructionFunctions::INC_BC }
	, { "INC B", 1, 1, &InstructionFunctions::INC_B }
	, { "DEC B", 1, 1, &InstructionFunctions::DEC_B }
	, { "LD B n", 2, 2, &InstructionFunctions::LD_B_n }
	, { "RLCA", 1, 1, &InstructionFunctions::RLCA }
	, { "LD (nn) SP", 3, 5, &InstructionFunctions::LD_mnn_SP }
	, { "ADD HL BC", 1, 2, &InstructionFunctions::ADD_HL_BC }
	, { "LD A (BC)", 1, 2, &InstructionFunctions::LD_A_mBC }
	, { "DEC BC", 1, 2, &InstructionFunctions::DEC_BC }
	, { "INC C", 1, 1, &InstructionFunctions::INC_C }
	, { "DEC C", 1, 1, &InstructionFunctions::DEC_C }
	, { "LD C n", 2, 2, &InstructionFunctions::LD_C_n }
	, { "RRCA", 1, 1, &InstructionFunctions::RRCA }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "LD DE nn", 3, 3, &InstructionFunctions::LD_DE_nn }
	, { "LD (DE) A", 1, 2, &InstructionFunctions::LD_mDE_A }
	, { "INC DE", 1, 2, &InstructionFunctions::INC_DE }
	, { "INC D", 1, 1, &InstructionFunctions::INC_D }
	, { "DEC D", 1, 1, &InstructionFunctions::DEC_D }
	, { "LD D n", 2, 2, &InstructionFunctions::LD_D_n }
	, { "RLA", 1, 1, &InstructionFunctions::RLA }
	, { "JR n", 2, 2, &InstructionFunctions::JR_n }
	, { "ADD HL DE", 1, 2, &InstructionFunctions::ADD_HL_DE }
	, { "LD A (DE)", 1, 2, &InstructionFunctions::LD_A_mDE }
	, { "DEC DE", 1, 2, &InstructionFunctions::DEC_DE }
	, { "INC E", 1, 1, &InstructionFunctions::INC_E }
	, { "DEC E", 1, 1, &InstructionFunctions::DEC_E }
	, { "LD E n", 2, 2, &InstructionFunctions::LD_E_n }
	, { "RRA", 1, 1, &InstructionFunctions::RRA }
	, { "JR NZ n", 2, 2, &InstructionFunctions::JR_NZ_n }
	, { "LD HL nn", 3, 3, &InstructionFunctions::LD_HL_nn }
	, { "LD (HL+) A", 1, 2, &InstructionFunctions::LD_mHLinc_A }
	, { "INC HL", 1, 1, &InstructionFunctions::INC_HL }
	, { "INC H", 1, 1, &InstructionFunctions::INC_H }
	, { "DEC H", 1, 1, &InstructionFunctions::DEC_H }
	, { "LD H n", 2, 2, &InstructionFunctions::LD_H_n }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "JR Z n", 2, 2, &InstructionFunctions::JR_Z_n }
	, { "ADD HL HL", 1, 2, &InstructionFunctions::ADD_HL_HL }
	, { "LD A (HL+)", 1, 2, &InstructionFunctions::LD_A_mHLinc }
	, { "DEC HL", 1, 2, &InstructionFunctions::DEC_HL }
	, { "INC L", 1, 1, &InstructionFunctions::INC_L }
	, { "DEC L", 1, 1, &InstructionFunctions::DEC_L }
	, { "LD L n", 2, 2, &InstructionFunctions::LD_L_n }
	, { "CPL", 1, 1, &InstructionFunctions::CPL }
	, { "JR NC n", 2, 2, &InstructionFunctions::JR_NC_n }
	, { "LD SP nn", 3, 3, &InstructionFunctions::LD_SP_nn }
	, { "LD (HL-) A", 1, 2, &InstructionFunctions::LD_mHLdec_A }
	, { "INC SP", 1, 2, &InstructionFunctions::INC_SP }
	, { "INC (HL)", 1, 3, &InstructionFunctions::INC_mHL }
	, { "DEC (HL)", 1, 3, &InstructionFunctions::DEC_mHL }
	, { "LD (HL) n", 2, 3, &InstructionFunctions::LD_mHL_n }
	, { "SCF", 1, 1, &InstructionFunctions::SCF }
	, { "JR C n", 2, 2, &InstructionFunctions::JR_C_n }
	, { "ADD HL SP", 1, 2, &InstructionFunctions::ADD_HL_SP }
	, { "LD A (HL-)", 1, 2, &InstructionFunctions::LD_A_mHLdec }
	, { "DEC SP", 1, 2, &InstructionFunctions::DEC_SP }
	, { "INC A", 1, 1, &InstructionFunctions::INC_A }
	, { "DEC_A", 1, 1, &InstructionFunctions::DEC_A }
	, { "LD A n", 2, 2, &InstructionFunctions::LD_A_n }
	, { "CCF", 1, 1, &InstructionFunctions::CCF }
	, { "LD B B", 1, 1, &InstructionFunctions::LD_B_B }
	, { "LD B C", 1, 1, &InstructionFunctions::LD_B_C }
	, { "LD B D", 1, 1, &InstructionFunctions::LD_B_D }
	, { "LD B E", 1, 1, &InstructionFunctions::LD_B_E }
	, { "LD B H", 1, 1, &InstructionFunctions::LD_B_H }
	, { "LD B L", 1, 1, &InstructionFunctions::LD_B_L }
	, { "LD B (HL)", 1, 1, &InstructionFunctions::LD_B_mHL }
	, { "LD B A", 1, 1, &InstructionFunctions::LD_B_A }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
	, { "TEST", 1, 1, &InstructionFunctions::UNIMPLEMENTED }
}
{
}