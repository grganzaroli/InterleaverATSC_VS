#include "stdafx.h"
#include "atsc_interleaver.h"

void atsc_interleaver::set(int N_bch, int N_ldpc, int Q_ldpc, int Rate)
{
	n_bch = N_bch;
	n_ldpc = N_ldpc;
	rate = Rate;
	q_ldpc = Q_ldpc;
}

void atsc_interleaver::set(int N_bch, int Q_ldpc, int Rate)
{
	n_bch = N_bch;
	n_ldpc = n_bch*Rate/15;
	q_ldpc = Q_ldpc;
}

void atsc_interleaver::parity_interleaver(const unsigned char *lambda, unsigned char *U)
{
	for (int i = 0; i < n_bch; i++)
		U[i] = lambda[i];

	for (int s = 0; s < 360; s++)
		for (int t = 0; t < q_ldpc; t++)
			U[n_bch+360*t+s] = lambda[n_bch+q_ldpc*s+t];
}

void atsc_interleaver::parity_deinterleaver(const unsigned char *U, unsigned char *lambda)
{
	for (int i = 0; i < n_bch; i++)
		lambda[i] = U[i];

	for (int s = 0; s < 360; s++)
		for (int t = 0; t < q_ldpc; t++)
			lambda[n_bch+q_ldpc*s+t] = U[n_bch+360*t+s];
}

void atsc_interleaver::group_interleaver(const unsigned char *GI_in, unsigned char *GI_out, int *tabela)
{
	if(N_ldpc == 16200)
	{
		for(int i = 0; i < 
	}
	else if(N_ldpc == 64800)
	{

	}
}
void atsc_interleaver::group_deinterleaver(const unsigned char *GDI_in, unsigned char *GDI_out, int *tabela)
{
	if(N_ldpc == 16200)
	{

	}
	else if(N_ldpc == 64800)
	{

	}
}