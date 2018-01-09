/*
 *  sign.h
 *  operation by bit Twiddling.
 *  http://graphics.stanford.edu/~seander/bithacks.html#OperationCounting
 *  zhangwenkai, 2018.1.9.
 */

#ifndef _ZWK_BIT_TWIDDLE_H_
#define _ZWK_BIT_TWIDDLE_H_

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

/* v = 0 if v >= 0, else -1 */
#define Z_N_SIGN_OF_INTEGER(v)             ((v) >> (sizeof(int) * CHAR_BIT - 1))
#define Z_N_SIGN_OF_INTEGER_PORTABLE(v)    (-(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1)))

/* v= 0 if v >= 0, else x */
#define Z_X_SIGN_OF_INTEGER(v, x)          ((x) & Z_N_SIGN_OF_INTEGER(v))

/* v = 1 if v >= 0, else -1 */
#define P_N_SIGN_OF_INTEGER(v)             (1 | Z_N_SIGN_OF_INTEGER(v))
#define P_N_SIGN_OF_INTEGER_PORTABLE(v)    (1 | Z_N_SIGN_OF_INTEGER_PORTABLE(v))

/* v = 1 if v > 0, v = -1 if v < 0, else 0 */
#define P_Z_N_SIGN_OF_INTEGER(v)           (((v) != 0) | Z_N_SIGN_OF_INTEGER(v))
#define P_Z_N_SIGN_OF_INTEGER_PORTABLE(v)  (((v) != 0) | Z_N_SIGN_OF_INTEGER_PORTABLE(v))

/* v = 1 if v >= 0, else v = 0 */
#define P_Z_SIGN_OF_INTEGER_PORTABLE(v)    (1 ^ ((unsigned int)(v) >> (sizeof(int) * CHAR_BIT - 1)))


/* |v| */
#define ABS_OF_INTEGER(v)                   (((v) + Z_N_SIGN_OF_INTEGER(v)) ^ Z_N_SIGN_OF_INTEGER(v))

/* min/max without branches prediction */
#define MIN_OF_INTEGER_WITHOUT_BRANCH_PREDICT(x, y) \
            (y + Z_X_SIGN_OF_INTEGER(x - y, x - y))
#define MAX_OF_INTEGER_WITHOUT_BRANCH_PREDICT(x, y) \
            (x - Z_X_SIGN_OF_INTEGER(x - y, x - y))

/* 2^x, include 0 */
#define INTEGER_IS_POWER_OF_TWO(v)           ((v) & ((v) -1))
#endif /* _ZWK_BIT_TWIDDLE_H_ */