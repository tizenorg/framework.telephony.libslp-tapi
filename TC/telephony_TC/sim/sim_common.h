/*
 * libslp-tapi
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Kyeongchul Kim <kyeongchul.kim@samsung.com>
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


#ifndef _SIM_COMMON_H
#define _SIM_COMMON_H

#include <stdio.h>
#include <glib.h>

#define SIM_INFO "sim_pw.txt"

#define PIN1_INVALID "999"
#define PIN2_INVALID "999"

typedef struct {
	char pin1[5];
	char pin2[5];
	char puk1[9];
	char puk2[9];
	char wpin1[5];
	char wpin2[5];
	char wpuk1[9];
	char wpuk2[9];
}sim_info_t;

#endif
