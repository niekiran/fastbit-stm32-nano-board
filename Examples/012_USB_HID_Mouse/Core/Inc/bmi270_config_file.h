/*
 * bmi270_config_file.h
 *
 *  Mandatory BMI270 initialization data, uploaded once at bmi270_init().
 *  Source: Bosch Sensortec official BMI270 Sensor API (bmi270.c).
 */

#ifndef INC_BMI270_CONFIG_FILE_H_
#define INC_BMI270_CONFIG_FILE_H_

#include <stdint.h>

#define BMI270_CONFIG_FILE_SIZE 8192U

extern const uint8_t bmi270_config_file[BMI270_CONFIG_FILE_SIZE];

#endif /* INC_BMI270_CONFIG_FILE_H_ */
