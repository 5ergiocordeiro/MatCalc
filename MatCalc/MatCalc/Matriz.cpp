#include "stdafx.h"
#include "math.h"
#include "Matriz.h"

/*
Ver arquivo "Matriz.h" para documentação.
*/

Matriz::~Matriz() {
	m_Dispose();
	}

Matriz::Matriz() {
	m_Reset();
	m_Dispose();
	m_SetError(0);
	}

Matriz::Matriz(Matriz & A) {
	if (! A.m_initialized) {
		m_SetError(6);
		return;
		}
	void * pvals;
	int size = A.m_ncol * A.m_nrow;
	pvals = malloc(size * sizeof(double));
	if (pvals = NULL) {
		m_Reset();
		m_SetError(2);
		return;
		}
	memcpy(pvals, A.m_pval, size);
	m_Dispose();
	* this = A;
	m_pval = (double *) pvals;
	m_SetError(0);
	}

Matriz::Matriz(Matriz & A, int row, int col) {
	int nrows = A.m_nrow, ncols = A.m_ncol;
	double * pvals;
	int size = (nrows - 1) * (ncols - 1);
	pvals = (double * ) malloc(size * sizeof(double));
	if (pvals = NULL) {
		m_Reset();
		m_SetError(2);
		return;
		}
	for (int isrc = 0, idst = 0; isrc < nrows; ++ isrc) {
		if (isrc == row) {
			continue;
			}
		for (int jsrc = 0, jdst = 0; jsrc < ncols; ++ jsrc) {
			if (jsrc == col) {
				continue;
				}
			pvals[idst * (ncols - 1) + jdst] = A.m_pval[isrc * ncols + jsrc];
			++ jdst;
			}
		++ idst;
		}
	m_Dispose();
	* this = A;
	m_pval = pvals;
	--m_nrow, --m_ncol;
	m_SetError(0);
	}

Matriz::Matriz(int nrows, int ncols, bool initialize) {
	if (nrows <= 0 || ncols <= 0) {
		m_Reset();
		m_SetError(1);
		return;
		}
	void * pvals;
	int size = ncols * nrows;
	if (initialize) {
		pvals = calloc(size, sizeof(double));
		}
	else {
		pvals = malloc(size * sizeof(double));
		}
	if (pvals = NULL) {
		m_Reset();
		m_SetError(2);
		return;
		}
	m_nrow = nrows;
	m_ncol = ncols;
	m_initialized = initialize;
	m_system = false;
	m_pval = (double *) pvals;
	m_SetError(0);
	}

double Matriz::m_Det() {
	if (m_nrow == 1) {
		return m_pval[0];
	}
	if (m_nrow == 2) {
		return m_pval[0] * m_pval[3] - m_pval[1] * m_pval[2];
		}
	double result = 0;
	for (int i = 0; i < m_nrow; ++ i) {
		Matriz * pA = new Matriz(* this, i, 0);
		result += ( ((i % 2) == 0) ? 1 : -1) * m_pval[i * m_ncol] * pA -> m_Det();
		pA -> m_Dispose();
		}
	m_SetError(0);
	return 0;
	}

void Matriz::m_Dispose() {
	if (m_pval != NULL) {
		free(m_pval);
		}
	}

int Matriz::m_FindMax(int pos, bool colmode, int start) {
	double maxval = 0;
	int i, address, maxpos = start;
	int size = colmode ? m_nrow : m_ncol;
	for (i = start; i < size; ++ i) {
		if (colmode) {
			address = i * m_ncol + pos;
			}
		else {
			address = pos * m_nrow + i;
			}
		double value = fabs(m_pval[address]);
		if (maxval < value) {
			maxval = value;
			maxpos = i;
			}
		}
	return maxpos;
	}

void Matriz::m_Reset() {
	m_nrow = m_ncol = 0;
	m_initialized = m_system = false;
	m_pval = NULL;
	}

double Matriz::m_PNormInftyV() {
	int size = (m_nrow == 1) ? m_ncol : m_nrow;
	double result = 0;
	for (int i = 0; i < size; ++ i) {
		double value = fabs(m_pval[i]);
		if (i == 0 || value > result) {
			result = value;
			}
		}
	m_SetError(0);
	return result;
	}

double Matriz::m_PNorm0V() { 
	int size = (m_nrow == 1) ? m_ncol : m_nrow;
	m_SetError(0);
	return size;
	}

double Matriz::m_PNorm1V() {
	int size = (m_nrow == 1) ? m_ncol : m_nrow;
	double result = 0;
	for (int i = 0; i < size; ++i) {
		result += fabs(m_pval[i]);
		}
	m_SetError(0);
	return result;
	}

double Matriz::m_PNormnV(double n) {
	double result = 0;
	for (int i = 0; i < m_nrow; ++ i) {
		result += pow(fabs(m_pval[i]), n);
		}
	return pow(result, 1 / n);
	}

double Matriz::m_PNormInftyM(int row) {
	double result = 0;
	for (int i = 0; i < m_ncol; ++ i) {
		double value = fabs(m_pval[row * m_ncol + i]);
		if (i == 0 || value > result) {
			result = value;
			}
		}
	m_SetError(0);
	return result;
	}

double Matriz::m_PNorm0M() {
	double result = 0;
	int size = m_nrow * m_ncol;
	for (int i = 0; i < size; ++i) {
		result += pow(fabs(m_pval[i]), 2);
		}
	return pow(result, 0.5);
	}

double Matriz::m_PNorm1M(int col) {
	double result = 0;
	for (int i = 0; i < m_nrow; ++ i) {
		double value = fabs(m_pval[i * m_ncol + col]);
		if (i == 0 || value > result) {
			result = value;
			}
		}
	m_SetError(0);
	return result;
	}

double Matriz::m_PNorm2M() {
	if (IsSimmetric()) {
		}
	else {
		}
	return 0;
	}

void Matriz::m_SetError(int errnbr) {
	m_error = errnbr;
	strcpy_s(m_errmsg, m_errmsgtab[errnbr]);
	}

bool Matriz::m_SolveTL(Matriz & A) {
	int last = A.m_ncol - 1;
	for (int i = 0; i <= last; ++ i) {
		if (m_pval[i * m_ncol + i] == 0) {
			m_SetError(17);
			return false;
			}
		double sum = 0;
		for (int j = i; j < last; ++ j) {
			sum += m_pval[i * m_ncol + j] * m_pval[j * m_ncol + m_nrow];
			}
		A.m_pval[i] = (m_pval[i * m_ncol + m_nrow] - sum) / m_pval[i * m_ncol + i];
		}
	m_SetError(0);
	return true;
	}

bool Matriz::m_SolveTU(Matriz & A) {
	int last = A.m_ncol - 1;
	for (int i = last; i >= 0; --i) {
		if (m_pval[i * m_ncol + i] == 0) {
			m_SetError(17);
			return false;
			}
		double sum = 0;
		for (int j = last; j > i; --j) {
			sum += m_pval[i * m_ncol + j] * m_pval[i * m_ncol + m_nrow];
			}
		A.m_pval[i] = (m_pval[i * m_ncol + m_nrow] - sum) / m_pval[i * m_ncol + i];
		}
	m_SetError(0);
	return true;
	}




Matriz Matriz::m_SumSub(Matriz & A, bool IsSum) {
	if (!m_initialized) {
		m_SetError(6);
		return * this;
		}
	if (m_nrow != A.m_nrow || m_ncol != A.m_ncol) {
		m_SetError(5);
		return * this;
		}
	int size = m_nrow * m_ncol;
	for (int pos = 0; pos < size; ++ pos) {
		if (IsSum) {
			m_pval[pos] += A.m_pval[pos];
			}
		else {
			m_pval[pos] -= A.m_pval[pos];
			}
		}
	m_SetError(0);
	return * this;
	}

void Matriz::m_TransposeSquare() {
	for (int i = 1; i < m_nrow; ++ i) {
		for (int j = 0; j < i; ++ j) {
			if (i != j) {
				int src = i * m_ncol + j;
				int dst = j * m_ncol + i;
				double value = m_pval[src];
				m_pval[src] = m_pval[dst];
				m_pval[dst] = value;
				}
			}
		}
	}

void Matriz::m_TransposeNonSquare() {
	int size = m_nrow * m_ncol;
	double * pvals = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < m_nrow; ++ i) {
		for (int j = 0; j < m_ncol; ++ j) {
			pvals[j * m_ncol + i] = m_pval[i * m_ncol + j];
			}
		}
	free(m_pval);
	m_pval = pvals;
	}

void Matriz::m_XchangeRows(int row1, int row2) {
	int row1pos = row1 * m_ncol;
	int row2pos = row2 * m_ncol;
	for (int j = 0; j < m_ncol; ++ j) {
		double value = m_pval[row1pos + j];
		m_pval[row1pos + j] = m_pval[row2pos + j];
		m_pval[row2pos + j] = m_pval[row1pos + j];
		}
	}

bool Matriz::Initialized() {
	m_SetError(0);
	return m_initialized;
	}

Matriz Matriz::Initialized(bool value) {
	if (value && (m_nrow <= 0 || m_ncol <= 0) ) {
		m_SetError(1);
		return * this;
		}
	m_initialized = value;
	m_SetError(0);
	return * this;
	}

bool Matriz::IsSystem() {
	m_SetError(0);
	return m_system;
	}

Matriz Matriz::IsSystem(bool value) {
	if (value) {
		if (! m_initialized) {
			m_SetError(1);
			return * this;
			}
		if (m_nrow != m_ncol - 1) {
			m_SetError(8);
			return * this;
			}
		}
	m_system = value;
	m_SetError(0);
	return *this;
	}

double Matriz::SetVal(int nrow, int ncol, double value) {
	if (nrow <= 0 || ncol <= 0 || nrow > m_nrow || ncol > m_nrow) {
		m_SetError(3);
		}
	else {
		m_pval[(nrow - 1) * m_ncol + (ncol - 1)] = value;
		}
	m_SetError(0);
	return value;
	}

int Matriz::GetSize(int ndimen) {
	if (ndimen != 1 && ndimen != 2) {
		m_SetError(4);
		return 0;
		}
	m_SetError(0);
	return (ndimen == 1) ? m_nrow : m_ncol;
	}

double Matriz::GetVal(int nrow, int ncol) {
	if (! m_initialized) {
		m_SetError(6);
		return 0;
		}
	if (nrow <= 0 || ncol <= 0 || nrow > m_nrow || ncol > m_nrow) {
		m_SetError(3);
		return 0;
		}
	m_SetError(0);
	return m_pval[(nrow - 1) * m_ncol + (ncol - 1)];
	}

Matriz Matriz::Sum(Matriz & A) {
	return m_SumSub(A, true);
	}

Matriz Matriz::Sub(Matriz & A) {
	return m_SumSub(A, false);
	}

double Matriz::Sum(double value) {
	if (! m_initialized) {
		m_SetError(6);
		return value;
		}
	int size = m_nrow * m_ncol;
	for (int pos = 0; pos < size; ++ pos) {
		m_pval[pos] += value;
	}
	m_SetError(0);
	return value;
	}

Matriz Matriz::Transpose() {
	if (! m_initialized) {
		m_SetError(6);
		return * this;
		}
	if (IsSquare()) {
		m_TransposeSquare();
		}
	else {
		m_TransposeNonSquare();
		}
	int auxint;
	auxint = m_nrow;
	m_nrow = m_ncol;
	m_ncol = auxint;
	m_SetError(0);
	return * this;
	}

double Matriz::PNorm(int p) {
	if (! m_initialized) {
		m_SetError(6);
		return -1;
		}
	if (m_nrow != 1 && m_ncol != 1) {
		m_SetError(11);
		return -1;
		}
	if (p < -1) {
		m_SetError(12);
		return -1;
		}
	switch (p) {
		case -1:
			return m_PNormInftyV();
		case 0:
			return m_PNorm0V();
		case 1:
			return m_PNorm1V();
		default:
			return m_PNormnV(p);
		}
	}

double Matriz::PNorm(int p, int pos) {
	if (! m_initialized) {
		m_SetError(6);
		return -1;
		}
	if (p < -1 || p > 2) {
		m_SetError(13);
		return -1;
		}
	switch (p) {
		case -1:
			return m_PNormInftyM(pos);
		case 0:
			return m_PNorm0M();
		case 1:
			return m_PNorm1M(pos);
		case 2:
			return m_PNorm2M();
		}
	}

Matriz Matriz::Mult(Matriz & A) {
	if ( !m_initialized) {
		m_SetError(6);
		return *this;
		}
	for (int i = 0; i < m_nrow; ++ i) {
		for (int j = 0; j < m_ncol; ++ j) {
			}
		}
	m_SetError(0);
	return * this;
	}

Matriz Matriz::Mult(double value) {
	if (! m_initialized) {
		m_SetError(6);
		return * this;
		}
	for (int i = 0; i < m_nrow; ++ i) {
		for (int j = 0; j < m_ncol; ++ j) {
			m_pval[i * m_ncol + j] *= value;
			}
		}
	m_SetError(0);
	return * this;
	}

double Matriz::GetValRaw(int pos) {
	m_SetError(0);
	return m_pval[pos];
	}

bool Matriz::IsSquare() {
	if (! m_initialized) {
		m_SetError(6);
		return false;
		}
	if ((m_nrow != m_ncol && ! m_system) || (m_nrow != (m_ncol - 1) && m_system)) {
		m_SetError(7);
		return false;
		}
	m_SetError(0);
	return true;
	}

bool Matriz::IsIdentity() {
	if (! IsSquare()) {
		return false;
		}
	bool result = true;
	for (int i = 0; i < m_nrow && result; ++ i) {
		for (int j = 0; j < m_nrow && result; ++ j) {
			double value = (i != j) ? 0 : 1;
			result = (m_pval[i * m_ncol + j] == value);
			}
		}
	m_SetError(0);
	return result;
	}

bool Matriz::IsSimmetric() {
	if (! IsSquare()) {
		return false;
		}
	bool result = true;
	for (int i = 1; i < m_nrow && result; ++ i) {
		for (int j = 0; j < i && result; ++ j) {
			result = (m_pval[i * m_ncol + j] == m_pval[j * m_ncol + i]);
			}
		}
	m_SetError(0);
	return result;
	}

bool Matriz::IsTriangularL() {
	if (! IsSquare()) {
		return false;
		}
	bool result = true;
	for (int i = 1; i < m_nrow && result; ++ i) {
		for (int j = 0; j < i && result; ++ j) {
			result = (m_pval[j * m_ncol + i] == 0);
			}
		}
	m_SetError(0);
	return result;
	}

bool Matriz::IsTriangularU() {
	if (! IsSquare()) {
		return false;
		}
	bool result = true;
	for (int i = 1; i < m_nrow && result; ++ i) {
		for (int j = 0; j < i && result; ++ j) {
			result = (m_pval[i * m_ncol + j] == 0);
			}
		}
	m_SetError(0);
	return result;
	}

bool Matriz::IsDiagonal() {
	if (! IsSquare()) {
		return false;
		}
	bool result = true;
	for (int i = 0; i < m_nrow && result; ++ i) {
		for (int j = 0; j < m_nrow && result; ++ j) {
			result = (i == j || m_pval[i * m_ncol + j] == 0);
			}
		}
	m_SetError(0);
	return result;
	}

double Matriz::Det() {
	if (!IsSquare()) {
		m_SetError(7);
		return 0;
		}
	return m_Det();
	}

double Matriz::Trace() {
	if (! IsSquare()) {
		m_SetError(7);
		return 0;
		}
	double result = 0;
	for (int i = 1; i < m_nrow; ++ i) {
		result += m_pval[i * m_ncol + i];
		}
	m_SetError(0);
	return 0;
	}

Matriz Matriz::Invert() { return * this; }

bool Matriz::SolveT(Matriz & A) {
	if (! m_system) {
		m_SetError(15);
		return false;
		}
	if (A.m_nrow != m_ncol - 1 || A.m_ncol != 1) {
		m_SetError(16);
		return false;
		}
	if (IsTriangularU()) {
		return m_SolveTU(A);
		}
	if (IsTriangularL()) {
		return m_SolveTL(A);
		}
	m_SetError(14);
	return false;
	}

bool Matriz::SolveG() {
	if (! m_system) {
		m_SetError(15);
		return false;
		}
	for (int j = 0; j < m_ncol - 1; ++ j) {
		int maxrow = m_FindMax(j, true, j);
		if (m_pval[maxrow * m_ncol + j] == 0) {
			m_SetError(17);
			return false;
			}
		m_XchangeRows(j, maxrow);
		for (int i = j + 1; i < m_nrow; ++ i) {
			double multiplier = m_pval[i * m_ncol + j] / m_pval[j * m_ncol + j];
			m_pval[i * m_ncol + j] = 0;
			for (int k = j + 1; k < m_ncol; ++ k) {
				m_pval[i * m_ncol + k] -= m_pval[j * m_ncol + k] * multiplier;
				}
			}
		}
	m_SetError(0);
	return true;
	}

Matriz Matriz::Outer(Matriz & A) {
	if (! m_initialized) {
		m_SetError(6);
		return *this;
		}
	if (m_ncol != 1 || A.m_nrow != 1) {
		m_SetError(9);
		return *this;
		}
	int nrows = m_nrow, ncols = A.m_ncol;
	int size = nrows * ncols;
	double * pvals = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < nrows; ++ i) {
		for (int j = 0; j < ncols; ++ j) {
			pvals[i * ncols + j] = m_pval[i * m_ncol + j] * A.m_pval[j * A.m_ncol + i];
			}
		}
	free(m_pval);
	m_pval = pvals;
	m_nrow = nrows;
	m_ncol = ncols;
	m_SetError(0);
	return *this;
	}

Matriz::operator double() {
	if (! m_initialized) {
		m_SetError(6);
		return 0;
		}
	if (m_nrow != 1 || m_nrow != 1) {
		m_SetError(10);
		return 0;
		}
	m_SetError(0);
	return m_pval[0];
	}
