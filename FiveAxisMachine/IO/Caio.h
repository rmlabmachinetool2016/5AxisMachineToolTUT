//==============================================================================================
//	API-AIO(WDM)用定義ファイル																	
//==============================================================================================
//#include <windows.h>
//----------------------------------------------------------------------------------------------
//	外部制御信号																				
//----------------------------------------------------------------------------------------------
#define	AIO_AIF_CLOCK				0	//アナログ入力外部クロック
#define	AIO_AIF_START				1	//アナログ入力外部開始トリガ
#define	AIO_AIF_STOP				2	//アナログ入力外部停止トリガ
#define	AIO_AOF_CLOCK				3	//アナログ出力外部クロック
#define	AIO_AOF_START				4	//アナログ出力外部開始トリガ
#define	AIO_AOF_STOP				5	//アナログ出力外部停止トリガ

//----------------------------------------------------------------------------------------------
//	入出力レンジ																				
//----------------------------------------------------------------------------------------------
#define	PM10						0	//±10V
#define	PM5							1	//±5V
#define	PM25						2	//±2.5V
#define	PM125						3	//±1.25V
#define	PM1							4	//±1V
#define	PM0625						5	//±0.625V
#define	PM05						6	//±0.5V
#define	PM03125						7	//±0.3125V
#define	PM025						8	//±0.25V
#define	PM0125						9	//±0.125V
#define	PM01						10	//±0.1V
#define	PM005						11	//±0.05V
#define	PM0025						12	//±0.025V
#define	PM00125						13	//±0.0125V
#define	PM001						14	//±0.01V
#define	P10							50	//0～10V
#define	P5							51	//0～5V
#define	P4095						52	//0～4.095V
#define	P25							53	//0～2.5V
#define	P125						54	//0～1.25V
#define	P1							55	//0～1V
#define	P05							56	//0～0.5V
#define	P025						57	//0～0.25V
#define	P01							58	//0～0.1V
#define	P005						59	//0～0.05V
#define	P0025						60	//0～0.025V
#define	P00125						61	//0～0.0125V
#define	P001						62	//0～0.01V
#define	P20MA						100	//0～20mA
#define	P4TO20MA					101	//4～20mA
#define	P1TO5						150	//1～5V

//----------------------------------------------------------------------------------------------
//	アナログ入力イベント																		
//----------------------------------------------------------------------------------------------
#define	AIE_START			0x00000002	//AD変換開始条件成立イベント
#define	AIE_RPTEND			0x00000010	//リピート終了イベント
#define	AIE_END				0x00000020	//デバイス動作終了イベント
#define	AIE_DATA_NUM		0x00000080	//指定サンプリング回数格納イベント
#define	AIE_DATA_TSF		0x00000100	//指定転送数毎イベント
#define	AIE_OFERR			0x00010000	//オーバーフローイベント
#define	AIE_SCERR			0x00020000	//サンプリングクロックエラーイベント
#define	AIE_ADERR			0x00040000	//AD変換エラーイベント

//----------------------------------------------------------------------------------------------
//	アナログ出力イベント																		
//----------------------------------------------------------------------------------------------
#define	AOE_START			0x00000002	//DA変換開始条件成立イベント
#define	AOE_RPTEND			0x00000010	//リピート終了イベント
#define	AOE_END				0x00000020	//デバイス動作終了イベント
#define	AOE_DATA_NUM		0x00000080	//指定サンプリング回数出力イベント
#define	AOE_DATA_TSF		0x00000100	//指定転送数毎イベント
#define	AOE_SCERR			0x00020000	//サンプリングクロックエラーイベント
#define	AOE_DAERR			0x00040000	//DA変換エラーイベント

//----------------------------------------------------------------------------------------------
//	カウンタイベント																			
//----------------------------------------------------------------------------------------------
#define	CNTE_DATA_NUM		0x00000010	//比較カウント一致イベント
#define	CNTE_ORERR			0x00010000	//カウントオーバーランイベント
#define	CNTE_ERR			0x00020000	//カウンタ動作エラー

//----------------------------------------------------------------------------------------------
//	タイマイベント																				
//----------------------------------------------------------------------------------------------
#define	TME_INT				0x00000001	//インターバル成立イベント

//----------------------------------------------------------------------------------------------
//	アナログ入力ステータス																		
//----------------------------------------------------------------------------------------------
#define	AIS_BUSY			0x00000001	//デバイス動作中
#define	AIS_START_TRG		0x00000002	//開始トリガ待ち
#define	AIS_DATA_NUM		0x00000010	//指定サンプリング回数格納
#define	AIS_OFERR			0x00010000	//オーバーフロー
#define	AIS_SCERR			0x00020000	//サンプリングクロックエラー
#define	AIS_AIERR			0x00040000	//AD変換エラー
#define	AIS_DRVERR			0x00080000	//ドライバスペックエラー

//----------------------------------------------------------------------------------------------
//	アナログ出力ステータス																		
//----------------------------------------------------------------------------------------------
#define	AOS_BUSY			0x00000001	//デバイス動作中
#define	AOS_START_TRG		0x00000002	//開始トリガ待ち
#define	AOS_DATA_NUM		0x00000010	//指定サンプリング回数出力
#define	AOS_SCERR			0x00020000	//サンプリングクロックエラー
#define	AOS_AOERR			0x00040000	//DA変換エラー
#define	AOS_DRVERR			0x00080000	//ドライバスペックエラー

//----------------------------------------------------------------------------------------------
//	カウンタステータス																			
//----------------------------------------------------------------------------------------------
#define	CNTS_BUSY			0x00000001	//カウンタ動作中
#define	CNTS_DATA_NUM		0x00000010	//比較カウント一致
#define	CNTS_ORERR			0x00010000	//オーバーラン
#define	CNTS_ERR			0x00020000	//カウンタ動作エラー

//----------------------------------------------------------------------------------------------
//	アナログ入力メッセージ																		
//----------------------------------------------------------------------------------------------
#define AIOM_AIE_START			0x1000	//AD変換開始条件成立イベント
#define AIOM_AIE_RPTEND			0x1001	//リピート終了イベント
#define AIOM_AIE_END			0x1002	//デバイス動作終了イベント
#define AIOM_AIE_DATA_NUM		0x1003	//指定サンプリング回数格納イベント
#define AIOM_AIE_DATA_TSF		0x1007	//指定転送数毎イベント
#define AIOM_AIE_OFERR			0x1004	//オーバーフローイベント
#define AIOM_AIE_SCERR			0x1005	//サンプリングクロックエラーイベント
#define AIOM_AIE_ADERR			0x1006	//AD変換エラーイベント

//----------------------------------------------------------------------------------------------
//	アナログ出力メッセージ																		
//----------------------------------------------------------------------------------------------
#define AIOM_AOE_START			0x1020	//DA変換開始条件成立イベント
#define AIOM_AOE_RPTEND			0x1021	//リピート終了イベント
#define AIOM_AOE_END			0x1022	//デバイス動作終了イベント
#define AIOM_AOE_DATA_NUM		0x1023	//指定サンプリング回数出力イベント
#define AIOM_AOE_DATA_TSF		0x1027	//指定転送数毎イベント
#define AIOM_AOE_SCERR			0x1025	//サンプリングクロックエラーイベント
#define AIOM_AOE_DAERR			0x1026	//DA変換エラーイベント

//----------------------------------------------------------------------------------------------
//	カウンタメッセージ																			
//----------------------------------------------------------------------------------------------
#define AIOM_CNTE_DATA_NUM		0x1042	//比較カウント一致イベント
#define AIOM_CNTE_ORERR			0x1043	//カウントオーバーランイベント
#define AIOM_CNTE_ERR			0x1044	//カウント動作エラーイベント

//----------------------------------------------------------------------------------------------
//	タイマメッセージ																			
//----------------------------------------------------------------------------------------------
#define AIOM_TME_INT			0x1060	//インターバル成立イベント

//----------------------------------------------------------------------------------------------
//	アナログ入力添付データ																		
//----------------------------------------------------------------------------------------------
#define	AIAT_AI				0x00000001	//アナログ入力付属情報
#define	AIAT_AO0			0x00000100	//アナログ出力データ
#define	AIAT_DIO0			0x00010000	//デジタル入出力データ
#define	AIAT_CNT0			0x01000000	//カウンタチャネル０データ
#define	AIAT_CNT1			0x02000000	//カウンタチャネル１データ

//----------------------------------------------------------------------------------------------
//	カウンタ動作モード																			
//----------------------------------------------------------------------------------------------
#define	CNT_LOADPRESET		0x0000001	//プリセットカウント値のロード
#define	CNT_LOADCOMP		0x0000002	//比較カウント値のロード

//----------------------------------------------------------------------------------------------
//	イベントコントローラ接続先信号																
//----------------------------------------------------------------------------------------------
#define	AIOECU_DEST_AI_CLK			4	//アナログ入力サンプリングクロック
#define	AIOECU_DEST_AI_START		0	//アナログ入力変換開始信号
#define	AIOECU_DEST_AI_STOP			2	//アナログ入力変換停止信号
#define	AIOECU_DEST_AO_CLK			36	//アナログ出力サンプリングクロック
#define	AIOECU_DEST_AO_START		32	//アナログ出力変換開始信号
#define	AIOECU_DEST_AO_STOP			34	//アナログ出力変換停止信号
#define	AIOECU_DEST_CNT0_UPCLK		134	//カウンタ０アップクロック信号
#define	AIOECU_DEST_CNT1_UPCLK		135	//カウンタ１アップクロック信号
#define	AIOECU_DEST_CNT0_START		128	//カウンタ０、タイマ０動作開始信号
#define	AIOECU_DEST_CNT1_START		129	//カウンタ１、タイマ１動作開始信号
#define	AIOECU_DEST_CNT0_STOP		130	//カウンタ０、タイマ０動作停止信号
#define	AIOECU_DEST_CNT1_STOP		131	//カウンタ１、タイマ１動作停止信号
#define	AIOECU_DEST_MASTER1			104	//同期バスマスタ信号１
#define	AIOECU_DEST_MASTER2			105	//同期バスマスタ信号２
#define	AIOECU_DEST_MASTER3			106	//同期バスマスタ信号３

//----------------------------------------------------------------------------------------------
//	イベントコントローラ接続元信号																
//----------------------------------------------------------------------------------------------
#define	AIOECU_SRC_OPEN				-1	//未接続
#define	AIOECU_SRC_AI_CLK			4	//アナログ入力内部クロック信号
#define	AIOECU_SRC_AI_EXTCLK		146	//アナログ入力外部クロック信号
#define	AIOECU_SRC_AI_TRGSTART		144	//アナログ入力外部トリガ開始信号
#define	AIOECU_SRC_AI_LVSTART		28	//アナログ入力レベルトリガ開始信号
#define	AIOECU_SRC_AI_STOP			17	//アナログ入力変換回数終了信号（遅延なし）
#define	AIOECU_SRC_AI_STOP_DELAY	18	//アナログ入力変換回数終了信号（遅延あり）
#define	AIOECU_SRC_AI_LVSTOP		29	//アナログ入力レベルトリガ停止信号
#define	AIOECU_SRC_AI_TRGSTOP		145	//アナログ入力外部トリガ停止信号
#define	AIOECU_SRC_AO_CLK			66	//アナログ出力内部クロック信号
#define	AIOECU_SRC_AO_EXTCLK		149	//アナログ出力外部クロック信号
#define	AIOECU_SRC_AO_TRGSTART		147	//アナログ出力外部トリガ開始信号
#define	AIOECU_SRC_AO_STOP_FIFO		352	//アナログ出力指定回数出力終了信号（FIFO使用）
#define	AIOECU_SRC_AO_STOP_RING		80	//アナログ出力指定回数出力終了信号（RING使用）
#define	AIOECU_SRC_AO_TRGSTOP		148	//アナログ出力外部トリガ停止信号
#define	AIOECU_SRC_CNT0_UPCLK		150	//カウンタ０アップクロック信号
#define	AIOECU_SRC_CNT1_UPCLK		152	//カウンタ１アップクロック信号
#define	AIOECU_SRC_CNT0_CMP			288	//カウンタ０比較カウント一致
#define	AIOECU_SRC_CNT1_CMP			289	//カウンタ１比較カウント一致
#define	AIOECU_SRC_SLAVE1			136	//同期バススレーブ信号１
#define	AIOECU_SRC_SLAVE2			137	//同期バススレーブ信号２
#define	AIOECU_SRC_SLAVE3			138	//同期バススレーブ信号３
#define	AIOECU_SRC_START			384	//Ai, Ao, Cnt, Tmソフトウェア開始信号
#define	AIOECU_SRC_STOP				385	//Ai, Ao, Cnt, Tmソフトウェア停止信号

//----------------------------------------------------------------------------------------------
// Mデバイス用カウンタメッセージ
//----------------------------------------------------------------------------------------------
#define	AIOM_CNTM_COUNTUP_CH0		0x1070	// カウントアップ、チャネル番号0
#define	AIOM_CNTM_COUNTUP_CH1		0x1071	//         "                   1
#define	AIOM_CNTM_TIME_UP			0x1090	//タイムアップ
#define	AIOM_CNTM_COUNTER_ERROR		0x1091	//カウンタエラー
#define	AIOM_CNTM_CARRY_BORROW		0x1092	//キャリー／ボロー

//----------------------------------------------------------------------------------------------
//	関数プロトタイプ																			
//----------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"{
#endif
//共通関数
long WINAPI AioInit(char * DeviceName, short * Id);
long WINAPI AioExit(short Id);
long WINAPI AioResetDevice(short Id);
long WINAPI AioGetErrorString(long ErrorCode, char * ErrorString);
long WINAPI AioQueryDeviceName(short Index, char * DeviceName, char * Device);
long WINAPI AioGetDeviceType(char * Device, short * DeviceType);
long WINAPI AioSetControlFilter(short Id, short Signal, float Value);
long WINAPI AioGetControlFilter(short Id, short Signal, float *Value);
long WINAPI AioResetProcess(short Id);

//アナログ入力関数
long WINAPI AioSingleAi(short Id, short AiChannel, long * AiData);
long WINAPI AioSingleAiEx(short Id, short AiChannel, float * AiData);
long WINAPI AioMultiAi(short Id, short AiChannels, long * AiData);
long WINAPI AioMultiAiEx(short Id, short AiChannels, float * AiData);
long WINAPI AioGetAiResolution(short Id, short * AiResolution);
long WINAPI AioSetAiInputMethod(short Id, short AiInputMethod);
long WINAPI AioGetAiInputMethod(short Id, short * AiInputMethod);
long WINAPI AioGetAiMaxChannels(short Id, short * AiMaxChannels);
long WINAPI AioSetAiChannel(short Id, short AiChannel, short Enabled);
long WINAPI AioGetAiChannel(short Id, short AiChannel, short *Enabled);
long WINAPI AioSetAiChannels(short Id, short AiChannels);
long WINAPI AioGetAiChannels(short Id, short * AiChannels);
long WINAPI AioSetAiChannelSequence(short Id, short AiSequence, short AiChannel);
long WINAPI AioGetAiChannelSequence(short Id, short AiSequence, short * AiChannel);
long WINAPI AioSetAiRange(short Id, short AiChannel, short AiRange);
long WINAPI AioSetAiRangeAll(short Id, short AiRange);
long WINAPI AioGetAiRange(short Id, short AiChannel, short * AiRange);
long WINAPI AioSetAiTransferMode(short Id, short AiTransferMode);
long WINAPI AioGetAiTransferMode(short Id, short *AiTransferMode);
long WINAPI AioSetAiDeviceBufferMode(short Id, short AiDeviceBufferMode);
long WINAPI AioGetAiDeviceBufferMode(short Id, short *AiDeviceBufferMode);
long WINAPI AioSetAiMemorySize(short Id, long AiMemorySize);
long WINAPI AioGetAiMemorySize(short Id, long *AiMemorySize);
long WINAPI AioSetAiTransferData(short Id, long DataNumber, long *Buffer);
long WINAPI AioSetAiAttachedData(short Id, long AttachedData);
long WINAPI AioGetAiSamplingDataSize(short Id, short *DataSize);
long WINAPI AioSetAiMemoryType(short Id, short AiMemoryType);
long WINAPI AioGetAiMemoryType(short Id, short * AiMemoryType);
long WINAPI AioSetAiRepeatTimes(short Id, long AiRepeatTimes);
long WINAPI AioGetAiRepeatTimes(short Id, long * AiRepeatTimes);
long WINAPI AioSetAiClockType(short Id, short AiClockType);
long WINAPI AioGetAiClockType(short Id, short * AiClockType);
long WINAPI AioSetAiSamplingClock(short Id, float AiSamplingClock);
long WINAPI AioGetAiSamplingClock(short Id, float * AiSamplingClock);
long WINAPI AioSetAiScanClock(short Id, float AiScanClock);
long WINAPI AioGetAiScanClock(short Id, float * AiScanClock);
long WINAPI AioSetAiClockEdge(short Id, short AoClockEdge);
long WINAPI AioGetAiClockEdge(short Id, short * AoClockEdge);
long WINAPI AioSetAiStartTrigger(short Id, short AiStartTrigger);
long WINAPI AioGetAiStartTrigger(short Id, short * AiStartTrigger);
long WINAPI AioSetAiStartLevel(short Id, short AiChannel, long AiStartLevel, short AiDirection);
long WINAPI AioSetAiStartLevelEx(short Id, short AiChannel, float AiStartLevel, short AiDirection);
long WINAPI AioGetAiStartLevel(short Id, short AiChannel, long * AiStartLevel, short * AiDirection);
long WINAPI AioGetAiStartLevelEx(short Id, short AiChannel, float * AiStartLevel, short * AiDirection);
long WINAPI AioSetAiStartInRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStartInRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStartInRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStartInRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStartOutRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStartOutRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStartOutRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStartOutRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopTrigger(short Id, short AiStopTrigger);
long WINAPI AioGetAiStopTrigger(short Id, short * AiStopTrigger);
long WINAPI AioSetAiStopTimes(short Id, long AiStopTimes);
long WINAPI AioGetAiStopTimes(short Id, long * AiStopTimes);
long WINAPI AioSetAiStopLevel(short Id, short AiChannel, long AiStopLevel, short AiDirection);
long WINAPI AioSetAiStopLevelEx(short Id, short AiChannel, float AiStopLevel, short AiDirection);
long WINAPI AioGetAiStopLevel(short Id, short AiChannel, long * AiStopLevel, short * AiDirection);
long WINAPI AioGetAiStopLevelEx(short Id, short AiChannel, float * AiStopLevel, short * AiDirection);
long WINAPI AioSetAiStopInRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStopInRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStopInRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStopInRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopOutRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStopOutRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStopOutRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStopOutRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopDelayTimes(short Id, long AiStopDelayTimes);
long WINAPI AioGetAiStopDelayTimes(short Id, long * AiStopDelayTimes);
long WINAPI AioSetAiEvent(short Id, HWND hWnd, long AiEvent);
long WINAPI AioGetAiEvent(short Id, HWND * hWnd, long * AiEvent);
long WINAPI AioSetAiCallBackProc(short Id,long (_stdcall *pProc)(short Id, short AiEvent, WPARAM wParam, LPARAM lParam, void *Param), long AiEvent, void *Param);
long WINAPI AioSetAiEventSamplingTimes(short Id, long AiSamplingTimes);
long WINAPI AioGetAiEventSamplingTimes(short Id, long * AiSamplingTimes);
long WINAPI AioSetAiEventTransferTimes(short Id, long AiTransferTimes);
long WINAPI AioGetAiEventTransferTimes(short Id, long *AiTransferTimes);
long WINAPI AioStartAi(short Id);
long WINAPI AioStartAiSync(short Id, long TimeOut);
long WINAPI AioStopAi(short Id);
long WINAPI AioGetAiStatus(short Id, long * AiStatus);
long WINAPI AioGetAiSamplingCount(short Id, long * AiSamplingCount);
long WINAPI AioGetAiStopTriggerCount(short Id, long * AiStopTriggerCount);
long WINAPI AioGetAiTransferCount(short Id, long *AiTransferCount);
long WINAPI AioGetAiTransferLap(short Id, long *Lap);
long WINAPI AioGetAiStopTriggerTransferCount(short Id, long *Count);
long WINAPI AioGetAiRepeatCount(short Id, long * AiRepeatCount);
long WINAPI AioGetAiSamplingData(short Id, long * AiSamplingTimes, long * AiData);
long WINAPI AioGetAiSamplingDataEx(short Id, long * AiSamplingTimes, float * AiData);
long WINAPI AioResetAiStatus(short Id);
long WINAPI AioResetAiMemory(short Id);

//アナログ出力関数
long WINAPI AioSingleAo(short Id, short AoChannel, long AoData);
long WINAPI AioSingleAoEx(short Id, short AoChannel, float AoData);
long WINAPI AioMultiAo(short Id, short AoChannels, long * AoData);
long WINAPI AioMultiAoEx(short Id, short AoChannels, float * AoData);
long WINAPI AioGetAoResolution(short Id, short * AoResolution);
long WINAPI AioSetAoChannels(short Id, short AoChannels);
long WINAPI AioGetAoChannels(short Id, short * AoChannels);
long WINAPI AioGetAoMaxChannels(short Id, short * AoMaxChannels);
long WINAPI AioSetAoRange(short Id, short AoChannel, short AoRange);
long WINAPI AioSetAoRangeAll(short Id, short AoRange);
long WINAPI AioGetAoRange(short Id, short AoChannel, short * AoRange);
long WINAPI AioSetAoTransferMode(short Id, short AoTransferMode);
long WINAPI AioGetAoTransferMode(short Id, short *AoTransferMode);
long WINAPI AioSetAoDeviceBufferMode(short Id, short AoDeviceBufferMode);
long WINAPI AioGetAoDeviceBufferMode(short Id, short *AoDeviceBufferMode);
long WINAPI AioSetAoMemorySize(short Id, long AoMemorySize);
long WINAPI AioGetAoMemorySize(short Id, long *AoMemorySize);
long WINAPI AioSetAoTransferData(short Id, long DataNumber, long *Buffer);
long WINAPI AioGetAoSamplingDataSize(short Id, short *DataSize);
long WINAPI AioSetAoMemoryType(short Id, short AoMemoryType);
long WINAPI AioGetAoMemoryType(short Id, short * AoMemoryType);
long WINAPI AioSetAoRepeatTimes(short Id, long AoRepeatTimes);
long WINAPI AioGetAoRepeatTimes(short Id, long * AoRepeatTimes);
long WINAPI AioSetAoClockType(short Id, short AoClockType);
long WINAPI AioGetAoClockType(short Id, short * AoClockType);
long WINAPI AioSetAoSamplingClock(short Id, float AoSamplingClock);
long WINAPI AioGetAoSamplingClock(short Id, float * AoSamplingClock);
long WINAPI AioSetAoClockEdge(short Id, short AoClockEdge);
long WINAPI AioGetAoClockEdge(short Id, short * AoClockEdge);
long WINAPI AioSetAoSamplingData(short Id, long AoSamplingTimes, long * AoData);
long WINAPI AioSetAoSamplingDataEx(short Id, long AoSamplingTimes, float * AoData);
long WINAPI AioGetAoSamplingTimes(short Id, long * AoSamplingTimes);
long WINAPI AioSetAoStartTrigger(short Id, short AoStartTrigger);
long WINAPI AioGetAoStartTrigger(short Id, short * AoStartTrigger);
long WINAPI AioSetAoStopTrigger(short Id, short AoStopTrigger);
long WINAPI AioGetAoStopTrigger(short Id, short * AoStopTrigger);
long WINAPI AioSetAoEvent(short Id, HWND hWnd, long AoEvent);
long WINAPI AioGetAoEvent(short Id, HWND * hWnd, long * AoEvent);
long WINAPI AioSetAoCallBackProc(short Id,
	long (_stdcall *pProc)(short Id, short AiEvent, WPARAM wParam, LPARAM lParam, void *Param), long AoEvent, void *Param);
long WINAPI AioSetAoEventSamplingTimes(short Id, long AoSamplingTimes);
long WINAPI AioGetAoEventSamplingTimes(short Id, long * AoSamplingTimes);
long WINAPI AioSetAoEventTransferTimes(short Id, long AoTransferTimes);
long WINAPI AioGetAoEventTransferTimes(short Id, long *AoTransferTimes);
long WINAPI AioStartAo(short Id);
long WINAPI AioStopAo(short Id);
long WINAPI AioEnableAo(short Id, short AoChannel);
long WINAPI AioDisableAo(short Id, short AoChannel);
long WINAPI AioGetAoStatus(short Id, long * AoStatus);
long WINAPI AioGetAoSamplingCount(short Id, long * AoSamplingCount);
long WINAPI AioGetAoTransferCount(short Id, long *AoTransferCount);
long WINAPI AioGetAoTransferLap(short Id, long *Lap);
long WINAPI AioGetAoRepeatCount(short Id, long * AoRepeatCount);
long WINAPI AioResetAoStatus(short Id);
long WINAPI AioResetAoMemory(short Id);

//デジタル入出力関数
long WINAPI AioSetDiFilter(short Id, short Bit, float Value);
long WINAPI AioGetDiFilter(short Id, short Bit, float *Value);
long WINAPI AioInputDiBit(short Id, short DiBit, short * DiData);
long WINAPI AioOutputDoBit(short Id, short DoBit, short DoData);
long WINAPI AioInputDiByte(short Id, short DiPort, short * DiData);
long WINAPI AioOutputDoByte(short Id, short DoPort, short DoData);
long WINAPI AioSetDioDirection(short Id, long Dir);
long WINAPI AioGetDioDirection (short Id, long * Dir);

//カウンタ関数
long WINAPI AioGetCntMaxChannels(short Id, short * CntMaxChannels);
long WINAPI AioSetCntComparisonMode(short Id, short CntChannel, short CntMode);
long WINAPI AioGetCntComparisonMode(short Id, short CntChannel, short *CntMode);
long WINAPI AioSetCntPresetReg(short Id, short CntChannel, long PresetNumber, long *PresetData, short Flag);
long WINAPI AioSetCntComparisonReg(short Id, short CntChannel, long ComparisonNumber, long *ComparisonData, short Flag);
long WINAPI AioSetCntInputSignal(short Id, short CntChannel, short CntInputSignal);
long WINAPI AioGetCntInputSignal(short Id, short CntChannel, short *CntInputSignal);
long WINAPI AioSetCntEvent(short Id, short CntChannel, HWND hWnd, long CntEvent);
long WINAPI AioGetCntEvent(short Id, short CntChannel, HWND *hWnd, long *CntEvent);
long WINAPI AioSetCntCallBackProc(short Id, short CntChannel,
	long (_stdcall *pProc)(short Id, short CntEvent, WPARAM wParam, LPARAM lParam, void *Param), long CntEvent, void *Param);
long WINAPI AioSetCntFilter(short Id, short CntChannel, short Signal, float Value);
long WINAPI AioGetCntFilter(short Id, short CntChannel, short Signal, float *Value);
long WINAPI AioStartCnt(short Id, short CntChannel);
long WINAPI AioStopCnt(short Id, short CntChannel);
long WINAPI AioPresetCnt(short Id, short CntChannel, long PresetData);
long WINAPI AioGetCntStatus(short Id, short CntChannel, long *CntStatus);
long WINAPI AioGetCntCount(short Id, short CntChannel, long *Count);
long WINAPI AioResetCntStatus(short Id, short CntChannel, long CntStatus);

//タイマ関数
long WINAPI AioSetTmEvent(short Id, short TimerId, HWND hWnd, long TmEvent);
long WINAPI AioGetTmEvent(short Id, short TimerId, HWND * hWnd, long * TmEvent);
long WINAPI AioSetTmCallBackProc(short Id, short TimerId,
	long (_stdcall *pProc)(short Id, short TmEvent, WPARAM wParam, LPARAM lParam, void *Param), long TmEvent, void *Param);
long WINAPI AioStartTmTimer(short Id, short TimerId, float Interval);
long WINAPI AioStopTmTimer(short Id, short TimerId);
long WINAPI AioStartTmCount(short Id, short TimerId);
long WINAPI AioStopTmCount(short Id, short TimerId);
long WINAPI AioLapTmCount(short Id, short TimerId, long *Lap);
long WINAPI AioResetTmCount(short Id, short TimerId);
long WINAPI AioTmWait(short Id, short TimerId, long Wait);

//イベントコントローラ
long WINAPI AioSetEcuSignal(short Id, short Destination, short Source);
long WINAPI AioGetEcuSignal(short Id, short Destination, short *Source);

// Setting function (set)
long WINAPI AioGetCntmMaxChannels(short Id, short *CntmMaxChannels);
long WINAPI AioSetCntmZMode(short Id, short ChNo, short Mode);
long WINAPI AioSetCntmZLogic(short Id, short ChNo, short ZLogic);
long WINAPI AioSelectCntmChannelSignal(short Id, short ChNo, short SigType);
long WINAPI AioSetCntmCountDirection(short Id, short ChNo, short Dir);
long WINAPI AioSetCntmOperationMode(short Id, short ChNo, short Phase, short Mul, short SyncClr);
long WINAPI AioSetCntmDigitalFilter(short Id, short ChNo, short FilterValue);
long WINAPI AioSetCntmPulseWidth(short Id, short ChNo, short PlsWidth);
long WINAPI AioSetCntmDIType(short Id, short ChNo, short InputType);
long WINAPI AioSetCntmOutputHardwareEvent(short Id, short ChNo, short OutputLogic, unsigned long EventType, short PulseWidth);
long WINAPI AioSetCntmInputHardwareEvent(short Id, short ChNo, unsigned long EventType, short RF0, short RF1, short Reserved);
long WINAPI AioSetCntmCountMatchHardwareEvent(short Id, short ChNo, short RegisterNo, unsigned long EventType, short Reserved);
long WINAPI AioSetCntmPresetRegister(short Id, short ChNo, unsigned long PresetData, short Reserved);
long WINAPI AioSetCntmTestPulse(short Id, short CntmInternal, short CntmOut, short CntmReserved);
// Setting function (get)
long WINAPI AioGetCntmZMode(short Id, short ChNo, short *Mode);
long WINAPI AioGetCntmZLogic(short Id, short ChNo, short *ZLogic);
long WINAPI AioGetCntmChannelSignal(short Id, short CntmChNo, short *CntmSigType);
long WINAPI AioGetCntmCountDirection(short Id, short ChNo, short *Dir);
long WINAPI AioGetCntmOperationMode(short Id, short ChNo, short *Phase, short *Mul, short *SyncClr);
long WINAPI AioGetCntmDigitalFilter(short Id, short ChNo, short *FilterValue);
long WINAPI AioGetCntmPulseWidth(short Id, short ChNo, short *PlsWidth);
// Counter function
long WINAPI AioCntmStartCount(short Id, short *ChNo, short ChNum);
long WINAPI AioCntmStopCount(short Id, short *ChNo, short ChNum);
long WINAPI AioCntmPreset(short Id, short *ChNo, short ChNum, unsigned long *PresetData);
long WINAPI AioCntmZeroClearCount(short Id, short *ChNo, short ChNum);
long WINAPI AioCntmReadCount(short Id, short *ChNo, short ChNum, unsigned long *CntDat);
long WINAPI AioCntmReadStatus(short Id, short ChNo, short *Sts);
long WINAPI AioCntmReadStatusEx(short Id, short ChNo, unsigned long *Sts);
// Notify function
long WINAPI AioCntmNotifyCountUp(short Id, short ChNo, short RegNo, unsigned long Count, HANDLE hWnd);
long WINAPI AioCntmStopNotifyCountUp(short Id, short ChNo, short RegNo);
long WINAPI AioCntmCountUpCallbackProc(short Id , void *CallBackProc , void *Param);
long WINAPI AioCntmNotifyCounterError(short Id, HANDLE hWnd);
long WINAPI AioCntmStopNotifyCounterError(short Id);
long WINAPI AioCntmCounterErrorCallbackProc(short Id , void *CallBackProc , void *Param);
long WINAPI AioCntmNotifyCarryBorrow(short Id, HANDLE hWnd);
long WINAPI AioCntmStopNotifyCarryBorrow(short Id);
long WINAPI AioCntmCarryBorrowCallbackProc(short Id, void *CallBackProc, void *Param);
long WINAPI AioCntmNotifyTimer(short Id, unsigned long TimeValue, HANDLE hWnd);
long WINAPI AioCntmStopNotifyTimer(short Id);
long WINAPI AioCntmTimerCallbackProc(short Id , void *CallBackProc , void *Param);
// General purpose input function
long WINAPI AioCntmInputDIByte(short Id, short Reserved, BYTE *bData);
long WINAPI AioCntmOutputDOBit(short Id, short AiomChNo, short Reserved, BYTE OutData);

#ifdef __cplusplus
};
#endif
