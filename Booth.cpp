#include <iostream>
#include <vector>

using namespace std;

void corrimiento_aritmetico(vector<bool>& A, vector<bool>& Q, bool& Q_1) {
	bool A0 = A[0];
	bool Q0 = Q[0];
	
	for (int i = 0; i < A.size() - 1; ++i) {
		A[i] = A[i + 1];
		Q[i] = Q[i + 1];
	}
	A[A.size() - 1] = Q0;
	Q[Q.size() - 1] = A0;
	Q_1 = Q0;
}

void suma_numeros_con_signo(vector<bool>& A, const vector<bool>& M) {
	bool acarreo = false;
	for (int i = A.size() - 1; i >= 0; --i) {
		bool A_bit = A[i];
		bool M_bit = M[i];
		
		A[i] = A_bit ^ M_bit ^ acarreo; 
		acarreo = (A_bit & M_bit) | (A_bit & acarreo) | (M_bit & acarreo); 
	}
}

void resta_complemento_2(vector<bool>& A, const vector<bool>& M) {
	vector<bool> neg_M;
	for (bool bit : M) {
		neg_M.push_back(!bit);
	}
	vector<bool> uno(A.size(), true); 
	suma_numeros_con_signo(neg_M, uno);
	suma_numeros_con_signo(A, neg_M); 
}

void mostrar_bits(const vector<bool>& A, const vector<bool>& Q) {
	cout << "A: ";
	for (bool bit : A) {
		cout << bit;
	}
	cout << endl;
	cout << "Q: ";
	for (bool bit : Q) {
		cout << bit;
	}
	cout << endl;
}

void multiplicacion_booth(const vector<bool>& M, const vector<bool>& Q) {
	vector<bool> A = M; 
	vector<bool> q = Q; 
	bool q_1 = false; 
	
	cout << "Operacion 0:" << endl;
	mostrar_bits(A, Q);
	
	// Empezar desde las últimas cinco iteraciones
	int start_iteration = max(0, static_cast<int>(Q.size()) - 5);
	
	for (int i = start_iteration; i < Q.size(); ++i) {
		cout << "Operacion " << i + 1 << ":" << endl;
		if (q[0] == 0 && q_1 == 1) { 
			resta_complemento_2(A, M);
			cout << "Restar M de A:" << endl;
		}
		else if (q[0] == 1 && q_1 == 0) { 
			suma_numeros_con_signo(A, M);
			cout << "Sumar M a A:" << endl;
		}
		corrimiento_aritmetico(A, q, q_1); 
		mostrar_bits(A, q);
	}
}

int main() {
	int multiplicando, multiplicador;
	cout << "Ingrese el multiplicando: ";
	cin >> multiplicando;
	cout << "Ingrese el multiplicador: ";
	cin >> multiplicador;
	
	int n_bits = max(__builtin_clz(abs(multiplicando)), __builtin_clz(abs(multiplicador))) + 1;
	multiplicacion_booth(vector<bool>(n_bits, multiplicando), vector<bool>(n_bits, multiplicador));
	
	return 0;
}
