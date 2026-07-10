#include "pch.h"
#include "GameViewRenderer.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

/**
 * \brief コンストラクタ
 * 
 */
GameViewRenderer::GameViewRenderer()
{
}

/**
 * \brief デストラクタ
 * 
 */
GameViewRenderer::~GameViewRenderer()
{
}

/**
 * \brief 更新
 * 
 * \param srv
 */
void GameViewRenderer::Update(ID3D11ShaderResourceView* srv)
{
    ImGui::Begin("Game");

    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Image(
        (ImTextureID)srv,
        size
    );

    // 描画領域
    ImVec2 leftTop = ImGui::GetItemRectMin();
    ImVec2 rightBottom = ImGui::GetItemRectMax();

    m_gameViewRect.left = leftTop.x;
    m_gameViewRect.top = leftTop.y;
    m_gameViewRect.right = rightBottom.x;
    m_gameViewRect.bottom = rightBottom.y;

    ImGui::End();

}
