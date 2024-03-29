//=============================================================================
//【 SceneCredit 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneCredit.h
//  @brief      SceneCredit
//  @author     yama
//*/
//=============================================================================

#pragma once

//=============================================================================
// ■ SceneCredit クラス
//-----------------------------------------------------------------------------
///**
//  @brief		リザルト画面
//*/
//=============================================================================
class SceneCredit : public LGameScene
{
public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneCredit"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:

    int         mPhase;
    int         mFrameCount;

    LSprite     mBGBlackSprite;
    LSprite     mWeaponSprite;

};

//=============================================================================
//								end of file
//=============================================================================