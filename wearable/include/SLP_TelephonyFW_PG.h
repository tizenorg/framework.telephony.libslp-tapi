/*
 * libslp-tapi
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd. All rights reserved.
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

/**
 * @ingroup   SLP_PG
 * @defgroup   TELEPHONY Telephony
@{

<h1 class="pg">Introduction</h1>
	<h2 class="pg">Purpose</h2>
The purpose of this document is to describe how applications can use Telephony Framework APIs. This document gives programming guidelines to application engineers.

	<h2 class="pg">Scope</h2>
The scope of this document is limited to Samsung Linux platform Telephony Framework API usage.

	<h2 class="pg">Abbreviations</h2>
<table>
<tr><td>OEM</td><td>Original Equipment Manufacturer</td></tr>
<tr><td>RPC</td><td>Remote Procedure Call</td></tr>
<tr><td>SAP</td><td>Sim Access Profile</td></tr>
<tr><td>SAT</td><td>SIM Application Toolkit</td></tr>
<tr><td>SIM</td><td>Subscriber Identity Module</td></tr>
<tr><td>SVC</td><td>Service</td></tr>
<tr><td>TAPI</td><td>Telephony API</td></tr>
<tr><td>EFL</td><td>Enlightenment Foundation Libraries</td></tr>
</table>

	<h2 class="pg">Restriction Modules</h2>
CALL, SMS, GPRS, SAT have the permission. Refer to each module API description
@}
@defgroup Telephony_Architecture 1.Architecture
@ingroup TELEPHONY
@{
<h1 class="pg">Telephony Framework Architecture</h1>
@image html SLP_TelephonyFW_PG_image001.png

@image html SLP_TelephonyFW_PG_image002.png System Architecture of Telephony Framework

Telephony is a middleware component which acts as an interface layer between applications and the OEM.
@n Telephony Framework provides interfaces to applications in the form of a library and to the OEM providers in the form of OEM plug-in.
@n The applications make use of the library of exported APIs, which uses a RPC mechanism for making telephony service requests.
@n On the other side, OEM-Plug-in library is the OEM layer, which is the wireless protocol stack specific implementation. This layer acts as a plug-in giving flexibility for any wireless protocol stack to be used avoiding any changes to be made in the Telephony clients.
@n Telephony has certain synchronous and asynchronous exported APIs. Synchronous APIs provide data as the function parameter passed to Telephony. Asynchronous APIs provide data using an event based mechanism.
@image html SLP_TelephonyFW_PG_image003.png Asynchronous service request (response Use-Case Diagram)
@image html SLP_TelephonyFW_PG_image003.png Synchronous service request (response Use-Case Diagram)
@}
@defgroup Telephony_Feature 2.SubModules & Services
@ingroup TELEPHONY
@{

<h1 class="pg">Telephony Framework SubModules & Services</h1>
	<h2 class="pg">Call & Call-dependent SS</h2>
	Also see Use Cases of @ref Use_Cases2_CALL
- Initiate, accept, reject and end calls.
- Call supplementary service ( Hold,CLI, Multiparty, Call Waiting, Forwarding, Barring)
- Get Call Time, Status, Duration, Conference List
- Get and Set Active Line
- Retrieve, swap, and transfer call.
- For CDMA
	- Call Flash Information
	- Get and Set voice privacy mode

	<h2 class="pg">SMS</h2>
	Also see Use Cases of @ref Use_Cases4_SMS
SMS service in Telephony Framework only provides the interface to the modem and doesn’t handle Transport layer, storing and deleting the SMS in the storage except SIM. We recommend you use MAPI of Message Framework.
- Send, save, receive, read and delete network texts.
- Receive Cell-Broadcast Message.
- Set and Get Cell broadcast configuration.
- Set message status, memory status.
- Set and Get sms parameters

	<h2 class="pg">Supplementary Service</h2>
- Interrogation and activation for Call Barring, forwarding and waiting.
- USSD services, AOC Services.

	<h2 class="pg">Network Registration/Configuration</h2>
- Search and Select Network.
- Set and Get Selection Mode, Service Domain, network Mode and Band.
- Get Network information.
- For CDMA
	- Get and Set CDMA Hybrid Mode
	- Get and Set Roaming Mode, Preferred PLMN

	<h2 class="pg">SIM</h2>
- Handling SIM security procedure (PIN, PUK).
- Get / Update / Delete SIM EF files.
- Support 2G/3G Phonebook data.
- SIM Lock Personalisation enable or disable
- SIM lock enable or disable
- SAP

	<h2 class="pg">SAT (SIM Application Tool Kit)</h2>
- Get main menu information from the SIM application
- Send envelope commands to the SIM application
- Send the execution results of which the SIM application requests to applications
- Send UI / User confirmation to the SIM application

	<h2 class="pg">Sound</h2>
Sound that is related with voice call is used to control modem configuration
- Sound user configuration
- Voice path control
- Volume control
- Mic mute control

	<h2 class="pg">Common</h2>

- TAPI initialization & De-initialization
- Register, Deregister event
- TAPI Initialization & De-initialization for Ecore
- Register, Deregister Ecore event
- Request Connection name

@}

<h1 class="pg">Feature Description</h1>
<h2 class="pg">COMMON</h2>

@defgroup Use_Cases1_1 TAPI Initialization
@ingroup Use_Cases1_COMMON
@{
<h3 class="pg">TAPI Initialization</h3>
This API shall be used to initialize the TAPI library. This API internally performs initialization routines related to Event delivery.
@n This API should be called before any other TAPI APIs. This API should be used by GTK/Glib applications.

@code
int tel_init (void);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void tapiinit()
{
	int api_err;

	api_err = tel_init();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf ("tel_init Failed - api_err = %d\n", api_err);
	}
}
@endcode
@}
@defgroup Use_Cases1_2 TAPI De-initialization
@ingroup Use_Cases1_COMMON
@{
		<h3 class="pg">TAPI De-initialization</h3>
This API shall be used to de initialize the Tapi library.
@n It shall perform the deinitializing routines related to event delivery.
@n The API shall be called finally, as a part of clean up routines. This API should be used by GTK/Glib applications.

@code
int tel_deinit (void);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void tapideinit()
{
	int api_err;

	api_err = tel_deinit();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf ("tel_deinit Failed - api_err = %d\n", api_err);
	}
}
@endcode
@}
@defgroup Use_Cases1_3 Register Event
@ingroup Use_Cases1_COMMON
@{

		<h3 class="pg">Register Event</h3>
API is used to register the callback function for a specific TAPI Event. Upon successful registration of the event, the function shall return a valid subscription id.

If Application registers multiple callbacks for a specific event, then all the callbacks will be called when an event indication is received.
@n This API should be used by GTK/Glib applications.

@code
int tel_register_event (int EventType , unsigned int * SubscriptionId, TelAppCallback AppCallBack);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void app_callback(TelTapiEvent_t *event);

// REGISTER EVENT
void registerevent()
{
	unsigned int subscription_id = 0;
	int api_err;

	api_err = tel_init();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf ("tel_init Failed - api_err = %d\n", api_err);
	}

	api_err = tel_register_event (TAPI_EVENT_CALL_SETUP_CNF, &subscription_id, (TelAppCallback)&app_callback);

	printf("MISC Event registeration is Done: sub id is %d, api_err is %d\n", subscription_id, api_err);

	tel_register_app_name("com.samsung.appname");
}

void app_callback(TelTapiEvent_t *event)
{
	//Callback function to be called
}
@endcode
@}

@defgroup Use_Cases1_4 Deregister Event
@ingroup Use_Cases1_COMMON
@{

		<h3 class="pg">Deregister Event</h3>
API shall de-register the pre-registered TAPI event and the associated application callback, based on the subscription id.
@n This identifier is the same as the subscription identifier returned to the application during the TAPI registration procedure. If the de-register API is called during any service requests, the registered callback will be cleared based on the subscription id. No application callback shall be called when any confirmation/indication events are received after de-registration.
@n This API should be used by GTK/Glib applications.

@code
int tel_deregister_event ( unsigned int  SubscriptionId);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void app_callback(TelTapiEvent_t *event);

void registerevent()
{
	unsigned int subscription_id = 0;
	int api_err;

	api_err = tel_init();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf ("tel_deregister_event Failed - api_err = %d\n", api_err);
	}

	// REGISTER EVENT
	api_err = tel_register_event (TAPI_EVENT_CALL_SETUP_CNF, &subscription_id, (TelAppCallback)&app_callback);
	printf("MISC Event registeration is Done: sub id is %d, api_err is %d\n",subscription_id,api_err);

	tel_register_app_name("com.samsung.appname");

	// DEREGISTER EVENT
	api_err = tel_deregister_event (subscription_id);
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("Event Deregistration Failed\n");
	}
}

void app_callback(TelTapiEvent_t *event)
{
	// callback function to be called
}
@endcode
@}


@defgroup Use_Cases1_5 TAPI Ecore Initialization
@ingroup Use_Cases1_COMMON
@{

	<h3 class="pg">TAPI Ecore Initialization</h3>
This API shall be used by Ecore based applications, to initialize TAPI library. This API internally performs event delivery related initialization routines. This API shall be called before any other TAPI APIs.
@n This API is for applications using Ecore library.

@code
int tel_init_ecore_loop (void);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void tapiinitecore()
{
	int api_err;

	api_err = tel_init_ecore_loop();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("tel_init_ecore_loop Failed - api_err = %d\n", api_err);
	}
}
@endcode

5		<h3 class="pg">TAPI Ecore De-Initialization</h3>
API shall be used to de-initialize the TAPI library. It shall be used by Ecore based applications.
@n This API shall be called finally, as a part of cleanup routine. This API is for applications using Ecore library.

@code
int tel_deinit_ecore_loop (void);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void tapideinitecore()
{
	int api_err;

	api_err = tel_deinit_ecore_loop();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("tel_deinit_ecore_loop Failed - api_err = %d\n", api_err);
	}
}
@endcode
@}

@defgroup Use_Cases1_6 TAPI RegisterEvent Ecore
@ingroup Use_Cases1_COMMON
@{

		<h3 class="pg">TAPI RegisterEvent Ecore</h3>
API shall be used to register for TAPI events (for application that use EFL).
@n Upon successful registration of the event, the API shall return a valid subscription id.
@n If Application registers multiple callbacks for a specific event, then all the callbacks will be called when an event indication is received
@n This API is for applications using Ecore library.

@code
int tel_register_event_at_ecore_loop(int EventType, unsigned int * SubscriptionId, TelAppCallback AppCallBack);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

void app_callback(TelTapiEvent_t *event);

void registereventecore()
{
	int api_err;
	unsigned int subscription_id = 0;

	api_err = tel_register_event_at_ecore_loop (TAPI_EVENT_CALL_SETUP_CNF, &subscription_id, (TellAppCallback)&app_callback);
	if (api_err != TAPI_API_SUCCESS)
	{
		printf ("tel_register_event_at_ecore_loop Failed - api_err = %d \n", api_err);
	}
	printf("RegisterEventEcore done with subscription_id:%d and return Status:%d\n", subscription_id, api_err);

	tel_register_app_name("com.samsung.appname");
}

void app_callback(TelTapiEvent_t *event)
{
	//Callback function to be called
}
@endcode
@}


@defgroup Use_Cases1_7 TAPI DeRegisterEvent Ecore
@ingroup Use_Cases1_COMMON
@{

	<h3 class="pg">TAPI DeRegisterEvent Ecore</h3>
API shall de-register the pre-registered TAPI event and the associated application callback, based on the subscription id.
@n This identifier is the same as the subscription identifier returned to the application during the TAPI registration procedure.
@n If the de-register API is called during any service requests, the registered callback will be cleared based on the subscription id. No application callback shall be called when any confirmation/indication events are received after de-registration.
@n This API is for applications based on Ecore library.

@code
int tel_deregister_event_at_ecore_loop (unsigned int SubscriptionId);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

Void deregistereventecore()
{
	int api_err;
	unsigned int subscription_id = 0;

	// REGISTER EVENT
	api_err = tel_register_event_at_ecore_loop (TAPI_EVENT_CALL_SETUP_CNF, &subscription_id, (TellAppCallback)&app_callback);
	printf("RegisterEventEcore done with subscription_id:%d and return Status:%d\n", subscription_id, api_err);

	tel_register_app_name("com.samsung.appname");

	// DEREGISTER EVENT
	api_err = tel_deregister_event_at_ecore_loop (subscription_id);
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("tel_deregister_event_at_ecore_loop Failed - api_err = %d\n", api_err);
	}
}
@endcode
@}

@defgroup Use_Cases1_8 Register Application Name
@ingroup Use_Cases1_COMMON
@{

		<h3 class="pg">Register Application Name</h3>
This function registers the application name which requests any telephony service. Telephony Server uses this name as the destination name of response message upon the service request. If the name is not set, the request will fails. Before an application invoke this function, it shall initialize a connection to Telephony Sever with #tel_init or #tel_init_ecore_loop. And the application name shall be registered prior to start a event loop.

@code
int tel_register_app_name(char *name)
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>

Void register_app_name()
{
	tel_init();
	//register telephony event
	tel_register_event(...);
	//...
	tel_register_app_name("com.samsung.appname");
	GMainLoop *loop = g_main_loop_new(NULL, false);
	g_main_loop_run(loop);
}
@endcode
@}

@defgroup Use_Cases1_9 Get Application Name
@ingroup Use_Cases1_COMMON
@{

		<h3 class="pg">Get Application Name</h3>
This function get the application name which was registered with #tel_register_application_name.

@code
int tel_get_app_name(tapi_dbus_connection_name *app_name)
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <TapiCommon.h>

void get_app_name()
{
	tapi_dbus_connection_name app_name;
	tel_get_app_name(&app_name);
	// printf("app_name = %s\n", app_name.name);
}
@endcode
@}
@defgroup Use_Cases1_10 TAPI Check service ready
@ingroup Use_Cases1_COMMON
@{

	<h3 class="pg">TAPI Check service ready </h3>
API is used to get the modem status i.e. whether modem is on or off.

@code
int tel_check_service_ready (int* bStatus)
@endcode

SAMPLE CODE:
@code
#include <stdio.h>
#include <TapiCommon.h>

void getmodemstatus()
{
	int bStatus = 0;
	int err_code;

	err_code = tel_check_service_ready(&bStatus);
	if (err_code != TAPI_API_SUCCESS) {
		printf("Error Code [%x]\n", err_code);
	}
	else {
		if (bStatus == 0)
			printf("Telephony Service Not Ready";
		else if (bStatus == 1)
			printf("Telephony Service Ready";
	}
}
@endcode
@}


<h2 class="pg">CALL</h2>

@defgroup Use_Cases2_1 Event Register and Deregister
@ingroup Use_Cases2_CALL
@{

	<h3 class="pg">Event Register and Deregister</h3>
To receive asynchronous event notifications for the call APIs, the registration of related events with their associated call backs is required. After these are registered, when an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

SAMPLE CODE:
@code
// REGISTER EVENT
int api_err;
unsigned int subscription_id = 0;

api_err = tel_init();
if (api_err != TAPI_API_SUCCESS)
{
	printf("tel_init Failed - api_err = %d \n", api_err);
}

api_err = tel_register_event (TAPI_EVENT_CALL_CALL_SETUP_CNF, &subscription_id, (TelAppCallback)&app_callback);
printf("VOICE CALL Event registration is Done: sub id is %d, api_err is %d\n",subscription_id,api_err);

tel_register_app_name("com.samsung.appname");

// DEREGISTER EVENT
api_err = tel_deregister_event (subscription_id);
if (api_err != TAPI_API_SUCCESS)
{
	printf("Event Class Unregistration Fail\n");
}
@endcode
@}

@defgroup Use_Cases2_2 Call Setup
@ingroup Use_Cases2_CALL
@{

<h3 class="pg">Call Setup</h3>
This API originates an MO call setup.

@code
int tel_dial_call(TapiHandle *handle, const TelCallDial_t *pParams, tapi_response_cb callback, void *user_data);
@endcode

On success, this API returns a valid call handle and the request ID as out parameters.
@n The MO call setup procedure continues in background. There are multiple states involved in the call setup procedure. Upon completion of the setup request, the event notifications and associated event data are sent to the client, based on the indication or response received by the Telephony Server.

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callsetup()
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	TelCallDial_t data;
	int result;
	int len;

	memset(&data, 0, sizeof(TelCallDial_t));

	data.CallType = atoi(data_call_type);
	len = strlen(data_call_number);
	if (len > TAPI_CALL_DIALDIGIT_LEN_MAX) {
		msg("number too long");
		return 0;
	}

	memcpy(data.szNumber, data_call_number, len);

	msg("call tel_dail_call()");

	result = tel_dial_call(handle, &data, on_dial_call, 0);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return 0;
}

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int status;
	void* EventData = NULL;

	unsigned int temp_handle = 0;

	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}

	switch (eventType)
	{
		case TAPI_EVENT_CALL_SETUP_CNF:
			printf("TAPI_EVENT_CALL_SETUP_CNF");
			memcpy(&temp_handle, EventData, sizeof(unsigned int));
			TEST_DEBUG("Received setup cnf for call Handle [%d]", temp_handle);

			break;

		case TAPI_EVENT_CALL_ALERT_IND:
			int index;
			TEST_DEBUG("TAPI_EVENT_CALL_ALERT_IND");
			memcpy(&temp_handle, event->pData, sizeof(unsigned int));
			TEST_DEBUG("Received Alert for call Handle [%d]", temp_handle);
			break;

		case TAPI_EVENT_CALL_CONNECTED_IND:
			int index;
			TEST_DEBUG("TAPI_EVENT_CALL_CONNECTED_IND");
			memcpy(&temp_handle, event->pData, sizeof(TS_UINT));
			TEST_DEBUG("Received Connected Event  for call Handle [%d]", temp_handle);
			break;
	}
	//...
}
@endcode
@}
@defgroup Use_Cases2_3 Call Answer
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Answer</h3>
This API responds to an incoming call either by accepting or rejecting the call.

Pre Conditions:
@n Call associated with the call handle should be in TAPI_CALL_STATE_INCOM state.
@n There should be no more than one existing call.

@code
int tel_answer_call(TapiHandle *handle, unsigned int CallHandle, TelCallAnswerType_t AnsType, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"
//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

void callsetup(unsigned int CallHandle)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;
	TelCallAnswerType_t answer_type;


	msg("call tel_answer_call()");

	call_id = atoi(data_call_id);
	answer_type = atoi(data_answer_type);

	result = tel_answer_call(handle, call_id, answer_type, on_answer_call, 0);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return 0;
}

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		//GET CALL HANDLE FROM INCOMING CALL EVENT DATA
		case TAPI_EVENT_CALL_INCOM_IND:
			unsigned int CallHandle;
			TelCallIncomingCallInfo_t IncomingInfo;
			memcpy(&IncomingInfo, event->pData, sizeof(TelCallIncomingCallInfo_t));
			CallHandle = IncomingInfo.CallHandle;
			break;

		case TAPI_EVENT_CALL_ANSWER_CNF:
			memcpy(&CallHandle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_ANSWER_CNF\n");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_4 Call Release
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Release</h3>
This API is used to release the call.
@n The call to be released can be a single call based on the call handle, or all active calls or all calls.

Pre Conditions:
@n Call handle should be valid and there should be an existing call in Active/hold state.

@code
<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

void callrelease(unsigned int CallHandle)
{
	TapiHandle *handle = menu_manager_ref_user_data(mm);
	int result;
	unsigned int call_id;
	TelCallEndType_t end_type;

	msg("call tel_end_call()");

	call_id = atoi(data_call_id);
	end_type = atoi(data_end_type);

	result = tel_end_call(handle, call_id, end_type, on_end_call, 0);
	if (result != TAPI_API_SUCCESS) {
		msg("failed. (result = %d)", result);
	}

	return 0;
} //WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TelTapiEvent_t *event)
{
	//...
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		//GET CALL HANDLE FROM INCOMING CALL EVENT DATA
		case TAPI_EVENT_CALL_INCOM_IND:
			TelCallIncomingCallInfo_t IncomingInfo;
			memcpy(&IncomingInfo, event->pData, sizeof(TelCallIncomingCallInfo_t));
			CallHandle = IncomingInfo.CallHandle;
			break;

		case TAPI_EVENT_CALL_RELEASE_CNF:
		case TAPI_EVENT_CALL_RELEASE_ALL_CNF:
		case TAPI_EVENT_CALL_RELEASE_ALL_ACTIVE_CNF:
		case TAPI_EVENT_CALL_RELEASE_ALL_HELD_CNF:
		case TAPI_EVENT_CALL_END_IND_IND:
			unsigned int handle;
			memcpy(&handle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_RELEASE_CNF\n");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases2_5 Call Hold
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Hold</h3>
This API puts the specified call on hold. The call identified by Call Handle should be in the active state.

@code
 int tel_hold_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callhold(unsigned int CallHandle)
{
	unsigned int call_handle = VC_TAPI_CALLHANDLE;
	TapiResult_t tapi_err = TAPI_API_SUCCESS;
	// Hold the call
	//Puts the given call on hold
	tapi_err = tel_hold_call(tapi_handle, call_handle, _vc_core_engine_hold_call_resp_cb, NULL);
	if (TAPI_API_SUCCESS != tapi_err) {
		CALL_ENG_DEBUG(ENG_DEBUG, "tel_hold_call() Failed Error Code: %d", tapi_err);
		return FALSE;
	}

	return;
} //WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_HOLD_CNF:
			unsigned int CallHandle;
			memcpy(&CallHandle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_HOLD_CNF\n");
			break;
		//...
	}
	//...
}
@endcode
@}
@defgroup Use_Cases2_6  Call Retrieve
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Retrieve</h3>
This API can be used to retrieve a held call.

Pre Conditions:
@n Call should be in held state in order to return to the active state, and no other call should be active.

@code
int tel_active_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"


//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callretrieve(unsigned int CallHandle)
{
	unsigned int call_handle = VC_TAPI_CALLHANDLE;
	TapiResult_t tapi_err = TAPI_API_SUCCESS;

	tapi_err = tel_active_call(tapi_handle, call_handle, _vc_core_engine_active_call_resp_cb, NULL);
	if (TAPI_API_SUCCESS != tapi_err) {
		CALL_ENG_DEBUG(ENG_DEBUG, "tel_active_call() Failed Error Code: %d", tapi_err);
		return FALSE;
	}
} //WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_HOLD_CNF:
			unsigned int CallHandle;
			memcpy(&CallHandle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_HOLD_CNF\n");
			break;

		case TAPI_EVENT_CALL_RETRIEVE_CNF:
			unsigned int CallHandle;
			memcpy(&CallHandle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_RETRIEVE_CNF ");
			break;
	}
	//...
}
//...
@endcode
@}
@defgroup Use_Cases2_7  Call Swap
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Swap</h3>
This API can be used to swap calls. This feature is only available for the calls that have been setup and answered using the Telephony service. The swap functionality is only available for voice calls.

Pre Conditions:
@n Two calls should be present, one of them in the Active state and the other in the held state

@code
int tel_swap_call(TapiHandle *handle, unsigned int CallHandle1, unsigned int CallHandle2, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"
//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

void callswap(unsigned int CallHandle1, unsigned int CallHandle2)
{
	int ret_status ;
	TapiHandle *handle;
	unsigned int CallHandle1;
	unsigned int CallHandle2;
	tapi_response_cb callback;
	void *user_data;
	ret_status = tel_swap_call(handle, CallHandle1, CallHandle2, callback, user_data);
	if (TAPI_API_SUCCESS != tapi_err) {
		CALL_ENG_DEBUG(ENG_DEBUG, "tel_swap_call() Failed, Error Code: %d", tapi_err);
		return FALSE;
	}

	return TRUE;
} //WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_SWAP_CNF:
			printf("TAPI_EVENT_CALL_RETRIEVE_CNF\n");
			break;
	}
	//..
}
//..
@endcode
@}
@defgroup Use_Cases2_8 Send DTMF
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Send DTMF</h3>
This API can be used for sending one or more DTMF digits during the call.

Pre Conditions:
@n Active call should be present.

@code
 int tel_call_dtmf(TapiHandle *handle, const char *pDtmfString, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void senddtmf()
{
	int ret_status ;
	TapiHandle *handle;
	unsigned int pCallHandle;
	void *user_data;
	char DtmfString[10] = {0, };
	strcpy(DtmfString, "123456789");//Sample DTMF digits that need to be sent
	ret_status= tel_call_dtmf(handle, DtmfString, callback, user_data);

	if (TAPI_API_SUCCESS != tapi_err) {
		CALL_ENG_DEBUG(ENG_DEBUG, "tapi_call_dtmf Failed, Error Code: %d", tapi_err);
		return FALSE;
	}

	CALL_ENG_DEBUG(ENG_DEBUG, " Ended...");

	return TRUE;
}
//WAIT FOR EVENT HERE
static void app_callback(TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_SEND_DTMF_CNF:
			printf("TAPI_EVENT_CALL_SEND_DTMF_CNF\n");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_9 Call Join
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Join</h3>
This API joins the specified two calls (one call which is in the active state and other call which is in the held state) into a conference call.

Pre Conditions:
@n For a Multiparty call or for joining two calls into conference, there should be one call in active state and another call in held state.

@code
 int tel_join_call(TapiHandle *handle, unsigned int CallHandle1, unsigned int CallHandle2, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void calljoin(unsigned int CallHandle1, unsigned int CallHandle2)
{
	int ret_status ;
	TapiHandle *handle
	unsigned int CallHandle1;
	unsigned int CallHandle2;
	tapi_response_cb callback;
	void *user_data;
	ret_status= tel_join_call(handle, CallHandle1, CallHandle2, callback, user_data); ;
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
} //WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_SETUPCONFERENCE_CNF:
			unsigned int temp_handle;
			memcpy(&temp_handle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_SETUPCONFERENCE_CNF ");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_10 Call Split
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call Split</h3>
This API triggers the split of a single call from multiparty call. This can be used for creating a private communication with one of remote parties in a multiparty session.
@n TAPI client application has to pass the call handle which should be split from the multiparty call.

Pre Conditions:
@n Call should be in multiparty conference call.

Post Conditions:
@n Split call will be the active call and the conference will be held call.

@code
 int tel_split_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callsplit(unsigned int CallHandle)
{
	 int ret_status ;
	TapiHandle *handle;
	unsigned int CallHandle;
	tapi_response_cb callback;
	void *user_data;
	ret_status= tel_split_call(handle, CallHandle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI TAPI_EVENT_CALL_SPLITCONFERENCE_CNF:
			unsigned int temp_handle;
			memcpy(&temp_handle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_SPLITCONFERENCE_CNF ");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_11 Active Line
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Active Line </h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n Telephony provides APIs for setting and getting the current calling line identification number.

@code
int tel_set_call_act_line(TapiHandle *handle, TelCallActiveLine_t active_line, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SET ACTIVE LINE
void activeline()
{
	int ret_status ;
 	TapiHandle *handle;
 	TelCallActiveLine_t active_line ;
	tapi_response_cb callback,;
	void *user_data;

	ret_status = tel_set_call_act_line (handle, active_line, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);

	//GET ACTIVE LINE
	ret_status = tel_get_call_act_line(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//..
}

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_SET_LINEID_CNF:
			//TEST_DEBUG("Received TAPI_EVENT_CALL_SET_LINEID_CNF");
			//AUTO_LOG("EVENT: SET_LINEID_CNF:");
			break;

		case TAPI_EVENT_CALL_GET_LINEID_CNF:
			TelCallActiveLine_t active_line;
			memcpy(&active_line, event->pData, sizeof(TelCallActiveLine_t));
			TEST_DEBUG("Received TAPI_EVENT_CALL_GET_LINEID_CNF");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_12  Call transfer
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call transfer</h3>
This API triggers an explicit call transfer by connecting two parties, one of which is in the active state with the other in the held state.

Pre Conditions:
@n In order to call transfer, 2 calls should be present. One in the active state and the other in the Held state.

Post Conditions:
@n When the request has been completed successfully, Call end indication will be sent to both the calls (active and held).

@code
int tel_transfer_call(TapiHandle *handle, unsigned int CallHandle, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE:
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void calltransfer(unsigned int CallHandle)
{
	int ret_status ;
	TapiHandle *handle;
	unsigned int pCallHandle;//active call
	tapi_response_cb callback;
	void *user_data;
	ret_status= tel_transfer_call (handle, pCallHandle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	//..
	switch (eventType) //REFER Call Setup TO GET eventType
	{
		case TAPI_EVENT_CALL_TRANSFER_CNF:
			unsigned int temp_handle = 0;
			memcpy(&temp_handle, event->pData, sizeof(unsigned int));
			printf("TAPI_EVENT_CALL_TRANSFER_CNF. ");
			break;
	}
	//..
}
@endcode
@}
@defgroup Use_Cases2_13 Get Call Status
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Get Call Status</h3>
When call status is requested by the application, this API gets the status of the call associated with the input Call Handle. Call status information consists of destination number, call direction (MO or MT), call type (voice or data etc), multiparty state (whether the call is in conference state or not) and present call state.
@n Call handle must be valid.

@code
int tel_get_call_status(TapiHandle *handle, int call_id, TelCallStatus_t *out );
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

void getcallstatus(unsigned int CallHandle)
{
	int ret_status ;
	int call_id;
	TapiHandle *handle;
	TelCallStatus_t *out;
	 ret_status= tel_get_call_status(handle, call_id, out);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
		printf("CallNumber: %s\n", callStatus.pNumber);
		printf("Is Mobile Originated:%d n\t CallType : %d \n\t CallActiveState: %d\n\t CallState : %d\n\t isConferenceState:%d \n",
				callStatus.bMoCall,
				callStatus.CallType,
				callStatus.CallActiveState,
				callStatus.CallState,
				callStatus.bConferenceState);
	}
	else {
		printf("error=%d\n", ret_status);
	}
}
@endcode
@}
@defgroup Use_Cases2_14  Get Call Duration
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Get Call Duration</h3>
This API gets the duration of the specified call.
@n This is a synchronous API. Duration is timed from the moment the connection is established, i.e. call goes into active state for first time. The total call duration is provided in seconds, from the call connecting time to the current time.

@code
 int tel_get_call_duration(TapiHandle *handle, unsigned int CallHandle, unsigned int * pDurationInSecs) ;
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

void getcallduration(unsigned int CallHandle)
{
	int ret_status ;
	TapiHandle *handle
	unsigned int CallHandle;
	unsigned int * pDurationInSecs;
	ret_status= tel_get_call_duration(handle, CallHandle, pDurationInSecs);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
		printf("Call Duration : %d Seconds\n", duration);
	}
	else {
		printf("error=%d\n", ret_status);
	}
}
@endcode
@}
@defgroup Use_Cases2_15 Get Call Conference List
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Get Call Conference List</h3>
This is a synchronous API which returns information about all the call handles and the total number of call handles, within the specified conference call.

Pre Conditions:
@n Call should be a multi-party conference call in order to return actual number of calls and call handles in the conference call.

@code
int tel_get_call_conf_list(TapiHandle *handle, unsigned int CallHandle, unsigned int *pCallList, int *pNoOfCalls);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

void getconferencelist(unsigned int CallHandle)
{
	int ret_status ;
	TapiHandle *handle;
	unsigned int CallHandle;
	unsigned int callList[5];
	tapi_response_cb callback;
	int noOfCalls;
	void *user_data;
	 ret_status= tel_get_call_conf_list(handle, CallHandle, callList, &noOfCalls, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
		printf("\n No.of Calls %d, \n", noOfCalls);
		for (i = 0; i < noOfCalls; i++)
		{
			printf("\n Call Handle in conference calls %d \n", callList[i]);
		}
	}
	else {
		printf("error=%d\n", ret_status);
	}
}
@endcode
@}
@defgroup Use_Cases2_16 Voice Privacy Mode
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Voice Privacy Mode</h3>
Telephony provides two APIs which can be used to set and get the CDMA voice privacy mode .

@code
int tel_get_call_privacy_mode(TapiHandle *handle, TelCallPrivacyType_t PrivacyType, tapi_response_cb callback, void *user_data);
int tel_set_call_privacy_mode(TapiHandle *handle, TelCallVoicePrivacyInfo_t PrivacyInfo, tapi_response_cb callback, void *user_data);
@endcode

This API is restricted for direct use.  Use the Voice call engine API instead.

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

//SetVoicePrivacyMode
void setvoiceprivacymode()
{
	TapiHandle *handle;
	int ret_status = -1;
	tapi_response_cb callback;
	void *user_data;
	TelCallPrivacyMode_t pPrivacyMode_info={0,};
 	pPrivacyMode_info = TAPI_CALL_PRIVACY_MODE_STANDARD;
	ret_status = tel_set_call_privacy_mode (handle, pPrivacyMode_info, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("Successful\n");
	else
		printf("error:%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED

bool call_app_callback (TelTapiEvent_t *Event)
{
	int ret = -1;
	int eventClass = Event->EventClass;
	int eventType = Event->EventType;
	int RequestId = Event->RequestId;
	int Status = Event->Status;

	if (eventClass == TAPI_EVENT_CLASS_CALL_VOICE)
	{
		switch (eventType) {
			case TAPI_EVENT_CALL_SET_PRIVACYMODE_CNF:
				if (RequestId != reqId) {
					printf("Invalid RequestID received %d \n", reqId);
					return false;
				}

				if (Status != TAPI_CAUSE_SUCCESS) {
					printf("Invalid Status value received");
					return false;
				}
				break;
		}
	}
}

//GetVoicePrivacyMode
void getprivacymode()
{
	 TapiHandle *handle;
 	int ret_status = -1;
	tapi_response_cb callback;
	void *user_data;
	TelCallPrivacyMode_t pPrivacyMode_info={0,};
	pPrivacyMode_info = TAPI_CALL_PRIVACY_MODE_STANDARD;
	 ret_status = tel_set_call_privacy_mode (handle, pPrivacyMode_info, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("Successful\n");
	else
		printf("error:%d\n", ret_status);
}

//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED

bool call_app_callback (TelTapiEvent_t *Event)
{
	int ret = -1;
	int eventClass = Event->EventClass;
	int eventType = Event->EventType;
	int RequestId = Event->RequestId;
	int Status = Event->Status;

	if (eventClass == TAPI_EVENT_CLASS_CALL_VOICE)
	{
		switch (eventType) {
			case TAPI_EVENT_CALL_GET_PRIVACYMODE_CNF:
				TelCallVoicePrivacyInfo_t vp_info;
				memcpy(&vp_info, event->pData, sizeof(TelCallVoicePrivacyInfo_t));
				if (Status != TAPI_CAUSE_SUCCESS)
				{
					printf("Invalid Status value received");
					return false;
				}
				break;
		}
	}
}
@endcode
@}
@defgroup Use_Cases2_17 Call FlashInformation
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Call FlashInformation</h3>
The user makes an additional outgoing call in CDMA, this API is used instead of the CALL Outgoing API because there is no additional voice call transaction in CDMA. So the voice call id is only one in CDMA. The multiparty call is not supported in CDMA.

@code
int tel_exe_call_flash_info(TapiHandle *handle, const char *pDialNumber, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
//CallFlashInfo
void callflashinfo()
{
	int ret_status = -1;
	int api_err;
	tapi_response_cb callback;
	void *user_data;
	const char *pDialNumber = "9999900000";

	ret_status = tel_exe_call_flash_info(handle, pDialNumber, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("Successful\n");
	else
		printf("error:%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
bool call_app_callback(TelTapiEvent_t *Event)
{
	int ret = -1;
	int eventClass = Event->EventClass;
	int eventType = Event->EventType;
	int RequestId = Event->RequestId;
	int Status = Event->Status;

	if (eventClass == TAPI_EVENT_CLASS_CALL_VOICE)
	{
		switch (eventType)
		{
			case TAPI_EVENT_CALL_FLASHINFO_CNF:
				if (RequestId != reqId)
				{
					printf("Invalid RequestID received %d \n", reqId);
					return false;
				}

				if (Status != TAPI_CAUSE_SUCCESS)
				{
					printf("Invalid Status value received");
					return false;
				}
				printf("\n Received TAPI_EVENT_CALL_FLASHINFO_CNF \n");
				break;

		}
	}
	return true;
}
@endcode
@}
@defgroup Use_Cases2_18 Getting Call Time
@ingroup Use_Cases2_CALL
@{

		<h3 class="pg">Getting Call Time</h3>
This API is used to query information about a call time and call count.

@code
int tel_get_call_time(TapiHandle *handle, unsigned short req_mask, tapi_response_cb callback, void *user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Voice call engine API instead.</strong>

SAMPLE CODE
@code
#include <ITapiCall.h>
#include <stdio.h>
#include "TapiCommon.h"

void getcalltime()
{
	  int ret_status = -1;
	 TapiHandle *handle;
	 tapi_response_cb callback;
	 void *user_data;
	 TelCallTimeMaskType_t mask_byte1 = {0,};
	 TelCallTimeMaskType_t mask_byte2 = {0,};
	 unsigned short mask_type;
	 mask_byte1 = TAPI_CALL_TIME_TYPE_TOTAL_CALL_CNT; //masking call type
	 mask_byte2 = TAPI_CALL_TIME_TYPE_TOTAL_CALL_TIME;
	 mask_type = mask_byte1;
	 mask_type << 8;
	 mask_type = mask_byte2;

	 ret_status = tel_get_call_time(handle, mask_type, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("Successful\n");
	else
		printf("error:%d\n", ret_status);
}
//WAIT FOR EVENT HERE

bool call_app_callback(TelTapiEvent_t *Event)
{
	int ret = -1;
	int eventClass = Event->EventClass;
	int eventType = Event->EventType;
	int RequestId = Event->RequestId;
	int Status = Event->Status;

	if (eventClass == TAPI_EVENT_CLASS_CALL_VOICE)
	{
		switch (eventType)
		{
			case TAPI_EVENT_CALL_SET_PRIVACYMODE_CNF:
				if (RequestId != reqId)
				{
					printf("Invalid RequestID received %d \n", reqId);
					return false;
				}

				if (Status != TAPI_CAUSE_SUCCESS)
				{
					printf("Invalid Status value received");
					return false;
				}
				break;
		}
	}
}
@endcode
@}

<h2 class="pg">SUPPLEMENTARY SERVICE </h2>
@defgroup Use_Cases3_1 Event register and deregister
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{
		<h3 class="pg">Event register and deregister</h3>
To receive asynchronous event notifications for the SS APIs, the registration of related events with their associated call backs is required. After these are registered, when an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

SAMPLE CODE
@code
// REGISTER EVENT
Tapi_handle *handle;
char *noti_id = TAPI_NOTI_SS_FORWARD_STATUS; // We need to register for all events, like barring, waiting etc.
tapi_response_cb callback;
void *user_data;
int ret;

handle = tel_init();
if (!handle)
{
	TEST_DEBUG("tel_init Failed");
}

ret = tel_register_noti_event(handle,noti_id,callback,userdata);
if(ret != TAPI_API_SUCCESS)
{
	TEST_DEBUG("SS Event registration failed");
}
else
{
	printf("SS Event registration is Done");
}

tel_register_app_name("com.samsung.appname");

// DEREGISTER EVENT
ret = tel_deregister_event(handle,noti_id);
if (ret != TAPI_API_SUCCESS)
{
	printf("Event Unregisteration Fail\n");
}
@endcode
@}
@defgroup Use_Cases3_2 Call Barring
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{

		<h3 class="pg">Call Barring </h3>
Telephony provides APIs to activate/deactivate call barring, get the barring status and change the barring password. It also provides APIs for applications to provide barring password requested by network for Call Barring Request or Change barring password request.
@n This service makes it possible for a mobile subscriber to activate barring for certain categories of outgoing or incoming calls. It also allows the deactivation of call barring based on categories set.
@n The mobile subscriber may also determine the type of barring preferrred for incoming/outgoing calls, by subscribing to a set of one or more unique barring programs .

@code
int   tel_set_ss_barring(TapiHandle *handle, TelSsBarringInfo_t *info, tapi_response_cb callback, void *user_data);
int   tel_get_ss_barring_status(TapiHandle *handle, TelSsClass_t class, TelSsBarringType_t type, tapi_response_cb callback, void *user_data);
int   tel_change_ss_barring_password(TapiHandle *handle,const char *old_password,const char *new_password,const char *new_password_again,tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE FOR SET CALL BARRING
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callbarring()
{
	int ret_status = -1;
	TelSsCallBarringInfo_t BarringInfo;
	char *bar_pwd = "0000";
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	BarringInfo.Mode = TAPI_SS_CALL_BAR_ACTIVATE;
	BarringInfo.Type = TAPI_CALL_BARRING_ALL_OUTGOING_CALLS;
	BarringInfo.CallType = TAPI_CALL_TYPE_VOICE_EV;
	strcpy(BarringInfo.szPassword, bar_pwd);

	ret_status = tel_set_ss_barring (handle,&BarringInfo,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS) {
		printf("successful\n");
	}
	else {
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

static void app_callback (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsBarringResp_t *resp = data;
	int i = 0;

	msg("");
	msgb("tel_set_ss_barring() or tel_get_ss_barring_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d, Flavour=%d",
				i,
				resp->record[i].Class,
				resp->record[i].Status,
				resp->record[i].Flavour);
	}
}
@endcode

SAMPLE CODE FOR GET BARRING STATUS
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

void callbarringstatus()
{
	//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
	int ret_status;
	TelSsCallBarType_t BarType = TAPI_CALL_BARRING_ALL_OUTGOING_INTERN_CALL;
	TelSsCallType_t CallType = TAPI_CALL_TYPE_VOICE_EV;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_ss_barring_status (handle,BarType, CallType,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

static void app_callback (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsBarringResp_t *resp = data;
	int i = 0;

	msg("");
	msgb("tel_set_ss_barring() or tel_get_ss_barring_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d, Flavour=%d",
				i,
				resp->record[i].Class,
				resp->record[i].Status,
				resp->record[i].Flavour);
	}
}
@endcode

SAMPLE CODE FOR CHANGING BARRING PASSWORD
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void changebarpwd()
{
	int ret_status;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_change_ss_barring_password ("0000", "0000", "0000", user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}

//WAIT FOR THE EVENT  HERE

static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	msg("");
	msgb("tel_change_ss_barring_password() response receive");
	msg(" - result = 0x%x", result);
}
@endcode
@}
@defgroup Use_Cases3_3 Call Forward
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{


		<h3 class="pg">Call Forward</h3>
These APIs are used to set (activate/deactivate) the call forwarding option at the Network and to get call forward status. Call forwarding allows a user to forward incoming calls to another party. This service permits a called mobile subscriber to have the network send all incoming calls, or just those associated with a specific Basic service group meeting various call FORWARD conditions, to another directory number. The ability of the served mobile subscriber to originate calls is unaffected. If the service is activated, a call is forwarded only if the enabled forward condition is satisfied.
@n Application has to call this API in order to explicitly register/erase/activate/deactivate the call forwarding. Request will be sent irrespective of whether another SS call forward is already ongoing.

@code
int   tel_set_ss_forward(TapiHandle *handle, const TelSsForwardInfo_t *info, tapi_response_cb callback, void *user_data);
int   tel_get_ss_forward_status(TapiHandle *handle, TelSsClass_t class, TelSsForwardWhen_t condition, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE FOR SET CALL FORWARD
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED INEvent Register and Deregister
void callfwd()
{
	int ret_status = 0;
	TelSsForwardInfo_t pForwardInfo;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	pForwardInfo.Mode = TAPI_CALL_FORWARD_MODE_ENABLE_EV;
	pForwardInfo.Type = TAPI_CS_FORWARD_TYPE_VOICE_EV;
	pForwardInfo.Condition = TAPI_SS_FORWARD_WHEN_UNCONDITIONAL_EV;
	pForwardInfo.NoReplyConditionTimer = 10;

	int len;
	char *cf_number = "9986529874"; //number to which calles need to be forwarded.

	len = strlen(cf_number);
	printf("Length of CF number :%d \n", len);
	memcpy(&(pForwardInfo.szPhoneNumber), cf_number, len);

	ret_status = tel_set_ss_forward(handle,&pForwardInfo,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsForwardResp_t *resp = data;
	int i;

	msg("");
	msgb("tel_set_ss_forward() or tel_get_ss_forward_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d, ForwardCondition=%d, NoReplyWaitTime=%d, bCallForwardingNumberPresend=%d, szCallForwardingNumber=[%s]",
				i,
				resp->record[i].Class,
				resp->record[i].Status,
				resp->record[i].ForwardCondition,
				resp->record[i].NoReplyWaitTime,
				resp->record[i].bCallForwardingNumberPresent,
				resp->record[i].szCallForwardingNumber);
	}
}
@endcode

SAMPLE CODE FOR GET CALL FORWARD STATUS
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callfwdstatus()
{
	int ret_status = 0;
	TelSsForwardType_t Type = TAPI_CS_FORWARD_TYPE_VOICE_EV;
	TelSsForwardWhen_t Condition = TAPI_SS_FORWARD_WHEN_UNCONDITIONAL_EV;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_ss_forward_status(handle,Type,Condition,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}

//WAIT FOR THE EVENT  HERE

static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsForwardResp_t *resp = data;
	int i;

	msg("");
	msgb("tel_set_ss_forward() or tel_get_ss_forward_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d, ForwardCondition=%d, NoReplyWaitTime=%d, bCallForwardingNumberPresend=%d, szCallForwardingNumber=[%s]",
				i,
				resp->record[i].Class,
				resp->record[i].Status,
				resp->record[i].ForwardCondition,
				resp->record[i].NoReplyWaitTime,
				resp->record[i].bCallForwardingNumberPresent,
				resp->record[i].szCallForwardingNumber);
	}
}
//...
@endcode
@}
@defgroup Use_Cases3_4 Call Waiting
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{


		<h3 class="pg">Call Waiting</h3>
These APIs activate/deactivate the call waiting service and provide the status of call wait feature. The call waiting service permits a mobile to be notified of an incoming call (as per basic call procedures) whilst the traffic channel is not available for the incoming call or when the mobile subscriber is engaged in an active or held call. Subsequently, the subscriber can accept, reject, or ignore the incoming call.

@code
int   tel_set_ss_waiting(TapiHandle *handle, const TelSsWaitingInfo_t *info, tapi_response_cb callback, void *user_data);
int   tel_get_ss_waiting_status(TapiHandle *handle, const TelSsClass_t class, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE FOR SET CALL WAITING
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callwaiting()
{
	int ret_status;
	TelSsWaitingInfo_t waitInfo;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	waitInfo.Mode = TAPI_SS_CW_ACTIVATE;
	waitInfo.CallType = TAPI_CALL_TYPE_VOICE_EV;

	ret_status = tel_set_ss_waiting (handle,&waitInfo,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsWaitingResp_t *resp = data;
	int i;

	msg("");
	msgb("tel_set_ss_waiting() or tel_get_ss_waiting_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d",
				i,
				resp->record[i].Class,
				resp->record[i].Status);
	}
}
@endcode

SAMPLE CODE FOR GET CALL WAITING STATUS
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void callwaiting()
{
	int ret_status;
	TelSsCallType_t CallType = TAPI_CALL_TYPE_VOICE_EV;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_ss_waiting_status(handle,CallType,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsWaitingResp_t *resp = data;
	int i;

	msg("");
	msgb("tel_set_ss_waiting() or tel_get_ss_waiting_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - record_num = %d", resp->record_num);

	for (i = 0; i < resp->record_num; i++) {
		msg(" - [%d] Class=%d, Status=%d",
				i,
				resp->record[i].Class,
				resp->record[i].Status);
	}
}
@endcode
@}
@defgroup Use_Cases3_5 CLI Service Status
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{


		<h3 class="pg">CLI Service Status</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Telephony provides an API to query the status of calling line identity service. The CLI service permits a mobile to show or hide his identity to the called party.

@code
int   tel_set_ss_cli_status(TapiHandle *handle, TelSsCliType_t type, TelSsCliStatus_t status, tapi_response_cb callback, void *user_data);
int   int tel_get_ss_cli_status(TapiHandle *handle, TelSsCliType_t type, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE FOR SET CLI STATUS
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void cliservicestatus()
{
	int ret_status;
	TelSsCliType_t type = TAPI_SS_CLI_CLIP;;
	TelSsCliStatus_t status;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_set_ss_cli_status(handle,type,status,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsCliResp_t *resp = data;

	msg("");
	msgb("tel_get_ss_cli_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - type = %d", resp->Type);
	msg(" - status = %d", resp->Status);
}
@endcode

SAMPLE CODE FOR GET CLI STATUS
@code
#include <stdio.h>
#include <TapiCommon.h
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void cliservicestatus()
{
	int ret_status;
	TelSsCliType_t CliType = TAPI_SS_CLI_CLIP;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_ss_cli_status (handle,CliType,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsCliResp_t *resp = data;

	msg("");
	msgb("tel_get_ss_cli_status() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - type = %d", resp->Type);
	msg(" - status = %d", resp->Status);
}
@endcode
@}
@defgroup Use_Cases3_6 Send USSD Request
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{


		<h3 class="pg">Send USSD Request </h3>
This API is used to send a USSD string to the Network. This is an Asynchronous API.

Pre Conditions:
@n No SS and USSD Transaction should be ongoing. If there an ongoing transaction, new USSD request will be returned to the Application with an error (USSD_BUSY)

@code
int  tel_send_ss_ussd_request tel_send_ss_ussd_request(TapiHandle *handle, const TelSsUssdMsgInfo_t *info, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE FOR SEND USSD REQUEST
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void sendussdreq()
{
	char ussdString[TAPI_SS_USSD_DATA_SIZE_MAX];
	int ret_status;

	memset(ussdString, 0, TAPI_SS_USSD_DATA_SIZE_MAX);
	strcpy(ussdString, "*124#");
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_send_ss_ussd_request (handle,ussdString,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
}
//WAIT FOR THE EVENT  HERE

static void app_callback(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSsUssdResp_t *resp = data;

	msg("");
	msgb("tel_send_ss_ussd_request() response receive");
	msg(" - result = 0x%x", result);

	if (!resp)
		return;

	msg(" - type = %d", resp->Type);
	msg(" - status = %d", resp->Status);
	msg(" - length = %d", resp->Length);
	msg(" - string = [%s]", resp->szString);
}
@endcode
@}
@defgroup Use_Cases3_7 AOC Info
@ingroup Use_Cases3_SUPPLEMENTARY_SERVICE
@{


		<h3 class="pg">AOC Info</h3>
These APIs set and read AOC parameter values on the SIM.

Pre Conditions:
@n Advice of charge feature is dependent on the SIM for setting or reading aoc parameters. Setting of AOC requires PIN2 Verification

@code
int   tel_set_ss_aoc_info(TapiHandle *handle, TelCallAocInfo_t *AocSetInfo, tapi_response_cb callback, void *user_data);
int   tel_get_ss_aoc_info(TapiHandle *handle, TelSsAocType_t AocType, tapi_response_cb callback, void *user_data);
{
@endcode

SAMPLE CODE FOR SET AOC INFO
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

//Complete PIN2verification process as mentioned in SIM
void aocinforeq()
{
	//set aoc
	printf(" Resetting Total Cost  \n");

	TelCallAocInfo_t *pAocSetInfo;
	int request_id;
	int ret_status = 0;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	pAocSetInfo = (TelCallAocInfo_t *)calloc(1, sizeof(TelCallAocInfo_t));
	pAocSetInfo->AocType = TAPI_SS_AOC_TYPE_RESET;

	ret = tel_set_ss_aoc_info(handle,pAocSetInfo,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}

//WAIT FOR THE EVENT  HERE
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;
	unsigned int temp_handle = -1;

	//
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d]\n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	switch (eventType)
	{
		case TAPI_EVENT_SS_SET_AOC_CNF:
			printf("Received Event : SS -- TAPI_EVENT_SS_SET_AOC_CNF\n");
			break;
	}//...
}
@endcode

SAMPLE CODE FOR GET AOC INFO
@code
#include <stdio.h>
#include <TapiCommon.h
#include <ITapiSS.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

void aocinforeq()
{
	TelSsAocType_t AocType = TAPI_SS_AOC_TYPE_ACM;
	Tapi_handle handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_ss_aoc_info(handle,AocType,callback,user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("Error  = %d \n", ret_status);
	}
}
//WAIT FOR THE EVENT  HERE

static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;
	unsigned int temp_handle = -1;

	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d]\n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}

	switch (eventType)
	{
		case TAPI_EVENT_SS_AOC_RSP:
			TelCallAocInfo_t aoc_info;
			memcpy(&aoc_info, (TelCallAocInfo_t*)EventData, sizeof(TelCallAocInfo_t));
			printf("Received Event : SS -- TAPI_EVENT_SS_AOC_RSP\n");
			printf(" AOC TYPE :%d\n", aoc_info.AocType);
			break;
	}

}//...
@endcode
@}

	<h2 class="pg">SMS</h2>

@defgroup Use_Cases4_1 Event register and deregister
@ingroup Use_Cases4_SMS
@{

		<h3 class="pg">Event register and deregister</h3>
To receive asynchronous event notifications for the SMS APIs, the registration of related events with their associated call backs is required. When an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.
The telephony framework only provides an interface to the modem and doesnot handle Transport layer, storing and deleting the SMS in the storage except SIM. Because of this we recommend you shouldn’t access this API directly, and should use the MAPI of Message Framework instead.

Notification Events are as follows.
@code
TAPI_EVENT_NETTEXT_INCOM_IND
TAPI_EVENT_NETTEXT_CB_INCOM_IND
TAPI_EVENT_NETTEXT_INCOM_EX_IND
TAPI_EVENT_NETTEXT_CB_INCOM_EX_IND
TAPI_EVENT_NETTEXT_MEMORY_STATUS_IND
TAPI_EVENT_NETTEXT_DEVICE_READY_IND
@endcode

SAMPLE CODE
@code
// REGISTER EVENT
TapiHandle *handle;
char *noti_id = TAPI_NOTI_SMS_INCOM_MSG;
tapi_response_cb callback;
void* user_data;
int api_err;

handle = tel_init();
if (handle)
{
	TEST_DEBUG("tel_init Failed");
}
api_err = tel_register_noti_event(handle, noti_id, callback, user_data);
printf("Nettext Class registration is Done: noti_id is %d, handle is %d\n", noti_id, handle);

// DEREGISTER EVENT
api_err = tel_deregister_noti_event(handle, noti_id);
if (handle)
{
	printf("Event Unregistration Fail\n");
}

// SMS notification callback function
void notification_callback(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	printf(" app _callback is called \n");

	switch (noti_id)
	{
		case TAPI_NOTI_SMS_INCOM_MSG:
			TelSmsDatapackageInfo_t *ptrDataPackage;
			printf("SMS Incoming Message\n");
			ptrDataPackage = (TelSmsDatapackageInfo_t *)EventData;
			// Decoding Service Center Address
			// Decoding TPDU(SMS-DELIVER, SMS-STATUS)
			break;

		case TAPI_NOTI_SMS_CB_INCOM_MSG:
			TelSmsCbMsg_t *ptrCbMsgInfo;
			printf("SMS Cell Broadcasting Incoming Message\n");
			ptrCbMsgInfo = (TelSmsCbMsg_t *)data;
			// Decoding Cell broadcasting Message in szData [Refer to 3GPP TS23.041 9.4.1]
			break;

		case TAPI_NOTI_SMS_INCOM_EX_MSG:
			TelSmsMsgInfo_t *pMsgInfo;
			printf("CDMA SMS Incoming Message\n");
			pMsgInfo = (TelSmsMsgInfo_t *)data;
			// Decoding TPDU(SMS-DELIVER, SMS-STATUS)
			break;

		case TAPI_NOTI_SMS_CB_INCOM_EX_MSG:
			TelSmsMsgInfo_t *pMsgInfo = NULL;
			printf("CDMA SMS Incoming Message\n");
			pMsgInfo = (TelSmsMsgInfo_t *)EventData;
			// Decoding Cell broadcasting Message in szData
			break;

		case TAPI_NOTI_SMS_MEMORY_STATUS:
			int *status = NULL;
			printf("SIM Memory Status Notification\n");
			status = (TelSmsMemStatusType *)data;
			if (*status == TAPI_NETTEXT_PHONE_MEMORY_STATUS_AVAILABLE)
				printf("SIM Memory Available\n");
			else if (*status == TAPI_NETTEXT_PHONE_MEMORY_STATUS_FULL)
				printf("SIM Memory Full\n");
			else
				printf("Unknown Type\n");
			break;

		case TAPI_NOTI_SMS_DEVICE_READY:
			int *pDeviceReady = NULL;
			printf("SMS Device Ready Status Notification\n");
			pDeviceReady = (int*)data;
			if (pDeviceReady->Result == 1)
				printf("Device Ready\n");
			else
				printf("Unknown Type\n");
			break;
	}
	return;
}
@endcode
@}
@defgroup Use_Cases4_2 Send SMS
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Send SMS</h3>
Telephony provides an API to send an SMS to the network. This API allows the transmission of an SMS PDU as defined by 3GPP TS 23.040 (SMS-SUBMIT, SMS-COMMAND) to the lower layers.
If there is a need to send multiple parts of a concatenated message, this API requests for a dedicated link, through the input parameter MoreMessageToSend, from the lower layers.
This will ensure the lower layers do not release the dedicated connection if there are more messages expected.

@code
int tel_send_sms(TapiHandle *handle, const TelSmsDatapackageInfo_t *pDataPackage, int bMoreMsgToSend, tapi_response_cb callback, void* user_data)
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void send_sms()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TelSmsDatapackageInfo_t *pDataPackage;
	int ret_status = TAPI_API_SUCCESS;
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;


	pDataPackage = (TelSmsDatapackageInfo_t*) malloc(sizeof(TelSmsDatapackageInfo_t));

	pDataPackage /* fill the structure appropriately/
	Sca parameter is optional. If you don't provide Service center address, you should fi
	MsgLength is length of szData
	fill the szData in TelSmsDatapackageInfo_t with SMS-SUBMIT or SMS-COMMAND TPDU.

	ret_status = tel_send_sms(handle, pDataPackage, bMoreMsgToSend, on_resp_send_sms, user_data);
	if  (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR THE EVENT  HERE
}

static void on_resp_send_sms(TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("%d", result);
	if (result != 0)
   	{
	        //TEST_DEBUG("******This is nonzero status. ******\n");
	        return;
   	}
}@endcode
@}
@defgroup Use_Cases4_3 Read SMS
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Read SMS</h3>
This API reads a message from SIM card storage. You should not access this API directly; instead use the Message Framework API.

@code
int tel_read_sms_in_sim(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void read_sms()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	int selectedNo;
	int ret;
	char buf[100];
	int returnStatus = 0;

	memset (buf, 0, sizeof (buf));

	returnStatus = tel_get_sms_count (handle, on_resp_get_sms_count, user_data);
	//In the Response of get count tel_read_sms_in_sim will be called
	printf("tel_get_sms_count():  0x%x", returnStatus)
}

static void on_resp_read_msg(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSmsData_t * sim_data;
	int scaAddr_len = 0;
	char * pTPDU;
	int tpdu_len = 0;
	char diallingNum[TAPI_NETTEXT_ADDRESS_LEN_MAX + 1] = { 0, };
	char scaAddr[TAPI_NETTEXT_SCADDRESS_LEN_MAX + 2] = { 0, }; //service center address
	int sca_ton, sca_npi;
	int position;

	sim_data = (TelSmsData_t *) data;

	//find msg_status from sim data

	position = 0;
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

	printf("SCA Number : %s tpdu_len is %d", scaAddr, tpdu_len);

	pTPDU = malloc (sizeof(unsigned char) * tpdu_len);
	if (!pTPDU)
		return;

	printf("bfor memcopy position is %d", position);
	memcpy (pTPDU, & (sim_data->SmsData.szData[0]), tpdu_len);
	printf("after memcpy");

	DecodeSmsDeliverTpdu (tpdu_len, pTPDU);
}
//...
@endcode
@}
@defgroup Use_Cases4_4 Write Sms
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Write Sms</h3>
This API writes a message to SIM storage area.
@n The parameter of this API is changed into TelSmsData_t.
@n If SIM index in TelSmsData_t is -1, SMS message is stored at the first empty SIM index . The contents of szData is SMS-SUBMIT, SMS-DELIVER or SMS-STATUS REPORT TPDU. You should not access this API directly; use the Message Framework API.

@code
int tel_write_sms_in_sim(TapiHandle *handle, const TelSmsData_t *pWriteData, tapi_response_cb callback, void* user_data);@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void write_sms()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	int ret_status = TAPI_API_SUCCESS;
	TapiHandle *handle;//Obtained from tel_init();
	tapi_response_cb callback;
	void* user_data;

	TelSmsData_t *pWriteData;
	char *msg = "This is an Test SMS";
	char *SCA = "821091";

	pWriteData =(TelSmsData_t *)malloc(sizeof(TelSmsData_t));

	conv_service_center_address(pWriteData->SmsData.Sca, SCA); //convert service center address
	conv_msg_into_tpdu(pWriteData->SmsData.szData, pWriteData->SmsData.MsgLength, msg); // convert message into TPDU
	pWrite->MsgStatus = TAPI_NETTEXT_STATUS_READ;
	pWrite->SimIndex = -1;

	ret_status = tel_write_sms_in_sim(handle, pWriteData, on_resp_write_sms, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR EVENT HERE
}
static void on_resp_write_sms(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *index = data;

	printf("tel_write_sms_in_sim() response receive");
	printf(" - result = 0x%x", result);
	printf(" - index = %d", *index);
}
@endcode
@}
@defgroup Use_Cases4_5 Delete Sms
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Delete Sms</h3>
This API deletes a message specified by the index (SIM index used when storing the sms) number or all the messages in the SIM storage area. If SIM index is -1, all SMS stored in SIM are deleted. You should not access this API directly; use the Message Framework API.

@code
int tel_delete_sms_in_sim(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void delete_sms()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	int ret_status = TAPI_API_SUCCESS;
	TapiHandle *handle;//Obtained from tel_init();
	tapi_response_cb callback;
	void* user_data;
	int index;

	ret_status = tel_delete_sms_in_sim(handle, index, on_resp_delete_sms, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR EVENT HERE
}
static void on_resp_delete_sms(TapiHandle *handle, int result, void *data, void *user_data)
{
	int *index = data;
	printf("tel_delete_sms_in_sim() response receive");
	printf(" - result = 0x%x", result);
	printf(" - index = %d", *index);
}
@endcode
@}
@defgroup Use_Cases4_6 Getting Sms Count
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Getting Sms Count</h3>
This API is used to retrieve message count information such as Total record count, used record count and the indices list for SIM Storage. You should not access this API directly; use the Message Framework API.

@code
int tel_get_sms_count(TapiHandle *handle, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void get_count()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	ret_status = tel_get_sms_count(handle, on_resp_get_count, user_data);
	if  (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR EVENT HERE
}
static void on_resp_get_count(TapiHandle *handle, int result, void *data, void *user_data)
{
	static TelSmsStoredMsgCountInfo_t *countInfo;
	int loop_counter = 0;
	TapiResult_t returnStatus = TAPI_API_SUCCESS;

	countInfo = (TelSmsStoredMsgCountInfo_t*) data;

	printf("tel_get_sms_count() response receive");
	printf(" - result = 0x%x", result);

	if (countInfo->UsedCount != 0x00)	//if used count is not zero
			{
		printf("Index LIST..........");
		for (loop_counter = 0; loop_counter < countInfo->UsedCount;
				loop_counter++) {
			printf("[%02x]", countInfo->IndexList[loop_counter]);
			returnStatus = tel_read_sms_in_sim (handle, countInfo->IndexList[loop_counter], on_resp_read_msg, user_data);
			printf("After read msg: returnstatus %d", returnStatus);
		}
		printf("In MsgCountNotification total cnt is %d, usedcnt is %dapi_err %d",
				countInfo->TotalCount, countInfo->UsedCount, returnStatus);
	}

	printf("In MsgCountNotification total cnt is %d, usedcnt is %d",
			countInfo->TotalCount, countInfo->UsedCount);
}
@endcode
@}
@defgroup Use_Cases4_7 Setting Sms CB message
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Setting Sms CB message</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n This API is used to set the SMS CB Message Identifiers in the appropriate EF-CBMI/EF-CBMIR file in (U)SIM.
This API also indicates the underlying provider to enable or disable CB Channel on which CB messages are received.
You should not access this API directly; use the Message Framework API.

@code
int  tel_set_sms_cb_config(handle, pCBConfig, callback, user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void set_cbconfig()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	pCBConfig = calloc (1, sizeof(TelSmsCbConfig_t));
	if (!pCBConfig)
		return -1;

	msg("Enter CB ON/OFF (1: Enable, 0:Disable): ");
	pCBConfig->CBEnabled =;//fill appropriately

	msg("Enter Max ID Count: ");
	pCBConfig->MsgIdMaxCount =);//fill appropriately

	msg("Enter MsgIdRangeCount ( < 10 ): ");
	pCBConfig->MsgIdRangeCount =;//fill appropriately

	if (pCBConfig->MsgIdRangeCount <= 0
			|| pCBConfig->MsgIdRangeCount >= TAPI_NETTEXT_GSM_SMS_CBMI_LIST_SIZE_MAX) {
		printf("Bad Range value");
		free (pCBConfig);
		return -1;
	}

	for (i = 0; i < pCBConfig->MsgIdRangeCount; i++) {
		printf("Enter %d FromMsgId : ", i + 1);
		pCBConfig->MsgIDs[i].Net3gpp.FromMsgId = _get_int();

		printf("Enter %d ToMsgId : ", i + 1);
		pCBConfig->MsgIDs[i].Net3gpp.ToMsgId = _get_int();

		printf("Enter %d Selected : ", i + 1);
		pCBConfig->MsgIDs[i].Net3gpp.Selected = _get_int();
	}

	pCBConfig->Net3gppType = 0x01;

	returnStatus = tel_set_sms_cb_config(handle, pCBConfig, on_resp_set_sms_cb_config, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_set_sms_cb_config (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("");
	printf("tel_set_sms_cb_config() response receive");
	printf(" - result = 0x%x", result);
}@endcode
@}
@defgroup Use_Cases4_8 Getting Sms CB configuration
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Getting Sms CB configuration</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n This API is used to retrieve SMS CB configuration options from EFcbmi file in the SIM. You should not access this API directly.
Use the Message Framework API.

@code
int tel_get_sms_cb_config(TapiHandle *handle, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:

@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void get_cbconfig()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	ret_status = tel_get_sms_cb_config(handle, on_resp_get_cb_config, user_data);

	printf ("The return value is %d\n", ret_status);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
	//WAIT FOR EVENT HERE
}
static void on_resp_get_cb_config (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSmsCbConfig_t * CBConfig;
	int i = 0;

	CBConfig = (TelSmsCbConfig_t *) data;

	printf("tel_get_sms_cb_config() response receive");
	printf(" - result = 0x%x", result);


	if (CBConfig->CBEnabled == TRUE)
		msg("Cell Broadcast Msg Enabled...")
	else
		msg("Cell Broadcast Msg Disabled...")


	if (CBConfig->Net3gppType == 0x01)
		msg("Network type is 3gpp ")
	else if (CBConfig->Net3gppType == 0x02)
		msg("Network type is CDMA");

	printf("CBMI Range Count: %d \n", CBConfig->MsgIdRangeCount);

	if (CBConfig->MsgIdRangeCount != 0) {
		msg("----- CBMI List -----");
		for (i = 0; i < CBConfig->MsgIdRangeCount; i++) {
			msg("From No.%d - [0x%04x]", i,
					CBConfig->MsgIDs[i].Net3gpp.FromMsgId);
			msg("To No.%d - [0x%04x]", i, CBConfig->MsgIDs[i].Net3gpp.ToMsgId);
		}
	}
}

//...
@endcode
@}
@defgroup Use_Cases4_9 Service Center Address
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Service Center Address</h3>
This API sets the SMS Service Centre Address information in order to send the SMS.
@n It is also possible to get current SMS Service Centre Address information.
Currently Only index 0 is supported in Aquila's Telephony OEM Plugin. You should not access this API directly; use the Message Framework API.

@code
int tel_set_sms_sca(TapiHandle *handle, const TelSmsAddressInfo_t *pSCA, int index, tapi_response_cb callback, void* user_data);
int tel_get_sms_sca(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void set_sca()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	TelSmsAddressInfo_t sca;

	memset (&sca, 0, sizeof(TelSmsAddressInfo_t));

	sca.DialNumLen = 0x5;
	sca.Npi = TAPI_SIM_NPI_ISDN_TEL;
	sca.Ton = TAPI_SIM_TON_INTERNATIONAL;
	sca.szDiallingNum[0] = 0x28;
	sca.szDiallingNum[1] = 0x01;
	sca.szDiallingNum[2] = 0x19;
	sca.szDiallingNum[3] = 0x11;
	sca.szDiallingNum[4] = 0x11;


	ret_status = int tel_set_sms_sca(handle, pSCA, index, on_resp_set_sms_sca, user_data);
	//[Note] Telephony Emulator Not Support

	printf("returnstatus after scaddr set is %d requestId:%d \n", ret_status, pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}

static void on_resp_set_sms_sca (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("tel_set_sms_sca() response receive");
	printf(" - result = 0x%x", result);
}

//..

//get SCA
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void get_sca()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	ret_status = int tel_get_sms_sca(handle, index, on_resp_get_sms_sca, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}

static void on_resp_get_sms_sca (TapiHandle *handle, int result, void *data,
		void *user_data)
{
	TelSmsAddressInfo_t *scaInfo = data;
	unsigned int i = 0;

	printf("tel_get_sms_sca() response receive");
	printf(" - result = 0x%x", result);
	printf(" - TON = %d", scaInfo->Ton);
	printf(" - NPI = %d", scaInfo->Npi);
	printf(" - DialNumLen = %d", scaInfo->DialNumLen);
	printf(" - SCA Num");

	for (i = 0; i < scaInfo->DialNumLen; i++) {
		printf("[%02x]", scaInfo->szDiallingNum[i]);
		if (i % 10 == 9)
			printf("\n");
	}
}


@endcode
@}
@defgroup Use_Cases4_10 Sms Preferred Bearer
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Sms Preferred Bearer</h3>
<strong>[Note] Telephony Emulator and Aquila’s Telephony OEM Plugin do not support this feature.</strong>
@n Telephony provides APIs to set SMS preferred bearer on which SMS has to be transmitted.
You should not access this API directly; use the Message Framework API.

@code
int tel_get_sms_preferred_bearer(TapiHandle *handle, tapi_response_cb callback, void* user_data);
int tel_set_sms_preferred_bearer(TapiHandle *handle, TelSmsBearerType_t BearerType, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void set_pb()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	TelSmsBearerType_t BearerType = TAPI_NETTEXT_BEARER_PS_ONLY;

	ret_status = tel_get_sms_preferred_bearer(handle, on_resp_set_sms_preferred_bearer, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_set_sms_preferred_bearer (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("");
	printf("tel_set_sms_preferred_bearer() response receive");
	printf(" - result = 0x%x", result);
}
//get preferred bearer
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>
void get_pb()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	ret_status = tel_get_sms_preferred_bearer(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_get_pref_bearer (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("");
	printf("tel_get_sms_preferred_bearer() response receive");
	printf(" - result = 0x%x", result);
}
@endcode
@}
@defgroup Use_Cases4_11 Sms Parameters
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Sms Parameters</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n Telephony provides APIs to set the header parameters of SMS, which are used in the origination of MO messages. It also provides API to get the SMS parameters for a particular SMS (sent/received) based on the SIM index where it is stored. You should not access this API directly; use the Message Framework API.

@code
int tel_get_sms_parameters(TapiHandle *handle, int index, tapi_response_cb callback, void* user_data);
int tel_set_sms_parameters(TapiHandle *handle, const TelSmsParams_t *pSmsSetParameters, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void set_param()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	int ret_status;

	TelSmsParams_t SmsSetParameters;

	SmsSetParameters.RecordIndex = 0x01;
	SmsSetParameters.RecordLen = 28;
	memcpy(SmsSetParameters.TpDestAddr.szDiallingNum, "9986529874", 10);
	printf("\ndial no is %s\n", SmsSetParameters.TpDestAddr.szDiallingNum);

	SmsSetParameters.TpDestAddr.DialNumLen = 10;
	SmsSetParameters.TpDestAddr.Ton = TAPI_SIM_TON_NATIONAL;//national no
	SmsSetParameters.TpDestAddr.Npi = TAPI_SIM_NPI_NATIONAL;

	ret_status = tel_set_sms_parameters(handle, pSmsSetParameters, on_resp_set_sms_params, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_set_sms_params (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("tel_set_sms_params() response receive");
	printf(" - result = 0x%x", result);
}
//...

//get params
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void get_params()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	ret_status = tel_get_sms_parameters(handle, index, on_resp_get_sms_parameters, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_get_sms_parameters (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSmsParams_t *smsp_param;

	smsp_param = (TelSmsParams_t *) data;

	printf("tel_get_sms_parameters() response receive");
	printf(" - result = 0x%x", result);

	printf("record index is 0x%x", smsp_param->RecordIndex);
	printf("record len  is 0x%x", smsp_param->RecordLen);
	printf("alpha_id len  is 0x%x ", (int )smsp_param->AlphaIdLen);
	printf("alpha_id is %s ", smsp_param->szAlphaId);
	printf("param indicator is  0x%x", smsp_param->ParamIndicator);
	printf("dest dialling num is %s", smsp_param->TpDestAddr.szDiallingNum);
	printf("svcaddr dialling num is %s", smsp_param->TpSvcCntrAddr.szDiallingNum);
	printf("pid 0x%x", smsp_param->TpProtocolId);
	printf("dcs is 0x%x", smsp_param->TpDataCodingScheme);
	printf("validity is 0x%x", smsp_param->TpValidityPeriod);
}
@endcode
@}
@defgroup Use_Cases4_12 Sending Delivery Report
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Sending Delivery Report</h3>
This API sends a SMS-deliver report to the network, after receiving an incoming SMS. You should not access this API directly.

@code
int tel_send_sms_deliver_report(TapiHandle *handle, const TelSmsDatapackageInfo_t *pDataPackage, TelSmsResponse_t RPCause, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>
void send_delivery()
{
	int ret_status;
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;

	TelSmsResponse_t RPCause;
	TelSmsDatapackageInfo_t *del_report = NULL;

	del_report = malloc(sizeof(TelSmsDatapackageInfo_t));
	memset(del_report, 0, sizeof(TelSmsDatapackageInfo_t));
	//Encode Send Delivery Report here
	//EncodeSmsDeliveryReportTpdu();

	RPCause = TAPI_NETTEXT_SENDSMS_SUCCESS;
	printf("***receive message (Api:SendDeliverreport)****\n");

	ret_status = tel_send_sms_deliver_report(handle, pDataPackage, RPCause, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_DeliverReport_msg (TapiHandle *handle, int result, void *data, void *user_data)
{
	int *index = data;

	printf("");
	printf("tel_send_sms_deliver_report() response receive");
	printf(" - result = 0x%x", result);
	printf(" - index = %d", *index);
}
@endcode
@}
@defgroup Use_Cases4_13 Setting Memory Status
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Setting Memory Status</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n This API is used by applications to inform the modem about the memory status of PDA (whether FULL or AVAILABLE) so that modem can inform network. You should not access this API directly.

@code
int tel_set_sms_memory_status(TapiHandle *handle, int memoryStatus, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>
void set_memstatus()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	int ret_status;
	int MemoryStatus = TAPI_NETTEXT_PDA_MEMORY_STATUS_AVAILABLE;

	ret_status = tel_set_sms_memory_status(handle, memoryStatus, on_resp_set_mem_status, user_data);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_set_mem_status (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("tel_set_sms_mem_status() response receive");
	printf(" - result = 0x%x", result);
}
@endcode
@}
@defgroup Use_Cases4_14 Setting Message Status
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Setting Message Status</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
This API is used by applications to set the message status in the Sim file. You should not access this API directly; use the Message Framework API.

@code
int tel_set_sms_message_status(TapiHandle *handle, int index, TelSmsMsgStatus_t msgStatus, tapi_response_cb callback, void* user_data);

@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void set_msgstatus()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	int ret_status;
	int Index = 2;
	TelSmsMsgStatus_t MsgStatus = TAPI_NETTEXT_STATUS_READ;

	ret_status = tel_set_sms_message_status(handle, index, msgStatus, on_resp_set_msg_status, user_data);
	printf ("The return value is %d\n", ret_status);

	returnStatus = tel_read_sms_in_sim (handle, index, on_resp_read_msg, user_data);
	printf("returnStatus after read is %d",returnStatus);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_set_msg_status (TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("tel_set_sms_msg_status() response receive");
	printf(" - result = 0x%x", result);
}
@endcode
@}
@defgroup Use_Cases4_15 Getting SMS Parameter Count
@ingroup Use_Cases4_SMS
@{


		<h3 class="pg">Getting SMS Parameter Count</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n This API is used by applications to get the count of sms parameter records stored in Sim EF. You should not access this API directly.

@code
int tel_get_sms_parameter_count(TapiHandle *handle, tapi_response_cb callback, void* user_data);
@endcode

<strong>This API is restricted for direct use.  Use the Message Framework API instead.</strong>

SAMPLE CODE:
@code
#include <stdio.h>
#include <stdlib.h>
#include <TapiCommon.h>
#include <ITapiNetText.h>

void get_paramcount()
{
	//Obtain Tapi Handle as mentioned in Event Register and Deregister
	TapiHandle *handle;
	tapi_response_cb callback;
	void* user_data;
	int ret_status;

	ret_status = tel_get_sms_parameter_count(handle, on_resp_get_paramcnt, user_data);
	printf ("The return value is %d\n", ret_status);
	if (ret_status == TAPI_API_SUCCESS)
	{
		printf("successful\n");
	}
	else
	{
		printf("error = %d\n", ret_status);
	}
}
static void on_resp_get_paramcnt (TapiHandle *handle, int result, void *data, void *user_data)
{
	int * RecordCount;

	RecordCount = (int *) data;

	printf("tel_get_sms_parameter_count() response receive");
	printf(" - result = 0x%x", result);
	printf(" - In param_count_noti the record count is %d", *RecordCount);
}
@endcode
@}

@defgroup Use_Cases5_1 Event register and deregister
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Event register and deregister</h3>
To receive asynchronous event notifications for the network APIs, the registration of related events with their associated call backs is required. When an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

Network Notification Events
@code
TAPI_EVENT_NETWORK_LOCATIONCELLINFO_IND
TAPI_EVENT_NETWORK_RADIO_INFO_IND
TAPI_EVENT_NETWORK_SPN_INFO
TAPI_EVENT_NETWORK_DISPLAYINFO_IND
@endcode

SAMPLE CODE:
@code

TapiHandle *handle;
char *noti_id = TAPI_EVENT_NETWORK_LOCATIONCELLINFO_IND;
tapi_response_cb callback;
void* user_data;
int api_err;

handle = tel_init();
if (handle)
{
	TEST_DEBUG("tel_init Failed");
}

// REGISTER EVENT
api_err = tel_register_noti_event(handle, noti_id, app_callback, user_data);
if (api_err == TAPI_API_SUCCESS)
{
	printf("Network notification registration is Done: noti_id is %d, handle is %d\n", noti_id, handle);
}

// DEREGISTER EVENT
api_err = tel_deregister_noti_event(handle, noti_id);
if (api_err != TAPI_API_SUCCESS)
{
	printf("Event Unregistration Fail\n");
}

// Network notification callback function
void app_callback(void)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void *EventData = NULL;

	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;
	printf(" app _callback is called \n");

	print_events((int)eventType);
	printf("\n event came in power_callback [%d] \n", eventType);
	printf("\n expected event is  in callback [%d] \n", expected_event);

	switch (eventType)
	{
		case TAPI_EVENT_NETWORK_LOCATIONCELLINFO_IND:
			//process notification data
			break;

		case TAPI_EVENT_NETWORK_RADIO_INFO_IND:
			//process notification data
			break;

		case TAPI_EVENT_NETWORK_SPN_INFO:
			//process notification data
			break;

		case TAPI_EVENT_NETWORK_DISPLAYINFO_IND:
			//process notification data
			break;
	}
}
@endcode
@}
@defgroup Use_Cases5_2 Network Selection
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Network Selection</h3>
Telephony provides APIs which can request the lower layers use the network (PLMN) which has been selected by the user from the Network List displayed to the User.

@code
int tel_select_network_automatic(TapiHandle *handle, tapi_response_cb callback, void *user_data)
int tel_select_network_manual(TapiHandle *handle, const char *plmn, int act, tapi_response_cb callback, void *user_data)
@endcode

SAMPLE CODE:
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void select_nw()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;
	unsigned int plmn = 0;

	//CASE 1. MANUAL MODE
	plmn = 45454;
	act = 0x1;
	ret_status = tel_select_network_manual(handle, plmn, act, callback, user_data);

	// CASE 2. AUTOMATIC MODE
	ret_status = tel_select_network_automatic(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);

	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType)
	{
		case TAPI_EVENT_NETWORK_SELECT_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_SELECT_CNF $$$$$$ \n");
	}
}
@endcode
@}
@defgroup Use_Cases5_3 Network Search
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Network Search</h3>
This API is used to search for the available networks, and to provide the Network List to the User/Application.

@code
int tel_search_network(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE:
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void searchnw()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_search_network(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;
	unsigned int temp_handle = -1;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType)   //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_SEARCH_CNF:
			int ui_entry_count = 0;
			TelNetworkPlmnList_t *pNetSearchCnf;
			pNetSearchCnf = (TelNetworkPlmnList_t *)EventData;
			while (ui_entry_count <  pNetSearchCnf->networks_count)
			{
				printf("Type_of_plmn[%d] 0:unkwon,1:home,2:available,3:forbidden, NetworkName[%s]",
						pNetSearchCnf->network_list[ui_entry_count].type_of_plmn,
						pNetSearchCnf->network_list[ui_entry_count].network_name);
				 printf("ServiceProviderName[%s]", pNetSearchCnf->network_list[ui_entry_count].service_provider_name);
				 printf("PLMN ID[%lu]", pNetSearchCnf->network_list[ui_entry_count].plmn_id);
				ui_entry_count++;
			}
			break;
	}
	//...
}
@endcode
@}
@defgroup Use_Cases5_4 Selection Mode
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Selection Mode</h3>
Telephony provides APIs to set and retrieve the current mode of network selection i.e. automatic or manual. Request for Automatic network selection or Manual network selection will allow OEM provider to do PLMN Selection based on network selection preference.

@code
int tel_get_network_selection_mode(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void get_selmode()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	//GET THE SELECTION MODE

	ret_status = tel_get_network_selection_mode (handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) // REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_GETSELECTIONMODE_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_GETSELECTIONMODE_CNF $$$$$$ \n");
			break;
	}
	//...
}
@endcode
@}
@defgroup Use_Cases5_5 Service Domain
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Service Domain</h3>
Telephony provides APIs so that User/application can configure the service domain and also retrieve the present network service domain.

@code
int tel_set_network_service_domain(TapiHandle *handle, TelNetworkServiceDomain_t domain, tapi_response_cb callback, void *user_data);
int tel_get_network_service_domain(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE
@code
#include <stdio.h>
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void set_servicedomain()
{
	int ret_status;
	TapiHandle *handle;
	TelNetworkServiceDomain_t domain;
	tapi_response_cb callback;
	void *user_data;

	//SET NETWORK SERVICE DOMAIN
	domain = TAPI_NETWORK_SERVICE_DOMAIN_AUTOMATIC;

	ret_status = tel_set_network_service_domain (handle, domain, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;
	unsigned int temp_handle = -1;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_SET_SVC_DOMAIN_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_SET_SVC_DOMAIN_CNF $$$$$$ \n");
			break;
	}

	//...
}

//GET NETWORK SERVICE DOMAIN
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"
void get_servicedomain()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_network_service_domain (handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_GET_SVC_DOMAIN_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_GET_SVC_DOMAIN_CNF $$$$$$ \n");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases5_6 Network Mode
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Network Mode</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n The Network Mode (Automatic, GSM, and WCDMA) can be configured at OEM provider, based on which lower layers can scan only those radio access technologies, to register with network.

@code
int tel_set_network_mode(TapiHandle *handle, int mode, tapi_response_cb callback, void *user_data);
int tel_get_network_mode(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void setnwmode()
{
	int ret_status;
	TapiHandle *handle;
	int mode;
	tapi_response_cb callback;
	void *user_data;

	mode = 0x01;
	ret_status = tel_set_network_mode(handle, mode, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_SETNWMODE_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_SETNWMODE_CNF $$$$$$ \n");
			break;
			//...
	}
}

//GET NETWORK MODE
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

void getnwmode()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_network_mode(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_GETNWMODE_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_GETNWMODE_CNF $$$$$$ \n");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases5_7 Network Band
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Network Band</h3>
Telephony provides APIs to set and retrieve the network band and allows the underlying OEM provider to scan the set band.

@code
int tel_set_network_band(TapiHandle *handle, TelNetworkBandPreferred_t mode, TelNetworkBand_t band, tapi_response_cb callback, void *user_data);
int tel_get_network_band(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE:
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void setnwband()
{
	int ret_status;
	TapiHandle *handle;
	TelNetworkBandPreferred_t mode;
	TelNetworkBand_t band;
	tapi_response_cb callback;
	void *user_data;

	mode = TAPI_NETWORK_BAND_MODE_PREFERRED;
	band = TAPI_NETWORK_BAND_TYPE_GSM_900_1800;

	ret_status = tel_set_network_band (handle, mode, band, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_SETNWBAND_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_SETNWBAND_CNF $$$$$$ \n");
			break;
			//...
	}
}

//GET NETWORK BAND
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"
void getnwband()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_network_band(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) // REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_GETNWBAND_CNF:
			printf("\n$$$$$$ TAPI_EVENT_NETWORK_GTNWBAND_CNF $$$$$$ \n");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases5_8 Preferred PLMN
@ingroup Use_Cases5_NETWORK
@{

<h3 class="pg">Preferred PLMN</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
@n Telephony provides APIs which can be used to set and retrieve the preferred plmn of network.

@code
int tel_set_network_preferred_plmn(TapiHandle *handle, TelNetworkPreferredPlmnOp_t operation, TelNetworkPreferredPlmnInfo_t *info, tapi_response_cb callback, void *user_data);
int tel_get_network_preferred_plmn(TapiHandle *handle, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE
@code
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN  Event Register and Deregister
void set_preferredplmn()
{
	int ret_status;
	TapiHandle *handle;
	TelNetworkPreferredPlmnOp_t operation;
	TelNetworkPreferredPlmnInfo_t info;
	tapi_response_cb callback;
	void *user_data;

	unsigned char *plmn = "45454";

	//SET PLMN
	operation = TAPI_NETWORK_PREF_PLMN_ADD;
	memset(&info, 0, sizeof(TelNetworkPreferredPlmnInfo_t));
	info.Index = 0;
	info.SystemType = TAPI_NETWORK_SYSTEM_GSM;
	memcpy(info.Plmn, plmn, strlen(plmn));

	ret_status = tel_set_network_preferred_plmn(handle, operation, &info, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}

	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_SETPREFFPLMN_CNF:
			printf("\n$$$$$$ TAPI TAPI_EVENT_NETWORK_SETPREFFPLMN_CNF $$$$$$ \n");
			break;
	}
	//...
}
@endcode

@code
//GET PLMN
#include <ITapiNetwork.h>
#include <stdio.h>
#include "TapiCommon.h"
void get_preferredplmn()
{
	int ret_status;
	TapiHandle *handle;
	tapi_response_cb callback;
	void *user_data;

	ret_status = tel_get_network_preferred_plmn(handle, callback, user_data);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status); //WAIT FOR EVENT HERE
	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	//...
	//...
	switch (eventType) //REFER Network Selection TO GET eventType
	{
		case TAPI_EVENT_NETWORK_GETPREFFPLMN_CNF:
			printf("\n$$$$$$ TAPI TAPI_EVENT_NETWORK_GETPREFFPLMN_CNF $$$$$$ \n");
			break;
	}
@endcode
@}
@defgroup Use_Cases6_1 SIM
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">SIM</h3>
Event Register and Deregister
To receive asynchronous event notifications for the SIM APIs, the registration of related events with their associated call backs is required. When an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

SAMPLE CODE:
@code
// REGISTER EVENT
unsigned int subscription_id = 0;
TapiResult_t api_err;
TapiHandle *handle;  // Handle given by tel_init()
char *noti_id; // Get Noti id
tapi_notification_cb callback; //Initialized call-back function pointer in which notification data is returned
void *user_data = NULL; // Set User data

api_err = TelTapiInit();
if (api_err != TAPI_API_SUCCESS)
{
	TEST_DEBUG("TelTapiInit Failed - api_err = %d \n", api_err);
}

api_err = tel_register_noti_event(handle, noti_id, callback, user_data);
printf("SIM Event registration is Done:");

// DEREGISTER EVENT
api_err = tel_deregister_noti_event(handle, noti_id);
if (api_err != TAPI_API_SUCCESS)
{
	printf("Event Class Unregeration Fail\n");

}
@endcode
@}
@defgroup Use_Cases6_2 PIN, SIM Lock operations
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">PIN, SIM Lock operations</h3>
Telephony provides APIs to enable/disable pin, change pin, unblock pin, pin verification and sim lock enable/disable/verification. It is also possible to retrieve the pin/sim lock status.

@code
int tel_enable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *sec_data, tapi_response_cb callback, void *user_data);
int tel_disable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *sec_data, tapi_response_cb callback, void *user_data);
int tel_change_sim_pins(TapiHandle *handle, const TelSimSecPw_t *old_pin, const TelSimSecPw_t *new_pin, tapi_response_cb callback, void *user_data);
int tel_verify_sim_puks(TapiHandle *handle, const TelSimSecPw_t *puk_data, const TelSimSecPw_t *new_pin_data, tapi_response_cb callback, void *user_data);
int tel_verifiy_sim_pins(TapiHandle *handle, const TelSimSecPw_t *pin_data, tapi_response_cb callback, void *user_data);
int tel_get_sim_facility(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);
int tel_get_sim_lock_info(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE: PIN1/PIN2/SIM LOCK/PUK1 VERIFICATION AND CHANGE PIN1
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//  OPERATION REQUEST PIN1 VERIFICATION PART
#define PIN1_NORMAL "0000" //Sample PIN1 code

Void pin1_verify()
{
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH + 1;
	char init_pin_val[length] ;
	TelSimSecPw_t pin_data;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data = NULL; // Set User data

	strcpy(init_pin_val, PIN1_NORMAL);

	pin_data.type = TAPI_SIM_PTYPE_PIN1;
	pin_data.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", pin_data.pw_len);

	pin_data.pw = (char*)malloc(length);
	memcpy(pin_data.pw, init_pin_val, length);

	err_code = tel_verifiy_sim_pins(handle, &pin_data, on_resp_sim_sec_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT FOR EVENT FROM HERE
}

//  OPERATION REQUEST PIN2 VERIFICATION PART
#define PIN2_NORMAL "0000" //Sample PIN2 code
Void verify_pin2()
{
	int request_id = 0;
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length] ;
	TelSimSecPw_t pin_data;

	strcpy(init_pin_val, PIN2_NORMAL);

	pin_data.type = TAPI_SIM_PTYPE_PIN2;
	pin_data.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", pin_data.pw_len);

	pin_data.pw = (char*)malloc(length);
	memcpy(pin_data.pw, init_pin_val, length);

	err_code = tel_verifiy_sim_pins(&pin_data, &request_id);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT FOR EVENT FROM HERE
}

//  OPERATION REQUEST CHANGE PIN1 PART
#define PIN1_ORG "0000" //Sample old PIN1 code
#define PIN1_NEW "1111" //Sample new PIN1 code
void change_pins()
{
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_old_pin_val[length] ;
	char init_new_pin_val[length];
	TelSimSecPw_t old_pin;
	TelSimSecPw_t new_pin;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data = NULL; // Set User data

	memset(&init_old_pin_val, 0, length);
	memset(&init_new_pin_val, 0, length);

	strcpy(init_old_pin_val, PIN1_ORG);

	old_pin.type = TAPI_SIM_PTYPE_PIN1;
	old_pin.pw_len = strlen(init_old_pin_val);
	printf("pw_len[%d]", old_pin.pw_len);
	old_pin.pw = (char*)malloc(length);
	memcpy(old_pin.pw, init_old_pin_val, length);

	strcpy(init_new_pin_val, PIN1_NEW);

	new_pin.type = TAPI_SIM_PTYPE_PIN1;
	new_pin.pw_len = strlen(init_new_pin_val);
	printf("pw_len[%d]", new_pin.pw_len);
	new_pin.pw = (char*)malloc(length);
	memcpy(new_pin.pw, init_new_pin_val, length);

	err_code = tel_change_sim_pins(handle, &old_pin, &new_pin, on_resp_sim_sec_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//  OPERATION REQUEST VERIFICATION PUK1 PART
#define PUK1_NORMAL "00000000" //Sample PUK1 code
#define PIN1_NORMAL "0000" //Sample PIN1 code

void verify_puks()
{
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH + 1;

	char init_pin_val[length];
	char init_puk_val[length];

	TelSimSecPw_t puk_data;
	TelSimSecPw_t new_pin_data;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data = NULL; // Set User data

	strcpy(init_pin_val, PIN1_NORMAL);
	strcpy(init_puk_val, PUK1_NORMAL);

	puk_data.type = TAPI_SIM_PTYPE_PUK1;   // 0x00
	puk_data.pw_len = length;
	puk_data.pw_len = strlen(init_puk_val);
	printf("pw_len[%d]", puk_data.pw_len);
	memcpy(puk_data.pw, init_pin_val, length);

	new_pin_data.type = TAPI_SIM_PTYPE_PIN1;   // 0x00
	new_pin_data.pw_len = strlen(init_pin_val);
	printf("pw_len[%d]", new_pin_data.pw_len);
	new_pin_data.pw = (char*)malloc(length);
	memcpy(new_pin_data.pw, init_pin_val, length);

	err_code = tel_verify_sim_puks(handle, &puk_data, &new_pin_data, on_resp_sim_sec_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}
//  OPERATION REQUEST SIM LOCK VERIFICATION PART
#define SIM_NORMAL "0000" //Sample SIM Lock code
Void verify_sim()
{
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH + 1;
	char init_pin_val[length] ;
	TelSimSecPw_t pin_data;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data = NULL; // Set User data

	strcpy(init_pin_val, SIM_NORMAL);

	pin_data.type = TAPI_SIM_PTYPE_SIM;
	pin_data.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", pin_data.pw_len);

	pin_data.pw = (char*)malloc(length);
	memcpy(pin_data.pw, init_pin_val, length);

	err_code = tel_verifiy_sim_pins(handle, &pin_data, on_resp_sim_sec_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT FOR EVENT FROM HERE
}

//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_sim_sec_op(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPinOperationResult_t sec_rt = result;
	TelSimSecResult_t *rt = data;

	printf("sec_rt[%d]", sec_rt);
	printf("rt->type[%d]", rt->type);
	printf("rt->retry_count[%d]", rt->retry_count);
}
@endcode

SAMPLE CODE: ENABLE/DISABLE PIN1 and SIM LOCK
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//  OPERATION REQUEST DISABLING PIN1 PART
#define PIN1_NORMAL "0000" //Sample PIN1 code
void disable_pin1()
{
	int request_id = 0;
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length];

	strcpy(init_pin_val, PIN1_NORMAL);

	TelSimFacilityPw_t sec_data;
	sec_data.lock_type = TAPI_SIM_PTYPE_PIN1;   // 0x00
	sec_data.pw_len = strlen(init_pin_val);
	printf("pw_len[%d]", sec_data.pw_len);

	sec_data.pw = (char*)malloc(length);
	memcpy(sec_data.pw, init_pin_val, length);

	err_code = tel_disable_sim_facility(handle, sec_data, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//  OPERATION REQUEST ENABLING PIN1 PART
#define PIN1_NORMAL "0000" //Sample PIN1 code
void enable_pin1()
{
	int request_id = 0;
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length];

	strcpy(init_pin_val, PIN1_NORMAL);

	TelSimFacilityPw_t sec_data;
	sec_data.lock_type = TAPI_SIM_PTYPE_PIN1;   // 0x00
	sec_data.pw_len = strlen(init_pin_val);
	printf("pw_len[%d]", sec_data.pw_len);

	sec_data.pw = (char*)malloc(length);
	memcpy(sec_data.pw, init_pin_val, length);

	err_code = tel_enable_sim_facility(handle, sec_data, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	//WAIT EVENT RESPONSE FROM HERE
}

//  OPERATION REQUEST DISABLING SIM LOCK PART
#define SIM_NORMAL "0000" //Sample SIM LOCK code
void disable_sim()
{
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length];

	strcpy(init_pin_val, SIM_NORMAL);

	TelSimFacilityPw_t sec_data;
	sec_data.lock_type = TAPI_SIM_PTYPE_SIM;   // 0x00
	sec_data.pw_len = strlen(init_pin_val);
	printf("pw_len[%d]", sec_data.pw_len);

	sec_data.pw = (char*)malloc(length);
	memcpy(sec_data.pw, init_pin_val, length);

	err_code = tel_disable_sim_facility(handle, sec_data, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	//WAIT EVENT RESPONSE FROM HERE
}


//  OPERATION REQUEST ENABLING SIM LOCK PART
#define SIM_NORMAL "0000" //Sample SIM LOCK code
void enable_sim()
{
	int request_id = 0;
	int err_code;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length];

	strcpy(init_pin_val, SIM_NORMAL);

	TelSimFacilityPw_t sec_data;
	sec_data.lock_type = TAPI_SIM_PTYPE_SIM;   // 0x00
	sec_data.pw_len = strlen(init_pin_val);
	printf("pw_len[%d]", sec_data.pw_len);

	sec_data.pw = (char*)malloc(length);
	memcpy(sec_data.pw, init_pin_val, length);

	err_code = tel_enable_sim_facility(handle, sec_data, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	//WAIT EVENT RESPONSE FROM HERE
}

@endcode

SAMPLE CODE: GET PIN1/PIN2/SIM LOCK STATUS
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//  OPERATION REQUEST GET PIN1/PIN2/SIM LOCK STATUS PART
void get_facility_status()
{
	int error_code;
	TelSimLockType_t type = TAPI_SIM_PTYPE_PIN1 // or TAPI_SIM_PTYPE_PIN2 or TAPI_SIM_PTYPE_SIM;

	err_code = tel_get_sim_facility(handle, type, callback, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	printf("*****************************************************");
}

void get_lock_status()
{
	int error_code;
	TelSimLockType_t type = TAPI_SIM_PTYPE_PIN1 // or TAPI_SIM_PTYPE_PIN2 or TAPI_SIM_PTYPE_SIM;

	err_code = tel_get_sim_lock_info(handle, type, callback, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	printf("*****************************************************");
}

@endcode
@}
@defgroup Use_Cases6_3 Personalisation Lock
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Personalisation Lock</h3>
These APIs are used to enable/disable and get the status information about personalisation of network, network subset, corporate, service provider personalisation.

@code
int tel_enable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);
int tel_disable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);
int tel_get_sim_facility(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE: GET PERSONALIZATION STATUS
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
//  OPERATION REQUEST GET NETWORK PERSONALIZATION PART
void get_net_pers()
{
	int err_code;
	TelSimLockType_t type = TAPI_SIM_LOCK_PN; // Set locktype for which facility should be disabled;

	err_code = tel_get_sim_facility(handle, type, on_resp_get_sim_facility, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_facility(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPinOperationResult_t sec_rt = result;
	TelSimFacilityInfo_t *fi = data;

	printf("sec_rt[%d]", sec_rt);
	printf("fi->type[%d]", fi->type);
	printf("fi->f_status[%d]", fi->f_status);
}
@endcode

SAMPLE CODE: ENABLE/DISABLE PERSONALIZATION
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
//  OPERATION REQUEST ENABLING NETWORK PERSONALIZATION PART
#define NET_ENCODE "54500112345678" //Sample Network Personalization code
void enable_net_pers()
{
	printf("Lock Personalisation MCC+MNC 5\n");
	printf("Plese input Network Lock CODE : length of MCC+MNC, MCC, MNC, NCK\n");
	printf("We need to use this for testing : length of MCC+MNC(5), MCC(450), MNC(01), NCK(12345678) => 54500112345678\n");

	int err_code;
	TelSimFacilityPw_t *fc_pw;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length] ;

	strcpy(init_pin_val, PIN1_NORMAL);

	fc_pw.lock_type = TAPI_SIM_LOCK_PN; // Set locktype for which facility should be disabled;
	fc_pw.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", fc_pw.pw_len);

	fc_pw.pw = (char*)malloc(length);
	 memcpy(fc_pw.pw,init_pin_val,length);

	err_code = tel_enable_sim_facility(handle, fc_pw, on_resp_sim_facility_op, user_data);

	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//  OPERATION REQUEST DISABLING NETWORK PERSONALIZATION PART
#define NET_DISCODE "12345678" //Sample Network Personalization code
void disable_net_pers()
{
	printf("de Personalisation key is 8 byte \n");
	printf("We need to use this for testing : 12345678\n");

	int err_code;
	TelSimFacilityPw_t *fc_pw;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length] ;

	strcpy(init_pin_val, PIN1_NORMAL);

	fc_pw.lock_type = TAPI_SIM_LOCK_PN; // Set locktype for which facility should be disabled;
	fc_pw.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", fc_pw.pw_len);

	fc_pw.pw = (char*)malloc(length);
	memcpy(fc_pw.pw,init_pin_val,length);

	err_code = tel_disable_sim_facility(handle, fc_pw, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_sim_facility_op(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPinOperationResult_t sec_rt = result;
	TelSimFacilityResult_t *f_rt = data;

	printf("sec_rt[%d]", sec_rt);
	printf("f_rt->type[%d]", f_rt->type);
	printf("f_rt->retry_count[%d]", f_rt->retry_count);
}

@endcode
@}
@defgroup Use_Cases6_4 FDN
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">FDN</h3>
These APIs are used to enable/disable FDN and to retrieve the current FDN status.

@code
int tel_enable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);
int tel_disable_sim_facility(TapiHandle *handle, TelSimFacilityPw_t *pw, tapi_response_cb callback, void *user_data);
int tel_get_sim_facility(TapiHandle *handle, TelSimLockType_t type, tapi_response_cb callback, void *user_data);

@endcode

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister

//  OPERATION REQUEST ENABLE FDN MODE PART
#define PIN2_NORMAL "0000" //Sample PIN2 code
void enable_fdn()
{
	int api_ret;
	TelSimFacilityPw_t *fc_pw;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length] ;

	strcpy(init_pin_val, PIN1_NORMAL);

	fc_pw.lock_type = TAPI_SIM_PTYPE_PIN2; // Set locktype for which facility should be disabled;
	fc_pw.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", fc_pw.pw_len);

	fc_pw.pw = (char*)malloc(length);
	memcpy(fc_pw.pw,init_pin_val,length);

	err_code = tel_enable_sim_facility(handle, fc_pw, on_resp_sim_facility_op, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT FOR EVENT FROM HERE
}


//  OPERATION REQUEST DISABLE FDN MODE PART
#define PIN2_NORMAL "0000" //Sample PIN2 code
void disable_fdn()
{
	int api_ret;
	TelSimFacilityPw_t *fc_pw;
	int length = TAPI_SIM_PIN_LENGTH+1;
	char init_pin_val[length] ;

	strcpy(init_pin_val, PIN1_NORMAL);

	fc_pw.lock_type = TAPI_SIM_PTYPE_PIN2; // Set locktype for which facility should be disabled;
	fc_pw.pw_len = strlen(init_pin_val);

	printf("pw_len[%d]", fc_pw.pw_len);

	fc_pw.pw = (char*)malloc(length);
	memcpy(fc_pw.pw,init_pin_val,length);

	err_code = tel_disable_sim_facility(handle, fc_pw, on_resp_sim_facility_op, user_data);

	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT FOR EVENT FROM HERE


	//RESPONSE PART
	//CALLBACK FUNCTION TO BE USED
	static void on_resp_disable_sim_facility(TapiHandle *handle, int result, void *data, void *user_data)
	{
		TelSimPinOperationResult_t sec_rt = result;
		TelSimFacilityResult_t *f_rt = data;

		printf("sec_rt[%d]", sec_rt);
		printf("f_rt->type[%d]", f_rt->type);
		printf("f_rt->retry_count[%d]", f_rt->retry_count);
	}

	//  OPERATION REQUEST GET FDN STATUS PART
	void get_fdn_status()
	{
		printf("Get FDN status");
		TelSimLockType_t type = TAPI_SIM_LOCK_SC; // Set locktype for which facility should be disabled;

		err_code = tel_get_sim_facility(handle, type, on_resp_get_sim_facility, user_data);

		err_code = tel_get_sim_facility(handle, type, on_resp_get_sim_facility, user_data);
		if (err_code == TAPI_API_SUCCESS)
		{
			if (fdn_status == 0)
			{
				printf("*************************");
				printf("FDN disabled ");
				printf("*************************");
			}
			else
			{
				printf("*************************");
				printf("FDN enabled");
				printf("*************************");
			}
		}
		else
		{
			printf("TAPI API FAIL: Error Code [0x%x]", err_code);
		}

	}
@endcode
@}
@defgroup Use_Cases6_5 IMSI Information
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">IMSI Information</h3>
This API retrieves the IMSI (International Mobile Subscriber Identity) information.

@code
int tel_get_sim_imsi(TelSimImsiInfo_t* imsi);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

void getimsiInfo()
{
	int err_code;
	TelSimImsiInfo_t sim_imsi_info;

	err_code = tel_get_sim_imsi(handle, &sim_imsi_info);
	if (err_code == TAPI_API_SUCCESS)
	{
		// printf("[SIM APP] IMSI [mcc,mnc,msin]= ");
		// printf(" [%s]",sim_imsi_info.szMcc);
		// printf(" [%s]",sim_imsi_info.szMnc);
		// printf(" [%s]",sim_imsi_info.szMsin);
	}
	else
	{
		// printf("Error Code [%x]\n", err_code);
	}
}
@endcode
@}
@defgroup Use_Cases6_6 ECC Information
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">ECC Information</h3>
This API retreieves the ECC (Emergency Call Codes) data.

@code
int tel_get_sim_ecc(TelSimEccData_t *ecc_data, int *ecc_count);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

void geteccinfo()
{
	int err_code;
	TelSimEccList_t ecc_info = {0}; // Get ECC list info and ecc_count
	err_code = tel_get_sim_ecc(handle, &ecc_info);

	printf("The Retrun Status is %d", err_code);

	printf(" ECC count [%d]\n", ecc_info.ecc_rec_count);
}

void get_uecc()
{
	int err_code;
	int i = 0;

	printf(" Get USIM ECC  ");

	TelSimEccList_t uecc_info = {{{0,}}};

	err_code = tel_get_sim_ecc(handle, &uecc_info);
	if (err_code == TAPI_API_SUCCESS)
	{
		printf("ECC count [%d]", uecc_info.uecc_rec_count );

		for (i=0; i<uecc_info.uecc_rec_count; i++)
		{
			printf("Loop(%d): ", i);
			printf(" ECC Used [%d]", uecc_info.UeccInfo[i].bUsed);
			printf(" ECC Len [%d]", uecc_info.UeccInfo[i].EccLen);

			if (NULL != uecc_info.UeccInfo[i].szEcc)
			{
				printf("ECC string [%s]", uecc_info.UeccInfo[i].szEcc);
			}
			else
			{
				printf("ECC string [null]");
			}

			printf("ECC alphaID [%s]",uecc_info.UeccInfo[i].szEccAlphaIdentifier);
		}
	}
	else
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
}
@endcode
@}
@defgroup Use_Cases6_7 Language Preference Information
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Language Preference Information</h3>
These APIs are used to get and set the language preference information stored in SIM.

@code
int tel_get_sim_language(TapiHandle *handle, tapi_response_cb callback, void *user_data);
int tel_set_sim_language(TapiHandle *handle, TelSimLanguagePreferenceCode_t language, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE: GET SIM LANGUAGE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

void getlanguageprefinfo()
{
	int err_code;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data

	err_code = tel_get_sim_language(handle, on_resp_getlanguage, user_data);
	printf("Error Code [%x]\n", err_code);

	for (i =0; i<li_info.LpCount; i++)
		printf(" LI[%d] --> Val  [%d]\n", i, li_info.Lp[i]);
}
@endcode

SAMPLE CODE: UPDATE SIM LANGUAGE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
//  OPERATION REQUEST UPDATE SIM LANGUAGE PART
void setlanguageprefinfo()
{
	int err_code;
	TelSimLanguagePreferenceCode_t language = 0x00; //init
	language = TAPI_SIM_LP_ENGLISH; //language value
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data
	err_code = tel_set_sim_language(handle, language, on_resp_setlanguage, user_data);

	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}


//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_getlanguage(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimLanguagePreferenceCode_t *language = data;
	TelSimAccessResult_t access_rt = result;

	printf("access rt[%d]", access_rt);
	printf("language[%d]", *language);
}
static void on_resp_setlanguage(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimAccessResult_t access_rt = result;

	printf("access_rt[%d]", access_rt);
}
@endcode
@}
@defgroup Use_Cases6_8 Getting Card Type
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Getting Card Type</h3>
This API is a synchronous API which gets the Card Type i.e. whether the SIM Card is a GSM SIM or a 3G SIM.

@code
int tel_get_sim_type(TelSimCardType_t *card_type);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

void getcardtype()
{
	int err_code;
	TelSimCardType_t cardInfo; //unkwon, sim(normally gsm), usim(normally umts)
	TapiHandle *handle;  // Handle given by tel_init()

	err_code = tel_get_sim_type(handle, &cardInfo);

	printf("card type is %d\n", cardInfo);
}
@endcode
@}
@defgroup Use_Cases6_9  Getting SIM Card Initialization Status
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Getting SIM Card Initialization Status</h3>
API is a synchronous API which gets the Card Init status and Identification.

@code
int tel_get_sim_init_info(TelSimCardStatus_t *sim_status, int *card_changed);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//  OPERATION REQUEST GET CARD INIT STATUS PART
void get_sim_init_status()
{
	int err_code = TAPI_API_SUCCESS;
	TelSimCardStatus_t status = 0x00;
	int b_card_changed = 0;
	TapiHandle *handle;  // Handle given by tel_init()

	// GET SIM INIT INFORMATION
	err_code = tel_get_sim_init_info(handle, &status, &b_card_changed);

	if (err_code == TAPI_API_SUCCESS)
	{
		printf("**********************************************");
		printf("CardStatus:[0x%x]",status);
		printf("b_card_changed[%d]\n",b_card_changed);
		printf("**********************************************");
	}
	else
	{
		printf("TAPI Fail: Error Code [%d]\n", err_code);
	}
}
@endcode
@}
@defgroup Use_Cases6_10 SIM ACCESS COMMANDS Interface
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">SIM ACCESS COMMANDS Interface</h3>
This API is used to handle SIM EF data directly according to sim access command (select-file info, read, update command). Use_Cases is defined in the 3GPP or ETSI SIM specifications.

@code
int tel_req_sim_access(const TelSimRSimReq_t *rsim_data, int *req_id);
@endcode

SAMPLE CODE: EF HANDLING ( SELECT-FILE INFO)
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
//  OPERATION REQUEST GET SIM FILE INFO PART
void get_sim_file_info()
{
	int err_code;
	void *user_data = NULL; // Set User data

	TelRSimReq_t rsim_data;
	rsim_data.file_id = TAPI_SIM_EFILE_SPN;      // rsim access : sim file id to access
	rsim_data.rsim_cmd = TAPI_SIM_GET_RESPONSE;  // rsim access : get response, read, update available

	err_code = tel_req_sim_access(handle, &rsim_data, user_data);
	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}
@endcode
@}
@defgroup Use_Cases6_11 SIM Mailbox EF management
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">SIM Mailbox EF management</h3>
These APIs are used to get and update the mailbox information stored in SIM.

@code
int tel_get_sim_mailbox_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);
int tel_set_sim_mailbox_info(TapiHandle *handle, TelSimMailBoxNumber_t *req_mb, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE: READ / UPDATE MAILBOX INFO
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister

void get_sim_mailbox()
{
	int err_code = 0;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data
	err_code = tel_get_sim_mailbox_info(handle, on_resp_get_sim_mailbox, user_data);
	if(err_code == TAPI_API_SUCCESS) {
		if(mbox.b_cphs) { //b_cphs means current SIM is for CPHS or not.
		  printf("Current SIM is CPHS");
		} else {
		  printf("Current SIM is not CPHS but 3GPP");
		}
	} else {
		printf("TAPI API FAIL: Error Code [0x%x]",err_code);
	}

}
//  OPERATION REQUEST UPDATE SIM MAILBOX INFO PART
void update_sim_mailbox()
{
	int err_code = 0;
	TelSimMailBoxNumber_t *req_mb; // Get SIM mail box number info
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data
	err_code = tel_set_sim_mailbox_info(handle, &req_mb, on_resp_set_sim_mailbox, user_data);

	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}

//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_mailbox(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimAccessResult_t access_rt = result;
	TelSimMailboxList_t *list = data;
	int i = 0;

	printf("access_rt[%d]", access_rt);
	printf("count[%d]", list->count);

	for (i = 0; i < list->count; i++) {
		printf("list->list[%d].b_cphs[%d]", i, list->list[i].b_cphs);
		printf("list->list[%d].rec_index[%d]", i, list->list[i].rec_index);
		printf("list->list[%d].profile_num[%d]", i, list->list[i].profile_num);
		printf("list->list[%d].mb_type[%d]", i, list->list[i].mb_type);
		printf("list->list[%d].alpha_id_max_len[%d]", i,
				list->list[i].alpha_id_max_len);
		printf("list->list[%d].alpha_id[%s]", i, list->list[i].alpha_id);
		printf("list->list[%d].ton[0x%x]", i, list->list[i].ton);
		printf("list->list[%d].npi[0x%x]", i, list->list[i].npi);
		printf("list->list[%d].num[%s]", i, list->list[i].num);
		printf("list->list[%d].cc_id[0x%x]", i, list->list[i].cc_id);
		printf("list->list[%d].ext1_id[0x%x]", i, list->list[i].ext1_id);
	}
}

static void on_resp_set_sim_mailbox(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimAccessResult_t access_rt = result;

	printf("access_rt[%d]", access_rt);
}
@endcode
@}
@defgroup Use_Cases6_12 SIM Indication Status EFs management
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">SIM Indication Status EFs management</h3>
These APIs are used to get and set the message indication status stored in SIM.

@code
int tel_get_sim_messagewaiting_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);
int tel_set_sim_messagewaiting_info(TapiHandle *handle, TelSimMessageWaitingReq_t *req_mw, tapi_response_cb callback, void *user_data);
@endcode

SAMPLE CODE:  READ / UPDATE INDICATION STATUS DATA
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister

//  OPERATION REQUEST READ SIM MESSAGE WAITING INDICATION STATUS INFO PART
void read_sim_mwis()
{
	int err_code = 0;
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data
	err_code = tel_get_sim_messagewaiting_info(handle, on_resp_get_sim_mwis, user_data);
	if(err_code == TAPI_API_SUCCESS) {
		if(mw_data.b_cphs) { //b_cphs means current SIM is for CPHS or not.
		  printf("Current SIM is CPHS");
		} else {
		  printf("Current SIM is not CPHS but 3GPP");
		}
	} else {
		printf("TAPI API FAIL: Error Code [0x%x]",err_code);
	}

}

//  OPERATION REQUEST UPDATE SIM MESSAGE WAITING INDICATION STATUS INFO PART
//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister

void update_sim_mwis()
{
	TelSimMessageWaiting_s mw_data;
	int err_code = 0;
	TelSimMessageWaitingReq_t *req_mw; // Get message waiting info
	TapiHandle *handle;  // Handle given by tel_init()
	tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	void *user_data; // Set User data
	err_code = tel_set_sim_messagewaiting_info(handle, &req_mw, on_resp_set_sim_mwis, user_data);

	if (err_code != TAPI_API_SUCCESS)
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
	// WAIT EVENT RESPONSE FROM HERE
}


//RESPONSE PART
//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_mwis(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimAccessResult_t access_rt = result;
	TelSimMessageWaitingResp_t *mw = data;
	int i = 0;

	printf("access_rt[%d]", access_rt);
	printf("mw->b_cphs[%d]", mw->b_cphs);

	if (mw->b_cphs) {
		printf("mw->cphs_mw.b_voice1[%d]", mw->cphs_mw.b_voice1);
		printf("mw->cphs_mw.b_voice2[%d]", mw->cphs_mw.b_voice2);
		printf("mw->cphs_mw.b_fax[%d]", mw->cphs_mw.b_fax);
		printf("mw->cphs_mw.b_data[%d]", mw->cphs_mw.b_data);
	}
	else {
		for (i = 0; i < mw->mw_list.profile_count; i++) {
			printf("mw->mw_list.mw[%d].rec_index[%d]", i,
					mw->mw_list.mw[i].rec_index);
			printf("mw->mw_list.mw[%d].indicator_status[0x%x]", i,
					mw->mw_list.mw[i].indicator_status);
			printf("mw->mw_list.mw[%d].voice_count[%d]", i,
					mw->mw_list.mw[i].voice_count);
			printf("mw->mw_list.mw[%d].fax_count[%d]", i,
					mw->mw_list.mw[i].fax_count);
			printf("mw->mw_list.mw[%d].email_count[%d]", i,
					mw->mw_list.mw[i].email_count);
			printf("mw->mw_list.mw[%d].other_count[%d]", i,
					mw->mw_list.mw[i].other_count);
			printf("mw->mw_list.mw[%d].video_count[%d]", i,
					mw->mw_list.mw[i].video_count);
		}
	}

}

static void on_resp_set_sim_mwis(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimAccessResult_t access_rt = result;
	printf("access_rt[%d]", access_rt);
}

@endcode
@}
@defgroup Use_Cases6_13 Phone Book
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Phone Book</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Telephony provides APIs for various phonebook related features such as getting SIM initialization status, supported phonebook types, first valid index, total records and used records in phonebook, phonebook entry information and reading, updating, deleting of SIM phonebook records.

@code
int tel_get_sim_pb_count(TapiHandle *handle, TelSimPbType_t pb_type, tapi_response_cb callback, void *user_data);
int tel_get_sim_pb_meta_info(TapiHandle *handle, TelSimPbType_t pb_type, tapi_response_cb callback, void *user_data);
int tel_get_sim_pb_usim_meta_info(TapiHandle *handle, tapi_response_cb callback, void *user_data);
int tel_read_sim_pb_record(TapiHandle *handle, TelSimPbType_t pb_type, unsigned short index, tapi_response_cb callback, void *user_data);
int tel_update_sim_pb_record(TapiHandle *handle, const TelSimPbRecord_t *req_data, tapi_response_cb callback, void *user_data);
int tel_delete_sim_pb_record(TapiHandle *handle, TelSimPbType_t pb_type, unsigned short index, tapi_response_cb callback, void *user_data);
int tel_get_sim_pb_init_info(TapiHandle *handle, int *init_completed, TelSimPbList_t *pb_list);
@endcode

SAMPLE CODE FOR GETTING STORAGE COUNT
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void getstoragecount()
{
	int ret_status;
	TelSimPbType_t StorageFileType = TAPI_SIM_PB_3GSIM;
	int pRequestId = 0;
	TapiHandle *handle;

	ret_status = tel_get_sim_pb_count(handle, StorageFileType, on_resp_get_sim_pb_count, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_pb_count (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;
	TelSimPbStorageInfo_t *ps = data;

	printf("on_pb_get_sim_pb_count received");
	printf("access_rt[%d]", access_rt);
	if (access_rt == TAPI_SIM_PB_SUCCESS) {
		if (ps->StorageFileType <= TAPI_SIM_PB_GAS) {
			printf("StorageFileType[%d][%s]",	ps->StorageFileType, dbg_pb_type_name[ps->StorageFileType]);
		} else {
			printf("StorageFileType[%d]", ps->StorageFileType);
		}
		printf("TotalRecordCount[%d]", ps->TotalRecordCount);
		printf("UsedRecordCount[%d]", ps->UsedRecordCount);
	}
}
@endcode

SAMPLE CODE TO GET PHONE BOOK ENTRY INFO
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
void getPBEntryInfo()
{
	int ret_status;
	TelSimPbType_t StorageFileType = TAPI_SIM_PB_FDN;
	int pRequestId = 0;
	TapiHandle *handle;

	ret_status = tel_get_sim_pb_meta_info (handle, StorageFileType, on_resp_get_sim_pb_meta_info, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf(successful\n);
	else
		printf(error=%d\n, ret_status);
	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_pb_meta_info(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;
	TelSimPbEntryInfo_t *pe = data;

	printf("on_pb_get_sim_pb_meta_info received");
	printf("access_rt[%d]", access_rt);
	if (access_rt == TAPI_SIM_PB_SUCCESS) {
		if (pe->StorageFileType <= TAPI_SIM_PB_GAS) {
			printf("StorageFileType[%d][%s]",	pe->StorageFileType, dbg_pb_type_name[pe->StorageFileType]);
		} else {
			printf("StorageFileType[%d]", pe->StorageFileType);
		}
		printf("PbIndexMin[%d]",pe->PbIndexMin);
		printf("PbIndexMax[%d]",pe->PbIndexMax);
		printf("PbNumLenMax[%d]",pe->PbNumLenMax);
		printf("PbTextLenMax[%d]",pe->PbTextLenMax);
		printf("PbUsedCount[%d]",pe->PbUsedCount);
	}

}
@endcode

SAMPLE CODE TO GET USIM ENTRY INFO AND CAPABILITY INFO
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENIONED IN Event Register and Deregister
void getPBCapabilityInfo()
{
	int ret_status;
	int pRequestId = 0;
	TapiHandle *handle;

	ret_status = tel_get_sim_pb_usim_meta_info(handle, on_resp_get_sim_pb_usim_meta_info, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf(successful\n);
	else
		printf(error=%d\n, ret_status);
	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_get_sim_pb_usim_meta_info(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;
	TelSimPbCapabilityInfo_t *capa = data;
	int i = 0;

	printf("on_pb_get_sim_pb_3g_meta_info received");
	printf("access_rt[%d]", access_rt);
	if (access_rt == TAPI_SIM_PB_SUCCESS) {
		for (i = 0; i < capa->FileTypeCount; i++) {
			if(capa->FileTypeInfo[i].field_type <=TAPI_PB_3G_PBC ) {
				printf("capa->FileTypeInfo[%d].field_type[%d][%s]", i, capa->FileTypeInfo[i].field_type, dbg_pb_adf_field_name[capa->FileTypeInfo[i].field_type]);
			} else {
				printf("capa->FileTypeInfo[%d].field_type[%d]", i, capa->FileTypeInfo[i].field_type);
			}
			printf("capa->FileTypeInfo[%d].index_max[%d]", i, capa->FileTypeInfo[i].index_max);
			printf("capa->FileTypeInfo[%d].text_max[%d]", i, capa->FileTypeInfo[i].text_max);
			printf("capa->FileTypeInfo[%d].used_count[%d]", i, capa->FileTypeInfo[i].used_count);
		}
	}

}
@endcode

SAMPLE CODE FOR READING RECORD
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void simreadrecord()
{
	int ret_status;
	TelSimPbType_t StorageFileType = TAPI_SIM_PB_FDN;
	unsigned short Index = 4;
	int pRequestId = 0;
	TapiHandle *handle;

	ret_status = tel_read_sim_pb_record (handle, StorageFileType,Index, on_resp_read_sim_pb_record, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf(successful\n);
	else
		printf(error=%d\n, ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void on_resp_read_sim_pb_record (TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;
	TelSimPbRecord_t *pr = data;

	printf("on_pb_read_sim_pb_record received");
	printf("access_rt[%d]", access_rt);
	if(access_rt == TAPI_SIM_PB_SUCCESS) {
		if( pr->phonebook_type <= TAPI_SIM_PB_GAS){
			printf("phonebook_type[%d][%s]", pr->phonebook_type, dbg_pb_type_name[pr->phonebook_type]);
		} else {
			printf("phonebook_type[%d]", pr->phonebook_type);
		}
		printf("index[%d]", pr->index);
		printf("next_index[%d]", pr->next_index);
		printf("name[%s]", pr->name);
		if(pr->dcs <= TAPI_SIM_TEXT_ENC_HEX) {
			printf("dcs[%d][%s]", pr->dcs, dbg_pb_dcs_name[pr->dcs]);
		} else {
			printf("dcs[%d]", pr->dcs);
		}
		printf("number[%s]", pr->number);

		if(pr->ton <= TAPI_SIM_TON_RESERVED_FOR_EXT) {
			printf("ton[%d][%s]", pr->ton, dbg_pb_ton_name[pr->ton]);
		} else {
			printf("ton[%d]", pr->ton);
		}

		if (pr->phonebook_type == TAPI_SIM_PB_3GSIM) {
			printf("anr1[%s]", pr->anr1);
			if(pr->anr1_ton <= TAPI_SIM_TON_RESERVED_FOR_EXT) {
				printf("anr1_ton[%d][%s]", pr->anr1_ton, dbg_pb_ton_name[pr->anr1_ton]);
			} else {
				printf("anr1_ton[%d]", pr->anr1_ton);
			}
			printf("anr2[%s]", pr->anr2);
			if(pr->anr2_ton <= TAPI_SIM_TON_RESERVED_FOR_EXT) {
				printf("anr2_ton[%d][%s]", pr->anr2_ton, dbg_pb_ton_name[pr->anr2_ton]);
			} else {
				printf("anr2_ton[%d]", pr->anr2_ton);
			}
			printf("anr3[%s]", pr->anr3);
			if(pr->anr3_ton <= TAPI_SIM_TON_RESERVED_FOR_EXT) {
				printf("anr3_ton[%d][%s]", pr->anr3_ton, dbg_pb_ton_name[pr->anr3_ton]);
			} else {
				printf("anr3_ton[%d]", pr->anr3_ton);
			}
			printf("email1[%s]", pr->email1);
			printf("email2[%s]", pr->email2);
			printf("email3[%s]", pr->email3);
			printf("email4[%s]", pr->email4);
			printf("group_index[%d]", pr->group_index);
			printf("pb_control[%d]", pr->pb_control);
		}
	}

}
@endcode

SAMPLE CODE FOR UPDATING RECORD
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void simupdaterecord()
{
	int ret_status;
	TelSimPbRecord_t pb_add;
	int pRequestId = 0;
	TapiHandle *handle;

	pb_add.StorageFileType = TAPI_SIM_PB_3GSIM;
	pb_add.Index  = 1;
	pb_add.NextIndex  = 0;

	ret_status = tel_update_sim_pb_record(handle, &pb_add, on_resp_update_sim_pb_record, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf(successful\n);
	else
		printf(error=%d\n, ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void on_resp_update_sim_pb_record(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;

	printf("on_pb_update_sim_pb_record received");
	printf("access_rt[%d]", access_rt);
}
@endcode

SAMPLE CODE FOR DELETING RECORD
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void contactdelete()
{
	int ret_status;
	TapiHandle *handle;
	TelSimPbType_t StorageFileType = TAPI_SIM_PB_3GSIM;
	unsigned short RecordIndex = 1;
	int pRequestId = 0;

	ret_status = tel_delete_sim_pb_record (handle, StorageFileType, RecordIndex, on_resp_delete_sim_pb_record, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf(successful\n);
	else
		printf(error=%d\n, ret_status);
	//WAIT FOR EVENT HERE
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_delete_sim_pb_record(TapiHandle *handle, int result, void *data, void *user_data)
{
	TelSimPbAccessResult_t access_rt = result;

	printf("on_pb_delete_sim_pb_record received");
	printf("access_rt[%d]", access_rt);

}
@endcode

SAMPLE CODE FOR GETTING PHONEBOOK INIT INFO
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//  OPERATION REQUEST GET SIM PHONEBOOK INIT STATUS PART
void get_sim_phonebook_init_status()
{
	TapiHandle *handle;
	TelSimPbList_t pb_list;
	int pPbInitCompleted = 0;

	err_code = tel_get_sim_pb_init_info(handle, &pPbInitCompleted, &pb_list);
	if (err_code == TAPI_API_SUCCESS)
	{
		if (pPbInitCompleted == 0)
		{
			printf(" SIM PB INIT NOT completed ");
		}
		else
		{
			printf("SIM PB INIT completed");
			// if no sim records at all then valid_index = 0xFF
			printf ("ADN First index is [%d]",valid_index);
			printf ("SIM phone book storage list Information ");
			printf ("********************************************");
			printf ("pb_list.b_fdn[%d]",pb_list.b_fdn);
			printf ("pb_list.b_msisdn[%d]",pb_list.b_msisdn);
			printf ("pb_list.b_adn[%d]",pb_list.b_adn);
			printf ("pb_list.b_sdn[%d]",pb_list.b_sdn);
			printf ("pb_list.b_3g[%d]",pb_list.b_3g);
			printf ("pb_list.b_aas[%d]",pb_list.b_aas);
			printf ("pb_list.b_gas[%d]",pb_list.b_gas);
		}
	}
	else
	{
		printf("TAPI API FAIL: Error Code [0x%x]", err_code);
	}
}
@endcode
@}
@defgroup Use_Cases6_14 Getting 3G Phone Book Information
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">Getting 3G Phone Book Information</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Telephony provides APIs to retrieve SIM EFs supported by 3G phone , such as ANR, SNE, GRP, EMAIL etc and corresponding EFs max text length, number length and size.

@code
int tel_get_sim_pb_3g_meta_info(int *req_id);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void get3gcapainfo()
{
	int ret_status;
	int req_id = 0;

	ret_status = tel_get_sim_pb_3g_meta_info (&req_id);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId, i;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (eventType) {
		case TAPI_EVENT_SIM_PB_CAPABILITY_INFO_CNF:
			printf("[SIM APP]SIM PB Capability Info event status = [%x]\n", sim_event->Status);
			TelSimPbCapabilityInfo_t *sim_capability_info = (TelSimPbCapabilityInfo_t*)sim_event->pData;
			int i;
			for (i=0; i<sim_capability_info->FileTypeCount; i++)
			{
				printf(" [SIM APP]Filed tag type[%d]", sim_capability_info->FileTypeInfo[i].FileType3G);
				printf(" [SIM APP]max index [%d]\n", sim_capability_info->FileTypeInfo[i].PbIndexMax);
				printf(" [SIM APP]max text [%d]\n", sim_capability_info->FileTypeInfo[i].PbTextMax);
				printf(" [SIM APP]used count [%d]\n",  sim_capability_info->FileTypeInfo[i].TotalRecordCount);
			}
			break;
			//...
	}
}
@endcode

@}
@defgroup Use_Cases6_15 SAP (Sim access Profile) features
@ingroup Use_Cases6_SIM
@{

		<h3 class="pg">SAP (Sim access Profile) features</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

The SIM Access Profile defines the protocols and procedures that shall be used to access data and services of GSM SIM card, a UICC card or a R-UIM card via a Bluetooth link.

The SIM Access Profile specifies the following features:
- Connection Management
- Transfer APDU
- Transfer ATR
- Power SIM off/on
- Transfer Card Reader Status
- Set Transport Protocol

<h4>Connection Management:</h4>
An established SIM Access Profile connection is the prerequisite for all other features.
Telephony exposes APIs to make a connection request to SIM and to get connection status information.

@code
int tel_req_sap_connection( TelSimSapConnect_t *req_data, int *req_id);
int tel_req_sap_connection_status( int *req_id);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"
//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void sapconnectreq()
{
	int ret_status;
	TelSimSapConnect_t pConnectionReq;
	int pRequestId = 0;

	pConnectionReq.MsgId = TAPI_SIM_SAP_CONNECT_REQ;
	pConnectionReq.MaxMsgSize = 10; //temp for testing only - not clear

	ret_status = tel_req_sap_connection (&pConnectionReq, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (eventType)
	{
		case TAPI_SIM_EVENT_SAP_CONNECT_CNF:
			printf("TAPI_SIM_EVENT_SAP_CONNECT_CNF");
			break;
			//...
	}
}

//GET STATUS
void sapconnectstatusreq()
{
	int request_id = 0;
	int ret_status = tel_req_sap_connection_status (&request_id);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED

static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (eventType)
	{
		case TAPI_SIM_EVENT_SAP_CONNECT_STATUS_CNF:
			printf("TAPI_SIM_EVENT_SAP_CONNECT_STATUS_CNF");
			break;
			//...
	}
}
@endcode

<h4>Transfer APDU:</h4>
The ability to send APDUs (Application Protocol Data Units) over the Bluetooth link
@n Telephony provides API to transfer APDU to sim.

@code
int tel_req_sap_transfer_apdu(TelSimSapApduData_t *apdu_data, int *req_id);
@endcode

SAMPLE CODE:
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void saptransferapdu()
{
	int err_code;
	int file_id = TAPI_SIM_EFILE_ICCID;

	// for selecting EF ICCID
	TelSimSapApduData_t apdu_data;
	int pRequestId = 0;

	apdu_data.ApduLength = 7;
	apdu_data.Apdu[0] = 0xA0; // class
	apdu_data.Apdu[1] = 0xA4; // instruction
	apdu_data.Apdu[2] = 0; // p1 = parameter 1
	apdu_data.Apdu[3] = 0; // p2 = parameter 2
	apdu_data.Apdu[4] = 2; // p3 - parameter 3

	memcpy(&apdu_data.Apdu[5], &file_id, sizeof(unsigned short));
	err_code = tel_req_sap_transfer_apdu (&apdu_data, NULL);
	if (err_code == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", err_code);
}
//WAIT FOR EVENT HERE
//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (eventType)
	{
		case TAPI_SIM_EVENT_SAP_TRANSFER_APDU_CNF:
			printf("TAPI_SIM_EVENT_SAP_TRANSFER_APDU_CNF");
			break;
	}//...
}
@endcode

<h4>Transfer ATR:</h4>
The ability to send the content of the ATR (Answer to Reset) from the Server to the Client over the Bluetooth link. It contains information about the interface provided by the subscription module and the services on the GSM SIM, the UICC or the R-UIM.

@code
int tel_req_sap_transfer_atr( int *req_id);
@endcode

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void saptransferatrreq()
{
	int ret_status;
	int pRequestId = 0;

	ret_status = tel_req_sap_transfer_atr (&pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (eventType)
	{
		case TAPI_SIM_EVENT_SAP_TRANSFER_ATR_CNF:
			printf("TAPI_SIM_EVENT_SAP_TRANSFER_ATR_CNF");
			break;
			//...
	}
}
@endcode

<h4>Power sim on/off:</h4>
The ability to power the subscription module on/off remotely.

@code
int tel_req_sap_power_operation(TelSimSapMsgId_t req_data, int *req_id );
@endcode

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void sapsetpower()
{
	int ret_status;
	TelSimSapMsgId_t MsgId = TAPI_SIM_SAP_CONNECT_REQ;
	int pRequestId = 0;

	ret_status = tel_req_sap_power_operation (MsgId, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;


	switch (EventType)
	{
		case TAPI_SIM_EVENT_SAP_SET_SIM_POWER_CNF:
			printf("TAPI_SIM_EVENT_SAP_SET_SIM_POWER_CNF");
			break;
			//...
	}
}
@endcode

<h4>Transfer Card Reader Status:</h4>
The card reader status contains some basic information about the Card Reader and the subscription module (e.g. the size of the SIM or if the SIM is removable).

@code
int tel_req_sap_cardreader_status(int *req_id);
@endcode

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void simsapcardreaderstatus()
{
	int ret_status;
	int pRequestId = 0;

	ret_status = tel_req_sap_cardreader_status (&pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;


	switch (eventType)
	{
		case TAPI_SIM_EVENT_SAP_CARD_READER_STATUS_CNF:
			printf("TAPI_SIM_EVENT_SAP_CARD_READER_STATUS_CNF");
			break;
			//...
	}
}
@endcode

<h4>Set Transport Protocol:</h4>
The server shall reset the subscription module and switch to the desired protocol if supported by subscription module and Server.

@code
int tel_req_sap_transport_protocol(TelSimSapProtocol_t protocol, int *req_id);
@endcode

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void sapsettransportprotocol()
{
	int ret_status;
	TelSimSapProtocol_t Protocol = TAPI_SIM_SAP_PROTOCOL_T0;
	int pRequestId = 0;

	ret_status = tel_req_sap_transport_protocol (Protocol, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (EventType)
	{
		case TAPI_SIM_EVENT_SAP_SET_PROTOCOL_CNF:
			printf("TAPI_SIM_EVENT_SAP_SET_PROTOCOL_CNF");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases6_16 ISIM Features
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">ISIM Features</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

@code
int tel_req_sim_authentication( TelSimAuthenticationData_t *authentication_data, int *req_id);
@endcode

Application uses this API to send the ISIM authentication request to telephony.

SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister
void isimauthreq()
{
	int ret_status;
	TelSimAuthenticationData_t authenticationData;
	authenticationData.rand_length = 100;
	authenticationData.rand_length = 100;
	authenticationData.rand_data = "test data";
	authenticationData.autn_data = "test data";
	int pRequestId = 0;

	ret_status = tel_req_sim_authentication (&authenticationData, &pRequestId);
	if (ret_status == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
}
//WAIT FOR EVENT HERE

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (EventType)
	{
		case TAPI_EVENT_SIM_AUTHENTICATION_CNF:
			printf("TAPI_EVENT_SIM_AUTHENTICATION_CNF");
			break;
			//...
	}
}
@endcode
@}
@defgroup Use_Cases6_17 SIM NOTIFICATION MESSAGE
@ingroup Use_Cases6_SIM
@{


		<h3 class="pg">SIM NOTIFICATION MESSAGE </h3>
These are not APIs, but EVENTs from the low layer. User can receive the following events:
@code
TAPI_EVENT_SIM_STATUS_IND
TAPI_EVENT_SIM_FDN_STATUS_IND
@endcode

Application uses this event as follows.
SAMPLE CODE
@code
#include <ITapiSim.h>
#include <stdio.h>
#include "TapiCommon.h"

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

//CALLBACK FUNCTION TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	TelTapiEvent_t *sim_event = (TelTapiEvent_t*) event ;

	unsigned int temp_handle = -1;
	//...
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	switch (EventType)
	{
		case TAPI_EVENT_SIM_STATUS_IND:
			printf("***********TAPI_EVENT_SIM_STATUS_IND**************");

			if (status == TAPI_SIM_STATUS_CARD_ERROR)
			{
				printf("SIM CARD ERROR");
			}
			else if (status == TAPI_SIM_STATUS_CARD_NOT_PRESENT)
			{
				printf("SIM CARD NOT INSERTED");
			}
			else if (status == TAPI_SIM_STATUS_SIM_INITIALIZING)
			{
				printf("SIM INITITIALIZING");
			}
			else if (status == TAPI_SIM_STATUS_SIM_INIT_COMPLETED)
			{
				printf("SIM INIT COMPLETED");
			}
			else if (status == TAPI_SIM_STATUS_SIM_PIN_REQUIRED)
			{
				printf("SIM PIN REQUIRED");
			}
			else if (status == TAPI_SIM_STATUS_SIM_PUK_REQUIRED)
			{
				printf("SIM PUK REQUIRED");
			}
			else if (status == TAPI_SIM_STATUS_CARD_BLOCKED)
			{
				printf("SIM CARD BLOCKED");
			}
			printf("********************************************");
			break;

		case TAPI_EVENT_SIM_FDN_STATUS_IND:
			printf("*********TAPI_EVENT_SIM_FDN_STATUS_IND***********");
			printf("SIM FDN status event status = [0x%x]", status);
			printf("********************************************");
			break;
			//...
	}
}
@endcode
@}

	<h2 class="pg">SOUND</h2>
<strong>[Note] Telephony Emulator does not support this feature.</strong>
These APIs provide the interface for configuring sound related parameters.

@defgroup Use_Cases7_1 Event Register and Deregister
@ingroup Use_Cases7_SOUND
@{


		<h3 class="pg">Event Register and Deregister </h3>
To receive asynchronous event notifications for the Sound APIs, the registration of related events with their associated call backs is required. When an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

SAMPLE CODE:
@code
// REGISTER EVENT
unsigned int subscription_id = 0;
int api_err;

api_err = tel_init ();
if (api_err != TAPI_API_SUCCESS)
{
	TEST_DEBUG("tel_init Failed - api_err = %d \n", api_err);
}

api_err = tel_register_event (TAPI_EVENT_SOUND_VOLUMECTRL_CNF, &subscription_id, (TelAppCallback)&app_callback);
printf("VSOUND Event registration is Done: sub id is %d, api_err is %d\n",subscription_id,api_err);

tel_register_app_name("com.samsung.appname");

// DEREGISTER EVENT
api_err = tel_deregister_event (subscription_id);
if (api_err != TAPI_API_SUCCESS)
{
	printf("Event Class Deregestration Fail\n");
}
@endcode

The main features provided by the Sound APIs include setting the volume,voice path and user configuration such as minute alert,Service change,Connet tone, Disconnect Tone...etc.
@}
@defgroup Use_Cases7_2 Voice path control
@ingroup Use_Cases7_SOUND
@{


		<h3 class="pg">Voice path control</h3>
This API provides an interface for controlling voice path via application.

@code
int tel_set_sound_path (tapi_sound_audio_path_t  vc_path, int *pRequestId);
@endcode

<strong>This API is permitted for Samsung in-house applications only</strong>
@}
@defgroup Use_Cases7_3 Volume control
@ingroup Use_Cases7_SOUND
@{


		<h3 class="pg">Volume control</h3>
These APIs provide interfaces for controlling volume via application.

@code
int     tel_set_sound_volume_info (tapi_sound_volume_control_t vol_control, int *pRequestId);
int     tel_get_sound_volume_info (tapi_sound_volume_type_t vol_control, int *pRequestId);
@endcode

<strong>This API is permitted for Samsung in-house applications only</strong>
@}
@defgroup Use_Cases7_4 Mic mute control
@ingroup Use_Cases7_SOUND
@{


		<h3 class="pg">Mic mute control</h3>
This API provides an interface for mute/unmute mic via application.

@code
int  tel_set_sound_mute_status(tapi_sound_mic_mute_t micmute_set, int * pRequestId);
@endcode

<strong>This API is permitted for Samsung in-house applications only</strong>

SAMPLE CODE
@code
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSound.h>

//SUBSCRIBE FOR EVENTS AS MENTIONED IN Event Register and Deregister

//VOLUME CONTROL
void vol_controlset()
{
	int ret_val;
	int requestId = -1;
	tapi_sound_volume_control_t vol_control;

	vol_control.volume = TAPI_SOUND_VOLUME_LEVEL_3;
	vol_control.vol_type = TAPI_SOUND_VOL_VOICE;

	ret_val = tel_set_sound_volume_info(vol_control, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_val);
	//WAIT FOR EVENT HERE
}
void vol_controlget()
{
	int ret_val;
	int requestId = -1;
	api_sound_volume_type_t vol_type;
	vol_type = TAPI_SOUND_VOL_VOICE;

	ret_val = tel_get_sound_volume_info (vol_type, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_val);
	//WAIT FOR EVENT HERE
}

//VOICE PATH AND USER CONFIGURATION
void voicepathset()
{
	int ret_val;
	int requestId = -1;

	tapi_sound_audio_path_t vc_path;
	//VOICE PATH
	vc_path = TAPI_SOUND_HANDSET;

	ret_val = tel_set_sound_path (vc_path, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}


//USER CONFIGURATION
void usr_configset()
{
	int ret_val;
	Int requestId = -1;
	tapi_sound_user_sound_mask_t snd_mask;
	tapi_sound_user_sound_value_t snd_value;

	snd_mask = TAPI_SOUND_USER_MASK_ONE_MIN_ALERT;
	snd_value = TAPI_SOUND_ON;
	printf("tapi_sound_usr_configuration_set\n");
	ret_val = tapi_sound_usr_configuration_set(snd_mask,snd_value, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}

void usr_configget()
{
	int ret_val;
	tapi_sound_user_sound_mask_t snd_mask;

	snd_mask = TAPI_SOUND_USER_MASK_SERVICE_CHANGE_ALERT;
	printf("tel_get_sound_mute_status \n");
	ret_val = tel_get_sound_mute_status(snd_mask, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}

//MIC MUTE CONT\ROL
void micmute_controlset()
{
	int ret_val;
	tapi_sound_mic_mute_t set_micmute;

	set_micmute = TAPI_SOUND_MIC_MUTE;

	printf(" tel_set_sound_mute_status \n");
	ret_val = tel_set_sound_mute_status (set_micmute, &requestId);
	if (ret_val == TAPI_API_SUCCESS)
		printf("successful\n");
	else
		printf("error=%d\n", ret_status);
	//WAIT FOR EVENT HERE
}


//CALL BACK TO BE USED
static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	unsigned int temp_handle = -1;
	//
	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;

	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d]\n", eventClass, eventType , requestId, status );

	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}


	switch (eventClass)
	{
		case TAPI_EVENT_CLASS_SOUND:
			switch (eventType)
			{
				case TAPI_EVENT_SOUND_VOLUMECTRL_RSP :
					printf("***  TAPI_EVENT_SOUND_VOLUMECTRL_RSP received : %x ****\n", eventType);
					tapi_sound_volumn_ctrl_res vlm_ctrl_info;
					int index;

					memcpy(&vlm_ctrl_info, event->pData,
							sizeof(tapi_sound_volumn_ctrl_res));
					break;

				case TAPI_EVENT_SOUND_AUDIOPATHCTRL_NOTI:
					tapi_sound_audio_path_t AudioPath = 0;
					int OldSndOutPath = MM_SOUND_PATH_NONE;
					AudioPath = *((tapi_sound_audio_path_t *)(event->pData));
					printf("***  TAPI_EVENT_SOUND_AUDIOPATHCTRL_NOTI received : %x ****\n", eventType);
					break;

				case TAPI_EVENT_SOUND_AUDIOSOURCECTRL_NOTI:
					tapi_sound_audio_source_type_t *pAudioSrcCtrl = NULL;
					pAudioSrcCtrl = (tapi_sound_audio_source_type_t*)(event->pData);
					printf("***  TAPI_EVENT_SOUND_AUDIOSOURCECTRL_NOTI received : %x ****\n", eventType);
					break;

				case TAPI_EVENT_SOUND_ERROR_IND:
					tapi_phone_err_t errorCause;
					errorCause = *(( tapi_phone_err_t *)(event->pData));
					printf("***  TAPI_EVENT_SOUND_ERROR_IND received : %x ****\n", eventType);
					break;

				case TAPI_EVENT_SOUND_MICMUTECTRL_RSP:
					tapi_sound_mic_mute_t *mute_status = NULL;
					mute_status = (tapi_sound_audio_source_type_t*)(event->pData);

					printf("***  TAPI_EVENT_SOUND_MICMUTECTRL_RSP received : %x ****\n", eventType);
					break;

				default:
					printf("***  Default Event  %x ****\n", eventType);
					break;
			}
			//...
			break;

		default:
			printf("*** Other TAPI EVENT received : class : %x ****\n", eventClass);
			break;
	}
}
@endcode
@}


	<h2 class="pg">SAT (SIM Application Toolkit)</h2>
@defgroup Use_Cases8_1 Event register and deregister
@ingroup Use_Cases8_SAT
@{

		<h3 class="pg">Event register and deregister</h3>
To receive asynchronous event notifications for SAT APIs, the registration of related events with their associated call backs is required. When an asynchronous API is called, the confirmation is returned as an asynchronous event notification which invokes the callback function along with the event data.

SAMPLE CODE
@code
// REGISTER EVENT
unsigned int subscription_id = 0;
int api_err;
TapiHandle *handle;  // Handle given by tel_init()
char *noti_id; // Get Noti id
tapi_notification_cb callback; //Initialized call-back function pointer in which notification data is returned
void *user_data = NULL; // Set User data

api_err = tel_init();
if (api_err != TAPI_API_SUCCESS)
{
	TEST_DEBUG("tel_init Failed - api_err = %d \n", api_err);
}

api_err = tel_register_noti_event(handle, noti_id, on_noti_sat, user_data);
printf("SAT Event registration is Done: sub id is %d, api_err is %d\n",subscription_id,api_err);

tel_register_app_name("com.samsung.appname");

// DEREGISTER EVENT
api_err = tel_deregister_noti_event(handle, noti_id);
if (api_err != TAPI_API_SUCCESS)
{
	printf("Event Class Unregeration Fail\n");
}

api_err = tel_deinit();
if (api_err != TAPI_API_SUCCESS)
{
	printf("tel_deinit Fail\n");
}

static void on_noti_sat(TapiHandle *handle, const char *noti_id, void *data, void *user_data)
{
	//CALL BACK FUNTION TO BE CALLED
	switch (noti_id)
	{
		case TAPI_EVENT_SAT_DISPLAY_TEXT_IND:
			TelSatDisplayTextInd_t *event_data;
			event_data = (TelSatDisplayTextInd_t*)event->pData;
			break;
		case TAPI_EVENT_SAT_GET_INKEY_IND:
			TelSatGetInkeyIndInfo_t *event_data;
			event_data = (TelSatGetInkeyIndInfo_t *)event->pData;
			break;
		case TAPI_EVENT_SAT_GET_INPUT_IND:
			TelSatGetInputInd_t *event_data;
			event_data = (TelSatGetInputInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_PLAY_TONE_IND:
			TelSatPlayToneInd_t *event_data;
			event_data = (TelSatPlayToneInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_PLAY_TONE_IND:
			TelSatPlayToneInd_t *event_data;
			event_data = (TelSatPlayToneInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_REFRESH_IND:
			TelSatRefreshIndUiInfo_t *event_data;
			event_data = (TelSatRefreshIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SETUP_MENU_IND:
			TelSatSetupMenuInfo_t *event_data;
			event_data = (TelSatSetupMenuInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SETUP_MENU_IND:
			TelSatSetupMenuInfo_t *event_data;
			event_data = (TelSatSetupMenuInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SELECT_ITEM_IND:
			TelSatSelectItemInd_t *event_data;
			event_data = (TelSatSelectItemInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SEND_SMS_IND:
			TelSatSendSmsIndUiInfo_t *event_data;
			event_data = (TelSatSendSmsIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SEND_SS_IND:
			TelSatSendSsIndUiInfo_t *event_data;
			event_data = (TelSatSendSsIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SEND_USSD_IND:
			TelSatSendUssdIndUiInfo_t *event_data;
			event_data = (TelSatSendUssdIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SETUP_CALL_IND:
			TelSatSetupCallIndUiInfo_t *event_data;
			event_data = (TelSatSetupCallIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_PROVIDE_LOCAL_INFO_IND:
			TelSatProvideLocalInfoInd_t *event_data;
			event_data = (TelSatProvideLocalInfoInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SETUP_IDLE_MODE_TEXT_IND:
			TelSatSetupIdleModeTextInd_t *event_data;
			event_data = (TelSatSetupIdleModeTextInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_SEND_DTMF_IND:
			TelSatSendDtmfIndUiInfo_t *event_data;
			event_data = (TelSatSendDtmfIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_LANGUAGE_NOTIFICATION_IND:
			TelSatLanguageNotiInfoInd_t *event_data;
			event_data = (TelSatLanguageNotiInfoInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_UI_LAUNCH_BROWSER_IND:
			TelSatLaunchBrowserIndUiInfo_t *event_data;
			event_data = (TelSatLaunchBrowserIndUiInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_END_PROACTIVE_SESSION_IND:
			TelSatEndProactiveSessionIndInfo_t *event_data;
			event_data = (TelSatEndProactiveSessionIndInfo_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_MENU_SELECTION_CNF:
			TelSatEnvelopeResp_t *event_data;
			event_data = (TelSatEnvelopeResp_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_CALL_CONTROL_IND:
			TelSatCallCtrlIndData_t *event_data;
			event_data = (TelSatCallCtrlIndData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_MO_SMS_CONTROL_IND:
			TelSatMoSmCtrlIndData_t *event_data;
			event_data = (TelSatMoSmCtrlIndData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_EVENT_DOWNLOAD_CNF:
			TelSatEnvelopeResp_t *event_data;
			event_data = (TelSatEnvelopeResp_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SMS_REFRESH_IND:
		case TAPI_EVENT_SAT_PB_REFRESH_IND:
		case TAPI_EVENT_SAT_IDLE_REFRESH_IND:
			TelSatRefreshInd_t *event_data;
			event_data = (TelSatRefreshInd_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SEND_SMS_IND:
			TelSatSendSmsIndSmsData_t *event_data;
			event_data = (TelSatSendSmsIndSmsData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SETUP_CALL_IND:
			TelSatSetupCallIndCallData_t *event_data;
			event_data = (TelSatSetupCallIndCallData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SEND_SS_IND:
			TelSatSendSsIndSsData_t *event_data;
			event_data = (TelSatSendSsIndSsData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SEND_USSD_IND:
			TelSatSendUssdIndUssdData_t *event_data;
			event_data = (TelSatSendUssdIndUssdData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_SEND_DTMF_IND:
			TelSatSendDtmfIndDtmfData_t *event_data;
			event_data = (TelSatSendDtmfIndDtmfData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_LAUNCH_BROWSER_IND:
			TelSatLaunchBrowserIndBrowserData_t *event_data;
			event_data = (TelSatLaunchBrowserIndBrowserData_t *)event->pData;
			break;

		case TAPI_EVENT_SAT_END_OF_APP_EXEC_IND:
			TelSatProactiveCmdEndIndInfo_t *event_data;
			event_data = (TelSatProactiveCmdEndIndInfo_t *)event->pData;
			break;

		default:
			break;
	}
}
@endcode
@}
@defgroup Use_Cases8_2 Main Menu Information
@ingroup Use_Cases8_SAT
@{


		<h3 class="pg">Main Menu Information</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Telephony provides APIs for retreiving SAT Main Menu Information.

<strong>This API is permitted for Samsung in-house applications only</strong>

@code
int tel_get_sat_main_menu_info(TelSatSetupMenuInfo_t* pMainMenu)
@endcode

SAMPLE CODE:
@code
//SAT MAIN MENU INFORMATION
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>

void mainmenuinformation()
{
	int i = 0;
	int ReturnStatus;
	TapiHandle *handle;  // Handle given by tel_init()
	TelSatSetupMenuInfo_t SatMainMenuInfo;

	ReturnStatus = tel_get_sat_main_menu_info(handle, &SatMainMenuInfo);
	if (ReturnStatus == TAPI_API_SUCCESS)
	{
		printf(" SAT Main Menu Information \n");
		printf("Main Menu Title  :%s\n", satMainMenuInfo.satMainTitle);
		printf("Number of SAT Menu Items :%d\n", satMainMenuNum);
		printf("Sat Menu Items are:\n");
		for (i=0; i<SatMainMenuInfo.satMainMenuNum; i++)
			printf(" %s \n", SatMainMenuInfo.satMainMenuItem[i]);
	}
	else
		printf("ReturnStatus =%d\n", ReturnStatus);
}
@endcode
@}
@defgroup Use_Cases8_3 Envelope Commands
@ingroup Use_Cases8_SAT
@{


		<h3 class="pg">Envelope Commands</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

This API sends a USIM application toolkit command to the USIM, using the envelope mechanism of USIM application toolkit. (See GSM TS 31.111)

<strong>These APIs are permitted for Samsung in-house applications only</strong>

@code
int tel_select_sat_menu(TelSatMenuSelectionReqInfo_t* pMenuSelect, int* pRequestId);
int tel_download_sat_event(TelSatEventDownloadReqInfo_t*  pEventData, int* pRequestId);
@endcode

SAMPLE CODE:
@code
//MENU SELECTION ENVELOPE
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>

//Precondition
//SUBSCRIBE TO SAT EVENT(TAPI_EVENT_SAT_MENU_SELECTION_CNF) AS MENTIONED IN //Event Register and Deregister

void satmenuselectionenvelope()
{
	int ReturnStatus;
	TapiHandle *handle;  // Handle given by tel_init()
      tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	TelSatMenuSelectionReqInfo_t SatMenuSelect;
	void *user_data = NULL; // Set User data

	SatMenuSelect.itemIdentifier = 1;
	SatMenuSelect.bIsHelpRequested = FALSE;

	ReturnStatus = tel_select_sat_menu(handle, &SatMenuSelect, on_resp_sat_select_menu, user_data);
	if (ReturnStatus != TAPI_API_SUCCESS)
	{
		printf("ReturnStatus =%d\n", ReturnStatus);
	}
	else
	{
		//WAIT FOR TAPI_EVENT_SAT_MENU_SELECTION_CNF EVENT HERE
	}
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_sat_select_menu(TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("select menu item result(%d)", result);

}
@endcode

@code
//EVENT DOWNLOAD ENVELOPE
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>


//Precondition
//SUBSCRIBE TO SAT EVENT(TAPI_EVENT_SAT_EVENT_DOWNLOAD_CNF) AS MENTIONED IN //Event Register and Deregister
void eventdownloadenvelope()
{
	int ReturnStatus;
	TapiHandle *handle;  // Handle given by tel_init()
      tapi_response_cb callback; //Initialized call-back function pointer in which response is returned
	TelSatEventDownloadReqInfo_t SatEventData;
	void *user_data = NULL; // Set User data

	SatEventData.eventDownloadType = TAPI_EVENT_SAT_DW_TYPE_IDLE_SCREEN_AVAILABLE;

	SatEventData.u.bIdleScreenAvailable = TRUE;

	ReturnStatus = tel_download_sat_event(handle, &SatEventData, on_resp_sat_download_event, user_data);
	if (ReturnStatus != TAPI_API_SUCCESS)
	{
		printf("ReturnStatus =%d\n", ReturnStatus);
	}
	else
	{
		//WAIT FOR TAPI_EVENT_SAT_EVENT_DOWNLOAD_CNF EVENT HERE
	}
}

//CALLBACK FUNCTION TO BE USED
static void on_resp_sat_download_event(TapiHandle *handle, int result, void *data, void *user_data)
{
	printf("select menu item result(%d)", result);
}
@endcode
@}
@defgroup Use_Cases8_4 Application Execution result
@ingroup Use_Cases8_SAT
@{


		<h3 class="pg">Application Execution result</h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Telephony provides this API to get the Application execution result.

<strong>This API is permitted for Samsung in-house applications only</strong>

@code
Int tel_send_sat_app_exec_result(TelSatAppsRetInfo_t* pAppRetInfo);
@endcode

SAMPLE CODE:
@code
//SAT MAIN MENU TITLE
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>

void sendappexecutionresult()
{
	int ReturnStatus;
	TapiHandle *handle;  // Handle given by tel_init()
	TelSatAppsRetInfo_t SatAppRetInfo;

	SatAppRetInfo.commandType = TAPI_SAT_CMD_TYPE_SETUP_IDLE_MODE_TEXT;
	SatAppRetInfo.appsRet.setupIdleModeText.resp = TAPI_SAT_R_SUCCESS;

	ReturnStatus = tel_send_sat_app_exec_result(handle, &SatAppRetInfo);
	if (ReturnStatus == TAPI_API_SUCCESS)
	{
		printf(" Sending Application Execution Result Successful \n");
	}
	else
		printf("ReturnStatus =%d\n", ReturnStatus);
}
@endcode
@}
@defgroup Use_Cases8_5  UI /User Confirmation
@ingroup Use_Cases8_SAT
@{


		<h3 class="pg">UI /User Confirmation </h3>
<strong>[Note] Telephony Emulator does not support this feature.</strong>

Send user's confirmation message to the USIM application

<strong>These APIs are permitted for Samsung in-house applications only</strong>

@code
int tel_send_sat_ui_display_status(int commandId, TelSatUiDisplayStatusType_t status);
int tel_send_sat_ui_user_confirm(TelSatUiUserConfirmInfo_t * pUserConfirmData) ;
@endcode

SAMPLE CODE:
@code
//UI DISPLAY STATUS
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>

void senduidisplaystatus()
{
	int ReturnStatus;
	TapiHandle *handle;
	TelSatUiDisplayStatusType_t DisplatStatus;
	int CommandId;

	DisplatStatus = TAPI_SAT_DISPLAY_SUCCESS;
	CommandId = commandId; //Command Id of the Proactive Command

	ReturnStatus = tel_send_sat_ui_display_status(handle, CommandId, DisplayStatus);
	if (ReturnStatus == TAPI_API_SUCCESS)
		printf(" Sending UI Display Status Successful \n");
	else
		printf("ReturnStatus =%d\n", ReturnStatus);
}
@endcode

@code
//USER CONFIRMATION
#include <stdio.h>
#include <TapiCommon.h>
#include <ITapiSat.h>

void senduiuserconfirm()
{
	int ReturnStatus;
	TapiHandle *handle;  // Handle given by tel_init()
	TelSatUiUserConfirmInfo_t UserConfirmData;

	UserConfirmData.commandId = commandId ; //Command Id of the Proactive Command

	UserConfirmData.commandType = TAPI_SAT_CMD_TYPE_PLAY_TONE;
	UserConfirmData.keyType = TAPI_SAT_USER_CONFIRM_YES;

	UserConfirmData.pAdditionalData = NULL;
	UserConfirmData.dataLen = 0;

	ReturnStatus = tel_send_sat_ui_user_confirm(handle, &UserConfirmData);
	if (ReturnStatus == TAPI_API_SUCCESS)
		printf(" Sending User Confirmation Data Successful \n");
	else
		printf("ReturnStatus =%d\n", ReturnStatus);
}
@endcode
@}

@defgroup Appendixes1 Appendix A. Sample Codes
@ingroup Appendix
@{
<h1 class="pg">Appendixes</h1>
	<h2 class="pg">Appendix A. Sample Codes</h2>
Some reference sample code is attached to help the application developer understand the telephony Framework Module

How to use supplementary service APIs and handle SS events
@code
#include <ITapiSs.h>
#include <TapiEvent.h>
#include <TapiCommon.h>
#include <TelUtility.h>

GMainLoop *nw_context_loop = NULL;

typedef struct
{
	int group;
	int type;
	int len;
	void *dst;
} data_t;

static int SS_Callback(int eventClass, int eventType, void * param2)
{
	int i;
	printf ("\n\n\n SS_Callback is called! eventClass : %d\n, eventType : %d\n", eventClass, eventType);
	fflush(stdout);
	switch (eventType)
	{
		case TAPI_EVENT_SS_REL_COMP_MSG_NOTIFY:
			if (param2 != NULL) {
				int x = 0;
				TelSsRelCompMsgInfo_t rel_comp_msg;
				memcpy(&rel_comp_msg, (TelSsRelCompMsgInfo_t *)param2,
						sizeof(TelSsRelCompMsgInfo_t));
				printf("Printing the Release Complete Message \n");

				for (x=0; x<rel_comp_msg.RelCompMsgLen; x++)
				{
					printf("[%.2x]", rel_comp_msg.szRelCompMsg[x]);
				}
			}// end if
			break;

		case TAPI_EVENT_SS_WAITING_CNF:
			printf("####    Received Event : TAPI_EVENT_SS_WAITING_CNF  ##### \n");
			if (param2 == NULL) {
				printf("param2 is NULL\n");
			}
			else {
				TelSsInfo_t SsInfo;
				memcpy(&SsInfo, (TelSsInfo_t*)param2, sizeof(TelSsInfo_t));
				for (i=0; i<SsInfo.NumberOfRecords; i++)
				{
					printf("Number of records %d \n", SsInfo.NumberOfRecords);
					printf("Record:%d Status:%d Teleservice:%d \n",
							i,
							sInfo.SsRecord.WaitingRecord.rec_class[i].Status,
							SsInfo.SsRecord.WaitingRecord.rec_class[i].TeleCommService);
					if (SsInfo.SsRecord.WaitingRecord.rec_class[i].Status == TAPI_SS_STATUS_ACTIVE)
						printf("####    Status: Active      #### \n");
					else
						printf("####     Status: Not Active   #### \n");
				} //end for
			}//end else
			break;

		case TAPI_EVENT_SS_WAITING_QUERYSTATUS_CNF:
			printf("####    Received vent :TAPI_EVENT_SS_WAITING_QUERYSTATUS_CNF  ##### \n");
			if (param2 == NULL) {
				printf("\n paran 2 is NULL\n");
				break;
			}
			TelSsInfo_t SsInfo;
			memcpy(&SsInfo, (TelSsInfo_t*)param2, sizeof(TelSsInfo_t));
			for (i=0; i<SsInfo.NumberOfRecords; i++) {
				printf("Number of records %d \n",SsInfo.NumberOfRecords);
				printf("Record:%d Status:%d Teleservice:%d \n",
						i,
						SsInfo.SsRecord.WaitingRecord.rec_class[i].Status,
						SsInfo.SsRecord.WaitingRecord.rec_class[i].TeleCommService);

				if (SsInfo.SsRecord.WaitingRecord.rec_class[i].Status == TAPI_SS_STATUS_ACTIVE)
					printf("####    Status: Active      #### \n");
				else
					printf("####     Status: Not Active   #### \n");
			}//end for
			break;

		case TAPI_EVENT_SS_BARRING_QUERYSTATUS_CNF:
			printf("####    Received Event :TAPI_EVENT_SS_BARRING_QUERYSTATUS_CNF  ##### \n");
			break;

		case TAPI_EVENT_SS_BARRING_CNF:
			printf("####    Received Event :TAPI_EVENT_SS_BARRING_CNF   ##### \n");
			break;

		case TAPI_EVENT_SS_BARRING_CHANGEPASS_CNF:
			printf("####    Received Event : TAPI_EVENT_SS_BARRING_CHANGEPASS_CNF  ##### \n");
			printf("Call barring Password Changed successfully\n");
			break;

		case TAPI_EVENT_SS_FORWARD_CNF:
			printf("####    Received Event :TAPI_EVENT_SS_FORWARD_CNF  ##### \n");
			if (param2 != NULL) {
				TelSsInfo_t SsInfo;
				memset(&SsInfo, 0, sizeof(TelSsInfo_t));
				memcpy(&SsInfo, (TelSsInfo_t*)param2, sizeof(TelSsInfo_t));
				printf("Number of records %d \n", SsInfo.NumberOfRecords);
				for (i=0; i<SsInfo.NumberOfRecords; i++)
				{
					printf("Number of records %d\n", SsInfo.NumberOfRecords);
					printf("Record:%d Status:%d Teleservice:%d \n",
							i,
							SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status,
							SsInfo.SsRecord.ForwardingRecord.rec_class[i].TeleCommService);
					if (SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status == TAPI_SS_STATUS_REGISTERED)
						printf("####    Status: Registered      #### \n");
					else if (SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status == TAPI_SS_STATUS_ACTIVE)
						printf("####     Status: Active   #### \n");
					else
						printf("####    Status: Not Registered /Not Active     ####\n");
				}//end for
			}
			else
			{
				printf("param2 is NULL\n");
			}
			break;

		case TAPI_EVENT_SS_FORWARD_QUERYSTATUS_CNF:
			printf("####    Received Event : TAPI_EVENT_SS_FORWARD_QUERYSTATUS_CNF  ##### \n");
			if (param2 != NULL) {
				TelSsInfo_t SsInfo;
				memcpy(&SsInfo, (TelSsInfo_t*)param2, sizeof(TelSsInfo_t));
				for (i=0; i<SsInfo.NumberOfRecords; i++)
				{
					printf("Number of records %d \n", SsInfo.NumberOfRecords);
					printf("Record:%d Status:%d Teleservice:%d \n",
							i,
							SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status,
							SsInfo.SsRecord.ForwardingRecord.rec_class[i].TeleCommService);
					if (SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status == TAPI_SS_STATUS_REGISTERED)
						printf("####    Status: Registered      #### \n");
					else if (SsInfo.SsRecord.ForwardingRecord.rec_class[i].Status == TAPI_SS_STATUS_ACTIVE)
						printf("####     Status: Active   #### \n");
					else
						printf("####    Status: Not Registered /Not Active     #### \n");
				}//end for
			}//end if
			else
			{
				printf("param 2 is NULL\n");
			}
			break;

		case TAPI_EVENT_SS_CLI_QUERYSTATUS_CNF:
			printf("####    Received Event : TAPI_EVENT_SS_IDENTIFY_IND #### \n");
			if (param2 != NULL) {
				TelSsInfo_t SsInfo;
				memcpy(&SsInfo, (TelSsInfo_t*)param2, sizeof(TelSsInfo_t));
				printf("Status :%d   CLI Service : %d \n",
						SsInfo.SsRecord.CliRecord.CliStatus,
						SsInfo.SsRecord.CliRecord.IdentificationType);
				if (SsInfo.SsRecord.CliRecord.CliStatus == 1)
					printf(" #####    Status : Not Provisioned   #####\n");
				else if (SsInfo.SsRecord.CliRecord.CliStatus == 2)
					printf(" #####    Status :  Provisioned  but Deactivated #####\n");
				else if (SsInfo.SsRecord.CliRecord.CliStatus == 3)
					printf(" #####    Status : Provisioned  and Activated   #####\n");
				else if (SsInfo.SsRecord.CliRecord.CliStatus == 4)
					printf(" #####    Status : Unknown   #####\n");
				else if (SsInfo.SsRecord.CliRecord.CliStatus == 5)
					printf(" #####    Status : Temporarily Restricted  #####\n");
				else if (SsInfo.SsRecord.CliRecord.CliStatus == 6)
					printf(" #####    Status : Temporarily Allowed  #####\n");
			}
			else
			{
				printf("param 2 is NULL\n");
			}
			break;

		default:
			printf("\n\nDID NOT GET THE EVENT\n");
			break;
	}//end switch
	g_main_loop_quit(nw_context_loop);
	return 0;
}//end call back

static void app_callback (TelTapiEvent_t *event)
{
	int eventClass;
	int eventType;
	int requestId;
	int status;
	void* EventData = NULL;

	eventClass = event->EventClass;
	eventType = event->EventType;
	requestId = event->RequestId;
	status = event->Status;
	EventData = event->pData;
	//TEST_DEBUG("Class:[%d], Event Type:[%d], RequestId:[%d], Status:[%d] \n", eventClass, eventType , requestId, status );
	if (status != 0)
	{
		//TEST_DEBUG("******This is nonzero status. ******\n");
		return;
	}
	SS_Callback((int)eventClass, (int)eventType, EventData);
}

ss_test_subscribe_tapi_events()
{
	//REGISTER EVENT
	unsigned int subscription_id = 0;
	TapiResult_t api_err;

	api_err = TelTapiInit();
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("TelTapiInit Failed - api_err = %d \n", api_err);
	}
	api_err = TelTapiRegisterEvent(TAPI_EVENT_SS_WAITING_CNF, &subscription_id, (TelAppCallback)&app_callback);
	printf("SS Class registeration is Done: sub id is %d, api_err is %d\n",subscription_id,api_err);
	fflush(stdout);
}

noti_finish()
{
	//DEREGISTER EVENT
	unsigned int subscription_id = 0;
	TapiResult_t api_err;

	api_err = tel_deregister_event(subscription_id);
	if (api_err != TAPI_API_SUCCESS)
	{
		printf("Event Class Unregeration Fail\n");
	}
}

tapi_ss_call_barr()
{
	TapiResult_t ret_status;
	TelSsCallBarringInfo_t pBarringInfo;
	int pRequestId = 0;
	char *bar_pwd = "0000";

	printf("Before copying ,,,length is %d\n", strlen(pBarringInfo.szPassword));
	printf("len initially is %d\n", strlen(bar_pwd));

	pBarringInfo.Mode = TAPI_SS_CALL_BAR_ACTIVATE;
	pBarringInfo.Type = TAPI_CALL_BARRING_ALL_OUTGOING_CALLS;//TAPI_CALL_BARRING_ALL_OUTGOING_INTERN_CALL;
	pBarringInfo.CallType = TAPI_CALL_TYPE_VOICE_EV;
	strcpy(pBarringInfo.szPassword, bar_pwd);
	printf("length is %d\n", strlen(pBarringInfo.szPassword));
	ret_status = tel_set_ss_barring(&pBarringInfo, &pRequestId);
	if (ret_status != TAPI_API_SUCCESS) {
		return;
	}

	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);


	//now , get the status
	TelSsCallBarType_t BarType = TAPI_CALL_BARRING_ALL_OUTGOING_INTERN_CALL;
	TelSsCallType_t CallType = TAPI_CALL_TYPE_VOICE_EV;
	ret_status = tel_get_ss_barring_status(BarType,CallType, &pRequestId);
	if (ret_status != TAPI_API_SUCCESS) {
		return ;
	}

	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);
}

tapi_ss_call_fwd()
{
	TapiResult_t ret_status;
	TelSsForwardInfo_t pForwardInfo;
	int len;
	int pRequestId = 0;
	char *cf_number = "9986529874";

	pForwardInfo.Mode = TAPI_CALL_FORWARD_MODE_ENABLE_EV;
	pForwardInfo.Type = TAPI_CS_FORWARD_TYPE_VOICE_EV;
	pForwardInfo.Condition = TAPI_SS_FORWARD_WHEN_UNCONDITIONAL_EV;
	pForwardInfo.NoReplyConditionTimer = 10;

	len = strlen(cf_number);
	printf("Length of CF number :%d \n", len);
	memcpy(&(pForwardInfo.szPhoneNumber), cf_number, len);
	ret_status = tel_set_ss_forward(&pForwardInfo, &pRequestId);
	if (ret_status != TAPI_API_SUCCESS) {
		return ;
	}

	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);

	//now , get call forward status
	TelSsForwardType_t Type = TAPI_CS_FORWARD_TYPE_VOICE_EV;
	TelSsForwardWhen_t Condition = TAPI_SS_FORWARD_WHEN_UNCONDITIONAL_EV;

	// Calling TAPI SS Call Frwd Query Req Status Api
	ret_status = tel_get_ss_forward_status(Type,Condition, &pRequestId);
	if (ret_status != TAPI_API_SUCCESS) {
		return ;
	}

	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);
}

tapi_ss_call_wait()
{
	//set and get call waiting
	TapiResult_t ret_status;
	TelSsWaitingInfo_t waitInfo;
	int RequestID;

	waitInfo.Mode = TAPI_SS_CW_ACTIVATE;
	waitInfo.CallType = TAPI_CALL_TYPE_VOICE_EV;

	//set call wait
	ret_status = tel_set_ss_waiting(&waitInfo, &RequestID);
	if (ret_status != TAPI_API_SUCCESS) {
		return;
	}

	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);

	sleep(4);

	//now get call wait
	TelSsCallType_t CallType = TAPI_CALL_TYPE_VOICE_EV;
	ret_status = tel_get_ss_waiting_status(CallType, &RequestID);
	if (ret_status != TAPI_API_SUCCESS) {
		return;
	}
	nw_context_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(nw_context_loop);
}

ss_test()
{
	ss_test_subscribe_tapi_events();
	tapi_ss_call_barr();
	tapi_ss_call_fwd();
	tapi_ss_call_wait();
	noti_finish();
}

int main(int argc, char *argv[])
{
	ss_test();
	return 0;
}
@endcode
@}
@defgroup Appendixes2 Appendix   B. Error Code
@ingroup Appendix
@{

	<h2 class="pg">Appendix B. Error Code</h2>
<table>
<tr><td>Error Num.</td>
<td>Error Code</td>
<td>Error Description</td></tr>
<tr><td>0</td>
<td>TAPI_API_SUCCESS</td>
<td>No Error occurred</td></tr>
<tr><td>-1</td>
<td>TAPI_API_INVALID_INPUT</td>
<td>Input values are not correct in TAPI Library</td></tr>
<tr><td>-2</td>
<td>TAPI_API_INVALID_PTR</td>
<td>invalid pointer</td></tr>
<tr><td>-3</td>
<td>TAPI_API_NOT_SUPPORTED</td>
<td>The feature corresponding to requested API is not supported. This may be due to market/network/vendor reasons such as the feature is not available in the network.</td></tr>
<tr><td>-4</td>
<td>TAPI_API_DEPRICATED </td>
<td>This API is deprecated and will be so in future also </td></tr>
<tr><td>-5</td>
<td>TAPI_API_SYSTEM_OUT_OF_MEM</td>
<td>Out of memory</td></tr>
<tr><td>-6</td>
<td>TAPI_API_SYSTEM_RPC_LINK_DOWN</td>
<td>RPC link down</td></tr>
<tr><td>-7</td>
<td>TAPI_API_SERVICE_NOT_READY          </td>
<td>Phone was powered on, but yet to receive the power up completed notification </td></tr>
<tr><td>-8</td>
<td>TAPI_API_SERVER_FAILURE</td>
<td>error occurred in Telephony server</td></tr>
<tr><td>-9</td>
<td>TAPI_API_OEM_PLUGIN_FAILURE</td>
<td>Plug-in layer failure</td></tr>
<tr><td>-10</td>
<td>TAPI_API_TRANSPORT_LAYER_FAILURE</td>
<td>Transport layer Failure</td></tr>
<tr><td>-11</td>
<td>TAPI_API_INVALID_DATA_LEN</td>
<td>Invalid data length</td></tr>
</table>
@}
*/
/**
* @defgroup  TELEPHONY
 @{
*	@defgroup Appendix Reference
*	@defgroup TELEPHONY_USECASES Use Cases
	@{
*		@defgroup Use_Cases1_COMMON COMMON
*		@defgroup Use_Cases2_CALL CALL
*		@defgroup Use_Cases3_SUPPLEMENTARY_SERVICE SUPPLEMENTARY_SERVICE
*		@defgroup Use_Cases4_SMS SMS
*		@defgroup Use_Cases5_NETWORK NETWORK_Registration_and_Configuration
*		@defgroup Use_Cases6_SIM SIM
*		@defgroup Use_Cases7_SOUND SOUND
*		@defgroup Use_Cases8_SAT SAT
	@}
 @}
*/
