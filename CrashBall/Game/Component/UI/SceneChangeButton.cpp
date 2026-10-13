#include "pch.h"
#include "SceneChangeButton.h"
#include "Game/Engine/SceneManegement.h"
#include "Game/Engine/Time.h"

RegisterComponent(SceneChangeButton)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
SceneChangeButton::SceneChangeButton(IGameObject* gameObejct)
	: ButtonController(gameObejct)
{
	m_baseTypeid = typeid(ButtonController);
}

/**
 * \brief アタッチ時の処理
 * 
 */
void SceneChangeButton::Awake()
{
	ButtonController::Awake();

	using namespace SimpleMath;

	m_defaultScale = m_rectTransform->GetLocalScale();

	m_scale.Initialize([](const Vector2& s, const Vector2& e, float t) { return Vector2::Lerp(s, e, t); });

	m_onFocusEnterCommand = [this]()
		{
			m_scale.Set(Ease::OutCubic, m_rectTransform->GetLocalScale(), m_defaultScale * 1.2f, m_easeTime);
		};

	m_onFocusExitCommand = [this]()
		{
			m_scale.Set(Ease::OutCubic, m_rectTransform->GetLocalScale(), m_defaultScale, m_easeTime);
		};

	m_onPushCommand = [this]()
		{
			SceneMamegement::RequestChangeScene(m_nextSceneName);
		};

	m_scale.Set(Ease::OutCubic, m_rectTransform->GetLocalScale(), m_defaultScale, 0.0f);
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SceneChangeButton::Start(const GameContext& gameContext)
{
	ButtonController::Start(gameContext);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SceneChangeButton::Update(const GameContext& gameContext)
{
	ButtonController::Update(gameContext);
	
	m_scale.DoEase(Time::GetUnscaleElapsedTime());

	m_rectTransform->SetLocalScale(m_scale.GetValue());
}
