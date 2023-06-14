#include "sdpch.h"
#include "Animation.h"

#include "Graphics/TextureManager.h"
#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

Animation::Animation(GameObject* pOwner, const std::string& filePath, int numberFrames, const glm::vec2& spriteDimentions, float timeBetween) :
	m_pOwner(pOwner),
	SPRITE_DIMENSIONS(spriteDimentions),
	TIME_BETWEEN(timeBetween),
	m_numTextures(numberFrames),
	m_timer(timeBetween)
{
	SetComponentType(ComponentType::Animation);

	m_textureId = TextureManager::Instance()->Load(filePath, m_pOwner->GetSceneParent()->GetWindow()->GetRenderer(), spriteDimentions.x * numberFrames, spriteDimentions.y);
}

void Animation::OnComponentAdd()
{
	DLOG("Animation added to '" + m_pOwner->GetName() + "'.")
}

void Animation::Update()
{
	if (m_paused)
		return;

	m_timer -= Time::Instance()->GetDeltaTime();

	if (m_timer > 0)
		return;

	m_timer = TIME_BETWEEN;
	m_textureIndex = (m_textureIndex + 1) % m_numTextures;
}

void Animation::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f));
#endif
	glm::vec3 scale = m_pOwner->GetTransform()->scale;


	float angle = m_pOwner->GetTransform()->rotation.z;
	TextureManager::Instance()->RenderSingle(pCamera, pRenderer, m_textureId, glm::vec2(worldPosition.x, worldPosition.y), glm::vec2(scale.x, scale.y), SPRITE_DIMENSIONS, m_textureIndex * SPRITE_DIMENSIONS.x, angle);
}

void Animation::OnComponentRemove()
{
	DLOG("Animtion removed from '" + m_pOwner->GetName() + "'.");
	TextureManager::Instance()->RemoveTexture(m_textureId);
}

SHADOW_NAMESPACE_END