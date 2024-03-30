#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model, ViewProjection* viewProjection)
{
	// nullptrチェック
	assert(model);

	// 受け取ったデータをメンバー変数に代入
	model_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;

	// ワールド変数の初期化
	worldTransform_.Initialize();
}

void Skydome::Update()
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Skydome::Draw()
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);

}
