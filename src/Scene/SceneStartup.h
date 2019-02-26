//=============================================================================
//【 SceneStartup 】
//-----------------------------------------------------------------------------
///**
//  @file       SceneStartup.h
//  @brief      SceneStartup
//  @author     yama
//  @par
//              起動後、一番最初に実行されるシーン。
//              前まで SceneLogo とか名前がついてたもの。
//*/
//=============================================================================

#pragma once

//=============================================================================
// ■ SceneStartup クラス
//-----------------------------------------------------------------------------
///**
//  @brief		起動後、一番最初に実行されるシーン
//*/
//=============================================================================
class SceneStartup : public LGameScene
{
public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneStartup"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:

    

    LSprite                             mFlashSprite;
    Core::Animation::FixedLengthScalar  mFlashScale;

    LSprite     mLogoSprite;

    LSprite     mTitleSubTextSprite;

    int         mStep;
    u32         mFrameCount;


};

//=============================================================================
//								end of file
//=============================================================================