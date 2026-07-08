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

    ImGui::End();
}
