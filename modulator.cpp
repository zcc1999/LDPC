#include "LDPC_encoder.h"
#include "modulator.h"

/**************************************************
 *function:BPSKMODULATOR::BPSKMODULATOR(void)
 *brief:���캯������ʼ���źŵ��볤
 *input:
 *output:
 *author: zhangcc
**************************************************/
BPSKMODULATOR::BPSKMODULATOR()
{
	tranSignal.resize(VARIABLE_BITS);
}
BPSKMODULATOR::~BPSKMODULATOR()
{
}
/**************************************************
 *function: BPSKMODULATOR::modulator(vector<int> code)
 *brief :����bpsk����,2����1��Ӧ-1,��Ӧ1��
 *input: ������code
 *output:
 *author: zhangcc
**************************************************/
void BPSKMODULATOR::modulator(vector<int> code)
{
	for (int i = 0;i < tranSignal.size();i++)
	{
		tranSignal[i] = code[i] == 1 ? -1.0f : 1.0f;
	}
	//for (int i = 0;i < tranSignal.size();i++)
	//	std::cout << tranSignal[i] << " ";
	//std::cout << std::endl;
}