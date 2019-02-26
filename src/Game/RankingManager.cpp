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


/*! @par include */
#include "stdafx.h"
#include	"DT_RankingManager.h"	/* For DynamicTracer-TestPoint */
#include "./RankingManager.h"
#include "./../Network/NetworkHelper.h"
#include "./../Utility/File.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <time.h>


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::RankingManager
	
	�f�t�H���g�R���X�g���N�^
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
RankingManager::RankingManager()
{
	__DtTestPoint( __DtFunc_RankingManager, __DtStep_0 )
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::~RankingManager
	
	�f�X�g���N�^
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
RankingManager::~RankingManager()
{
	__DtTestPoint( __DtFunc_RankingManager, __DtStep_1 )
	this->Release();
	__DtTestPoint( __DtFunc_RankingManager, __DtStep_2 )
}


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
bool RankingManager::Initialize()
{
	__DtTestPoint( __DtFunc_Initialize, __DtStep_0 )
	this->Release();

	//SocketManager::getInstance()->Initialize();

	__DtTestPoint( __DtFunc_Initialize, __DtStep_1 )
	return true;
}


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
bool RankingManager::Release()
{
	__DtTestPoint( __DtFunc_Release, __DtStep_0 )
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetStoryRanking
	
	�X�g�[���[���[�h�̃����L���O���擾����
	
	@param[in]      int nRankingNum_     - �擾��
	@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetStoryRanking(int nRankingNum_)
{
	//������
	SOCKET hSock = INVALID_SOCKET;
	sockaddr_in stServerAddr;
	__DtTestPoint( __DtFunc_GetStoryRanking, __DtStep_0 )
	std::list<ScoreData> liRes;

	::memset(&stServerAddr,NULL,sizeof(stServerAddr));

	//�\�P�b�g�쐬
	if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		return liRes;

	//�ڑ���ݒ�
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = ::htons(80);

	hostent* stHost = ::gethostbyname(scg_szScoreServerName);
	if(!stHost)
		return liRes;

	if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
		return liRes;

	//�T�[�o�ɐڑ�
	if(!NetworkHelper::getInstance()->ConnectEx(hSock,stServerAddr,5000))
	{
		__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_1)
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		__DtTestPoint( __DtFunc_GetStoryRanking, __DtStep_2 )
		return liRes;
	}

	//�T�[�o��HTTP���N�G�X�g�𑗐M���A�����L���O���擾����
	static const char sc_szRequest[] = "GET /ota-gamepg/lastvalfirle/storyscore.php HTTP/1.1\r\nHost: www.aleibar.net\r\nConnection: close\r\n\r\n";

	if(::send(hSock,sc_szRequest,sizeof(sc_szRequest),0) < 0)
	{
		__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_3)
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		__DtTestPoint( __DtFunc_GetStoryRanking, __DtStep_4 )
		return liRes;
	}

	//�T�[�o����̉�������M
	int nRecvSize = 0,nDone = 0,cnt = 0;
	std::vector<char> vcRecvBuffer;
	const int c_nRecvBufferSize = ETHERNET_MTU;

	do
	{
		__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_5)
		++cnt;
		vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

		nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

		if(nRecvSize <= 0)
			break;

		nDone += nRecvSize;
	}while(nRecvSize >= c_nRecvBufferSize);

	//�\�P�b�g�̉��
	::shutdown(hSock,SD_BOTH);
	::closesocket(hSock);
		
	//���X�|���X�̉��
	std::string strRes = &vcRecvBuffer[0];
	ScoreData stBuf;
	char szBuf[128];
	std::stringstream ss;
	unsigned int nIndex = 0,nEndIndex = 0,nStrDone = 0;

	::memset(&stBuf,'\0',sizeof(stBuf));
	::memset(&szBuf,'\0',sizeof(szBuf));

	for(int i = 0;i < nRankingNum_;++i)
	{
		__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_6)
		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&stBuf,'\0',sizeof(stBuf));
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Name="����������
		if((nIndex = strRes.find(scg_szNameRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Name="�������Z
		nIndex += sizeof(scg_szNameRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_7)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���\���̂ɃR�s�[
		if(::memcpy_s(&stBuf.szName,sizeof(stBuf.szName),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Score="����������
		if((nIndex = strRes.find(scg_szScoreRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Score="�������Z
		nIndex += sizeof(scg_szScoreRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_8)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���o�b�t�@�ɃR�s�[
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//�����񂩂琔�l�ɕϊ�
		ss << szBuf;
		ss >> stBuf.unScore;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Time="����������
		if((nIndex = strRes.find(scg_szTimeRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Time="�������Z
		nIndex += sizeof(scg_szTimeRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_9)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���o�b�t�@�ɃR�s�[
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//�����񂩂琔�l�ɕϊ�
		ss << szBuf;
		ss >> stBuf.unTime;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Stage="����������
		if((nIndex = strRes.find(scg_szStageRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Stage="�������Z
		nIndex += sizeof(scg_szStageRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_10)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���o�b�t�@�ɃR�s�[
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//�����񂩂琔�l�ɕϊ�
		ss << szBuf;
		ss >> stBuf.nStage;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Date="����������
		if((nIndex = strRes.find(scg_szDateRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Date="�������Z
		nIndex += sizeof(scg_szDateRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_11)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���\���̂ɃR�s�[
		if(::memcpy_s(&stBuf.szDate,sizeof(stBuf.szDate),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Rank="����������
		if((nIndex = strRes.find(scg_szRankRefPoint)) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Rank="�������Z
		nIndex += sizeof(scg_szRankRefPoint) - 1;

		//��؂�ł���' '��������܂ő�����
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			__DtTestPoint(__DtFunc_GetStoryRanking, __DtStep_12)
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//���������O���o�b�t�@�ɃR�s�[
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//�����񂩂琔�l�ɕϊ�
		ss << szBuf;
		ss >> stBuf.nRank;

		/*-----------------------------------------------------------------*/

		//���̃X�R�A�Ɉڂ�
		//"<br />"����������
		if((nIndex = strRes.find("<br />")) == std::string::npos)
			return liRes;

		//�������ꂽ�l��"Name="�������Z
		nIndex += sizeof("<br />") - 1;
		nStrDone += nIndex;

		strRes = &vcRecvBuffer[nStrDone];

		liRes.push_back(stBuf);
	}

	__DtTestPoint( __DtFunc_GetStoryRanking, __DtStep_13 )
	return liRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetSurvivalRanking
	
	�T�o�C�o�����[�h�̃����L���O���擾����
	
	@param[in]      int nRankingNum_     - �擾��
	@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetSurvivalRanking(int nRankingNum_)
{
	__DtTestPoint( __DtFunc_GetSurvivalRanking, __DtStep_0 )
	std::list<ScoreData> liRes;

	__DtTestPoint( __DtFunc_GetSurvivalRanking, __DtStep_1 )
	return liRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetLocalStoryRanking
	
	�X�g�[���[���[�h�̃��[�J�������L���O���擾����
	
	@param[in]      int nRankingNum_     - �擾��
	@return         std::list<ScoreData> - �X�R�A�f�[�^���X�g
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetLocalStoryRanking(int nRankingNum_)
{
	__DtTestPoint( __DtFunc_GetLocalStoryRanking, __DtStep_0 )
	std::list<ScoreData> liRes;

	JZX::File *pFile = new JZX::File(scg_szRankingFileName,"rb");

	if(!pFile)
	{
		__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_1)
		SAFE_DELETE(pFile);
		__DtTestPoint( __DtFunc_GetLocalStoryRanking, __DtStep_2 )
		return liRes;
	}

	if(pFile->getFileParam() != JZX::FILE_OPEN_SUCCEED)
	{
		__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_3)
		SAFE_DELETE(pFile);
		__DtTestPoint( __DtFunc_GetLocalStoryRanking, __DtStep_4 )
		return liRes;
	}

	char szBuf[256],szTemp[256];
	std::string str = szBuf;
	unsigned int unIndex = 0;
	ScoreData stData;

	::memset(szBuf,'\0',256);
	::memset(szTemp,'\0',256);

	while(::fgets(szBuf,256,pFile->getFile()))
	{
		//1�s�I���܂ŏ�������
		__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_5)
		for(int i = 0;i < 6;++i)
		{
			std::string str = szBuf;

			__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_6)
			if((unIndex = str.find(',')) == std::string::npos)
				break;
		
			switch(i)
			{
			case 0:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_7)
				::memcpy_s(&stData.szName[0],128,str.c_str(),unIndex);
				stData.szName[unIndex] = '\0';
				break;

			case 1:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_8)
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.unScore = static_cast<unsigned int>(atoi(szTemp));
				break;

			case 2:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_9)
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.nStage = atoi(szTemp);
				break;

			case 3:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_10)
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.unTime = static_cast<unsigned int>(atoi(szTemp));
				break;

			case 4:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_11)
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.nRank = atoi(szTemp);
				break;

			case 5:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_12)
				::memcpy_s(&stData.szDate[0],32,str.c_str(),unIndex);
				stData.szDate[unIndex] = '\0';
				break;

			default:
				__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_13)
				break;
			}

			::memcpy_s(szBuf,256,&szBuf[unIndex + 1],256 - (unIndex + 1));
			::memset(szTemp,'\0',256);
		}

		liRes.push_back(stData);

		::memset(szBuf,'\0',256);
		::memset(szTemp,'\0',256);
		::memset(&stData,sizeof(stData),NULL);
	}

	liRes.sort(ScoreDesc);

	if(liRes.size() > nRankingNum_)
	{
		__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_14)
		std::list<ScoreData>::iterator itr = liRes.begin();
		for(int i = 0;i < nRankingNum_;++i)
		{
			__DtTestPoint(__DtFunc_GetLocalStoryRanking, __DtStep_15)
			++itr;
		}

		liRes.erase(itr,liRes.end());
	}

	pFile->Close();
	SAFE_DELETE(pFile);

	__DtTestPoint( __DtFunc_GetLocalStoryRanking, __DtStep_16 )
	return liRes;
}


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
bool RankingManager::PostStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	//������
	SOCKET hSock = INVALID_SOCKET;
	sockaddr_in stServerAddr;
	__DtTestPoint( __DtFunc_PostStoryScore, __DtStep_0 )
	std::list<ScoreData> liRes;

	::memset(&stServerAddr,NULL,sizeof(stServerAddr));

	//�\�P�b�g�쐬
	if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		return false;

	//�ڑ���ݒ�
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = ::htons(80);

	hostent* stHost = ::gethostbyname(scg_szScoreServerName);
	if(!stHost)
		return false;

	if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
		return false;

	//�T�[�o�ɐڑ�
	if(!NetworkHelper::getInstance()->ConnectEx(hSock,stServerAddr,5000))
	{
		__DtTestPoint(__DtFunc_PostStoryScore, __DtStep_1)
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		__DtTestPoint( __DtFunc_PostStoryScore, __DtStep_2 )
		return false;
	}

	//�T�[�o��HTTP���N�G�X�g�𑗐M���A�X�R�A��o�^����
	std::string strBuf,strBody;
	char szBuf[256];
	::memset(&szBuf[0],'\0',sizeof(szBuf));

	strBody += "Name=";
	strBody += pszName_;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%u",unScore_);
	strBody += "Score=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%d",nStage_);
	strBody += "Stage=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%u",unTime_);
	strBody += "Time=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%d",nRank_);
	strBody += "Rank=";
	strBody += szBuf;
	strBody += "\r\n";

	::sprintf_s(&szBuf[0],sizeof(szBuf),"POST /ota-gamepg/lastvalfirle/storyscore.php HTTP/1.1\r\nHost: www.aleibar.net\r\nContent-type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",strBody.length());
	strBuf = szBuf;
	strBuf += strBody;

	if(::send(hSock,strBuf.c_str(),strBuf.size(),0) < 0)
	{
		__DtTestPoint(__DtFunc_PostStoryScore, __DtStep_3)
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		__DtTestPoint( __DtFunc_PostStoryScore, __DtStep_4 )
		return false;
	}

	//�T�[�o����̉�������M
	int nRecvSize = 0,nDone = 0,cnt = 0;
	std::vector<char> vcRecvBuffer;
	const int c_nRecvBufferSize = ETHERNET_MTU;

	do
	{
		__DtTestPoint(__DtFunc_PostStoryScore, __DtStep_5)
		++cnt;
		vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

		nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

		if(nRecvSize <= 0)
			break;

		nDone += nRecvSize;
	}while(nRecvSize >= c_nRecvBufferSize);

	//�\�P�b�g�̉��
	::shutdown(hSock,SD_BOTH);
	::closesocket(hSock);
		
	//���X�|���X�̉��
	for(int i = 0;i < nDone;++i)
	{
		__DtTestPoint(__DtFunc_PostStoryScore, __DtStep_6)
		std::cout << vcRecvBuffer[i];
	}

	__DtTestPoint( __DtFunc_PostStoryScore, __DtStep_7 )
	return true;
}


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
bool RankingManager::PostSurvivalScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	__DtTestPoint( __DtFunc_PostSurvivalScore, __DtStep_0 )
	return true;
}


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
bool RankingManager::PostLocalStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	__DtTestPoint( __DtFunc_PostLocalStoryScore, __DtStep_0 )
	JZX::File *pFile = new JZX::File(scg_szRankingFileName,"ab+");

	if(!pFile)
	{
		__DtTestPoint(__DtFunc_PostLocalStoryScore, __DtStep_1)
		SAFE_DELETE(pFile);
		__DtTestPoint( __DtFunc_PostLocalStoryScore, __DtStep_2 )
		return false;
	}

	if(pFile->getFileParam() != JZX::FILE_OPEN_SUCCEED)
	{
		__DtTestPoint(__DtFunc_PostLocalStoryScore, __DtStep_3)
		SAFE_DELETE(pFile);
		__DtTestPoint( __DtFunc_PostLocalStoryScore, __DtStep_4 )
		return false;
	}

	//���t���擾
    time_t unTimer = 0;
    tm *stDate = NULL;
    char szBuf[256];

	::memset(szBuf,'\0',256);

    unTimer = ::time(NULL);
    stDate = ::localtime(&unTimer);
    strftime(szBuf,255,"%Y-%b-%d %I:%M:%S",stDate);

	//�t�@�C���o��
	::fprintf_s(pFile->getFile(),"%s,%u,%d,%u,%d,%s,\r\n",pszName_,unScore_,nStage_,unTime_,nRank_,szBuf);

	pFile->Close();
	SAFE_DELETE(pFile);

	__DtTestPoint( __DtFunc_PostLocalStoryScore, __DtStep_5 )
	return true;
}


bool ScoreDesc(const ScoreData &a_,const ScoreData &b_)
{
	__DtTestPoint( __DtFunc_ScoreDesc, __DtStep_0 )
	return a_.unScore > b_.unScore;
}



//=============================================================================
//								End of File
//=============================================================================