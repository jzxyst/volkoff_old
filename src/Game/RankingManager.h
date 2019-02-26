//=============================================================================
/*! 
    @addtogroup 
    @file       RankingManager.h
    @brief      RankingManager�N���X�w�b�_
    
    �����L���O�T�[�o�ɐڑ����A�X�R�A�Ɋւ��鏈�����s���N���X
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/22
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/22 Hi-ra Mizuno
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_RANKING_MANAGER_H__
#define __INCLUDE_RANKING_MANAGER_H__


/*! @par include */
#include <winsock2.h>
#include <list>


/*! @val global */
static const char scg_szScoreServerName[] = "www.aleibar.net";
static const char scg_szNameRefPoint[] = "Name=";
static const char scg_szScoreRefPoint[] = "Score=";
static const char scg_szTimeRefPoint[] = "Time=";
static const char scg_szStageRefPoint[] = "Stage=";
static const char scg_szDateRefPoint[] = "Date=";
static const char scg_szRankRefPoint[] = "Rank=";

static const char scg_szRankingFileName[] = "ranking.dat";


/*! @par struct */
typedef struct _TAG_SCORE_DATA
{
	char szName[128];
	unsigned int unScore;
	unsigned int unTime;
	int nStage;
	char szDate[32];
	int nRank;
}ScoreData;


/*! @class RankingManager
	@brief RankingManager�N���X

	�����L���O�T�[�o�ɐڑ����A�X�R�A�Ɋւ��鏈�����s���N���X

*/
class RankingManager
{
public:
	/*! @par public�����o�ϐ� */

private:
	/*! @par private�����o�ϐ� */

public:
	/*! @par ��O���� */


private:
	/*! @par �R���X�g���N�^�E�f�X�g���N�^ */
	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::RankingManager
	
		�f�t�H���g�R���X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	RankingManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::~RankingManager
	
		�f�X�g���N�^
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~RankingManager();

public:
	/*! @par public�����o�֐� */
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::getInstance
	
		�C���X�^���X���擾����
	
		@param[in]      void
		@return         RankingManager* - �C���X�^���X�|�C���^
		@exception      none
	*/
	//---------------------------------------------------------------------------
	static RankingManager* getInstance() {static RankingManager CInstance; return &CInstance;};

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::Initialize
	
		����������
	
		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::Release
	
		�I������
	
		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetStoryRanking
	
		�X�g�[���[���[�h�̃����L���O���擾����
	
		@param[in]      int nRankingNum_     - �擾��
		@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetStoryRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetSurvivalRanking
	
		�T�o�C�o�����[�h�̃����L���O���擾����
	
		@param[in]      int nRankingNum_     - �擾��
		@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetSurvivalRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetLocalStoryRanking
	
		�X�g�[���[���[�h�̃��[�J�������L���O���擾����
	
		@param[in]      int nRankingNum_     - �擾��
		@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetLocalStoryRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostStoryScore
	
		�X�g�[���[���[�h�̃X�R�A�f�[�^�𑗐M����
	
		@param[in]      char         *pszName_ - ���O
		@param[in]      unsigned int unScore_  - �X�R�A
		@param[in]      int          nStage_   - �X�e�[�W��
		@param[in]      unsigned int unTime_   - �N���A����
		@param[in]      int          nRank_    - ��Փx
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostSurvivalScore
	
		�T�o�C�o�����[�h�̃X�R�A�f�[�^�𑗐M����
	
		@param[in]      char         *pszName_ - ���O
		@param[in]      unsigned int unScore_  - �X�R�A
		@param[in]      int          nStage_   - �X�e�[�W��
		@param[in]      unsigned int unTime_   - �N���A����
		@param[in]      int          nRank_    - ��Փx
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostSurvivalScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostLocalStoryScore
	
		�X�g�[���[���[�h�̃X�R�A�f�[�^�����[�J���ɏ�������
	
		@param[in]      char         *pszName_ - ���O
		@param[in]      unsigned int unScore_  - �X�R�A
		@param[in]      int          nStage_   - �X�e�[�W��
		@param[in]      unsigned int unTime_   - �N���A����
		@param[in]      int          nRank_    - ��Փx
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostLocalStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);
};


bool ScoreDesc(const ScoreData &a_,const ScoreData &b_);


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================