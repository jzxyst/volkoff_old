//=============================================================================
//【 EffectManager 】
//-----------------------------------------------------------------------------
///**
//  @file       EffectManager.h
//  @brief      EffectManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <list>

class EffectBase;

//=============================================================================
// ■ EffectManager クラス
//-----------------------------------------------------------------------------
///**
//  @brief		エフェクトの管理クラス。取得は GameManager() から。
//*/
//=============================================================================
class EffectManager
{
public:

	/// コンストラクタ
    EffectManager();

    /// デストラクタ
    ~EffectManager();

public:

    /// フレーム更新 (作成されている全てのエフェクトの update() を呼ぶ)
    void update();

public:

    // ↓この方法だと、イテレート中は追加も削除もできない。後で必要になったら何か考えておく

    /// EffectBase のコンストラクタから呼ばれる
    void addEffect( EffectBase* effect_ );

    /// EffectBase のデストラクタから呼ばれる
    //void removeEffect( EffectBase* effect_ );

private:

    typedef std::list< EffectBase* >    EffectList;

private:

    EffectList      mEffectList;    ///< 全てのエフェクトを管理するリスト

};

//=============================================================================
//								end of file
//=============================================================================