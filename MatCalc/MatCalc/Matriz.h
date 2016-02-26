#pragma once
#define MATRIZ_MAX_ERRMSG_SIZE 255
static char * m_errmsgtab[] = {
	// 0
	"Sucesso." ,
	"Tamanho(s) inv�lido(s)! O n�mero de linhas e o de colunas devem ser maiores que 0." ,
	"N�o conseguiu alocar mem�ria para a matriz!" ,
	"Subscrito(s) inv�lido(s)! Os subscritos devem ser maiores que 0." ,
	"Dimens�o inv�lida! A dimens�o deve ser 1 ou 2." ,
	"As matrizes n�o t�m as mesmas dimens�es!" ,
	"A matriz ainda n�o foi inicializada!" ,
	"A matriz n�o � quadrada!" ,
	"A matriz n�o corresponde a um sistema! O n�mero de colunas deve ser igual ao n�mero de linhas mais um." ,
	"Pelo menos uma das matrizes n�o � unidimensional!"
	// 10
	"A matriz n�o � 1 x 1!"
	"A matriz n�o � unidimensional!"
	"Norma inv�lida! A norma vetorial deve ser igual a -1 (infinita), 0, 1 ou n (n > 0)."
	"Norma inv�lida! A norma matricial deve ser igual a -1 (infinita), 0 (Frobenius), 1 ou 2."
	"A matriz n�o � triangular!"
	"A matriz n�o est� definida como um sistema!"
	"O destino deve ser uma matriz n x 1, sendo n o n�mero de inc�gnitas!"
	"A matriz � singular!"
};


class Matriz {
/*
Esta classe �, basicamente, um 'array' de duas dimens�es cujos componentes s�o do tipo 'double'.
Em obedi�ncia � conven��o da Matem�tica, os subscritos iniciam-se em 1, n�o em 0.
Al�m disso, verificam-se os subscritos na execu��o dos m�todos p�blicos.
Esta vers�o n�o utiliza processamento paralelo.
*/


private:
	int m_nrow, m_ncol, m_error;
	bool m_initialized, m_system;
	double * m_pval;
	char m_errmsg[MATRIZ_MAX_ERRMSG_SIZE + 1];
	Matriz::Matriz(Matriz & A, int row, int col);
	double Matriz::m_Det();
	void Matriz::m_Dispose();
	int Matriz::m_FindMax(int pos, bool colmode = true, int start = 0);
	double Matriz::m_PNormInftyV();
	double Matriz::m_PNorm0V();
	double Matriz::m_PNorm1V();
	double Matriz::m_PNormnV(double n);
	double Matriz::m_PNormInftyM(int row);
	double Matriz::m_PNorm0M();
	double Matriz::m_PNorm1M(int col);
	double Matriz::m_PNorm2M();
	void Matriz::m_Reset();
	void Matriz::m_SetError(int errnbr);
	bool Matriz::m_SolveTL(Matriz & A);
	bool Matriz::m_SolveTU(Matriz & A);
	Matriz Matriz::m_SumSub(Matriz & A, bool IsSum);
	void Matriz::m_TransposeSquare();
	void Matriz::m_TransposeNonSquare();
	void Matriz::m_XchangeRows(int row1, int row2);

public:
	Matriz::~Matriz();
	Matriz::Matriz();
	Matriz::Matriz(Matriz & A);
	Matriz::Matriz(int nrows, int ncols, bool initialize = false);
	bool Initialized();
	Matriz Initialized (bool value);
	bool IsSystem();
	Matriz IsSystem(bool value);
	double Matriz::SetVal(int nrow, int ncol, double value);
	int Matriz::GetSize(int ndimen = 1);
	// V�lidos apenas para matrizes j� inicializadas
	double Matriz::GetVal(int nrow, int ncol);
	Matriz Matriz::Sum(Matriz & A);
	Matriz Matriz::Sub(Matriz & A);
	double Matriz::Sum(double value);
	Matriz Matriz::Transpose();
	double Matriz::PNorm(int p);
	double Matriz::PNorm(int p, int pos);
	Matriz Matriz::Mult(Matriz & A);
	Matriz Matriz::Mult(double value);
	bool Matriz::IsSquare();
	bool Matriz::IsIdentity();
	bool Matriz::IsSimmetric();
	// ... v�lidos apenas para matrizes quadradas e sistemas
	bool Matriz::IsTriangularU();
	bool Matriz::IsTriangularL();
	bool Matriz::IsDiagonal();
	double Matriz::Det();
	double Matriz::Trace();
	Matriz Matriz::Invert();
	// ... v�lidos apenas para sistemas
	bool Matriz::SolveG();
	// ...... v�lidos apenas para sistemas triangulares
	bool Matriz::SolveT(Matriz & A);
	// ... v�lidos apenas para matrizes unidimensionais
	Matriz Matriz::Outer(Matriz & A);
	// ... v�lidos apenas para matrizes 1 x 1
	operator double();

protected:
	double Matriz::GetValRaw(int pos);
};

