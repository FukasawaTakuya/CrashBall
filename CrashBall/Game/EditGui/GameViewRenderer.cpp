#include "pch.h"
#include "GameViewRenderer.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

GameViewRenderer::GameViewRenderer()
{
}

GameViewRenderer::~GameViewRenderer()
{
}

void GameViewRenderer::Update(ID3D11ShaderResourceView* srv)
{
    ImGui::Begin("Scene");

    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Image(
        (ImTextureID)srv,
        size
    );

    ImVec2 leftTop = ImGui::GetItemRectMin();
    ImVec2 rightBottom = ImGui::GetItemRectMax();

    m_gameViewRect.left = leftTop.x;
    m_gameViewRect.top = leftTop.y;
    m_gameViewRect.right = rightBottom.x;
    m_gameViewRect.bottom = rightBottom.y;

    ImGui::End();

}
