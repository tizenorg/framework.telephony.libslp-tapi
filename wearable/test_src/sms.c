/*
 * Telephony test application
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <glib.h>

#include <tapi_common.h>
#include <TelSms.h>
#include <TapiUtility.h>
#include <ITapiNetText.h>

#include "menu.h"
#include "sms.h"
#include "sms_util.h"

// Global Variabl
int dcs_pos = 0;
unsigned int SmsMsgId = 0;
unsigned char tp_mr = 0x00;

char *cmdString[] = { "TAPI_SERVICE_SMS_SEND_UMTS_MSG",
		"TAPI_SERVICE_SMS_READ_MSG", "TAPI_SERVICE_SMS_SAVE_MSG",
		"TAPI_SERVICE_SMS_DELETE_MSG", "TAPI_SERVICE_SMS_GET_COUNT",
		"TAPI_SERVICE_SMS_GET_SCA", "TAPI_SERVICE_SMS_SET_SCA",
		"TAPI_SERVICE_SMS_GET_CB_CONFIG", "TAPI_SERVICE_SMS_SET_CB_CONFIG",
		"TAPI_SERVICE_SMS_SET_MEM_STATUS", "TAPI_SERVICE_SMS_GET_PREF_BEARER",
		"TAPI_SERVICE_SMS_SET_PREF_BEARER",
		"TAPI_SERVICE_SMS_SET_DELIVERY_REPORT",
		"TAPI_SERVICE_SMS_SET_MSG_STATUS", "TAPI_SERVICE_SMS_GET_PARAMS",
		"TAPI_SERVICE_SMS_SET_PARAMS", "TAPI_SERVICE_SMS_GET_PARAMCNT",
		"TAPI_SERVICE_SMS_SEND_CDMA_MSG" };

static void on_resp_send_msg (TapiHandle *handle, int result, void *data,
		void *user_data);
static void on_resp_read_msg (TapiHandle *handle, int result, void *data,
		void *user_data);
static void on_resp_save_msg (TapiHandle *handle, int result, void *data,
		void *user_data);
static void on_resp_DeliverReport_msg (TapiHandle *handle, int result,
		void *data, void *user_data);

#ifdef TODO_BY_JYGU
static BOOL EncodeCdmaSmsParamTeleservice(int teleservice_id ,ParamTeleserv_t *ParamTeleserv)
{
	BOOL ret = FALSE;

	if(ParamTeleserv == NULL) {
		printf("[EncodeCdmaSmsParamTeleservice] NULL pointer  \n");
		return ret;
	}

	switch(teleservice_id) {
		case TELESERVICEID_CPT95:
		case TELESERVICEID_CMT95:
		case TELESERVICEID_VMN95:
		case TELESERVICEID_WAP:
		ret = TRUE;
		break;
		default:
		ret = FALSE;
	}

	if(ret == TRUE) {
		ParamTeleserv->param_id = PARAMID_TELESERVICE_ID;
		ParamTeleserv->param_len = 2;
		ParamTeleserv->teleserv_id = teleservice_id;
	}

	return ret;
}

static BOOL EncodeCdmaSmsParamDestAddress(int NumberPlan, char* diallingNum ,ParamAddress_t *ParamAddr)
{
	BOOL ret = FALSE;
	int length = 0;

	if(ParamAddr == NULL || diallingNum == NULL) {
		printf("[EncodeCdmaSmsParamAddress] NULL pointer  \n");
		return ret;
	}

	length = strlen(diallingNum); //remove CR

	ParamAddr->param_id = PARAMID_ADDRESS;
	ParamAddr->len = length;
	ParamAddr->digit = DIGITMODE_4BITDTMF;
	ParamAddr->num = NUMMODE_NONE_DATANETWORK;
	ParamAddr->numtype = NUMBER_TYPE_UNKNOWN;
	ParamAddr->numplan = NumberPlan;

	strncpy((char *)ParamAddr->CHARi, diallingNum, length);

	length +=5;
	ParamAddr->param_len = length;

	ret = TRUE;

	return ret;
}

static BOOL EncodeCdmaSmsParamCallbackAddress(int NumberPlan, char* diallingNum ,ParamCallback_t *ParamCallback)
{
	BOOL ret = FALSE;
	int length = 0;

	if(ParamCallback == NULL || diallingNum == NULL) {
		printf("[EncodeCdmaSmsParamAddress] NULL pointer  \n");
		return ret;
	}

	length = strlen(diallingNum); //remove CR

	ParamCallback->param_id = PARAMID_CALLBACK;
	ParamCallback->digit = DIGITMODE_4BITDTMF;
	ParamCallback->numtype = NUMBER_TYPE_UNKNOWN;
	ParamCallback->numplan = NumberPlan;
	ParamCallback->len = length;
	strncpy((char *)ParamCallback->CHARi, diallingNum, length);

	length +=4;
	ParamCallback->param_len = length;

	ret = TRUE;

	return ret;
}

static BOOL EncodeCdmaSmsParamMsgId(int type, ParamMsgId_t *ParamMsg)
{
	BOOL ret = FALSE;

	if(ParamMsg == NULL) {
		printf("[EncodeCdmaSmsParamMsgId] NULL pointer  \n");
		return ret;
	}

	ParamMsg->param_id = PARAMID_MESSAGE_ID;
	ParamMsg->param_len =3;
	ParamMsg->type = type;
	ParamMsg->msg_id = SmsMsgId++;

	ret = TRUE;

	return ret;
}

static BOOL EncodeCdmaSmsParamUserData(char* SendTxt, ParamUserData_t *ParamUser)
{
	BOOL ret = FALSE;
	int length = 0;

	if(ParamUser == NULL || SendTxt == NULL) {
		printf("[EncodeCdmaSmsParamUserData] NULL pointer  \n");
		return ret;
	}

	length = strlen(SendTxt);

	ParamUser->param_id = PARAMID_USER_DATA;
	ParamUser->encoding = MSGENCODING_7BIT_ASCII;
	strncpy((char *)ParamUser->CHARi, SendTxt, length);

	ParamUser->len = length;
	length += 2;;
	ParamUser->param_len = length;

	ret = TRUE;

	return ret;
}
#endif

static BOOL EncodeCdmaSmsSubmitTpdu (char* diallingNum, int dialNumLen,
		char* msgTxt, int msg_len)
{
#ifdef TODO_BY_JYGU
	ParamTeleserv_t ParamTeleserv = {0,};
	ParamAddress_t ParamAddr = {0,};
	ParamMsgId_t ParamMsg = {0,};
	ParamUserData_t ParamUser = {0,};

	int i;
	int requestId = 0;

	msg("EncodeCdmaSmsSubmitTpdu Func Enter");

	TelSmsMsgInfo_t *pDataPackage = malloc(sizeof(TelSmsMsgInfo_t));
	memset(pDataPackage, 0, sizeof(TelSmsMsgInfo_t));

	pDataPackage->MsgType = SMS_MESSAGETYPE_SUBMIT;

	//1 TeleService Identifier
	EncodeCdmaSmsParamTeleservice(TELESERVICEID_CMT95, &ParamTeleserv);
	pDataPackage->ParamMask |= SMS_PARAM_TELESERVICE_MASK;
	memcpy(&pDataPackage->MsgData.OutSubmit.TeleService, &ParamTeleserv.teleserv_id, sizeof(unsigned short));
	msg("teleservice at TEST APP: 0x%x", pDataPackage->MsgData.OutSubmit.TeleService);

	//1 Destination Address
	diallingNum[dialNumLen] = '\0';
	EncodeCdmaSmsParamDestAddress(NUMBER_PLAN_UNKNOWN, diallingNum, &ParamAddr);
	pDataPackage->ParamMask |= SMS_PARAM_ADDRESS_MASK;
	pDataPackage->MsgData.OutSubmit.DstAddr.Digit = ParamAddr.digit;
	pDataPackage->MsgData.OutSubmit.DstAddr.NumberMode = ParamAddr.num;
	pDataPackage->MsgData.OutSubmit.DstAddr.NumberType = ParamAddr.numtype;
	pDataPackage->MsgData.OutSubmit.DstAddr.NumberPlan = ParamAddr.numplan;
	pDataPackage->MsgData.OutSubmit.DstAddr.szAddrLength = ParamAddr.len;
	memcpy(pDataPackage->MsgData.OutSubmit.DstAddr.szAddress, ParamAddr.CHARi, ParamAddr.len);

	//1  Message Identifier
	EncodeCdmaSmsParamMsgId(MESSAGETYPE_SUBMIT, &ParamMsg);
	pDataPackage->ParamMask |= SMS_PARAM_MESSAGE_ID_MASK;
	pDataPackage->MsgData.OutSubmit.MsgId = ParamMsg.type;
	pDataPackage->MsgType = ParamMsg.type;

	//1  bearer
	pDataPackage->ParamMask |= SMS_PARAM_BEARER_REPLY_MASK;
	pDataPackage->MsgData.OutSubmit.ReplySeqNumber = 1;

#if 0
	//1 Callback Address
	EncodeCdmaSmsParamCallbackAddress(NUMBER_PLAN_UNKNOWN, CallbackNum, &Paramcallback);
	pDataPackage->ParamMask |= SMS_PARAM_CALLBACK_MASK;
	pDataPackage->MsgData.OutSubmit.CallBackNumber.Digit = Paramcallback.digit;
	pDataPackage->MsgData.OutSubmit.CallBackNumber.NumberType = Paramcallback.numtype;
	pDataPackage->MsgData.OutSubmit.CallBackNumber.NumberPlan = Paramcallback.numplan;
	pDataPackage->MsgData.OutSubmit.CallBackNumber.szAddrLength = Paramcallback.len;
	memcpy(pDataPackage->MsgData.OutSubmit.CallBackNumber.szAddress, Paramcallback.CHARi, Paramcallback.len);
#endif
	//1 User Date
	msgTxt[msg_len - 1] = '\0';
	EncodeCdmaSmsParamUserData(msgTxt, &ParamUser);
	pDataPackage->ParamMask |= SMS_PARAM_USER_DATA_MASK;
	pDataPackage->MsgData.OutSubmit.MsgEncoding = ParamUser.encoding;
	pDataPackage->MsgData.OutSubmit.MsgLength = ParamUser.len;
	memcpy(pDataPackage->MsgData.OutSubmit.szData, ParamUser.CHARi, ParamUser.len);

	msg("");
	msg("=============== Test App Message =================");
	msg(" - MsgType: %d", pDataPackage->MsgType);
	msg(" - ParamMask: 0x%08x", pDataPackage->ParamMask);
	printf("0000: ");
	for (i = 0; i < sizeof(TelSmsMsgInfo_t); i++) {
		printf("%02x ", *(((unsigned char *) pDataPackage) + i));
		if ((i + 1) % 8 == 0)
		printf("  ");

		if ((i + 1) % 16 == 0)
		printf("\n%04x: ", i+1);
	}
	printf("\n");
	fflush(stdout);

	msg("==============================================");

	returnStatus = tel_send_sms_msg(pDataPackage, 0x26, &requestId); //more to send is false since it is not concatenated.for concatenated send 1

	msg("tel_send_sms_msg() requestId: %d", requestId);

	free(pDataPackage);

#endif
	return TRUE;
}

static BOOL DecodeCellBroadcastMsg (int length, char * pPDU)
{
	int msgLength;
	int sn = 0; //serial number
	int msgID; //message identifier
	Sms_coding_scheme dcs;

	unsigned char page[2];
	int contents_length;
	char contents[SMS_CB_SIZE_MAX];

	unsigned char gs;
	unsigned char msgCode;
	unsigned char updateNumber;

	if (pPDU == NULL ) {
		msg("pData is Null")
		return FALSE;
	}

	msg("cb msg type is %x", pPDU[0]);
	msg("cb msg len is %x", pPDU[1]);

	msg("$$$$$$$$$$$$$$$length of cb msg is %d", length);
	sn = (pPDU[2] << 8) | pPDU[1];

	gs = (pPDU[2] & 0xC0) >> 6;  //bit 7, bit 6

	msgCode = ( ( (pPDU[2] & 0x3F) << 4) | pPDU[3]) & 0xF0;

	updateNumber = pPDU[3] & 0x0F;  //bit3, bit2, bit1, bit0

	msgID = pPDU[4] << 4 | pPDU[3];

	SmsUtilDecodeDCS (&dcs, pPDU[6]);

	page[0] = pPDU[7] & 0x0F; //total page
	page[1] = (pPDU[7] & 0xF0) >> 4; //current page

	msgLength = length - 2;

	contents_length = msgLength - 6;

	if (dcs.alphabet_type == SMS_ALPHABET_DEFAULT) {
		unsigned char inData[SMS_CB_SIZE_MAX + 1];

		memset (inData, 0x00, SMS_CB_SIZE_MAX + 1);

		memcpy ((void*) inData, (void*) &pPDU[8], contents_length);
		SmsUtilUnpackGSMCode (contents, &pPDU[8], msgLength);
	}
	else {
		memcpy (contents, &pPDU[8], msgLength);
		contents[msgLength] = 0;
	}

	printf ("*************************************\n");
	printf ("serical number : 0x%04x \n", sn);
	printf ("Geographical Scope: 0x%x\n", gs);
	printf ("message code : 0x%x\n", msgCode);
	printf ("update Number : 0x%x\n", updateNumber);
	printf ("message identifier :  0x%x\n", msgID);
	printf ("DCS-Commpressed?: %d (1: true)\n", dcs.bCompressed);
	printf ("DCS-coding_group_type:  %x\n", dcs.coding_group_type);
	printf ("contents bytes size : %d\n", contents_length);
	printf ("page : (%d /%d) (page /total ) \n", page[1], page[0]);
	printf ("contents: %s\n", contents);
	printf ("*************************************\n");

	return TRUE;
}

static BOOL EncodeSmsSubmitTpdu (MManager *mm, char* diallingNum,
		int dialNumLen, char* msg, int msg_len)
{
	TapiHandle *handle = menu_manager_ref_user_data (mm);

	TPDU_SMS_SUBMIT tpdu_submit;

	unsigned char packet[TAPI_NETTEXT_MSG_SIZE_MAX];

	unsigned char SCA[TAPI_NETTEXT_SCADDRESS_LEN_MAX + 1];
	int ret = 0;

	//	unsigned char tp_mr = 0x03;
	tp_mr++;
	unsigned char tp_pid = 0; //reaplace type (65)
	unsigned char tp_dcs; //=17; //class_1(17),class_2(18)
	unsigned char tp_vp;

	int index = 0, ScIndex = 0;
	int i;
	int requestId = 0;
	unsigned char sca_len = 0;
	TapiResult_t returnStatus;

	TelSmsDatapackageInfo_t *pDataPackage = NULL;

	memset (packet, 0, TAPI_NETTEXT_MSG_SIZE_MAX);

	/************SCA ADDRESS GET START**************/
	/*
	 returnStatus = TelTapiSmsGetSCA(&sc_addr,0);
	 printf("Service center addr returned from TAPI SCA address %s returnStatus %d\n",sc_addr.szDiallingNum,returnStatus);
	 SmsUtilDecodeAddrField(decodeScaAddr, &sc_addr.szDiallingNum[0],&sc_addr.Ton, &sc_addr.Npi);
	 sca_len = strlen( decodeScaAddr );

	 memcpy( SCA, decodeScaAddr, sca_len);
	 SCA[sca_len] = '\0';
	 */
	msg("Enter SCA: ");
	memset (SCA, 0, sizeof (SCA));

	ret = read (0, SCA, sizeof (SCA) - 1);
	if (ret <= 0) {
		msg(" NULL msg can NOT be sent ");
		return -1;
	}
	SCA[ret] = '\0';

	pDataPackage = malloc (sizeof(TelSmsDatapackageInfo_t));
	memset (pDataPackage, 0, sizeof(TelSmsDatapackageInfo_t));

	sca_len = strlen ((char *) SCA) - 1;

	msg("Decode SCA Address =========");
	msg("SCA Number :%s, SCA Length :%d ", SCA, sca_len);
	msg("========================");

	//SCA ADDRESS GET END

	//SCA

	//TODO : SCA

	//	index +=SmsUtilEncodeAddrField(packet,SCA, strlen(SCA)  ,0x01,0x01);
	ScIndex = SmsUtilEncodeAddrField ((unsigned char*) pDataPackage->Sca,
			(char *) SCA, sca_len, 0x01, 0x01);

	msg("ScIndex is %d", ScIndex);

	// TP-MTI, TP-RD, TP-VPF, TP-SRR, TP_UDHI, TP-RP
	tpdu_submit.msg_type = SMS_TPDU_SUBMIT;
	tpdu_submit.rd = FALSE; //false :accept duplicate msg , true: reject duplicate msg
	tpdu_submit.vpf = SMS_VP_RELATIVE;
	tpdu_submit.srr = FALSE; //false :A status report is not requested , true: A status report is requested
	tpdu_submit.udhi = FALSE; //false: contains only the short message , true :a Header in addition to the short message
	tpdu_submit.rp = FALSE; //false :TP Reply Path parameter is not set in this SMS SUBMIT, true : TP Reply Path parameter is set in this SMS SUBMIT

	packet[index] = tpdu_submit.msg_type;					// SUBMIT: bits 0, 1
	packet[index] |= tpdu_submit.rd ? 0x04 : 0;						// bit 2
	packet[index] |= tpdu_submit.vpf << 3;	// bits 3, 4
	packet[index] |= tpdu_submit.srr ? 0x20 : 0;						// bit 5
	packet[index] |= tpdu_submit.udhi ? 0x40 : 0;						// bit 6
	packet[index] |= tpdu_submit.rp ? 0x80 : 0;						// bit 7

	index++;
	msg("index of message ref is %d, msgref is %d", index, tp_mr);
	/* TP-MR */
	packet[index++] = tp_mr;

	// TP-DA
	index += SmsUtilEncodeAddrField (packet + index, diallingNum, dialNumLen,
			0x02, 0x01);

	//msg("DESTINATTION  ADDR Encoded =========");

	//TP-PID
	packet[index++] = tp_pid;

	// TP_DCS (Data Coding Scheme)

	tpdu_submit.dcs.bCompressed = FALSE;
	tpdu_submit.dcs.bmsg_class_set = TRUE;
	tpdu_submit.dcs.coding_group_type = SMS_CODGRP_SM_GENERAL_DCS;
	tpdu_submit.dcs.alphabet_type = SMS_ALPHABET_DEFAULT;
	tpdu_submit.dcs.class_type = SMS_CLASS_2;

	SmsUtilEncodeDCS (&tp_dcs, &tpdu_submit.dcs);

	packet[index++] = tp_dcs;

	//msg("DCS Encoded:tp_dcs =%d =========",tp_dcs);

	//TP-VP

	tpdu_submit.vp.vp_rel_type = SMS_VP_REL_6H;
	tpdu_submit.vp.vp_type = SMS_VP_RELATIVE;
	tpdu_submit.vp.vpValue = 0xff;

	SmsUtilEncodeValidity (&tp_vp, &tpdu_submit.vp);

	//tp_vp =65;
	packet[index++] = tp_vp;
	//msg("Validity Encoded :tp_vp =%d =========",tp_vp);

	// UDL
	packet[index++] = msg_len;

	// TP-UD

	if (tpdu_submit.dcs.alphabet_type == SMS_ALPHABET_DEFAULT) {
		int pos;
		pos = SmsUtilPackGSMCode (packet + index, msg, msg_len);
		index += pos;
	}

	msg("Send packet to phonseSever[%d] -----", index);

	for (i = 0; i < index; i++) {
		msg("[%02x]", packet[i]);
		if (i % 10 == 9)
			msg("\n");
	}
	msg("\n");

	memcpy (pDataPackage->szData, packet, index);
	pDataPackage->MsgLength = index;

	msg("***Sending the Message (Api:SendMsg)***");

	msg("Length : %d", pDataPackage->MsgLength);

	returnStatus = tel_send_sms (handle, pDataPackage, 0, on_resp_send_msg,
			NULL );

	msg("SendMsg : returnStatus=%d requestId=%d", returnStatus, requestId);

	free (pDataPackage);

	return TRUE;

#if 0
	TPDU_SMS_SUBMIT tpdu_submit;
	unsigned char entered_SCA[SMS_SCADDRESS_LEN_MAX]; //send SMS �Ҷ� ����ϴ� ���� SCA��
	int ret = 0;

	//	unsigned char tp_mr = 0x03;
	tp_mr++;
	unsigned char tp_pid = 0;//reaplace type (65)
	unsigned char tp_dcs;//=17; //class_1(17),class_2(18)
	unsigned char tp_vp;

	int index = 0, ScIndex = 0;
	int i;
	unsigned char sca_len =0;
	gboolean returnStatus;

	int msgLength = 0; /**< Size of array szData (which is actual TPDU message) */
	unsigned char szData[SMS_MSG_SIZE_MAX]; /**<SMS TPDU message */

	TelSmsDatapackageInfo_t *pDataPackage= malloc(sizeof(TelSmsDatapackageInfo_t));

	memset(pDataPackage, 0, sizeof(TelSmsDatapackageInfo_t));
	memset(szData, 0, SMS_MSG_SIZE_MAX);

	/************SCA ADDRESS GET START**************/
	msg("Enter SCA: ");
	memset(entered_SCA,0,sizeof(entered_SCA));

	ret = read(0, entered_SCA, sizeof(entered_SCA));

	if (ret <= 0) {
		msg(" NULL msg can NOT be sent ");
		return -1;
	}

	sca_len=strlen((char *)entered_SCA)-1;

	msg("Decode SCA Address =========");
	msg("SCA Number :%s, SCA Length :%d ",entered_SCA , sca_len);
	msg("========================");

	//SCA ADDRESS GET END

	//SCA
	ScIndex =SmsUtilEncodeAddrField((unsigned char*)pDataPackage->Sca ,(char *)entered_SCA, sca_len ,0x01,0x01);

	msg("ScIndex is %d", ScIndex);

	// TP-MTI, TP-RD, TP-VPF, TP-SRR, TP_UDHI, TP-RP
	tpdu_submit.msg_type = SMS_TPDU_SUBMIT;
	tpdu_submit.rd =FALSE;//false :accept duplicate msg , true: reject duplicate msg
	tpdu_submit.vpf = SMS_VP_RELATIVE;
	tpdu_submit.srr = FALSE;//false :A status report is not requested , true: A status report is requested
	tpdu_submit.udhi = FALSE;//false: contains only the short message , true :a Header in addition to the short message
	tpdu_submit.rp = FALSE;//false :TP Reply Path parameter is not set in this SMS SUBMIT, true : TP Reply Path parameter is set in this SMS SUBMIT

	szData[index] = tpdu_submit.msg_type;// SUBMIT: bits 0, 1
	szData[index] |= tpdu_submit.rd? 0x04 : 0;// bit 2
	szData[index] |= tpdu_submit.vpf << 3;// bits 3, 4
	szData[index] |= tpdu_submit.srr ? 0x20 : 0;// bit 5
	szData[index] |= tpdu_submit.udhi? 0x40 : 0;// bit 6
	szData[index] |= tpdu_submit.rp ? 0x80 : 0;// bit 7

	index++;
	msg("index of message ref is %d, msgref is %d",index,tp_mr);
	/* TP-MR */
	szData[index++] = tp_mr;

	// TP-DA
	index += SmsUtilEncodeAddrField( szData+index, diallingNum, dialNumLen, 0x02, 0x01);

	//msg("DESTINATTION  ADDR Encoded =========");

	//TP-PID
	szData[index++] = tp_pid;

	// TP_DCS (Data Coding Scheme)
	tpdu_submit.dcs.bCompressed = FALSE;
	tpdu_submit.dcs.bmsg_class_set = TRUE;
	tpdu_submit.dcs.coding_group_type =SMS_CODGRP_SM_GENERAL_DCS;
	tpdu_submit.dcs.alphabet_type = SMS_ALPHABET_DEFAULT;
	tpdu_submit.dcs.class_type = SMS_CLASS_2;

	SmsUtilEncodeDCS(&tp_dcs, &tpdu_submit.dcs);

	szData[index++] = tp_dcs;

	//msg("DCS Encoded:tp_dcs =%d =========",tp_dcs);

	//TP-VP
	tpdu_submit.vp.vp_rel_type = SMS_VP_REL_6H;
	tpdu_submit.vp.vp_type = SMS_VP_RELATIVE;
	tpdu_submit.vp.vpValue =0xff;

	SmsUtilEncodeValidity(&tp_vp,&tpdu_submit.vp);

	//tp_vp =65;
	szData[index++] = tp_vp;
	//msg("Validity Encoded :tp_vp =%d =========",tp_vp);

	// UDL
	szData[index++] = msg_len;

	// TP-UD
	if (tpdu_submit.dcs.alphabet_type == SMS_ALPHABET_DEFAULT )
	{
		int pos;
		pos =SmsUtilPackGSMCode( szData + index, msg, msg_len);
		index += pos;
	}

	msg("Send szData to phonseSever[%d] -----", index);

	for(i=0; i< index; i++ )
	{
		msg("[%02x]", szData[i]);
		if( i%10 == 9)
		msg("\n");
	}
	msg("\n");

	memcpy( pDataPackage->szData, szData, index);
	pDataPackage->MsgLength = index;

	msg("***Sending the Message (Api:SendMsg)***");
	msg("Length : %d", msgLength);

	returnStatus = tel_send_sms(handle, pDataPackage, 0, on_resp_send_msg, NULL);

	msg("SendMsg : returnStatus=0x%x", returnStatus);

	return TRUE;
#endif
}

#if 0
static int DecodeSmsSubmitTpdu(int pdu_len, char * pPDU)
{
	TPDU_SMS_SUBMIT tpdu_submit;
	unsigned char scaAddr_len =0;
	int destAddr_len = 0;
	char diallingNum[SMS_ADDRESS_LEN_MAX];
	char scaAddr[SMS_SCADDRESS_LEN_MAX]; //service center address
	char destAddr[SMS_ADDRESS_LEN_MAX];//destination number
	int sca_ton, sca_npi, dest_ton,dest_npi;
	int position;

	position=0;

	/* SCA_ADDR */
	memset(diallingNum, 0, sizeof(diallingNum));

	SmsUtilDecodeAddrField(diallingNum, &pPDU[position],&sca_ton, &sca_npi);

	position+=2;  //include Address-Length, Type of Address

	scaAddr_len = strlen( (char *)diallingNum );

	if ( scaAddr_len % 2 )
	position += scaAddr_len / 2 + 1;
	else
	position += scaAddr_len / 2;

	if ( sca_ton == SMS_TON_INTERNATIONAL )
	{
		scaAddr[0] = '+';
		memcpy( &scaAddr[1], diallingNum, scaAddr_len );
		scaAddr[scaAddr_len+1] = '\0';
	}
	else
	{
		memcpy( scaAddr, diallingNum, scaAddr_len );
		scaAddr[scaAddr_len] = '\0';
	}

	//msg(" sca length: %d , sca # : %s", scaAddr_len, scaAddr);

	/* TP-MTI, TP-RD, TP-VPF,  TP-RP, TP_UDHI, TP-SRR */

	tpdu_submit.msg_type = SMS_TPDU_SUBMIT;// bit 0,1(Message Type Indicator )
	tpdu_submit.rd = ( pPDU[position] & 0x04 ) ? TRUE : FALSE;// bit 2 (Message Type Indicator)
	tpdu_submit.vpf =( pPDU[position] & 0x18) >> 3;//  bits 3, 4 ( validity period format)
	tpdu_submit.srr=( pPDU[position] & 0x20 ) ? TRUE : FALSE;// bit 5 (Status Report Request)
	tpdu_submit.udhi=( pPDU[position] & 0x40 ) ? TRUE : FALSE;// bit 6 (User Data Header Indicator)
	tpdu_submit.rp = ( pPDU[position] & 0x80 ) ? TRUE : FALSE;// bit 7 (Reply Path)

	position++;

	/* TP-MR */
	tpdu_submit.mr = pPDU[position];

	position++;

	/* TP-DA */

	memset(diallingNum, 0, sizeof(diallingNum));

	SmsUtilDecodeAddrField(diallingNum, &pPDU[position],&dest_ton, &dest_npi);

	position+=2;

	destAddr_len = strlen( (char*) diallingNum );
	if ( destAddr_len % 2 )
	position += destAddr_len / 2 + 1;
	else
	position += destAddr_len / 2;

	if ( dest_ton == SMS_TON_INTERNATIONAL )
	{
		destAddr[0] = '+';
		memcpy( &destAddr[1], diallingNum, destAddr_len );
		destAddr[destAddr_len+1] = '\0';
	}
	else
	{
		memcpy( destAddr, diallingNum, destAddr_len );
		destAddr[destAddr_len] = '\0';
	}
	//msg(" dest length: %d , dest # : %s", destAddr_len, destAddr);

	tpdu_submit.desAddr.DialNumLen= destAddr_len;
	memcpy(tpdu_submit.desAddr.szDiallingNum, destAddr , destAddr_len);
	tpdu_submit.desAddr.Npi = dest_npi;
	tpdu_submit.desAddr.Ton = dest_ton;

	/* TP-PID */

	tpdu_submit.pId = pPDU[position];
	position++;

	/* TP DCS */
	SmsUtilDecodeDCS( &tpdu_submit.dcs, pPDU[position] );
	position ++;

	/* TP VP */
	tpdu_submit.vp.vp_type = SMS_VP_RELATIVE;  //temp

	if(tpdu_submit.vp.vp_type == SMS_VP_RELATIVE)
	{
		tpdu_submit.vp.vpValue = pPDU[position];
		tpdu_submit.vp.vp_rel_type = SMS_VP_REL_1D;
		position++;
	}
	else if (tpdu_submit.vp.vp_type == SMS_VP_ABSOLUTE || tpdu_submit.vp.vp_type == SMS_VP_ENHANCED)
	{
		position += 7;
	}

	/* TP UDL */
	tpdu_submit.udl = pPDU[position];

	if ( tpdu_submit.udl> SMS_SMDATA_SIZE_MAX )
	tpdu_submit.udl = SMS_SMDATA_SIZE_MAX;

	position++;

	/* TP UD */
	tpdu_submit.userData = malloc( sizeof ( unsigned char ) * ( SMS_SMDATA_SIZE_MAX + 1 ) );

	memset(tpdu_submit.userData, 0, sizeof ( unsigned char ) * ( SMS_SMDATA_SIZE_MAX + 1 ) );

	if (tpdu_submit.dcs.alphabet_type == SMS_ALPHABET_DEFAULT )
	{
		char inData[SMS_SMDATA_SIZE_MAX+1];

		memset( inData, 0x00, SMS_SMDATA_SIZE_MAX + 1 );

		memcpy( (void*) inData, (void*) &pPDU[position], tpdu_submit.udl );

		SmsUtilUnpackGSMCode((char *)tpdu_submit.userData, inData, (unsigned char) tpdu_submit.udl);
	}

	msg("*************************************");
	msg("Msg Type: TPDU_SUBMIT");

	if(tpdu_submit.rd)
	{
		msg("RD: Reject Duplicate")
	}

	else if(!tpdu_submit.rd)
	{
		msg("RD: Accept Duplicate")
	}

	if(tpdu_submit.srr)
	{
		msg("SRR: A status report is requested")
	}

	else if(!tpdu_submit.srr)
	{
		msg("SRR: A status report is not  requested")
	}

	if(tpdu_submit.udhi)
	{
		msg("UDHI: Contains a Header in addition to the short message.")
	}
	else if(!tpdu_submit.udhi)
	{
		msg("UDHI: Only Short Message")
	}

	if(tpdu_submit.rp)
	{
		msg("RP: Set Reply Path")
	}

	else if(!tpdu_submit.rp)
	{
		msg("RP: Not set Reply Path")
	}

	msg("SCA Addr : %s",scaAddr);
	msg("To : %s" ,destAddr);
	msg("Message : %s " , tpdu_submit.userData);
	msg("*************************************");

	return TRUE;
}
#endif

static int DecodeSmsDeliverTpdu (int tpdu_len, char* pTPDU)
{
	TPDU_SMS_DELIVER tpdu_deliver;
	TmDateTime SCTimeStamp;
	;
	int orgAddr_len = 0;
	char diallingNum[SMS_ADDRESS_LEN_MAX + 1];
	char orgAddr[SMS_ADDRESS_LEN_MAX + 1]; //originating number
	int org_ton, org_npi;
	int position = 0;

	/* TP-MTI, TP-MMS, TP-SRI, TP_UDHI, TP-RP */
	tpdu_deliver.msg_type = SMS_TPDU_DELIVER;
	tpdu_deliver.mms = (pTPDU[position] & 0x04) ? TRUE : FALSE; // bit 2 (Message Type Indicator)
	tpdu_deliver.sri = (pTPDU[position] & 0x20) ? TRUE : FALSE;	// bit 5 (Status Report Indication)
	tpdu_deliver.udhi = (pTPDU[position] & 0x40) ? TRUE : FALSE;// bit 6 (User Data Header Indicator)
	tpdu_deliver.rp = (pTPDU[position] & 0x80) ? TRUE : FALSE;// bit 7 (Reply Path)

	position++;

	/* TP-OA */

	memset (diallingNum, 0, sizeof (diallingNum));

	orgAddr_len = SmsUtilDecodeAddrField (diallingNum, &pTPDU[position],
			&org_ton, &org_npi);
	if (orgAddr_len > SMS_ADDRESS_LEN_MAX - 1)
		orgAddr_len = SMS_ADDRESS_LEN_MAX - 1;

	position += 2;

	if (orgAddr_len % 2)
		position += orgAddr_len / 2 + 1;
	else
		position += orgAddr_len / 2;

	msg("pos = %d, length = %d", position, orgAddr_len);

	if (org_ton == SMS_TON_INTERNATIONAL) {
		orgAddr[0] = '+';
		memcpy (&orgAddr[1], diallingNum, orgAddr_len - 1);
		orgAddr[orgAddr_len + 1] = '\0';
	}
	else {
		memcpy (orgAddr, diallingNum, orgAddr_len);
		orgAddr[orgAddr_len] = '\0';
	}

	/* TP-PID */
	tpdu_deliver.pId = pTPDU[position];

	position++;

	/* TP-DCS */
	SmsUtilDecodeDCS (&tpdu_deliver.dcs, pTPDU[position]);
	dcs_pos = position;
	position++;

	/* TP-SCTS */
	SmsUtilDecodeTimeStamp (&pTPDU[position], &SCTimeStamp);

	position += 7;

	/* TP-UDL */
	tpdu_deliver.udl = pTPDU[position];

	if (tpdu_deliver.udl > SMS_SMDATA_SIZE_MAX)
		tpdu_deliver.udl = SMS_SMDATA_SIZE_MAX;

	position++;

	/* TP-UD */
	tpdu_deliver.userData = malloc (
			sizeof(unsigned char) * (SMS_SMDATA_SIZE_MAX + 1));

	memset (tpdu_deliver.userData, 0,
			sizeof(unsigned char) * (SMS_SMDATA_SIZE_MAX + 1));

	if (tpdu_deliver.dcs.alphabet_type == SMS_ALPHABET_DEFAULT) {
		char inData[SMS_SMDATA_SIZE_MAX + 1];

		memset (inData, 0x00, SMS_SMDATA_SIZE_MAX + 1);

		memcpy ((void*) inData, (void*) &pTPDU[position], tpdu_deliver.udl);

		SmsUtilUnpackGSMCode (tpdu_deliver.userData, inData,
				(unsigned char) tpdu_deliver.udl);
	}

	msg("*************************************");
	msg("Msg Type: TPDU_DELIVER");

	if (tpdu_deliver.rp) {
		msg("RP: Set Reply Path")
	}
	else if (!tpdu_deliver.rp) {
		msg("RP: Not set Reply Path")
	}

	if (tpdu_deliver.sri) {
		msg("SRI: A status report shall be returned to the SME")
	}
	else if (!tpdu_deliver.sri) {
		msg("SRI: A status report shall be not returned to the SME")
	}

	if (tpdu_deliver.mms) {
		msg("MMS: No more messages are waiting for the MS in this SC")
	}
	else if (!tpdu_deliver.mms) {
		msg("MMS: More messages are waiting for the MS in this SC")
	}

	if (tpdu_deliver.udhi) {
		msg("UDHI: Contains a Header in addition to the short message.")
	}
	else if (!tpdu_deliver.udhi) {
		msg("UDHI: Only short message.")
	}

	msg("DcsClass : %x (4 means Class None) ", tpdu_deliver.dcs.class_type);

	msg("From : %10s", orgAddr);
	msg("Time : %d-%d-%d  , %d:%d:%d", SCTimeStamp.year, SCTimeStamp.month,
			SCTimeStamp.day, SCTimeStamp.hour, SCTimeStamp.minute,
			SCTimeStamp.second);
	msg("Message : %s ", tpdu_deliver.userData);
	msg("*************************************");

	return dcs_pos;
}

#if 0
static BOOL EncodeSmsDeliverReportTpdu()
{
	TPDU_SMS_DELIVER_REPORT deliver_report;
	unsigned char packet[500];
	TelSmsDatapackageInfo_t * pDataPackage;
	unsigned char tp_dcs;
	unsigned char mask=0x69;
	int index=0;
	int i;

	TelSmsDatapackageInfo_t del_report;

	memset(&(del_report), 0 , sizeof(TelSmsDatapackageInfo_t));

	pDataPackage = malloc(sizeof(TelSmsDatapackageInfo_t));
	memset(pDataPackage, 0, sizeof(TelSmsDatapackageInfo_t));

	memset(packet, 0, 500);

	/* TP-MTI , TP-UDHI */
	deliver_report.msg_type = SMS_TPDU_DELIVER_REPORT;
	deliver_report.udhi = FALSE;

	packet[index] = deliver_report.msg_type;					//DELIVER REPORT
	packet[index] |= deliver_report.udhi? 0x40 : 0;//bit 6

	index ++;

	/* TP-FCS */
	//if(result==FAIL)
	//{

	//}

	/* TP -PI */
	deliver_report.paraInd = mask;
	packet[index] = deliver_report.paraInd;

	if ( ( mask != 0xFF ) && ( mask != 0 ) )
	{
		index++;
		/* TP-PID */
		if ( mask & 0x01)
		{
			deliver_report.pId = 0x65;
			packet[index++] = deliver_report.pId;
		}

		/* TP-DCS */
		if ( mask & 0x02)
		{
			deliver_report.dcs.bCompressed = FALSE;
			deliver_report.dcs.bmsg_class_set = TRUE;
			deliver_report.dcs.coding_group_type =SMS_CODGRP_SM_GENERAL_DCS;
			deliver_report.dcs.alphabet_type = SMS_ALPHABET_DEFAULT;
			deliver_report.dcs.class_type = SMS_CLASS_2;

			SmsUtilEncodeDCS(&tp_dcs, &deliver_report.dcs);
			packet[index++] = tp_dcs;
		}
		/* TP-UDL */
		if ( mask & 0x04)
		{
			deliver_report.udl =0x00;
			packet[index++] = deliver_report.udl;

			/* TP-UD */

			if (deliver_report.dcs.alphabet_type == SMS_ALPHABET_DEFAULT )
			{
				//SmsUtilPackGSMCode( packet + index, msg, msg_len);
			}
		}
	}
	msg("EncodeSmsDeliverReportTpdu");
	msg("Send packet to phonseSever[%d] -----", index);

	for(i=0; i< index; i++ )
	{
		msg("[%02x]", packet[i]);
		if( i%10 == 9)
		msg("\n");
	}
	msg("\n");
	memcpy( del_report.szData, packet, index);
	del_report.MsgLength = index;
	msg("msgLength :%d",del_report.MsgLength);
	int requestId =0;
	tel_send_sms_deliver_report(&del_report,0, &requestId);	//madhavi
	msg("after send deliver report request id is %d",requestId);
	return TRUE;
}
#endif

#if 0
static BOOL DecodeSmsSubmitReportTpdu(int length , char *data)
{

	TPDU_SMS_SUBMIT_REPORT submit_report;
	TmDateTime SCTimeStamp;;
	int position=1;
	int i=0;
	unsigned char msgRef, tpdu_len;
	int result=0;
	unsigned char mask;

	/* Result */

	if(data == NULL) {
		msg("pData is Null")
		return FALSE;
	}

	msg("length :%d",length);

	for(i=0;i<length;i++)
	msg("[%02x]",data[i]);

	result = data[position];

	msg("In ackrecv (return status) result is %x",result);
	position ++;

	/* Msg Reference */

	msgRef = data[position++];
	msg("In ackrecv  position :%d msgref is %x",position,msgRef);
	position ++;

	/* TPDU Length */

	tpdu_len = data[position];
	msg("In ackrecv position :%d len is %d",position,tpdu_len);

	/**** SUBMIT REPORT TPDU PARSING
	 ***/

	/* TP-MTI , TP-UDHI */
	msg("before TPDU position value:%d",position);

	submit_report.msg_type = data[position] & 0x03; //bit 0,1
	submit_report.udhi = data[position] & 0x40 ? TRUE : FALSE;//bit 6;

	position ++;

	if(result == FAIL)
	{
		/* TP-FCS */
		submit_report.fcs = data[position];
		position ++;
	}

	/* TP-PI  - set to a 1 indicates that a particular optional parameter is present in the fields which follow. */
	/* Masking Bit  - TP -PID (bit 0), TP-DCS(bit 1), TP-UDL(bit 2) */

	submit_report.paraInd = data[position];
	mask = submit_report.paraInd;
	position ++;

	//msg("Parmeter Indication mask =%x", mask);

	/* TP-SCTS */

	SmsUtilDecodeTimeStamp( &data[position], & SCTimeStamp );

	position+=7;

	if( ( mask != 0xFF ) && ( mask != 0 ) )
	{
		/* TP-PID */
		if ( mask & 0x01)
		{
			submit_report.pId= data[position];
			position ++;
			msg("TP-PID :%x", submit_report.pId);
		}

		/* TP-DCS */
		if ( mask & 0x02)
		{
			SmsUtilDecodeDCS( &submit_report.dcs, data[position] );
			position ++;
			msg("TP-DCS :%x",data[position] );
		}

		if ( mask & 0x04)
		{
			/* TP-UDL */
			submit_report.udl = data[position];
			position++;

			msg("TP-UDL :%x",data[position] );

			/* TP-UD */

			submit_report.userData = malloc( sizeof ( unsigned char ) * ( SMS_SMDATA_SIZE_MAX + 1 ) );

			memset(submit_report.userData, 0, sizeof ( unsigned char ) * ( SMS_SMDATA_SIZE_MAX + 1 ) );

			if (submit_report.dcs.alphabet_type == SMS_ALPHABET_DEFAULT )
			{
				char inData[SMS_SMDATA_SIZE_MAX+1];

				memset( inData, 0x00, SMS_SMDATA_SIZE_MAX + 1 );

				memcpy( (void*) inData, (void*) &data[position], submit_report.udl );

				SmsUtilUnpackGSMCode(submit_report.userData, inData, (unsigned char) submit_report.udl);
			}

		}
	}

	msg("*************************************");

	if(result != 0x00)
	msg("SMS SEND FAIL!!")
	else
	msg("SMS SEND SUCCESS!!")

	if(result != 0x00)
	msg("Failure Code : %x",submit_report.fcs)

	msg("*************************************");

	return TRUE;
}
#endif

static int DecodeSmsStatusReportTpdu (int tpdu_len, char* pTPDU)
{
	TPDU_SMS_STATUS_REPORT status_report;

	TmDateTime SCTimeStamp;
	TmDateTime DischargeTime;

	int rcpAddr_len = 0;
	char diallingNum[SMS_ADDRESS_LEN_MAX];

	char rcpAddr[SMS_ADDRESS_LEN_MAX]; //recipient number
	int rcp_ton, rcp_npi;
	int position = 0;
	unsigned int mask;

	/* TP-MTI, TP MMS, TP SRQ, TP_UDHI */

	status_report.msg_type = pTPDU[position] & 0x03; // bit 0,1
	status_report.mms = pTPDU[position] & 0x04 ? TRUE : FALSE; // bit 2
	status_report.srq = pTPDU[position] & 0x20 ? TRUE : FALSE; //bit 5
	status_report.udhi = pTPDU[position] & 0x40 ? TRUE : FALSE;	 //bit 6

	position++;

	/* TP-MR */
	status_report.mr = pTPDU[position];
	position++;

	/* TP-RA */

	memset (diallingNum, 0, sizeof (diallingNum));

	SmsUtilDecodeAddrField (diallingNum, &pTPDU[position], &rcp_ton, &rcp_npi);

	position += 2;

	rcpAddr_len = strlen ((char*) diallingNum);
	if (rcpAddr_len % 2)
		position += rcpAddr_len / 2 + 1;
	else
		position += rcpAddr_len / 2;

	if (rcp_ton == SMS_TON_INTERNATIONAL) {
		rcpAddr[0] = '+';
		memcpy (&rcpAddr[1], diallingNum, rcpAddr_len);
		rcpAddr[rcpAddr_len + 1] = '\0';
	}
	else {
		memcpy (rcpAddr, diallingNum, rcpAddr_len);
		rcpAddr[rcpAddr_len] = '\0';
	}

	status_report.rcpAddr.DialNumLen = rcpAddr_len;
	memcpy (status_report.rcpAddr.szDiallingNum, rcpAddr, rcpAddr_len);
	status_report.rcpAddr.Npi = rcp_npi;
	status_report.rcpAddr.Ton = rcp_ton;

	/* TP-SCTS */
	SmsUtilDecodeTimeStamp (&pTPDU[position], &SCTimeStamp);
	position += 7;

	/* TP-DT */
	SmsUtilDecodeTimeStamp (&pTPDU[position], &DischargeTime);
	position += 7;

	/* TP-ST */
	status_report.status = pTPDU[position];
	position++;

	/* TP-PI */
	status_report.paraInd = pTPDU[position];

	mask = status_report.paraInd;

	if ( (mask != 0xFF) && (mask != 0)) {
		/* Increment only if mask is valid */
		position++;

		/* TP-PID */
		if (mask & 0x01) {
			status_report.pId = pTPDU[position];
			position++;
		}
		/* TP-DCS */
		if (mask & 0x02) {
			SmsUtilDecodeDCS (&status_report.dcs, pTPDU[position]);
			position++;
		}
		if (mask & 0x04) {
			/* TP-UDL */
			status_report.udl = pTPDU[position];
			position++;

			/* TP-UD */

			status_report.userData = malloc (
					sizeof(unsigned char) * (SMS_SMDATA_SIZE_MAX + 1));

			memset (status_report.userData, 0,
					sizeof(unsigned char) * (SMS_SMDATA_SIZE_MAX + 1));

			if (status_report.dcs.alphabet_type == SMS_ALPHABET_DEFAULT) {
				char inData[SMS_SMDATA_SIZE_MAX + 1];

				memset (inData, 0x00, SMS_SMDATA_SIZE_MAX + 1);

				memcpy ((void*) inData, (void*) &pTPDU[position],
						status_report.udl);

				SmsUtilUnpackGSMCode (status_report.userData, inData,
						(unsigned char) status_report.udl);
			}

		}
	}

	msg("*************************************");
	msg("Msg Type: STATUS_REPORT");
	if (status_report.mms) {
		msg("MMS: No more messages are waiting for the MS in this SC")
	}
	else if (!status_report.mms) {
		msg("MMS: More messages are waiting for the MS in this SC")
	}

	if (status_report.srq) {
		msg("SRQ: the result of an SMS COMMAND ")
	}
	else if (!status_report.srq) {
		msg("SRQ: the result of a SMS SUBMIT.")
	}

	if (status_report.udhi) {
		msg("UDHI: Contains a Header in addition to the short message.")
	}
	else if (!status_report.udhi) {
		msg("UDHI: Only Short Message")
	}

	msg("STATUS:%x", status_report.status);
	if (status_report.status == 0x00) {
		msg("STATUS : Short message received by the SME")
	}
	else if (status_report.status == 0x01) {
		msg(
				"STATUS : Short message forwarded by the SC to the SMEbut the SC is unable to confirm delivery")
	}
	else if (status_report.status == 0x02) {
		msg("STATUS : Short message replaced by the SC")
	}

	msg("Recipient Number : %s", rcpAddr);
	msg("SC Time Stamp : %d-%d-%d  , %d:%d:%d", SCTimeStamp.year,
			SCTimeStamp.month, SCTimeStamp.day, SCTimeStamp.hour,
			SCTimeStamp.minute, SCTimeStamp.second);
	msg("Discharge Time : %d-%d-%d  , %d:%d:%d", DischargeTime.year,
			DischargeTime.month, DischargeTime.day, DischargeTime.hour,
			DischargeTime.minute, DischargeTime.second);

	if (mask & 0x04)
		msg("Message : %s ", status_report.userData);

	msg("*************************************");

	return 1;
}

static void on_noti_sms_incom_msg (TapiHandle *handle, const char *noti_id,
		void *data, void *user_data)
{
	int scaAddr_len = 0;
	char * pTPDU;
	int tpdu_len = 0;
	char diallingNum[TAPI_NETTEXT_ADDRESS_LEN_MAX + 1] = { 0, };
	char scaAddr[TAPI_NETTEXT_SCADDRESS_LEN_MAX + 2] = { 0, }; //service center address
	int sca_ton, sca_npi;
	int position;

	unsigned char MTI = 0;
	unsigned char MMS = 0;
	unsigned char SRI = 0;
	unsigned char UDHI = 0;
	unsigned char RP = 0;

	Sms_coding_scheme dcs;
	TelSmsDatapackageInfo_t * datapackage;
	TapiResult_t returnStatus;
	position = 0;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_SMS_INCOM_MSG);

	if (data == NULL ) {
		msg("data is Null")
		return;
	}

	datapackage = (TelSmsDatapackageInfo_t *) data;

	memset (diallingNum, 0, sizeof (diallingNum));

	SmsUtilDecodeAddrField (diallingNum, (char *) datapackage->Sca, &sca_ton,
			&sca_npi);

	scaAddr_len = strlen (diallingNum);
	if (scaAddr_len > TAPI_NETTEXT_SCADDRESS_LEN_MAX)
		scaAddr_len = TAPI_NETTEXT_SCADDRESS_LEN_MAX;

	if (sca_ton == SMS_TON_INTERNATIONAL) {
		scaAddr[0] = '+';
		memcpy (&scaAddr[1], diallingNum, scaAddr_len - 1);
	}
	else {
		memcpy (scaAddr, diallingNum, scaAddr_len);
	}

	msg("Sc address in test app is %s", scaAddr);

	RP = datapackage->szData[position] & 0x80;
	UDHI = datapackage->szData[position] & 0x40;
	SRI = datapackage->szData[position] & 0x20;
	MMS = datapackage->szData[position] & 0x04;
	MTI = datapackage->szData[position] & 0x03;

	msg("RP [%x]", RP);
	msg("UDHI [%x]", UDHI);
	msg("SRI [%x]", SRI);
	msg("MMS [%x]", MMS);
	msg("MTI [%02x]", MTI);

	tpdu_len = datapackage->MsgLength;

	pTPDU = malloc (sizeof(unsigned char) * tpdu_len);

	memcpy (pTPDU, &datapackage->szData[position], tpdu_len);

	if (MTI == SMS_TPDU_DELIVER) {
		DecodeSmsDeliverTpdu (tpdu_len, pTPDU);

		msg("dcs_pos : %d", dcs_pos);

		SmsUtilDecodeDCS (&dcs, datapackage->szData[position + dcs_pos]);

		//if(dcs.class_type == TAPI_NETTEXT_CLASS_2)
		{
			msg("dcs type is of class2");
			TelSmsData_t WriteData;

			memset (&WriteData, 0, sizeof(TelSmsData_t));

			memcpy (WriteData.SmsData.Sca, datapackage->Sca,
					TAPI_SIM_SMSP_ADDRESS_LEN);

			WriteData.SmsData.MsgLength = datapackage->MsgLength;

			memcpy (WriteData.SmsData.szData, datapackage->szData,
					datapackage->MsgLength);

			WriteData.MsgStatus = TAPI_NETTEXT_STATUS_READ;

			returnStatus = tel_write_sms_in_sim (handle, &WriteData,
					on_resp_save_msg, NULL );

			msg("returnStatus for tel_write_sms_in_sim(): 0x%x", returnStatus);
		}

	}
	else if (MTI == SMS_TPDU_STATUS_REPORT) {
		DecodeSmsStatusReportTpdu (tpdu_len, pTPDU);
	}

	TelSmsDatapackageInfo_t * del_report = NULL;

	del_report = malloc (sizeof(TelSmsDatapackageInfo_t));

	memset (del_report, 0, sizeof(TelSmsDatapackageInfo_t));

	memcpy (del_report->Sca, datapackage->Sca, TAPI_SIM_SMSP_ADDRESS_LEN);

	del_report->szData[0] = SMS_TPDU_DELIVER_REPORT;	//TP-UDHI[bit6] : 0
	del_report->szData[1] = 0;// TP-PI = 0; bit2: TP-UDL bit1: TP-DCS bit0: TP-PID (No option field)
	del_report->MsgLength = 2;

	msg("***receive message (Api:SendDeliverreport)****");

	returnStatus = tel_send_sms_deliver_report (handle, del_report,
			TAPI_NETTEXT_SENDSMS_SUCCESS, on_resp_DeliverReport_msg, NULL );

	msg("returnStatus for tel_send_sms_deliver_report(): 0x%x", returnStatus);

	free (del_report);

	free (pTPDU);
}

static void on_noti_sms_cb_incom_msg (TapiHandle *handle, const char *noti_id,
		void *data, void *user_data)
{
	TelSmsCbMsg_t *cbMsg = data;
	int length = 0;
	char pPDU[SMS_CB_SIZE_MAX + 3] = { 0, };

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_SMS_CB_INCOM_MSG);

	length = cbMsg->Length;
	pPDU[0] = cbMsg->CbMsgType;
	pPDU[1] = length;
	memcpy (& (pPDU[2]), cbMsg->szMsgData, SMS_CB_SIZE_MAX + 1);

	DecodeCellBroadcastMsg (length, pPDU);
}

static void on_noti_sms_etws_incom_msg (TapiHandle *handle, const char *noti_id,
		void *data, void *user_data)
{
	TelSmsEtwsMsg_t *etwsMsg = data;
	int length = 0;
	char pPDU[TAPI_NETTEXT_ETWS_SIZE_MAX + 3] = { 0, };

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_SMS_ETWS_INCOM_MSG);

	length = etwsMsg->Length;
	pPDU[0] = etwsMsg->EtwsMsgType;
	pPDU[1] = length;
	memcpy (& (pPDU[2]), etwsMsg->szMsgData, TAPI_NETTEXT_ETWS_SIZE_MAX + 1);
}

#if 0
static void on_noti_sms_incom_ex_msg(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	tel_service_object_get_int(notiObj, "ParamMask");
	tel_service_object_get_int(notiObj, "MsgType");

	switch(tel_service_object_get_int(notiObj, "MsgType"))
	{
		case MESSAGETYPE_DELIVER:
			/* Origination address */
			tel_service_object_get_int(notiObj, "OrigAddr.Digit");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberMode");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberType");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberPlan");
			tel_service_object_get_char(notiObj, "OrigAddr.szAddrLength");
			tel_service_object_get_string(notiObj, "OrigAddr.szAddress");

			/* Origination subaddress */
			tel_service_object_get_int(notiObj, "OrigSubAddr.SubType");
			tel_service_object_get_char(notiObj, "OrigSubAddr.Odd");
			tel_service_object_get_char(notiObj, "OrigSubAddr.szAddrLength");
			tel_service_object_get_string(notiObj, "OrigSubAddr.szAddress");

			tel_service_object_get_int(notiObj, "TeleService");
			tel_service_object_get_int(notiObj, "bBearerReplySeqRequest");
			tel_service_object_get_char(notiObj, "ReplySeqNumber");
			tel_service_object_get_int(notiObj, "MsgId");
			tel_service_object_get_int(notiObj, "MsgEncoding");
			tel_service_object_get_int(notiObj, "MsgLength");
			tel_service_object_get_string(notiObj, "szData");

			/* Message center time stamp */
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.year");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.month");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.day");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.hours");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.minutes");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.seconds");

			/* Validity period - Absolute */
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.year");
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.month");
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.day");
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.hours");
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.minutes");
			tel_service_object_get_int(notiObj, "ValidityPeriodAbs.seconds");

			tel_service_object_get_char(notiObj, "ValidityPeriodRel");

			/* Deferred delivery time - Absolute (not supported) */
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.year");
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.month");
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.day");
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.hours");
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.minutes");
			tel_service_object_get_int(notiObj, "DeferredDelTimeAbs.seconds");

			/* Deferred delivery time - Relative (not supported) */
			tel_service_object_get_char(notiObj, "DeferredDelTimeRel");

			tel_service_object_get_int(notiObj, "Priority");
			tel_service_object_get_int(notiObj, "Privacy");
			tel_service_object_get_char(notiObj, "NumMsg");
			tel_service_object_get_int(notiObj, "bUserAckRequest");
			tel_service_object_get_int(notiObj, "bDeliveryAckRequest");
			tel_service_object_get_int(notiObj, "AlertPriority");
			tel_service_object_get_int(notiObj, "MsgLang");

			/* Callback number address */
			tel_service_object_get_int(notiObj, "CallBackNumer.Digit");
			tel_service_object_get_int(notiObj, "CallBackNumer.NumberMode");
			tel_service_object_get_int(notiObj, "CallBackNumer.NumberType");
			tel_service_object_get_int(notiObj, "CallBackNumer.NumberPlan");
			tel_service_object_get_char(notiObj, "CallBackNumer.szAddrLength");
			tel_service_object_get_string(notiObj, "CallBackNumer.szAddress");

			tel_service_object_get_int(notiObj, "Display");

			break;

		case MESSAGETYPE_DELIVERY_ACK:
			/* Origination address */
			tel_service_object_get_int(notiObj, "OrigAddr.Digit");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberMode");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberType");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberPlan");
			tel_service_object_get_char(notiObj, "OrigAddr.szAddrLength");
			tel_service_object_get_string(notiObj, "OrigAddr.szAddress");

			/* Origination subaddress */
			tel_service_object_get_int(notiObj, "OrigSubAddr.SubType");
			tel_service_object_get_char(notiObj, "OrigSubAddr.Odd");
			tel_service_object_get_char(notiObj, "OrigSubAddr.szAddrLength");
			tel_service_object_get_char(notiObj, "OrigSubAddr.szAddress");

			tel_service_object_get_int(notiObj, "TeleService");
			tel_service_object_get_int(notiObj, "bBearerReplySeqRequest");
			tel_service_object_get_char(notiObj, "ReplySeqNumber");
			tel_service_object_get_int(notiObj, "MsgId");
			tel_service_object_get_int(notiObj, "MsgEncoding");
			tel_service_object_get_int(notiObj, "MsgLength");
			tel_service_object_get_string(notiObj, "szData");

			tel_service_object_get_char(notiObj, "UserResponseCode");

			/* Message center time stamp */
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.year");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.month");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.day");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.hours");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.minutes");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.seconds");

			break;

		case MESSAGETYPE_USER_ACK:
			/* Origination address */
			tel_service_object_get_int(notiObj, "OrigAddr.Digit");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberMode");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberType");
			tel_service_object_get_int(notiObj, "OrigAddr.NumberPlan");
			tel_service_object_get_char(notiObj, "OrigAddr.szAddrLength");
			tel_service_object_get_string(notiObj, "OrigAddr.szAddress");

			/* Origination subaddress */
			tel_service_object_get_int(notiObj, "OrigSubAddr.SubType");
			tel_service_object_get_char(notiObj, "OrigSubAddr.Odd");
			tel_service_object_get_char(notiObj, "OrigSubAddr.szAddrLength");
			tel_service_object_get_char(notiObj, "OrigSubAddr.szAddress");

			tel_service_object_get_int(notiObj, "TeleService");
			tel_service_object_get_int(notiObj, "bBearerReplySeqRequest");
			tel_service_object_get_char(notiObj, "ReplySeqNumber");
			tel_service_object_get_int(notiObj, "MsgId");
			tel_service_object_get_int(notiObj, "MsgEncoding");
			tel_service_object_get_int(notiObj, "MsgLength");
			tel_service_object_get_string(notiObj, "szData");

			/* Message center time stamp */
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.year");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.month");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.day");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.hours");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.minutes");
			tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.seconds");

			break;
		default:
			break;
	}
}
#endif

#if 0
static void on_noti_sms_cb_incom_ex_msg(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	tel_service_object_get_string(notiObj, "szData");

	/* Message center time stamp */
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.year");
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.month");
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.day");
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.hours");
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.minutes");
	tel_service_object_get_int(notiObj, "MessageCenterTimeStamp.seconds");

	/* Validity period - Absolute */
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.year");
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.month");
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.day");
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.hours");
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.minutes");
	tel_service_object_get_int(notiObj, "ValidityPeriodAbs.seconds");

	tel_service_object_get_char(notiObj, "ValidityPeriodRel");

	tel_service_object_get_int(notiObj, "Priority");
	tel_service_object_get_int(notiObj, "AlertPriority");
	tel_service_object_get_int(notiObj, "MsgLang");
	tel_service_object_get_int(notiObj, "Display");
}
#endif

static void on_noti_sms_memory_status (TapiHandle *handle, const char *noti_id,
		void *data, void *user_data)
{
	int *memory_status = data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_SMS_MEMORY_STATUS);
	msg(" - memory_status = 0x%x", *memory_status);
}

static void on_noti_sms_ready_status (TapiHandle *handle, const char *noti_id,
		void *data, void *user_data)
{
	gboolean *device_ready = data;

	msg("");
	msgb("event(%s) receive !!", TAPI_NOTI_SMS_DEVICE_READY);
	msg(" - device_ready = %s", *device_ready ? "TRUE" : "FALSE");
}

static void on_resp_send_msg (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	msg("");
	msgb("tel_send_sms() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_read_msg (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	TelSmsData_t * sim_data;
	int scaAddr_len = 0;
	char * pTPDU;
	int tpdu_len = 0;
	char diallingNum[TAPI_NETTEXT_ADDRESS_LEN_MAX + 1] = { 0, };
	char scaAddr[TAPI_NETTEXT_SCADDRESS_LEN_MAX + 2] = { 0, }; //service center address
	int sca_ton, sca_npi;
	int position;

	if (data == NULL ) {
		msg("data is Null");
		return;
	}

	sim_data = (TelSmsData_t *) data;

	if (sim_data->MsgStatus == TAPI_NETTEXT_STATUS_UNREAD)
		msg("Msg Staus : received unread msg")
	else if (sim_data->MsgStatus == TAPI_NETTEXT_STATUS_READ)
		msg("Msg Staus : received read msg")
	else if (sim_data->MsgStatus == TAPI_NETTEXT_STATUS_UNSENT)
		msg("Msg Staus : unsent msg")
	else
		msg("Msg Staus : [%d]", sim_data->MsgStatus)

	msg("First Data [%x]", sim_data->SmsData.szData[0]);
	msg("Second Data [%x]", sim_data->SmsData.szData[1]);
	msg("Third Data [%x]", sim_data->SmsData.szData[2]);
	msg("Fourth Data [%x]", sim_data->SmsData.szData[3]);

	position = 0;
	// SCA_ADDR
	memset (diallingNum, 0, sizeof (diallingNum));

	SmsUtilDecodeAddrField (diallingNum, (char *) sim_data->SmsData.Sca,
			&sca_ton, &sca_npi);

	position += 2;  //include Address-Length, Type of Address

	scaAddr_len = strlen ((char *) diallingNum);
	if (scaAddr_len > TAPI_NETTEXT_SCADDRESS_LEN_MAX - 1)
		scaAddr_len = TAPI_NETTEXT_SCADDRESS_LEN_MAX - 1;

	if (scaAddr_len % 2)
		position += scaAddr_len / 2 + 1;
	else
		position += scaAddr_len / 2;

	if (sca_ton == SMS_TON_INTERNATIONAL) {
		scaAddr[0] = '+';
		memcpy (&scaAddr[1], diallingNum, scaAddr_len);
	}
	else {
		memcpy (scaAddr, diallingNum, scaAddr_len);
	}

	tpdu_len = sim_data->SmsData.MsgLength;

	msg("SCA Number : %s tpdu_len is %d", scaAddr, tpdu_len);

	pTPDU = malloc (sizeof(unsigned char) * tpdu_len);
	if (!pTPDU)
		return;

	msg("bfor memcopy position is %d", position);
	memcpy (pTPDU, & (sim_data->SmsData.szData[0]), tpdu_len);
	msg("after memcpy");

	DecodeSmsDeliverTpdu (tpdu_len, pTPDU);

	free (pTPDU);
}

static void on_resp_save_msg (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int *index = data;

	msg("");
	msgb("tel_write_sms_in_sim() response receive");
	msg(" - result = 0x%x", result);
	msg(" - index = %d", *index);
}

static void on_resp_delete_msg (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int *index = data;

	msg("");
	msgb("tel_delete_sms_in_sim() response receive");
	msg(" - result = 0x%x", result);
	msg(" - index = %d", *index);
}

static void on_resp_DeliverReport_msg (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	int *index = data;

	msg("");
	msgb("tel_send_sms_deliver_report() response receive");
	msg(" - result = 0x%x", result);
	msg(" - index = %d", *index);
}

static void on_resp_set_sms_sca (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	msg("");
	msgb("tel_set_sms_sca() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_set_sms_preferred_bearer (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	msg("");
	msgb("tel_set_sms_preferred_bearer() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_set_sms_cb_config (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	msg("");
	msgb("tel_set_sms_cb_config() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_set_sms_params (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	msg("");
	msgb("tel_set_sms_params() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_set_mem_status (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	msg("");
	msgb("tel_set_sms_mem_status() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_get_sms_sca (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	TelSmsAddressInfo_t *scaInfo = data;
	unsigned int i = 0;

	msg("");
	msgb("tel_get_sms_sca() response receive");
	msg(" - result = 0x%x", result);
	msg(" - TON = %d", scaInfo->Ton);
	msg(" - NPI = %d", scaInfo->Npi);
	msg(" - DialNumLen = %d", scaInfo->DialNumLen);
	msg(" - SCA Num");

	for (i = 0; i < scaInfo->DialNumLen; i++) {
		msg("[%02x]", scaInfo->szDiallingNum[i]);
		if (i % 10 == 9)
			msg("\n");
	}
}

static void on_resp_get_cb_config (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	TelSmsCbConfig_t * CBConfig;
	int i = 0;

	if (data == NULL ) {
		msg("pData is Null")
		return;
	}

	CBConfig = (TelSmsCbConfig_t *) data;

	msg("");
	msgb("tel_get_sms_cb_config() response receive");
	msg(" - result = 0x%x", result);

	msg("=========CB Configuration=========");

	/*** CB Enable/Diable ***/
	if (CBConfig->CBEnabled == TRUE)
		msg("Cell Broadcast Msg Enabled...")
	else
		msg("Cell Broadcast Msg Disabled...")

	/*** Selected ID ***/
	if (CBConfig->Net3gppType == 0x01)
		msg("Network type is 3gpp ")
	else if (CBConfig->Net3gppType == 0x02)
		msg("Network type is CDMA");

	/*** CBMI  Count ***/
	msg("CBMI Range Count: %d \n", CBConfig->MsgIdRangeCount);

	/*** CBMI  List ***/
	if (CBConfig->MsgIdRangeCount != 0) {
		msg("----- CBMI List -----");
		for (i = 0; i < CBConfig->MsgIdRangeCount; i++) {
			msg("From No.%d - [0x%04x]", i,
					CBConfig->MsgIDs[i].Net3gpp.FromMsgId);
			msg("To No.%d - [0x%04x]", i, CBConfig->MsgIDs[i].Net3gpp.ToMsgId);
		}
	}
	msg("==================================");
}

static void on_resp_get_sms_parameters (TapiHandle *handle, int result,
		void *data, void *user_data)
{
	TelSmsParams_t *smsp_param;

	if (data == NULL ) {
		msg("data is Null")
		return;
	}
	smsp_param = (TelSmsParams_t *) data;

	msg("");
	msgb("tel_get_sms_parameters() response receive");
	msg(" - result = 0x%x", result);

	msg("record index is 0x%x", smsp_param->RecordIndex);
	msg("record len  is 0x%x", smsp_param->RecordLen);
	msg("alpha_id len  is 0x%x ", (int )smsp_param->AlphaIdLen);
	msg("alpha_id is %s ", smsp_param->szAlphaId);
	msg("param indicator is  0x%x", smsp_param->ParamIndicator);
	msg("dest dialling num is %s", smsp_param->TpDestAddr.szDiallingNum);
	msg("svcaddr dialling num is %s", smsp_param->TpSvcCntrAddr.szDiallingNum);
	msg("pid 0x%x", smsp_param->TpProtocolId);
	msg("dcs is 0x%x", smsp_param->TpDataCodingScheme);
	msg("validity is 0x%x", smsp_param->TpValidityPeriod);
}

static void on_resp_get_pref_bearer (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	msg("");
	msgb("tel_get_sms_preferred_bearer() response receive");
	msg(" - result = 0x%x", result);
}

static void on_resp_get_paramcnt (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	int * RecordCount;

	if (data == NULL ) {
		msg("data is Null")
		return;
	}

	RecordCount = (int *) data;

	msg("");
	msgb("tel_get_sms_parameter_count() response receive");
	msg(" - result = 0x%x", result);
	msg(" - In param_count_noti the record count is %d", *RecordCount);
}

static void on_resp_get_sms_count (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	static TelSmsStoredMsgCountInfo_t *countInfo;
	int loop_counter = 0;
	TapiResult_t returnStatus = TAPI_API_SUCCESS;

	if (data == NULL ) {
		msg("data is Null")
		return;
	}

	countInfo = (TelSmsStoredMsgCountInfo_t*) data;

	msg("");
	msgb("tel_get_sms_count() response receive");
	msg(" - result = 0x%x", result);

	if (countInfo->UsedCount != 0x00)	//if used count is not zero
			{
		msg("Index LIST..........");
		for (loop_counter = 0; loop_counter < countInfo->UsedCount;
				loop_counter++) {
			msg("[%02x]", countInfo->IndexList[loop_counter]);
			returnStatus = tel_read_sms_in_sim (handle,
					countInfo->IndexList[loop_counter], on_resp_read_msg,
					NULL );
			msg("After read msg: returnstatus %d", returnStatus);
		}
		msg("In MsgCountNotification total cnt is %d, usedcnt is %dapi_err %d",
				countInfo->TotalCount, countInfo->UsedCount, returnStatus);
	}

	msg("In MsgCountNotification total cnt is %d, usedcnt is %d",
			countInfo->TotalCount, countInfo->UsedCount);

}	//Madhavi

static int SendMessage (MManager *mm, struct menu_data *menu)
{
	int ret;
	int msg_len = 0;
	char buf[SMS_ADDRESS_LEN_MAX];
	char message[512];
	char diallingNum[SMS_ADDRESS_LEN_MAX];
	int diallingNum_len = 0;

	memset (buf, 0, sizeof (buf));
	memset (diallingNum, 0, sizeof (diallingNum));
	diallingNum_len = 0;

	msg("Enter destination Number: ");

	ret = read (0, buf, sizeof (buf));
	if (ret < 0) {
		if (errno == EINTR)
			perror ("read(1)");
		return -1;
	}
	else if (ret == 0)
		return ret;

	buf[SMS_ADDRESS_LEN_MAX - 1] = '\0';
	diallingNum_len = strlen (diallingNum);
	memcpy (&diallingNum[diallingNum_len], buf, strlen (buf));

	diallingNum_len = strlen (diallingNum); //recalculate
	msg("dialling num %s and dialling num len is %d", diallingNum,
			diallingNum_len);
	diallingNum[diallingNum_len] = 0;
	diallingNum_len = diallingNum_len - 1;

	msg("Enter Message: ");
	memset (message, 0, sizeof (message));

	ret = read (0, message, sizeof (message) - 1);

	if (ret <= 0) {
		msg(" NULL msg can NOT be sent ");
		return -1;
	}
	message[sizeof (message) - 1] = '\0';

	msg_len = strlen (message);
	message[--msg_len] = 0;

	msg("==========================");
	msg("To :%s", diallingNum);
	msg("Message: %sMsg Length:%d", message, msg_len);
	msg("Dialling number Length : %d", diallingNum_len);
	msg("==========================\n");

	EncodeSmsSubmitTpdu (mm, diallingNum, diallingNum_len, message, msg_len);
	return 1;

}

static int SendMessageCDMA ()
{
	int ret;
	int msg_len = 0;
	char buf[512] = { 0, };
	char message[512] = { 0, };
	char diallingNum[SMS_ADDRESS_LEN_MAX + 1] = { 0, };
	int diallingNum_len = 0;

	printf ("\n");
	printf ("Enter destination Number:\n>> ");
	fflush (stdout);

	ret = read (0, buf, sizeof (buf));
	if (ret < 0) {
		if (errno == EINTR)
			perror ("read(1)");
		return -1;
	}
	else if (ret == 0)
		return ret;

	buf[SMS_ADDRESS_LEN_MAX - 1] = '\0';
	memcpy (diallingNum, buf, sizeof (diallingNum));
	diallingNum_len = strlen (diallingNum);

	printf ("dialling num [%s], dialling num len [%d]\n", diallingNum,
			diallingNum_len);
	printf ("Enter Message\n>> ");
	fflush (stdout);

	ret = read (0, message, sizeof (message) - 1);
	if (ret <= 0) {
		printf (" NULL msg can NOT be sent \n");
		return -1;
	}
	message[sizeof (message) - 1] = '\0';

	msg_len = strlen (message);

	printf ("===========================\n");
	printf ("To: [%s] (len: %d)\n", diallingNum, diallingNum_len);
	printf ("Message: [%s]\nMsg Length: [%d]\n", message, msg_len);
	printf ("===========================\n\n");

	EncodeCdmaSmsSubmitTpdu (diallingNum, diallingNum_len, message, msg_len);
	//EncodeSmsSubmitTpdu(diallingNum, diallingNum_len,message, msg_len) ;

	return 1;
}

static int ReadMessage (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data (mm);
	int selectedNo;
	int ret;
	char buf[100];
	int returnStatus = 0;

	memset (buf, 0, sizeof (buf));

	msg("*************************************");
	msg("1. SIM Message");

	msg("Select Number:");

	ret = read (0, buf, sizeof (buf));

	if (ret < 0) {
		if (errno == EINTR)
			perror ("read(1)");
		return -1;
	}
	else if (ret == 0)
		return ret;

	selectedNo = atoi (buf);
	msg("Selected Num in read message(value is 1) is %d ", selectedNo);
	switch (selectedNo) {
		case 1:

			msg("***Reading the message in SIM***")
			;
			returnStatus = tel_get_sms_count (handle, on_resp_get_sms_count,
					NULL );
			msg("tel_get_sms_count():  0x%x", returnStatus)
			;

			break;
		default:
			msg("Not supported Menu(%d) !!!", selectedNo)
			;
			break;
	}

	return 1;
}

static int DeleteMessage (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data (mm);

	int ret;
	int index;
	char buf[100];

	TapiResult_t returnStatus;

	memset (buf, 0, sizeof (buf));

	msg("Enter delete index >>");

	ret = read (0, buf, sizeof (buf));
	if (ret < 0) {
		if (errno == EINTR)
			perror ("read(1)");
		return -1;
	}
	else if (ret == 0)
		return ret;

	index = atoi (buf);
	msg("index value :%d", index);

	msg("***Deleting the message(Api:DeleteMsg,GetMsgCount)***");

	returnStatus = tel_delete_sms_in_sim (handle, index, on_resp_delete_msg,
			NULL );
	msg("returnstatus  tel_delete_sms_in_sim()  is for delete%d ", returnStatus);
	returnStatus = tel_get_sms_count (handle, on_resp_get_sms_count, NULL );
	msg("returnStatus for tel_get_sms_count()  %d", returnStatus);

	return 1;

}

static int Getting (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data (mm);
	int selectedNo;
	int returnStatus = 0;
	gboolean bReadyStatus = FALSE;

	selectedNo = atoi (menu->key);

	switch (selectedNo) {
		case 1:
			msg("***Getting the SCA(Api: GetSCA)****")
			;
			returnStatus = tel_get_sms_sca (handle, 0, on_resp_get_sms_sca,
					NULL );
			msg("returnstatus for tel_get_sms_sca(): 0x %x", returnStatus)
			;

			break;

		case 2:
			msg("***Getting the CB Configuration(Api: GetCBConfig)***")
			;
			returnStatus = tel_get_sms_cb_config (handle, on_resp_get_cb_config,
					NULL );
			msg("ReturnStatus[%d] ", returnStatus)
			;

			break;

		case 3:
			msg("****Getting the parameter(Api:GetParameter)****")
			;
			returnStatus = tel_get_sms_parameters (handle, 0,
					on_resp_get_sms_parameters, NULL );
			msg("ReturnStatus[%d]]", returnStatus)
			;

			break;

		case 4:
			msg("***Getting preferrredBearer(Api:GetPreferredBearer)***")
			;
			returnStatus = tel_get_sms_preferred_bearer (handle,
					on_resp_get_pref_bearer, NULL );
			msg("ReturnStatus[%d]", returnStatus)
			;

			break;

		case 5:
			msg("***Getting the parameterCount(Api:GetParameterCount)***")
			;
			returnStatus = tel_get_sms_parameter_count (handle,
					on_resp_get_paramcnt, NULL );
			msg("ReturnStatus[%d]", returnStatus)
			;
			break;

		case 6:
			msg("***Getting the SmsCount(Api:GetSmsCount)***")
			;
			returnStatus = tel_get_sms_count (handle, on_resp_get_sms_count,
					NULL );
			msg("ReturnStatus[%d]", returnStatus)
			;

			break;

		case 7:
			msg(
					"***Getting the Sms Ready status(Api:Check_sms_device_status)***")
			;
			returnStatus = tel_check_sms_device_status (handle, &bReadyStatus);
			msg("ReturnStatus[%d]", returnStatus)
			;
			msg("Ready status = %s", bReadyStatus ? "TRUE" : "FALSE")
			;

			break;

		default:
			return -1;

	}

	return 1;
}

static int _get_int()
{
	char buf[255];
	int ret;

	memset (buf, 0, 255);
	ret = read (0, buf, 254);
	if (ret <= 0)
		return 0;

	return atoi(buf);
}

static int Setting (MManager *mm, struct menu_data *menu)
{
	TapiHandle *handle = menu_manager_ref_user_data (mm);

	int settingMenu;
	int ret;
	int i;

	char MemoryStatus[255] = { 0, }; //2006/8/8
	char bearerType[255] = { 0, };  //2006/8/8

	TelSmsCbConfig_t *pCBConfig;

	TelSmsParams_t smsParameters = { 0, };
	TapiResult_t returnStatus;

	settingMenu = atoi (menu->key);

	switch (settingMenu) {
		case 1:  //Set Service Center Number
		{
			msg("*** Setting SCA (API: tel_set_sms_sca()) ****");
			TelSmsAddressInfo_t sca = {0, };
			unsigned char sca_num[TAPI_SIM_SMSP_ADDRESS_LEN + 1];
			unsigned int sca_length = 0;
			unsigned int additional_len = 0;
			unsigned index, j;

			RETRY:
			    msg("Enter the SCA NUMBER:");
			    ret = scanf("%s", sca_num);
			    if (ret > TAPI_SIM_SMSP_ADDRESS_LEN) {
			        msg("Entered SCA is INVALID - SCA length cannot be greater than %d", TAPI_SIM_SMSP_ADDRESS_LEN);
			        goto RETRY;
			    }
			    sca.Npi = TAPI_SIM_NPI_ISDN_TEL;
			    sca.Ton = TAPI_SIM_TON_UNKNOWN;
			    if (sca_num[0] == '+') {
			        sca.Ton = TAPI_SIM_TON_INTERNATIONAL;
			        additional_len = 1;
			    }
			    sca_length = strlen((char *)sca_num) - additional_len;
			    if (sca_length % 2 == 0) {
			        for (index = additional_len, j = 0; index < sca_length; index += 2, j++)
			            sca.szDiallingNum[j] = ((sca_num[index+1]-'0') << 4) | (sca_num[index]-'0');
			    } else {
			        for (index = additional_len, j = 0; index < sca_length; index += 2, j++) {
			            if (index == (sca_length - 1))
			                sca.szDiallingNum[j] = ((0xF0) | (sca_num[index]-'0'));
			            else
			                sca.szDiallingNum[j] = ((sca_num[index+1]-'0') << 4) | (sca_num[index]-'0');
			        }
			    }
			    sca.szDiallingNum[(sca_length+1)/2] = '\0';
			    sca.DialNumLen = strlen((char *)sca.szDiallingNum);
			    msg("%d", sca.DialNumLen);
			    returnStatus = tel_set_sms_sca (handle, &sca, 0, on_resp_set_sms_sca, NULL);
			    msg("Return status: [%d]", returnStatus);
			    break;
		}

		case 2: {
			msg("****Setting the BearerType(Api:SetPreferredBearer)****");

			msg("Enter Bearer Type(1:PD, 2:CS, 3:PDP 4:CSP):");

			memset (bearerType, 0, sizeof (bearerType));

			ret = read (0, bearerType, sizeof (bearerType));
			if (ret <= 0) {
				msg(" NULL msg can NOT be sent ");
				return -1;
			}
			msg("Set Preferred Bearer : bearerType =%d ", atoi (bearerType));

			returnStatus = tel_set_sms_preferred_bearer (handle,
					atoi (bearerType), on_resp_set_sms_preferred_bearer, NULL );
			msg("returnStatus  after prefbearer set  is %d", returnStatus);

			break;
		}

		case 3: //Set Deliver Report
		{
			msg("****Setting  Deliver Report(Api:SetDeliverReport)****");
			//EncodeSmsDeliverReportTpdu();
			break;
		}

		case 4: //Set CB Enable/Disable
		{
			msg("****Setting the CB configuration(Api:SetCbConfig)****");

			pCBConfig = calloc (1, sizeof(TelSmsCbConfig_t));
			if (!pCBConfig)
				return -1;

			msg("Enter CB ON/OFF (1: Enable, 0:Disable): ");
			pCBConfig->CBEnabled = _get_int();

			msg("Enter Max ID Count: ");
			pCBConfig->MsgIdMaxCount = _get_int();

			msg("Enter MsgIdRangeCount ( < 10 ): ");
			pCBConfig->MsgIdRangeCount = _get_int();

			if (pCBConfig->MsgIdRangeCount <= 0
					|| pCBConfig->MsgIdRangeCount >= TAPI_NETTEXT_GSM_SMS_CBMI_LIST_SIZE_MAX) {
				msg("Bad Range value");
				free (pCBConfig);
				return -1;
			}

			for (i = 0; i < pCBConfig->MsgIdRangeCount; i++) {
				msg("Enter %d FromMsgId : ", i + 1);
				pCBConfig->MsgIDs[i].Net3gpp.FromMsgId = _get_int();

				msg("Enter %d ToMsgId : ", i + 1);
				pCBConfig->MsgIDs[i].Net3gpp.ToMsgId = _get_int();

				msg("Enter %d Selected : ", i + 1);
				pCBConfig->MsgIDs[i].Net3gpp.Selected = _get_int();
			}

			pCBConfig->Net3gppType = 0x01;

			msg(
					"from sms test setting the cb configuration:CBEnabled:%d,Net3gppType:%d,msgIdRangeCount:%d,From: %d\t To: %d\t Selected: %d",
					pCBConfig->CBEnabled, pCBConfig->Net3gppType,
					pCBConfig->MsgIdRangeCount,
					pCBConfig->MsgIDs[0].Net3gpp.FromMsgId,
					pCBConfig->MsgIDs[0].Net3gpp.ToMsgId,
					pCBConfig->MsgIDs[0].Net3gpp.Selected);

			returnStatus = tel_set_sms_cb_config (handle, pCBConfig,
					on_resp_set_sms_cb_config, NULL );
			msg("returnStatus after cbconfig set is is [%d]", returnStatus);

			free (pCBConfig);

			break;
		}
		case 5: {
			char* name = "Lpg";
			char* num = "0103001408";
			char* sca = "8210911111";

			msg("****Setting Parameters(Api:SetParameters)****");

			smsParameters.RecordIndex = 0x00;
			smsParameters.RecordLen = 31;
			smsParameters.AlphaIdLen = 3;
			memcpy (&smsParameters.szAlphaId, name, strlen (name));

			smsParameters.ParamIndicator = 0xe0;
			smsParameters.TpDestAddr.DialNumLen = 10;
			smsParameters.TpDestAddr.Ton = 1;
			smsParameters.TpDestAddr.Npi = 1;

			smsParameters.TpSvcCntrAddr.DialNumLen = 10;
			smsParameters.TpSvcCntrAddr.Ton = 1;
			smsParameters.TpSvcCntrAddr.Npi = 1;

			memcpy (smsParameters.TpDestAddr.szDiallingNum, num, strlen (num));
			memcpy (smsParameters.TpSvcCntrAddr.szDiallingNum, sca,
					strlen (sca));
			smsParameters.TpProtocolId = 3;
			smsParameters.TpDataCodingScheme = 2;
			smsParameters.TpValidityPeriod = 1;

			returnStatus = tel_set_sms_parameters (handle, &smsParameters,
					on_resp_set_sms_params, NULL );
			msg("returnstatus after sparam set  is %d", returnStatus);

			break;
		}

		case 6: //Set Memory Full Notification
		{
			msg(
					"Enter Memory Status to be set(1:Memory Available, 2:Memory Full)");
			memset (MemoryStatus, 0, sizeof (MemoryStatus));
			ret = read (0, MemoryStatus, sizeof (MemoryStatus));
			if (ret <= 0) {
				msg(" NULL msg can NOT be sent ");
				return -1;
			}
			msg("Memory Status type is %d ", atoi (MemoryStatus));
			returnStatus = tel_set_sms_memory_status (handle,
					atoi (MemoryStatus), on_resp_set_mem_status, NULL ); //Set to full 0x02-Full, 0x01-available
			msg("api err after memstatus set is is %d", returnStatus);

			break;
		}
		case 7: //Set Stored MsgStaus
		{
#if 0 //JYGU
			memType=2;
			index=2;
			msgStauts =2;

			//TapiReadNetText(index, &CurMsgStauts, &DataPackage);
			returnStatus = tel_read_sms_in_sim(index,&requestId);//To avoid  mismatch of prototypes
			msg("returnStatus after read is is %d",returnStatus);

			msg("Before set status : index = %d, CurMsgStauts=%d",index,msgStauts);

			returnStatus = tel_set_sms_message_status(index, msgStauts,&requestId);
			msg("returnStatus after msgstatus set is %d",returnStatus);

			//tel_nettext_read(index, &CurMsgStauts, &DataPackage);
			returnStatus = tel_read_sms_in_sim(index,&requestId);//To avoid  mismatch of prototypes
			msg("returnStatus after read is %d",returnStatus);
#endif
			msg("Not suppored in this Test App !!!");
			break;
		}
		case 8: {
// JYGU				returnStatus =tel_set_sms_device_status();
			msg("Not suppored in this Test App !!!");
			break;
		}
		case 9: {
#if 0 //JYGU
			int status = 0;
			returnStatus =tel_check_sms_device_status(&status);
			if (status == 1)
			{
				msg("Device Ready");
			}
			else
			{
				msg("Device Not Ready");
			}
			msg("returnStatus after read is %d",returnStatus);
#endif
			msg("Not suppored in this Test App !!!");
			break;
		}
		default:
			return -1;
	}
	return 1;
}

static struct menu_data menu_sms_getting[] = { { "1",
		"Get Service Center Number", NULL, Getting, NULL }, { "2",
		"Get CB Setting Information", NULL, Getting, NULL }, { "3",
		"Get SMS Parameters", NULL, Getting, NULL }, { "4",
		"Get SMS PreferredBearer Information (Not supported)", NULL, Getting,
		NULL }, { "5", "Get SMS Parameter Count", NULL, Getting, NULL }, { "6",
		"Get Message Count", NULL, Getting, NULL }, { "7",
		"Get SMS ready status", NULL, Getting, NULL }, { NULL, NULL , }, };

static struct menu_data menu_sms_setting[] =
		{ { "1", "Set Service Center Number", NULL, Setting, NULL }, { "2",
				"Set PreferredBearer Type", NULL, Setting, NULL }, { "3",
				"Set Deliver Report", NULL, Setting, NULL }, { "4",
				"Set CB Enable/Disable", NULL, Setting, NULL }, { "5",
				"Set SMS Parameters", NULL, Setting, NULL }, { "6",
				"Set Memory Status", NULL, Setting, NULL }, { "7",
				"Set Stored MsgStaus", NULL, Setting, NULL }, { "8",
				"Set Device Ready", NULL, Setting, NULL }, { "9",
				"Check Device Status", NULL, Setting, NULL }, { NULL, NULL , }, };

static struct menu_data menu_sms_wcdma[] = { { "1", "Send Message", NULL,
		SendMessage, NULL }, { "2", "Read Message", NULL, ReadMessage, NULL }, {
		"3", "Delete Message", NULL, DeleteMessage, NULL }, { "4",
		"Delete All Message", NULL, NULL, NULL },	//DeleteAllMessage
		{ "5", "Setting", menu_sms_setting, NULL, NULL }, { "6",
				"Getting SMS Information", menu_sms_getting, NULL, NULL }, {
				NULL, NULL , }, };

static struct menu_data menu_sms_cdma[] = { { "1", "Send Message", NULL,
		SendMessageCDMA, NULL }, { NULL, NULL , }, };

struct menu_data menu_sms[] = { { "1", "WCDMA", menu_sms_wcdma, NULL, NULL }, {
		"2", "CDMA", menu_sms_cdma, NULL, NULL }, { NULL, NULL , }, };

void register_sms_event (TapiHandle *handle)
{
	int ret;

	/* SMS */
	ret = tel_register_noti_event (handle, TAPI_NOTI_SMS_INCOM_MSG,
			on_noti_sms_incom_msg, NULL );
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle, TAPI_NOTI_SMS_CB_INCOM_MSG,
			on_noti_sms_cb_incom_msg, NULL );
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle, TAPI_NOTI_SMS_ETWS_INCOM_MSG,
			on_noti_sms_etws_incom_msg, NULL );
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

//        ret = tel_register_noti_event(handle, TAPI_NOTI_SMS_INCOM_EX_MSG, on_noti_sms_incom_ex_msg, NULL);
//        ret = tel_register_noti_event(handle, TAPI_NOTI_SMS_CB_INCOM_EX_MSG, on_noti_sms_cb_incom_ex_msg, NULL);

	ret = tel_register_noti_event (handle, TAPI_NOTI_SMS_MEMORY_STATUS,
			on_noti_sms_memory_status, NULL );
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}

	ret = tel_register_noti_event (handle, TAPI_NOTI_SMS_DEVICE_READY,
			on_noti_sms_ready_status, NULL );
	if (ret != TAPI_API_SUCCESS) {
		msg("event register failed(%d)", ret);
	}
}
