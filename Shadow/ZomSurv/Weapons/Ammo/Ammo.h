#pragma once


enum class AmmoType { LIGHT, MEDIUM, HEAVY, SPECIAL };

class Ammo
{
public:
	inline static Ammo* Instance() { return m_pInstance == nullptr ? m_pInstance = new Ammo() : m_pInstance; }

	void AddAmmo(AmmoType ammoType, unsigned short amount);
	void ReduceAmmo(AmmoType ammoType, unsigned short amount);
	void MaxAmmo();

	bool IsMaxAmmo();

	// Accessors.
	unsigned short GetAmmo(AmmoType ammoType) { return m_ammoCount[ammoType]; }

	// Constants.
	const unsigned short MAX_LIGHT = 120;
	const unsigned short MAX_MEDIUM = 240;
	const unsigned short MAX_HEAVY = 96;
	const unsigned short MAX_SPECIAL = 200;
private:
	Ammo();
	~Ammo();

	static Ammo* m_pInstance;

	std::unordered_map<AmmoType, unsigned short> m_ammoCount;

	void ClampTop(unsigned short& value, unsigned short addition, unsigned int max);
};