
// 許容距離
static const float toleranceSqrt = 0.01f * 0.01f;
// チーム数
static const int TEAM_NUM = 8;

// ビン数
static const uint BIN_NUM = 8;

// 定数バッファ
cbuffer HistInfo : register(b0)
{
    uint NowFrame; // 現フレーム
    uint BinWidth; // ビンの幅
}

// ビンを求める
uint CalcBin(uint2 stamp)
{
    uint delta = NowFrame - stamp.y;
    uint age = min(delta / BIN_NUM, BIN_NUM - 1);
    return age + BIN_NUM * stamp.x;
}