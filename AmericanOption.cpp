#include "AmericanOption.h"

double AmericanOption::calculPrix() {
    // Implémentation conditionnelle pour tester
    if (Maturity_ > 1.0) {
        return Strike_ * 0.9; // Prix simulé si maturité > 1 an
    } else {
        return Strike_ * 0.85; // Prix simulé si maturité ≤ 1 an
    }
}
