/*
 * libslp-tapi
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Ja-young Gu <jygu@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TAPI_EVENT_H__
#define __TAPI_EVENT_H__

#include <tapi_type.h>

__BEGIN_DECLS

#define DBUS_TELEPHONY_CALL_INTERFACE				DBUS_TELEPHONY_SERVICE".Call"

#define TAPI_NOTI_VOICE_CALL_STATUS_IDLE			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusIdle"
#define TAPI_NOTI_VOICE_CALL_STATUS_ACTIVE			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusActive"
#define TAPI_NOTI_VOICE_CALL_STATUS_HELD			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusHeld"
#define TAPI_NOTI_VOICE_CALL_STATUS_DIALING			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusDialing"
#define TAPI_NOTI_VOICE_CALL_STATUS_ALERT			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusAlert"
#define TAPI_NOTI_VOICE_CALL_STATUS_INCOMING		DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusIncoming"
#define TAPI_NOTI_VOICE_CALL_STATUS_WAITING			DBUS_TELEPHONY_CALL_INTERFACE":VoiceCallStatusWaiting"

#define TAPI_NOTI_VIDEO_CALL_STATUS_IDLE			DBUS_TELEPHONY_CALL_INTERFACE":VideoCallStatusIdle"
#define TAPI_NOTI_VIDEO_CALL_STATUS_ACTIVE			DBUS_TELEPHONY_CALL_INTERFACE":VideoCallStatusActive"
#define TAPI_NOTI_VIDEO_CALL_STATUS_DIALING			DBUS_TELEPHONY_CALL_INTERFACE":VideoCallStatusDialing"
#define TAPI_NOTI_VIDEO_CALL_STATUS_ALERT			DBUS_TELEPHONY_CALL_INTERFACE":VideoCallStatusAlert"
#define TAPI_NOTI_VIDEO_CALL_STATUS_INCOMING		DBUS_TELEPHONY_CALL_INTERFACE":VideoCallStatusIncoming"

#define TAPI_NOTI_CALL_INFO_CALL_CONNECTED_LINE		DBUS_TELEPHONY_CALL_INTERFACE":CallConnectedLine"
#define TAPI_NOTI_CALL_INFO_WAITING					DBUS_TELEPHONY_CALL_INTERFACE":Waiting"
#define TAPI_NOTI_CALL_INFO_CUG						DBUS_TELEPHONY_CALL_INTERFACE":Cug"
#define TAPI_NOTI_CALL_INFO_FORWARDED				DBUS_TELEPHONY_CALL_INTERFACE":Forwarded"
#define TAPI_NOTI_CALL_INFO_BARRED_INCOMING			DBUS_TELEPHONY_CALL_INTERFACE":BarredIncoming"
#define TAPI_NOTI_CALL_INFO_BARRED_OUTGOING			DBUS_TELEPHONY_CALL_INTERFACE":BarredOutgoing"
#define TAPI_NOTI_CALL_INFO_DEFLECTED				DBUS_TELEPHONY_CALL_INTERFACE":Deflected"
#define TAPI_NOTI_CALL_INFO_CLIR_SUPPRESSION_REJECT	DBUS_TELEPHONY_CALL_INTERFACE":ClirSuppressionReject"
#define TAPI_NOTI_CALL_INFO_FORWARD_UNCONDITIONAL	DBUS_TELEPHONY_CALL_INTERFACE":ForwardUnconditional"
#define TAPI_NOTI_CALL_INFO_FORWARD_CONDITIONAL		DBUS_TELEPHONY_CALL_INTERFACE":ForwardConditional"
#define TAPI_NOTI_CALL_INFO_CALL_LINE_IDENTITY		DBUS_TELEPHONY_CALL_INTERFACE":CallLineIdentity"
#define TAPI_NOTI_CALL_INFO_CALL_NAME_INFORMATION	DBUS_TELEPHONY_CALL_INTERFACE":CallNameInformation"
#define TAPI_NOTI_CALL_INFO_FORWARDED_CALL			DBUS_TELEPHONY_CALL_INTERFACE":ForwardedCall"
#define TAPI_NOTI_CALL_INFO_CUG_CALL				DBUS_TELEPHONY_CALL_INTERFACE":CugCall"
#define TAPI_NOTI_CALL_INFO_DEFLECTED_CALL			DBUS_TELEPHONY_CALL_INTERFACE":DeflectedCall"
#define TAPI_NOTI_CALL_INFO_TRANSFERED_CALL			DBUS_TELEPHONY_CALL_INTERFACE":TransferedCall"
#define TAPI_NOTI_CALL_INFO_HELD					DBUS_TELEPHONY_CALL_INTERFACE":Held"
#define TAPI_NOTI_CALL_INFO_ACTIVE					DBUS_TELEPHONY_CALL_INTERFACE":Active"
#define TAPI_NOTI_CALL_INFO_JOINED					DBUS_TELEPHONY_CALL_INTERFACE":Joined"
#define TAPI_NOTI_CALL_INFO_RELEASED_ON_HOLD		DBUS_TELEPHONY_CALL_INTERFACE":ReleaseOnHold"
#define TAPI_NOTI_CALL_INFO_TRANSFER_ALERT			DBUS_TELEPHONY_CALL_INTERFACE":TransferAlert"
#define TAPI_NOTI_CALL_INFO_TRANSFERED				DBUS_TELEPHONY_CALL_INTERFACE":Transfered"
#define TAPI_NOTI_CALL_INFO_CF_CHECK_MESSAGE		DBUS_TELEPHONY_CALL_INTERFACE":CfCheckMessage"

#define TAPI_NOTI_CALL_SOUND_PATH					DBUS_TELEPHONY_CALL_INTERFACE":SoundPath"
#define TAPI_NOTI_CALL_SOUND_RINGBACK_TONE			DBUS_TELEPHONY_CALL_INTERFACE":SoundRingbackToneControl"
#define TAPI_NOTI_CALL_SOUND_WBAMR					DBUS_TELEPHONY_CALL_INTERFACE":SoundWbamr"
#define TAPI_NOTI_CALL_SOUND_EQUALIZATION			DBUS_TELEPHONY_CALL_INTERFACE":SoundEqualiztion"
#define TAPI_NOTI_CALL_SOUND_NOISE_REDUCTION		DBUS_TELEPHONY_CALL_INTERFACE":SoundNoiseReduction"


#define DBUS_TELEPHONY_MODEM_INTERFACE				DBUS_TELEPHONY_SERVICE".Modem"
#define TAPI_NOTI_MODEM_POWER						DBUS_TELEPHONY_MODEM_INTERFACE":Power"
#define TAPI_NOTI_MODEM_DUN_PIN_CTRL				DBUS_TELEPHONY_MODEM_INTERFACE":DunPinCtrl"
#define TAPI_NOTI_MODEM_DUN_EXTERNAL_CALL			DBUS_TELEPHONY_MODEM_INTERFACE":DunExternalCall"
#define TAPI_PROP_MODEM_POWER						DBUS_TELEPHONY_MODEM_INTERFACE":power"

#define DBUS_TELEPHONY_SIM_INTERFACE				DBUS_TELEPHONY_SERVICE".Sim"
#define TAPI_NOTI_SIM_STATUS						DBUS_TELEPHONY_SIM_INTERFACE":Status"

#define DBUS_TELEPHONY_SAP_INTERFACE				DBUS_TELEPHONY_SERVICE".Sap"
#define TAPI_NOTI_SAP_STATUS						DBUS_TELEPHONY_SAP_INTERFACE":Status"
#define TAPI_NOTI_SAP_DISCONNECT					DBUS_TELEPHONY_SAP_INTERFACE":Disconnect"

#define DBUS_TELEPHONY_SAT_INTERFACE				DBUS_TELEPHONY_SERVICE".SAT"
#define TAPI_NOTI_SAT_SETUP_MENU					DBUS_TELEPHONY_SAT_INTERFACE":SetupMenu"
#define TAPI_NOTI_SAT_DISPLAY_TEXT					DBUS_TELEPHONY_SAT_INTERFACE":DisplayText"
#define TAPI_NOTI_SAT_SELECT_ITEM					DBUS_TELEPHONY_SAT_INTERFACE":SelectItem"
#define TAPI_NOTI_SAT_GET_INKEY						DBUS_TELEPHONY_SAT_INTERFACE":GetInkey"
#define TAPI_NOTI_SAT_GET_INPUT						DBUS_TELEPHONY_SAT_INTERFACE":GetInput"
#define TAPI_NOTI_SAT_REFRESH						DBUS_TELEPHONY_SAT_INTERFACE":Refresh"
#define TAPI_NOTI_SAT_SEND_SMS						DBUS_TELEPHONY_SAT_INTERFACE":SendSMS"
#define TAPI_NOTI_SAT_SETUP_EVENT_LIST				DBUS_TELEPHONY_SAT_INTERFACE":SetupEventList"
#define TAPI_NOTI_SAT_SEND_DTMF						DBUS_TELEPHONY_SAT_INTERFACE":SendDtmf"
#define TAPI_NOTI_SAT_SESSION_END_EVENT				DBUS_TELEPHONY_SAT_INTERFACE":EndProactiveSession"
#define TAPI_NOTI_SAT_MO_SMS_CTRL					DBUS_TELEPHONY_SAT_INTERFACE":MoSmsCtrl"

#define DBUS_TELEPHONY_PB_INTERFACE					DBUS_TELEPHONY_SERVICE".Phonebook"
#define TAPI_NOTI_PB_STATUS							DBUS_TELEPHONY_PB_INTERFACE":Status"

// Network
#define DBUS_TELEPHONY_NETWORK_INTERFACE			DBUS_TELEPHONY_SERVICE".Network"
#define TAPI_NOTI_NETWORK_REGISTRATION_STATUS		DBUS_TELEPHONY_NETWORK_INTERFACE":RegistrationStatus"
#define TAPI_NOTI_NETWORK_CELLINFO					DBUS_TELEPHONY_NETWORK_INTERFACE":CellInfo"
#define TAPI_NOTI_NETWORK_INFO						DBUS_TELEPHONY_NETWORK_INTERFACE":Info"
#define TAPI_NOTI_NETWORK_CHANGE					DBUS_TELEPHONY_NETWORK_INTERFACE":Change"
#define TAPI_NOTI_NETWORK_TIMEINFO					DBUS_TELEPHONY_NETWORK_INTERFACE":TimeInfo"
#define TAPI_NOTI_NETWORK_IDENTITY					DBUS_TELEPHONY_NETWORK_INTERFACE":Identity"

// SS
#define DBUS_TELEPHONY_SS_INTERFACE					DBUS_TELEPHONY_SERVICE".Ss"
#define TAPI_NOTI_SS_USSD							DBUS_TELEPHONY_SS_INTERFACE":NotifyUSSD"

// PS
#define TAPI_NOTI_PS_DUN_PIN_CONTROL "org.tizen.telephony.Ps.PinCtrl"

// SMS
#define DBUS_TELEPHONY_SMS_INTERFACE	DBUS_TELEPHONY_SERVICE".sms"
#define TAPI_NOTI_SMS_INCOM_MSG			DBUS_TELEPHONY_SMS_INTERFACE":IncommingMsg"	/* This is an unsolicited Incoming SMS Event*/
#define TAPI_NOTI_SMS_CB_INCOM_MSG		DBUS_TELEPHONY_SMS_INTERFACE":IncommingCbMsg"	/* This is an unsolicited Incoming cell broadcast message*/
#define TAPI_NOTI_SMS_ETWS_INCOM_MSG	DBUS_TELEPHONY_SMS_INTERFACE":IncommingEtwsMsg"	/* This is an unsolicited Incoming cell broadcast message*/
#if 0
#define TAPI_NOTI_SMS_INCOM_EX_MSG "org.tizen.telephony. "		/* This is an extended unsolicited Incoming SMS Event*/
#define TAPI_NOTI_SMS_CB_INCOM_EX_MSG "org.tizen.telephony. "	/* This is an extended unsolicited Incoming cell broadcast message*/
#endif
#define TAPI_NOTI_SMS_MEMORY_STATUS		DBUS_TELEPHONY_SMS_INTERFACE":MemoryStatus"	/* This event is an unsolicited event indicating SIM memory status */
#define TAPI_NOTI_SMS_DEVICE_READY		DBUS_TELEPHONY_SMS_INTERFACE":DeviceReady"	/* Device Ready indication */

__END_DECLS

#endif /* __TAPI_EVENT_H__ */
