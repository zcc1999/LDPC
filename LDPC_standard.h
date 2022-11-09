#ifndef		LDPC_STANDARD_H
#define		LDPC_STANDARD_H

#include <iostream>
#include <vector>
#include <bitset>


#define  M_ROW 112    //M�����������
#define  M_COL 293    //M�����������

#define  M_ROW_MAX_INDEX M_ROW-1    //M�����������
#define  M_COL_MAX_INDEX M_COL-1    //M�����������


#define ZEROS_BITS 173    //M������173λ��0�������봫��

#define INFO_BITS 30592  //��Ϣ��bit��
#define INFO_ROW  105   //��Ϣλ��������105    105*293 = 30765 = ZEROS_BITS+INFO_BITS
#define INFO_ROW_MAX_INDEX  (INFO_ROW-1)  // ��Ϣλ������б�

#define VARIABLE_BITS  (INFO_BITS+CHECK_BITS)
#define CHECK_BITS	2045   //У��λ�ܱ�����    7*293 =  2051  ,����6λ������ġ� 
#define CHECK_ROW 7 
#define CHECK_REDUNDANCY_ROW 6 //����6λ����
#define CHECK_ROW_START_INDEX 105

using  std::vector;
using  std::bitset;

class LDPC_STANDARD
{
public:
	LDPC_STANDARD(void);
	~LDPC_STANDARD();
	int slope[7] = { 7,2,3,4,5,6,1 };
	//vector <bitset<M_COL>> M;
	vector <bitset<VARIABLE_BITS>> H;
	vector <bitset<VARIABLE_BITS>> H_tran;
	vector <vector<int> > variable_node;
	vector <vector<int> > check_node;
	//��ʾ������0��c��,б��Ϊslope��ֱ�ߣ��������ڵ�a�е�����
	void get_variable_index(int slope,int c, int a,int &index);   
	void get_H(void);
	void get_H_tran(void);
	//void get_variable_node(void);
	//void get_check_node(void);
};

void   getnew(vector <bitset <VARIABLE_BITS> > mar, vector <bitset <VARIABLE_BITS> >& mar_tran);
#endif // ! LDPC_STANDARD_H




