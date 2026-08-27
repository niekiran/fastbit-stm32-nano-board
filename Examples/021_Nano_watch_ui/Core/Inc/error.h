/*
 * error.h
 *
 *  Created on: Mar 13, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */

#ifndef INC_ERROR_H_
#define INC_ERROR_H_

typedef enum {
    ERR_OK = 0,
    ERR_INVALID_PARAM,
    ERR_TIMEOUT,
    ERR_HW_FAILURE
} err_t;


#endif /* INC_ERROR_H_ */
