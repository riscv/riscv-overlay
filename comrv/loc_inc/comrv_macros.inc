/* 
* SPDX-License-Identifier: Apache-2.0
* Copyright 2019-2021 Western Digital Corporation or its affiliates.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http:*www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @file   comrv_macros.inc
* @author Ronen Haen
* @date   02.10.2019
* @brief  The defines COM-RV assembly macros
* 
*/

/**
* include files
*/

/**
* definitions
*/
.equ D_PSP_MIE,8

/**
* macros
*/
.if __riscv_xlen == 32
    .equ REGBYTES, 4

    .macro M_PSP_STORE operand1,operand2
        sw \operand1, \operand2
    .endm

    .macro M_PSP_LOAD operand1,operand2
        lw \operand1, \operand2
    .endm

    .macro M_PSP_ADDI operand1,operand2,operand3
        addi \operand1, \operand2, \operand3
    .endm

.elseif __riscv_xlen == 64

    .equ REGBYTES, 8

    .macro M_PSP_STORE operand1,operand2
        sd \operand1, \operand2
    .endm

    .macro M_PSP_LOAD operand1,operand2
        ld \operand1, \operand2
    .endm

    .macro M_PSP_ADDI operand1,operand2,operand3
        addiw \operand1, \operand2, \operand3
    .endm
.endif

.macro M_PSP_STORE_BYTE operand1,operand2
    sb \operand1, \operand2
.endm

.macro M_PSP_LOAD_BYTE operand1,operand2
    lb \operand1, \operand2
.endm

.macro M_PSP_STORE_HALF operand1,operand2
    sh \operand1, \operand2
.endm

.macro M_PSP_LOAD_HALF operand1,operand2
    lh \operand1, \operand2
.endm

/* Disable machine interrupts after reading the current status . Available in MACHINE mode only */
.macro M_PSP_MACHINE_DISABLE_INTERRUPTS saveCurrentStatusToReg
    csrrci \saveCurrentStatusToReg, mstatus, D_PSP_MIE
.endm

/* Restore machine interrupts status . Available in MACHINE mode only */
.macro M_PSP_MACHINE_RESTORE_INTERRUPTS restorStatusFromReg
    csrs mstatus, \restorStatusFromReg
.endm

/* save the 'args' regs */
.macro M_COMRV_SAVE_ARGS_REGS reg
   M_PSP_STORE a0, D_COMRV_A0_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a1, D_COMRV_A1_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a2, D_COMRV_A2_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a3, D_COMRV_A3_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a4, D_COMRV_A4_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a5, D_COMRV_A5_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a6, D_COMRV_A6_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE a7, D_COMRV_A7_REG_STACK_OFFSET_TMP(\reg)
.endm

/* save the a0 reg */
.macro M_COMRV_SAVE_ARG0_REG reg
   M_PSP_STORE a0, D_COMRV_A0_REG_STACK_OFFSET_TMP(\reg)
.endm

/* restore 'args' regs */
.macro M_COMRV_RESTORE_ARGS_REGS reg
   M_PSP_LOAD  a0, D_COMRV_A0_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a1, D_COMRV_A1_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a2, D_COMRV_A2_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a3, D_COMRV_A3_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a4, D_COMRV_A4_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a5, D_COMRV_A5_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a6, D_COMRV_A6_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  a7, D_COMRV_A7_REG_STACK_OFFSET_TMP(\reg)
.endm

#ifdef D_COMRV_RTOS_SUPPORT
/* save the 'saved' regs */
.macro M_COMRV_SAVE_SAVED_REGS reg
   M_PSP_STORE s0, D_COMRV_S0_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s1, D_COMRV_S1_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s2, D_COMRV_S2_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s3, D_COMRV_S3_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s4, D_COMRV_S4_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s5, D_COMRV_S5_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s6, D_COMRV_S6_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s7, D_COMRV_S7_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s8, D_COMRV_S8_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s9, D_COMRV_S9_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s10, D_COMRV_S10_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE s11, D_COMRV_S11_REG_STACK_OFFSET_TMP(\reg)
.endm

/* restore the 'saved' regs */
.macro M_COMRV_RESTORE_SAVED_REGS reg
   M_PSP_LOAD  s0, D_COMRV_S0_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s1, D_COMRV_S1_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s2, D_COMRV_S2_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s3, D_COMRV_S3_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s4, D_COMRV_S4_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s5, D_COMRV_S5_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s6, D_COMRV_S6_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s7, D_COMRV_S7_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s8, D_COMRV_S8_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s9, D_COMRV_S9_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s10, D_COMRV_S10_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_LOAD  s11, D_COMRV_S11_REG_STACK_OFFSET_TMP(\reg)
.endm

/* save comrv state */
.macro M_COMRV_SAVE_RTOS_STATE_REGS reg, state
   li          t2, \state
   M_PSP_STORE t2, D_COMRV_STATE_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE sp, D_COMRV_SP_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE ra, D_COMRV_RA_REG_STACK_OFFSET_TMP(\reg)
   M_PSP_STORE t5, D_COMRV_T5_REG_STACK_OFFSET_TMP(\reg)
.endm

   /* save 'args', 'saved' regs and comrv 'state' -
      this is needed since comrv is about to 'search and
      load' and these regs are use for that purpose;
      if a context switch occures, comrv will use
      the saved values for restoring comrv state */
.macro M_COMRV_SAVE_REGS_AND_STATE state
   /* disable ints before saving */
   M_COMRV_DISABLE_INTS         t1
   /* save 'args' regs */
   M_COMRV_SAVE_ARGS_REGS       tp
   /* save 'saved' regs */
   M_COMRV_SAVE_SAVED_REGS      tp
   /* save comrv state */
   M_COMRV_SAVE_RTOS_STATE_REGS tp, \state
#ifdef D_COMRV_OVL_DATA_SUPPORT
   /* clear a0 - NULL arg for comrvGetAddressFromToken */
   mv a0,zero
#endif /* D_COMRV_OVL_DATA_SUPPORT */
   /* re-enable ints */
   M_COMRV_RESTORE_INTS         t1
.endm
   /* this macro is the same as M_COMRV_SAVE_REGS_AND_STATE
      but w/o saving the 'saved' and regs */
.macro M_COMRV_SAVE_STATE state
   /* disable ints before saving */
   M_COMRV_DISABLE_INTS         t1
   /* save comrv state */
   M_COMRV_SAVE_RTOS_STATE_REGS tp, \state
   /* save a0 reg */
   M_COMRV_SAVE_ARG0_REG        tp
   /* re-enable ints */
   M_COMRV_RESTORE_INTS         t1
.endm
.macro M_COMRV_RESTORE_A_REGS
   M_COMRV_DISABLE_INTS         t1
   M_COMRV_RESTORE_ARGS_REGS    tp
   M_COMRV_RESTORE_INTS         t1
.endm
.macro M_COMRV_CLEAR_STATE
   M_PSP_STORE zero, D_COMRV_STATE_STACK_OFFSET_TMP(tp)
.endm
.macro M_COMRV_RESTORE_INTS restoreStatusFromReg
   M_PSP_MACHINE_RESTORE_INTERRUPTS \restoreStatusFromReg
.endm
.macro M_COMRV_DISABLE_INTS saveStatusInReg
   M_PSP_MACHINE_DISABLE_INTERRUPTS \saveStatusInReg
.endm
#else
.macro M_COMRV_SAVE_REGS_AND_STATE state
   M_PSP_ADDI  sp, sp, -D_COMRV_STACK_FRAME_SIZE
   M_COMRV_SAVE_ARGS_REGS    sp
#ifdef D_COMRV_OVL_DATA_SUPPORT
   /* clear a0 - NULL arg for comrvGetAddressFromToken */
   mv a0,zero
#endif /* D_COMRV_OVL_DATA_SUPPORT */
.endm
.macro M_COMRV_SAVE_STATE state
   M_PSP_ADDI  sp, sp, -D_COMRV_STACK_FRAME_SIZE
   M_COMRV_SAVE_ARG0_REG     sp
.endm
.macro M_COMRV_RESTORE_A_REGS
   M_COMRV_RESTORE_ARGS_REGS sp
   M_PSP_ADDI  sp, sp, D_COMRV_STACK_FRAME_SIZE
.endm
.macro M_COMRV_CLEAR_STATE
.endm
.macro M_COMRV_RESTORE_INTS restoreStatusFromReg
.endm
.macro M_COMRV_DISABLE_INTS saveStatusInReg
.endm
#endif /* D_COMRV_RTOS_SUPPORT */

.macro M_COMRV_STORE operand1,operand2
   M_PSP_STORE \operand1, \operand2
.endm

.macro M_COMRV_LOAD operand1,operand2
   M_PSP_LOAD \operand1, \operand2
.endm

.macro M_COMRV_STORE_BYTE operand1,operand2
   M_PSP_STORE_BYTE \operand1, \operand2
.endm

.macro M_COMRV_LOAD_BYTE operand1,operand2
   M_PSP_LOAD_BYTE \operand1, \operand2
.endm

.macro M_COMRV_STORE_HALF operand1,operand2
   M_PSP_STORE_HALF \operand1, \operand2
.endm

.macro M_COMRV_LOAD_HALF operand1,operand2
   M_PSP_LOAD_HALF \operand1, \operand2
.endm
