//=============================================================================
/*! 
    @addtogroup 
    @file       GameObjectManager.cpp
    @brief      
    
    GameObjectManagerクラスの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include	"DT_GameObjectManager.h"	/* For DynamicTracer-TestPoint */
#include "./GameObjectManager.h"
#include "./GameObject.h"
#include "./../Game/GameManager.h"
#include "./Player.h"
#include "./../Object/Weapon.h"

#include "../Utility/Util.h"

//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::GameObjectManager

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GameObjectManager::GameObjectManager()
    : m_unNextHandle        ( 1 )
    , mUsingEventQueueIndex ( 0 )
{
    __DtTestPoint( __DtFunc_GameObjectManager, __DtStep_0 )
    for ( int i = 0; i < MAX_MSG_QUEUES; ++i )
    {
        __DtTestPoint(__DtFunc_GameObjectManager, __DtStep_1)
        mEventQueueArray[ i ].setCapacity( MSGQUEUE_SIZE );
    }
	__DtTestPoint( __DtFunc_GameObjectManager, __DtStep_2 )
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::~GameObjectManager

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GameObjectManager::~GameObjectManager()
{
	__DtTestPoint( __DtFunc_GameObjectManager, __DtStep_3 )
	this->Release();
	__DtTestPoint( __DtFunc_GameObjectManager, __DtStep_4 )
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool GameObjectManager::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool GameObjectManager::Release()
{
    

	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	while(!this->m_dqObjectList.empty())
	{
		__DtTestPoint(__DtFunc_Release, __DtStep_1)
		SAFE_DELETE(this->m_dqObjectList.front());
		this->m_dqObjectList.pop_front();
	}

	if (!m_dqTempList.empty())
	{
		__DtTestPoint(__DtFunc_Release, __DtStep_2)
		ln_foreach(GameObject* obj, m_dqTempList)
		{
			SAFE_DELETE(obj);
		}
		m_dqTempList.clear();
	}

	__DtTestPoint( __DtFunc_Release, __DtStep_3 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Update

	フレーム更新処理

	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void GameObjectManager::Update()
{
    //_p(m_dqObjectList.size() );

    GameObjectList::iterator itr = this->m_dqObjectList.begin();
    GameObjectList::iterator end = this->m_dqObjectList.end();
	__DtTestPoint( __DtFunc_Update, __DtStep_0 )
	for(;itr != end; )
	{
		//マップ外に出てしまったオブジェクトを強制的に初期座標に移動する
		__DtTestPoint(__DtFunc_Update, __DtStep_1)
		if(((*itr)->getPosition().x < 0) || ((*itr)->getPosition().x >= 2000) || ((*itr)->getPosition().y < 0) || ((*itr)->getPosition().y >= 2000))
		{
			__DtTestPoint(__DtFunc_Update, __DtStep_2)
			(*itr)->setPosition((*itr)->getDefPosition());
		}

        //削除フラグ
        if((*itr)->getExit())
		{
            //printf( "Delete %d\n", (*itr)->getHandle() );
            // map からも取り除く
            __DtTestPoint(__DtFunc_Update, __DtStep_3)
            m_mObjectMap.erase( (*itr)->getHandle() );

            // [yama] 先頭を削除していいのか不安なので書き換え
			//SAFE_DELETE(this->m_dqObjectList.front());

            SAFE_DELETE((*itr));

			itr = this->m_dqObjectList.erase(itr);
        }
        else
        {
		    __DtTestPoint(__DtFunc_Update, __DtStep_4)
		    (*itr)->Update();

            (*itr)->UpdateSelf();

            ++itr;
        }
	}


 

    // キューにあるイベントを処理する
    int   size;
    char* data;

    for ( int i = 0; i <= mUsingEventQueueIndex; ++i )
    {
        __DtTestPoint(__DtFunc_Update, __DtStep_5)
        LNote::Utility::MessageQueue& msg_queue = mEventQueueArray[ i ];

        while ( !msg_queue.empty() )
        {
           

            __DtTestPoint(__DtFunc_Update, __DtStep_6)
            msg_queue.top( (void**)&data, &size );
            msg_queue.pop();

            EventHeader* header = reinterpret_cast< EventHeader* >( data );
			// printf("これ:%d\n",header->ObjectHandle);

            // 単一のオブジェクトに送信する場合
            if ( header->ObjectHandle != 0xffffffff )
            {
                __DtTestPoint(__DtFunc_Update, __DtStep_7)
                sendEvent( header->ObjectHandle, header->Type, &data[ sizeof( EventHeader ) ], header->ArgSize );
            }

            itr = this->m_dqObjectList.begin();

        }

        msg_queue.clear();
    }


    GameObjectList::iterator titr = this->m_dqTempList.begin();
    GameObjectList::iterator tend = this->m_dqTempList.end();
	for(;titr != tend; )
	{
		__DtTestPoint(__DtFunc_Update, __DtStep_8)
		m_dqObjectList.push_back(*titr);
		m_mObjectMap.insert( GameObjectPair((*titr)->getHandle(), *titr) );
		++titr;
	}
	m_dqTempList.clear();

	__DtTestPoint( __DtFunc_Update, __DtStep_9 )
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::AddObject

	リスナーをリストに追加する

	@param[in]      GameObject *pCObj 追加するオブジェクトポインタ
	@return         追加されたオブジェクトに割り当てられたハンドル (gatHandle() で得られるものと同じ)
	@exception      none
*/
//---------------------------------------------------------------------------
u32 GameObjectManager::AddObject(GameObject *pCObj)
{
    __DtTestPoint( __DtFunc_AddObject, __DtStep_0 )
    pCObj->setHandle(m_unNextHandle);

	//TempListに移動
	m_dqTempList.push_back(pCObj);
    //m_dqObjectList.push_back(pCObj);
    //m_mObjectMap.insert( GameObjectPair(m_unNextHandle, pCObj) );

    ++m_unNextHandle;

	__DtTestPoint( __DtFunc_AddObject, __DtStep_1 )
	return m_unNextHandle;
}


//---------------------------------------------------------------------
// ● オブジェクトを削除する
//---------------------------------------------------------------------
void GameObjectManager::deleteObject( GameObject* obj_ )
{
    __DtTestPoint( __DtFunc_deleteObject, __DtStep_0 )
    obj_->setExit( true );
    //obj_->mExit = true;

    //printf( "deleteObject %p\n", obj_ );

    // Update 内などでイテレート中に RemoveObject() が呼ばれるとよろしくない。

    //SAFE_DELETE( obj_ );
	__DtTestPoint( __DtFunc_deleteObject, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 攻撃の関係するオブジェクトを追加する (AttackedObject のコンストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameObjectManager::addAttackedObject( AttackedObject* obj_ )
{
    __DtTestPoint( __DtFunc_addAttackedObject, __DtStep_0 )
    mAttackedObjectList.push_back( obj_ );
	__DtTestPoint( __DtFunc_addAttackedObject, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● 攻撃の関係するオブジェクトを外す (AttackedObject のデストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameObjectManager::removeAttackedObject( AttackedObject* obj_ )
{
    __DtTestPoint( __DtFunc_removeAttackedObject, __DtStep_0 )
    mAttackedObjectList.remove( obj_ );
	__DtTestPoint( __DtFunc_removeAttackedObject, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● オブジェクトを検索する
//---------------------------------------------------------------------
GameObject* GameObjectManager::findObject( u32 handle_ )
{
    GameObjectMap::iterator it = m_mObjectMap.find( handle_ );
    __DtTestPoint( __DtFunc_findObject, __DtStep_0 )
    if ( it != m_mObjectMap.end() )
    {
        // 削除されようとしている場合は検索に引っかからない
        __DtTestPoint(__DtFunc_findObject, __DtStep_1)
        if ( it->second->getExit() )
        {
            __DtTestPoint( __DtFunc_findObject, __DtStep_2 )
            return NULL;
        }

        __DtTestPoint( __DtFunc_findObject, __DtStep_3 )
        return it->second;
    }
    __DtTestPoint( __DtFunc_findObject, __DtStep_4 )
    return NULL;
}

//---------------------------------------------------------------------
// ● 指定したハンドルを持つオブジェクトにイベントを送信する (キューイング無し)
//---------------------------------------------------------------------
void GameObjectManager::sendEvent( u32 handle_, u32 event_, void* data_, u32 size_ )
{
    GameObjectMap::iterator it = m_mObjectMap.find( handle_ );
    __DtTestPoint( __DtFunc_sendEvent, __DtStep_0 )
    if ( it != m_mObjectMap.end() )
    {
        __DtTestPoint(__DtFunc_sendEvent, __DtStep_1)
        it->second->HandleEvent( event_, data_ );
    }
	__DtTestPoint( __DtFunc_sendEvent, __DtStep_2 )
}

//---------------------------------------------------------------------
// ● 指定したハンドルを持つオブジェクトにイベントを送信する (キューイングあり)
//---------------------------------------------------------------------
void GameObjectManager::postEvent( u32 handle_, u32 event_, void* data_, u32 size_ )
{
	// Debug
	// static int a = 0;
	// a++;
	// ::printf("回数：%d イベント番号:%d 送り先番号:%d\n",a,event_,handle_);

	// ヘッダを作る
    EventHeader header;
    __DtTestPoint( __DtFunc_postEvent, __DtStep_0 )
    header.Type         = event_;
    header.ObjectHandle = handle_;
    header.ArgSize      = size_;

    // 一度 mTempBuffer に全て格納
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );

    // キューにコピー
    mEventQueueArray[ mUsingEventQueueIndex ].push( mTempBuffer, sizeof( EventHeader ) + size_ );
	__DtTestPoint( __DtFunc_postEvent, __DtStep_1 )
}

//---------------------------------------------------------------------
// ● AttackedObject ととの当たり判定を行う
//---------------------------------------------------------------------
HitObjectList* GameObjectManager::judgeCollitionToAttackedObject( const LRect& rect_, u32 target_group_ )
{
    __DtTestPoint( __DtFunc_judgeCollitionToAttackedObject, __DtStep_0 )
    mHitObjectList.clear();

    /*
    const LRect* rc;
    int l0, t0, r0, b0;
    int l1, t1, r1, b1;

    l0 = rect_.x;
    t0 = rect_.y - rect_.height;
    b0 = rect_.y;
    r0 = rect_.x + rect_.width;
    */
	const LRect* rect2;

    AttackedObjectList::iterator itr = mAttackedObjectList.begin();
    AttackedObjectList::iterator end = mAttackedObjectList.end();
    for ( ; itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_judgeCollitionToAttackedObject, __DtStep_1)
        if ( target_group_ & (*itr)->getAttackedGroup() && !(*itr)->isDead() )
        {
            //rect_.dump();
            //(*itr)->getAttackedCollisionRect()->dump();
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->x);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->y);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->width);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->height);

            /*
            rc = (*itr)->getAttackedCollisionRect();
            l1 = rc->x;
            t1 = rc->y - rc->height;
            b1 = rc->y;
            r1 = rc->x + rc->width;
            */

            

		    //if((rect_.x<=(*itr)->getAttackedCollisionRect()->x+(*itr)->getAttackedCollisionRect()->width)&&((*itr)->getAttackedCollisionRect()->x<=rect_.x+rect_.width)&&(rect_.y<=(*itr)->getAttackedCollisionRect()->y+(*itr)->getAttackedCollisionRect()->height)&&((*itr)->getAttackedCollisionRect()->y<=rect_.y+rect_.height))
            
            //printf( "%d <= %d && %d >= %d && %d >= %d && %d <= %d\n", l0, r1, r0, l1, t0, b1, b0, t1 );
            
            /*
            if ( l0 <= r1 && r0 >= l1 && t0 <= b1 && b0 >= t1 )
            {
                mHitObjectList.push_back( (*itr) );
            }
            */
			__DtTestPoint(__DtFunc_judgeCollitionToAttackedObject, __DtStep_2)
			rect2 = (*itr)->getAttackedCollisionRect();
			if ( rect2 ) 
			{
				__DtTestPoint(__DtFunc_judgeCollitionToAttackedObject, __DtStep_3)
				if ( Util::judgeCollitionRect( rect_, *rect2 ) )
				{
					__DtTestPoint(__DtFunc_judgeCollitionToAttackedObject, __DtStep_4)
					mHitObjectList.push_back( (*itr) );
				}
			}
        }
    }  
    
    __DtTestPoint( __DtFunc_judgeCollitionToAttackedObject, __DtStep_5 )
    return &mHitObjectList;
}

//---------------------------------------------------------------------
// ● 指定した種類のオブジェクトと当たり判定を行う
//---------------------------------------------------------------------
u32 GameObjectManager::judgeCollitionTypeSpecified( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ )
{
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();

    // ひとつの種類との判定
    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecified, __DtStep_0 )
    if ( target_type_end_ == OBJ_UNDEF )
    {
        __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_1)
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_2)
            if ( (*itr)->getObjType() == target_type_ )
            {
                __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_3)
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecified, __DtStep_4 )
                    return (*itr)->getHandle();
                }
            }
        }
    }
    // 複数の種類との判定
    else
    {
        __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_5)
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_6)
            if ( target_type_ <= (*itr)->getObjType() && (*itr)->getObjType() <= target_type_end_ )
            {
                __DtTestPoint(__DtFunc_judgeCollitionTypeSpecified, __DtStep_7)
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecified, __DtStep_8 )
                    return (*itr)->getHandle();
                }
            }
        }
    }
    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecified, __DtStep_9 )
    return 0;
}

//---------------------------------------------------------------------
///**
//  @brief      指定した種類のオブジェクトと当たり判定を行ったのちに消去する
//
//  @param[in]  rect_             : ワールド座標上の矩形
//  @param[in]  target_type_      : 対象の種類
//  @param[in]  target_type_end_  : 対象の種類
//
//  @return     当たったオブジェクトのハンドル
//
//  @par
//              target_type_end_ は範囲指定する場合に値を渡す。
//              指定した場合、target_type_ 以上、target_type_end_ 以下の
//              種類のオブジェクトと判定を行う。
//*/
//---------------------------------------------------------------------
u32 GameObjectManager::judgeCollitionTypeSpecifiedAndDelete( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ )
{
	GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();

	u32 result = OBJ_UNDEF;

    // ひとつの種類との判定
    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_0 )
    if ( target_type_end_ == OBJ_UNDEF )
    {
        __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_1)
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_2)
            if ( (*itr)->getObjType() == target_type_ )
            {
                __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_3)
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_4)
                    result = (*itr)->getHandle();

                    printf( "● delete h:%d p:%p\n", result, this->findObject( result ) );

					this->deleteObject( *itr );
					break;
                }
            }
        }
    }
    // 複数の種類との判定
    else
    {
        __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_5)
        for ( ; itr != end; ++itr )
        {
            __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_6)
            if ( target_type_ <= (*itr)->getObjType() && (*itr)->getObjType() <= target_type_end_ )
            {
                __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_7)
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    __DtTestPoint(__DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_8)
                    result = (*itr)->getHandle();

                    printf( "● delete h:%d p:%p\n", result, this->findObject( result ) );

					this->deleteObject( *itr );
					break;
                }
            }
        }
    }
    __DtTestPoint( __DtFunc_judgeCollitionTypeSpecifiedAndDelete, __DtStep_9 )
    return result;
}

//
// GameObjectManager::CollisionToObject
//
// @param[u32] obj_type_ : 対象のオブジェクトタイプ
// @param[LRect]   rect_ : 対象の矩形
// @param[LVector2]dist_ : オブジェクトと対象矩形の中心座標の距離
// @param[LVector2] over_: オブジェクトとのめり込み量 (戻すべき距離)
// @return[u32]          : リストの中の当たっていたオブジェクトの種類
//
//    渡された矩形とリスト内の矩形を比較
//    当たっていた場合ObjectTypeを返す
//
u32 GameObjectManager::CollisionToObject( const u32 obj_type_, LRect rect_, LVector2* dist_, LVector2* over_ )
{
    const LRect* rc;

	// [細田]
	GameObjectList::iterator itr = this->m_dqObjectList.begin();
    GameObjectList::iterator end = this->m_dqObjectList.end();

    /*
	LRect player_rect;
	player_rect.set( rect_.x, rect_.y, rect_.width, rect_.height );

   	LRect target_rect;
	

	int distance_x = 0;
	int distance_y = 0;

	int player_worldwidth = player_rect.x + player_rect.width;
	int player_worldheight = player_rect.y - player_rect.height;
    */

    __DtTestPoint( __DtFunc_CollisionToObject, __DtStep_0 )
    dist_->set( 0, 0 );
    over_->set( 0, 0 );

    // 自分のワールド上の左、上、右、下、それらの中心。
    // 上 > 下 な点に注意。下の方が 0 に近い。
    int pl = rect_.x;
    int pt = rect_.y;
    int pr = rect_.x + rect_.w;
    int pb = rect_.y - rect_.h;
    LVector2 pc( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );
    LVector2 start_pc( pc );

	// 失敗したら0, 0を返す
	u32 result = OBJ_UNDEF;



	for ( ; itr != end; ++itr )
	{
		u32 target_type = ( *itr )->getObjType();

		// オブジェクトと指定OBJ以外のオブジェクトとの当たり判定
		__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_1)
		if ( target_type != OBJ_UNDEF
			&& target_type != OBJ_CHARACTER
			&& target_type != OBJ_ENEMY
			&& target_type != OBJ_WEAPON )
        {
            // [山本] NULL 参照回避のため、ちょっと修正
            __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_2)
            rc = ( *itr )->getBoundingRect();
			if ( rc )
			{
                // ターゲットのワールド上の左、上、右、下、それらの中心。
                int tl = rc->x;
                int tt = rc->y;
                int tr = rc->x + rc->w;
                int tb = rc->y - rc->h;
                LVector2 tc( tl + ( tr - tl ) / 2, tb + ( tt - tb ) / 2 );

                //printf( "p %d %d %d %d\n", pl, pt, pr, pb );
                //printf( "t %d %d %d %d\n", tl, tt, tr, tb );

                bool is_col_width  = ( pl <= tr && pr >= tl );  // 左右が当たっているかチェック
                bool is_col_height = ( pt >= tb && pb <= tt );  // 上下が当たっているかチェック

                // 当たっている場合
                __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_3)
                if ( is_col_width && is_col_height )
                {
                    __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_4)
                    result = target_type;

                    

                    // 横からぶつかった場合など、縦よりも横の差の方が大きい場合
                    if ( abs( pc.x - tc.x ) > abs( pc.y - tc.y ) )
                    {
                        // 自分が対象の左にいる場合
                        __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_5)
                        if ( pc.x < tc.x )
                        {
                            __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_6)
                            over_->x = tl - pr - 1;     // この値はマイナスになる
                        }
                        // 自分が対象の右にいる場合
                        else
                        {
                            __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_7)
                            over_->x = tr - pl + 1;     // この値はプラスになる
                        }
                    }
                    // 上から乗った場合など、横よりも縦の差の方が大きい場合
                    else
                    {
                        // 自分が対象の下にいる場合
                        __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_8)
                        if ( pc.y < tc.y )
                        {
                            __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_9)
                            over_->y = tb - pt;     // この値はマイナスになる
                        }
                        // 自分が対象の上にいる場合
                        else
                        {
                            __DtTestPoint(__DtFunc_CollisionToObject, __DtStep_10)
                            over_->y = tt - pb;     // この値はプラスになる
                        }
                    }

                    
                    // 二つの中心座標の距離
                    dist_->set( tc.x - pc.x, tc.y - pc.y );

                    break;

                    /*
                    //dist_->x += tc.x - pc.x;
                    //dist_->y += tc.y - pc.y;


                    if ( target_type == OBJ_BOX )
                    {
                        //rect_.x += dist_->x;
                        //rect_.y += dist_->y;

                        


                        pl = pl + over_->x;
                        pt = pt + over_->y;
                        pr = pl + rect_.width;
                        pb = pt - rect_.height;
                        pc.set( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );

                        over_->set( pc.x - start_pc.x, pc.y - start_pc.y );

                        over_->dump();

                        
                    }
                    else
                    {
                        break;
                    }
                    */
                }
                

                

                /*

                target_rect = *rc;

				// 改訂後
				int target_worldwidth  = target_rect.x + target_rect.width;
				int target_worldheight = target_rect.y - target_rect.height;

				bool hit_side = false;
				bool hit_height = false;

				// プレイヤが右 obj		->	player
				if ( target_rect.x <= player_rect.x
					&& player_rect.x <= target_worldwidth )
				{
					over_->x = static_cast< float >( player_rect.x - target_worldwidth );
					dist_->x = static_cast< float >(
						( target_rect.x + target_rect.width*0.5f )
						- ( player_rect.x + player_rect.width*0.5f ) );
					hit_side = true;
				}
				// プレイヤが左 player	<-	obj
				else if ( player_rect.x < target_rect.x
					&& target_rect.x < player_worldwidth )
				{
					over_->x = static_cast< float >( player_worldwidth - target_rect.x );
					dist_->x = static_cast< float >(
						( target_rect.x + target_rect.width*0.5f )
						- ( player_rect.x + player_rect.width*0.5f ) );
					hit_side = true;
				}

				if ( hit_side )
				{
					// プレイヤが上
					if ( target_rect.y <= player_rect.y
						&& player_worldheight <= target_rect.y )
					{
						over_->y = static_cast< float >( player_worldheight - target_rect.y );
						dist_->y = static_cast< float >(
							( player_rect.y - player_rect.height*0.5f )
							- ( target_rect.y - target_rect.height*0.5f ) );
						hit_height = true;
					}
					// プレイヤが下
					else if ( player_rect.y <= target_rect.y
						&& target_worldheight <= player_rect.y )
					{
						over_->y = static_cast< float >( target_worldheight - player_rect.y );
						dist_->y = static_cast< float >(
							( target_rect.y - target_rect.height*0.5f )
							- ( player_rect.y - player_rect.height*0.5f ) );
						hit_height = true;
					}

					if ( hit_height )
					{
						break;
					}
				}
                */
			}
		}
		/*else
		{
			result = OBJ_UNDEF;
		}*/
	}

	if ( itr != end )
	{
		// プレイヤー専用アイテムに触れていた場合
		__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_11)
		if ( OBJ_ITEM_BEGIN < result && result < OBJ_ITEM_END )
		{
			// プレイヤーは
			__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_12)
			if ( obj_type_ == OBJ_CHARACTER )
			{
				//スコアの処理
				__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_13)
				switch(result)
				{
				case OBJ_CURE_S:
					//GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(500*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1)));          
					__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_14)
					break;
				case OBJ_CURE_M:
					__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_15)
					GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(1000*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1))); 
					break;
				case OBJ_CURE_L:
					__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_16)
					GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(2000*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1))); 
					break;
				}
				//this->deleteObject( *itr );  // オブジェクトを消す
			}
			else // プレイヤー以外は
			{
				__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_17)
				result = OBJ_UNDEF;      // 何にも触れていないとする
			}
		}
	}

	if ( result == OBJ_UNDEF )
	{
		__DtTestPoint(__DtFunc_CollisionToObject, __DtStep_18)
		dist_->set( 0, 0 );
		over_->set( 0, 0 );
	}

	__DtTestPoint( __DtFunc_CollisionToObject, __DtStep_19 )
	return result;
}


//---------------------------------------------------------------------
///**
//  @brief      指定した種類のオブジェクトを削除する
//
//  @param[in]  target_type_  : 対象の種類
//
//  @return     当たったオブジェクトのハンドル
//*/
//---------------------------------------------------------------------
u32 GameObjectManager::removeObject( ObjectType target_type_ )
{
	u32 cnt = 0;
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();
    __DtTestPoint( __DtFunc_removeObject, __DtStep_0 )
    for ( ; itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_removeObject, __DtStep_1)
        if ( (*itr)->getObjType() == target_type_ )
        {
			__DtTestPoint(__DtFunc_removeObject, __DtStep_2)
			++cnt;
			(*itr)->setExit(true);
        }
    }
    __DtTestPoint( __DtFunc_removeObject, __DtStep_3 )
    return cnt;
}


//---------------------------------------------------------------------
///**
//  @brief      プレイヤー以外のオブジェクトを削除する
//
//  @return     
//*/
//---------------------------------------------------------------------
void GameObjectManager::deleteStageObject()
{
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();
    __DtTestPoint( __DtFunc_deleteStageObject, __DtStep_0 )
    for ( ; itr != end; ++itr )
    {
        __DtTestPoint(__DtFunc_deleteStageObject, __DtStep_1)
        if ( (*itr)->getObjType() != OBJ_CHARACTER )
        {
			__DtTestPoint(__DtFunc_deleteStageObject, __DtStep_2)
			(*itr)->setExit(true);
        }
    }
    __DtTestPoint( __DtFunc_deleteStageObject, __DtStep_3 )
    return;
}

//=============================================================================
//								End of File
//=============================================================================
