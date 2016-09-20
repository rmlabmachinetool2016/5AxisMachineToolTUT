//============================================================-
// CNT.H
// Headder file for CONTEC Counter device
//
//                                              CONTEC.Co.,Ltd.
//============================================================-
#include <Windows.h>
//-------------------------------------------------
// Prototype definition
//-------------------------------------------------
#ifdef __cplusplus
extern "C"{
#endif
// Common function
long WINAPI CntInit(char *DeviceName, short *Id);
long WINAPI CntExit(short Id);
long WINAPI CntResetDevice(short Id);
long WINAPI CntGetErrorString(long ErrorCode , char *ErrorString);
// Setting function (set)
long WINAPI CntSetZMode(short Id, short ChNo, short Mode);
long WINAPI CntSetZLogic(short Id, short ChNo, short ZLogic);
long WINAPI CntSelectChannelSignal(short Id, short ChNo, short SigType);
long WINAPI CntSetCountDirection(short Id, short ChNo, short Dir);
long WINAPI CntSetOperationMode(short Id, short ChNo, short Phase, short Mul, short SyncClr);
long WINAPI CntSetDigitalFilter(short Id, short ChNo, short FilterValue);
long WINAPI CntSetPulseWidth(short Id, short ChNo, short PlsWidth);
long WINAPI CntSetDIType(short Id, short ChNo, short InputType);
long WINAPI CntSetOutputHardwareEvent(short Id, short ChNo, short OutputLogic, unsigned long EventType, short PulseWidth);
long WINAPI CntSetInputHardwareEvent(short Id, short ChNo, unsigned long EventType, short RF0, short RF1, short Reserved);
long WINAPI CntSetCountMatchHardwareEvent(short Id, short ChNo, short RegisterNo, unsigned long EventType, short Reserved);
long WINAPI CntSetPresetRegister(short Id, short ChNo, unsigned long PresetData, short Reserved);
// Setting function (get)
long WINAPI CntGetZMode(short Id, short ChNo, short *Mode);
long WINAPI CntGetZLogic(short Id, short ChNo, short *ZLogic);
long WINAPI CntGetChannelSignal(short Id, short ChNo, short *SigType);
long WINAPI CntGetCountDirection(short Id, short ChNo, short *Dir);
long WINAPI CntGetOperationMode(short Id, short ChNo, short *Phase, short *Mul, short *SyncClr);
long WINAPI CntGetDigitalFilter(short Id, short ChNo, short *FilterValue);
long WINAPI CntGetPulseWidth(short Id, short ChNo, short *PlsWidth);
// Counter function
long WINAPI CntStartCount(short Id, short *ChNo, short ChNum);
long WINAPI CntStopCount(short Id, short *ChNo, short ChNum);
long WINAPI CntPreset(short Id, short *ChNo, short ChNum, unsigned long *PresetData);
long WINAPI CntZeroClearCount(short Id, short *ChNo, short ChNum);
long WINAPI CntReadCount(short Id, short *ChNo, short ChNum, unsigned long *CntDat);
long WINAPI CntReadStatus(short Id, short ChNo, short *Sts);
long WINAPI CntReadStatusEx(short Id, short ChNo, unsigned long *Sts);
// Notify function
long WINAPI CntNotifyCountUp(short Id, short ChNo, short RegNo, unsigned long Count, HANDLE hWnd);
long WINAPI CntStopNotifyCountUp(short Id, short ChNo, short RegNo);
long WINAPI CntCountUpCallbackProc(short Id , void *CallBackProc , void *Param);
long WINAPI CntNotifyCounterError(short Id, HANDLE hWnd);
long WINAPI CntStopNotifyCounterError(short Id);
long WINAPI CntCounterErrorCallbackProc(short Id , void *CallBackProc , void *Param);
long WINAPI CntNotifyCarryBorrow(short Id, HANDLE hWnd);
long WINAPI CntStopNotifyCarryBorrow(short Id);
long WINAPI CntCarryBorrowCallbackProc(short Id, void *CallBackProc, void *Param);
long WINAPI CntNotifyTimer(short Id, unsigned long TimeValue, HANDLE hWnd);
long WINAPI CntStopNotifyTimer(short Id);
long WINAPI CntTimerCallbackProc(short Id , void *CallBackProc , void *Param);
// General purpose input function
long WINAPI CntInputDIByte(short Id, short Reserved, BYTE *bData);
long WINAPI CntOutputDOBit(short Id, short ChNo, short Reserved, BYTE OutData);
// Information function
long WINAPI CntQueryDeviceName(short Index, char *DeviceName, char *Device);
long WINAPI CntGetMaxChannels(short Id, short *ChannelNum);
// Test function
long WINAPI CntSetTestPulse(short Id, short Internal, short Out, unsigned long Reserved);
// Sampling mode function
long WINAPI CntSetSyncSignal(short Id, short StartSignal, short StopSignal, short ClockSignal);
long WINAPI CntSetStandAlone(short Id);
long WINAPI CntSetMaster(short Id, short ExtSig1, short ExtSig2, short ExtSig3, short MasterHalt, short SlaveHalt);
long WINAPI CntSetSlave(short Id, short ExtSig1, short ExtSig2, short ExtSig3, short MasterHalt, short SlaveHalt);
long WINAPI CntSetCounterMode(short Id, short ChNo, short CountMode);
// Sampling condition function
long WINAPI CntSetSamplingStartTrigger(short Id, short StartTrg, short CountStartMode, short CountChNum);
long WINAPI CntSetSamplingClockTrigger(short Id, short ClockTrg);
long WINAPI CntSetSamplingStopTrigger(short Id, short StopTrg, short CountStopMode, short CountChNum);
long WINAPI CntSetSamplingInternalClock(short Id, unsigned long Clock, short Unit);
long WINAPI CntSetSamplingStopNumber(short Id, unsigned long StopNum);
// Sampling message function
long WINAPI CntNotifySamplingStop(short Id, HANDLE hWnd);
long WINAPI CntSamplingStopCallbackProc(short Id, void *CallBackProc, void *Param);
long WINAPI CntNotifySamplingCount(short Id, long Count, HANDLE hWnd);
long WINAPI CntSamplingCountCallbackProc(short Id, void *CallBackProc, void *Param);
// Sampling operation function
long WINAPI CntSamplingFifoReset(short Id);
long WINAPI CntSamplingSetBuffer(short Id, unsigned long *Buffer, short ChNum, unsigned long ScanNum, short IsRing);
long WINAPI CntSamplingStart(short Id);
long WINAPI CntSamplingStop(short Id);
// Sampling status function
long WINAPI CntGetSamplingStatus(short Id, unsigned long *Status, unsigned long *Err);
long WINAPI CntGetSamplingCount(short Id, unsigned long *ScanCount, unsigned long *ScanCarry);
long WINAPI CntGetSamplingWritePointer(short Id, unsigned long *WritePointer, unsigned long *ScanCount, unsigned long *ScanCarry);

long WINAPI CntGetDeviceInfo(char *Device, short InfoType, void *Param1, void *Param2, void *Param3);
long WINAPI CntGetDeviceType(char *Device, short *DeviceType);
#ifdef __cplusplus
};
#endif
//-------------------------------------------------
// Type definition
//-------------------------------------------------

#define	DEVICE_TYPE_ISA							0				//ISA or C Bus
#define	DEVICE_TYPE_PCI							1				//PCI Bus
#define	DEVICE_TYPE_PCMCIA						2				//PCMCIA
#define	DEVICE_TYPE_USB							3				//USB
#define	DEVICE_TYPE_FIT							4				//FIT

//-------------------------------------------------
// Mode definition
//-------------------------------------------------
// Z Phase Mode
#define	CNT_ZPHASE_NOT_USE						1
#define	CNT_ZPHASE_NEXT_ONE						2
#define	CNT_ZPHASE_EVERY_TIME					3
// Z Phase Logic
#define	CNT_ZLOGIC_POSITIVE						0
#define	CNT_ZLOGIC_NEGATIVE						1
// Signal Source
#define	CNT_SIGTYPE_ISOLATE						0
#define	CNT_SIGTYPE_TTL							1
#define	CNT_SIGTYPE_LINERECEIVER				2
// Count Direction
#define	CNT_DIR_DOWN							0
#define	CNT_DIR_UP								1
// 1Phase/2Phase
#define	CNT_MODE_1PHASE							0
#define	CNT_MODE_2PHASE							1
#define	CNT_MODE_GATECONTROL					2
// Mul
#define	CNT_MUL_X1								0
#define	CNT_MUL_X2								1
#define	CNT_MUL_X4								2
// Sync Clear
#define	CNT_CLR_ASYNC							0
#define	CNT_CLR_SYNC							1
// Gate Control
#define	CNT_UPDOWN								1
#define	CNT_GATECONTROL							0
// Generic I/O Signal
#define	CNT_GENIO_LINERECEIVER					0
#define	CNT_GENIO_TTL							1
// Output Logic
#define	CNT_OEVENT_NEGATIVE						0
#define	CNT_OEVENT_POSITIVE						1
// Output Hardware Event
#define	CNT_OEVENT_GENOUT						0x00
#define	CNT_OEVENT_MATCH0						0x01
#define	CNT_OEVENT_MATCH1						0x02
#define	CNT_OEVENT_FLTERR						0x04
#define	CNT_OEVENT_AIERR						0x08
#define	CNT_OEVENT_ALMERR						0x10
// Input Signal Event
#define	CNT_IEVENT_GENINP						0
#define	CNT_IEVENT_STARTSTOP					1
#define	CNT_IEVENT_PRESET						2
#define	CNT_IEVENT_CLEAR						3
// RIZE/FALL
#define	CNT_INP_NONE							0
#define	CNT_INP_RIZE							1
#define	CNT_INP_FALL							2
// Couunt Match Event
#define	CNT_MATCH_NONE							0
#define	CNT_MATCH_PRESET						1
#define	CNT_MATCH_CLEAR							2
// Error Type
#define	CNT_AI_ERROR							1
#define	CNT_FLT_ERROR							2
#define	CNT_ALM_ERROR							3
// Carry/Borrow
#define	CNT_CB_CARRY							1
#define	CNT_CB_BORROW							2
// Device Information
#define	ICNT_DEVICE_TYPE						0				// device type.						Param1:short
#define	ICNT_NUMBER_OF_CH						1				// Channel number					Param1:short
#define	ICNT_BIT								2				// bit number						Param1:short
#define	ICNT_IS_DIGITAL_FILTER					3				// Can digital filter be used?		Param1short
#define	ICNT_IS_DEFF							4				// The differential motion of general-purpose input it changes? 	Param1:short
#define	ICNT_CNTSOURCE							5				// Signal source of counter			Param1:short(BIT0:TTL, BIT1:PHOTO, BIT2:LINERECEIVER)
// Cnt Source
#define	ICNT_CNTSOURCE_TTL						0x01
#define	ICNT_CNTSOURCE_PHOTO					0x02
#define	ICNT_CNTSOURCE_LINERECEIVER				0x04

// SyncSignal
#define	CNTS_CLOCK_OUT_OFF						0
#define	CNTS_CLOCK_OUT_ON						1
#define	CNTS_START_OUT_OFF						0
#define	CNTS_START_OUT_ON						1
#define	CNTS_STOP_OUT_OFF						0
#define	CNTS_STOP_OUT_ON						1
// ExtSig
#define	CNTS_EXT_NOTUSE							0				// Not Used
#define CNTS_EXT_START_SOFT						1				// Software Start
#define CNTS_EXT_STOP_SOFT						2				// Software Stop
#define CNTS_EXT_CLOCK							3				// Internal Clock
#define CNTS_EXT_EXT_TRG						4				// External Clock
#define CNTS_EXT_START_EXT_RISE					5				// External Start Rize
#define CNTS_EXT_START_EXT_FALL					6				// External Start Fall
#define CNTS_EXT_STOP_EXT_RISE					7				// External Stop Rize
#define CNTS_EXT_STOP_EXT_FALL					8				// External Stop Fall
#define CNTS_EXT_CLOCK_ERROR					9				// Sampling Clock Error
#define	CNTS_EXT_TRNSNUM						10				// Stop Number of Transfer Data
#define	CNTS_EXT_CNTMATCH_CH0_REG0				11				// Count Match Ch0:REG0
#define	CNTS_EXT_CNTMATCH_CH1_REG0				12				// Count Match CH1:REG0
#define	CNTS_EXT_CNTMATCH_CH2_REG0				13				// Count Match CH2:REG0
#define	CNTS_EXT_CNTMATCH_CH3_REG0				14				// Count Match CH3:REG0
#define	CNTS_EXT_CNTMATCH_CH4_REG0				15				// Count Match CH4:REG0
#define	CNTS_EXT_CNTMATCH_CH5_REG0				16				// Count Match CH5:REG0
#define	CNTS_EXT_CNTMATCH_CH6_REG0				17				// Count Match CH6:REG0
#define	CNTS_EXT_CNTMATCH_CH7_REG0				18				// Count Match CH7:REG0
#define	CNTS_EXT_CNTMATCH_CH0_REG1				19				// Count Match CH0:REG1
#define	CNTS_EXT_CNTMATCH_CH1_REG1				20				// Count Match CH1:REG1
#define	CNTS_EXT_CNTMATCH_CH2_REG1				21				// Count Match CH2:REG1
#define	CNTS_EXT_CNTMATCH_CH3_REG1				22				// Count Match CH3:REG1
#define	CNTS_EXT_CNTMATCH_CH4_REG1				23				// Count Match CH4:REG1
#define	CNTS_EXT_CNTMATCH_CH5_REG1				24				// Count Match CH5:REG1
#define	CNTS_EXT_CNTMATCH_CH6_REG1				25				// Count Match CH6:REG1
#define	CNTS_EXT_CNTMATCH_CH7_REG1				26				// Count Match CH7:REG1
// Count Mode
#define	CNTS_MODE_NORMAL						0				// Normal Counter
#define	CNTS_MODE_DIFF							1				// Differencial Counter
// Sampling Start
#define	CNTS_START_SOFT							1				// Software Start
#define	CNTS_START_EXT_RISE						2				// External Start Rize
#define	CNTS_START_EXT_FALL						3				// External Start Fall
#define	CNTS_START_CNTMATCH_CH0_REG0			4				// Count Match CH0:REG0
#define	CNTS_START_CNTMATCH_CH1_REG0			5				// Count Match CH1:REG0
#define	CNTS_START_CNTMATCH_CH2_REG0			6				// Count Match CH2:REG0
#define	CNTS_START_CNTMATCH_CH3_REG0			7				// Count Match CH3:REG0
#define	CNTS_START_CNTMATCH_CH4_REG0			8				// Count Match CH4:REG0
#define	CNTS_START_CNTMATCH_CH5_REG0			9				// Count Match CH5:REG0
#define	CNTS_START_CNTMATCH_CH6_REG0			10				// Count Match CH6:REG0
#define	CNTS_START_CNTMATCH_CH7_REG0			11				// Count Match CH7:REG0
#define	CNTS_START_CNTMATCH_CH0_REG1			12				// Count Match CH0:REG1
#define	CNTS_START_CNTMATCH_CH1_REG1			13				// Count Match CH1:REG1
#define	CNTS_START_CNTMATCH_CH2_REG1			14				// Count Match CH2:REG1
#define	CNTS_START_CNTMATCH_CH3_REG1			15				// Count Match CH3:REG1
#define	CNTS_START_CNTMATCH_CH4_REG1			16				// Count Match CH4:REG1
#define	CNTS_START_CNTMATCH_CH5_REG1			17				// Count Match CH5:REG1
#define	CNTS_START_CNTMATCH_CH6_REG1			18				// Count Match CH6:REG1
#define	CNTS_START_CNTMATCH_CH7_REG1			19				// Count Match CH7:REG1
#define	CNTS_START_EXTSIG_1						20				// EXTSIG1
#define	CNTS_START_EXTSIG_2						21				// EXTSIG2
#define	CNTS_START_EXTSIG_3						22				// EXTSIG3
// Counter Start
#define	CNTS_START_CNT_NOT_WITH_SAMP			3				// Counter Start not with Sampling Start
#define	CNTS_START_CNT_WITH_SAMP				4				// Counter Start with Sampling Start
// Sampling Clock
#define	CNTS_CLOCK_CLOCK						1				// Internal Clock
#define	CNTS_CLOCK_EXT_TRG						2				// External Clock
#define	CNTS_CLOCK_EXTSIG_1						3				// EXTSIG1
#define	CNTS_CLOCK_EXTSIG_2						4				// EXTSIG2
#define	CNTS_CLOCK_EXTSIG_3						5				// EXTSIG3
// Sampling Stop
#define	CNTS_STOP_SOFT							1				// Software Stop
#define	CNTS_STOP_EXT_RISE						2				// External Stop Rize
#define	CNTS_STOP_EXT_FALL						3				// External Stop Fall
#define	CNTS_STOP_NUM							4				// Stop with Number of Data
#define	CNTS_STOP_CNTMATCH_CH0_REG0				5				// Count Match CH0:REG0
#define	CNTS_STOP_CNTMATCH_CH1_REG0				6				// Count Match CH1:REG0
#define	CNTS_STOP_CNTMATCH_CH2_REG0				7				// Count Match CH2:REG0
#define	CNTS_STOP_CNTMATCH_CH3_REG0				8				// Count Match CH3:REG0
#define	CNTS_STOP_CNTMATCH_CH4_REG0				9				// Count Match CH4:REG0
#define	CNTS_STOP_CNTMATCH_CH5_REG0				10				// Count Match CH5:REG0
#define	CNTS_STOP_CNTMATCH_CH6_REG0				11				// Count Match CH6:REG0
#define	CNTS_STOP_CNTMATCH_CH7_REG0				12				// Count Match CH7:REG0
#define	CNTS_STOP_CNTMATCH_CH0_REG1				13				// Count Match CH0:REG1
#define	CNTS_STOP_CNTMATCH_CH1_REG1				14				// Count Match CH1:REG1
#define	CNTS_STOP_CNTMATCH_CH2_REG1				15				// Count Match CH2:REG1
#define	CNTS_STOP_CNTMATCH_CH3_REG1				16				// Count Match CH3:REG1
#define	CNTS_STOP_CNTMATCH_CH4_REG1				17				// Count Match CH4:REG1
#define	CNTS_STOP_CNTMATCH_CH5_REG1				18				// Count Match CH5:REG1
#define	CNTS_STOP_CNTMATCH_CH6_REG1				19				// Count Match CH6:REG1
#define	CNTS_STOP_CNTMATCH_CH7_REG1				20				// Count Match CH7:REG1
#define	CNTS_STOP_EXTSIG_1						21				// EXTSIG1
#define	CNTS_STOP_EXTSIG_2						22				// EXTSIG2
#define	CNTS_STOP_EXTSIG_3						23				// EXTSIG3
// Clock Unit
#define	CNTS_TIM_UNIT_S							1
#define	CNTS_TIM_UNIT_MS						2
#define	CNTS_TIM_UNIT_US						3
#define	CNTS_TIM_UNIT_NS						4
// Counter Stop
#define	CNTS_STOP_CNT_NOT_WITH_SAMP				3				// Counter Stop not with Sampling Stop
#define	CNTS_STOP_CNT_WITH_SAMP					4				// Counter Stop with Sampling Stop
// Buffer
#define	CNTS_WRITE_ONCE							0
#define	CNTS_WRITE_RING							1

//-------------------------------------------------
// Message
//-------------------------------------------------
#define	CNTM_COUNTUP_CH0						0x1100			// count up, channel number 0
#define	CNTM_COUNTUP_CH1						0x1101			// count up, channel number 1
#define	CNTM_COUNTUP_CH2						0x1102			// count up, channel number 2
#define	CNTM_COUNTUP_CH3						0x1103			// count up, channel number 3
#define	CNTM_COUNTUP_CH4						0x1104			// count up, channel number 4
#define	CNTM_COUNTUP_CH5						0x1105			// count up, channel number 5
#define	CNTM_COUNTUP_CH6						0x1106			// count up, channel number 6
#define	CNTM_COUNTUP_CH7						0x1107			// count up, channel number 7

#define	CNTM_TIMER								0x1140			// timer
#define	CNTM_COUNTER_ERROR						0x1141			// counter error
#define	CNTM_CARRY_BORROW						0x1142			// carry / borrow

#define	CNTM_SAMPLING_STOP						0x1150			// sampling stop
#define	CNTM_SAMPLING_COUNT						0x1151			// completion of specified sampling count

// Count Match Direction(UP=1, DOWN=2)
#define	CNTM_DIR_UP								1				// match of up count
#define	CNTM_DIR_DOWN							2				// match of down count

//-------------------------------------------------
// Status
//-------------------------------------------------
#define	CNTS_STATUS_BMSTOP						0x00000001
#define	CNTS_STATUS_CNTSTART					0x00000002
#define	CNTS_STATUS_CNTSTOP						0x00000004
#define	CNTS_STATUS_TRGIN						0x00000008
#define	CNTS_STATUS_OVERRUN						0x00000010	

#define	CNTS_STATUS_FIFOFULL					0x00000002
#define	CNTS_STATUS_SGOVERIN					0x00000004
#define	CNTS_STATUS_TRGERR						0x00000008
#define	CNTS_STATUS_CLKERR						0x00000010
#define	CNTS_STATUS_SLAVEHALT					0x00000020
#define	CNTS_STATUS_MASTERHALT					0x00000040

//-------------------------------------------------
// Error codes
//-------------------------------------------------
// Initialize Error
// Common
#define	CNT_ERR_SUCCESS							0				// Normality completion
#define CNT_ERR_INI_RESOURCE					1				// Failed in the acquisition of the resource
#define	CNT_ERR_INI_INTERRUPT					2				// Failed in the registration of the interruption routine
#define	CNT_ERR_INI_MEMORY						3				// Failed in the allocation of the memory
#define	CNT_ERR_INI_REGISTRY					4				// Failed in the access of registry

#define	CNT_ERR_SYS_RECOVERED_FROM_STANDBY		7				// Execute the function CntResetDevice to return from the standby mode.
#define	CNT_ERR_INI_NOT_FOUND_SYS_FILE			8				// Because the ccnt.sys file is not found, it is not possible to initialize it.
#define	CNT_ERR_INI_DLL_FILE_VERSION			9				// Because the version information on the ccnt.dll file cannot be retrieved, it is not possible to initialize it.
#define	CNT_ERR_INI_SYS_FILE_VERSION			10				// Because the version information on the ccnt.sys file cannot be retrieved, it is not possible to initialize it.
#define	CNT_ERR_INI_NO_MATCH_DRV_VERSION		11				// Because the version information of ccnt.dll is not corresponding to the version information of ccnt.sys, it is not possible to initialize it.
// CNT

// DLL Error
// Common
#define	CNT_ERR_DLL_DEVICE_NAME					10000			// The devicename which wasn't registered by a device manager was specified
#define	CNT_ERR_DLL_INVALID_ID					10001			// Invalid ID was specified
#define	CNT_ERR_DLL_CALL_DRIVER					10002			// CNT driver can't be called
#define	CNT_ERR_DLL_CREATE_FILE					10003			// Failed in the creation of the file
#define	CNT_ERR_DLL_CLOSE_FILE					10004			// Failed in the closing of the file
#define	CNT_ERR_DLL_CREATE_THREAD				10005			// Failed in the creation of the thread
#define	CNT_ERR_INFO_INVALID_DEVICE				10050			// Specified device name is not found. Please check spelling
#define	CNT_ERR_INFO_NOT_FIND_DEVICE			10051			// No more device
#define	CNT_ERR_INFO_INVALID_INFOTYPE			10052			// Infomation type is invalid
// CNT
#define	CNT_ERR_DLL_MODE						10100			// Invalid Mode setting
#define CNT_ERR_DLL_BUFF_ADDRESS				10101			// Invalid data buffer address
#define	CNT_ERR_DLL_HWND						10200			// Window handle is invalid

// SYS Error
// Common
#define	CNT_ERR_SYS_MEMORY						20000			// It failed in memory allocation for the object preparation
#define	CNT_ERR_SYS_NOT_SUPPORTED				20001			// This function can't be used by this device.
#define	CNT_ERR_SYS_BOARD_EXECUTING				20002			// Can not use while by another decice works
#define	CNT_ERR_SYS_USING_OTHER_PROCESS			20003			// Can not use becouse another process is using the device

#ifndef STATUS_SYS_USB_CRC
#define	STATUS_SYS_USB_CRC						20020			// USB Error:CRC error
#define	STATUS_SYS_USB_BTSTUFF					20021			// USB Error:Bit pack error
#define	STATUS_SYS_USB_DATA_TOGGLE_MISMATCH		20022			// USB Error:Toggle mismatch
#define	STATUS_SYS_USB_STALL_PID				20023			// USB Error:Stall PID
#define	STATUS_SYS_USB_DEV_NOT_RESPONDING		20024			// USB Error:Device ot responding
#define	STATUS_SYS_USB_PID_CHECK_FAILURE		20025			// USB Error:PID check failure
#define	STATUS_SYS_USB_UNEXPECTED_PID			20026			// USB Error:Unexpected PID
#define	STATUS_SYS_USB_DATA_OVERRUN				20027			// USB Error:Data overrun
#define	STATUS_SYS_USB_DATA_UND0RRUN			20028			// USB Error:Data underrun
#define	STATUS_SYS_USB_BUFFER_OVERRUN			20029			// USB Error:Buffer oberrun
#define	STATUS_SYS_USB_BUFFER_UNDERRUN			20030			// USB Error:Buffer underrun
#define	STATUS_SYS_USB_ENDPOINT_HALTED			20031			// USB Error:Endpoint halted
#define	STATUS_SYS_USB_NOT_FOUND_DEVINFO		20032			// USB Error:Not found device infomation
#define STATUS_SYS_USB_ACCESS_DENIED			20033			// Access denied
#define STATUS_SYS_USB_INVALID_HANDLE			20034			// Invalid handle value
#endif
// CNT
#define	CNT_ERR_SYS_MODE						20100			// Invalid mode setting
#define	CNT_ERR_SYS_CH_NO						20201			// Channel number is out of range
#define	CNT_ERR_SYS_CH_NUM						20202			// Number of channels is out of range
#define	CNT_ERR_SYS_CH_VALUE					20203			// Counter value is out of range
#define	CNT_ERR_SYS_REGNO						20204			// Compare register number is out of range
#define	CNT_ERR_SYS_TIMER_VALUE					20300			// Timer value is out of range.
#define	CNT_ERR_SYS_OUTPUT_LOGIC				20301			// The output logic of the control output signal is out of range.
#define	CNT_ERR_SYS_EVENT_TYPE					20302			// The kind of hardware event is out of range.
#define	CNT_ERR_SYS_PULSE_WIDTH					20303			// The coefficient of one-shot pulse width is out of range.
#define	CNT_ERR_SYS_INPUT_LOGIC					20304			// The input logic of control input signal is out of range.
#define	CNT_ERR_SYS_OUTPUT_DATA					20305			// The output data is out of range.

// CNT Sampling
#define	CNT_ERR_SYS_START_SIGNAL				21000			// The start signal is out of range.
#define	CNT_ERR_SYS_STOP_SIGNAL					21001			// The stop signal is out of range.
#define	CNT_ERR_SYS_CLOCK_SIGNAL				21002			// The clock signal is out of range.
#define	CNT_ERR_SYS_SIGNAL						21003			// The available signal is out of range.
#define	CNT_ERR_SYS_COUNTER_MODE				21004			// The count mode is out of range.
#define	CNT_ERR_SYS_START_TRG					21005			// The start condition is out of range.
#define	CNT_ERR_SYS_COUNT_START_MODE			21006			// The count start condition is out of range.
#define	CNT_ERR_SYS_CLOCK_TRG					21007			// The clock condition is out of range.
#define	CNT_ERR_SYS_STOP_TRG					21008			// The stop condition is out of range.
#define	CNT_ERR_SYS_CLOCK_VAL					21009			// The clock value is out of range.
#define	CNT_ERR_SYS_CLOCK_UNIT					21010			// The unit of clock value is out of range.
#define	CNT_ERR_SYS_STOP_NUM					21011			// The time of sampling stop is out of range.
#define	CNT_ERR_SYS_COUNT_STOP_MODE				21012			// The count stop condition is out of range.
#define	CNT_ERR_SYS_SCAN_NUM					21013			// Frequency of scan of the buffer is out of range.
#define	CNT_ERR_SYS_RING						21014			// Buffer repetition use setting is out of range.
#define	CNT_ERR_SYS_TRANS_COUNT					21015			// The data transfer quantity is out of range.

#define	CNT_ERR_SYS_PARAM						21050			// One of parameter is out of range

#define	CNT_ERR_SYS_BUFFER						21100			// Because the buffer was too large, it was not possible to secure it.
#define	CNT_ERR_SYS_LOCK_MEMORY					21101			// The memory cannot be locked.
#define	CNT_ERR_SYS_SEQUENCE					21102			// Execution procedure error


