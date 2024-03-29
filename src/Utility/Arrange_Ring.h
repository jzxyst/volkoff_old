//=============================================================================
// ■ Arrange_Ring
// 2011/1/21 Keisuke Hosoda
//
// 動作：
//   中心点からの円周上の座標を返す
//=============================================================================
#ifndef ARRANGE_RING_H
#define ARRANGE_RING_H

#include <vector>

class Ring
{
private:

	struct HVector2
	{
		float x;
		float y;
	};

	// 円周上に座標が並ぶ円のデータ
	struct StandardCircle
	{
		// 円の中心点
		HVector2 Origin;
		// 円の半径
		HVector2 Radius;
	};

	// 円周上に並ぶ座標(Star)のデータ
	struct StarData
	{
		// Star座標
		std::vector< HVector2 > Pos;
		// いくつ配置するのか
		unsigned int setNum;
		// 何度間隔か
		float Angle;
		// 基準座標の角度( 0〜359 )
		float OriginDeg;
		// 基準座標にあるStarの添え字( 0~setNum-1 )
		unsigned int Target;
	};

	// 回転に必要なデータ
	struct TurnData
	{
		// 座標の回転方向( -1, 0, 1 )
		int TurnVec;
		// 1フレーム前の回転方向を保持
		int OldTurnVec;
		// 回転する速度
		float TurnSpeed;
		//何度回転するか
		float TurnLimit;

		// 回転角度
		float Deg;
		float Rad; // ラジアン指定の場所もあるため。

		// Star間移動で使う入力ロック
		bool InputLock;
	};

	StandardCircle mStdCir;
	StarData       mSData;
	TurnData       mTData;

public:

	// コンストラクタ
	Ring();
	
	// デストラクタ
	~Ring();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： Initialize
	//
	//  引数 ： < void >
	// 戻り値： < void >
	//  処理 ： 初期化。使用前に一度だけ呼ぶこと
	//---------------------------------------------------------------------
	void Initialize();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： Process
	//
	//  引数 ： < void >
	// 戻り値： < void >
	//  処理 ： ループの中で呼ぶこと
	//---------------------------------------------------------------------
	void Process();

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： Release
	//
	//  引数 ： < void >
	// 戻り値： < void >
	//  処理 ： 解放処理。必ず明示的に呼ぶこと
	//---------------------------------------------------------------------
	void Release();

// 以下セッタ&ゲッタ

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setCircleOrigin
	//
	//  引数 ： < const int x, const int y >
	// 戻り値： < void >
	//  処理 ： 引数指定の場所を円の原点とする
	//---------------------------------------------------------------------
	void setCircleOrigin( const int x, const int y );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setCircleSize
	//
	//  引数 ： < const float width, const float height >
	// 戻り値： < void >
	//  処理 ： 円の大きさを引数で指定する
	//---------------------------------------------------------------------
	void setCircleSize( const float width, const float height );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setCircle
	//
	//  引数 ： < const int x, const int y, 
	//            const float width, const float height >
	// 戻り値： < void >
	//  処理 ： 円のデータを引数で指定する
	//---------------------------------------------------------------------
	void setCircle( const int x, const int y, const float width, const float height );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setStarNum
	//
	//  引数 ： < const unsigned int number >
	// 戻り値： < void >
	//  処理 ： 円周上に並ぶ座標( Star )の数を設定
	//---------------------------------------------------------------------
	void setStarNum( const unsigned int number );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setOriginDeg
	//
	//  引数 ： < const float degree >
	// 戻り値： < void >
	//  処理 ： Starの基準角度を引数指定( 0〜359 )
	//---------------------------------------------------------------------
	void setOriginDeg( const float degree );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setTarget
	//
	//  引数 ： < const unsigned int idx >
	// 戻り値： < void >
	//  処理 ： 基準位置に引数指定のStarを配置
	//---------------------------------------------------------------------
	void setTarget( const unsigned int idx );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setTurnDirection
	//
	//  引数 ： < const int direct >
	// 戻り値： < void >
	//  処理 ： 回転方向、-1, 0, 1で指定
	//---------------------------------------------------------------------
	void setTurnDirection( const int direct );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： setTurnSpeed
	//
	//  引数 ： < const float speed >
	// 戻り値： < void >
	//  処理 ： 基準位置に引数指定のStarを配置
	//---------------------------------------------------------------------
	void setTurnSpeed( const float speed );

  // ゲッタ

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： getCircle
	//
	//  引数 ： < void >
	// 戻り値： < StandardCircle >
	//  処理 ： 円のデータを取得
	//---------------------------------------------------------------------
	StandardCircle *getCircle(){ return &mStdCir; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： getStarNum
	//
	//  引数 ： < void >
	// 戻り値： < const int >
	//  処理 ： 円周上に並ぶ座標( Star )の数を取得
	//---------------------------------------------------------------------
	const unsigned int *getStarNum(){ return &mSData.setNum; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： getTarget
	//
	//  引数 ： < void >
	// 戻り値： < const unsigned int >
	//  処理 ： 基準位置のStarの添え字を取得
	//---------------------------------------------------------------------
	const unsigned int *getTarget(){ return &mSData.Target; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： getTurnDirection
	//
	//  引数 ： < void >
	// 戻り値： < const int >
	//  処理 ： 回転方向、-1, 0, 1で指定
	//---------------------------------------------------------------------
	const int *getTurnDirection(){ return &mTData.TurnVec; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： nowTurn
	//
	//  引数 ： < void >
	// 戻り値： < const bool >
	//  処理 ： 回転してるかどうか、trueで回転中
	//---------------------------------------------------------------------
	const bool *nowTurn(){ return &mTData.InputLock; }

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： getStarPos
	//
	//  引数 ： < const int >
	// 戻り値： < const StarData >
	//  処理 ： Starの座標を取得
	//---------------------------------------------------------------------
	const HVector2* getStarPos( const int idx ){ return &mSData.Pos[ idx ]; }

private:

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： ResetDeg
	//
	//  引数 ： < const int target >
	// 戻り値： < void >
	//  処理 ： 基準座標に引数指定のStarをセットする
	//---------------------------------------------------------------------
	void ResetDeg( const unsigned int *target );

	//---------------------------------------------------------------------
	// < 2011/10/21 Keisuke_Hosoda >
	//
	// 関数名： calcAngle
	//
	//  引数 ： < void >
	// 戻り値： < void >
	//  処理 ： 円周上の点を等間隔に並べるための角度を計算。
	//    基準点から見て最適な角度に調整する。
	//    増減させるたびに一度だけ呼ぶ。
	//---------------------------------------------------------------------
	void calcAngle();
};

#endif

//=============================================================================
//								End of File
//=============================================================================