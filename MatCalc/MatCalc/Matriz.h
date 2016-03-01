#pragma once
#define MATRIZ_MAX_ERRMSG_SIZE 255
static char * m_errmsgtab[] = {
	// 0
	"Sucesso." ,
	"Tamanho(s) inválido(s)! O número de linhas e o de colunas devem ser maiores que 0." ,
	"Não conseguiu alocar memória para a matriz!" ,
	"Subscrito(s) inválido(s)! Os subscritos devem ser maiores que 0." ,
	"Dimensão inválida! A dimensão deve ser 1 ou 2." ,
	"As matrizes não têm as mesmas dimensões!" ,
	"A matriz ainda não foi inicializada!" ,
	"A matriz não é quadrada!" ,
	"A matriz não corresponde a um sistema! O número de colunas deve ser igual ao número de linhas mais um." ,
	"Pelo menos uma das matrizes não é unidimensional!"
	// 10
	"A matriz não é 1 x 1!"
	"A matriz não é unidimensional!"
	"Norma inválida! A norma vetorial deve ser igual a -1 (infinita), 0, 1 ou n (n > 0)."
	"Norma inválida! A norma matricial deve ser igual a -1 (infinita), 0 (Frobenius), 1 ou 2."
	"A matriz não é triangular!"
	"A matriz não está definida como um sistema!"
	"O destino deve ser uma matriz n x 1, sendo n o número de incógnitas!"
	"A matriz é singular!"
	"As matrizes têm tamanhos incompatíveis! O número de linhas da segunda deve ser igual ao número de colunas da primeira."
	"Esta operação não se aplica a sistemas."
	// 20

};


class Matriz {
/*
Esta classe é, basicamente, um 'array' de duas dimensões cujos componentes são do tipo 'double'.
Em obediência à convenção da Matemática, os subscritos iniciam-se em 1, não em 0.
Além disso, verificam-se os subscritos na execução dos métodos públicos.
Esta versão não utiliza processamento paralelo.
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
	double Matriz::m_PNorm1M(int col);										// Ainda não implementado
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
	Matriz::Matriz();
	Matriz::Matriz(const Matriz & A);
	Matriz::Matriz(int nrows, int ncols, bool initialize = false);
	void Matriz::Clear();
	bool Matriz::Initialized();
	Matriz Matriz::Initialized (bool value);
	bool Matriz::IsSystem();
	Matriz Matriz::IsSystem(bool value);
	double Matriz::SetVal(int nrow, int ncol, double value);
	int Matriz::GetSize(int ndimen = 1);
	// Válidos apenas para matrizes já inicializadas
	double Matriz::GetVal(int nrow, int ncol);
	Matriz Matriz::Sum(Matriz & A);
	Matriz Matriz::Sub(Matriz & A);
	double Matriz::Sum(double value);
	Matriz Matriz::Transpose();
	double Matriz::PNorm(int p);
	double Matriz::PNorm(int p, int pos);
	Matriz Matriz::Mult(double value);
	bool Matriz::IsSquare();
	bool Matriz::IsIdentity();
	bool Matriz::IsSimmetric();
	Matriz & Matriz::operator=(const Matriz & A);
	// ... válidos apenas para matrizes quadradas e sistemas
	bool Matriz::IsTriangularU();
	bool Matriz::IsTriangularL();
	bool Matriz::IsDiagonal();
	double Matriz::Det();
	double Matriz::Trace();
	Matriz Matriz::Invert();										// Ainda não implementado
	// ... válidos apenas para sistemas
	bool Matriz::SolveG();
	// ...... válidos apenas para sistemas triangulares
	bool Matriz::SolveT(Matriz & A);
	// ... válidos apenas para matrizes
	Matriz Matriz::Mult(Matriz & B);
	// ..... válidos apenas para matrizes unidimensionais
	Matriz Matriz::Outer(Matriz & A);
	// ...... válidos apenas para matrizes 1 x 1
	operator double();

protected:
	virtual Matriz::~Matriz();
	double Matriz::GetValRaw(int pos);
};

