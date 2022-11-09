#include "LDPC_encoder.h"
#include "modulator.h"

/**************************************************
 *function:BPSKMODULATOR::BPSKMODULATOR(void)
 *brief:构造函数，初始化信号的码长
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
 *brief :进行bpsk调制,2进制1对应-1,对应1。
 *input: 编码后的code
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