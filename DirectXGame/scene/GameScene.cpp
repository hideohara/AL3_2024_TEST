#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathUtilityForText.h"

// 2Dアクション　プレイヤー

GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	// モデルの解放
	delete model_;
	delete modelBlock_;

	// 自キャラクラスの解放
	delete player_;


	// ブロックの解放
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();


}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("test.png");

	// モデルの生成
	model_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();


	// 自キャラクラスの生成
	player_ = new Player();

	// 自キャラクラスの初期化
	player_->Initialize(model_, textureHandle_, &viewProjection_);


	// ブロックのモデルの生成
	modelBlock_ = Model::CreateFromOBJ("cube");


	// 要素数
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockHorizontal);

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; ++i) {

		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}


}

void GameScene::Update() {

	// 自キャラの更新
	player_->Update();



	// ブロックの更新
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {

		//スケーリング行列の作成

		//	X軸周り回転行列の作成
		//	Y軸周り回転行列の作成
		//	Z軸周り回転行列の作成
		//	回転行列の合成(Z回転 * X回転 * Y回転)

		//	平行移動行列の作成

		//	worldTransformBlock->matWorld_ =
		//	スケーリング行列 * 回転行列 * 平行移動行列;


		// 行列更新
		// スケール、回転、平行移動を合成して行列を計算する
		//matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

		worldTransformBlock->UpdateMatrix();

		// 定数バッファに転送する
		//worldTransformBlock->TransferMatrix();
	}



}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	// 自キャラの描画
	player_->Draw();


	// ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlock, viewProjection_);
	}



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
