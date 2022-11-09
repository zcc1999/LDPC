#include <iostream>
#include "channel.h"
#include "LDPC_standard.h"
#include <random>
CHANNEL::CHANNEL()
{
	reSignal.resize(VARIABLE_BITS);
}
CHANNEL :: ~CHANNEL()
{

}
void CHANNEL::addAWGN(vector <float>tran_signal)
{
	std::random_device rd;
	std::mt19937 m_rng(rd());
	std::normal_distribution<float> awgn_generator(0, sigma);//sigma

	for (int i = 0;i < VARIABLE_BITS;i++)
	{
		reSignal[i] = tran_signal[i] + awgn_generator(m_rng);
		//reSignal[i] = tran_signal[i] ;
	}
	
	//for (int i = 0;i < reSignal.size();i++)
	//{
	//	std::cout.setf(std::ios::right);
	//	std::cout.width(12);
	//	std::cout << reSignal[i];
	//}
	//	
	//std::cout << std::endl;
}