
SEMANTIC_FUNCTION(NEG, 2)
SEMANTIC_FUNCTION(ADD, 3)
SEMANTIC_FUNCTION(ADD1, 3)
SEMANTIC_FUNCTION(ADD2, 3)
SEMANTIC_FUNCTION(ADD3, 3)
SEMANTIC_FUNCTION(ADC, 3)
SEMANTIC_FUNCTION(SBC, 3)
SEMANTIC_FUNCTION(SUB, 3)
SEMANTIC_FUNCTION(SUB1, 3)
SEMANTIC_FUNCTION(SUB2, 3)
SEMANTIC_FUNCTION(SUB3, 3)
SEMANTIC_FUNCTION(MAX, 3)
SEMANTIC_FUNCTION(MIN, 3)
SEMANTIC_FUNCTION(CMP, 2)
SEMANTIC_FUNCTION(AND, 3)
SEMANTIC_FUNCTION(OR, 3)
SEMANTIC_FUNCTION(XOR, 3)
SEMANTIC_FUNCTION(MOV, 2)
SEMANTIC_FUNCTION(ASL, 3)
SEMANTIC_FUNCTION(ASR, 3)
SEMANTIC_FUNCTION(ASR8, 2)
SEMANTIC_FUNCTION(ASR16, 2)
SEMANTIC_FUNCTION(LSL16, 2)
SEMANTIC_FUNCTION(LSL8, 2)
SEMANTIC_FUNCTION(LSR, 3)
SEMANTIC_FUNCTION(LSR16, 2)
SEMANTIC_FUNCTION(LSR8, 2)
SEMANTIC_FUNCTION(BIC, 3)
SEMANTIC_FUNCTION(BCLR, 3)
SEMANTIC_FUNCTION(BMSK, 3)
SEMANTIC_FUNCTION(BMSKN, 3)
SEMANTIC_FUNCTION(BSET, 3)
SEMANTIC_FUNCTION(BXOR, 3)
SEMANTIC_FUNCTION(ROL, 3)
SEMANTIC_FUNCTION(ROR, 3)
SEMANTIC_FUNCTION(RLC, 2)
SEMANTIC_FUNCTION(RRC, 2)
SEMANTIC_FUNCTION(SEXB, 2)
SEMANTIC_FUNCTION(SEXH, 2)
SEMANTIC_FUNCTION(EXTB, 2)
SEMANTIC_FUNCTION(EXTH, 2)
SEMANTIC_FUNCTION(BTST, 2)
SEMANTIC_FUNCTION(TST, 2)
SEMANTIC_FUNCTION(XBFU, 3)
SEMANTIC_FUNCTION(AEX, 2)
SEMANTIC_FUNCTION(LR, 2)
SEMANTIC_FUNCTION(SR, 2)
SEMANTIC_FUNCTION(MPY, 3)
SEMANTIC_FUNCTION(ABS, 2)
SEMANTIC_FUNCTION(SWAP, 2)
SEMANTIC_FUNCTION(SWAPE, 2)
SEMANTIC_FUNCTION(NOT, 2)
SEMANTIC_FUNCTION(BI, 1)
SEMANTIC_FUNCTION(BIH, 1)
SEMANTIC_FUNCTION(B, 1)
SEMANTIC_FUNCTION(B_S, 1)
SEMANTIC_FUNCTION(BBIT0, 3)
SEMANTIC_FUNCTION(BBIT1, 3)
SEMANTIC_FUNCTION(BL, 1)
SEMANTIC_FUNCTION(J, 1)
SEMANTIC_FUNCTION(JL, 1)
SEMANTIC_FUNCTION(BREQ, 3)
SEMANTIC_FUNCTION(SETEQ, 3)
SEMANTIC_FUNCTION(BRNE, 3)
SEMANTIC_FUNCTION(SETNE, 3)
SEMANTIC_FUNCTION(BRLT, 3)
SEMANTIC_FUNCTION(SETLT, 3)
SEMANTIC_FUNCTION(BRGE, 3)
SEMANTIC_FUNCTION(SETGE, 3)
SEMANTIC_FUNCTION(SETLE, 3)
SEMANTIC_FUNCTION(SETGT, 3)
SEMANTIC_FUNCTION(BRLO, 3)
SEMANTIC_FUNCTION(SETLO, 3)
SEMANTIC_FUNCTION(BRHS, 3)
SEMANTIC_FUNCTION(SETHS, 3)
SEMANTIC_FUNCTION(LD, 3)
SEMANTIC_FUNCTION(LDD, 3)
SEMANTIC_FUNCTION(ST, 3)
SEMANTIC_FUNCTION(STD, 3)
SEMANTIC_FUNCTION(POP, 1)
SEMANTIC_FUNCTION(PUSH, 1)
SEMANTIC_FUNCTION(LP, 1)


MAPPING(neg, NEG, 2, 0, 1)
MAPPING(neg_s, NEG, 2, 0, 1)
MAPPING(add, ADD, 3, 0, 1, 2)
MAPPING(add_s, ADD, 3, 0, 1, 2)
MAPPING(add1, ADD1, 3, 0, 1, 2)
MAPPING(add1_s, ADD1, 3, 0, 1, 2)
MAPPING(add2, ADD2, 3, 0, 1, 2)
MAPPING(add2_s, ADD2, 3, 0, 1, 2)
MAPPING(add3, ADD3, 3, 0, 1, 2)
MAPPING(add3_s, ADD3, 3, 0, 1, 2)
MAPPING(adc, ADC, 3, 0, 1, 2)
MAPPING(sbc, SBC, 3, 0, 1, 2)
MAPPING(rsub, SUB, 3, 0, 2, 1)
MAPPING(sub, SUB, 3, 0, 1, 2)
MAPPING(sub_s, SUB, 3, 0, 1, 2)
MAPPING(sub1, SUB1, 3, 0, 1, 2)
MAPPING(sub2, SUB2, 3, 0, 1, 2)
MAPPING(sub3, SUB3, 3, 0, 1, 2)
MAPPING(max, MAX, 3, 1, 2, 0)
MAPPING(min, MIN, 3, 1, 2, 0)
MAPPING(cmp, CMP, 2, 0, 1)
MAPPING(cmp_s, CMP, 2, 0, 1)
MAPPING(rcmp, CMP, 2, 1, 0)
MAPPING(and, AND, 3, 0, 1, 2)
MAPPING(and_s, AND, 3, 0, 1, 2)
MAPPING(or, OR, 3, 0, 1, 2)
MAPPING(or_s, OR, 3, 0, 1, 2)
MAPPING(xor, XOR, 3, 0, 1, 2)
MAPPING(xor_s, XOR, 3, 0, 1, 2)
MAPPING(mov, MOV, 2, 0, 1)
MAPPING(mov_s, MOV, 2, 0, 1)
MAPPING(asl, ASL, 3, 0, 1, 2)
MAPPING(asl_s, ASL, 3, 0, 1, 2)
MAPPING(asr, ASR, 3, 0, 1, 2)
MAPPING(asr_s, ASR, 3, 0, 1, 2)
MAPPING(asr8, ASR8, 2, 0, 1)
MAPPING(asr16, ASR16, 2, 0, 1)
MAPPING(lsl16, LSL16, 2, 0, 1)
MAPPING(lsl8, LSL8, 2, 0, 1)
MAPPING(lsr, LSR, 3, 0, 1, 2)
MAPPING(lsr_s, LSR, 3, 0, 1, 2)
MAPPING(lsr16, LSR16, 2, 0, 1)
MAPPING(lsr8, LSR8, 2, 0, 1)
MAPPING(bic, BIC, 3, 0, 1, 2)
MAPPING(bic_s, BIC, 3, 0, 1, 2)
MAPPING(bclr, BCLR, 3, 2, 0, 1)
MAPPING(bclr_s, BCLR, 3, 2, 0, 1)
MAPPING(bmsk, BMSK, 3, 2, 0, 1)
MAPPING(bmsk_s, BMSK, 3, 2, 0, 1)
MAPPING(bmskn, BMSKN, 3, 2, 0, 1)
MAPPING(bset, BSET, 3, 2, 0, 1)
MAPPING(bset_s, BSET, 3, 2, 0, 1)
MAPPING(bxor, BXOR, 3, 2, 0, 1)
MAPPING(rol, ROL, 3, 0, 1, 2)
MAPPING(rol8, ROL, 3, 0, 1, 2)
MAPPING(ror, ROR, 3, 2, 1, 0)
MAPPING(ror8, ROR, 3, 0, 1, 2)
MAPPING(rlc, RLC, 2, 0, 1)
MAPPING(rrc, RRC, 2, 0, 1)
MAPPING(sexb, SEXB, 2, 0, 1)
MAPPING(sexb_s, SEXB, 2, 0, 1)
MAPPING(sexh, SEXH, 2, 0, 1)
MAPPING(sexh_s, SEXH, 2, 0, 1)
MAPPING(extb, EXTB, 2, 0, 1)
MAPPING(extb_s, EXTB, 2, 0, 1)
MAPPING(exth, EXTH, 2, 0, 1)
MAPPING(exth_s, EXTH, 2, 0, 1)
MAPPING(btst, BTST, 2, 1, 0)
MAPPING(btst_s, BTST, 2, 1, 0)
MAPPING(tst, TST, 2, 0, 1)
MAPPING(tst_s, TST, 2, 0, 1)
MAPPING(xbfu, XBFU, 3, 2, 1, 0)
MAPPING(aex, AEX, 2, 1, 0)
MAPPING(lr, LR, 2, 0, 1)
MAPPING(sr, SR, 2, 1, 0)
MAPPING(mpy, MPY, 3, 0, 1, 2)
MAPPING(mpy_s, MPY, 3, 0, 1, 2)
MAPPING(abs, ABS, 2, 1, 0)
MAPPING(abs_s, ABS, 2, 1, 0)
MAPPING(swap, SWAP, 2, 1, 0)
MAPPING(swape, SWAPE, 2, 1, 0)
MAPPING(not, NOT, 2, 0, 1)
MAPPING(not_s, NOT, 2, 0, 1)
MAPPING(bi, BI, 1, 0)
MAPPING(bih, BIH, 1, 0)
MAPPING(b, B, 1, 0)
MAPPING(beq_s, B_S, 1, 0)
MAPPING(bne_s, B_S, 1, 0)
MAPPING(bgt_s, B_S, 1, 0)
MAPPING(bge_s, B_S, 1, 0)
MAPPING(blt_s, B_S, 1, 0)
MAPPING(ble_s, B_S, 1, 0)
MAPPING(bhi_s, B_S, 1, 0)
MAPPING(bhs_s, B_S, 1, 0)
MAPPING(blo_s, B_S, 1, 0)
MAPPING(bls_s, B_S, 1, 0)
MAPPING(b_s, B_S, 1, 0)
MAPPING(bbit0, BBIT0, 3, 1, 0, 2)
MAPPING(bbit1, BBIT1, 3, 1, 0, 2)
MAPPING(bl, BL, 1, 0)
MAPPING(bl_s, BL, 1, 0)
MAPPING(j, J, 1, 0)
MAPPING(j_s, J, 1, 0)
MAPPING(jeq_s, J, 1, 0)
MAPPING(jne_s, J, 1, 0)
MAPPING(jl, JL, 1, 0)
MAPPING(jl_s, JL, 1, 0)
MAPPING(breq, BREQ, 3, 0, 1, 2)
MAPPING(breq_s, BREQ, 3, 0, 1, 2)
MAPPING(seteq, SETEQ, 3, 1, 2, 0)
MAPPING(brne, BRNE, 3, 0, 1, 2)
MAPPING(brne_s, BRNE, 3, 0, 1, 2)
MAPPING(setne, SETNE, 3, 1, 2, 0)
MAPPING(brlt, BRLT, 3, 0, 1, 2)
MAPPING(setlt, SETLT, 3, 1, 2, 0)
MAPPING(brge, BRGE, 3, 0, 1, 2)
MAPPING(setge, SETGE, 3, 1, 2, 0)
MAPPING(setle, SETLE, 3, 1, 2, 0)
MAPPING(setgt, SETGT, 3, 1, 2, 0)
MAPPING(brlo, BRLO, 3, 0, 1, 2)
MAPPING(setlo, SETLO, 3, 1, 2, 0)
MAPPING(brhs, BRHS, 3, 0, 1, 2)
MAPPING(seths, SETHS, 3, 1, 2, 0)
MAPPING(ld, LD, 3, 1, 2, 0)
MAPPING(ld_s, LD, 3, 1, 2, 0)
MAPPING(ldb_s, LD, 3, 1, 2, 0)
MAPPING(ldh_s, LD, 3, 1, 2, 0)
MAPPING(ldw_s, LD, 3, 1, 2, 0)
MAPPING(ldi, LD, 3, 0, 1, 2)
MAPPING(ldi_s, LD, 3, 0, 1, 2)
MAPPING(ldd, LDD, 3, 1, 2, 0)
MAPPING(st, ST, 3, 1, 2, 0)
MAPPING(st_s, ST, 3, 1, 2, 0)
MAPPING(stb_s, ST, 3, 1, 2, 0)
MAPPING(sth_s, ST, 3, 1, 2, 0)
MAPPING(stw_s, ST, 3, 1, 2, 0)
MAPPING(std, STD, 3, 1, 2, 0)
MAPPING(pop_s, POP, 1, 0)
MAPPING(push_s, PUSH, 1, 0)
MAPPING(lp, LP, 1, 0)

