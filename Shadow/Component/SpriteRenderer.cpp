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
}

SpriteRenderer::~SpriteRenderer()
{
	// Empty.
}

void SpriteRenderer::OnComponentAdd()
{
	m_textureId = TextureManager::Instance()->Load(m_filePath, WindowManager::Instance()->GetMainWindow()->GetRenderer());

	DLOG("Sprite Renderer added to '" + m_pOwner->GetName() + "'.");
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

	TextureManager::Instance()->RenderSingle(pCamera, pRenderer, m_textureId, worldPosition.x, worldPosition.y);
}

void SpriteRenderer::OnComponentRemove()
{
	// TODO destroys the texture.
	DLOG("Sprite Renderer removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END