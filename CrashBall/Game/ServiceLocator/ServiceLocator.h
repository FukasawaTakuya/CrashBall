/*****************************************************************//**
 * \file   ServiceLocator.h
 * \brief  サービスロケータークラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Service.h"

/**
 * @brief サービスロケーター
 */
class  ServiceLocator {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unordered_map<std::type_index, Service*> m_services;	// サービスのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	ServiceLocator() = default;

	// 複数生成の禁止
	ServiceLocator(ServiceLocator&) = delete;
	ServiceLocator& operator=(const ServiceLocator&) = delete;

	// デストラクタ
	~ServiceLocator() = default;

	// 操作
public:
	// 取得/設定
public:
	// サービスの取得
	template <typename ServiceType>
	static ServiceType* Get() {
		auto& instance = GetInstance();
		// イテレータの取得
		auto it = instance.m_services.find(typeid(ServiceType));

		// 見つかれば返す
		if (it != instance.m_services.end())
		{
			return static_cast<ServiceType*>(it->second);
		}
		else return nullptr;
	}

	// サービスの設定
	template <typename ServiceType>
	static void Set(ServiceType* service)
	{
		auto& instance = GetInstance();
		// イテレータの取得
		auto it = instance.m_services.find(typeid(ServiceType));

		// まだ設定されてないなら設定する
		if (it == instance.m_services.end())
		{
			instance.m_services.emplace(typeid(ServiceType), service);
		}
	}

	// 内部実装
private:

	// インスタンスの取得
	static ServiceLocator& GetInstance()
	{
		static ServiceLocator instance;
		return instance;
	}

};
