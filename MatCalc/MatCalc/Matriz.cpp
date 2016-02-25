#include "stdafx.h"
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
	if (A.m_pval != NULL) {
		memcpy(pvals, A.m_pval, size);
		}
	m_Dispose();
	* this = A;
	m_pval = (double *) pvals;
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
	m_pval = (double *) pvals;
	m_SetError(0);
	}

void Matriz::m_Dispose() {
	if (m_pval != NULL) {
		free(m_pval);
		}
	}

void Matriz::m_Reset() {
	m_nrow = m_ncol = 0;
	m_initialized = false;
	m_pval = NULL;
	}

double Matriz::m_PNormInftyV() { return 0; }
double Matriz::m_PNorm0V() { return 0; }
double Matriz::m_PNorm1V() { return 0; }
double Matriz::m_PNormnV() { return 0; }
double Matriz::m_PNormInftyM(int pos) { return 0; }
double Matriz::m_PNorm0M(int pos) { return 0; }
double Matriz::m_PNorm1M(int pos) { return 0; }
double Matriz::m_PNormnM(int pos) { return 0; }


void Matriz::m_SetError(int errnbr) {
	m_error = errnbr;
	strcpy_s(m_errmsg, m_errmsgtab[errnbr]);
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
			return m_PNormnV();
		}
	}

double Matriz::PNorm(int p, int pos) {
	if (! m_initialized) {
		m_SetError(6);
		return -1;
		}
	if (p < -1) {
		m_SetError(12);
		return -1;
		}
	switch (p) {
		case -1:
			return m_PNormInftyM(pos);
		case 0:
			return m_PNorm0M(pos);
		case 1:
			return m_PNorm1M(pos);
		default:
			return m_PNormnM(pos);
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
	for (int i = 1; i < m_nrow; ++ i) {
		for (int j = 0; j < m_nrow; ++ j) {
			double value = (i != j) ? 0 : 1;
			if (m_pval[i * m_ncol + j] != value) {
				return false;
				}
			}
		}
	m_SetError(0);
	return true;
	}

bool Matriz::IsSimmetric() {
	if (! IsSquare()) {
		return false;
		}
	for (int i = 1; i < m_nrow; ++ i) {
		for (int j = 0; j < i; ++ j) {
			if (m_pval[i * m_ncol + j] != m_pval[j * m_ncol + i]) {
				return false;
				}
			}
		}
	m_SetError(0);
	return true;
	}

bool Matriz::IsTriangularL() {
	if (! IsSquare()) {
		return false;
		}
	for (int i = 1; i < m_nrow; ++ i) {
		for (int j = 0; j < i; ++ j) {
			if (m_pval[j * m_ncol + i] != 0) {
				return false;
				}
			}
		}
	m_SetError(0);
	return true;
	}

bool Matriz::IsTriangularU() {
	if (! IsSquare()) {
		return false;
		}
	for (int i = 1; i < m_nrow; ++ i) {
		for (int j = 0; j < i; ++ j) {
			if (m_pval[i * m_ncol + j] != 0) {
				return false;
				}
			}
		}
	m_SetError(0);
	return true;
	}

bool Matriz::IsDiagonal() {
	if (! IsSquare()) {
		return false;
		}
	for (int i = 0; i < m_nrow; ++ i) {
		for (int j = 0; j < m_nrow; ++ j) {
			if (i != j && m_pval[i * m_ncol + j] != 0) {
				return false;
				}
			}
		}
	m_SetError(0);
	return true;
	}

double Matriz::Det() { return 0; }
double Matriz::Trace() { return 0; }
Matriz Matriz::Invert() { return * this; }


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
