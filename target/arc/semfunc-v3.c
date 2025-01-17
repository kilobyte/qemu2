/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2017 Cupertino Miranda
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see
 *  <http://www.gnu.org/licenses/lgpl-2.1.html>
 */

#include "qemu/osdep.h"
#include "translate.h"
#include "semfunc.h"
#include "exec/gen-icount.h"
#include "tcg/tcg-op-gvec.h"




/* FLAG
 *    Variables: @src
 *    Functions: getCCFlag, getRegister, getBit, hasInterrupts, Halt, ReplMask, targetHasOption, setRegister
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      status32 = getRegister (R_STATUS32);
      if(((getBit (@src, 0) == 1) && (getBit (status32, 7) == 0)))
        {
          if((hasInterrupts () > 0))
            {
              status32 = (status32 | 1);
              Halt ();
            };
        }
      else
        {
          ReplMask (status32, @src, 3840);
          if(((getBit (status32, 7) == 0) && (hasInterrupts () > 0)))
            {
              ReplMask (status32, @src, 30);
              if(targetHasOption (DIV_REM_OPTION))
                {
                  ReplMask (status32, @src, 8192);
                };
              if(targetHasOption (STACK_CHECKING))
                {
                  ReplMask (status32, @src, 16384);
                };
              if(targetHasOption (LL64_OPTION))
                {
                  ReplMask (status32, @src, 524288);
                };
              ReplMask (status32, @src, 1048576);
            };
        };
      setRegister (R_STATUS32, status32);
    };
}
 */

int
arc_gen_FLAG (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_13 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_14 = tcg_temp_local_new();
  TCGv status32 = tcg_temp_local_new();
  TCGv temp_16 = tcg_temp_local_new();
  TCGv temp_15 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_18 = tcg_temp_local_new();
  TCGv temp_17 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_19 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_20 = tcg_temp_local_new();
  TCGv temp_22 = tcg_temp_local_new();
  TCGv temp_21 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_23 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_24 = tcg_temp_local_new();
  TCGv temp_25 = tcg_temp_local_new();
  TCGv temp_26 = tcg_temp_local_new();
  TCGv temp_27 = tcg_temp_local_new();
  TCGv temp_28 = tcg_temp_local_new();
  getCCFlag(temp_13);
  tcg_gen_mov_tl(cc_flag, temp_13);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  getRegister(temp_14, R_STATUS32);
  tcg_gen_mov_tl(status32, temp_14);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_movi_tl(temp_16, 0);
  getBit(temp_15, src, temp_16);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, temp_15, 1);
  tcg_gen_movi_tl(temp_18, 7);
  getBit(temp_17, status32, temp_18);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_4, temp_17, 0);
  tcg_gen_and_tl(temp_5, temp_3, temp_4);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_2);;
  TCGLabel *done_3 = gen_new_label();
  hasInterrupts(temp_19);
  tcg_gen_setcondi_tl(TCG_COND_GT, temp_7, temp_19, 0);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, done_3);;
  tcg_gen_ori_tl(status32, status32, 1);
  Halt();
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_movi_tl(temp_20, 3840);
  ReplMask(status32, src, temp_20);
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_movi_tl(temp_22, 7);
  getBit(temp_21, status32, temp_22);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_9, temp_21, 0);
  hasInterrupts(temp_23);
  tcg_gen_setcondi_tl(TCG_COND_GT, temp_10, temp_23, 0);
  tcg_gen_and_tl(temp_11, temp_9, temp_10);
  tcg_gen_xori_tl(temp_12, temp_11, 1); tcg_gen_andi_tl(temp_12, temp_12, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_12, arc_true, done_4);;
  tcg_gen_movi_tl(temp_24, 30);
  ReplMask(status32, src, temp_24);
  if (targetHasOption (DIV_REM_OPTION))
    {
    tcg_gen_movi_tl(temp_25, 8192);
  ReplMask(status32, src, temp_25);
;
    }
  else
    {
  ;
    }
  if (targetHasOption (STACK_CHECKING))
    {
    tcg_gen_movi_tl(temp_26, 16384);
  ReplMask(status32, src, temp_26);
;
    }
  else
    {
  ;
    }
  if (targetHasOption (LL64_OPTION))
    {
    tcg_gen_movi_tl(temp_27, 524288);
  ReplMask(status32, src, temp_27);
;
    }
  else
    {
  ;
    }
  tcg_gen_movi_tl(temp_28, 1048576);
  ReplMask(status32, src, temp_28);
  gen_set_label(done_4);
  gen_set_label(done_2);
  setRegister(R_STATUS32, status32);
  gen_set_label(done_1);
  tcg_temp_free(temp_13);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_14);
  tcg_temp_free(status32);
  tcg_temp_free(temp_16);
  tcg_temp_free(temp_15);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_18);
  tcg_temp_free(temp_17);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_19);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_20);
  tcg_temp_free(temp_22);
  tcg_temp_free(temp_21);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_23);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_24);
  tcg_temp_free(temp_25);
  tcg_temp_free(temp_26);
  tcg_temp_free(temp_27);
  tcg_temp_free(temp_28);

  return ret;
}





/* KFLAG
 *    Variables: @src
 *    Functions: getCCFlag, getRegister, getBit, hasInterrupts, Halt, ReplMask, targetHasOption, setRegister
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      status32 = getRegister (R_STATUS32);
      if(((getBit (@src, 0) == 1) && (getBit (status32, 7) == 0)))
        {
          if((hasInterrupts () > 0))
            {
              status32 = (status32 | 1);
              Halt ();
            };
        }
      else
        {
          ReplMask (status32, @src, 3840);
          if(((getBit (status32, 7) == 0) && (hasInterrupts () > 0)))
            {
              ReplMask (status32, @src, 62);
              if(targetHasOption (DIV_REM_OPTION))
                {
                  ReplMask (status32, @src, 8192);
                };
              if(targetHasOption (STACK_CHECKING))
                {
                  ReplMask (status32, @src, 16384);
                };
              ReplMask (status32, @src, 65536);
              if(targetHasOption (LL64_OPTION))
                {
                  ReplMask (status32, @src, 524288);
                };
              ReplMask (status32, @src, 1048576);
              ReplMask (status32, @src, 2147483648);
            };
        };
      setRegister (R_STATUS32, status32);
    };
}
 */

int
arc_gen_KFLAG (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_13 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_14 = tcg_temp_local_new();
  TCGv status32 = tcg_temp_local_new();
  TCGv temp_16 = tcg_temp_local_new();
  TCGv temp_15 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_18 = tcg_temp_local_new();
  TCGv temp_17 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_19 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_20 = tcg_temp_local_new();
  TCGv temp_22 = tcg_temp_local_new();
  TCGv temp_21 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_23 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_24 = tcg_temp_local_new();
  TCGv temp_25 = tcg_temp_local_new();
  TCGv temp_26 = tcg_temp_local_new();
  TCGv temp_27 = tcg_temp_local_new();
  TCGv temp_28 = tcg_temp_local_new();
  TCGv temp_29 = tcg_temp_local_new();
  TCGv temp_30 = tcg_temp_local_new();
  getCCFlag(temp_13);
  tcg_gen_mov_tl(cc_flag, temp_13);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  getRegister(temp_14, R_STATUS32);
  tcg_gen_mov_tl(status32, temp_14);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_movi_tl(temp_16, 0);
  getBit(temp_15, src, temp_16);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, temp_15, 1);
  tcg_gen_movi_tl(temp_18, 7);
  getBit(temp_17, status32, temp_18);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_4, temp_17, 0);
  tcg_gen_and_tl(temp_5, temp_3, temp_4);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_2);;
  TCGLabel *done_3 = gen_new_label();
  hasInterrupts(temp_19);
  tcg_gen_setcondi_tl(TCG_COND_GT, temp_7, temp_19, 0);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, done_3);;
  tcg_gen_ori_tl(status32, status32, 1);
  Halt();
  gen_set_label(done_3);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_movi_tl(temp_20, 3840);
  ReplMask(status32, src, temp_20);
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_movi_tl(temp_22, 7);
  getBit(temp_21, status32, temp_22);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_9, temp_21, 0);
  hasInterrupts(temp_23);
  tcg_gen_setcondi_tl(TCG_COND_GT, temp_10, temp_23, 0);
  tcg_gen_and_tl(temp_11, temp_9, temp_10);
  tcg_gen_xori_tl(temp_12, temp_11, 1); tcg_gen_andi_tl(temp_12, temp_12, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_12, arc_true, done_4);;
  tcg_gen_movi_tl(temp_24, 62);
  ReplMask(status32, src, temp_24);
  if (targetHasOption (DIV_REM_OPTION))
    {
    tcg_gen_movi_tl(temp_25, 8192);
  ReplMask(status32, src, temp_25);
;
    }
  else
    {
  ;
    }
  if (targetHasOption (STACK_CHECKING))
    {
    tcg_gen_movi_tl(temp_26, 16384);
  ReplMask(status32, src, temp_26);
;
    }
  else
    {
  ;
    }
  tcg_gen_movi_tl(temp_27, 65536);
  ReplMask(status32, src, temp_27);
  if (targetHasOption (LL64_OPTION))
    {
    tcg_gen_movi_tl(temp_28, 524288);
  ReplMask(status32, src, temp_28);
;
    }
  else
    {
  ;
    }
  tcg_gen_movi_tl(temp_29, 1048576);
  ReplMask(status32, src, temp_29);
  tcg_gen_movi_tl(temp_30, 2147483648);
  ReplMask(status32, src, temp_30);
  gen_set_label(done_4);
  gen_set_label(done_2);
  setRegister(R_STATUS32, status32);
  gen_set_label(done_1);
  tcg_temp_free(temp_13);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_14);
  tcg_temp_free(status32);
  tcg_temp_free(temp_16);
  tcg_temp_free(temp_15);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_18);
  tcg_temp_free(temp_17);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_19);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_20);
  tcg_temp_free(temp_22);
  tcg_temp_free(temp_21);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_23);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_24);
  tcg_temp_free(temp_25);
  tcg_temp_free(temp_26);
  tcg_temp_free(temp_27);
  tcg_temp_free(temp_28);
  tcg_temp_free(temp_29);
  tcg_temp_free(temp_30);

  return ret;
}





/* ADD
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarryADD32, setVFlag, OverflowADD32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  lc = se32to64 (@c);
  if((cc_flag == true))
    {
      @a = ((lb + lc) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarryADD32 (@a, lb, lc));
          setVFlag (OverflowADD32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_ADD (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  se32to64(temp_5, c);
  tcg_gen_mov_tl(lc, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_add_tl(temp_6, lb, lc);
  tcg_gen_andi_tl(a, temp_6, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarryADD32(temp_8, a, lb, lc);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
  OverflowADD32(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setVFlag(temp_9);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}




/*
 * ADD1
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, CarryADD32,
 *               setVFlag, OverflowADD32, se32to64
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = se32to64 (@b);
 *   lc = se32to64 (@c << 1);
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc) & 0xffffffff;
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag32 (@a);
 *           setCFlag (CarryADD32 (@a, lb, lc));
 *           setVFlag (OverflowADD32 (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD1(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    se32to64(lb, b);
    tcg_gen_shli_tl(temp_4, c, 1);
    se32to64(lc, temp_4);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(temp_5, b, lc);
    tcg_gen_andi_tl(a, temp_5, 4294967295);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag32(a);
        CarryADD32(temp_6, a, lb, lc);
        setCFlag(temp_6);
        OverflowADD32(temp_7, a, lb, lc);
        setVFlag(temp_7);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(temp_4);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_6);
    tcg_temp_free(temp_7);

    return ret;
}



/*
 * ADD2
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, CarryADD32,
 *               setVFlag, OverflowADD32, se32to64
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = se32to64 (@b);
 *   lc = se32to64 (@c << 2);
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc) & 0xffffffff;
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag32 (@a);
 *           setCFlag (CarryADD32 (@a, lb, lc));
 *           setVFlag (OverflowADD32 (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD2(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    se32to64(lb, b);
    tcg_gen_shli_tl(temp_4, c, 2);
    se32to64(lc, temp_4);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(temp_5, b, lc);
    tcg_gen_andi_tl(a, temp_5, 4294967295);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag32(a);
        CarryADD32(temp_6, a, lb, lc);
        setCFlag(temp_6);
        OverflowADD32(temp_7, a, lb, lc);
        setVFlag(temp_7);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(temp_4);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_6);
    tcg_temp_free(temp_7);

    return ret;
}




/*
 * ADD3
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, CarryADD32,
 *               setVFlag, OverflowADD32, se32to64
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = se32to64 (@b);
 *   lc = se32to64 (@c << 3);
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc) & 0xffffffff;
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag32 (@a);
 *           setCFlag (CarryADD32 (@a, lb, lc));
 *           setVFlag (OverflowADD32 (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD3(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    se32to64(lb, b);
    tcg_gen_shli_tl(temp_4, c, 3);
    se32to64(lc, temp_4);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(temp_5, b, lc);
    tcg_gen_andi_tl(a, temp_5, 4294967295);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag32(a);
        CarryADD32(temp_6, a, lb, lc);
        setCFlag(temp_6);
        OverflowADD32(temp_7, a, lb, lc);
        setVFlag(temp_7);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(temp_4);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_6);
    tcg_temp_free(temp_7);

    return ret;
}







/* ADC
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, CarryADD32, setVFlag, OverflowADD32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  lc = se32to64 (@c);
  if((cc_flag == true))
    {
      @a = ((lb + lc) + getCFlag ());
      @a = (@a & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarryADD32 (@a, lb, lc));
          setVFlag (OverflowADD32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_ADC (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  se32to64(temp_5, c);
  tcg_gen_mov_tl(lc, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_add_tl(temp_6, lb, lc);
  getCFlag(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_add_tl(a, temp_6, temp_7);
  tcg_gen_andi_tl(a, a, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarryADD32(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setCFlag(temp_9);
  OverflowADD32(temp_12, a, lb, lc);
  tcg_gen_mov_tl(temp_11, temp_12);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* SBC
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  lc = se32to64 (@c);
  if((cc_flag == true))
    {
      @a = ((lb - lc) - getCFlag ());
      @a = (@a & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SBC (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  se32to64(temp_5, c);
  tcg_gen_mov_tl(lc, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_sub_tl(temp_6, lb, lc);
  getCFlag(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_sub_tl(a, temp_6, temp_7);
  tcg_gen_andi_tl(a, a, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarrySUB32(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setCFlag(temp_9);
  OverflowSUB32(temp_12, a, lb, lc);
  tcg_gen_mov_tl(temp_11, temp_12);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}





/* NEG
 *    Variables: @b, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      @a = (0 - @b);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, 0, lb));
          setVFlag (OverflowSUB32 (@a, 0, lb));
        };
    };
}
 */

int
arc_gen_NEG (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_subfi_tl(a, 0, b);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  tcg_gen_movi_tl(temp_7, 0);
  CarrySUB32(temp_6, a, temp_7, lb);
  tcg_gen_mov_tl(temp_5, temp_6);
  setCFlag(temp_5);
  tcg_gen_movi_tl(temp_10, 0);
  OverflowSUB32(temp_9, a, temp_10, lb);
  tcg_gen_mov_tl(temp_8, temp_9);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* SUB
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = se32to64 (@c);
      @a = ((lb - lc) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_5, c);
  tcg_gen_mov_tl(lc, temp_5);
  tcg_gen_sub_tl(temp_6, lb, lc);
  tcg_gen_andi_tl(a, temp_6, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarrySUB32(temp_8, a, lb, lc);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
  OverflowSUB32(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setVFlag(temp_9);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* SUB1
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = (se32to64 (@c) << 1);
      @a = ((lb - lc) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB1 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_6, c);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_shli_tl(lc, temp_5, 1);
  tcg_gen_sub_tl(temp_7, lb, lc);
  tcg_gen_andi_tl(a, temp_7, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarrySUB32(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  OverflowSUB32(temp_11, a, lb, lc);
  tcg_gen_mov_tl(temp_10, temp_11);
  setVFlag(temp_10);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SUB2
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = (se32to64 (@c) << 2);
      @a = ((lb - lc) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB2 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_6, c);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_shli_tl(lc, temp_5, 2);
  tcg_gen_sub_tl(temp_7, lb, lc);
  tcg_gen_andi_tl(a, temp_7, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarrySUB32(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  OverflowSUB32(temp_11, a, lb, lc);
  tcg_gen_mov_tl(temp_10, temp_11);
  setVFlag(temp_10);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* SUB3
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = (se32to64 (@c) << 3);
      @a = ((lb - lc) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB3 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  se32to64(temp_4, b);
  tcg_gen_mov_tl(lb, temp_4);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_6, c);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_shli_tl(lc, temp_5, 3);
  tcg_gen_sub_tl(temp_7, lb, lc);
  tcg_gen_andi_tl(a, temp_7, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  CarrySUB32(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  OverflowSUB32(temp_11, a, lb, lc);
  tcg_gen_mov_tl(temp_10, temp_11);
  setVFlag(temp_10);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_4);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(lc);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* MAX
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = se32to64 (@c);
      alu = (lb - lc);
      if((lc >= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      alu = (alu & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag32 (alu);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_MAX (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  se32to64(temp_6, b);
  tcg_gen_mov_tl(lb, temp_6);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_7, c);
  tcg_gen_mov_tl(lc, temp_7);
  tcg_gen_sub_tl(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, lc, lb);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, lb);
  gen_set_label(done_2);
  tcg_gen_andi_tl(alu, alu, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(alu);
  setNFlag32(alu);
  CarrySUB32(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  OverflowSUB32(temp_11, a, lb, lc);
  tcg_gen_mov_tl(temp_10, temp_11);
  setVFlag(temp_10);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_6);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(lc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* MIN
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64, getFFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  lb = se32to64 (@b);
  if((cc_flag == true))
    {
      lc = se32to64 (@c);
      alu = (lb - lc);
      if((lc <= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      alu = (alu & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag32 (alu);
          setCFlag (CarrySUB32 (@a, lb, lc));
          setVFlag (OverflowSUB32 (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_MIN (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  se32to64(temp_6, b);
  tcg_gen_mov_tl(lb, temp_6);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  se32to64(temp_7, c);
  tcg_gen_mov_tl(lc, temp_7);
  tcg_gen_sub_tl(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LE, temp_3, lc, lb);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, lb);
  gen_set_label(done_2);
  tcg_gen_andi_tl(alu, alu, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(alu);
  setNFlag32(alu);
  CarrySUB32(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  OverflowSUB32(temp_11, a, lb, lc);
  tcg_gen_mov_tl(temp_10, temp_11);
  setVFlag(temp_10);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_6);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(lc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);

  return ret;
}





/* CMP
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag32, setCFlag, CarrySUB32, setVFlag, OverflowSUB32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      v = 4294967295;
      lb = (@b & v);
      lc = (@c & v);
      alu = (lb - lc);
      alu = (alu & 4294967295);
      setZFlag (alu);
      setNFlag32 (alu);
      setCFlag (CarrySUB32 (alu, lb, lc));
      setVFlag (OverflowSUB32 (alu, lb, lc));
    };
}
 */

int
arc_gen_CMP (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv v = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(v, 4294967295);
  tcg_gen_and_tl(lb, b, v);
  tcg_gen_and_tl(lc, c, v);
  tcg_gen_sub_tl(alu, lb, lc);
  tcg_gen_andi_tl(alu, alu, 4294967295);
  setZFlag(alu);
  setNFlag32(alu);
  CarrySUB32(temp_5, alu, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB32(temp_7, alu, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(v);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* AND
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & @c);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_AND (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_tl(a, b, c);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* OR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b | @c);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_OR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_or_tl(a, b, c);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* XOR
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b ^ @c);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_XOR (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_xor_tl(a, b, c);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* MOV
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = @b;
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_MOV (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(a, b);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* ASL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, getBit, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      lc = (@c & 31);
      la = (lb << lc);
      la = (la & 4294967295);
      @a = la;
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (32 - lc)));
            };
          if((@c == 268435457))
            {
              t1 = getBit (la, 31);
              t2 = getBit (lb, 31);
              if((t1 == t2))
                {
                  setVFlag (0);
                }
              else
                {
                  setVFlag (1);
                };
            };
        };
    };
}
 */

int
arc_gen_ASL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv la = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_15 = tcg_temp_local_new();
  TCGv temp_14 = tcg_temp_local_new();
  TCGv t1 = tcg_temp_local_new();
  TCGv temp_17 = tcg_temp_local_new();
  TCGv temp_16 = tcg_temp_local_new();
  TCGv t2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_18 = tcg_temp_local_new();
  TCGv temp_19 = tcg_temp_local_new();
  getCCFlag(temp_9);
  tcg_gen_mov_tl(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_andi_tl(lc, c, 31);
  tcg_gen_shl_tl(la, lb, lc);
  tcg_gen_andi_tl(la, la, 4294967295);
  tcg_gen_mov_tl(a, la);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_10, 0);
  setCFlag(temp_10);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subfi_tl(temp_13, 32, lc);
  getBit(temp_12, lb, temp_13);
  tcg_gen_mov_tl(temp_11, temp_12);
  setCFlag(temp_11);
  gen_set_label(done_2);
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_5, c, 268435457);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, done_3);;
  tcg_gen_movi_tl(temp_15, 31);
  getBit(temp_14, la, temp_15);
  tcg_gen_mov_tl(t1, temp_14);
  tcg_gen_movi_tl(temp_17, 31);
  getBit(temp_16, lb, temp_17);
  tcg_gen_mov_tl(t2, temp_16);
  TCGLabel *else_4 = gen_new_label();
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_7, t1, t2);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, else_4);;
  tcg_gen_movi_tl(temp_18, 0);
  setVFlag(temp_18);
  tcg_gen_br(done_4);
  gen_set_label(else_4);
  tcg_gen_movi_tl(temp_19, 1);
  setVFlag(temp_19);
  gen_set_label(done_4);
  gen_set_label(done_3);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(la);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_15);
  tcg_temp_free(temp_14);
  tcg_temp_free(t1);
  tcg_temp_free(temp_17);
  tcg_temp_free(temp_16);
  tcg_temp_free(t2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_18);
  tcg_temp_free(temp_19);

  return ret;
}





/* ASR
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, arithmeticShiftRight32, getFFlag, setZFlag, setNFlag32, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      lc = (@c & 31);
      @a = arithmeticShiftRight32 (lb, lc);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc_gen_ASR (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_andi_tl(lc, c, 31);
  arithmeticShiftRight32(temp_6, lb, lc);
  tcg_gen_mov_tl(a, temp_6);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subi_tl(temp_10, lc, 1);
  getBit(temp_9, lb, temp_10);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* ASR8
 *    Variables: @b, @a
 *    Functions: getCCFlag, arithmeticShiftRight32, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = arithmeticShiftRight32 (lb, 8);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_ASR8 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 8);
  arithmeticShiftRight32(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* ASR16
 *    Variables: @b, @a
 *    Functions: getCCFlag, arithmeticShiftRight32, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = arithmeticShiftRight32 (lb, 16);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_ASR16 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 16);
  arithmeticShiftRight32(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSL16
 *    Variables: @b, @a
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = logicalShiftLeft (lb, 16);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_LSL16 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 16);
  logicalShiftLeft(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSL8
 *    Variables: @b, @a
 *    Functions: getCCFlag, logicalShiftLeft, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = logicalShiftLeft (lb, 8);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_LSL8 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 8);
  logicalShiftLeft(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSR
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag32, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      lc = (@c & 31);
      @a = logicalShiftRight (lb, lc);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc_gen_LSR (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_andi_tl(lc, c, 31);
  logicalShiftRight(temp_6, lb, lc);
  tcg_gen_mov_tl(a, temp_6);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subi_tl(temp_10, lc, 1);
  getBit(temp_9, lb, temp_10);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* LSR16
 *    Variables: @b, @a
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = logicalShiftRight (lb, 16);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_LSR16 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 16);
  logicalShiftRight(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LSR8
 *    Variables: @b, @a
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = (@b & 4294967295);
      @a = logicalShiftRight (lb, 8);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_LSR8 (DisasCtxt *ctx, TCGv b, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lb, b, 4294967295);
  tcg_gen_movi_tl(temp_5, 8);
  logicalShiftRight(temp_4, lb, temp_5);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* BIC
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & ~@c);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BIC (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_not_tl(temp_4, c);
  tcg_gen_and_tl(a, b, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);

  return ret;
}





/* BCLR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      @a = (@b & ~tmp);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BCLR (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 31);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_not_tl(temp_5, tmp);
  tcg_gen_and_tl(a, b, temp_5);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_5);

  return ret;
}





/* BMSK
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 31) + 1);
      if((tmp1 == 32))
        {
          tmp2 = 0xffffffff;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & tmp2);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BMSK (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_6, c, 31);
  tcg_gen_addi_tl(tmp1, temp_6, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, tmp1, 32);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(tmp2, 0xffffffff);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_tl(temp_7, 1, tmp1);
  tcg_gen_subi_tl(tmp2, temp_7, 1);
  gen_set_label(done_2);
  tcg_gen_and_tl(a, b, tmp2);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_7);

  return ret;
}





/* BMSKN
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 31) + 1);
      if((tmp1 == 32))
        {
          tmp2 = 0xffffffff;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & ~tmp2);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BMSKN (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_6, c, 31);
  tcg_gen_addi_tl(tmp1, temp_6, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, tmp1, 32);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(tmp2, 0xffffffff);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_tl(temp_7, 1, tmp1);
  tcg_gen_subi_tl(tmp2, temp_7, 1);
  gen_set_label(done_2);
  tcg_gen_not_tl(temp_8, tmp2);
  tcg_gen_and_tl(a, b, temp_8);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* BSET
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      @a = (@b | tmp);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BSET (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 31);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_or_tl(a, b, tmp);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);

  return ret;
}





/* BXOR
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << @c);
      @a = (@b ^ tmp);
      f_flag = getFFlag ();
      @a = (@a & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
        };
    };
}
 */

int
arc_gen_BXOR (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shlfi_tl(tmp, 1, c);
  tcg_gen_xor_tl(a, b, tmp);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag32(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(tmp);

  return ret;
}





/* ROL
 *    Variables: @src, @n, @dest
 *    Functions: getCCFlag, rotateLeft32, getFFlag, setZFlag, setNFlag32, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      ln = (@n & 31);
      @dest = rotateLeft32 (lsrc, ln);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
          setCFlag (extractBits (lsrc, 31, 31));
        };
    };
}
 */

int
arc_gen_ROL (DisasCtxt *ctx, TCGv src, TCGv n, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv ln = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_andi_tl(ln, n, 31);
  rotateLeft32(temp_4, lsrc, ln);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_movi_tl(temp_8, 31);
  tcg_gen_movi_tl(temp_7, 31);
  extractBits(temp_6, lsrc, temp_7, temp_8);
  tcg_gen_mov_tl(temp_5, temp_6);
  setCFlag(temp_5);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(ln);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);

  return ret;
}





/* ROL8
 *    Variables: @src, @dest
 *    Functions: getCCFlag, rotateLeft32, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      @dest = rotateLeft32 (lsrc, 8);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_ROL8 (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_movi_tl(temp_5, 8);
  rotateLeft32(temp_4, lsrc, temp_5);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* ROR
 *    Variables: @src, @n, @dest
 *    Functions: getCCFlag, rotateRight32, getFFlag, setZFlag, setNFlag32, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      ln = (@n & 31);
      @dest = rotateRight32 (lsrc, ln);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
          setCFlag (extractBits (lsrc, (ln - 1), (ln - 1)));
        };
    };
}
 */

int
arc_gen_ROR (DisasCtxt *ctx, TCGv src, TCGv n, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv ln = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_andi_tl(ln, n, 31);
  rotateRight32(temp_4, lsrc, ln);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_subi_tl(temp_8, ln, 1);
  tcg_gen_subi_tl(temp_7, ln, 1);
  extractBits(temp_6, lsrc, temp_7, temp_8);
  tcg_gen_mov_tl(temp_5, temp_6);
  setCFlag(temp_5);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(ln);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);

  return ret;
}





/* ROR8
 *    Variables: @src, @dest
 *    Functions: getCCFlag, rotateRight32, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      @dest = rotateRight32 (lsrc, 8);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_ROR8 (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_movi_tl(temp_5, 8);
  rotateRight32(temp_4, lsrc, temp_5);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* RLC
 *    Variables: @src, @dest
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      @dest = (lsrc << 1);
      @dest = (@dest | getCFlag ());
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
          setCFlag (extractBits (lsrc, 31, 31));
        };
    };
}
 */

int
arc_gen_RLC (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_shli_tl(dest, lsrc, 1);
  getCFlag(temp_5);
  tcg_gen_mov_tl(temp_4, temp_5);
  tcg_gen_or_tl(dest, dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_movi_tl(temp_9, 31);
  tcg_gen_movi_tl(temp_8, 31);
  extractBits(temp_7, lsrc, temp_8, temp_9);
  tcg_gen_mov_tl(temp_6, temp_7);
  setCFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* RRC
 *    Variables: @src, @dest
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag32, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = (@src & 4294967295);
      @dest = (lsrc >> 1);
      @dest = (@dest | (getCFlag () << 31));
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
          setCFlag (extractBits (lsrc, 0, 0));
        };
    };
}
 */

int
arc_gen_RRC (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(lsrc, src, 4294967295);
  tcg_gen_shri_tl(dest, lsrc, 1);
  getCFlag(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_shli_tl(temp_4, temp_5, 31);
  tcg_gen_or_tl(dest, dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_movi_tl(temp_10, 0);
  tcg_gen_movi_tl(temp_9, 0);
  extractBits(temp_8, lsrc, temp_9, temp_10);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);

  return ret;
}





/* SEXB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 56), 56);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_SEXB (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 56);
  tcg_gen_shli_tl(temp_5, src, 56);
  arithmeticShiftRight(temp_4, temp_5, temp_6);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
    setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* SEXH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 48), 48);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_SEXH (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 48);
  tcg_gen_shli_tl(temp_5, src, 48);
  arithmeticShiftRight(temp_4, temp_5, temp_6);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* EXTB
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = (@src & 255);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_EXTB (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(dest, src, 255);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* EXTH
 *    Variables: @dest, @src
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = (@src & 65535);
      f_flag = getFFlag ();
      @dest = (@dest & 4294967295);
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag32 (@dest);
        };
    };
}
 */

int
arc_gen_EXTH (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(dest, src, 65535);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* BTST
 *    Variables: @c, @b
 *    Functions: getCCFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 31));
      alu = (@b & tmp);
      alu = (alu & 4294967295);
      setZFlag (alu);
      setNFlag32 (alu);
    };
}
 */

int
arc_gen_BTST (DisasCtxt *ctx, TCGv c, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 31);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_and_tl(alu, b, tmp);
  tcg_gen_andi_tl(alu, alu, 4294967295);
  setZFlag(alu);
  setNFlag32(alu);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);
  tcg_temp_free(alu);

  return ret;
}





/* TST
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag32
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      alu = (@b & @c);
      alu = (alu & 4294967295);
      setZFlag (alu);
      setNFlag32 (alu);
    };
}
 */

int
arc_gen_TST (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_tl(alu, b, c);
  tcg_gen_andi_tl(alu, alu, 4294967295);
  setZFlag(alu);
  setNFlag32(alu);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);

  return ret;
}





/* XBFU
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, extractBits, getFFlag, setZFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      N = extractBits (@src2, 4, 0);
      M = (extractBits (@src2, 9, 5) + 1);
      tmp1 = (@src1 >> N);
      tmp2 = ((1 << M) - 1);
      @dest = (tmp1 & tmp2);
      @dest = (@dest & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
        };
    };
}
 */

int
arc_gen_XBFU (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv N = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv M = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 0);
  tcg_gen_movi_tl(temp_5, 4);
  extractBits(temp_4, src2, temp_5, temp_6);
  tcg_gen_mov_tl(N, temp_4);
  tcg_gen_movi_tl(temp_10, 5);
  tcg_gen_movi_tl(temp_9, 9);
  extractBits(temp_8, src2, temp_9, temp_10);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_addi_tl(M, temp_7, 1);
  tcg_gen_shr_tl(tmp1, src1, N);
  tcg_gen_shlfi_tl(temp_11, 1, M);
  tcg_gen_subi_tl(tmp2, temp_11, 1);
  tcg_gen_and_tl(dest, tmp1, tmp2);
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(N);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(M);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_11);
  tcg_temp_free(tmp2);

  return ret;
}





/* AEX
 *    Variables: @src2, @b
 *    Functions: getCCFlag, readAuxReg, writeAuxReg
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = readAuxReg (@src2);
      writeAuxReg (@src2, @b);
      @b = tmp;
    };
}
 */

int
arc_gen_AEX (DisasCtxt *ctx, TCGv src2, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  readAuxReg(temp_4, src2);
  tcg_gen_mov_tl(tmp, temp_4);
  writeAuxReg(src2, b);
  tcg_gen_mov_tl(b, tmp);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);

  return ret;
}





/* LR
 *    Variables: @dest, @src
 *    Functions: readAuxReg
--- code ---
{
  @dest = readAuxReg (@src);
}
 */

int
arc_gen_LR (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NORETURN;

  if (tb_cflags(ctx->base.tb) & CF_USE_ICOUNT) {
      gen_io_start();
  }

  TCGv temp_1 = tcg_temp_local_new();
  readAuxReg(temp_1, src);
  tcg_gen_andi_tl(temp_1, temp_1, 0xffffffff);
  tcg_gen_mov_tl(dest, temp_1);
  tcg_temp_free(temp_1);

  return ret;
}





/* CLRI
 *    Variables: @c
 *    Functions: getRegister, setRegister, inKernelMode
--- code ---
{
  in_kernel_mode = inKernelMode();
  if(in_kernel_mode != 1)
    {
      throwExcpPriviledgeV();
    }
  status32 = getRegister (R_STATUS32);
  ie = (status32 & 2147483648);
  ie = (ie >> 27);
  e = ((status32 & 30) >> 1);
  a = 32;
  @c = ((ie | e) | a);
  mask = 2147483648;
  mask = ~mask;
  status32 = (status32 & mask);
  setRegister (R_STATUS32, status32);
}
 */

int
arc_gen_CLRI (DisasCtxt *ctx, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_1 = tcg_temp_local_new();
  TCGv status32 = tcg_temp_local_new();
  TCGv ie = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv e = tcg_temp_local_new();
  TCGv a = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv mask = tcg_temp_local_new();
  TCGv in_kernel_mode = tcg_temp_local_new();
  inKernelMode(in_kernel_mode);
  TCGLabel *done_in_kernel_mode = gen_new_label();
  tcg_gen_brcondi_tl(TCG_COND_EQ, in_kernel_mode, 1, done_in_kernel_mode);
  throwExcpPriviledgeV();
  gen_set_label(done_in_kernel_mode);
  getRegister(temp_1, R_STATUS32);
  tcg_gen_mov_tl(status32, temp_1);
  tcg_gen_andi_tl(ie, status32, 2147483648);
  tcg_gen_shri_tl(ie, ie, 27);
  tcg_gen_andi_tl(temp_2, status32, 30);
  tcg_gen_shri_tl(e, temp_2, 1);
  tcg_gen_movi_tl(a, 32);
  tcg_gen_or_tl(temp_3, ie, e);
  tcg_gen_or_tl(c, temp_3, a);
  tcg_gen_movi_tl(mask, 2147483648);
  tcg_gen_not_tl(mask, mask);
  tcg_gen_and_tl(status32, status32, mask);
  setRegister(R_STATUS32, status32);
  tcg_temp_free(temp_1);
  tcg_temp_free(status32);
  tcg_temp_free(ie);
  tcg_temp_free(temp_2);
  tcg_temp_free(e);
  tcg_temp_free(a);
  tcg_temp_free(temp_3);
  tcg_temp_free(mask);
  tcg_temp_free(in_kernel_mode);

  return ret;
}





/* SETI
 *    Variables: @c
 *    Functions: getRegister, setRegister, inKernelMode
--- code ---
{
  in_kernel_mode = inKernelMode();
  if(in_kernel_mode != 1)
    {
      throwExcpPriviledgeV();
    }
  status32 = getRegister (R_STATUS32);
  if((temp1 != 0))
    {
      status32 = ((status32 & e_mask) | e_value);
      ie_mask = 2147483648;
      ie_mask = ~ie_mask;
      ie_value = ((@c & 16) << 27);
      status32 = ((status32 & ie_mask) | ie_value);
    }
  else
    {
      status32 = (status32 | 2147483648);
      temp2 = (@c & 16);
      if((temp2 != 0))
        {
          status32 = ((status32 & e_mask) | e_value);
        };
    };
  setRegister (R_STATUS32, status32);
}
 */

int
arc_gen_SETI (DisasCtxt *ctx, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv status32 = tcg_temp_local_new();
  TCGv e_mask = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv e_value = tcg_temp_local_new();
  TCGv temp1 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv ie_mask = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv ie_value = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv in_kernel_mode = tcg_temp_local_new();
  inKernelMode(in_kernel_mode);
  TCGLabel *done_in_kernel_mode = gen_new_label();
  tcg_gen_brcondi_tl(TCG_COND_EQ, in_kernel_mode, 1, done_in_kernel_mode);
  throwExcpPriviledgeV();
  gen_set_label(done_in_kernel_mode);
  getRegister(temp_5, R_STATUS32);
  tcg_gen_mov_tl(status32, temp_5);
  tcg_gen_movi_tl(e_mask, 30);
  tcg_gen_not_tl(e_mask, e_mask);
  tcg_gen_andi_tl(temp_6, c, 15);
  tcg_gen_shli_tl(e_value, temp_6, 1);
  tcg_gen_andi_tl(temp1, c, 32);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_1, temp1, 0);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_and_tl(temp_7, status32, e_mask);
  tcg_gen_or_tl(status32, temp_7, e_value);
  tcg_gen_movi_tl(ie_mask, 2147483648);
  tcg_gen_not_tl(ie_mask, ie_mask);
  tcg_gen_andi_tl(temp_8, c, 16);
  tcg_gen_shli_tl(ie_value, temp_8, 27);
  tcg_gen_and_tl(temp_9, status32, ie_mask);
  tcg_gen_or_tl(status32, temp_9, ie_value);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_ori_tl(status32, status32, 2147483648);
  tcg_gen_andi_tl(temp2, c, 16);
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, temp2, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, done_2);;
  tcg_gen_and_tl(temp_10, status32, e_mask);
  tcg_gen_or_tl(status32, temp_10, e_value);
  gen_set_label(done_2);
  gen_set_label(done_1);
  setRegister(R_STATUS32, status32);
  tcg_temp_free(temp_5);
  tcg_temp_free(status32);
  tcg_temp_free(e_mask);
  tcg_temp_free(temp_6);
  tcg_temp_free(e_value);
  tcg_temp_free(temp1);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(ie_mask);
  tcg_temp_free(temp_8);
  tcg_temp_free(ie_value);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_10);
  tcg_temp_free(in_kernel_mode);

  return ret;
}





/* NOP
 *    Variables:
 *    Functions: doNothing
--- code ---
{
  doNothing ();
}
 */

int
arc_gen_NOP (DisasCtxt *ctx)
{
  int ret = DISAS_NEXT;

  return ret;
}





/* PREALLOC
 *    Variables:
 *    Functions: doNothing
--- code ---
{
  doNothing ();
}
 */

int
arc_gen_PREALLOC (DisasCtxt *ctx)
{
  int ret = DISAS_NEXT;

  return ret;
}





/* PREFETCH
 *    Variables: @src1, @src2
 *    Functions: getAAFlag, doNothing
--- code ---
{
  AA = getAAFlag ();
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    }
  else
    {
      doNothing ();
    };
}
 */

int
arc_gen_PREFETCH (DisasCtxt *ctx, TCGv src1, TCGv src2)
{
  int ret = DISAS_NEXT;
  int AA;
  AA = getAAFlag ();
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_tl(src1, src1, src2);
;
    }
  else
    {
    doNothing();
;
    }

  return ret;
}





/* MPY
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, HELPER, setZFlag, setNFlag32, setVFlag
 *  HAND_TUNED FUNCTION - not really optimized yet
 */

int
arc_gen_MPY(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv _b = tcg_temp_local_new();
    TCGv _c = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv high_part = tcg_temp_local_new();
    TCGv tmp1 = tcg_temp_local_new();
    TCGv tmp2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_andi_tl(_b, b, 0xffffffff);
    tcg_gen_andi_tl(_c, c, 0xffffffff);
    tcg_gen_ext32s_tl(_b, _b);
    tcg_gen_ext32s_tl(_c, _c);
    tcg_gen_mul_tl(temp_4, _b, _c);
    tcg_gen_andi_tl(a, temp_4, 4294967295);
    if ((getFFlag () == true)) {
	tcg_gen_sari_tl(high_part, temp_4, 32);
        tcg_gen_sari_tl(tmp2, temp_4, 31);
        setZFlag(a);
        setNFlag(high_part);
        tcg_gen_setcond_tl(TCG_COND_NE, temp_5, high_part, tmp2);
        setVFlag(temp_5);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(_b);
    tcg_temp_free(_c);
    tcg_temp_free(temp_4);
    tcg_temp_free(high_part);
    tcg_temp_free(tmp1);
    tcg_temp_free(tmp2);
    tcg_temp_free(temp_5);

    return ret;
}





/* MPYMU
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, HELPER, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = HELPER (mpymu, @b, @c);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (0);
          setVFlag (0);
        };
    };
}
 */

int
arc_gen_MPYMU (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  ARC_HELPER(mpymu, a, b, c);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  tcg_gen_movi_tl(temp_4, 0);
  setNFlag32(temp_4);
  tcg_gen_movi_tl(temp_5, 0);
  setVFlag(temp_5);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);

  return ret;
}





/* MPYM
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, HELPER, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = HELPER (mpym, @b, @c);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setVFlag (0);
        };
    };
}
 */

int
arc_gen_MPYM (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  ARC_HELPER(mpym, a, b, c);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  tcg_gen_movi_tl(temp_4, 0);
  setVFlag(temp_4);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);

  return ret;
}





/* MPYU
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, HELPER, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      _b = @b;
      _c = @c;
      @a = ((_b * _c) & 4294967295);
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          high_part = HELPER (mpymu, _b, _c);
          setZFlag (@a);
          setNFlag32 (0);
          setVFlag ((high_part != 0));
        };
    };
}
 */

int
arc_gen_MPYU (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv _b = tcg_temp_local_new();
  TCGv _c = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv high_part = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(_b, b);
  tcg_gen_mov_tl(_c, c);
  tcg_gen_mul_tl(temp_4, _b, _c);
  tcg_gen_andi_tl(a, temp_4, 4294967295);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    ARC_HELPER(mpym, high_part, _b, _c);
  setZFlag(a);
  tcg_gen_movi_tl(temp_5, 0);
  setNFlag32(temp_5);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_6, high_part, 0);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(_b);
  tcg_temp_free(_c);
  tcg_temp_free(temp_4);
  tcg_temp_free(high_part);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* MPYUW
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = ((@b & 65535) * (@c & 65535));
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (0);
          setVFlag (0);
        };
    };
}
 */

int
arc_gen_MPYUW (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_5, c, 65535);
  tcg_gen_andi_tl(temp_4, b, 65535);
  tcg_gen_mul_tl(a, temp_4, temp_5);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  tcg_gen_movi_tl(temp_6, 0);
  setNFlag32(temp_6);
  tcg_gen_movi_tl(temp_7, 0);
  setVFlag(temp_7);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);

  return ret;
}





/* MPYW
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (arithmeticShiftRight ((@b << 48), 48) * arithmeticShiftRight ((@c << 48), 48));
      @a = (@a & 4294967295);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag32 (@a);
          setVFlag (0);
        };
    };
}
 */

int
arc_gen_MPYW (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_11, 48);
  tcg_gen_shli_tl(temp_10, c, 48);
  tcg_gen_movi_tl(temp_7, 48);
  tcg_gen_shli_tl(temp_6, b, 48);
  arithmeticShiftRight(temp_5, temp_6, temp_7);
  tcg_gen_mov_tl(temp_4, temp_5);
  arithmeticShiftRight(temp_9, temp_10, temp_11);
  tcg_gen_mov_tl(temp_8, temp_9);
  tcg_gen_mul_tl(a, temp_4, temp_8);
  tcg_gen_andi_tl(a, a, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag32(a);
  tcg_gen_movi_tl(temp_12, 0);
  setVFlag(temp_12);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_12);

  return ret;
}





/* DIV
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divSigned32, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divSigned32 (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag32 (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_DIV (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_9);
  tcg_gen_mov_tl(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_tl(temp_6, temp_4, temp_5);
  tcg_gen_and_tl(temp_7, temp_3, temp_6);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, else_2);;
  divSigned32(temp_10, src1, src2);
  tcg_gen_mov_tl(dest, temp_10);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_movi_tl(temp_11, 0);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* DIVU
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divUnsigned32, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divUnsigned32 (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag32 (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_DIVU (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  divUnsigned32(temp_6, src1, src2);
  tcg_gen_mov_tl(dest, temp_6);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  tcg_gen_movi_tl(temp_7, 0);
  setNFlag32(temp_7);
  tcg_gen_movi_tl(temp_8, 0);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* REM
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divRemainingSigned32, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divRemainingSigned32 (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag32 (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_REM (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_9);
  tcg_gen_mov_tl(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_tl(temp_6, temp_4, temp_5);
  tcg_gen_and_tl(temp_7, temp_3, temp_6);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, else_2);;
  divRemainingSigned32(temp_10, src1, src2);
  tcg_gen_mov_tl(dest, temp_10);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_movi_tl(temp_11, 0);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* REMU
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divRemainingUnsigned32, getFFlag, setZFlag, setNFlag32, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divRemainingUnsigned32 (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag32 (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_REMU (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  divRemainingUnsigned32(temp_6, src1, src2);
  tcg_gen_mov_tl(dest, temp_6);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  tcg_gen_movi_tl(temp_7, 0);
  setNFlag32(temp_7);
  tcg_gen_movi_tl(temp_8, 0);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}

static void
arc_gen_mac_op_i64(TCGv mul_bc, TCGv a, TCGv b, TCGv c,
                   void (*OP)(TCGv, TCGv,
                              unsigned int ofs,
                              unsigned int len),
                   int w0)
{
    TCGv b_w0, c_w0;

    b_w0 = tcg_temp_new();
    c_w0 = tcg_temp_new();

    OP(b_w0, b, 0, 32);
    OP(c_w0, c, 0, 32);
    tcg_gen_mul_tl(mul_bc, b_w0, c_w0);
    tcg_gen_add_tl(cpu64_acc, cpu64_acc, mul_bc);
    tcg_gen_mov_tl(a, cpu64_acc);
    if (w0)             
      tcg_gen_andi_tl(a, a, 0xffffffffull);

    tcg_temp_free(c_w0);
    tcg_temp_free(b_w0);
}

/*
 * MAC - CODED BY HAND
 */

int
arc_gen_MAC(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    TCGv old_acc, mul_bc;

    TCGv cc_temp = tcg_temp_local_new();
    TCGLabel *cc_done = gen_new_label();

    /* Conditional execution */
    getCCFlag(cc_temp);
    tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

    old_acc = tcg_temp_new();
    mul_bc = tcg_temp_new();

    tcg_gen_mov_tl(old_acc, cpu64_acc);
    arc_gen_mac_op_i64(mul_bc, a, b, c,
                       tcg_gen_sextract_tl, TRUE);
    
    if (getFFlag()) { // F flag is set, affect the flags
        TCGLabel *vf_done = gen_new_label();
        TCGv vf_temp = tcg_temp_new();

        setNFlag(cpu64_acc);

        tcg_gen_mov_tl(vf_temp, cpu_Vf);
        OverflowADD(cpu_Vf, cpu64_acc, old_acc, mul_bc);        
        tcg_gen_brcondi_tl(TCG_COND_EQ, vf_temp, 0, vf_done);
        tcg_gen_movi_tl(cpu_Vf, 1);
        gen_set_label(vf_done);

        tcg_temp_free(vf_temp);
    }

    tcg_temp_free(mul_bc);
    tcg_temp_free(old_acc);

    /* Conditional execution end. */
    gen_set_label(cc_done);
    tcg_temp_free(cc_temp);

    return DISAS_NEXT;
}

/*
 * MACU - CODED BY HAND
 */

int
arc_gen_MACU(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    TCGv old_acc, mul_bc;

    TCGv cc_temp = tcg_temp_local_new();
    TCGLabel *cc_done = gen_new_label();

    /* Conditional execution */
    getCCFlag(cc_temp);
    tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

    old_acc = tcg_temp_new();
    mul_bc = tcg_temp_new();

    tcg_gen_mov_tl(old_acc, cpu64_acc);
    arc_gen_mac_op_i64(mul_bc, a, b, c,
                       tcg_gen_extract_tl, TRUE);
    
    if (getFFlag()) { // F flag is set, affect the flags
        TCGLabel *vf_done = gen_new_label();
        TCGv vf_temp = tcg_temp_new();

        tcg_gen_mov_tl(vf_temp, cpu_Vf);
        CarryADD(cpu_Vf, cpu64_acc, old_acc, mul_bc);
        tcg_gen_brcondi_tl(TCG_COND_EQ, vf_temp, 0, vf_done);
        tcg_gen_movi_tl(cpu_Vf, 1);
        gen_set_label(vf_done);

        tcg_temp_free(vf_temp);
    }

    tcg_temp_free(mul_bc);
    tcg_temp_free(old_acc);

    /* Conditional execution end. */
    gen_set_label(cc_done);
    tcg_temp_free(cc_temp);

    return DISAS_NEXT;
}

/*
 * MACD - CODED BY HAND
 */

int
arc_gen_MACD(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    TCGv old_acc, mul_bc;

    TCGv cc_temp = tcg_temp_local_new();
    TCGLabel *cc_done = gen_new_label();

    /* Conditional execution */
    getCCFlag(cc_temp);
    tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

    old_acc = tcg_temp_new();
    mul_bc = tcg_temp_new();

    tcg_gen_mov_tl(old_acc, cpu64_acc);
    arc_gen_mac_op_i64(mul_bc, a, b, c,
                       tcg_gen_sextract_tl, FALSE);
    
    if (getFFlag()) { // F flag is set, affect the flags
        TCGLabel *vf_done = gen_new_label();
        TCGv vf_temp = tcg_temp_new();

        setNFlag(cpu64_acc);

        tcg_gen_mov_tl(vf_temp, cpu_Vf);
        OverflowADD(cpu_Vf, cpu64_acc, old_acc, mul_bc);        
        tcg_gen_brcondi_tl(TCG_COND_EQ, vf_temp, 0, vf_done);
        tcg_gen_movi_tl(cpu_Vf, 1);
        gen_set_label(vf_done);

        tcg_temp_free(vf_temp);
    }

    tcg_temp_free(mul_bc);
    tcg_temp_free(old_acc);

    /* Conditional execution end. */
    gen_set_label(cc_done);
    tcg_temp_free(cc_temp);

    return DISAS_NEXT;
}

/*
 * MACDU - CODED BY HAND
 */

int
arc_gen_MACDU(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    TCGv old_acc, mul_bc;

    TCGv cc_temp = tcg_temp_local_new();
    TCGLabel *cc_done = gen_new_label();

    /* Conditional execution */
    getCCFlag(cc_temp);
    tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

    old_acc = tcg_temp_new();
    mul_bc = tcg_temp_new();

    tcg_gen_mov_tl(old_acc, cpu64_acc);
    arc_gen_mac_op_i64(mul_bc, a, b, c,
                       tcg_gen_extract_tl, FALSE);
    
    if (getFFlag()) { // F flag is set, affect the flags
        TCGLabel *vf_done = gen_new_label();
        TCGv vf_temp = tcg_temp_new();

        tcg_gen_mov_tl(vf_temp, cpu_Vf);
        CarryADD(cpu_Vf, cpu64_acc, old_acc, mul_bc);
        tcg_gen_brcondi_tl(TCG_COND_EQ, vf_temp, 0, vf_done);
        tcg_gen_movi_tl(cpu_Vf, 1);
        gen_set_label(vf_done);

        tcg_temp_free(vf_temp);
    }

    tcg_temp_free(mul_bc);
    tcg_temp_free(old_acc);

    /* Conditional execution end. */
    gen_set_label(cc_done);
    tcg_temp_free(cc_temp);

    return DISAS_NEXT;
}

/* ABS
 *    Variables: @src, @dest
 *    Functions: se32to64, Carry32, getFFlag, setZFlag, setNFlag32, setCFlag, Zero, setVFlag, getNFlag
--- code ---
{
  lsrc = se32to64 (@src);
  alu = (0 - lsrc);
  if((Carry32 (lsrc) == 1))
    {
      @dest = alu;
    }
  else
    {
      @dest = lsrc;
    };
  @dest = (@dest & 4294967295);
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag32 (@dest);
      setCFlag (Zero ());
      setVFlag (getNFlag ());
    };
}
 */

int
arc_gen_ABS (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  se32to64(temp_3, src);
  tcg_gen_mov_tl(lsrc, temp_3);
  tcg_gen_subfi_tl(alu, 0, lsrc);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  Carry32(temp_4, lsrc);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, temp_4, 1);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_tl(dest, lsrc);
  gen_set_label(done_1);
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
  tcg_gen_mov_tl(temp_5, Zero());
  setCFlag(temp_5);
  tcg_gen_mov_tl(temp_6, getNFlag());
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(temp_3);
  tcg_temp_free(lsrc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* SWAP
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag32
--- code ---
{
  tmp1 = (@src << 16);
  tmp2 = ((@src >> 16) & 65535);
  @dest = (tmp1 | tmp2);
  f_flag = getFFlag ();
  @dest = (@dest & 4294967295);
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag32 (@dest);
    };
}
 */

int
arc_gen_SWAP (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  int f_flag;
  tcg_gen_shli_tl(tmp1, src, 16);
  tcg_gen_shri_tl(temp_1, src, 16);
  tcg_gen_andi_tl(tmp2, temp_1, 65535);
  tcg_gen_or_tl(dest, tmp1, tmp2);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_1);
  tcg_temp_free(tmp2);

  return ret;
}





/* SWAPE
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag32
--- code ---
{
  tmp1 = ((@src << 24) & 4278190080);
  tmp2 = ((@src << 8) & 16711680);
  tmp3 = ((@src >> 8) & 65280);
  tmp4 = ((@src >> 24) & 255);
  @dest = (((tmp1 | tmp2) | tmp3) | tmp4);
  f_flag = getFFlag ();
  @dest = (@dest & 4294967295);
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag32 (@dest);
    };
}
 */

int
arc_gen_SWAPE (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_1 = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv tmp3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  int f_flag;
  tcg_gen_shli_tl(temp_1, src, 24);
  tcg_gen_andi_tl(tmp1, temp_1, 4278190080);
  tcg_gen_shli_tl(temp_2, src, 8);
  tcg_gen_andi_tl(tmp2, temp_2, 16711680);
  tcg_gen_shri_tl(temp_3, src, 8);
  tcg_gen_andi_tl(tmp3, temp_3, 65280);
  tcg_gen_shri_tl(temp_4, src, 24);
  tcg_gen_andi_tl(tmp4, temp_4, 255);
  tcg_gen_or_tl(temp_6, tmp1, tmp2);
  tcg_gen_or_tl(temp_5, temp_6, tmp3);
  tcg_gen_or_tl(dest, temp_5, tmp4);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(temp_1);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_2);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_3);
  tcg_temp_free(tmp3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);

  return ret;
}





/* NOT
 *    Variables: @dest, @src
 *    Functions: getFFlag, setZFlag, setNFlag32
--- code ---
{
  @dest = ~@src;
  f_flag = getFFlag ();
  @dest = (@dest & 4294967295);
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag32 (@dest);
    };
}
 */

int
arc_gen_NOT (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  int f_flag;
  tcg_gen_not_tl(dest, src);
  f_flag = getFFlag ();
  tcg_gen_andi_tl(dest, dest, 4294967295);
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag32(dest);
;
    }
  else
    {
  ;
    }

  return ret;
}





/* BI
 *    Variables: @c
 *    Functions: setPC, nextInsnAddress
--- code ---
{
  setPC ((nextInsnAddress () + (@c << 2)));
}
 */

int
arc_gen_BI (DisasCtxt *ctx, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  tcg_gen_shli_tl(temp_4, c, 2);
  nextInsnAddress(temp_3);
  tcg_gen_mov_tl(temp_2, temp_3);
  tcg_gen_add_tl(temp_1, temp_2, temp_4);
  setPC(temp_1);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* BIH
 *    Variables: @c
 *    Functions: setPC, nextInsnAddress
--- code ---
{
  setPC ((nextInsnAddress () + (@c << 1)));
}
 */

int
arc_gen_BIH (DisasCtxt *ctx, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  tcg_gen_shli_tl(temp_4, c, 1);
  nextInsnAddress(temp_3);
  tcg_gen_mov_tl(temp_2, temp_3);
  tcg_gen_add_tl(temp_1, temp_2, temp_4);
  setPC(temp_1);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);

  return ret;
}





/* B
 *    Variables: @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      take_branch = true;
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      setPC (bta);
    };
}
 */

int
arc_gen_B (DisasCtxt *ctx, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_1);
  getPCL(temp_7);
  tcg_gen_mov_tl(temp_6, temp_7);
  tcg_gen_add_tl(bta, temp_6, rd);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setPC(bta);
  gen_set_label(done_2);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BBIT0
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  p_b = @b;
  p_c = (@c & 31);
  tmp = (1 << p_c);
  if((cc_flag == true))
    {
      if(((p_b && tmp) == 0))
        {
          take_branch = true;
        };
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      if(((p_b && tmp) == 0))
        {
          setPC (bta);
        };
    };
}
 */

int
arc_gen_BBIT0 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_11);
  tcg_gen_mov_tl(cc_flag, temp_11);
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_andi_tl(p_c, c, 31);
  tcg_gen_shlfi_tl(tmp, 1, p_c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_tl(temp_3, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_4, temp_3, 0);
  tcg_gen_xori_tl(temp_5, temp_4, 1); tcg_gen_andi_tl(temp_5, temp_5, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_5, arc_true, done_2);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_2);
  gen_set_label(done_1);
  getPCL(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  tcg_gen_add_tl(bta, temp_12, rd);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_6, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_7, temp_6, 1); tcg_gen_andi_tl(temp_7, temp_7, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_7, arc_true, done_3);;
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_and_tl(temp_8, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_9, temp_8, 0);
  tcg_gen_xori_tl(temp_10, temp_9, 1); tcg_gen_andi_tl(temp_10, temp_10, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_10, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  gen_set_label(done_3);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);

  return ret;
}





/* BBIT1
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  p_b = @b;
  p_c = (@c & 31);
  tmp = (1 << p_c);
  if((cc_flag == true))
    {
      if(((p_b && tmp) != 0))
        {
          take_branch = true;
        };
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      if(((p_b && tmp) != 0))
        {
          setPC (bta);
        };
    };
}
 */

int
arc_gen_BBIT1 (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_11);
  tcg_gen_mov_tl(cc_flag, temp_11);
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_andi_tl(p_c, c, 31);
  tcg_gen_shlfi_tl(tmp, 1, p_c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_tl(temp_3, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, temp_3, 0);
  tcg_gen_xori_tl(temp_5, temp_4, 1); tcg_gen_andi_tl(temp_5, temp_5, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_5, arc_true, done_2);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_2);
  gen_set_label(done_1);
  getPCL(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  tcg_gen_add_tl(bta, temp_12, rd);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_6, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_7, temp_6, 1); tcg_gen_andi_tl(temp_7, temp_7, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_7, arc_true, done_3);;
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_and_tl(temp_8, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_9, temp_8, 0);
  tcg_gen_xori_tl(temp_10, temp_9, 1); tcg_gen_andi_tl(temp_10, temp_10, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_10, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  gen_set_label(done_3);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);

  return ret;
}





/* BL
 *    Variables: @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, executeDelaySlot, nextInsnAddress, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      take_branch = true;
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == 1))
    {
      if(take_branch)
        {
          setBLINK (nextInsnAddressAfterDelaySlot ());
        };
      executeDelaySlot (bta, take_branch);
    }
  else
    {
      if(take_branch)
        {
          setBLINK (nextInsnAddress ());
        };
    };
  if((cc_flag == true))
    {
      setPC (bta);
    };
}
 */

int
arc_gen_BL (DisasCtxt *ctx, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_1);
  getPCL(temp_9);
  tcg_gen_mov_tl(temp_8, temp_9);
  tcg_gen_add_tl(bta, temp_8, rd);
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGLabel *done_2 = gen_new_label();
  tcg_gen_xori_tl(temp_3, take_branch, 1); tcg_gen_andi_tl(temp_3, temp_3, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_3, arc_true, done_2);;
  nextInsnAddressAfterDelaySlot(temp_11);
  tcg_gen_mov_tl(temp_10, temp_11);
  setBLINK(temp_10);
  gen_set_label(done_2);
  executeDelaySlot(bta, take_branch);
;
    }
  else
    {
    TCGLabel *done_3 = gen_new_label();
  tcg_gen_xori_tl(temp_4, take_branch, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, done_3);;
  nextInsnAddress(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  setBLINK(temp_12);
  gen_set_label(done_3);
;
    }
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_5, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* J
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      take_branch = true;
    };
  bta = @src;
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      setPC (bta);
    };
}
 */

int
arc_gen_J (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_1);
  tcg_gen_mov_tl(bta, src);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, done_2);;
  setPC(bta);
  gen_set_label(done_2);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* JL
 *    Variables: @src
 *    Functions: getCCFlag, shouldExecuteDelaySlot, setBLINK, nextInsnAddressAfterDelaySlot, executeDelaySlot, nextInsnAddress, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      take_branch = true;
    };
  bta = @src;
  if((shouldExecuteDelaySlot () == 1))
    {
      if(take_branch)
        {
          setBLINK (nextInsnAddressAfterDelaySlot ());
        };
      executeDelaySlot (bta, take_branch);
    }
  else
    {
      if(take_branch)
        {
          setBLINK (nextInsnAddress ());
        };
    };
  if((cc_flag == true))
    {
      setPC (bta);
    };
}
 */

int
arc_gen_JL (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_1);
  tcg_gen_mov_tl(bta, src);
  if ((shouldExecuteDelaySlot () == 1))
    {
    TCGLabel *done_2 = gen_new_label();
  tcg_gen_xori_tl(temp_3, take_branch, 1); tcg_gen_andi_tl(temp_3, temp_3, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_3, arc_true, done_2);;
  nextInsnAddressAfterDelaySlot(temp_9);
  tcg_gen_mov_tl(temp_8, temp_9);
  setBLINK(temp_8);
  gen_set_label(done_2);
  executeDelaySlot(bta, take_branch);
;
    }
  else
    {
    TCGLabel *done_3 = gen_new_label();
  tcg_gen_xori_tl(temp_4, take_branch, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, done_3);;
  nextInsnAddress(temp_11);
  tcg_gen_mov_tl(temp_10, temp_11);
  setBLINK(temp_10);
  gen_set_label(done_3);
;
    }
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_5, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_11);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* SETEQ
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b == p_c))
        {
        }
      else
        {
        };
      if((p_b == p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETEQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BREQ
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = (@b & 4294967295);
  p_c = (@c & 4294967295);
  p_b = se32to64 (p_b);
  p_c = se32to64 (p_c);
  take_branch = false;
  if((p_b == p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b == p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BREQ (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_5, p_b);
  tcg_gen_mov_tl(p_b, temp_5);
  se32to64(temp_6, p_c);
  tcg_gen_mov_tl(p_c, temp_6);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_add_tl(bta, temp_7, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETNE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b != p_c))
        {
        }
      else
        {
        };
      if((p_b != p_c))
        {
	  @a = 0;
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BRNE
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = (@b & 4294967295);
  p_c = (@c & 4294967295);
  p_b = se32to64 (p_b);
  p_c = se32to64 (p_c);
  take_branch = false;
  if((p_b != p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b != p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRNE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_5, p_b);
  tcg_gen_mov_tl(p_b, temp_5);
  se32to64(temp_6, p_c);
  tcg_gen_mov_tl(p_c, temp_6);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_add_tl(bta, temp_7, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETLT
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b < p_c))
        {
        }
      else
        {
        };
      if((p_b < p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BRLT
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = (@b & 4294967295);
  p_c = (@c & 4294967295);
  p_b = se32to64 (p_b);
  p_c = se32to64 (p_c);
  take_branch = false;
  if((p_b < p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b < p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRLT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_5, p_b);
  tcg_gen_mov_tl(p_b, temp_5);
  se32to64(temp_6, p_c);
  tcg_gen_mov_tl(p_c, temp_6);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_add_tl(bta, temp_7, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETGE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b >= p_c))
        {
        }
      else
        {
        };
      if((p_b >= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BRGE
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = (@b & 4294967295);
  p_c = (@c & 4294967295);
  p_b = se32to64 (p_b);
  p_c = se32to64 (p_c);
  take_branch = false;
  if((p_b >= p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b >= p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRGE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_5, p_b);
  tcg_gen_mov_tl(p_b, temp_5);
  se32to64(temp_6, p_c);
  tcg_gen_mov_tl(p_c, temp_6);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_8);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_add_tl(bta, temp_7, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETLE
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b <= p_c))
        {
        }
      else
        {
        };
      if((p_b <= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETLE (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LE, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* SETGT
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, se32to64
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = (@b & 4294967295);
      p_c = (@c & 4294967295);
      p_b = se32to64 (p_b);
      p_c = se32to64 (p_c);
      take_branch = false;
      if((p_b > p_c))
        {
        }
      else
        {
        };
      if((p_b > p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETGT (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_7 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_7);
  tcg_gen_mov_tl(cc_flag, temp_7);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(p_b, b, 4294967295);
  tcg_gen_andi_tl(p_c, c, 4294967295);
  se32to64(temp_8, p_b);
  tcg_gen_mov_tl(p_b, temp_8);
  se32to64(temp_9, p_c);
  tcg_gen_mov_tl(p_c, temp_9);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  TCGLabel *else_3 = gen_new_label();
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GT, temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_6, temp_5, 1); tcg_gen_andi_tl(temp_6, temp_6, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_6, arc_true, else_3);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_3);
  gen_set_label(else_3);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_3);
  gen_set_label(done_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);

  return ret;
}





/* BRLO
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, unsignedLT, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = se32to64 (@b);
  p_c = se32to64 (@c);
  take_branch = false;
  if(unsignedLT (p_b, p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if(unsignedLT (p_b, p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  se32to64(temp_3, b);
  tcg_gen_mov_tl(p_b, temp_3);
  se32to64(temp_4, c);
  tcg_gen_mov_tl(p_c, temp_4);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedLT(temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_5, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_7);
  tcg_gen_mov_tl(temp_6, temp_7);
  tcg_gen_add_tl(bta, temp_6, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedLT(temp_8, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_8, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_4);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(bta);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_2);

  return ret;
}





/* SETLO
 *    Variables: @b, @c, @a
 *    Functions: se32to64, unsignedLT
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = se32to64 (@b);
      p_c = se32to64 (@c);
      take_branch = false;
      if(unsignedLT (p_b, p_c))
        {
        }
      else
        {
        };
      if(unsignedLT (p_b, p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    }
}
 */

int
arc_gen_SETLO (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv cc_temp_1 = tcg_temp_local_new();
  getCCFlag(cc_flag);
  TCGLabel *done_cc = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, cc_temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(cc_temp_1, cc_temp_1, 1); tcg_gen_andi_tl(cc_temp_1, cc_temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, cc_temp_1, arc_true, done_cc);;
  se32to64(temp_3, b);
  tcg_gen_mov_tl(p_b, temp_3);
  se32to64(temp_4, c);
  tcg_gen_mov_tl(p_c, temp_4);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedLT(temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_5, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedLT(temp_6, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_6, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_cc);
  tcg_temp_free(temp_3);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_4);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_2);
  tcg_temp_free(cc_temp_1);
  tcg_temp_free(cc_flag);

  return ret;
}





/* BRHS
 *    Variables: @b, @c, @offset
 *    Functions: se32to64, unsignedGE, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = se32to64 (@b);
  p_c = se32to64 (@c);
  take_branch = false;
  if(unsignedGE (p_b, p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if(unsignedGE (p_b, p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  se32to64(temp_3, b);
  tcg_gen_mov_tl(p_b, temp_3);
  se32to64(temp_4, c);
  tcg_gen_mov_tl(p_c, temp_4);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedGE(temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_5, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_7);
  tcg_gen_mov_tl(temp_6, temp_7);
  tcg_gen_add_tl(bta, temp_6, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedGE(temp_8, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_8, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_4);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(bta);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_2);

  return ret;
}





/* SETHS
 *    Variables: @b, @c, @a
 *    Functions: se32to64, unsignedGE
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = se32to64 (@b);
      p_c = se32to64 (@c);
      take_branch = false;
      if(unsignedGE (p_b, p_c))
        {
        }
      else
        {
        };
      if(unsignedGE (p_b, p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    }
}
 */

int
arc_gen_SETHS (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv cc_temp_1 = tcg_temp_local_new();
  getCCFlag(cc_flag);
  TCGLabel *done_cc = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, cc_temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(cc_temp_1, cc_temp_1, 1); tcg_gen_andi_tl(cc_temp_1, cc_temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, cc_temp_1, arc_true, done_cc);;
  se32to64(temp_3, b);
  tcg_gen_mov_tl(p_b, temp_3);
  se32to64(temp_4, c);
  tcg_gen_mov_tl(p_c, temp_4);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedGE(temp_5, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_5, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedGE(temp_6, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_6, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_cc);
  tcg_temp_free(temp_3);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_4);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_2);
  tcg_temp_free(cc_temp_1);
  tcg_temp_free(cc_flag);

  return ret;
}





/*
 * EX - CODED BY HAND
 */

int
arc_gen_EX (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp = tcg_temp_local_new();
  tcg_gen_mov_tl(temp, b);
  tcg_gen_atomic_xchg_tl(b, c, temp, ctx->mem_idx, MO_UL);
  tcg_temp_free(temp);

  return ret;
}


#undef ARM_LIKE_LLOCK_SCOND

extern TCGv cpu_exclusive_addr;
extern TCGv cpu_exclusive_val;

/*
 * LLOCK -- CODED BY HAND
 */

int
arc_gen_LLOCK(DisasCtxt *ctx, TCGv dest, TCGv src)
{
    int ret = DISAS_NEXT;
#ifndef ARM_LIKE_LLOCK_SCOND
    gen_helper_llock(dest, cpu_env, src);
#else
    tcg_gen_qemu_ld_tl(cpu_exclusive_val, src, ctx->mem_idx, MO_UL);
    tcg_gen_mov_tl(dest, cpu_exclusive_val);
    tcg_gen_mov_tl(cpu_exclusive_addr, src);
#endif

    return ret;
}

/*
 * LLOCKL -- CODED BY HAND
 */

int
arc_gen_LLOCKL(DisasCtxt *ctx, TCGv dest, TCGv src)
{
    int ret = DISAS_NEXT;
#ifndef ARM_LIKE_LLOCK_SCOND
    gen_helper_llockl(dest, cpu_env, src);
#else
    tcg_gen_qemu_ld_tl(cpu_exclusive_val, src, ctx->mem_idx, MO_UQ);
    tcg_gen_mov_tl(dest, cpu_exclusive_val);
    tcg_gen_mov_tl(cpu_exclusive_addr, src);
#endif

    return ret;
}


/*
 * SCOND -- CODED BY HAND
 */

int
arc_gen_SCOND(DisasCtxt *ctx, TCGv addr, TCGv value)
{
    int ret = DISAS_NEXT;
#ifndef ARM_LIKE_LLOCK_SCOND
    TCGv temp_4 = tcg_temp_local_new();
    gen_helper_scond(temp_4, cpu_env, addr, value);
    setZFlag(temp_4);
    tcg_temp_free(temp_4);
#else
    TCGLabel *fail_label = gen_new_label();
    TCGLabel *done_label = gen_new_label();
    TCGv tmp;

    tcg_gen_brcond_tl(TCG_COND_NE, addr, cpu_exclusive_addr, fail_label);
    tmp = tcg_temp_new();

    tcg_gen_atomic_cmpxchg_tl(tmp, cpu_exclusive_addr, cpu_exclusive_val,
                               value, ctx->mem_idx,
                               MO_UL | MO_ALIGN);
    tcg_gen_setcond_tl(TCG_COND_NE, tmp, tmp, cpu_exclusive_val);

    setZFlag(tmp);

    tcg_temp_free(tmp);
    tcg_gen_br(done_label);

    gen_set_label(fail_label);
    tcg_gen_movi_tl(cpu_Zf, 1);
    gen_set_label(done_label);
    tcg_gen_movi_tl(cpu_exclusive_addr, -1);
#endif

    return ret;
}


/*
 * SCONDL -- CODED BY HAND
 */

int
arc_gen_SCONDL(DisasCtxt *ctx, TCGv addr, TCGv value)
{
    int ret = DISAS_NEXT;
#ifndef ARM_LIKE_LLOCK_SCOND
    TCGv temp_4 = tcg_temp_local_new();
    gen_helper_scondl(temp_4, cpu_env, addr, value);
    setZFlag(temp_4);
    tcg_temp_free(temp_4);
#else
    TCGLabel *fail_label = gen_new_label();
    TCGLabel *done_label = gen_new_label();
    TCGv tmp;

    tcg_gen_brcond_tl(TCG_COND_NE, addr, cpu_exclusive_addr, fail_label);
    tmp = tcg_temp_new();

    tcg_gen_atomic_cmpxchg_tl(tmp, cpu_exclusive_addr, cpu_exclusive_val,
                               value, ctx->mem_idx,
                               MO_Q | MO_ALIGN);
    tcg_gen_setcond_tl(TCG_COND_NE, tmp, tmp, cpu_exclusive_val);

    setZFlag(tmp);

    tcg_temp_free(tmp);
    tcg_gen_br(done_label);

    gen_set_label(fail_label);
    tcg_gen_movi_tl(cpu_Zf, 1);
    gen_set_label(done_label);
    tcg_gen_movi_tl(cpu_exclusive_addr, -1);
#endif

    return ret;
}





/* DMB - HAND MADE
 */

int
arc_gen_DMB (DisasCtxt *ctx, TCGv a)
{
  int ret = DISAS_NEXT;

  TCGBar bar = 0;
  switch(ctx->insn.operands[0].value & 7) {
    case 1:
      bar |= TCG_BAR_SC | TCG_MO_LD_LD | TCG_MO_LD_ST;
      break;
    case 2:
      bar |= TCG_BAR_SC | TCG_MO_ST_ST;
      break;
    default:
      bar |= TCG_BAR_SC | TCG_MO_ALL;
      break;
  }
  tcg_gen_mb(bar);

  return ret;
}





/* LD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, getFlagX, SignExtend, NoFurtherLoadsPending
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  l_src1 = @src1;
  l_src2 = @src2;
  setDebugLD (1);
  new_dest = getMemory (address, ZZ);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (l_src1 + l_src2);
    };
  if((getFlagX () == 1))
    {
      new_dest = SignExtend (new_dest, ZZ);
    };
  if(NoFurtherLoadsPending ())
    {
      setDebugLD (0);
    };
  @dest = new_dest;
}
 */

int
arc_gen_LD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv l_src1 = tcg_temp_local_new();
  TCGv l_src2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv new_dest = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
      ARC64_ADDRESS_ADD(address, src1, src2);
      //tcg_gen_add_tl(address, src1, src2);
    }
  if ((AA == 2))
    {
      tcg_gen_mov_tl(address, src1);
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      tcg_gen_shli_tl(temp_2, src2, 2);
      ARC64_ADDRESS_ADD(address, src1, temp_2);
      //tcg_gen_add_tl(address, src1, temp_2);
    }
  if (((AA == 3) && (ZZ == 2)))
    {
      tcg_gen_shli_tl(temp_3, src2, 1);
      ARC64_ADDRESS_ADD(address, src1, temp_3);
      //tcg_gen_add_tl(address, src1, temp_3);
    }
  tcg_gen_mov_tl(l_src1, src1);
  tcg_gen_mov_tl(l_src2, src2);
  tcg_gen_movi_tl(temp_4, 1);
  setDebugLD(temp_4);
  getMemory(temp_5, address, ZZ);
  tcg_gen_mov_tl(new_dest, temp_5);
  if (((AA == 1) || (AA == 2)))
    {
      //tcg_gen_add_tl(src1, l_src1, l_src2);
      ARC64_ADDRESS_ADD(src1, l_src1, l_src2);
    }
  if ((getFlagX () == 1))
    {
      new_dest = SignExtend (new_dest, ZZ);
    }
  TCGLabel *done_1 = gen_new_label();
  NoFurtherLoadsPending(temp_6);
  tcg_gen_xori_tl(temp_1, temp_6, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, done_1);;
  tcg_gen_movi_tl(temp_7, 0);
  setDebugLD(temp_7);
  gen_set_label(done_1);
  tcg_gen_mov_tl(dest, new_dest);
  tcg_temp_free(address);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(l_src1);
  tcg_temp_free(l_src2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(new_dest);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_7);

  return ret;
}





/* LDD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, nextReg, NoFurtherLoadsPending
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  l_src1 = @src1;
  l_src2 = @src2;
  setDebugLD (1);
  new_dest = getMemory (address, LONG);
  pair = nextReg (dest);
  pair = getMemory ((address + 4), LONG);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (l_src1 + l_src2);
    };
  if(NoFurtherLoadsPending ())
    {
      setDebugLD (0);
    };
  @dest = new_dest;
}
 */

int
arc_gen_LDD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv l_src1 = tcg_temp_local_new();
  TCGv l_src2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv new_dest = tcg_temp_local_new();
  TCGv pair = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
      ARC64_ADDRESS_ADD(address, src1, src2);
    }
  if ((AA == 2))
    {
    tcg_gen_mov_tl(address, src1);
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      tcg_gen_shli_tl(temp_2, src2, 2);
      ARC64_ADDRESS_ADD(address, src1, temp_2);
    }
  if (((AA == 3) && (ZZ == 2)))
    {
      tcg_gen_shli_tl(temp_3, src2, 1);
      ARC64_ADDRESS_ADD(address, src1, temp_3);
    }
  tcg_gen_mov_tl(l_src1, src1);
  tcg_gen_mov_tl(l_src2, src2);
  tcg_gen_movi_tl(temp_4, 1);
  setDebugLD(temp_4);
  getMemory(temp_5, address, LONG);
  tcg_gen_mov_tl(new_dest, temp_5);
  pair = nextReg (dest);
  tcg_gen_addi_tl(temp_7, address, 4);
  getMemory(temp_6, temp_7, LONG);
  tcg_gen_mov_tl(pair, temp_6);
  if (((AA == 1) || (AA == 2)))
    {
      ARC64_ADDRESS_ADD(src1, l_src1, l_src2);
    }
  TCGLabel *done_1 = gen_new_label();
  NoFurtherLoadsPending(temp_8);
  tcg_gen_xori_tl(temp_1, temp_8, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, done_1);;
  tcg_gen_movi_tl(temp_9, 0);
  setDebugLD(temp_9);
  gen_set_label(done_1);
  tcg_gen_mov_tl(dest, new_dest);
  tcg_temp_free(address);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(l_src1);
  tcg_temp_free(l_src2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(new_dest);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_9);

  return ret;
}





/* ST
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, ZZ, @dest);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
}
 */

int
arc_gen_ST (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
      ARC64_ADDRESS_ADD(address, src1, src2);
    }
  if ((AA == 2))
    {
      tcg_gen_mov_tl(address, src1);
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      tcg_gen_shli_tl(temp_1, src2, 2);
      ARC64_ADDRESS_ADD(address, src1, temp_1);
    }
  if (((AA == 3) && (ZZ == 2)))
    {
      tcg_gen_shli_tl(temp_2, src2, 1);
      ARC64_ADDRESS_ADD(address, src1, temp_2);
    }
  setMemory(address, ZZ, dest);
  if (((AA == 1) || (AA == 2)))
    {
      ARC64_ADDRESS_ADD(src1, src1, src2);
    }
  tcg_temp_free(address);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* STD
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory, instructionHasRegisterOperandIn, nextReg, getBit
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, LONG, @dest);
  if(instructionHasRegisterOperandIn (0))
    {
      pair = nextReg (dest);
    }
  else
    {
      if((getBit (@dest, 31) == 1))
        {
          pair = 4294967295;
        }
      else
        {
          pair = 0;
        };
    };
  setMemory ((address + 4), LONG, pair);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
}
 */

int
arc_gen_STD (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv pair = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
      ARC64_ADDRESS_ADD(address, src1, src2);
    }
  if ((AA == 2))
    {
      tcg_gen_mov_tl(address, src1);
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      tcg_gen_shli_tl(temp_3, src2, 2);
      ARC64_ADDRESS_ADD(address, src1, temp_3);
    }
  if (((AA == 3) && (ZZ == 2)))
    {
      tcg_gen_shli_tl(temp_4, src2, 1);
      ARC64_ADDRESS_ADD(address, src1, temp_4);
    }
  setMemory(address, LONG, dest);
  if (instructionHasRegisterOperandIn (0))
    {
    pair = nextReg (dest);
    }
  else
    {
    TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_movi_tl(temp_6, 31);
  getBit(temp_5, dest, temp_6);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, temp_5, 1);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_movi_tl(pair, 4294967295);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_movi_tl(pair, 0);
  gen_set_label(done_1);
;
    }
  tcg_gen_addi_tl(temp_7, address, 4);
  setMemory(temp_7, LONG, pair);
  if (((AA == 1) || (AA == 2)))
    {
      ARC64_ADDRESS_ADD(src1, src1, src2);
    }
  tcg_temp_free(address);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_7);

  return ret;
}





/* POP
 *    Variables: @dest
 *    Functions: getMemory, getRegister, setRegister
--- code ---
{
  new_dest = getMemory (getRegister (R_SP), LONG);
  setRegister (R_SP, (getRegister (R_SP) + 4));
  @dest = new_dest;
}
 */

int
arc_gen_POP (DisasCtxt *ctx, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv new_dest = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getRegister(temp_3, R_SP);
  tcg_gen_mov_tl(temp_2, temp_3);
  getMemory(temp_1, temp_2, LONG);
  tcg_gen_mov_tl(new_dest, temp_1);
  getRegister(temp_6, R_SP);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_addi_tl(temp_4, temp_5, 4);
  setRegister(R_SP, temp_4);
  tcg_gen_mov_tl(dest, new_dest);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(new_dest);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* PUSH
 *    Variables: @src
 *    Functions: setMemory, getRegister, setRegister
--- code ---
{
  local_src = @src;
  setMemory ((getRegister (R_SP) - 4), LONG, local_src);
  setRegister (R_SP, (getRegister (R_SP) - 4));
}
 */

int
arc_gen_PUSH (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv local_src = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(local_src, src);
  getRegister(temp_3, R_SP);
  tcg_gen_mov_tl(temp_2, temp_3);
  tcg_gen_subi_tl(temp_1, temp_2, 4);
  setMemory(temp_1, LONG, local_src);
  getRegister(temp_6, R_SP);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_subi_tl(temp_4, temp_5, 4);
  setRegister(R_SP, temp_4);
  tcg_temp_free(local_src);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* LP
 *    Variables: @rd
 *    Functions: getCCFlag, getRegIndex, writeAuxReg, nextInsnAddress, getPCL, setPC
--- code ---
{
  if((getCCFlag () == true))
    {
      lp_start_index = getRegIndex (LP_START);
      lp_end_index = getRegIndex (LP_END);
      writeAuxReg (lp_start_index, nextInsnAddress ());
      writeAuxReg (lp_end_index, (getPCL () + @rd));
    }
  else
    {
      setPC ((getPCL () + @rd));
    };
}
 */

int
arc_gen_LP (DisasCtxt *ctx, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv lp_start_index = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv lp_end_index = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  getCCFlag(temp_3);
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, temp_3, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  getRegIndex(temp_4, LP_START);
  tcg_gen_mov_tl(lp_start_index, temp_4);
  getRegIndex(temp_5, LP_END);
  tcg_gen_mov_tl(lp_end_index, temp_5);
  nextInsnAddress(temp_7);
  tcg_gen_mov_tl(temp_6, temp_7);
  writeAuxReg(lp_start_index, temp_6);
  getPCL(temp_10);
  tcg_gen_mov_tl(temp_9, temp_10);
  tcg_gen_add_tl(temp_8, temp_9, rd);
  writeAuxReg(lp_end_index, temp_8);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  getPCL(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  tcg_gen_add_tl(temp_11, temp_12, rd);
  setPC(temp_11);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(lp_start_index);
  tcg_temp_free(temp_5);
  tcg_temp_free(lp_end_index);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(temp_11);

  return ret;
}




/*
 * NORM
 *    Variables: @src, @dest
 *    Functions: CRLSB, getFFlag, setZFlag, setNFlag32
 * --- code ---
 * {
 *   psrc = @src;
 *   psrc = SignExtend16to32 (psrc);
 *   @dest = 32 - CRLSB (psrc);
 *   if((getFFlag () == true))
 *     {
 *       setZFlag (psrc);
 *       setNFlag32 (psrc);
 *     };
 * }
 */

int
arc_gen_NORM(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    tcg_gen_mov_tl(psrc, src);
    tcg_gen_ext32s_tl(psrc, psrc);
    tcg_gen_clrsb_tl(dest, psrc);
    tcg_gen_subi_tl(dest, dest, 32);
    if ((getFFlag () == true)) {
        setZFlag(psrc);
        setNFlag32(psrc);
    }
    tcg_temp_free(psrc);

    return ret;
}


/*
 * NORMH
 *    Variables: @src, @dest
 *    Functions: SignExtend16to32, CRLSB, getFFlag, setZFlag, setNFlagByNum
 * --- code ---
 * {
 *   psrc = (@src & 65535);
 *   psrc = SignExtend16to32 (psrc);
 *   @dest = CRLSB (psrc);
 *   @dest = (@dest - 16);
 *   if((getFFlag () == true))
 *     {
 *       setZFlagByNum (psrc, 16);
 *       setNFlagByNum (psrc, 16);
 *     };
 * }
 */

int
arc_gen_NORMH(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    tcg_gen_andi_tl(psrc, src, 65535);
    tcg_gen_ext16s_tl(psrc, psrc);
    tcg_gen_clrsb_tl(dest, psrc);
    tcg_gen_subi_tl(dest, dest, 16);
    if ((getFFlag () == true)) {
        setZFlagByNum(psrc, 16);
        setNFlagByNum(psrc, 16);
    }
    tcg_temp_free(psrc);

    return ret;
}


/*
 * FLS
 *    Variables: @src, @dest
 *    Functions: CLZ, getFFlag, setZFlag, setNFlag
 * --- code ---
 * {
 *   psrc = @src & 0xffffffff;
 *   if((psrc == 0))
 *     {
 *       @dest = 0;
 *     }
 *   else
 *     {
 *       @dest = 63 - CLZ (psrc, 32);
 *     };
 *   if((getFFlag () == true))
 *     {
 *       setZFlag (psrc);
 *       setNFlag32 (psrc);
 *     };
 * }
 */

int
arc_gen_FLS(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_3 = tcg_temp_local_new();
    tcg_gen_andi_tl(psrc, src, 0xffffffff);
    TCGLabel *else_1 = gen_new_label();
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, psrc, 0);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);
    tcg_gen_movi_tl(dest, 0);
    tcg_gen_br(done_1);
    gen_set_label(else_1);
    tcg_gen_movi_tl(temp_5, 32);
    tcg_gen_clz_tl(temp_4, psrc, temp_5);
    tcg_gen_mov_tl(temp_3, temp_4);
    tcg_gen_subfi_tl(dest, 63, temp_3);
    gen_set_label(done_1);
    if ((getFFlag () == true)) {
        setZFlag(psrc);
        setNFlag32(psrc);
    }
    tcg_temp_free(psrc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_3);

    return ret;
}





/*
 * FFS
 *    Variables: @src, @dest
 *    Functions: CTZ, getFFlag, setZFlag, setNFlag32
 * --- code ---
 * {
 *   psrc = @src & 0xffffffff;
 *   if((psrc == 0))
 *     {
 *       @dest = 31;
 *     }
 *   else
 *     {
 *       @dest = CTZ (psrc, 32);
 *     };
 *   if((getFFlag () == true))
 *     {
 *       setZFlag (psrc);
 *       setNFlag32 (psrc);
 *     };
 * }
 */

int
arc_gen_FFS(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_3 = tcg_temp_local_new();
    tcg_gen_andi_tl(psrc, src, 0xffffffff);
    TCGLabel *else_1 = gen_new_label();
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, psrc, 0);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);
    tcg_gen_movi_tl(dest, 31);
    tcg_gen_br(done_1);
    gen_set_label(else_1);
    tcg_gen_movi_tl(temp_4, 32);
    tcg_gen_ctz_tl(temp_3, psrc, temp_4);
    tcg_gen_mov_tl(dest, temp_3);
    gen_set_label(done_1);
    if ((getFFlag () == true)) {
        setZFlag(psrc);
        setNFlag32(psrc);
    }
    tcg_temp_free(psrc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_3);

    return ret;
}



/*
 *  Long instructions
 */


/* ADDL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b + @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_ADDL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_add_tl(a, b, c);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarryADD(temp_5, a, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowADD(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}




/*
 * ADD1L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD,
 *               setVFlag, OverflowADD
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = @b;
 *   lc = @c << 1;
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc);
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag (@a);
 *           setCFlag (CarryADD (@a, lb, lc));
 *           setVFlag (OverflowADD (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD1L(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    tcg_gen_mov_tl(lb, b);
    tcg_gen_shli_tl(lc, c, 1);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(a, b, lc);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag(a);
        CarryADD(temp_5, a, lb, lc);
        tcg_gen_mov_tl(temp_4, temp_5);
        setCFlag(temp_4);
        OverflowADD(temp_7, a, lb, lc);
        tcg_gen_mov_tl(temp_6, temp_7);
        setVFlag(temp_6);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_7);
    tcg_temp_free(temp_6);

    return ret;
}
/*
 * ADD2L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD,
 *               setVFlag, OverflowADD
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = @b;
 *   lc = @c << 2;
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc);
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag (@a);
 *           setCFlag (CarryADD (@a, lb, lc));
 *           setVFlag (OverflowADD (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD2L(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    tcg_gen_mov_tl(lb, b);
    tcg_gen_shli_tl(lc, c, 2);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(a, b, lc);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag(a);
        CarryADD(temp_5, a, lb, lc);
        tcg_gen_mov_tl(temp_4, temp_5);
        setCFlag(temp_4);
        OverflowADD(temp_7, a, lb, lc);
        tcg_gen_mov_tl(temp_6, temp_7);
        setVFlag(temp_6);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_7);
    tcg_temp_free(temp_6);

    return ret;
}




/*
 * ADD3L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD,
 *               setVFlag, OverflowADD
 * --- code ---
 * {
 *   cc_flag = getCCFlag ();
 *   lb = @b;
 *   lc = @c << 3;
 *   if((cc_flag == true))
 *     {
 *       @a = (@b + lc);
 *       if((getFFlag () == true))
 *         {
 *           setZFlag (@a);
 *           setNFlag (@a);
 *           setCFlag (CarryADD (@a, lb, lc));
 *           setVFlag (OverflowADD (@a, lb, lc));
 *         };
 *     };
 * }
 */

int
arc_gen_ADD3L(DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
    int ret = DISAS_NEXT;
    TCGv temp_3 = tcg_temp_local_new();
    TCGv cc_flag = tcg_temp_local_new();
    TCGv lb = tcg_temp_local_new();
    TCGv lc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_7 = tcg_temp_local_new();
    TCGv temp_6 = tcg_temp_local_new();
    getCCFlag(temp_3);
    tcg_gen_mov_tl(cc_flag, temp_3);
    tcg_gen_mov_tl(lb, b);
    tcg_gen_shli_tl(lc, c, 3);
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);
    tcg_gen_add_tl(a, b, lc);
    if ((getFFlag () == true)) {
        setZFlag(a);
        setNFlag(a);
        CarryADD(temp_5, a, lb, lc);
        tcg_gen_mov_tl(temp_4, temp_5);
        setCFlag(temp_4);
        OverflowADD(temp_7, a, lb, lc);
        tcg_gen_mov_tl(temp_6, temp_7);
        setVFlag(temp_6);
    }
    gen_set_label(done_1);
    tcg_temp_free(temp_3);
    tcg_temp_free(cc_flag);
    tcg_temp_free(lb);
    tcg_temp_free(lc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_7);
    tcg_temp_free(temp_6);

    return ret;
}






/* ADCL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarryADD, setVFlag, OverflowADD
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = ((@b + @c) + getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarryADD (@a, lb, lc));
          setVFlag (OverflowADD (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_ADCL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_add_tl(temp_4, b, c);
  getCFlag(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_add_tl(a, temp_4, temp_5);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarryADD(temp_8, a, lb, lc);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
  OverflowADD(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setVFlag(temp_9);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* SBCL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  lc = @c;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = ((@b - @c) - getCFlag ());
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SBCL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_sub_tl(temp_4, b, c);
  getCFlag(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_sub_tl(a, temp_4, temp_5);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarrySUB(temp_8, a, lb, lc);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
  OverflowSUB(temp_10, a, lb, lc);
  tcg_gen_mov_tl(temp_9, temp_10);
  setVFlag(temp_9);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);

  return ret;
}





/* SUBL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      @a = (@b - @c);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUBL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_sub_tl(a, b, c);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarrySUB(temp_5, a, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* SUB1L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c << 1);
      @a = (@b - lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB1L (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_shli_tl(lc, c, 1);
  tcg_gen_sub_tl(a, b, lc);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarrySUB(temp_5, a, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* SUB2L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c << 2);
      @a = (@b - lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB2L (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_shli_tl(lc, c, 2);
  tcg_gen_sub_tl(a, b, lc);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarrySUB(temp_5, a, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* SUB3L
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c << 3);
      @a = (@b - lc);
      if((getFFlag () == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_SUB3L (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_shli_tl(lc, c, 3);
  tcg_gen_sub_tl(a, b, lc);
  if ((getFFlag () == true))
    {
    setZFlag(a);
  setNFlag(a);
  CarrySUB(temp_5, a, lb, lc);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* MAXL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      alu = (lb - lc);
      if((lc >= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_MAXL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_sub_tl(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, lc, lb);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, lb);
  gen_set_label(done_2);
  if ((getFFlag () == true))
    {
    setZFlag(alu);
  setNFlag(alu);
  CarrySUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setCFlag(temp_6);
  OverflowSUB(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* MINL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  lb = @b;
  if((cc_flag == true))
    {
      lb = @b;
      lc = @c;
      alu = (lb - lc);
      if((lc <= lb))
        {
          @a = lc;
        }
      else
        {
          @a = lb;
        };
      if((getFFlag () == true))
        {
          setZFlag (alu);
          setNFlag (alu);
          setCFlag (CarrySUB (@a, lb, lc));
          setVFlag (OverflowSUB (@a, lb, lc));
        };
    };
}
 */

int
arc_gen_MINL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  tcg_gen_mov_tl(lb, b);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_mov_tl(lc, c);
  tcg_gen_sub_tl(alu, lb, lc);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LE, temp_3, lc, lb);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, lc);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, lb);
  gen_set_label(done_2);
  if ((getFFlag () == true))
    {
    setZFlag(alu);
  setNFlag(alu);
  CarrySUB(temp_7, a, lb, lc);
  tcg_gen_mov_tl(temp_6, temp_7);
  setCFlag(temp_6);
  OverflowSUB(temp_9, a, lb, lc);
  tcg_gen_mov_tl(temp_8, temp_9);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(lb);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* CMPL
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag, setCFlag, CarrySUB, setVFlag, OverflowSUB
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      alu = (@b - @c);
      setZFlag (alu);
      setNFlag (alu);
      setCFlag (CarrySUB (alu, @b, @c));
      setVFlag (OverflowSUB (alu, @b, @c));
    };
}
 */

int
arc_gen_CMPL (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_sub_tl(alu, b, c);
  setZFlag(alu);
  setNFlag(alu);
  CarrySUB(temp_5, alu, b, c);
  tcg_gen_mov_tl(temp_4, temp_5);
  setCFlag(temp_4);
  OverflowSUB(temp_7, alu, b, c);
  tcg_gen_mov_tl(temp_6, temp_7);
  setVFlag(temp_6);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* ANDL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & @c);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_ANDL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_tl(a, b, c);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* ORL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b | @c);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_ORL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_or_tl(a, b, c);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* XORL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b ^ @c);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_XORL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_xor_tl(a, b, c);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* MOVL
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = @b;
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_MOVL (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(a, b);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}

/* MOVHL
 *    Variables: @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = @b << 32;
      @a = @b
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_MOVHL (DisasCtxt *ctx, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;

      //tmp = @b << 32;
      //@a = tmp;

  tcg_gen_shli_tl(temp_4, b, 32);
  tcg_gen_mov_tl(a, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);

  return ret;
}





/* ASLL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 63);
      @a = (lb << lc);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (64 - lc)));
            };
        };
    };
}
 */

int
arc_gen_ASLL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_andi_tl(lc, c, 63);
  tcg_gen_shl_tl(a, lb, lc);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_6, 0);
  setCFlag(temp_6);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subfi_tl(temp_9, 64, lc);
  getBit(temp_8, lb, temp_9);
  tcg_gen_mov_tl(temp_7, temp_8);
  setCFlag(temp_7);
  gen_set_label(done_2);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);

  return ret;
}





/* ASRL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 63);
      @a = arithmeticShiftRight (lb, lc);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc_gen_ASRL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_andi_tl(lc, c, 63);
  arithmeticShiftRight(temp_6, lb, lc);
  tcg_gen_mov_tl(a, temp_6);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subi_tl(temp_10, lc, 1);
  getBit(temp_9, lb, temp_10);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}





/* LSRL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag, logicalShiftRight, getFFlag, setZFlag, setNFlag, setCFlag, getBit
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lb = @b;
      lc = (@c & 63);
      @a = logicalShiftRight (lb, lc);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
          if((lc == 0))
            {
              setCFlag (0);
            }
          else
            {
              setCFlag (getBit (lb, (lc - 1)));
            };
        };
    };
}
 */

int
arc_gen_LSRL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lb = tcg_temp_local_new();
  TCGv lc = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lb, b);
  tcg_gen_andi_tl(lc, c, 63);
  logicalShiftRight(temp_6, lb, lc);
  tcg_gen_mov_tl(a, temp_6);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, lc, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(temp_7, 0);
  setCFlag(temp_7);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_subi_tl(temp_10, lc, 1);
  getBit(temp_9, lb, temp_10);
  tcg_gen_mov_tl(temp_8, temp_9);
  setCFlag(temp_8);
  gen_set_label(done_2);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lb);
  tcg_temp_free(lc);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);

  return ret;
}






/* BICL
 *    Variables: @a, @b, @c
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @a = (@b & ~@c);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BICL (DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_not_tl(temp_4, c);
  tcg_gen_and_tl(a, b, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);

  return ret;
}





/* BCLRL
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 63));
      @a = (@b & ~tmp);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BCLRL (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 63);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_not_tl(temp_5, tmp);
  tcg_gen_and_tl(a, b, temp_5);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_5);

  return ret;
}





/* BMSKL
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 63) + 1);
      if((tmp1 == 64))
        {
          tmp2 = 0xffffffffffffffff;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & tmp2);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BMSKL (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_6, c, 63);
  tcg_gen_addi_tl(tmp1, temp_6, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, tmp1, 64);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(tmp2, 0xffffffffffffffff);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_tl(temp_7, 1, tmp1);
  tcg_gen_subi_tl(tmp2, temp_7, 1);
  gen_set_label(done_2);
  tcg_gen_and_tl(a, b, tmp2);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_7);

  return ret;
}





/* BMSKNL
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp1 = ((@c & 63) + 1);
      if((tmp1 == 64))
        {
          tmp2 = 0xffffffffffffffff;
        }
      else
        {
          tmp2 = ((1 << tmp1) - 1);
        };
      @a = (@b & ~tmp2);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BMSKNL (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_6, c, 63);
  tcg_gen_addi_tl(tmp1, temp_6, 1);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_3, tmp1, 64);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_movi_tl(tmp2, 0xffffffffffffffff);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_shlfi_tl(temp_7, 1, tmp1);
  tcg_gen_subi_tl(tmp2, temp_7, 1);
  gen_set_label(done_2);
  tcg_gen_not_tl(temp_8, tmp2);
  tcg_gen_and_tl(a, b, temp_8);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp2);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* BSETL
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 63));
      @a = (@b | tmp);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BSETL (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 63);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_or_tl(a, b, tmp);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);

  return ret;
}





/* BXORL
 *    Variables: @c, @a, @b
 *    Functions: getCCFlag, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << @c);
      @a = (@b ^ tmp);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@a);
          setNFlag (@a);
        };
    };
}
 */

int
arc_gen_BXORL (DisasCtxt *ctx, TCGv c, TCGv a, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_shlfi_tl(tmp, 1, c);
  tcg_gen_xor_tl(a, b, tmp);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(a);
  setNFlag(a);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(tmp);

  return ret;
}





/* ROLL
 *    Variables: @src, @dest
 *    Functions: getCCFlag, rotateLeft, getFFlag, setZFlag, setNFlag, setCFlag, extractBits
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      lsrc = @src;
      @dest = rotateLeft (lsrc, 1);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
          setCFlag (extractBits (lsrc, 63, 63));
        };
    };
}
 */

int
arc_gen_ROLL (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv lsrc = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(lsrc, src);
  tcg_gen_movi_tl(temp_5, 1);
  rotateLeft(temp_4, lsrc, temp_5);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_tl(temp_9, 63);
  tcg_gen_movi_tl(temp_8, 63);
  extractBits(temp_7, lsrc, temp_8, temp_9);
  tcg_gen_mov_tl(temp_6, temp_7);
  setCFlag(temp_6);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(lsrc);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);

  return ret;
}





/* SEXBL
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 24), 24);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc_gen_SEXBL (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 56);
  tcg_gen_shli_tl(temp_5, src, 56);
  arithmeticShiftRight(temp_4, temp_5, temp_6);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* SEXHL
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 16), 16);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc_gen_SEXHL (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 48);
  tcg_gen_shli_tl(temp_5, src, 48);
  arithmeticShiftRight(temp_4, temp_5, temp_6);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}


/* SEXWL
 *    Variables: @dest, @src
 *    Functions: getCCFlag, arithmeticShiftRight, getFFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      @dest = arithmeticShiftRight ((@src << 32), 32);
      f_flag = getFFlag ();
      if((f_flag == true))
        {
          setZFlag (@dest);
          setNFlag (@dest);
        };
    };
}
 */

int
arc_gen_SEXWL (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  int f_flag;
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 32);
  tcg_gen_shli_tl(temp_5, src, 32);
  arithmeticShiftRight(temp_4, temp_5, temp_6);
  tcg_gen_mov_tl(dest, temp_4);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* BTSTL
 *    Variables: @c, @b
 *    Functions: getCCFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = (1 << (@c & 63));
      alu = (@b & tmp);
      setZFlag (alu);
      setNFlag (alu);
    };
}
 */

int
arc_gen_BTSTL (DisasCtxt *ctx, TCGv c, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_andi_tl(temp_4, c, 63);
  tcg_gen_shlfi_tl(tmp, 1, temp_4);
  tcg_gen_and_tl(alu, b, tmp);
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);
  tcg_temp_free(alu);

  return ret;
}





/* TSTL
 *    Variables: @b, @c
 *    Functions: getCCFlag, setZFlag, setNFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      alu = (@b & @c);
      setZFlag (alu);
      setNFlag (alu);
    };
}
 */

int
arc_gen_TSTL (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_and_tl(alu, b, c);
  setZFlag(alu);
  setNFlag(alu);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(alu);

  return ret;
}





/* XBFUL
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, extractBits, getFFlag, setZFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      N = extractBits (@src2, 5, 0);
      M = (extractBits (@src2, 11, 6) + 1);
      tmp1 = (@src1 >> N);
      tmp2 = ((1 << M) - 1);
      @dest = (tmp1 & tmp2);
      if((getFFlag () == true))
        {
          setZFlag (@dest);
        };
    };
}
 */

int
arc_gen_XBFUL (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv N = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv M = tcg_temp_local_new();
  TCGv tmp1 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv tmp2 = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_movi_tl(temp_6, 0);
  tcg_gen_movi_tl(temp_5, 5);
  extractBits(temp_4, src2, temp_5, temp_6);
  tcg_gen_mov_tl(N, temp_4);
  tcg_gen_movi_tl(temp_10, 6);
  tcg_gen_movi_tl(temp_9, 11);
  extractBits(temp_8, src2, temp_9, temp_10);
  tcg_gen_mov_tl(temp_7, temp_8);
  tcg_gen_addi_tl(M, temp_7, 1);
  tcg_gen_shr_tl(tmp1, src1, N);
  tcg_gen_shlfi_tl(temp_11, 1, M);
  tcg_gen_subi_tl(tmp2, temp_11, 1);
  tcg_gen_and_tl(dest, tmp1, tmp2);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
;
    }
  else
    {
  ;
    }
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(N);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_7);
  tcg_temp_free(M);
  tcg_temp_free(tmp1);
  tcg_temp_free(temp_11);
  tcg_temp_free(tmp2);

  return ret;
}





/* AEXL
 *    Variables: @src2, @b
 *    Functions: getCCFlag, readAuxReg, writeAuxReg
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      tmp = readAuxReg (@src2);
      writeAuxReg (@src2, @b);
      @b = tmp;
    };
}
 */

int
arc_gen_AEXL (DisasCtxt *ctx, TCGv src2, TCGv b)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  getCCFlag(temp_3);
  tcg_gen_mov_tl(cc_flag, temp_3);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  readAuxReg(temp_4, src2);
  tcg_gen_mov_tl(tmp, temp_4);
  writeAuxReg(src2, b);
  tcg_gen_mov_tl(b, tmp);
  gen_set_label(done_1);
  tcg_temp_free(temp_3);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(tmp);

  return ret;
}





/* LRL
 *    Variables: @dest, @src
 *    Functions: readAuxReg
--- code ---
{
  @dest = readAuxReg (@src);
}
 */

int
arc_gen_LRL (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NORETURN;

  if (tb_cflags(ctx->base.tb) & CF_USE_ICOUNT) {
      gen_io_start();
  }

  TCGv temp_1 = tcg_temp_local_new();
  readAuxReg(temp_1, src);
  tcg_gen_mov_tl(dest, temp_1);
  tcg_temp_free(temp_1);

  return ret;
}





/* DIVL
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divSigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divSigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_DIVL (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_9);
  tcg_gen_mov_tl(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_tl(temp_6, temp_4, temp_5);
  tcg_gen_and_tl(temp_7, temp_3, temp_6);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, else_2);;
  divSigned(temp_10, src1, src2);
  tcg_gen_mov_tl(dest, temp_10);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_tl(temp_11, 0);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* DIVUL
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divUnsigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divUnsigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_DIVUL (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  divUnsigned(temp_6, src1, src2);
  tcg_gen_mov_tl(dest, temp_6);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  tcg_gen_movi_tl(temp_7, 0);
  setNFlag(temp_7);
  tcg_gen_movi_tl(temp_8, 0);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* REML
 *    Variables: @src2, @src1, @dest
 *    Functions: getCCFlag, divRemainingSigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if(((@src2 != 0) && ((@src1 != 2147483648) || (@src2 != 4294967295))))
        {
          @dest = divRemainingSigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (@dest);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_REML (DisasCtxt *ctx, TCGv src2, TCGv src1, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_9 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  getCCFlag(temp_9);
  tcg_gen_mov_tl(cc_flag, temp_9);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, src1, 2147483648);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_5, src2, 4294967295);
  tcg_gen_or_tl(temp_6, temp_4, temp_5);
  tcg_gen_and_tl(temp_7, temp_3, temp_6);
  tcg_gen_xori_tl(temp_8, temp_7, 1); tcg_gen_andi_tl(temp_8, temp_8, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_8, arc_true, else_2);;
  divRemainingSigned(temp_10, src1, src2);
  tcg_gen_mov_tl(dest, temp_10);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag(dest);
  tcg_gen_movi_tl(temp_11, 0);
  setVFlag(temp_11);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_9);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_10);
  tcg_temp_free(temp_11);

  return ret;
}





/* REMUL
 *    Variables: @src2, @dest, @src1
 *    Functions: getCCFlag, divRemainingUnsigned, getFFlag, setZFlag, setNFlag, setVFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      if((@src2 != 0))
        {
          @dest = divRemainingUnsigned (@src1, @src2);
          if((getFFlag () == true))
            {
              setZFlag (@dest);
              setNFlag (0);
              setVFlag (0);
            };
        }
      else
        {
        };
    };
}
 */

int
arc_gen_REMUL (DisasCtxt *ctx, TCGv src2, TCGv dest, TCGv src1)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_3, src2, 0);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  divRemainingUnsigned(temp_6, src1, src2);
  tcg_gen_mov_tl(dest, temp_6);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  tcg_gen_movi_tl(temp_7, 0);
  setNFlag(temp_7);
  tcg_gen_movi_tl(temp_8, 0);
  setVFlag(temp_8);
;
    }
  else
    {
  ;
    }
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);

  return ret;
}





/* ABSL
 *    Variables: @src, @dest
 *    Functions: Carry, getFFlag, setZFlag, setNFlag, setCFlag, Zero, setVFlag, getNFlag
--- code ---
{
  lsrc = @src;
  alu = (0 - lsrc);
  if((Carry (lsrc) == 1))
    {
      @dest = alu;
    }
  else
    {
      @dest = lsrc;
    };
  if((getFFlag () == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
      setCFlag (Zero ());
      setVFlag (getNFlag ());
    };
}
 */

int
arc_gen_ABSL (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv lsrc = tcg_temp_local_new();
  TCGv alu = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  tcg_gen_mov_tl(lsrc, src);
  tcg_gen_subfi_tl(alu, 0, lsrc);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  Carry(temp_3, lsrc);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, temp_3, 1);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(dest, alu);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_tl(dest, lsrc);
  gen_set_label(done_1);
  if ((getFFlag () == true))
    {
    setZFlag(dest);
  setNFlag(dest);
  tcg_gen_mov_tl(temp_4, Zero());
  setCFlag(temp_4);
  tcg_gen_mov_tl(temp_5, getNFlag());
  setVFlag(temp_5);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(lsrc);
  tcg_temp_free(alu);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);

  return ret;
}





/* SWAP
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  tmp1 = (@src << 32);
  tmp2 = ((@src >> 32) & 0xFFFFFFFF);
  @dest = (tmp1 | tmp2);
  f_flag = getFFlag ();
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc_gen_SWAPL (DisasCtxt *ctx, TCGv src, TCGv dest)
{
    const int ret = DISAS_NEXT;
    TCGv hi = tcg_temp_local_new();
    TCGv lo = tcg_temp_local_new();

    tcg_gen_shli_tl(lo, src, 32);
    tcg_gen_shri_tl(hi, src, 32);
    tcg_gen_andi_tl(hi, hi, 0xFFFFFFFF);
    tcg_gen_or_tl(dest, hi, lo);

    if (getFFlag() == true) {
        setZFlag(dest);
        setNFlag(dest);
    }

    tcg_temp_free(hi);
    tcg_temp_free(lo);

    return ret;
}





/* SWAPE
 *    Variables: @src, @dest
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  @dest = tcg_gen_bswap64_tl(@src);
  f_flag = getFFlag ();
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc_gen_SWAPEL (DisasCtxt *ctx, TCGv src, TCGv dest)
{
    const int ret = DISAS_NEXT;

    tcg_gen_bswap64_tl(dest, src);

    if (getFFlag() == true) {
        setZFlag(dest);
        setNFlag(dest);
    }

    return ret;
}





/* NOTL
 *    Variables: @dest, @src
 *    Functions: getFFlag, setZFlag, setNFlag
--- code ---
{
  @dest = ~@src;
  f_flag = getFFlag ();
  if((f_flag == true))
    {
      setZFlag (@dest);
      setNFlag (@dest);
    };
}
 */

int
arc_gen_NOTL (DisasCtxt *ctx, TCGv dest, TCGv src)
{
  int ret = DISAS_NEXT;
  int f_flag;
  tcg_gen_not_tl(dest, src);
  f_flag = getFFlag ();
  if ((f_flag == true))
    {
    setZFlag(dest);
  setNFlag(dest);
;
    }
  else
    {
  ;
    }

  return ret;
}





/* SETEQL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b == p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETEQL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BREQL
 *    Variables: @b, @c, @offset
 *    Functions: getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if((p_b == p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b == p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BREQL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_add_tl(bta, temp_5, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETNEL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b != p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETNEL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRNEL
 *    Variables: @b, @c, @offset
 *    Functions: getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if((p_b != p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b != p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRNEL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_add_tl(bta, temp_5, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_NE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETLTL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b < p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETLTL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRLTL
 *    Variables: @b, @c, @offset
 *    Functions: getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if((p_b < p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b < p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRLTL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_add_tl(bta, temp_5, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETGEL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b >= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETGEL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv v = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(v);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRGEL
 *    Variables: @b, @c, @offset
 *    Functions: getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if((p_b >= p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((p_b >= p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRGEL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_1, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_6);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_add_tl(bta, temp_5, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(bta);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETLEL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b <= p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETLEL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv v = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_LE, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(v);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* SETGTL
 *    Variables: @b, @c, @a
 *    Functions: getCCFlag
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if((p_b > p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    };
}
 */

int
arc_gen_SETGTL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv temp_5 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv v = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getCCFlag(temp_5);
  tcg_gen_mov_tl(cc_flag, temp_5);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_GT, temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_4, temp_3, 1); tcg_gen_andi_tl(temp_4, temp_4, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_4, arc_true, else_2);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_2);
  gen_set_label(done_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(cc_flag);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(v);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_6);
  tcg_temp_free(p_b);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_8);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);

  return ret;
}





/* BRLOL
 *    Variables: @b, @c, @offset
 *    Functions: unsignedLT, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if(unsignedLT (p_b, p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if(unsignedLT (p_b, p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRLOL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedLT(temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_3, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_5);
  tcg_gen_mov_tl(temp_4, temp_5);
  tcg_gen_add_tl(bta, temp_4, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedLT(temp_6, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_6, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_2);

  return ret;
}





/* SETLOL
 *    Variables: @b, @c, @a
 *    Functions: unsignedLT
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if(unsignedLT (p_b, p_c))
	{
	  @a = true;
	}
      else
	{
	  @a = false;
	};
    }
}
 */

int
arc_gen_SETLOL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv cc_temp_1 = tcg_temp_local_new();
  getCCFlag(cc_flag);
  TCGLabel *done_cc = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, cc_temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(cc_temp_1, cc_temp_1, 1); tcg_gen_andi_tl(cc_temp_1, cc_temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, cc_temp_1, arc_true, done_cc);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedLT(temp_2, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_2, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_1);
  gen_set_label(done_cc);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(cc_temp_1);
  tcg_temp_free(cc_flag);

  return ret;
}





/* BRHSL
 *    Variables: @b, @c, @offset
 *    Functions: unsignedGE, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  p_b = @b;
  p_c = @c;
  take_branch = false;
  if(unsignedGE (p_b, p_c))
    {
      take_branch = true;
    }
  else
    {
    };
  bta = (getPCL () + @offset);
  if((shouldExecuteDelaySlot () == 1))
    {
      executeDelaySlot (bta, take_branch);
    };
  if(unsignedGE (p_b, p_c))
    {
      setPC (bta);
    }
  else
    {
    };
}
 */

int
arc_gen_BRHSL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv offset)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  tcg_gen_mov_tl(take_branch, arc_false);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedGE(temp_3, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_3, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(take_branch, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  gen_set_label(done_1);
  getPCL(temp_5);
  tcg_gen_mov_tl(temp_4, temp_5);
  tcg_gen_add_tl(bta, temp_4, offset);
  if ((shouldExecuteDelaySlot () == 1))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *else_2 = gen_new_label();
  TCGLabel *done_2 = gen_new_label();
  unsignedGE(temp_6, p_b, p_c);
  tcg_gen_xori_tl(temp_2, temp_6, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_2);;
  setPC(bta);
  tcg_gen_br(done_2);
  gen_set_label(else_2);
  gen_set_label(done_2);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_2);

  return ret;
}





/* SETHSL
 *    Variables: @b, @c, @a
 *    Functions: unsignedGE
--- code ---
{
  cc_flag = getCCFlag ();
  if((cc_flag == true))
    {
      p_b = @b;
      p_c = @c;
      if(unsignedGE (p_b, p_c))
        {
          @a = true;
        }
      else
        {
          @a = false;
        };
    }
}
 */

int
arc_gen_SETHSL (DisasCtxt *ctx, TCGv b, TCGv c, TCGv a)
{
  int ret = DISAS_NEXT;
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv cc_temp_1 = tcg_temp_local_new();
  getCCFlag(cc_flag);
  TCGLabel *done_cc = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, cc_temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(cc_temp_1, cc_temp_1, 1); tcg_gen_andi_tl(cc_temp_1, cc_temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, cc_temp_1, arc_true, done_cc);;
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_mov_tl(p_c, c);
  TCGLabel *else_1 = gen_new_label();
  TCGLabel *done_1 = gen_new_label();
  unsignedGE(temp_2, p_b, p_c);
  tcg_gen_xori_tl(temp_1, temp_2, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, else_1);;
  tcg_gen_mov_tl(a, arc_true);
  tcg_gen_br(done_1);
  gen_set_label(else_1);
  tcg_gen_mov_tl(a, arc_false);
  gen_set_label(done_1);
  gen_set_label(done_cc);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(cc_temp_1);
  tcg_temp_free(cc_flag);

  return ret;
}





/*
 * EXL - CODED BY HAND
 */

int
arc_gen_EXL (DisasCtxt *ctx, TCGv b, TCGv c)
{
  int ret = DISAS_NEXT;
  TCGv temp = tcg_temp_local_new();
  tcg_gen_mov_tl(temp, b);
  tcg_gen_atomic_xchg_tl(b, c, temp, ctx->mem_idx, MO_UQ);
  tcg_temp_free(temp);

  return ret;
}





/* LDL
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setDebugLD, getMemory, getFlagX, SignExtend, NoFurtherLoadsPending
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  l_src1 = @src1;
  l_src2 = @src2;
  setDebugLD (1);
  new_dest = getMemory (address, ZZ);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (l_src1 + l_src2);
    };
  if((getFlagX () == 1))
    {
      new_dest = SignExtend (new_dest, ZZ);
    };
  if(NoFurtherLoadsPending ())
    {
      setDebugLD (0);
    };
  @dest = new_dest;
}
 */

int
arc_gen_LDL (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv l_src1 = tcg_temp_local_new();
  TCGv l_src2 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv new_dest = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_tl(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_tl(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_tl(temp_2, src2, 3);
  tcg_gen_add_tl(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_tl(temp_3, src2, 1);
  tcg_gen_add_tl(address, src1, temp_3);
;
    }
  else
    {
  ;
    }
  tcg_gen_mov_tl(l_src1, src1);
  tcg_gen_mov_tl(l_src2, src2);
  tcg_gen_movi_tl(temp_4, 1);
  setDebugLD(temp_4);
  getMemory(temp_5, address, ZZ);
  tcg_gen_mov_tl(new_dest, temp_5);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_tl(src1, l_src1, l_src2);
;
    }
  else
    {
  ;
    }
  if ((getFlagX () == 1))
    {
    new_dest = SignExtend (new_dest, ZZ);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_1 = gen_new_label();
  NoFurtherLoadsPending(temp_6);
  tcg_gen_xori_tl(temp_1, temp_6, 1); tcg_gen_andi_tl(temp_1, temp_1, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_1, arc_true, done_1);;
  tcg_gen_movi_tl(temp_7, 0);
  setDebugLD(temp_7);
  gen_set_label(done_1);
  tcg_gen_mov_tl(dest, new_dest);
  tcg_temp_free(address);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(l_src1);
  tcg_temp_free(l_src2);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(new_dest);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_7);

  return ret;
}





/* STL
 *    Variables: @src1, @src2, @dest
 *    Functions: getAAFlag, getZZFlag, setMemory
--- code ---
{
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  address = 0;
  if(((AA == 0) || (AA == 1)))
    {
      address = (@src1 + @src2);
    };
  if((AA == 2))
    {
      address = @src1;
    };
  if(((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
      address = (@src1 + (@src2 << 2));
    };
  if(((AA == 3) && (ZZ == 2)))
    {
      address = (@src1 + (@src2 << 1));
    };
  setMemory (address, ZZ, @dest);
  if(((AA == 1) || (AA == 2)))
    {
      @src1 = (@src1 + @src2);
    };
}
 */

int
arc_gen_STL (DisasCtxt *ctx, TCGv src1, TCGv src2, TCGv dest)
{
  int ret = DISAS_NEXT;
  int AA;
  int ZZ;
  TCGv address = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  AA = getAAFlag ();
  ZZ = getZZFlag ();
  tcg_gen_movi_tl(address, 0);
  if (((AA == 0) || (AA == 1)))
    {
    tcg_gen_add_tl(address, src1, src2);
;
    }
  else
    {
  ;
    }
  if ((AA == 2))
    {
    tcg_gen_mov_tl(address, src1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && ((ZZ == 0) || (ZZ == 3))))
    {
    tcg_gen_shli_tl(temp_1, src2, 3);
  tcg_gen_add_tl(address, src1, temp_1);
;
    }
  else
    {
  ;
    }
  if (((AA == 3) && (ZZ == 2)))
    {
    tcg_gen_shli_tl(temp_2, src2, 1);
  tcg_gen_add_tl(address, src1, temp_2);
;
    }
  else
    {
  ;
    }
  setMemory(address, ZZ, dest);
  if (((AA == 1) || (AA == 2)))
    {
    tcg_gen_add_tl(src1, src1, src2);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(address);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);

  return ret;
}





/* POPL
 *    Variables: @dest
 *    Functions: getMemory, getRegister, setRegister
--- code ---
{
  new_dest = getMemory (getRegister (R_SP), LONG);
  setRegister (R_SP, (getRegister (R_SP) + 4));
  @dest = new_dest;
}
 */

int
arc_gen_POPL (DisasCtxt *ctx, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv new_dest = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  getRegister(temp_3, R_SP);
  tcg_gen_mov_tl(temp_2, temp_3);
  getMemory(temp_1, temp_2, LONGLONG);
  tcg_gen_mov_tl(new_dest, temp_1);
  getRegister(temp_6, R_SP);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_addi_tl(temp_4, temp_5, 8);
  setRegister(R_SP, temp_4);
  tcg_gen_mov_tl(dest, new_dest);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(new_dest);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* PUSHL
 *    Variables: @src
 *    Functions: setMemory, getRegister, setRegister
--- code ---
{
  local_src = @src;
  setMemory ((getRegister (R_SP) - 8), LONG, local_src);
  setRegister (R_SP, (getRegister (R_SP) - 8));
}
 */

int
arc_gen_PUSHL (DisasCtxt *ctx, TCGv src)
{
  int ret = DISAS_NEXT;
  TCGv local_src = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  tcg_gen_mov_tl(local_src, src);
  getRegister(temp_3, R_SP);
  tcg_gen_mov_tl(temp_2, temp_3);
  tcg_gen_subi_tl(temp_1, temp_2, 8);
  setMemory(temp_1, LONGLONG, local_src);
  getRegister(temp_6, R_SP);
  tcg_gen_mov_tl(temp_5, temp_6);
  tcg_gen_subi_tl(temp_4, temp_5, 8);
  setRegister(R_SP, temp_4);
  tcg_temp_free(local_src);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_4);

  return ret;
}





/* NORML
 *    Variables: @src, @dest
 *    Functions: HELPER, getFFlag, setZFlag, setNFlag
--- code ---
{
  psrc = @src;
  i = HELPER (norml, psrc);
  @dest = (63 - i);
  if((getFFlag () == true))
    {
      setZFlag (psrc);
      setNFlag (psrc);
    };
}
 */

int
arc_gen_NORML (DisasCtxt *ctx, TCGv src, TCGv dest)
{
  int ret = DISAS_NEXT;
  TCGv psrc = tcg_temp_local_new();
  TCGv i = tcg_temp_local_new();
  tcg_gen_mov_tl(psrc, src);
  ARC_HELPER(norml, i, psrc);
  tcg_gen_subfi_tl(dest, 63, i);
  if ((getFFlag () == true))
    {
    setZFlag(psrc);
  setNFlag(psrc);
;
    }
  else
    {
  ;
    }
  tcg_temp_free(psrc);
  tcg_temp_free(i);

  return ret;
}





/*
 * FLSL
 *    Variables: @src, @dest
 *    Functions: CLZ, getFFlag, setZFlag, setNFlag
 * --- code ---
 * {
 *   psrc = @src;
 *   if((psrc == 0))
 *     {
 *       @dest = 0;
 *     }
 *   else
 *     {
 *       @dest = 63 - CLZ (psrc, 64);
 *     };
 *   if((getFFlag () == true))
 *     {
 *       setZFlag (psrc);
 *       setNFlag (psrc);
 *     };
 * }
 */

int
arc_gen_FLSL(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_5 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_3 = tcg_temp_local_new();
    tcg_gen_mov_tl(psrc, src);
    TCGLabel *else_1 = gen_new_label();
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, psrc, 0);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);
    tcg_gen_movi_tl(dest, 0);
    tcg_gen_br(done_1);
    gen_set_label(else_1);
    tcg_gen_movi_tl(temp_5, 64);
    tcg_gen_clz_tl(temp_4, psrc, temp_5);
    tcg_gen_mov_tl(temp_3, temp_4);
    tcg_gen_subfi_tl(dest, 63, temp_3);
    gen_set_label(done_1);
    if ((getFFlag () == true)) {
        setZFlag(psrc);
        setNFlag(psrc);
    }
    tcg_temp_free(psrc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_5);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_3);

    return ret;
}





/*
 * FFSL
 *    Variables: @src, @dest
 *    Functions: CTZ, getFFlag, setZFlag, setNFlag
 * --- code ---
 * {
 *   psrc = @src;
 *   if((psrc == 0))
 *     {
 *       @dest = 63;
 *     }
 *   else
 *     {
 *       @dest = CTZ (psrc, 64);
 *     };
 *   if((getFFlag () == true))
 *     {
 *       setZFlag (psrc);
 *       setNFlag (psrc);
 *     };
 * }
 */

int
arc_gen_FFSL(DisasCtxt *ctx, TCGv src, TCGv dest)
{
    int ret = DISAS_NEXT;
    TCGv psrc = tcg_temp_local_new();
    TCGv temp_1 = tcg_temp_local_new();
    TCGv temp_2 = tcg_temp_local_new();
    TCGv temp_4 = tcg_temp_local_new();
    TCGv temp_3 = tcg_temp_local_new();
    tcg_gen_mov_tl(psrc, src);
    TCGLabel *else_1 = gen_new_label();
    TCGLabel *done_1 = gen_new_label();
    tcg_gen_setcondi_tl(TCG_COND_EQ, temp_1, psrc, 0);
    tcg_gen_xori_tl(temp_2, temp_1, 1);
    tcg_gen_andi_tl(temp_2, temp_2, 1);
    tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, else_1);
    tcg_gen_movi_tl(dest, 63);
    tcg_gen_br(done_1);
    gen_set_label(else_1);
    tcg_gen_movi_tl(temp_4, 64);
    tcg_gen_ctz_tl(temp_3, psrc, temp_4);
    tcg_gen_mov_tl(dest, temp_3);
    gen_set_label(done_1);
    if ((getFFlag () == true)) {
        setZFlag(psrc);
        setNFlag(psrc);
    }
    tcg_temp_free(psrc);
    tcg_temp_free(temp_1);
    tcg_temp_free(temp_2);
    tcg_temp_free(temp_4);
    tcg_temp_free(temp_3);

    return ret;
}





/* DBNZ
 *    Variables: @a, @offset
 *    Functions: getPCL, setPC
--- code ---
{
  bta = getPCL() + @offset;
  @a = @a - 1
  if (shouldExecuteDelaySlot() == 1)
  {
      take_branch = true;
      if (@a == 0)
      {
          take_branch = false;
      };
      executeDelaySlot (bta, take_branch);
  };
  if(@a != 0) {
    setPC(getPCL () + @offset)
  }
}
 */

int
arc_gen_DBNZ (DisasCtxt *ctx, TCGv a, TCGv offset)
{
    int ret = DISAS_NEXT;
    TCGLabel *do_not_branch = gen_new_label();
    TCGLabel *keep_take_branch_1 = gen_new_label();
    TCGv bta = tcg_temp_local_new();

    getPCL(bta);
    tcg_gen_add_tl(bta, bta, offset);
    tcg_gen_subi_tl(a, a, 1);

    if (shouldExecuteDelaySlot() == 1) {
        TCGv take_branch = tcg_const_local_tl(1);
        tcg_gen_brcondi_tl(TCG_COND_NE, a, 0, keep_take_branch_1);
        tcg_temp_free(take_branch);
        tcg_gen_mov_tl(take_branch, tcg_const_local_tl(0));
        gen_set_label(keep_take_branch_1);
        executeDelaySlot(bta, take_branch);
        tcg_temp_free(take_branch);
    }

    tcg_gen_brcondi_tl(TCG_COND_EQ, a, 0, do_not_branch);
        setPC(bta);
    gen_set_label(do_not_branch);
    tcg_temp_free(bta);

  return ret;
}

/* BBIT0L
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  p_b = @b;
  p_c = (@c & 63);
  tmp = (1 << p_c);
  if((cc_flag == true))
    {
      if(((p_b && tmp) == 0))
        {
          take_branch = true;
        };
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      if(((p_b && tmp) == 0))
        {
          setPC (bta);
        };
    };
}
 */

int
arc_gen_BBIT0L (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_11);
  tcg_gen_mov_tl(cc_flag, temp_11);
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_andi_tl(p_c, c, 63);
  tcg_gen_shlfi_tl(tmp, 1, p_c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_tl(temp_3, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_4, temp_3, 0);
  tcg_gen_xori_tl(temp_5, temp_4, 1); tcg_gen_andi_tl(temp_5, temp_5, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_5, arc_true, done_2);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_2);
  gen_set_label(done_1);
  getPCL(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  tcg_gen_add_tl(bta, temp_12, rd);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_6, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_7, temp_6, 1); tcg_gen_andi_tl(temp_7, temp_7, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_7, arc_true, done_3);;
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_and_tl(temp_8, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_EQ, temp_9, temp_8, 0);
  tcg_gen_xori_tl(temp_10, temp_9, 1); tcg_gen_andi_tl(temp_10, temp_10, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_10, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  gen_set_label(done_3);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);

  return ret;
}





/* BBIT1L
 *    Variables: @b, @c, @rd
 *    Functions: getCCFlag, getPCL, shouldExecuteDelaySlot, executeDelaySlot, setPC
--- code ---
{
  take_branch = false;
  cc_flag = getCCFlag ();
  p_b = @b;
  p_c = (@c & 63);
  tmp = (1 << p_c);
  if((cc_flag == true))
    {
      if(((p_b && tmp) != 0))
        {
          take_branch = true;
        };
    };
  bta = (getPCL () + @rd);
  if((shouldExecuteDelaySlot () == true))
    {
      executeDelaySlot (bta, take_branch);
    };
  if((cc_flag == true))
    {
      if(((p_b && tmp) != 0))
        {
          setPC (bta);
        };
    };
}
 */

int
arc_gen_BBIT1L (DisasCtxt *ctx, TCGv b, TCGv c, TCGv rd)
{
  int ret = DISAS_NEXT;
  TCGv take_branch = tcg_temp_local_new();
  TCGv temp_11 = tcg_temp_local_new();
  TCGv cc_flag = tcg_temp_local_new();
  TCGv p_b = tcg_temp_local_new();
  TCGv p_c = tcg_temp_local_new();
  TCGv tmp = tcg_temp_local_new();
  TCGv temp_1 = tcg_temp_local_new();
  TCGv temp_2 = tcg_temp_local_new();
  TCGv temp_3 = tcg_temp_local_new();
  TCGv temp_4 = tcg_temp_local_new();
  TCGv temp_5 = tcg_temp_local_new();
  TCGv temp_13 = tcg_temp_local_new();
  TCGv temp_12 = tcg_temp_local_new();
  TCGv bta = tcg_temp_local_new();
  TCGv temp_6 = tcg_temp_local_new();
  TCGv temp_7 = tcg_temp_local_new();
  TCGv temp_8 = tcg_temp_local_new();
  TCGv temp_9 = tcg_temp_local_new();
  TCGv temp_10 = tcg_temp_local_new();
  tcg_gen_mov_tl(take_branch, arc_false);
  getCCFlag(temp_11);
  tcg_gen_mov_tl(cc_flag, temp_11);
  tcg_gen_mov_tl(p_b, b);
  tcg_gen_andi_tl(p_c, c, 63);
  tcg_gen_shlfi_tl(tmp, 1, p_c);
  TCGLabel *done_1 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_1, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_2, temp_1, 1); tcg_gen_andi_tl(temp_2, temp_2, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_2, arc_true, done_1);;
  TCGLabel *done_2 = gen_new_label();
  tcg_gen_and_tl(temp_3, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_4, temp_3, 0);
  tcg_gen_xori_tl(temp_5, temp_4, 1); tcg_gen_andi_tl(temp_5, temp_5, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_5, arc_true, done_2);;
  tcg_gen_mov_tl(take_branch, arc_true);
  gen_set_label(done_2);
  gen_set_label(done_1);
  getPCL(temp_13);
  tcg_gen_mov_tl(temp_12, temp_13);
  tcg_gen_add_tl(bta, temp_12, rd);
  if ((shouldExecuteDelaySlot () == true))
    {
    executeDelaySlot(bta, take_branch);
;
    }
  else
    {
  ;
    }
  TCGLabel *done_3 = gen_new_label();
  tcg_gen_setcond_tl(TCG_COND_EQ, temp_6, cc_flag, arc_true);
  tcg_gen_xori_tl(temp_7, temp_6, 1); tcg_gen_andi_tl(temp_7, temp_7, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_7, arc_true, done_3);;
  TCGLabel *done_4 = gen_new_label();
  tcg_gen_and_tl(temp_8, p_b, tmp);
  tcg_gen_setcondi_tl(TCG_COND_NE, temp_9, temp_8, 0);
  tcg_gen_xori_tl(temp_10, temp_9, 1); tcg_gen_andi_tl(temp_10, temp_10, 1);;
  tcg_gen_brcond_tl(TCG_COND_EQ, temp_10, arc_true, done_4);;
  setPC(bta);
  gen_set_label(done_4);
  gen_set_label(done_3);
  tcg_temp_free(take_branch);
  tcg_temp_free(temp_11);
  tcg_temp_free(cc_flag);
  tcg_temp_free(p_b);
  tcg_temp_free(p_c);
  tcg_temp_free(tmp);
  tcg_temp_free(temp_1);
  tcg_temp_free(temp_2);
  tcg_temp_free(temp_3);
  tcg_temp_free(temp_4);
  tcg_temp_free(temp_5);
  tcg_temp_free(temp_13);
  tcg_temp_free(temp_12);
  tcg_temp_free(bta);
  tcg_temp_free(temp_6);
  tcg_temp_free(temp_7);
  tcg_temp_free(temp_8);
  tcg_temp_free(temp_9);
  tcg_temp_free(temp_10);

  return ret;
}

int
arc_gen_VPACK4HL(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  TCGv b_h0 = tcg_temp_new();
  TCGv b_h2 = tcg_temp_new();
  TCGv c_h0 = tcg_temp_new();
  TCGv c_h2 = tcg_temp_new();

  TCGv cc_temp = tcg_temp_local_new();
  TCGLabel *cc_done = gen_new_label();

  /* Conditional execution */
  getCCFlag(cc_temp);
  tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

  /* Instruction code */

  tcg_gen_sextract_tl(b_h0, b, 0, 16);
  tcg_gen_sextract_tl(b_h2, b, 32, 16);
  tcg_gen_sextract_tl(c_h0, c, 0, 16);
  tcg_gen_sextract_tl(c_h2, c, 32, 16);

  tcg_gen_mov_tl(a, b_h0);
  tcg_gen_deposit_tl(a, a, b_h2, 16, 16);
  tcg_gen_deposit_tl(a, a, c_h0, 32, 16);
  tcg_gen_deposit_tl(a, a, c_h2, 48, 16);

  /* Conditional execution end. */
  gen_set_label(cc_done);
  tcg_temp_free(cc_temp);

  tcg_temp_free(b_h0);
  tcg_temp_free(b_h2);
  tcg_temp_free(c_h0);
  tcg_temp_free(c_h2);
    
  return DISAS_NEXT;
}

int
arc_gen_VPACK4HM(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  TCGv b_h1 = tcg_temp_new();
  TCGv b_h3 = tcg_temp_new();
  TCGv c_h1 = tcg_temp_new();
  TCGv c_h3 = tcg_temp_new();

  TCGv cc_temp = tcg_temp_local_new();
  TCGLabel *cc_done = gen_new_label();

  /* Conditional execution */
  getCCFlag(cc_temp);
  tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

  /* Instruction code */

  tcg_gen_sextract_tl(b_h1, b, 16, 16);
  tcg_gen_sextract_tl(b_h3, b, 48, 16);
  tcg_gen_sextract_tl(c_h1, c, 16, 16);
  tcg_gen_sextract_tl(c_h3, c, 48, 16);

  tcg_gen_mov_tl(a, b_h1);
  tcg_gen_deposit_tl(a, a, b_h3, 16, 16);
  tcg_gen_deposit_tl(a, a, c_h1, 32, 16);
  tcg_gen_deposit_tl(a, a, c_h3, 48, 16);

  /* Conditional execution end. */
  gen_set_label(cc_done);
  tcg_temp_free(cc_temp);

  tcg_temp_free(b_h1);
  tcg_temp_free(b_h3);
  tcg_temp_free(c_h1);
  tcg_temp_free(c_h3);
    
  return DISAS_NEXT;
}

int
arc_gen_VPACK2WL(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  TCGv b_w0 = tcg_temp_new();
  TCGv c_w0 = tcg_temp_new();
  
  TCGv cc_temp = tcg_temp_local_new();
  TCGLabel *cc_done = gen_new_label();

  /* Conditional execution */
  getCCFlag(cc_temp);
  tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

  /* Instruction code */

  tcg_gen_sextract_tl(b_w0, b, 0, 32);
  tcg_gen_sextract_tl(c_w0, c, 0, 32);

  tcg_gen_mov_tl(a, b_w0);
  tcg_gen_deposit_tl(a, a, c_w0, 32, 32);

  /* Conditional execution end. */
  gen_set_label(cc_done);
  tcg_temp_free(cc_temp);

  tcg_temp_free(b_w0);
  tcg_temp_free(c_w0);
    
  return DISAS_NEXT;
}

int
arc_gen_VPACK2WM(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  TCGv b_w1 = tcg_temp_new();
  TCGv c_w1 = tcg_temp_new();
  
  TCGv cc_temp = tcg_temp_local_new();
  TCGLabel *cc_done = gen_new_label();

  /* Conditional execution */
  getCCFlag(cc_temp);
  tcg_gen_brcondi_tl(TCG_COND_EQ, cc_temp, 0, cc_done);

  /* Instruction code */

  tcg_gen_sextract_tl(b_w1, b, 32, 32);
  tcg_gen_sextract_tl(c_w1, c, 32, 32);

  tcg_gen_mov_tl(a, b_w1);
  tcg_gen_deposit_tl(a, a, c_w1, 32, 32);

  /* Conditional execution end. */
  gen_set_label(cc_done);
  tcg_temp_free(cc_temp);

  tcg_temp_free(b_w1);
  tcg_temp_free(c_w1);
    
  return DISAS_NEXT;
}

#define VEC_ADD16_SUB16_I64_W0(NAME, OP)                 \
static void                                              \
arc_gen_vec_##NAME##16_i64_w0(TCGv dest, TCGv b, TCGv c) \
{                                                        \
  TCGv t1 = tcg_temp_new();                              \
                                                         \
  OP(t1, b, c);                                          \
  tcg_gen_deposit_i64(dest, dest, t1, 0, 32);            \
                                                         \
  tcg_temp_free(t1);                                     \
}

VEC_ADD16_SUB16_I64_W0(add, tcg_gen_vec_add16_i64)
VEC_ADD16_SUB16_I64_W0(sub, tcg_gen_vec_sub16_i64)

#define VEC_ADD_SUB(INSN, OP, FIELD_SIZE)                 \
int                                                       \
arc_gen_##INSN(DisasCtxt *ctx, TCGv dest, TCGv b, TCGv c) \
{                                                         \
    ARC_GEN_SEMFUNC_INIT();                               \
                                                          \
    ARC_GEN_VEC_FIRST_OPERAND(operand_##FIELD_SIZE, b);   \
    ARC_GEN_VEC_SECOND_OPERAND(operand_##FIELD_SIZE, c);  \
                                                          \
    /* Instruction code */                                \
    OP(dest, b, c);                                       \
                                                          \
    ARC_GEN_SEMFUNC_DEINIT();                             \
    return DISAS_NEXT;                                    \
}

VEC_ADD_SUB(VADD2,  tcg_gen_vec_add32_i64,    32bit)
VEC_ADD_SUB(VADD2H, arc_gen_vec_add16_i64_w0, 16bit)
VEC_ADD_SUB(VADD4H, tcg_gen_vec_add16_i64,    16bit)
VEC_ADD_SUB(VSUB2,  tcg_gen_vec_sub32_i64,    32bit)
VEC_ADD_SUB(VSUB2H, arc_gen_vec_sub16_i64_w0, 16bit)
VEC_ADD_SUB(VSUB4H, tcg_gen_vec_sub16_i64,    16bit)



static void
arc_gen_vmac2_op(DisasCtxt *ctx, TCGv dest, TCGv b, TCGv c,
                 void (*OP)(TCGv, TCGv, unsigned int, unsigned int))
{
  TCGv t1 = tcg_temp_new();
  TCGv t2 = tcg_temp_new();
  TCGv t3 = tcg_temp_new();
  TCGv t4 = tcg_temp_new();

  OP(t1, b, 0, 16);                           /* t1 = b.h0 */
  OP(t2, c, 0, 16);                           /* t2 = c.h0 */
  tcg_gen_mul_tl(t3, t1, t2);                 /* t3 = b.h0 * c.h0 */ 
  tcg_gen_extract_tl(t2, cpu64_acc, 0, 32);   /* t2 = acclo */
  tcg_gen_add_tl(t3, t3, t2);                 /* t3 = (b.h0 * c.h0) + acclo */

  OP(t1, b, 16, 16);                          /* t1 = b.h1 */
  OP(t2, c, 16, 16);                          /* t2 = c.h1 */
  tcg_gen_mul_tl(t4, t1, t2);                 /* t4 = b.h1 * c.h1 */
  tcg_gen_extract_tl(t2, cpu64_acc, 32, 32);  /* t2 = acchi */
  tcg_gen_add_tl(t4, t4, t2);                 /* t4 = (b.h1 * c.h1) + acchi */

  tcg_gen_deposit_tl(dest, dest, t3, 0, 32);  /* dest.w0 = (b.h0 * c.h0) + acclo */
  tcg_gen_deposit_tl(dest, dest, t4, 32, 32); /* dest.w1 = (b.h1 * c.h1) + acchi */
  tcg_gen_mov_tl(cpu64_acc, dest);            /* acc = dest */

  tcg_temp_free(t1);
  tcg_temp_free(t2);
  tcg_temp_free(t3);
  tcg_temp_free(t4);
}

#define ARC_GEN_VEC_MAC2H(INSN, OP, FIELD_SIZE)             \
int                                                         \
arc_gen_##INSN(DisasCtxt *ctx, TCGv dest, TCGv b, TCGv c)   \
{                                                           \
    ARC_GEN_SEMFUNC_INIT();                                 \
                                                            \
    ARC_GEN_VEC_FIRST_OPERAND(operand_##FIELD_SIZE, b);     \
    ARC_GEN_VEC_SECOND_OPERAND(operand_##FIELD_SIZE, c);    \
                                                            \
    arc_gen_vmac2_op(ctx, dest, b, c, OP);                  \
                                                            \
    ARC_GEN_SEMFUNC_DEINIT();                               \
                                                            \
    return DISAS_NEXT;                                      \
}  

ARC_GEN_VEC_MAC2H(VMAC2H, tcg_gen_sextract_tl, 16bit)
ARC_GEN_VEC_MAC2H(VMAC2HU, tcg_gen_extract_tl, 16bit)

#define ARC_GEN_VEC_ADD_SUB(INSN, FIELD, OP, FIELD_SIZE)      \
int                                                           \
arc_gen_##INSN(DisasCtxt *ctx, TCGv dest, TCGv b, TCGv c)     \
{                                                             \
    TCGv t1;                                                  \
    ARC_GEN_SEMFUNC_INIT();                                   \
                                                              \
    ARC_GEN_VEC_FIRST_OPERAND(operand_##FIELD_SIZE, b);       \
    ARC_GEN_VEC_SECOND_OPERAND(operand_##FIELD_SIZE, c);      \
                                                              \
    t1 = tcg_temp_new();                                      \
    ARC_GEN_CMPL2_##FIELD##_I64(t1, c);                       \
    OP(dest, b, t1);                                          \
    tcg_temp_free(t1);                                        \
                                                              \
    ARC_GEN_SEMFUNC_DEINIT();                                 \
                                                              \
    return DISAS_NEXT;                                        \
}


ARC_GEN_VEC_ADD_SUB(VADDSUB, W1, tcg_gen_vec_add32_i64,      32bit)
ARC_GEN_VEC_ADD_SUB(VADDSUB2H, H1, arc_gen_vec_add16_w0_i64, 16bit)
ARC_GEN_VEC_ADD_SUB(VADDSUB4H, H1_H3, tcg_gen_vec_add16_i64, 16bit)
ARC_GEN_VEC_ADD_SUB(VSUBADD, W0, tcg_gen_vec_add32_i64,      32bit)
ARC_GEN_VEC_ADD_SUB(VSUBADD2H, H0, arc_gen_vec_add16_w0_i64, 16bit)
ARC_GEN_VEC_ADD_SUB(VSUBADD4H, H0_H2, tcg_gen_vec_add16_i64, 16bit)

int
arc_gen_QMACH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_qmach_base_i64(ctx, a, b, c, cpu64_acc, true, \
                           tcg_gen_sextract_i64, \
                           arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_QMACHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_qmach_base_i64(ctx, a, b, c, cpu64_acc, false, \
                           tcg_gen_extract_i64, \
                           arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMACWH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmacwh_base_i64(ctx, a, b, c, cpu64_acc, true, \
                            tcg_gen_sextract_i64, \
                            arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMACWHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmacwh_base_i64(ctx, a, b, c, cpu64_acc, false, \
                            tcg_gen_extract_i64, \
                            arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMACH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  ARC_GEN_SEMFUNC_INIT();

  arc_gen_dmach_base_i64(ctx, a, b, c, cpu64_acc, true, \
                         tcg_gen_sextract_i64, \
                         arc_gen_add_signed_overflow_i64);

  ARC_GEN_SEMFUNC_DEINIT();

  return DISAS_NEXT;
}

int
arc_gen_DMACHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
  ARC_GEN_SEMFUNC_INIT();

  arc_gen_dmach_base_i64(ctx, a, b, c, cpu64_acc, false, \
                         tcg_gen_extract_i64, \
                         arc_gen_add_unsigned_overflow_i64);

  ARC_GEN_SEMFUNC_DEINIT();

  return DISAS_NEXT;
}

int
arc_gen_DMPYH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmpyh_base_i64(ctx, a, b, c, cpu64_acc, true, \
                            tcg_gen_sextract_i64, \
                            arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMPYHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmpyh_base_i64(ctx, a, b, c, cpu64_acc, false, \
                            tcg_gen_extract_i64, \
                            arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_QMPYH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_qmpyh_base_i64(ctx, a, b, c, cpu64_acc, true, \
                            tcg_gen_sextract_i64, \
                            arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_QMPYHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_qmpyh_base_i64(ctx, a, b, c, cpu64_acc, false, \
                            tcg_gen_extract_i64, \
                            arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMPYWH(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmpywh_base_i64(ctx, a, b, c, cpu64_acc, true, \
                            tcg_gen_sextract_i64, \
                            arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_DMPYWHU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_dmpywh_base_i64(ctx, a, b, c, cpu64_acc, false, \
                            tcg_gen_extract_i64, \
                            arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_VMPY2H(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_vmpy2h_base_i64(ctx, a, b, c, cpu64_acc, true, \
                            tcg_gen_sextract_i64, \
                            arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_VMPY2HU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_vmpy2h_base_i64(ctx, a, b, c, cpu64_acc, false, \
                            tcg_gen_extract_i64, \
                            arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_MPYD(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_mpyd_base_i64(ctx, a, b, c, cpu64_acc, true, \
                          tcg_gen_sextract_i64, \
                          arc_gen_add_signed_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}

int
arc_gen_MPYDU(DisasCtxt *ctx, TCGv a, TCGv b, TCGv c)
{
    ARC_GEN_SEMFUNC_INIT();

    arc_gen_mpyd_base_i64(ctx, a, b, c, cpu64_acc, false, \
                          tcg_gen_extract_i64, \
                          arc_gen_add_unsigned_overflow_i64);

    ARC_GEN_SEMFUNC_DEINIT();

    return DISAS_NEXT;
}
