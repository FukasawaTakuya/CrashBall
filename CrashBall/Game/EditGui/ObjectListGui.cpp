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
#include "Game/Component/Default/Physics/RectTransform.h"

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

    DrawObjectGui(sceneEditer->GetWorldObject());

    // スクリプタブルオブジェクト表示
    ImGui::SeparatorText("ScriptableObject");

    for (auto& scriptable : *Scriptable::GetScriptableObejctList())
    {
        DrawObjectGui(scriptable.second.get());
    }

    // 新オブジェクト生成ボタン表示
    if (ImGui::Button("New 2DGameObject"))
    {
        m_isCreate2dObject = !m_isCreate3dObject;
    }
    if (ImGui::Button("New 3DGameObject"))
    {
        m_isCreate3dObject = !m_isCreate2dObject;
    }

    // 新オブジェクト生成
    if (m_isCreate3dObject || m_isCreate2dObject)
    {
        ImGui::InputText("objectName", &m_newObejctName);
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            GameObject* obj = sceneEditer->CreateNewGameObject(m_newObejctName);
            if (m_isCreate3dObject)
            {
                obj->AddComponent<Transform>();
                m_isCreate3dObject = false;
            }
            else if (m_isCreate2dObject)
            {
                obj->AddComponent<RectTransform>();
                m_isCreate2dObject = false;
            }
            m_newObejctName = "";
        }
    }

    ImGui::EndChild();

    ImGui::End();

    // 親子関係追加関数実行
    m_AddChildFunc();
    m_AddChildFunc = [](void) {};

    // オブジェクト削除
    if (Input::GetKeyTrigger(DirectX::Keyboard::Delete))
    {
        sceneEditer->RemoveGameObject(m_selectedObject);
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
            const ImGuiPayload* payload =
                ImGui::AcceptDragDropPayload("DragGameObject");

            if (payload != nullptr)
            {
                GameObject* child =
                    *static_cast<GameObject**>(payload->Data);
                    
                m_AddChildFunc = [&, child, object](void)
                    {
                        GameObject* parent = child->GetParent();
                        // 親がいないならリターン
                        if (parent == nullptr)
                        {
                            return;
                        }

                        // 子を削除
                        auto temp = parent->RemoveChild(child->GetName());
                        // 表示中のオブジェクトの子に設定
                        object->AddChildrenInRunTime(std::move(temp));
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
