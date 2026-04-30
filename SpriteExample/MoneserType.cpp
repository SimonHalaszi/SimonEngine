#include "MoneserType.hpp"

float getDamageMult(const MoneserType& attacker, const MoneserType& defender) {
	if (attacker == MoneserType::Null || defender == MoneserType::Null) {
		return 0.0f;
	}
	if (attacker == MoneserType::Norm || defender == MoneserType::Norm) {
		return 1.0f;
	}

	float effectiveScalar = 0.75;

	if (attacker == MoneserType::Fire) {
		if (defender == MoneserType::Grass) {
			return 1.0f + effectiveScalar;
		}
		else if (defender == MoneserType::Fire) {
			return 1.0f - effectiveScalar;
		}
		else if (defender == MoneserType::Water) {
			return 1.0f - effectiveScalar;
		}
	}
	if (attacker == MoneserType::Water) {
		if (defender == MoneserType::Grass) {
			return 1.0f - effectiveScalar;
		}
		else if (defender == MoneserType::Fire) {
			return 1.0f + effectiveScalar;
		}
		else if (defender == MoneserType::Water) {
			return 1.0f - effectiveScalar;
		}
	}
	if (attacker == MoneserType::Grass) {
		if (defender == MoneserType::Grass) {
			return 1.0f - effectiveScalar;
		}
		else if (defender == MoneserType::Fire) {
			return 1.0f - effectiveScalar;
		}
		else if (defender == MoneserType::Water) {
			return 1.0f + effectiveScalar;
		}
	}
	return 0.0f;
}