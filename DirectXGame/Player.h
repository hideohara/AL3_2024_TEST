#pragma once

// プレイヤー

#include "Model.h"
#include "WorldTransform.h"


class Player
{

public:

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="model">モデル</param>
    /// <param name="textureHandle">テクスチャ</param>
    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();


private:
    // ワールド変換データ
    WorldTransform worldTransform_;
    // モデル
    Model* model_ = nullptr;
    Model* modelSkydome_ = nullptr;
    // テクスチャハンドル
    uint32_t textureHandle_ = 0u;

    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

};

