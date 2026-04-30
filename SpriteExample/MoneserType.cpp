#include "MoneserType.hpp"

float getDamageMult(const MoneserType& attacker, const MoneserType& defender) {
	if (attacker == MoneserType::Null || defender == MoneserType::Null) {
		return 0.0f;
	}
	if (attacker == MoneserType::Norm) {
		return 1.0f;
	}
	if (attacker == MoneserType::Fire) {
		if (defender == MoneserType::Grass) {
			return 1.5f;
		}
		else if (defender == MoneserType::Fire) {
			return 0.5f;
		}
		else if (defender == MoneserType::Water) {
			return 0.5f;
		}
	}
	if (attacker == MoneserType::Water) {
		if (defender == MoneserType::Grass) {
			return 0.5f;
		}
		else if (defender == MoneserType::Fire) {
			return 1.5f;
		}
		else if (defender == MoneserType::Water) {
			return 0.5f;
		}
	}
	if (attacker == MoneserType::Grass) {
		if (defender == MoneserType::Grass) {
			return 0.5f;
		}
		else if (defender == MoneserType::Fire) {
			return 0.5f;
		}
		else if (defender == MoneserType::Water) {
			return 1.5f;
		}
	}
	return 0.0f;
}