/*****************************************************************//**
 * \file   Easing.h
 * \brief  イージング
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include <functional>
#include "SimpleMath.h"

template<typename T>
class Easing
{
private:

    std::function<T(const T&, const T&, float)> m_lerp; // 線形補完関数

    std::function<float(float)> m_easing = [](float t) { return t; };   // イージング関数

    float m_time = 0.0f;    // 補完時間

    float m_current = 0.0f; // 経過時間

    T m_start;      // 開始位置

    T m_end;        // 終了位置

    T m_value;      // 現在値

public:
    Easing() = default;

    // 初期設定
    void Initialize(std::function<T(const T&, const T&, float)> lerp)
    {
        m_lerp = lerp;
    }

    // 設定
    void Set(std::function<float(float)> easing, const T& start, const T& end, float time)
    {
        m_easing = easing;
        m_start = start;
        m_end = end;
        m_time = time;

        m_current = 0.0f;
        m_value = m_start;
    }

    // イージングの実行
    void DoEase(float s)
    {
        // イージングが終了しているならリターン
        if (!IsEase()) return;

        m_current += s;
        m_current = std::clamp(m_current, 0.0f, m_time);
        float t = m_easing(m_current / m_time);
        m_value = m_lerp(m_start, m_end, t);

        if (m_current >= m_time)
        {
            m_current = m_time;
        }
    }

    // イージング中か
    bool IsEase()
    {
        return m_current != m_time;
    }

    // 現在値の取得
    T GetValue()
    {
        return m_value;
    }

    // 終了値の差し替え
    void ChangeEnd(const T& end)
    {
        m_end = end;
        m_start = m_value;

        m_current = 0.0f;
    }

};

// イージング関数一覧
namespace Ease{

    inline float Linear(float x)
    {
        return x;
    }

    inline float InSine(float x)
    {
        return 1 - std::cosf((x * DirectX::XM_PI) / 2);
    }

    inline float OutSine(float x)
    {
        return std::sinf((x * DirectX::XM_PI) / 2.0f);
    }

    inline float InOutSine(float x)
    {
        return -(std::cosf(DirectX::XM_PI * x) - 1.0f) / 2.0f;
    }

    inline float InQuad(float x)
    {
        return x * x;
    }

    inline float OutQuad(float x)
    {
        return 1.0f - (1.0f - x) * (1.0f - x);
    }

    inline float InOutQuad(float x)
    {
        return x < 0.5f ? (2.0f * x * x) : (1.0f - std::pow(-2.0f * x + 2.0f, 2.0f) / 2.0f);
    }

    inline float InCubic(float x)
    {
        return x * x * x;
    }

    inline float OutCubic(float x)
    {
        return 1.0f - std::pow(1.0f - x, 3.0f);
    }

    inline float InOutCubic(float x)
    {
        return x < 0.5f ? (4.0f * x * x * x) : (1.0f - std::pow(-2.0f * x + 2.0f, 3.0f) / 2.0f);
    }

    inline float InQuart(float x)
    {
        return  x * x * x * x;
    }

    inline float OutQuart(float x)
    {
        return 1.0f - std::pow(1.0f - x, 4.0f);
    }

    inline float InOutQuart(float x)
    {
        return x < 0.5f ? (8.0f * x * x * x * x) : (1.0f - std::pow(-2.0f * x + 2.0f, 4.0f) / 2.0f);
    }

    inline float InQuint(float x)
    {
        return x * x * x * x * x;
    }

    inline float OutQuint(float x)
    {
        return 1.0f - std::pow(1.0f - x, 5.0f);
    }

    inline float InOutQuint(float x)
    {
        return x < 0.5f ? (16.0f * x * x * x * x * x) : (1.0f - std::pow(-2.0f * x + 2.0f, 5.0f) / 2.0f);
    }

    inline float InExpo(float x)
    {
        return x == 0.0f ? (0.0f) : std::pow(2.0f, 10.0f * x - 10.0f);
    }

    inline float OutExpo(float x)
    {
        return x == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * x);
    }

    inline float InOutExpo(float x)
    {
        return x == 0.0f ? 0.0f
            : x == 1.0f ? 1.0f
            : x < 0.5f ? std::pow(2.0f, 20.0f * x - 10.0f) / 2.0f
            : (2.0f - std::pow(2.0f, -20.0f * x + 10.0f)) / 2.0f;
    }

    inline float InCirc(float x)
    {
        return 1.0f - std::sqrt(1.0f - std::pow(x, 2.0f));
    }

    inline float OutCirc(float x)
    {
        return std::sqrt(1.0f - std::pow(x - 1.0f, 2.0f));
    }

    inline float InOutCirc(float x)
    {
        return x < 0.5f
            ? (1 - std::sqrt(1.0f - std::pow(2.0f * x, 2.0f))) / 2.0f
            : (std::sqrt(1.0f - std::pow(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
    }

    inline float InBack(float x)
    {
        float c1 = 1.70158f;
        float c3 = c1 + 1.0f;
        return c3 * x * x * x - c1 * x * x;
    }

    inline float OutBack(float x)
    {
        float c1 = 1.70158f;
        float c3 = c1 + 1.0f;
        return 1.0f + c3 * std::pow(x - 1.0f, 3.0f) + c1 * std::pow(x - 1.0f, 2.0f);
    }

    inline float InOutBack(float x)
    {
        float c1 = 1.70158f;
        float c2 = c1 * 1.525f;
        return x < 0.5f
            ? (std::pow(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f
            : (std::pow(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
    }

    inline float InElastic(float x)
    {
        float c4 = (2.0f * DirectX::XM_PI) / 3.0f;
        return x == 0.0f
            ? 0.0f
            : x == 1.0f
            ? 1.0f
            : -std::pow(2.0f, 10.0f * x - 10.0f) * std::sin((x * 10.0f - 10.75f) * c4);
    }

    inline float OutElastic(float x)
    {
        float c4 = (2.0f * DirectX::XM_PI) / 3.0f;
        return x == 0.0f
            ? 0.0f
            : x == 1.0f
            ? 1.0f
            : std::pow(2.0f, -10.0f * x) * std::sin((x * 10.0f - 0.75f) * c4) + 1.0f;
    }

    inline float InOutElastic(float x)
    {
        float c5 = (2.0f * DirectX::XM_PI) / 4.5f;
        return x == 0.0f
            ? 0.0f
            : x == 1.0f
            ? 1.0f
            : x < 0.5f
            ? -(std::pow(2.0f, 20.0f * x - 10.0f) * std::sin((20.0f * x - 11.125f) * c5)) / 2.0f
            : (std::pow(2.0f, -20.0f * x + 10.0f) * std::sin((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
    }


    inline float OutBounce(float x)
    {
        float a = 7.5625f;
        float b = 2.75f;
        if (x < 1.0f / b)
        {
            return a * x * x;
        }
        else if (x < 2.0f / b)
        {
            float c = (x - 1.5f / b);
            return a * c * c + 0.75f;
        }
        else if (x < 2.5 / b)
        {
            float c = (x - 2.25f / b);
            return a * c * c + 0.9375f;
        }
        else
        {
            float c = (x - 2.625f / b);
            return a * c * c + 0.984375f;
        }
    }

    inline float InBounce(float x)
    {
        return 1.0f - OutBounce(1.0f - x);
    }


    inline float InOutBounce(float x)
    {
        return x < 0.5f
            ? (1.0f - OutBounce(1.0f - 2.0f * x)) / 2.0f
            : (1.0f + OutBounce(2.0f * x - 1.0f)) / 2.0f;
    }
}
