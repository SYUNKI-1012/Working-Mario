#define _CRT_SECURE_NO_WARNINGS
#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine//Camera.h"
#include "Food.h"
#include "Engine/Text.h"


namespace
{
	Ground* pGround;
}

//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	//pWp = Instantiate<Weapon>(this);
	pPlayer_ = Instantiate <Player>(this);
	pGround = Instantiate<Ground>(this);
	pPlayer_->SetGround(pGround);


	Camera::SetPosition({ 0.0f, -20.0f, 8.0f });
	Camera::SetTarget({ 5.0f, 0.0f, 4.0f });

	pText_ = new Text;
	pText_->Initialize();

}

//更新
void TestScene::Update()
{
	XMFLOAT3 pos = pPlayer_->GetPosition();
	Camera::SetPosition({ pos.x, 5.0f, pos.z - 15.0f });
	Camera::SetTarget({ pos.x, 5.0f, pos.z });
}

//餌を数えて、残り餌数を表示
//スコアを表示
//やり方は任せる
//sprintfでcの文字列を直で作ってもいいよ

//描画
void TestScene::Draw()
{
	std::string scrText;
	char buffer[256];
	sprintf(buffer, "%010d", myScore);
	scrText = "SCORE:" + std::string(buffer);
	pText_->Draw(500, 50, scrText.c_str());
	int esaCount, normalEsaCount, powerEsaCount;
	std::tuple<int, int, int> esa = pGround->GetEsaCount();
	esaCount = std::get<0>(esa);
	normalEsaCount = std::get<1>(esa);
	powerEsaCount = std::get<2>(esa);
	std::string EsaString = "NOEMAL ESA:" + std::to_string(normalEsaCount) + " POWER ESA:" + std::to_string(powerEsaCount);
	pText_->Draw(500, 100, EsaString.c_str());
}

//開放
void TestScene::Release()
{
	pText_->Release();//テキスト開放
}
