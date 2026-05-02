#ifndef  MONESER_TYPES_HPP
#define MONESER_TYPES_HPP

enum class MoneserType {
	Norm,
	Grass,
	Fire,
	Water,
	Null
};

float getDamageMult(const MoneserType& attacker, const MoneserType& defender);

#endif // ! MONESER_TYPES_HPP
