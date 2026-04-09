#ifndef __LSM6DSR_h
#define __LSM6DSR_h

#include "stdint.h"
#include "rtio.h"
#include "sensor.h"

#define LSM6DSR_ID                           0x6BU

#define LSM6DSR_FUNC_CFG_ACCESS              0x01U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t reg_access               : 2; /* shub_reg_access + func_cfg_access */
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t reg_access               : 2; /* shub_reg_access + func_cfg_access */
  uint8_t not_used_01              : 6;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_func_cfg_access_t;

#define LSM6DSR_PIN_CTRL                     0x02U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t sdo_pu_en                : 1;
  uint8_t ois_pu_dis               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ois_pu_dis               : 1;
  uint8_t sdo_pu_en                : 1;
  uint8_t not_used_01              : 6;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_pin_ctrl_t;

#define LSM6DSR_S4S_TPH_L                    0x04U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tph_l                    : 7;
  uint8_t tph_h_sel                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tph_h_sel                : 1;
  uint8_t tph_l                    : 7;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_s4s_tph_l_t;

#define LSM6DSR_S4S_TPH_H                    0x05U
typedef struct
{
  uint8_t tph_h                    : 8;
} lsm6dsr_s4s_tph_h_t;

#define LSM6DSR_S4S_RR                       0x06U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rr                       : 2;
  uint8_t not_used_01              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t rr                       : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_s4s_rr_t;

#define LSM6DSR_FIFO_CTRL1                   0x07U
typedef struct
{
  uint8_t wtm                      : 8;
} lsm6dsr_fifo_ctrl1_t;

#define LSM6DSR_FIFO_CTRL2                   0x08U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wtm                      : 1;
  uint8_t uncoptr_rate             : 2;
  uint8_t not_used_01              : 1;
  uint8_t odrchg_en                : 1;
  uint8_t not_used_02              : 1;
  uint8_t fifo_compr_rt_en         : 1;
  uint8_t stop_on_wtm              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t stop_on_wtm              : 1;
  uint8_t fifo_compr_rt_en         : 1;
  uint8_t not_used_02              : 1;
  uint8_t odrchg_en                : 1;
  uint8_t not_used_01              : 1;
  uint8_t uncoptr_rate             : 2;
  uint8_t wtm                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fifo_ctrl2_t;

#define LSM6DSR_FIFO_CTRL3                   0x09U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bdr_xl                   : 4;
  uint8_t bdr_gy                   : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bdr_gy                   : 4;
  uint8_t bdr_xl                   : 4;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fifo_ctrl3_t;

#define LSM6DSR_FIFO_CTRL4                   0x0AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fifo_mode                : 3;
  uint8_t not_used_01              : 1;
  uint8_t odr_t_batch              : 2;
  uint8_t dec_ts_batch             : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t dec_ts_batch             : 2;
  uint8_t odr_t_batch              : 2;
  uint8_t not_used_01              : 1;
  uint8_t fifo_mode                : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fifo_ctrl4_t;

#define LSM6DSR_COUNTER_BDR_REG1             0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t cnt_bdr_th               : 3;
  uint8_t not_used_01              : 2;
  uint8_t trig_counter_bdr         : 1;
  uint8_t rst_counter_bdr          : 1;
  uint8_t dataready_pulsed         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t dataready_pulsed         : 1;
  uint8_t rst_counter_bdr          : 1;
  uint8_t trig_counter_bdr         : 1;
  uint8_t not_used_01              : 2;
  uint8_t cnt_bdr_th               : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_counter_bdr_reg1_t;

#define LSM6DSR_COUNTER_BDR_REG2             0x0CU
typedef struct
{
  uint8_t cnt_bdr_th               : 8;
} lsm6dsr_counter_bdr_reg2_t;

#define LSM6DSR_INT1_CTRL                    0x0DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_drdy_xl             : 1;
  uint8_t int1_drdy_g              : 1;
  uint8_t int1_boot                : 1;
  uint8_t int1_fifo_th             : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_fifo_full           : 1;
  uint8_t int1_cnt_bdr             : 1;
  uint8_t den_drdy_flag            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_drdy_flag            : 1;
  uint8_t int1_cnt_bdr             : 1;
  uint8_t int1_fifo_full           : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_fifo_th             : 1;
  uint8_t int1_boot                : 1;
  uint8_t int1_drdy_g              : 1;
  uint8_t int1_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_int1_ctrl_t;

#define LSM6DSR_INT2_CTRL                    0x0EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_drdy_xl             : 1;
  uint8_t int2_drdy_g              : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t int2_fifo_th             : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_fifo_full           : 1;
  uint8_t int2_cnt_bdr             : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t int2_cnt_bdr             : 1;
  uint8_t int2_fifo_full           : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_fifo_th             : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t int2_drdy_g              : 1;
  uint8_t int2_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_int2_ctrl_t;

#define LSM6DSR_WHO_AM_I                     0x0FU
#define LSM6DSR_CTRL1_XL                     0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t lpf2_xl_en               : 1;
  uint8_t fs_xl                    : 2;
  uint8_t odr_xl                   : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t odr_xl                   : 4;
  uint8_t fs_xl                    : 2;
  uint8_t lpf2_xl_en               : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl1_xl_t;

#define LSM6DSR_CTRL2_G                      0x11U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fs_g                     : 4; /* fs_4000 + fs_125 + fs_g */
  uint8_t odr_g                    : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t odr_g                    : 4;
  uint8_t fs_g                     : 4; /* fs_4000 + fs_125 + fs_g */
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl2_g_t;

#define LSM6DSR_CTRL3_C                      0x12U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sw_reset                 : 1;
  uint8_t not_used_01              : 1;
  uint8_t if_inc                   : 1;
  uint8_t sim                      : 1;
  uint8_t pp_od                    : 1;
  uint8_t h_lactive                : 1;
  uint8_t bdu                      : 1;
  uint8_t boot                     : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot                     : 1;
  uint8_t bdu                      : 1;
  uint8_t h_lactive                : 1;
  uint8_t pp_od                    : 1;
  uint8_t sim                      : 1;
  uint8_t if_inc                   : 1;
  uint8_t not_used_01              : 1;
  uint8_t sw_reset                 : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl3_c_t;

#define LSM6DSR_CTRL4_C                      0x13U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t i2c_disable              : 1;
  uint8_t drdy_mask                : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_on_int1             : 1;
  uint8_t sleep_g                  : 1;
  uint8_t not_used_03              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_03              : 1;
  uint8_t sleep_g                  : 1;
  uint8_t int2_on_int1             : 1;
  uint8_t not_used_02              : 1;
  uint8_t drdy_mask                : 1;
  uint8_t i2c_disable              : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl4_c_t;

#define LSM6DSR_CTRL5_C                      0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t st_xl                    : 2;
  uint8_t st_g                     : 2;
  uint8_t not_used_01              : 1;
  uint8_t rounding                 : 2;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t rounding                 : 2;
  uint8_t not_used_01              : 1;
  uint8_t st_g                     : 2;
  uint8_t st_xl                    : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl5_c_t;

#define LSM6DSR_CTRL6_C                      0x15U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ftype                    : 3;
  uint8_t usr_off_w                : 1;
  uint8_t xl_hm_mode               : 1;
  uint8_t den_mode                 : 3;   /* trig_en + lvl1_en + lvl2_en */
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_mode                 : 3;   /* trig_en + lvl1_en + lvl2_en */
  uint8_t xl_hm_mode               : 1;
  uint8_t usr_off_w                : 1;
  uint8_t ftype                    : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl6_c_t;

#define LSM6DSR_CTRL7_G                      0x16U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ois_on                   : 1;
  uint8_t usr_off_on_out           : 1;
  uint8_t ois_on_en                : 1;
  uint8_t not_used_01              : 1;
  uint8_t hpm_g                    : 2;
  uint8_t hp_en_g                  : 1;
  uint8_t g_hm_mode                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t g_hm_mode                : 1;
  uint8_t hp_en_g                  : 1;
  uint8_t hpm_g                    : 2;
  uint8_t not_used_01              : 1;
  uint8_t ois_on_en                : 1;
  uint8_t usr_off_on_out           : 1;
  uint8_t ois_on                   : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl7_g_t;

#define LSM6DSR_CTRL8_XL                     0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t low_pass_on_6d           : 1;
  uint8_t not_used_01              : 1;
  uint8_t hp_slope_xl_en           : 1;
  uint8_t fastsettl_mode_xl        : 1;
  uint8_t hp_ref_mode_xl           : 1;
  uint8_t hpcf_xl                  : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t hpcf_xl                  : 3;
  uint8_t hp_ref_mode_xl           : 1;
  uint8_t fastsettl_mode_xl        : 1;
  uint8_t hp_slope_xl_en           : 1;
  uint8_t not_used_01              : 1;
  uint8_t low_pass_on_6d           : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl8_xl_t;

#define LSM6DSR_CTRL9_XL                     0x18U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t i3c_disable              : 1;
  uint8_t den_lh                   : 1;
  uint8_t den_xl_g                 : 2;   /* den_xl_en + den_xl_g */
  uint8_t den_z                    : 1;
  uint8_t den_y                    : 1;
  uint8_t den_x                    : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_x                    : 1;
  uint8_t den_y                    : 1;
  uint8_t den_z                    : 1;
  uint8_t den_xl_g                 : 2;   /* den_xl_en + den_xl_g */
  uint8_t den_lh                   : 1;
  uint8_t i3c_disable              : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl9_xl_t;

#define LSM6DSR_CTRL10_C                     0x19U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t timestamp_en             : 1;
  uint8_t not_used_02              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 2;
  uint8_t timestamp_en             : 1;
  uint8_t not_used_01              : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl10_c_t;

#define LSM6DSR_ALL_INT_SRC                  0x1AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ff_ia                    : 1;
  uint8_t wu_ia                    : 1;
  uint8_t single_tap               : 1;
  uint8_t double_tap               : 1;
  uint8_t d6d_ia                   : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t not_used_01              : 1;
  uint8_t timestamp_endcount       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t timestamp_endcount       : 1;
  uint8_t not_used_01              : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t d6d_ia                   : 1;
  uint8_t double_tap               : 1;
  uint8_t single_tap               : 1;
  uint8_t wu_ia                    : 1;
  uint8_t ff_ia                    : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_all_int_src_t;

#define LSM6DSR_WAKE_UP_SRC                  0x1BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t z_wu                     : 1;
  uint8_t y_wu                     : 1;
  uint8_t x_wu                     : 1;
  uint8_t wu_ia                    : 1;
  uint8_t sleep_state              : 1;
  uint8_t ff_ia                    : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t ff_ia                    : 1;
  uint8_t sleep_state              : 1;
  uint8_t wu_ia                    : 1;
  uint8_t x_wu                     : 1;
  uint8_t y_wu                     : 1;
  uint8_t z_wu                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_wake_up_src_t;

#define LSM6DSR_TAP_SRC                      0x1CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t z_tap                    : 1;
  uint8_t y_tap                    : 1;
  uint8_t x_tap                    : 1;
  uint8_t tap_sign                 : 1;
  uint8_t double_tap               : 1;
  uint8_t single_tap               : 1;
  uint8_t tap_ia                   : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t tap_ia                   : 1;
  uint8_t single_tap               : 1;
  uint8_t double_tap               : 1;
  uint8_t tap_sign                 : 1;
  uint8_t x_tap                    : 1;
  uint8_t y_tap                    : 1;
  uint8_t z_tap                    : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_tap_src_t;

#define LSM6DSR_D6D_SRC                      0x1DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xl                       : 1;
  uint8_t xh                       : 1;
  uint8_t yl                       : 1;
  uint8_t yh                       : 1;
  uint8_t zl                       : 1;
  uint8_t zh                       : 1;
  uint8_t d6d_ia                   : 1;
  uint8_t den_drdy                 : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t den_drdy                 : 1;
  uint8_t d6d_ia                   : 1;
  uint8_t zh                       : 1;
  uint8_t zl                       : 1;
  uint8_t yh                       : 1;
  uint8_t yl                       : 1;
  uint8_t xh                       : 1;
  uint8_t xl                       : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_d6d_src_t;

#define LSM6DSR_STATUS_REG                   0x1EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlda                     : 1;
  uint8_t gda                      : 1;
  uint8_t tda                      : 1;
  uint8_t not_used_01              : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t tda                      : 1;
  uint8_t gda                      : 1;
  uint8_t xlda                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_status_reg_t;

#define LSM6DSR_STATUS_SPIAUX                0x1EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlda                     : 1;
  uint8_t gda                      : 1;
  uint8_t gyro_settling            : 1;
  uint8_t not_used_01              : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t gyro_settling            : 1;
  uint8_t gda                      : 1;
  uint8_t xlda                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_status_spiaux_t;

#define LSM6DSR_OUT_TEMP_L                   0x20U
#define LSM6DSR_OUT_TEMP_H                   0x21U
#define LSM6DSR_OUTX_L_G                     0x22U
#define LSM6DSR_OUTX_H_G                     0x23U
#define LSM6DSR_OUTY_L_G                     0x24U
#define LSM6DSR_OUTY_H_G                     0x25U
#define LSM6DSR_OUTZ_L_G                     0x26U
#define LSM6DSR_OUTZ_H_G                     0x27U
#define LSM6DSR_OUTX_L_A                     0x28U
#define LSM6DSR_OUTX_H_A                     0x29U
#define LSM6DSR_OUTY_L_A                     0x2AU
#define LSM6DSR_OUTY_H_A                     0x2BU
#define LSM6DSR_OUTZ_L_A                     0x2CU
#define LSM6DSR_OUTZ_H_A                     0x2DU

#define LSM6DSR_EMB_FUNC_STATUS_MAINPAGE     0x35U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01             : 3;
  uint8_t is_step_det             : 1;
  uint8_t is_tilt                 : 1;
  uint8_t is_sigmot               : 1;
  uint8_t not_used_02             : 1;
  uint8_t is_fsm_lc               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm_lc               : 1;
  uint8_t not_used_02             : 1;
  uint8_t is_sigmot               : 1;
  uint8_t is_tilt                 : 1;
  uint8_t is_step_det             : 1;
  uint8_t not_used_01             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_status_mainpage_t;

#define LSM6DSR_FSM_STATUS_A_MAINPAGE        0x36U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t is_fsm1                 : 1;
  uint8_t is_fsm2                 : 1;
  uint8_t is_fsm3                 : 1;
  uint8_t is_fsm4                 : 1;
  uint8_t is_fsm5                 : 1;
  uint8_t is_fsm6                 : 1;
  uint8_t is_fsm7                 : 1;
  uint8_t is_fsm8                 : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm8                 : 1;
  uint8_t is_fsm7                 : 1;
  uint8_t is_fsm6                 : 1;
  uint8_t is_fsm5                 : 1;
  uint8_t is_fsm4                 : 1;
  uint8_t is_fsm3                 : 1;
  uint8_t is_fsm2                 : 1;
  uint8_t is_fsm1                 : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_status_a_mainpage_t;

#define LSM6DSR_FSM_STATUS_B_MAINPAGE        0x37U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t is_fsm9                 : 1;
  uint8_t is_fsm10                : 1;
  uint8_t is_fsm11                : 1;
  uint8_t is_fsm12                : 1;
  uint8_t is_fsm13                : 1;
  uint8_t is_fsm14                : 1;
  uint8_t is_fsm15                : 1;
  uint8_t is_fsm16                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm16                : 1;
  uint8_t is_fsm15                : 1;
  uint8_t is_fsm14                : 1;
  uint8_t is_fsm13                : 1;
  uint8_t is_fsm12                : 1;
  uint8_t is_fsm11                : 1;
  uint8_t is_fsm10                : 1;
  uint8_t is_fsm9                 : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_status_b_mainpage_t;

#define LSM6DSR_STATUS_MASTER_MAINPAGE       0x39U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sens_hub_endop          : 1;
  uint8_t not_used_01             : 2;
  uint8_t slave0_nack             : 1;
  uint8_t slave1_nack             : 1;
  uint8_t slave2_nack             : 1;
  uint8_t slave3_nack             : 1;
  uint8_t wr_once_done            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t wr_once_done            : 1;
  uint8_t slave3_nack             : 1;
  uint8_t slave2_nack             : 1;
  uint8_t slave1_nack             : 1;
  uint8_t slave0_nack             : 1;
  uint8_t not_used_01             : 2;
  uint8_t sens_hub_endop          : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_status_master_mainpage_t;

#define LSM6DSR_FIFO_STATUS1                 0x3AU
typedef struct
{
  uint8_t diff_fifo                : 8;
} lsm6dsr_fifo_status1_t;

#define LSM6DSR_FIFO_STATUS2                 0x3BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t diff_fifo                : 2;
  uint8_t not_used_01              : 1;
  uint8_t over_run_latched         : 1;
  uint8_t counter_bdr_ia           : 1;
  uint8_t fifo_full_ia             : 1;
  uint8_t fifo_ovr_ia              : 1;
  uint8_t fifo_wtm_ia              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fifo_wtm_ia              : 1;
  uint8_t fifo_ovr_ia              : 1;
  uint8_t fifo_full_ia             : 1;
  uint8_t counter_bdr_ia           : 1;
  uint8_t over_run_latched         : 1;
  uint8_t not_used_01              : 1;
  uint8_t diff_fifo                : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fifo_status2_t;

#define LSM6DSR_TIMESTAMP0                   0x40U
#define LSM6DSR_TIMESTAMP1                   0x41U
#define LSM6DSR_TIMESTAMP2                   0x42U
#define LSM6DSR_TIMESTAMP3                   0x43U
#define LSM6DSR_TAP_CFG0                     0x56U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lir                      : 1;
  uint8_t tap_z_en                 : 1;
  uint8_t tap_y_en                 : 1;
  uint8_t tap_x_en                 : 1;
  uint8_t slope_fds                : 1;
  uint8_t sleep_status_on_int      : 1;
  uint8_t int_clr_on_read          : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t int_clr_on_read          : 1;
  uint8_t sleep_status_on_int      : 1;
  uint8_t slope_fds                : 1;
  uint8_t tap_x_en                 : 1;
  uint8_t tap_y_en                 : 1;
  uint8_t tap_z_en                 : 1;
  uint8_t lir                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_tap_cfg0_t;

#define LSM6DSR_TAP_CFG1                     0x57U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tap_ths_x                : 5;
  uint8_t tap_priority             : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tap_priority             : 3;
  uint8_t tap_ths_x                : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_tap_cfg1_t;

#define LSM6DSR_TAP_CFG2                     0x58U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tap_ths_y                : 5;
  uint8_t inact_en                 : 2;
  uint8_t interrupts_enable        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t interrupts_enable        : 1;
  uint8_t inact_en                 : 2;
  uint8_t tap_ths_y                : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_tap_cfg2_t;

#define LSM6DSR_TAP_THS_6D                   0x59U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tap_ths_z                : 5;
  uint8_t sixd_ths                 : 2;
  uint8_t d4d_en                   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t d4d_en                   : 1;
  uint8_t sixd_ths                 : 2;
  uint8_t tap_ths_z                : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_tap_ths_6d_t;

#define LSM6DSR_INT_DUR2                     0x5AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t shock                    : 2;
  uint8_t quiet                    : 2;
  uint8_t dur                      : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t dur                      : 4;
  uint8_t quiet                    : 2;
  uint8_t shock                    : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_int_dur2_t;

#define LSM6DSR_WAKE_UP_THS                  0x5BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wk_ths                   : 6;
  uint8_t usr_off_on_wu            : 1;
  uint8_t single_double_tap        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t single_double_tap        : 1;
  uint8_t usr_off_on_wu            : 1;
  uint8_t wk_ths                   : 6;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_wake_up_ths_t;

#define LSM6DSR_WAKE_UP_DUR                  0x5CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sleep_dur                : 4;
  uint8_t wake_ths_w               : 1;
  uint8_t wake_dur                 : 2;
  uint8_t ff_dur                   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ff_dur                   : 1;
  uint8_t wake_dur                 : 2;
  uint8_t wake_ths_w               : 1;
  uint8_t sleep_dur                : 4;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_wake_up_dur_t;

#define LSM6DSR_FREE_FALL                    0x5DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ff_ths                   : 3;
  uint8_t ff_dur                   : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ff_dur                   : 5;
  uint8_t ff_ths                   : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_free_fall_t;

#define LSM6DSR_MD1_CFG                      0x5EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_shub                : 1;
  uint8_t int1_emb_func            : 1;
  uint8_t int1_6d                  : 1;
  uint8_t int1_double_tap          : 1;
  uint8_t int1_ff                  : 1;
  uint8_t int1_wu                  : 1;
  uint8_t int1_single_tap          : 1;
  uint8_t int1_sleep_change        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_sleep_change        : 1;
  uint8_t int1_single_tap          : 1;
  uint8_t int1_wu                  : 1;
  uint8_t int1_ff                  : 1;
  uint8_t int1_double_tap          : 1;
  uint8_t int1_6d                  : 1;
  uint8_t int1_emb_func            : 1;
  uint8_t int1_shub                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_md1_cfg_t;

#define LSM6DSR_MD2_CFG                      0x5FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_timestamp           : 1;
  uint8_t int2_emb_func            : 1;
  uint8_t int2_6d                  : 1;
  uint8_t int2_double_tap          : 1;
  uint8_t int2_ff                  : 1;
  uint8_t int2_wu                  : 1;
  uint8_t int2_single_tap          : 1;
  uint8_t int2_sleep_change        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_sleep_change        : 1;
  uint8_t int2_single_tap          : 1;
  uint8_t int2_wu                  : 1;
  uint8_t int2_ff                  : 1;
  uint8_t int2_double_tap          : 1;
  uint8_t int2_6d                  : 1;
  uint8_t int2_emb_func            : 1;
  uint8_t int2_timestamp           : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_md2_cfg_t;

#define LSM6DSR_S4S_ST_CMD_CODE              0x60U
typedef struct
{
  uint8_t s4s_st_cmd_code          : 8;
} lsm6dsr_s4s_st_cmd_code_t;

#define LSM6DSR_S4S_DT_REG                   0x61U
typedef struct
{
  uint8_t dt                       : 8;
} lsm6dsr_s4s_dt_reg_t;

#define LSM6DSR_I3C_BUS_AVB                  0x62U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t pd_dis_int1              : 1;
  uint8_t not_used_01              : 2;
  uint8_t i3c_bus_avb_sel          : 2;
  uint8_t not_used_02              : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 3;
  uint8_t i3c_bus_avb_sel          : 2;
  uint8_t not_used_01              : 2;
  uint8_t pd_dis_int1              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_i3c_bus_avb_t;

#define LSM6DSR_INTERNAL_FREQ_FINE           0x63U
typedef struct
{
  int8_t freq_fine                 : 8;
} lsm6dsr_internal_freq_fine_t;

#define LSM6DSR_INT_OIS                      0x6FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t st_xl_ois                : 2;
  uint8_t not_used_01              : 3;
  uint8_t den_lh_ois               : 1;
  uint8_t lvl2_ois                 : 1;
  uint8_t int2_drdy_ois            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_drdy_ois            : 1;
  uint8_t lvl2_ois                 : 1;
  uint8_t den_lh_ois               : 1;
  uint8_t not_used_01              : 3;
  uint8_t st_xl_ois                : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_int_ois_t;

#define LSM6DSR_CTRL1_OIS                    0x70U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ois_en_spi2              : 1;
  uint8_t fs_125_ois               : 1;
  uint8_t fs_g_ois                 : 2;
  uint8_t mode4_en                 : 1;
  uint8_t sim_ois                  : 1;
  uint8_t lvl1_ois                 : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t lvl1_ois                 : 1;
  uint8_t sim_ois                  : 1;
  uint8_t mode4_en                 : 1;
  uint8_t fs_g_ois                 : 2;
  uint8_t fs_125_ois               : 1;
  uint8_t ois_en_spi2              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl1_ois_t;

#define LSM6DSR_CTRL2_OIS                    0x71U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t hp_en_ois                : 1;
  uint8_t ftype_ois                : 2;
  uint8_t not_used_01              : 1;
  uint8_t hpm_ois                  : 2;
  uint8_t not_used_02              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 2;
  uint8_t hpm_ois                  : 2;
  uint8_t not_used_01              : 1;
  uint8_t ftype_ois                : 2;
  uint8_t hp_en_ois                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl2_ois_t;

#define LSM6DSR_CTRL3_OIS                    0x72U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t st_ois_clampdis          : 1;
  uint8_t st_ois                   : 2;
  uint8_t filter_xl_conf_ois       : 3;
  uint8_t fs_xl_ois                : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fs_xl_ois                : 2;
  uint8_t filter_xl_conf_ois       : 3;
  uint8_t st_ois                   : 2;
  uint8_t st_ois_clampdis          : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_ctrl3_ois_t;

#define LSM6DSR_X_OFS_USR                    0x73U
#define LSM6DSR_Y_OFS_USR                    0x74U
#define LSM6DSR_Z_OFS_USR                    0x75U
#define LSM6DSR_FIFO_DATA_OUT_TAG            0x78U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tag_parity               : 1;
  uint8_t tag_cnt                  : 2;
  uint8_t tag_sensor               : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tag_sensor               : 5;
  uint8_t tag_cnt                  : 2;
  uint8_t tag_parity               : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fifo_data_out_tag_t;

#define LSM6DSR_FIFO_DATA_OUT_X_L            0x79U
#define LSM6DSR_FIFO_DATA_OUT_X_H            0x7AU
#define LSM6DSR_FIFO_DATA_OUT_Y_L            0x7BU
#define LSM6DSR_FIFO_DATA_OUT_Y_H            0x7CU
#define LSM6DSR_FIFO_DATA_OUT_Z_L            0x7DU
#define LSM6DSR_FIFO_DATA_OUT_Z_H            0x7EU

#define LSM6DSR_PAGE_SEL                     0x02U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t page_sel                 : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t page_sel                 : 4;
  uint8_t not_used_01              : 4;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_page_sel_t;

#define LSM6DSR_ADV_PEDO                     0x03U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t pedo_fpr_adf_dis         : 1;
  uint8_t not_used_02              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 6;
  uint8_t pedo_fpr_adf_dis         : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_adv_pedo_t;

#define LSM6DSR_EMB_FUNC_EN_A                0x04U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 3;
  uint8_t pedo_en                  : 1;
  uint8_t tilt_en                  : 1;
  uint8_t sign_motion_en           : 1;
  uint8_t not_used_02              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 2;
  uint8_t sign_motion_en           : 1;
  uint8_t tilt_en                  : 1;
  uint8_t pedo_en                  : 1;
  uint8_t not_used_01              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_en_a_t;

#define LSM6DSR_EMB_FUNC_EN_B                0x05U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fsm_en                   : 1;
  uint8_t not_used_01              : 2;
  uint8_t fifo_compr_en            : 1;
  uint8_t pedo_adv_en              : 1;
  uint8_t not_used_02              : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 3;
  uint8_t pedo_adv_en              : 1;
  uint8_t fifo_compr_en            : 1;
  uint8_t not_used_01              : 2;
  uint8_t fsm_en                   : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_en_b_t;

#define LSM6DSR_PAGE_ADDRESS                 0x08U
typedef struct
{
  uint8_t page_addr                : 8;
} lsm6dsr_page_address_t;

#define LSM6DSR_PAGE_VALUE                   0x09U
typedef struct
{
  uint8_t page_value               : 8;
} lsm6dsr_page_value_t;

#define LSM6DSR_EMB_FUNC_INT1                0x0AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 3;
  uint8_t int1_step_detector       : 1;
  uint8_t int1_tilt                : 1;
  uint8_t int1_sig_mot             : 1;
  uint8_t not_used_02              : 1;
  uint8_t int1_fsm_lc              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_fsm_lc              : 1;
  uint8_t not_used_02              : 1;
  uint8_t int1_sig_mot             : 1;
  uint8_t int1_tilt                : 1;
  uint8_t int1_step_detector       : 1;
  uint8_t not_used_01              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_int1_t;

#define LSM6DSR_FSM_INT1_A                   0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_fsm1                : 1;
  uint8_t int1_fsm2                : 1;
  uint8_t int1_fsm3                : 1;
  uint8_t int1_fsm4                : 1;
  uint8_t int1_fsm5                : 1;
  uint8_t int1_fsm6                : 1;
  uint8_t int1_fsm7                : 1;
  uint8_t int1_fsm8                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_fsm8                : 1;
  uint8_t int1_fsm7                : 1;
  uint8_t int1_fsm6                : 1;
  uint8_t int1_fsm5                : 1;
  uint8_t int1_fsm4                : 1;
  uint8_t int1_fsm3                : 1;
  uint8_t int1_fsm2                : 1;
  uint8_t int1_fsm1                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_int1_a_t;

#define LSM6DSR_FSM_INT1_B                   0x0CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_fsm9                : 1;
  uint8_t int1_fsm10               : 1;
  uint8_t int1_fsm11               : 1;
  uint8_t int1_fsm12               : 1;
  uint8_t int1_fsm13               : 1;
  uint8_t int1_fsm14               : 1;
  uint8_t int1_fsm15               : 1;
  uint8_t int1_fsm16               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_fsm16               : 1;
  uint8_t int1_fsm15               : 1;
  uint8_t int1_fsm14               : 1;
  uint8_t int1_fsm13               : 1;
  uint8_t int1_fsm12               : 1;
  uint8_t int1_fsm11               : 1;
  uint8_t int1_fsm10               : 1;
  uint8_t int1_fsm9                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_int1_b_t;

#define LSM6DSR_EMB_FUNC_INT2                0x0EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 3;
  uint8_t int2_step_detector       : 1;
  uint8_t int2_tilt                : 1;
  uint8_t int2_sig_mot             : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_fsm_lc              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_fsm_lc              : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_sig_mot             : 1;
  uint8_t int2_tilt                : 1;
  uint8_t int2_step_detector       : 1;
  uint8_t not_used_01              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_int2_t;

#define LSM6DSR_FSM_INT2_A                   0x0FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_fsm1                : 1;
  uint8_t int2_fsm2                : 1;
  uint8_t int2_fsm3                : 1;
  uint8_t int2_fsm4                : 1;
  uint8_t int2_fsm5                : 1;
  uint8_t int2_fsm6                : 1;
  uint8_t int2_fsm7                : 1;
  uint8_t int2_fsm8                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_fsm8                : 1;
  uint8_t int2_fsm7                : 1;
  uint8_t int2_fsm6                : 1;
  uint8_t int2_fsm5                : 1;
  uint8_t int2_fsm4                : 1;
  uint8_t int2_fsm3                : 1;
  uint8_t int2_fsm2                : 1;
  uint8_t int2_fsm1                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_int2_a_t;

#define LSM6DSR_FSM_INT2_B                   0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_fsm9                : 1;
  uint8_t int2_fsm10               : 1;
  uint8_t int2_fsm11               : 1;
  uint8_t int2_fsm12               : 1;
  uint8_t int2_fsm13               : 1;
  uint8_t int2_fsm14               : 1;
  uint8_t int2_fsm15               : 1;
  uint8_t int2_fsm16               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_fsm16               : 1;
  uint8_t int2_fsm15               : 1;
  uint8_t int2_fsm14               : 1;
  uint8_t int2_fsm13               : 1;
  uint8_t int2_fsm12               : 1;
  uint8_t int2_fsm11               : 1;
  uint8_t int2_fsm10               : 1;
  uint8_t int2_fsm9                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_int2_b_t;

#define LSM6DSR_EMB_FUNC_STATUS              0x12U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 3;
  uint8_t is_step_det              : 1;
  uint8_t is_tilt                  : 1;
  uint8_t is_sigmot                : 1;
  uint8_t not_used_02              : 1;
  uint8_t is_fsm_lc                : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm_lc                : 1;
  uint8_t not_used_02              : 1;
  uint8_t is_sigmot                : 1;
  uint8_t is_tilt                  : 1;
  uint8_t is_step_det              : 1;
  uint8_t not_used_01              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_status_t;

#define LSM6DSR_FSM_STATUS_A                 0x13U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t is_fsm1                  : 1;
  uint8_t is_fsm2                  : 1;
  uint8_t is_fsm3                  : 1;
  uint8_t is_fsm4                  : 1;
  uint8_t is_fsm5                  : 1;
  uint8_t is_fsm6                  : 1;
  uint8_t is_fsm7                  : 1;
  uint8_t is_fsm8                  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm8                  : 1;
  uint8_t is_fsm7                  : 1;
  uint8_t is_fsm6                  : 1;
  uint8_t is_fsm5                  : 1;
  uint8_t is_fsm4                  : 1;
  uint8_t is_fsm3                  : 1;
  uint8_t is_fsm2                  : 1;
  uint8_t is_fsm1                  : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_status_a_t;

#define LSM6DSR_FSM_STATUS_B                 0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t is_fsm9                  : 1;
  uint8_t is_fsm10                 : 1;
  uint8_t is_fsm11                 : 1;
  uint8_t is_fsm12                 : 1;
  uint8_t is_fsm13                 : 1;
  uint8_t is_fsm14                 : 1;
  uint8_t is_fsm15                 : 1;
  uint8_t is_fsm16                 : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t is_fsm16                 : 1;
  uint8_t is_fsm15                 : 1;
  uint8_t is_fsm14                 : 1;
  uint8_t is_fsm13                 : 1;
  uint8_t is_fsm12                 : 1;
  uint8_t is_fsm11                 : 1;
  uint8_t is_fsm10                 : 1;
  uint8_t is_fsm9                  : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_status_b_t;

#define LSM6DSR_PAGE_RW                      0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t page_rw                  : 2;  /* page_write + page_read */
  uint8_t emb_func_lir             : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t emb_func_lir             : 1;
  uint8_t page_rw                  : 2;  /* page_write + page_read */
  uint8_t not_used_01              : 5;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_page_rw_t;

#define LSM6DSR_EMB_FUNC_FIFO_CFG            0x44U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t pedo_fifo_en             : 1;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t pedo_fifo_en             : 1;
  uint8_t not_used_01              : 6;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_fifo_cfg_t;

#define LSM6DSR_FSM_ENABLE_A                 0x46U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fsm1_en                  : 1;
  uint8_t fsm2_en                  : 1;
  uint8_t fsm3_en                  : 1;
  uint8_t fsm4_en                  : 1;
  uint8_t fsm5_en                  : 1;
  uint8_t fsm6_en                  : 1;
  uint8_t fsm7_en                  : 1;
  uint8_t fsm8_en                  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fsm8_en                  : 1;
  uint8_t fsm7_en                  : 1;
  uint8_t fsm6_en                  : 1;
  uint8_t fsm5_en                  : 1;
  uint8_t fsm4_en                  : 1;
  uint8_t fsm3_en                  : 1;
  uint8_t fsm2_en                  : 1;
  uint8_t fsm1_en                  : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_enable_a_t;

#define LSM6DSR_FSM_ENABLE_B                 0x47U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fsm9_en                  : 1;
  uint8_t fsm10_en                 : 1;
  uint8_t fsm11_en                 : 1;
  uint8_t fsm12_en                 : 1;
  uint8_t fsm13_en                 : 1;
  uint8_t fsm14_en                 : 1;
  uint8_t fsm15_en                 : 1;
  uint8_t fsm16_en                 : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fsm16_en                 : 1;
  uint8_t fsm15_en                 : 1;
  uint8_t fsm14_en                 : 1;
  uint8_t fsm13_en                 : 1;
  uint8_t fsm12_en                 : 1;
  uint8_t fsm11_en                 : 1;
  uint8_t fsm10_en                 : 1;
  uint8_t fsm9_en                  : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_enable_b_t;

#define LSM6DSR_FSM_LONG_COUNTER_L           0x48U
#define LSM6DSR_FSM_LONG_COUNTER_H           0x49U
#define LSM6DSR_FSM_LONG_COUNTER_CLEAR       0x4AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fsm_lc_clr               : 2;  /* fsm_lc_cleared + fsm_lc_clear */
  uint8_t not_used_01              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t fsm_lc_clr               : 2;  /* fsm_lc_cleared + fsm_lc_clear */
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_fsm_long_counter_clear_t;

#define LSM6DSR_FSM_OUTS1                    0x4CU
#define LSM6DSR_FSM_OUTS2                    0x4DU
#define LSM6DSR_FSM_OUTS3                    0x4EU
#define LSM6DSR_FSM_OUTS4                    0x4FU
#define LSM6DSR_FSM_OUTS5                    0x50U
#define LSM6DSR_FSM_OUTS6                    0x51U
#define LSM6DSR_FSM_OUTS7                    0x52U
#define LSM6DSR_FSM_OUTS8                    0x53U
#define LSM6DSR_FSM_OUTS9                    0x54U
#define LSM6DSR_FSM_OUTS10                   0x55U
#define LSM6DSR_FSM_OUTS11                   0x56U
#define LSM6DSR_FSM_OUTS12                   0x57U
#define LSM6DSR_FSM_OUTS13                   0x58U
#define LSM6DSR_FSM_OUTS14                   0x59U
#define LSM6DSR_FSM_OUTS15                   0x5AU
#define LSM6DSR_FSM_OUTS16                   0x5BU

#define LSM6DSR_EMB_FUNC_ODR_CFG_B           0x5FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 3;
  uint8_t fsm_odr                  : 2;
  uint8_t not_used_02              : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 3;
  uint8_t fsm_odr                  : 2;
  uint8_t not_used_01              : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_odr_cfg_b_t;

#define LSM6DSR_STEP_COUNTER_L               0x62U
#define LSM6DSR_STEP_COUNTER_H               0x63U
#define LSM6DSR_EMB_FUNC_SRC                 0x64U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t stepcounter_bit_set      : 1;
  uint8_t step_overflow            : 1;
  uint8_t step_count_delta_ia      : 1;
  uint8_t step_detected            : 1;
  uint8_t not_used_02              : 1;
  uint8_t pedo_rst_step            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t pedo_rst_step            : 1;
  uint8_t not_used_02              : 1;
  uint8_t step_detected            : 1;
  uint8_t step_count_delta_ia      : 1;
  uint8_t step_overflow            : 1;
  uint8_t stepcounter_bit_set      : 1;
  uint8_t not_used_01              : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_src_t;

#define LSM6DSR_EMB_FUNC_INIT_A              0x66U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01               : 3;
  uint8_t step_det_init             : 1;
  uint8_t tilt_init                 : 1;
  uint8_t sig_mot_init              : 1;
  uint8_t not_used_02               : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02               : 2;
  uint8_t sig_mot_init              : 1;
  uint8_t tilt_init                 : 1;
  uint8_t step_det_init             : 1;
  uint8_t not_used_01               : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_init_a_t;

#define LSM6DSR_EMB_FUNC_INIT_B              0x67U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fsm_init                 : 1;
  uint8_t not_used_01              : 2;
  uint8_t fifo_compr_init          : 1;
  uint8_t not_used_02              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 4;
  uint8_t fifo_compr_init          : 1;
  uint8_t not_used_01              : 2;
  uint8_t fsm_init                 : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_emb_func_init_b_t;

/** @defgroup bitfields page 0 and 1
  * @{
  *
  */
#define LSM6DSR_MAG_SENSITIVITY_L            0xBAU
#define LSM6DSR_MAG_SENSITIVITY_H            0xBBU
#define LSM6DSR_MAG_OFFX_L                   0xC0U
#define LSM6DSR_MAG_OFFX_H                   0xC1U
#define LSM6DSR_MAG_OFFY_L                   0xC2U
#define LSM6DSR_MAG_OFFY_H                   0xC3U
#define LSM6DSR_MAG_OFFZ_L                   0xC4U
#define LSM6DSR_MAG_OFFZ_H                   0xC5U
#define LSM6DSR_MAG_SI_XX_L                  0xC6U
#define LSM6DSR_MAG_SI_XX_H                  0xC7U
#define LSM6DSR_MAG_SI_XY_L                  0xC8U
#define LSM6DSR_MAG_SI_XY_H                  0xC9U
#define LSM6DSR_MAG_SI_XZ_L                  0xCAU
#define LSM6DSR_MAG_SI_XZ_H                  0xCBU
#define LSM6DSR_MAG_SI_YY_L                  0xCCU
#define LSM6DSR_MAG_SI_YY_H                  0xCDU
#define LSM6DSR_MAG_SI_YZ_L                  0xCEU
#define LSM6DSR_MAG_SI_YZ_H                  0xCFU
#define LSM6DSR_MAG_SI_ZZ_L                  0xD0U
#define LSM6DSR_MAG_SI_ZZ_H                  0xD1U
#define LSM6DSR_MAG_CFG_A                    0xD4U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t mag_z_axis               : 3;
  uint8_t not_used_01              : 1;
  uint8_t mag_y_axis               : 3;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t mag_y_axis               : 3;
  uint8_t not_used_01              : 1;
  uint8_t mag_z_axis               : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_mag_cfg_a_t;

#define LSM6DSR_MAG_CFG_B                    0xD5U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t mag_x_axis               : 3;
  uint8_t not_used_01              : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t mag_x_axis               : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_mag_cfg_b_t;

#define LSM6DSR_FSM_LC_TIMEOUT_L             0x17AU
#define LSM6DSR_FSM_LC_TIMEOUT_H             0x17BU
#define LSM6DSR_FSM_PROGRAMS                 0x17CU

#define LSM6DSR_PEDO_CMD_REG                 0x183U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ad_det_en                : 1;
  uint8_t not_used_01              : 1;
  uint8_t fp_rejection_en          : 1;
  uint8_t carry_count_en           : 1;
  uint8_t not_used_02              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 4;
  uint8_t carry_count_en           : 1;
  uint8_t fp_rejection_en          : 1;
  uint8_t not_used_01              : 1;
  uint8_t ad_det_en                : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_pedo_cmd_reg_t;

#define LSM6DSR_PEDO_DEB_STEPS_CONF          0x184U
#define LSM6DSR_PEDO_SC_DELTAT_L             0x1D0U
#define LSM6DSR_PEDO_SC_DELTAT_H             0x1D1U

/**
  * @}
  *
  */

/** @defgroup bitfields page sensor_hub
  * @{
  *
  */

#define LSM6DSR_SENSOR_HUB_1                 0x02U
#define LSM6DSR_SENSOR_HUB_2                 0x03U
#define LSM6DSR_SENSOR_HUB_3                 0x04U
#define LSM6DSR_SENSOR_HUB_4                 0x05U
#define LSM6DSR_SENSOR_HUB_5                 0x06U
#define LSM6DSR_SENSOR_HUB_6                 0x07U
#define LSM6DSR_SENSOR_HUB_7                 0x08U
#define LSM6DSR_SENSOR_HUB_8                 0x09U
#define LSM6DSR_SENSOR_HUB_9                 0x0AU
#define LSM6DSR_SENSOR_HUB_10                0x0BU
#define LSM6DSR_SENSOR_HUB_11                0x0CU
#define LSM6DSR_SENSOR_HUB_12                0x0DU
#define LSM6DSR_SENSOR_HUB_13                0x0EU
#define LSM6DSR_SENSOR_HUB_14                0x0FU
#define LSM6DSR_SENSOR_HUB_15                0x10U
#define LSM6DSR_SENSOR_HUB_16                0x11U
#define LSM6DSR_SENSOR_HUB_17                0x12U
#define LSM6DSR_SENSOR_HUB_18                0x13U

#define LSM6DSR_MASTER_CONFIG                0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t aux_sens_on              : 2;
  uint8_t master_on                : 1;
  uint8_t shub_pu_en               : 1;
  uint8_t pass_through_mode        : 1;
  uint8_t start_config             : 1;
  uint8_t write_once               : 1;
  uint8_t rst_master_regs          : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t rst_master_regs          : 1;
  uint8_t write_once               : 1;
  uint8_t start_config             : 1;
  uint8_t pass_through_mode        : 1;
  uint8_t shub_pu_en               : 1;
  uint8_t master_on                : 1;
  uint8_t aux_sens_on              : 2;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_master_config_t;

#define LSM6DSR_SLV0_ADD                     0x15U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t rw_0                     : 1;
  uint8_t slave0                   : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t slave0                   : 7;
  uint8_t rw_0                     : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv0_add_t;

#define LSM6DSR_SLV0_SUBADD                  0x16U
typedef struct
{
  uint8_t slave0_reg               : 8;
} lsm6dsr_slv0_subadd_t;

#define LSM6DSR_SLV0_CONFIG                  0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t slave0_numop             : 3;
  uint8_t batch_ext_sens_0_en      : 1;
  uint8_t not_used_01              : 2;
  uint8_t shub_odr                 : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t shub_odr                 : 2;
  uint8_t not_used_01              : 2;
  uint8_t batch_ext_sens_0_en      : 1;
  uint8_t slave0_numop             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv0_config_t;

#define LSM6DSR_SLV1_ADD                     0x18U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t r_1                      : 1;
  uint8_t slave1_add               : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t slave1_add               : 7;
  uint8_t r_1                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv1_add_t;

#define LSM6DSR_SLV1_SUBADD                  0x19U
typedef struct
{
  uint8_t slave1_reg               : 8;
} lsm6dsr_slv1_subadd_t;

#define LSM6DSR_SLV1_CONFIG                  0x1AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t slave1_numop             : 3;
  uint8_t batch_ext_sens_1_en      : 1;
  uint8_t not_used_01              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t batch_ext_sens_1_en      : 1;
  uint8_t slave1_numop             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv1_config_t;

#define LSM6DSR_SLV2_ADD                     0x1BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t r_2                      : 1;
  uint8_t slave2_add               : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t slave2_add               : 7;
  uint8_t r_2                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv2_add_t;

#define LSM6DSR_SLV2_SUBADD                  0x1CU
typedef struct
{
  uint8_t slave2_reg               : 8;
} lsm6dsr_slv2_subadd_t;

#define LSM6DSR_SLV2_CONFIG                  0x1DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t slave2_numop             : 3;
  uint8_t batch_ext_sens_2_en      : 1;
  uint8_t not_used_01              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t batch_ext_sens_2_en      : 1;
  uint8_t slave2_numop             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv2_config_t;

#define LSM6DSR_SLV3_ADD                     0x1EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t r_3                      : 1;
  uint8_t slave3_add               : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t slave3_add               : 7;
  uint8_t r_3                      : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv3_add_t;

#define LSM6DSR_SLV3_SUBADD                  0x1FU
typedef struct
{
  uint8_t slave3_reg               : 8;
} lsm6dsr_slv3_subadd_t;

#define LSM6DSR_SLV3_CONFIG                  0x20U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t slave3_numop             : 3;
  uint8_t batch_ext_sens_3_en      : 1;
  uint8_t not_used_01              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t batch_ext_sens_3_en      : 1;
  uint8_t slave3_numop             : 3;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_slv3_config_t;

#define LSM6DSR_DATAWRITE_SLV0  0x21U
typedef struct
{
  uint8_t slave0_dataw             : 8;
} lsm6dsr_datawrite_slv0_t;

#define LSM6DSR_STATUS_MASTER                0x22U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sens_hub_endop           : 1;
  uint8_t not_used_01              : 2;
  uint8_t slave0_nack              : 1;
  uint8_t slave1_nack              : 1;
  uint8_t slave2_nack              : 1;
  uint8_t slave3_nack              : 1;
  uint8_t wr_once_done             : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t wr_once_done             : 1;
  uint8_t slave3_nack              : 1;
  uint8_t slave2_nack              : 1;
  uint8_t slave1_nack              : 1;
  uint8_t slave0_nack              : 1;
  uint8_t not_used_01              : 2;
  uint8_t sens_hub_endop           : 1;
#endif /* DRV_BYTE_ORDER */
} lsm6dsr_status_master_t;

#define LSM6DSR_FSM_LC_TIMEOUT_L             0x17AU
#define LSM6DSR_FSM_LC_TIMEOUT_H             0x17BU
#define LSM6DSR_FSM_PROGRAMS                 0x17CU
#define LSM6DSR_FSM_START_ADD_L              0x17EU
#define LSM6DSR_FSM_START_ADD_H              0x17FU

typedef struct
{
	RawBuffer_t				          BufGyroX;
	RawBuffer_t				          BufGyroY;
	RawBuffer_t				          BufGyroZ;
	RawBuffer_t				          BufAccX;
	RawBuffer_t				          BufAccY;
	RawBuffer_t				          BufAccZ;
	RawBuffer_t				          BufTemp;
	
	float                       Temp;
	float                       Accs[3];
	float                       Gyros[3];
	uint8_t                     AccsValid[3];
	uint8_t                     GyrosValid[3];
	uint8_t                     TempValid;
	
	volatile uint64_t           lastUpdate;
}LSM6DSR_Status_Type;

#define LSM6DSR_CS_enable            gpio_bits_write(GPIOA,GPIO_PINS_15,FALSE);
#define LSM6DSR_CS_disenable         gpio_bits_write(GPIOA,GPIO_PINS_15,TRUE);

#define AccScale (9.7947f * 8.0f / 32768.0f) 
#define GyroScale ((3.1415926f * 2000.0f / 180.0f) / 32768.0f) 

void LSM6DSR_Init(void);
void LSM6DSR_callback(rtio_t *rtio);
void LSM6DSR_Conversion(uint8_t *Data_Receive);

extern LSM6DSR_Status_Type LSM6DSR;
extern rt_mq_t sensor_cqe_mq;
extern uint8_t LSM6DR_Data_Receive[15];
extern int LSM6DSR_Decode(LSM6DSR_Status_Type* LSM6DSR);
#endif
