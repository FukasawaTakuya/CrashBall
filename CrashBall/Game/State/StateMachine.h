/*****************************************************************//**
 * \file   StateMachine.h
 * \brief  ステートマシン 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "pch.h"

#include "IStateMachine.h"
#include "StateBase.h"

/**
 * \brief ステートマシン
 */
template <typename Owner>
class  StateMachine : public IStateMachine {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// エイリアス宣言
	using StateCache = std::unordered_map<std::type_index, std::unique_ptr<StateBase<Owner>>>;

	std::function<void()> m_changeStateCmd = []() {};		// ステート変更命令

	Owner* m_owner = nullptr;								// オーナー

	StateBase<Owner>* m_currentState = nullptr;				// 今のステート
	
	StateCache m_states;									// ステートのキャッシュ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	StateMachine(Owner* owner)
		: m_owner(owner) 
	{}

	// デストラクタ
	~StateMachine() = default;

	// 操作
public:

	/**
	 * \brief 初期化.
	 * 
	 * \param owner オーナー
	 */
	void Initialeze(Owner* owner)
	{
		// オーナーのセット
		m_owner = owner;
		// ステート変更命令のクリア
		m_changeStateCmd = []() {};

		// 各ステートのオーナーとステートマシンのセット
		for (auto& state : m_states)
		{
			state.second->SetOwner(owner);
			state.second->SetStateMachine(this);
			//state.second->CallInitialize();
		}
	}

	/**
	 * \brief 更新.
	 * 
	 */
	void Update()
	{
		// ステート変更命令の実行
		m_changeStateCmd();
		// ステート変更命令のクリア
		m_changeStateCmd = []() {};

		// ステートのアップデート
		if (m_currentState != nullptr)
			m_currentState->CallUpdate();
	}

	// ステートの変更
	using IStateMachine::ChangeState;

	// ステートの生成
	template<typename State, typename... Args>
	requires std::derived_from<State, StateBase<Owner>>
	void CreateState(Args&&... args)
	{
		// イテレータの取得
		auto it = m_states.find(typeid(State));

		// 既にコンテナにステートが存在するならリターン
		if (it != m_states.end()) return;

		// ステートの生成
		std::unique_ptr<StateBase<Owner>> state = std::make_unique<State>(std::forward<Args>(args)...);

		// オーナーを設定
		state->SetOwner(m_owner);
		// ステートマシンを設定
		state->SetStateMachine(this);

		m_states.emplace(typeid(State), std::move(state));
	}

	// 取得/設定
public:

	// 現在のステートの型情報を取得
	std::type_index GetCurrentStateType() override
	{
		return typeid(*m_currentState);
	}

	// ステートの取得
	template<typename State>
	State* GetState()
	{
		auto it = m_states.find(typeid(State));

		if (it != m_states.end())
		{
			return it.second.get();
		}
	}



	// 内部実装
private:

	// 関数テンプレート無しでステートを変更
	void ChangeState(std::type_index StateType)
	{
		// オーナーがいないならリターン
		if (m_owner == nullptr) return;

		// イテレータの取得
		auto it = m_states.find(StateType);

		// イテレータが終端ならリターン
		if (it == m_states.end()) return;

		// 変更先のステートを取得
		StateBase<Owner>* state = it->second.get();

		// ステート変更命令
		m_changeStateCmd = [this, state]()
			{
				if (m_currentState != nullptr)
				{
					// 現ステートの終了処理
					m_currentState->CallOnExit();
				}

				// 新ステートをセット
				m_currentState = state;

				// 新ステートの開始処理
				m_currentState->CallOnEnter();
			};
	}


};