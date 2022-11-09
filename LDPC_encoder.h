#ifndef HANMING_ENCODER_H
#define HANMING_ENCODER_H

#include <iostream>
#include <vector>
#include <bitset>
#include "LDPC_standard.h"
using std::vector;
using std::bitset;
class LDPC_Encoder
{
public:
	LDPC_Encoder(void);
	~LDPC_Encoder();
	void getMessage(void);
	vector <int> Message;         //
	vector <int> Code;           //
	void mesEncoder(vector <bitset<VARIABLE_BITS>> H_tran);
};


#endif // !ENCODER_H


