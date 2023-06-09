#include "sdpch.h"
#include "SpriteRenderer.h"

#include "GameObject/GameObject.h"
#include "Graphics/TextureManager.h"

SHADOW_NAMESPACE_BEGIN

SpriteRenderer::SpriteRenderer(GameObject* pOwner, std::string filePath) :
	m_pOwner(pOwner)
{
	SetComponentType(ComponentType::SpriteRenderer);

	m_textureId = TextureManager::Instance()->Load(filePath, m_pOwner->GetSceneParent()->GetWindow()->GetRenderer());
}

SpriteRenderer::SpriteRenderer(GameObject* pOwner, const std::string& filePath, const glm::vec2& dimensions, const glm::vec2& screenPosition, bool staticSprite) :
	m_pOwner(pOwner),
	m_screenPosition(screenPosition),
	m_dimensions(dimensions),
	m_staticSprite(staticSprite)
{
	SetComponentType(ComponentType::SpriteRenderer);

	m_textureId = TextureManager::Instance()->Load(filePath, m_pOwner->GetSceneParent()->GetWindow()->GetRenderer(), dimensions.x, dimensions.y);
}

SpriteRenderer::SpriteRenderer(GameObject* pOwner, uint16_t textureId) : 
	m_pOwner(pOwner),
	m_textureId(textureId),
	m_loadTexture(false)
{
	SetComponentType(ComponentType::SpriteRenderer);
}

SpriteRenderer::~SpriteRenderer()
{
	// Empty.
}

void SpriteRenderer::OnComponentAdd()
{
	DLOG("Sprite Renderer added to '" + m_pOwner->GetName() + "'.")
}

void SpriteRenderer::Update()
{
	// Empty.
}

void SpriteRenderer::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();

	if (m_staticSprite)
	{
		glm::vec2 cameraPosition = pCamera->GetPosition();
		TextureManager::Instance()->RenderSingle(pCamera, pRenderer, m_textureId, m_screenPosition + cameraPosition, glm::vec2(1.0f), m_dimensions, 0, m_pOwner->GetTransform()->rotation.z);
		return;
	}

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f));
#endif
	glm::vec3 scale = m_pOwner->GetTransform()->scale;

	TextureManager::Instance()->RenderSingle(pCamera, pRenderer, m_textureId, glm::vec2(worldPosition.x, worldPosition.y), glm::vec2(scale.x, scale.y), m_dimensions, 0, m_pOwner->GetTransform()->rotation.z);
}

void SpriteRenderer::OnComponentRemove()
{
	DLOG("Sprite Renderer removed from '" + m_pOwner->GetName() + "'.");

	if(m_loadTexture)
		TextureManager::Instance()->RemoveTexture(m_textureId);
}

SHADOW_NAMESPACE_END