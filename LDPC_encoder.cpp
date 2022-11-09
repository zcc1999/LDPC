#include <iostream>
#include <random>
#include "LDPC_encoder.h"
LDPC_Encoder::LDPC_Encoder(void)
{
	Message.resize(INFO_BITS);
	Code.resize(VARIABLE_BITS);
}
LDPC_Encoder::~LDPC_Encoder()
{
}

/**************************************************
 *function: getMessage(void)
 *brief: 随机得到四位2进制数
 *input:
 *output:
 *author: zhangcc
**************************************************/
void LDPC_Encoder::getMessage(void)
{
	std::random_device rand_1;
	std::mt19937 m_rng(rand_1());
	for (int i = 0;i < INFO_BITS ;i++)
	{
		Message[i] = m_rng() % 2;
		//mes++;
	}

	//for (int i = 0;i < Message.size();i++)
	//	std::cout << Message[i] << " ";
	//std::cout << std::endl;
}

/**************************************************
 *function: mesEncoder(void)
 *brief :对产生的4位信息位进行编码
 *input:
 *output:
 *author: zhangcc
**************************************************/
void LDPC_Encoder::mesEncoder(vector <bitset<VARIABLE_BITS>> H_tran)
{
	for (int i = 0;i < Code.size(); i++)
	{
		if (i < INFO_BITS)
		{
			Code[i] = Message[i];
		}
		else if (i <= VARIABLE_BITS)
		{
			Code[i] = 0;
			for (int j  = 0; j < INFO_BITS; j++)
			{
				Code[i] ^= H_tran[i - INFO_BITS][j] * Code[j];
			}
		}
	}

	//for (int i = 0;i < Code.size();i++)
	//	std::cout << Code[i] << " ";
	//std::cout << std::endl;

}