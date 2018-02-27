#ifndef ATSC_INTERLEAVER_H
#define ATSC_INTERLEAVER_H

class atsc_interleaver
{
private:
	int rate; //taxa de codificação LDPC
	int n_bch; //N_bch
	int n_ldpc; //N_ldpc
	int q_ldpc; //Q_ldpc
public:
	void set(int N_bch, int N_ldpc, int Q_ldpc, int Rate, int mod);
	void set(int N_bch, int Q_ldpc, int Rate);

	void parity_interleaver(const unsigned char *lambda, unsigned char *U); // APENAS LDPC TIPO B
	void parity_deinterleaver(const unsigned char *U, unsigned char *lambda); // APENAS LDPC TIPO B

	void group_interleaver(const unsigned char *GI_in, unsigned char *GI_out, int *tabela);
	void group_deinterleaver(const unsigned char *GDI_in, unsigned char *GDI_out, int *tabela);
};

#endif