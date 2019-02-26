//=============================================================================
/*! 
    @addtogroup 
    @file       SceneGame.h
    @brief      
    
    �Q�[���̃��C���ƂȂ�V�[���̒�`
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "../Map/MapManager.h"
#include "../Object/Player.h"


/*! @par global */
static const int scg_nCameraSceneFrame[] = {1,180,360,540};


/*! @class SceneGame
	@brief SceneGame�N���X

	�Q�[���̃��C���ƂȂ�V�[��
*/
class SceneGame : public LGameScene
{
public:

    /// �R���X�g���N�^
    SceneGame();

public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneGame"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:

    MapManager*     mMapManager;

	//Debug
	int mFrameCount;
	int mUBW;
	bool mBeginScene;
    int mBossCollapseCount;
	
};

//=============================================================================
//								End of File
//=============================================================================
