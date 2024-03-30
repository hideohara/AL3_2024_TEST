#include "Player.h"
#include <cassert>

// プレイヤー

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection)
{
	// nullptrチェック
	assert(model);

	// 受け取ったデータをメンバー変数に代入
	model_ = model;
	textureHandle_ = textureHandle;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;


	// ワールド変数の初期化
	worldTransform_.Initialize();

}

// 更新
void Player::Update()
{

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


}

// 描画
void Player::Draw()
{

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);


}
