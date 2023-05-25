#include "sdpch.h"
#include "SpriteRenderer.h"

#include "GameObject/GameObject.h"
#include "Window/WindowManager.h"
#include "Graphics/TextureManager.h"

SHADOW_NAMESPACE_BEGIN

SpriteRenderer::SpriteRenderer(GameObject* pOwner, std::string filePath) :
	m_pOwner(pOwner),
	m_filePath(filePath)
{
	SetComponentType(ComponentType::SpriteRenderer);

	m_textureId = TextureManager::Instance()->Load(m_filePath, WindowManager::Instance()->GetMainWindow()->GetRenderer());
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

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f));
#endif
	glm::vec3 scale = m_pOwner->GetTransform()->scale;
	TextureManager::Instance()->RenderSingle(pCamera, pRenderer, m_textureId, glm::vec2(worldPosition.x, worldPosition.y), glm::vec2(scale.x, scale.y));
}

void SpriteRenderer::OnComponentRemove()
{
	// TODO destroys the texture.
	DLOG("Sprite Renderer removed from '" + m_pOwner->GetName() + "'.");

	if(m_loadTexture)
		TextureManager::Instance()->RemoveTexture(m_textureId);
}

SHADOW_NAMESPACE_END