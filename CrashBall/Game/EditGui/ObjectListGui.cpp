/*****************************************************************//**
 * \file   ObjectListGui.cpp
 * \brief  オブジェクトリスト表示
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ObjectListGui.h"

#include "ImGui/imgui_stdlib.h"

#include "Game/ScriptableObject/Scriptable.h"
#include "Game/Engine/SceneManegement.h"
#include "Game/Engine/Input.h"

/**
 * \brief コンストラクタ
 * 
 */
ObjectListGui::ObjectListGui()
{
}

/**
 * \brief デストラクタ
 * 
 */
ObjectListGui::~ObjectListGui()
{
}

/**
 * \brief 更新
 * 
 * \param gameObjects ゲームオブジェクトのコンテナ
 */
void ObjectListGui::Update(ISceneEditer* sceneEditer)
{
    ImGui::Begin("ObjectList");

    ImGui::BeginChild("ObjectList");

    ImGui::SeparatorText("GameObject");

    // オブジェクトリストを表示
    for (auto& object : sceneEditer->GetGameObjects())
    {
        DrawObjectGui(object.get());
    }

    ImGui::SeparatorText("ScriptableObject");

    for (auto& scriptable : *Scriptable::GetScriptableObejctList())
    {
        DrawObjectGui(scriptable.second.get());
    }

    if (ImGui::Button("New GameObject"))
    {
        m_isCreateObject = true;
    }

    if (m_isCreateObject)
    {
        ImGui::InputText("objectName", &m_newObejctName);
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            sceneEditer->CreateNewGameObject(m_newObejctName);
            m_isCreateObject = false;
            m_newObejctName = "";
        }
    }

    ImGui::EndChild();

    ImGui::End();

    m_AddChildFunc(sceneEditer->GetGameObjects());
    m_AddChildFunc = [](ObjectCollection&) {};

    if (Input::GetKeyTrigger(DirectX::Keyboard::Delete))
    {
        sceneEditer->DeleteGameObject(m_selectedObject);
        m_selectedObject = nullptr;
    }
}

/**
 * \brief リセット
 * 
 */
void ObjectListGui::Reset()
{
    m_selectedObject = nullptr;
}

/**
 * \brief オブジェクトの表示
 *
 * \param object ゲームオブジェクト
 */
void ObjectListGui::DrawObjectGui(GameObject* object)
{
    // 表示詳細フラグ
    ImGuiBackendFlags flags = ImGuiTreeNodeFlags_FramePadding;

    // 子がいない場合葉ノード描画
    if (object->GetChildren().empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    // 選択されているなら選択フラグをオンにする
    if (object == m_selectedObject)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    // ノードの描画
    bool opened =
        ImGui::TreeNodeEx(
            object,
            flags,
            object->GetName().c_str());

    // クリック時の処理
    if (ImGui::IsItemDeactivated() && ImGui::IsItemHovered())
    {
        m_selectedObject = object;
    }

    // 開いているの時の処理
    if (opened)
    {
        // ドラッグされている場合の処理
        if (ImGui::BeginDragDropSource())
        {
            ImGui::Text(object->GetName().c_str());

            ImGui::SetDragDropPayload(
                "DragGameObject",
                &object,
                sizeof(object));

            ImGui::EndDragDropSource();
        }

        // ドロップ時の処理
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload =
                ImGui::AcceptDragDropPayload("DragGameObject"))
            {
                GameObject* child =
                    *(GameObject**)payload->Data;
                    
                m_AddChildFunc = [&, child, object](ObjectCollection& objects)
                    {
                        GameObject* parent = child->GetParent();
                        std::unique_ptr<GameObject> temp;
                        // 親がいる場合
                        if (parent != nullptr)
                        {
                            temp = parent->RemoveChild(child->GetName());
                        }
                        // 親がいない場合
                        else
                        {
                            auto it = std::ranges::find_if(objects, [&](std::unique_ptr<GameObject>& g)
                                {
                                    return child->GetID() == g->GetID();
                                });

                            if (it != objects.end())
                            {
                                temp = std::move(*it);
                                objects.erase(it);
                            }
                        }

                        if (object != nullptr)
                        {
                            object->AddChildrenInRunTime(std::move(temp));
                        }
                    };
            }

            ImGui::EndDragDropTarget();
        }

        // 子オブジェクトを描画
        for (auto& child : object->GetChildren())
        {
            DrawObjectGui(child.get());
        }

        ImGui::TreePop();
    }
}
