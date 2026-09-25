#include "pch.h"
#include "SceneSelect.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"

#include "Game/Engine/SceneManegement.h"

/**
 * \brief コンストラクタ
 * 
 */
SceneSelect::SceneSelect()
{
}

/**
 * \brief デストラクタ
 * 
 */
SceneSelect::~SceneSelect()
{
}

/**
 * \brief 更新
 * 
 * \param sceneEditer
 */
void SceneSelect::Update(ISceneEditer* sceneEditer)
{
	ImGui::Begin("Scene");

	if (ImGui::BeginCombo("Scene", sceneEditer->GetCurrrentSceneName().c_str()))
	{
		for (auto sceneName : sceneEditer->GetSceneNameList())
		{
			bool isSelected = sceneName == sceneEditer->GetCurrrentSceneName();

			if (ImGui::Selectable(sceneName.c_str(), &isSelected))
			{
				SceneMamegement::RequestChangeScene(sceneName);
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	if (ImGui::Button("CreateNewScene"))
	{
		m_isCreateScene = !m_isCreateScene;
	}

	if (m_isCreateScene)
	{

		ImGui::InputText("newSceneName", &m_newSceneName);
		if (ImGui::IsItemDeactivatedAfterEdit())
		{
			sceneEditer->CreateNewScene(m_newSceneName);
		}
	}

	ImGui::End();
}
