
// 許容距離
static const float toleranceSqrt = 0.01f * 0.01f;
// チーム数
static const int TEAM_NUM = 8;

// ビン数
static const uint BIN_NUM = 32;

// 定数バッファ
cbuffer HistInfo : register(b0)
{
    uint nowFrame; // 現フレーム
    uint binWidth; // ビンの幅
}

uint AgeBin(int stamp)
{
    uint delta = nowFrame - stamp;
    return min(delta / binWidth, BIN_NUM - 1);
}