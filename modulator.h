#ifndef MODULATOR_H
#define MODULATOR_H
#include "LDPC_standard.h"
#include <vector>
using std::vector;
class BPSKMODULATOR
{
public:
	BPSKMODULATOR(void);
	~BPSKMODULATOR();
	void modulator(vector<int> code);
	vector<float> tranSignal;
};

#endif

