#include <iostream>
#include <cstdint>
#include <cmath>
#include <bitset>

struct PuntoFlotante32 {
	uint32_t signo;
	uint32_t exponente;
	uint32_t significando;
};

PuntoFlotante32 multiplicar(PuntoFlotante32 a, PuntoFlotante32 b) {
	if (a.exponente == 0 && a.significando == 0) {
		return a;
	}
	if (b.exponente == 0 && b.significando == 0) {
		return b;
	}
	
	int32_t suma_exponentes = int32_t(a.exponente) - 127 + int32_t(b.exponente) - 127 + 127;
	suma_exponentes -= 127;
	
	if (suma_exponentes < 0) {
		std::cerr << "Underflow en exponente" << std::endl;
		exit(1);
	}
	if (suma_exponentes > 255) {
		std::cerr << "Overflow en exponente" << std::endl;
		exit(1);
	}
	
	uint64_t producto_significandos = uint64_t(a.significando) * uint64_t(b.significando);
	
	if (producto_significandos & (1ULL << 47)) {
		producto_significandos += (1ULL << 48);
	}
	
	PuntoFlotante32 resultado;
	resultado.signo = a.signo ^ b.signo;
	resultado.exponente = suma_exponentes;
	resultado.significando = producto_significandos >> 24;
	
	return resultado;
}

int main() {
	PuntoFlotante32 a, b;
	std::cout << "Ingrese el primer número en formato (signo, exponente, significando): ";
	std::cin >> a.signo >> a.exponente >> a.significando;
	
	std::cout << "Ingrese el segundo número en formato (signo, exponente, significando): ";
	std::cin >> b.signo >> b.exponente >> b.significando;
	
	PuntoFlotante32 resultado = multiplicar(a, b);
	
	std::bitset<1> result_signo(resultado.signo);
	std::bitset<8> result_exponente(resultado.exponente);
	std::bitset<23> result_significando(resultado.significando);
	
	std::cout << "Resultado (signo, exponente, significando): "
		<< result_signo << " " << result_exponente << " " << result_significando << std::endl;
	
	return 0;
}
