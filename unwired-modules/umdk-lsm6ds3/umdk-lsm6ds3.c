/*
 * Copyright (C) 2016 Unwired Devices [info@unwds.com]
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup
 * @ingroup
 * @brief
 * @{
 * @file		umdk-lsm6ds3.c
 * @brief       umdk-lsm6ds3 module implementation
 * @author      Eugene Ponomarev
 */

#ifdef __cplusplus
extern "C" {
#endif

/* define is autogenerated, do not change */
#undef _UMDK_MID_
#define _UMDK_MID_ UNWDS_LSM6DS3_MODULE_ID

/* define is autogenerated, do not change */
#undef _UMDK_NAME_
#define _UMDK_NAME_ "lsm6ds3"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "periph/gpio.h"

#include "board.h"

#include "unwds-common.h"
#include "include/umdk-lsm6ds3.h"
#include "lsm6ds3.h"
#include "lsm6ds3_regs.h"

#include "thread.h"
#include "xtimer.h"

static uwnds_cb_t *callback;

static lsm6ds3_t lsm6ds3;

static kernel_pid_t acq_pid;
static msg_t acq_msg = {};
static xtimer_t acq_timer;

int acq_ths = 500;

lsm6ds3_data_t acc_max_value;

static void *acq_thread(void *arg) {
    msg_t msg;
    msg_t msg_queue[4];
    msg_init_queue(msg_queue, 4);

    puts("[umdk-" _UMDK_NAME_ "] Continuous acquisition thread started");

    while (1) {
        msg_receive(&msg);

        lsm6ds3_data_t acc_data = {};
        lsm6ds3_read_acc(&lsm6ds3, &acc_data);
        
        char buf[10];
        
        if (acc_data.acc_x > 0) {
            if (acc_data.acc_x > acc_max_value.acc_x) {
                acc_max_value.acc_x = acc_data.acc_x;
            } else {
                if ((acc_data.acc_x + acq_ths) < acc_max_value.acc_x) {
                    int_to_float_str(buf, acc_max_value.acc_x, 3);
                    printf("[umdk-" _UMDK_NAME_ "] Acceleration peak: X %s g\n", buf);
                    acc_max_value.acc_x = INT_MIN;
                }
            }
        }
        
        if (acc_data.acc_y > 0) {
            if (acc_data.acc_y > acc_max_value.acc_y) {
                acc_max_value.acc_y = acc_data.acc_y;
            } else {
                if ((acc_data.acc_y + acq_ths) < acc_max_value.acc_y) {
                    int_to_float_str(buf, acc_max_value.acc_y, 3);
                    printf("[umdk-" _UMDK_NAME_ "] Acceleration peak: Y %s g\n", buf);
                    acc_max_value.acc_y = INT_MIN;
                }
            }
        }
        
        if (acc_data.acc_z > 0) {
            if (acc_data.acc_z > acc_max_value.acc_z) {
                acc_max_value.acc_z = acc_data.acc_z;
            }
             else {
                if ((acc_data.acc_z + acq_ths) < acc_max_value.acc_z) {
                    int_to_float_str(buf, acc_max_value.acc_z, 3);
                    printf("[umdk-" _UMDK_NAME_ "] Acceleration peak: Z %s g\n", buf);
                    acc_max_value.acc_z = INT_MIN;
                }
            }
        }
        
        /* every 10 ms */
        xtimer_set_msg(&acq_timer, 10U * 1000U, &acq_msg, acq_pid);
    }
    return NULL;
}

int umdk_lsm6ds3_shell_cmd(int argc, char **argv) {
    if (argc == 1) {
        puts (_UMDK_NAME_ " get - get results now");
        puts (_UMDK_NAME_ " send - get and send results now");
        puts (_UMDK_NAME_ " start - continuous acquisition with peak detection");
        puts (_UMDK_NAME_ " stop - stop continuous acquisition");
        puts (_UMDK_NAME_ " rate <13|26|52|104|208|416|833|1660> - set sensor data rate");
        puts (_UMDK_NAME_ " ths <value> - accelerometer threshold for peak detection, mg");
        puts (_UMDK_NAME_ " filter <50|100|200|400> - anti-aliasing filter, Hz");
        return 0;
    }
    
    char *cmd = argv[1];
	
    if (strcmp(cmd, "get") == 0) {
        lsm6ds3_data_t acc_data = {};
        
        lsm6ds3_read_acc(&lsm6ds3, &acc_data);
        lsm6ds3_read_gyro(&lsm6ds3, &acc_data);
        
		uint16_t temp = lsm6ds3_read_temp(&lsm6ds3);

        char buf[3][10] = { };
        
        int_to_float_str(buf[0], acc_data.acc_x, 3);
        int_to_float_str(buf[1], acc_data.acc_y, 3);
        int_to_float_str(buf[2], acc_data.acc_z, 3);
        printf("[umdk-" _UMDK_NAME_ "] Accelerometer: X %s g, Y %s g, Z %s g\n", buf[0], buf[1], buf[2]);
        
        int_to_float_str(buf[0], acc_data.gyr_x, 3);
        int_to_float_str(buf[1], acc_data.gyr_x, 3);
        int_to_float_str(buf[2], acc_data.gyr_x, 3);
        printf("[umdk-" _UMDK_NAME_ "] Gyroscope: X %s dps, Y %s dps, Z %s dps\n", buf[0], buf[1], buf[2]);
        
        int_to_float_str(buf[0], temp, 3);
        printf("[umdk-" _UMDK_NAME_ "] Temperature: %s C\n", buf[0]);
    }
    
    if (strcmp(cmd, "send") == 0) {
        puts("[umdk-" _UMDK_NAME_ "] Not implemented yet");
    }
    
    if (strcmp(cmd, "start") == 0) {
        acc_max_value.acc_x = INT_MIN;
        acc_max_value.acc_y = INT_MIN;
        acc_max_value.acc_z = INT_MIN;
        
        acc_max_value.gyr_x = INT_MIN;
        acc_max_value.gyr_y = INT_MIN;
        acc_max_value.gyr_z = INT_MIN;
        
        xtimer_set_msg(&acq_timer, 10U * 1000U, &acq_msg, acq_pid);
    }
    
    if (strcmp(cmd, "stop") == 0) {
        xtimer_remove(&acq_timer);
    }
    
    if (strcmp(cmd, "ths") == 0) {
        acq_ths = atoi(argv[2]);
        printf("[umdk-" _UMDK_NAME_ "] Threshold set: %d mg\n", acq_ths);
    }
    
    if (strcmp(cmd, "filter") == 0) {
        int filter = atoi(argv[2]);
        switch (filter)
        {
            case 50:
                lsm6ds3.params.accel_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_50Hz;
                break;
            case 100:
                lsm6ds3.params.accel_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_100Hz;
                break;
            case 200:
                lsm6ds3.params.accel_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_200Hz;
                break;
            case 400:
                lsm6ds3.params.accel_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_400Hz;
                break;
            default:
                puts("[umdk-" _UMDK_NAME_ "] Invalid filter value");
        }
        if (lsm6ds3_init(&lsm6ds3) < 0) {
            puts("[umdk-" _UMDK_NAME_ "] LSM6DS3 initialization failed");
            return -1;
        } else {
            printf("[umdk-" _UMDK_NAME_ "] Filter value set: %d Hz\n", filter);
        }
    }
   
    if (strcmp(cmd, "rate") == 0) {
        int rate = atoi(argv[2]);
        switch (rate)
        {
            case 13:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_13Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_13Hz;
                break;
            case 26:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_26Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_26Hz;
                break;
            case 52:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_52Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_52Hz;
                break;
            case 104:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_104Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_104Hz;
                break;
            case 208:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_208Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_208Hz;
                break;
            case 416:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_416Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_416Hz;
                break;
            case 833:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_833Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_833Hz;
                break;
            case 1660:
                lsm6ds3.params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_1660Hz;
                lsm6ds3.params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_1660Hz;
                break;
            default:
                puts("[umdk-" _UMDK_NAME_ "] Invalid sample rate value");
        }
        if (lsm6ds3_init(&lsm6ds3) < 0) {
            puts("[umdk-" _UMDK_NAME_ "] LSM6DS3 initialization failed");
            return -1;
        } else {
            printf("[umdk-" _UMDK_NAME_ "] Sample rate set: %d Hz\n", rate);
        }
    }
    
    return 1;
}

void umdk_lsm6ds3_init(uint32_t *non_gpio_pin_map, uwnds_cb_t *event_callback)
{
    (void) non_gpio_pin_map;

    callback = event_callback;

    lsm6ds3_param_t lsm_params;
    lsm_params.i2c_addr = 0x6A;
    lsm_params.i2c = UMDK_LSM6DS3_I2C;

    /* Configure the default settings */
    lsm_params.gyro_enabled = true;
    lsm_params.gyro_range = LSM6DS3_ACC_GYRO_FS_G_500dps;
    lsm_params.gyro_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_1660Hz;
    lsm_params.gyro_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_400Hz;
    lsm_params.gyro_fifo_enabled = true;
    lsm_params.gyro_fifo_decimation = true;

    lsm_params.accel_enabled = true;
    lsm_params.accel_odr_off = true;
    lsm_params.accel_range = LSM6DS3_ACC_GYRO_FS_XL_16g;
    lsm_params.accel_sample_rate = LSM6DS3_ACC_GYRO_ODR_XL_1660Hz;
    lsm_params.accel_bandwidth = LSM6DS3_ACC_GYRO_BW_XL_400Hz;
    lsm_params.accel_fifo_enabled = true;
    lsm_params.accel_fifo_decimation = true;

    lsm_params.temp_enabled = true;

    lsm_params.comm_mode = 1;

    lsm_params.fifo_threshold = 3000;
    lsm_params.fifo_sample_rate = LSM6DS3_ACC_GYRO_ODR_FIFO_1600Hz;
    lsm_params.fifo_mode_word = 0;

    lsm6ds3.params = lsm_params;
    
    if (lsm6ds3_init(&lsm6ds3) < 0) {
        puts("[umdk-" _UMDK_NAME_ "] LSM6DS3 initialization failed");
        return;
    }
    
    char *stack = (char *) allocate_stack(UMDK_LSM6DS3_STACK_SIZE);
	if (!stack) {
		puts("[umdk-" _UMDK_NAME_ "] unable to allocate memory. Are too many modules enabled?");
		return;
	}
    acq_pid = thread_create(stack, UMDK_LSM6DS3_STACK_SIZE, THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                            acq_thread, NULL, "LSM6DS3 acquisition");
    
    unwds_add_shell_command(_UMDK_NAME_, "type '" _UMDK_NAME_ "' for commands list", umdk_lsm6ds3_shell_cmd);
}

bool umdk_lsm6ds3_cmd(module_data_t *cmd, module_data_t *reply)
{
	/* Check for empty command */
	if (cmd->length < 1)
		return false;

	umdk_lsm6ds3_cmd_t c = cmd->data[0];

	switch (c) {
	case UMDK_LSM6DS3_CMD_POLL:
	{
		lsm6ds3_data_t acc_data = {};
        lsm6ds3_read_acc(&lsm6ds3, &acc_data);
        lsm6ds3_read_gyro(&lsm6ds3, &acc_data);
		uint16_t temp = lsm6ds3_read_temp(&lsm6ds3);
		
		reply->length = 1 + sizeof(lsm6ds3_data_t) + 2;
		reply->data[0] = _UMDK_MID_;
		
		memcpy(reply->data + 1, &acc_data, sizeof(lsm6ds3_data_t));
		memcpy(reply->data + 1 + sizeof(lsm6ds3_data_t), &temp, 2);
		
		break;
	}
	default:
		return false;
	}
	
    return true;
}

#ifdef __cplusplus
}
#endif
