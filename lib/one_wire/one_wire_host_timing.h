/**
 * @file one_wire_host_timing.h
 * @author Sergey Gavrilov (who.just.the.doctor@gmail.com)
 * @version 1.0
 * @date 2021-11-18
 * 
 * 1-Wire library, timing list
 */

#pragma once

#define OWH_TIMING_A 9
#define OWH_TIMING_B 64
#define OWH_TIMING_C 64
#define OWH_TIMING_D 14
#define OWH_TIMING_E 9
#define OWH_TIMING_F 55
#define OWH_TIMING_G 0
#define OWH_TIMING_H 480
#define OWH_TIMING_I 70
#define OWH_TIMING_J 410

#define OWH_WRITE_1_DRIVE OWH_TIMING_A
#define OWH_WRITE_1_RELEASE OWH_TIMING_B
#define OWH_WRITE_0_DRIVE OWH_TIMING_C
#define OWH_WRITE_0_RELEASE OWH_TIMING_D
#define OWH_READ_DRIVE 3
#define OWH_READ_RELEASE OWH_TIMING_E
#define OWH_READ_DELAY_POST OWH_TIMING_F
#define OWH_RESET_DELAY_PRE OWH_TIMING_G
#define OWH_RESET_DRIVE OWH_TIMING_H
#define OWH_RESET_RELEASE OWH_TIMING_I
#define OWH_RESET_DELAY_POST OWH_TIMING_J
