#pragma once

class Bullet
{
public:
	Bullet(Shadow::Scene* pScene, const glm::vec2& pos, const glm::vec2& dir, float dam);
	~Bullet();

	void Update();

	// Accessors.
	inline glm::vec3 GetPosition() const { return *m_position; }
	inline float GetDamage() const { return m_damage; }
	inline const Shadow::GameObject* GetGameObject() const { return m_pGameObject; }
private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::GameObject* m_pGameObject = nullptr;

	glm::vec3* m_position;
	glm::vec3 m_direction;
	float m_damage;
};

