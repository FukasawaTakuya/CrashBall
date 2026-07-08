#include "pch.h"
#include "EditGuiManager.h"

EditGuiManager::EditGuiManager()
{
    m_objectListGui         = std::make_unique<ObjectListGui>();
    m_objectInspectorGui    = std::make_unique<ObjectInspectorGui>();
    m_gameViewRenderer      = std::make_unique<GameViewRenderer>();
}

EditGuiManager::~EditGuiManager()
{
}

void EditGuiManager::Update(
    std::vector<GameObject*>* gameObjects, 
    std::vector<const GameObject*>* scriptableObjects, 
    ID3D11ShaderResourceView* srv)
{
    if (!m_isEditMode) return;

    ImGui::DockSpaceOverViewport();
    m_objectListGui->SetGameObejcts(gameObjects);
    m_objectListGui->SetScriptableObjects(scriptableObjects);

    m_objectListGui->Update();
    m_objectInspectorGui->Updata(m_objectListGui->GetSelectedObject());
    m_gameViewRenderer->Update(srv);
}
