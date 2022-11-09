#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>

#include "LDPC_standard.h"
#include "LDPC_encoder.h"
#include "modulator.h"
#include "channel.h"
#include "SPA_Iterator.h"
#include "MSA_Iterator.h"
#include "MSA_FixedPoint_Iterator.h"

using namespace std;
int main()
{
	LDPC_STANDARD ldpc_standard;
	LDPC_Encoder ldpc_encoder;
	BPSKMODULATOR bpskmodulator;
	CHANNEL channel;
	std::ofstream msaf;
	msaf.open("test(3).csv", std::ios::out | std::ios::trunc); 
	//msa_fix_float_(5_2)_12
	float SNR ;
	float SNR_a[25] = {4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0,5.1,5.2,5.225,5.25,5.275,5.3,5.325,5.35,5.375,5.4,5.425,5.45,5.475,5.5,};
	float SNR_b[12] = {4.0,4.5,5.0,5.1,5.2,5.3,5.35,5.4,5.425,5.45,5.475};
	float SNR_c[29] = { 4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8, 6.0,6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8 ,7.0,7.2,7.4,7.6,7.8,8.0,8.2,8.4,8.6,8.8};
	for (int k = 2; k <=11;k++)
	{
		SNR = SNR_b[k];
		channel.sigma = sqrt((1 / (pow(10, SNR / 10)* INFO_BITS / (VARIABLE_BITS + 3) * 2.0))); //极大概率是这里有问题
		std::cout << channel.sigma;
		//channel.sigma = (1 / std::sqrt(2 * std::pow(10, (((float)SNR) / 10)) * INFO_BITS / (VARIABLE_BITS+3)));

		float BER = 0;
		int error_time = 0;
		int time;
		int sum_error;
		float ave_ite_time = 0;
		ldpc_standard.get_H();
		ldpc_standard.get_H_tran();
		int mu_time = 0;
		//for (time = 0;  time < 10000;time++)
		for (time = 0; error_time <200&& time < 10000;time++)
		//for (time = 0; time < 100 || error_time < 20;time++)
		//for (time = 0; error_time < 100 && time < 10000;time++)
		//for (time = 0;  time < 10;time++)
		{

			ldpc_encoder.getMessage();
			ldpc_encoder.mesEncoder(ldpc_standard.H_tran);
			bpskmodulator.modulator(ldpc_encoder.Code);
			channel.addAWGN(bpskmodulator.tranSignal);

			MSA_FP spa(ldpc_standard.H, ldpc_standard.variable_node, ldpc_standard.check_node);
			MSA_FP msa(ldpc_standard.H, ldpc_standard.variable_node, ldpc_standard.check_node);
			msa.get_q0(channel.reSignal, channel.sigma);

			msa.get_q();
			msa.hard_decide();

			//下面两行位MSA算法译码
			int i;
			for ( i = 1; i <=50;i++)//  改为i<12，以及SPA的msa.get_q()函数
			{
				msa.hard_decide();
				if (msa.check())
				{
					//std::cout << "迭代了" << i-1 << "次";
					/*std::cout << "\n\n\n\n\n\n\n";*/
					break;
				}
				msa.get_R();
				msa.get_Q();
				msa.get_q();

				//spa.output();
			}
			sum_error = 0;
			if (i >= 50)
			{
				mu_time += 1;
				i = 0;
			}

			//计算误比特数
			for (int j = 0;j < INFO_BITS;j++)
			{
				if (ldpc_encoder.Code[j] != msa.c[j])
				{
					sum_error++;
				}
			}
			if(time % 1000 == 0) std::cout << "timep:" << time << "   ";

			if (sum_error >10000)
				std::cout << sum_error <<"i  = "<<i<< " ";
			if (sum_error > 10000)
			{
				std::cout << "now_time:" << time << "   ";
				std::cout << sum_error << "   ";
				sum_error = 0;
			}
			if (sum_error >0)
			{
				error_time += 1;
				//std::cout << sum_error<< "   ";
			}
			//cout << sum_error << endl;
			BER += (float)sum_error / INFO_BITS; ///注意！！！！！
			ave_ite_time += i;
		}
		BER = BER / time;
		ave_ite_time = ave_ite_time / (time- mu_time);
		std::cout << SNR << "," << BER << "time:" << time << "error_time:" << error_time << "ave_ite_time:" << ave_ite_time <<std::endl;
		msaf << SNR << "," << BER << std::endl;
	}
	msaf.close();

	return 0;
}