/*****************************************************************//**
 * \file   ObjectListGui.cpp
 * \brief  オブジェクトリスト表示
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ObjectListGui.h"

#include "Game/ScriptableObject/Scriptable.h"

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
void ObjectListGui::Update(ObjectCollection& gameObjects)
{
    ImGui::Begin("ObjectList");

    ImGui::BeginChild("ObjectList");

    // オブジェクトリストを表示
    for (auto& object : gameObjects)
    {
        DrawObjectGui(object.get());
    }

    ImGui::EndChild();

    ImGui::End();

    m_AddChildFunc(gameObjects);
    m_AddChildFunc = [](ObjectCollection&) {};
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

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload =
                ImGui::AcceptDragDropPayload("DragGameObject"))
            {
                GameObject* child =
                    *(GameObject**)payload->Data;
                    
                m_AddChildFunc = [&, child](ObjectCollection& objects)
                    {
                        auto it = std::ranges::find_if(objects, [&](std::unique_ptr<GameObject>& g)
                            {
                                return child->GetID() == g->GetID();
                            });

                        // 子オブジェクトの検索ができないため呼ばれない
                        if (it != objects.end())
                        {
                            object->AddChildren(std::move(*it));
                            objects.erase(it);
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
