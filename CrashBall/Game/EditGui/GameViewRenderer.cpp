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
void GameViewRenderer::Update(
    ID3D11ShaderResourceView* gameSrv,
    ID3D11ShaderResourceView* debugSrv)
{
    {
        ImGui::Begin("GameView");
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImGui::Image(
            (ImTextureID)gameSrv,
            size
        );
        ImGui::End();
    }

    {
        ImGui::Begin("DebugView");
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImGui::Image(
            (ImTextureID)debugSrv,
            size);

        // 描画領域の取得
        ImVec2 leftTop = ImGui::GetItemRectMin();
        ImVec2 rightBottom = ImGui::GetItemRectMax();

        m_gameViewRect.left = leftTop.x;
        m_gameViewRect.top = leftTop.y;
        m_gameViewRect.right = rightBottom.x;
        m_gameViewRect.bottom = rightBottom.y;

        ImGui::End();
    }
}
