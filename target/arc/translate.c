/*
 *  QEMU ARC CPU
 *
 *  Copyright (c) 2016 Michael Rolnik
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

#include "translate.h"

TCGv_env cpu_env;

TCGv     cpu_gp;        /*  Global Pointer                      */
TCGv     cpu_fp;        /*  Frame Pointer                       */
TCGv     cpu_sp;        /*  Stack Pointer                       */
TCGv     cpu_ilink1;    /*  Level 1 interrupt link register     */
TCGv     cpu_ilink2;    /*  Level 2 interrupt link register     */
TCGv     cpu_blink;     /*  Branch link register                */
TCGv     cpu_limm;      /*  Long immediate data indicator       */
TCGv     cpu_pcl;       /*  Program Counter [31:2], read-only,
                                    32-bit aligned address.     */

TCGv     cpu_mlo;       /*  Multiply low 32 bits, read only     */
TCGv     cpu_mmi;       /*  Multiply middle 32 bits, read only  */
TCGv     cpu_mhi;       /*  Multiply high 32 bits, read only    */

TCGv     cpu_S1f;
TCGv     cpu_S2f;
TCGv     cpu_CSf;

TCGv     cpu_Lf;
TCGv     cpu_Zf;
TCGv     cpu_Nf;
TCGv     cpu_Cf;
TCGv     cpu_Vf;
TCGv     cpu_Uf;

TCGv     cpu_DEf;
TCGv     cpu_AEf;
TCGv     cpu_A2f;
TCGv     cpu_A1f;
TCGv     cpu_E2f;
TCGv     cpu_E1f;
TCGv     cpu_Hf;

TCGv     cpu_l1_Lf;
TCGv     cpu_l1_Zf;
TCGv     cpu_l1_Nf;
TCGv     cpu_l1_Cf;
TCGv     cpu_l1_Vf;
TCGv     cpu_l1_Uf;

TCGv     cpu_l1_DEf;
TCGv     cpu_l1_AEf;
TCGv     cpu_l1_A2f;
TCGv     cpu_l1_A1f;
TCGv     cpu_l1_E2f;
TCGv     cpu_l1_E1f;
TCGv     cpu_l1_Hf;

TCGv     cpu_l2_Lf;
TCGv     cpu_l2_Zf;
TCGv     cpu_l2_Nf;
TCGv     cpu_l2_Cf;
TCGv     cpu_l2_Vf;
TCGv     cpu_l2_Uf;

TCGv     cpu_l2_DEf;
TCGv     cpu_l2_AEf;
TCGv     cpu_l2_A2f;
TCGv     cpu_l2_A1f;
TCGv     cpu_l2_E2f;
TCGv     cpu_l2_E1f;
TCGv     cpu_l2_Hf;

TCGv     cpu_er_Lf;
TCGv     cpu_er_Zf;
TCGv     cpu_er_Nf;
TCGv     cpu_er_Cf;
TCGv     cpu_er_Vf;
TCGv     cpu_er_Uf;

TCGv     cpu_er_DEf;
TCGv     cpu_er_AEf;
TCGv     cpu_er_A2f;
TCGv     cpu_er_A1f;
TCGv     cpu_er_E2f;
TCGv     cpu_er_E1f;
TCGv     cpu_er_Hf;

TCGv     cpu_eret;
TCGv     cpu_erbta;
TCGv     cpu_ecr;
TCGv     cpu_efa;

TCGv     cpu_bta;
TCGv     cpu_bta_l1;
TCGv     cpu_bta_l2;

TCGv     cpu_pc;
TCGv     cpu_lpc; 
// replaced by AUX_REG array
TCGv     cpu_lps;
TCGv     cpu_lpe;

TCGv     cpu_r[64];

TCGv     cpu_intvec;

TCGv     cpu_debug_LD;
TCGv     cpu_debug_SH;
TCGv     cpu_debug_BH;
TCGv     cpu_debug_UB;
TCGv     cpu_debug_ZZ;
TCGv     cpu_debug_RA;
TCGv     cpu_debug_IS;
TCGv     cpu_debug_FH;
TCGv     cpu_debug_SS;

#include "exec/gen-icount.h"
#define REG(x)  (cpu_r[x])

static inline bool use_goto_tb(DisasCtxt *dc, target_ulong dest)
{
#ifndef CONFIG_USER_ONLY
    return (dc->tb->pc & TARGET_PAGE_MASK) == (dest & TARGET_PAGE_MASK);
#else
    return true;
#endif
}

void gen_goto_tb(DisasCtxt *ctx, int n, TCGv dest)
{
  TranslationBlock   *tb;
  tb = ctx->tb;

#if 1
    tcg_gen_goto_tb(n);
    tcg_gen_mov_tl(cpu_pc, dest);
    tcg_gen_andi_tl(cpu_pcl, dest, 0xfffffffc);
    tcg_gen_exit_tb((uintptr_t)tb + n);
#else
    tcg_gen_mov_tl(cpu_pc,  dest);
    tcg_gen_andi_tl(cpu_pcl, dest, 0xfffffffc);
    tcg_gen_exit_tb(0);
#endif
}
static void  gen_gotoi_tb(DisasCtxt *ctx, int n, target_ulong dest)
{
    TranslationBlock   *tb;
    tb = ctx->tb;

    if (use_goto_tb(ctx, dest)) {
        tcg_gen_goto_tb(n);
        tcg_gen_movi_tl(cpu_pc, dest);
        tcg_gen_movi_tl(cpu_pcl, dest & 0xfffffffc);
        tcg_gen_exit_tb((uintptr_t)tb + n);
    } else {
        tcg_gen_movi_tl(cpu_pc, dest);
        tcg_gen_movi_tl(cpu_pcl, dest & 0xfffffffc);
        tcg_gen_exit_tb(0);
    }
}

void arc_translate_init(void)
{
    int i;
    static int init_not_done = 1;

    if (init_not_done == 0) {
        return;
    }
#define ARC_REG_OFFS(x) offsetof(CPUARCState, x)

#define NEW_ARC_REG(x) \
        tcg_global_mem_new_i32(cpu_env, offsetof(CPUARCState, x), #x)

    cpu_env = tcg_global_reg_new_ptr(TCG_AREG0, "env");

    cpu_S1f = NEW_ARC_REG(macmod.S1);
    cpu_S2f = NEW_ARC_REG(macmod.S2);
    cpu_CSf = NEW_ARC_REG(macmod.CS);

    cpu_Zf = NEW_ARC_REG(stat.Zf);
    cpu_Lf = NEW_ARC_REG(stat.Lf);
    cpu_Nf = NEW_ARC_REG(stat.Nf);
    cpu_Cf = NEW_ARC_REG(stat.Cf);
    cpu_Vf = NEW_ARC_REG(stat.Vf);
    cpu_Uf = NEW_ARC_REG(stat.Uf);
    cpu_DEf = NEW_ARC_REG(stat.DEf);
    cpu_AEf = NEW_ARC_REG(stat.AEf);
    cpu_A2f = NEW_ARC_REG(stat.A2f);
    cpu_A1f = NEW_ARC_REG(stat.A1f);
    cpu_E2f = NEW_ARC_REG(stat.E2f);
    cpu_E1f = NEW_ARC_REG(stat.E1f);
    cpu_Hf = NEW_ARC_REG(stat.Hf);

    cpu_l1_Zf = NEW_ARC_REG(stat_l1.Zf);
    cpu_l1_Lf = NEW_ARC_REG(stat_l1.Lf);
    cpu_l1_Nf = NEW_ARC_REG(stat_l1.Nf);
    cpu_l1_Cf = NEW_ARC_REG(stat_l1.Cf);
    cpu_l1_Vf = NEW_ARC_REG(stat_l1.Vf);
    cpu_l1_Uf = NEW_ARC_REG(stat_l1.Uf);
    cpu_l1_DEf = NEW_ARC_REG(stat_l1.DEf);
    cpu_l1_AEf = NEW_ARC_REG(stat_l1.AEf);
    cpu_l1_A2f = NEW_ARC_REG(stat_l1.A2f);
    cpu_l1_A1f = NEW_ARC_REG(stat_l1.A1f);
    cpu_l1_E2f = NEW_ARC_REG(stat_l1.E2f);
    cpu_l1_E1f = NEW_ARC_REG(stat_l1.E1f);
    cpu_l1_Hf = NEW_ARC_REG(stat_l1.Hf);

    cpu_l2_Zf = NEW_ARC_REG(stat_l2.Zf);
    cpu_l2_Lf = NEW_ARC_REG(stat_l2.Lf);
    cpu_l2_Nf = NEW_ARC_REG(stat_l2.Nf);
    cpu_l2_Cf = NEW_ARC_REG(stat_l2.Cf);
    cpu_l2_Vf = NEW_ARC_REG(stat_l2.Vf);
    cpu_l2_Uf = NEW_ARC_REG(stat_l2.Uf);
    cpu_l2_DEf = NEW_ARC_REG(stat_l2.DEf);
    cpu_l2_AEf = NEW_ARC_REG(stat_l2.AEf);
    cpu_l2_A2f = NEW_ARC_REG(stat_l2.A2f);
    cpu_l2_A1f = NEW_ARC_REG(stat_l2.A1f);
    cpu_l2_E2f = NEW_ARC_REG(stat_l2.E2f);
    cpu_l2_E1f = NEW_ARC_REG(stat_l2.E1f);
    cpu_l2_Hf = NEW_ARC_REG(stat_l2.Hf);

    cpu_er_Zf = NEW_ARC_REG(stat_er.Zf);
    cpu_er_Lf = NEW_ARC_REG(stat_er.Lf);
    cpu_er_Nf = NEW_ARC_REG(stat_er.Nf);
    cpu_er_Cf = NEW_ARC_REG(stat_er.Cf);
    cpu_er_Vf = NEW_ARC_REG(stat_er.Vf);
    cpu_er_Uf = NEW_ARC_REG(stat_er.Uf);
    cpu_er_DEf = NEW_ARC_REG(stat_er.DEf);
    cpu_er_AEf = NEW_ARC_REG(stat_er.AEf);
    cpu_er_A2f = NEW_ARC_REG(stat_er.A2f);
    cpu_er_A1f = NEW_ARC_REG(stat_er.A1f);
    cpu_er_E2f = NEW_ARC_REG(stat_er.E2f);
    cpu_er_E1f = NEW_ARC_REG(stat_er.E1f);
    cpu_er_Hf = NEW_ARC_REG(stat_er.Hf);

    cpu_eret = NEW_ARC_REG(eret);
    cpu_erbta = NEW_ARC_REG(erbta);
    cpu_ecr = NEW_ARC_REG(ecr);
    cpu_efa = NEW_ARC_REG(efa);
    cpu_bta = NEW_ARC_REG(bta);
    cpu_lps = NEW_ARC_REG(lps);
    cpu_lpe = NEW_ARC_REG(lpe);
    cpu_pc = NEW_ARC_REG(pc);

    cpu_bta_l1 = NEW_ARC_REG(bta_l1);
    cpu_bta_l2 = NEW_ARC_REG(bta_l2);

    cpu_intvec = NEW_ARC_REG(intvec);

    for (i = 0; i < 64; i++) {
        char    name[16];

        sprintf(name, "r[%d]", i);

        cpu_r[i] = tcg_global_mem_new_i32(cpu_env, ARC_REG_OFFS(r[i]), strdup(name));
    }

    cpu_gp = cpu_r[26];
    cpu_fp = cpu_r[27];
    cpu_sp = cpu_r[28];
    cpu_ilink1 = cpu_r[29];
    cpu_ilink2 = cpu_r[30];
    cpu_blink = cpu_r[31];
    cpu_mlo = cpu_r[57];
    cpu_mmi = cpu_r[58];
    cpu_mhi = cpu_r[59];
    cpu_lpc = cpu_r[60];
    cpu_limm = cpu_r[62];
    cpu_pcl = cpu_r[63];

    cpu_debug_LD = NEW_ARC_REG(debug.LD);
    cpu_debug_SH = NEW_ARC_REG(debug.SH);
    cpu_debug_BH = NEW_ARC_REG(debug.BH);
    cpu_debug_UB = NEW_ARC_REG(debug.UB);
    cpu_debug_ZZ = NEW_ARC_REG(debug.ZZ);
    cpu_debug_RA = NEW_ARC_REG(debug.RA);
    cpu_debug_IS = NEW_ARC_REG(debug.IS);
    cpu_debug_FH = NEW_ARC_REG(debug.FH);
    cpu_debug_SS = NEW_ARC_REG(debug.SS);
    
    init_not_done = 0;
}

void gen_intermediate_code(CPUState *cs, struct TranslationBlock *tb)
{
    CPUARCState *env = cs->env_ptr;
    DisasCtxt ctx;
    target_ulong pc_start;
    int num_insns;
    int max_insns;
    uint32_t next_page_start;

    pc_start = tb->pc;
    ctx.tb = tb;
    ctx.memidx = 0;
    ctx.bstate = BS_NONE;
    ctx.singlestep = cs->singlestep_enabled;

    next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;
    num_insns = 0;
    max_insns = tb->cflags & CF_COUNT_MASK;

    if (max_insns == 0) {
        max_insns = CF_COUNT_MASK;
    }
    if (max_insns > TCG_MAX_INSNS) {
        max_insns = TCG_MAX_INSNS;
    }

    gen_tb_start(tb);

    ctx.zero = tcg_const_local_i32(0);
    ctx.one = tcg_const_local_i32(1);

    ctx.npc = pc_start;
    ctx.env = env;
    ctx.ds = 0;

    do {
        ctx.cpc = ctx.npc;
        ctx.pcl = ctx.cpc & 0xfffffffc;

        tcg_gen_insn_start(ctx.cpc);
        num_insns++;

        if (unlikely(cpu_breakpoint_test(cs, ctx.cpc, BP_ANY)))
	  {
            tcg_gen_movi_i32(cpu_pc, ctx.cpc);
            gen_helper_debug(cpu_env);
            ctx.bstate = BS_EXCP;
            break;
          }

        if (num_insns == max_insns && (tb->cflags & CF_LAST_IO)) {
            gen_io_start();
        }

        int tmp = arc_decode (&ctx);
        if (ctx.bstate == BS_BRANCH_DS)
          num_insns++;
        else
          ctx.bstate = tmp;

	/* Hardware loop control code */
	if (ctx.npc == env->lpe)
	  {
            TCGLabel *label = gen_new_label();
            tcg_gen_subi_tl(cpu_lpc, cpu_lpc, 1);
            tcg_gen_brcondi_i32(TCG_COND_EQ, cpu_lpc, 0, label);
	    gen_goto_tb(&ctx, 0, cpu_lps);
            gen_set_label(label);
	    gen_gotoi_tb(&ctx, 1, ctx.npc);

            ctx.bstate = BS_BRANCH_HW_LOOP;
	  }

    } while (ctx.bstate == BS_NONE
             && !tcg_op_buf_full()
             && !ctx.singlestep
             && (num_insns < max_insns)
             && (ctx.cpc < next_page_start));

    if (tb->cflags & CF_LAST_IO) {
        gen_io_end();
    }

    if (ctx.singlestep) {
	assert(0); // TODO
        if (ctx.bstate == BS_STOP || ctx.bstate == BS_NONE) {
            tcg_gen_movi_tl(cpu_pc, ctx.npc);
            tcg_gen_movi_tl(cpu_pcl, ctx.npc & 0xfffffffc);
        }
        gen_helper_debug(cpu_env);
        //tcg_gen_exit_tb(0);
    } else {
        switch (ctx.bstate) {
        case BS_STOP:
        case BS_NONE:
            gen_gotoi_tb(&ctx, 0, ctx.npc);
            break;
        case BS_BRANCH_DS:
          //ctx.npc = ctx.dpc;
        case BS_BRANCH:
	    {
	    //  TCGLabel *skip_fallthrough = gen_new_label();
	    //  // NOTE: cpu_pc is not update on every single instruction on non single step mode.
	    //  // For that reason we should compare cpu_pc with tb->pc instead of the instruction pc.
	    //  tcg_gen_brcondi_i32(TCG_COND_NE, cpu_pc, tb->pc, skip_fallthrough);
	    //  //tcg_gen_movi_tl (cpu_pc, ctx.npc);
	      gen_gotoi_tb(&ctx, 0, ctx.npc);
	    //tcg_gen_exit_tb(0);
	    //  gen_set_label (skip_fallthrough);
	    }
	    break;
	case BS_BRANCH_HW_LOOP:
        case BS_EXCP:
            //tcg_gen_exit_tb(0);
            break;
        default:
            break;
        }
    }

    tcg_temp_free_i32(ctx.one);
    tcg_temp_free_i32(ctx.zero);

    gen_tb_end(tb, num_insns);

    tb->size = (ctx.npc - pc_start);
    tb->icount = num_insns;

#ifdef DEBUG_DISAS
    if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)
        && qemu_log_in_addr_range(pc_start)) {
        qemu_log_lock();
        qemu_log("------------------\n");
        log_target_disas(cs, pc_start, ctx.npc - pc_start, 0);
        qemu_log("\nisize=%d osize=%d\n",
                 ctx.npc - pc_start, tcg_op_buf_count());
        qemu_log_unlock();
    }
#endif

}

void restore_state_to_opc(CPUARCState *env, TranslationBlock *tb,
                                                            target_ulong *data)
{
    env->pc = data[0];
}

void arc_cpu_dump_state(CPUState *cs, FILE *f, fprintf_function cpu_fprintf,
                            int flags)
{
    ARCCPU *cpu = ARC_CPU(cs);
    CPUARCState *env = &cpu->env;
    int i;

    cpu_fprintf(f, "STATUS:  [ %c %c %c %c %c %c %s %s %s %s %s %s %c]\n",
                        env->stat.Lf ? 'L' : '-',
                        env->stat.Zf ? 'Z' : '-',
                        env->stat.Nf ? 'N' : '-',
                        env->stat.Cf ? 'C' : '-',
                        env->stat.Vf ? 'V' : '-',
                        env->stat.Uf ? 'U' : '-',
                        env->stat.DEf ? "DE" : "--",
                        env->stat.AEf ? "AE" : "--",
                        env->stat.A2f ? "A2" : "--",
                        env->stat.A1f ? "A1" : "--",
                        env->stat.E2f ? "E2" : "--",
                        env->stat.E1f ? "E1" : "--",
                        env->stat.Hf ? 'H' : '-'
                        );

    cpu_fprintf(f, "\n");
    for (i = 0; i < ARRAY_SIZE(env->r); i++) {
        cpu_fprintf(f, "R[%02d]:  %02x   ", i, env->r[i]);

        if ((i % 8) == 7) {
            cpu_fprintf(f, "\n");
        }
    }
}
