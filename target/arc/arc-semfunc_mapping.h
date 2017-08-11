
SEMANTIC_FUNCTION(ADD, 3, a, b, c)
SEMANTIC_FUNCTION(ADD1, 3, a, b, c)
SEMANTIC_FUNCTION(ADD2, 3, a, b, c)
SEMANTIC_FUNCTION(ADD3, 3, a, b, c)
SEMANTIC_FUNCTION(MUL, 3, a, b, c)
SEMANTIC_FUNCTION(DIV, 3, a, b, c)
SEMANTIC_FUNCTION(ADC, 3, a, b, c)
SEMANTIC_FUNCTION(SUB, 3, a, b, c)
SEMANTIC_FUNCTION(SUB1, 3, a, b, c)
SEMANTIC_FUNCTION(SUB2, 3, a, b, c)
SEMANTIC_FUNCTION(SUB3, 3, a, b, c)
SEMANTIC_FUNCTION(MAX, 3, b, c, a)
SEMANTIC_FUNCTION(MIN, 3, b, c, a)
SEMANTIC_FUNCTION(AND, 3, a, b, c)
SEMANTIC_FUNCTION(OR, 3, a, b, c)
SEMANTIC_FUNCTION(XOR, 3, a, b, c)
SEMANTIC_FUNCTION(MOV, 2, a, b)
SEMANTIC_FUNCTION(ASL, 3, a, b, c)
SEMANTIC_FUNCTION(ASR, 3, a, b, c)
SEMANTIC_FUNCTION(ASR8, 2, a, b)
SEMANTIC_FUNCTION(ASR16, 2, a, b)
SEMANTIC_FUNCTION(LSL16, 2, a, b)
SEMANTIC_FUNCTION(LSL8, 2, a, b)
SEMANTIC_FUNCTION(LSR, 3, a, b, c)
SEMANTIC_FUNCTION(LSR16, 2, a, b)
SEMANTIC_FUNCTION(LSR8, 2, a, b)
SEMANTIC_FUNCTION(BIC, 3, a, b, c)
SEMANTIC_FUNCTION(BCLR, 3, c, a, b)
SEMANTIC_FUNCTION(TST, 2, b, c)
SEMANTIC_FUNCTION(BMSK, 3, c, a, b)
SEMANTIC_FUNCTION(BMSKN, 3, c, a, b)
SEMANTIC_FUNCTION(BSET, 3, c, a, b)
SEMANTIC_FUNCTION(BTST, 2, c, b)
SEMANTIC_FUNCTION(MPY, 3, a, b, c)
SEMANTIC_FUNCTION(ABS, 2, src, dest)
SEMANTIC_FUNCTION(B, 1, rd)
SEMANTIC_FUNCTION(B_S, 1, rd)
SEMANTIC_FUNCTION(BBIT0, 3, c, b, rd)
SEMANTIC_FUNCTION(BBIT1, 3, c, b, rd)
SEMANTIC_FUNCTION(BL, 1, rd)
SEMANTIC_FUNCTION(J, 1, src)
SEMANTIC_FUNCTION(JL, 1, src)
SEMANTIC_FUNCTION(CMP, 2, src1, src2)
SEMANTIC_FUNCTION(BREQ, 3, b, c, offset)
SEMANTIC_FUNCTION(SETEQ, 3, b, c, a)
SEMANTIC_FUNCTION(BRNE, 3, b, c, offset)
SEMANTIC_FUNCTION(SETNE, 3, b, c, a)
SEMANTIC_FUNCTION(BRLT, 3, b, c, offset)
SEMANTIC_FUNCTION(SETLT, 3, b, c, a)
SEMANTIC_FUNCTION(BRGE, 3, b, c, offset)
SEMANTIC_FUNCTION(SETGE, 3, b, c, a)
SEMANTIC_FUNCTION(SETLE, 3, b, c, a)
SEMANTIC_FUNCTION(SETGT, 3, b, c, a)
SEMANTIC_FUNCTION(BRLO, 3, b, c, offset)
SEMANTIC_FUNCTION(SETLO, 3, b, c, a)
SEMANTIC_FUNCTION(BRHS, 3, b, c, offset)
SEMANTIC_FUNCTION(SETHS, 3, b, c, a)
SEMANTIC_FUNCTION(LD, 3, src1, src2, dest)
SEMANTIC_FUNCTION(ST, 3, src1, src2, dest)


MAPPING(add, ADD)
MAPPING(add_s, ADD)
MAPPING(add1, ADD1)
MAPPING(add1_s, ADD1)
MAPPING(add2, ADD2)
MAPPING(add2_s, ADD2)
MAPPING(add3, ADD3)
MAPPING(add3_s, ADD3)
MAPPING(div, DIV)
MAPPING(adc, ADC)
MAPPING(sub, SUB)
MAPPING(sub_s, SUB)
MAPPING(sub1, SUB1)
MAPPING(sub2, SUB2)
MAPPING(sub3, SUB3)
MAPPING(max, MAX)
MAPPING(min, MIN)
MAPPING(and, AND)
MAPPING(and_s, AND)
MAPPING(or, OR)
MAPPING(or_s, OR)
MAPPING(xor, XOR)
MAPPING(xor_s, XOR)
MAPPING(mov, MOV)
MAPPING(mov_s, MOV)
MAPPING(asl, ASL)
MAPPING(asl_s, ASL)
MAPPING(asr, ASR)
MAPPING(asr_s, ASR)
MAPPING(asr8, ASR8)
MAPPING(asr16, ASR16)
MAPPING(lsl16, LSL16)
MAPPING(lsl8, LSL8)
MAPPING(lsr, LSR)
MAPPING(lsr_s, LSR)
MAPPING(lsr16, LSR16)
MAPPING(lsr8, LSR8)
MAPPING(bic, BIC)
MAPPING(bic_s, BIC)
MAPPING(bclr, BCLR)
MAPPING(bclr_s, BCLR)
MAPPING(tst, TST)
MAPPING(tst_s, TST)
MAPPING(bmsk, BMSK)
MAPPING(bmsk_s, BMSK)
MAPPING(bmskn, BMSKN)
MAPPING(bset, BSET)
MAPPING(bset_s, BSET)
MAPPING(btst, BTST)
MAPPING(btst_s, BTST)
MAPPING(mpy, MPY)
MAPPING(mpy_s, MPY)
MAPPING(abs, ABS)
MAPPING(abs_s, ABS)
MAPPING(b, B)
MAPPING(b_s, B_S)
MAPPING(bbit0, BBIT0)
MAPPING(bbit1, BBIT1)
MAPPING(bl, BL)
MAPPING(bl_s, BL)
MAPPING(j, J)
MAPPING(j_s, J)
MAPPING(jl, JL)
MAPPING(jl_s, JL)
MAPPING(cmp, CMP)
MAPPING(cmp_s, CMP)
MAPPING(breq, BREQ)
MAPPING(breq_s, BREQ)
MAPPING(seteq, SETEQ)
MAPPING(brne, BRNE)
MAPPING(brne_s, BRNE)
MAPPING(setne, SETNE)
MAPPING(brlt, BRLT)
MAPPING(setlt, SETLT)
MAPPING(brge, BRGE)
MAPPING(setge, SETGE)
MAPPING(setle, SETLE)
MAPPING(setgt, SETGT)
MAPPING(brlo, BRLO)
MAPPING(setlo, SETLO)
MAPPING(brhs, BRHS)
MAPPING(seths, SETHS)
MAPPING(ld, LD)
MAPPING(ld_s, LD)
MAPPING(ldb_s, LD)
MAPPING(ldh_s, LD)
MAPPING(ldw_s, LD)
MAPPING(ldd, LD)
MAPPING(ldi, LD)
MAPPING(ldi_s, LD)
MAPPING(ldm, LD)
MAPPING(st, ST)
MAPPING(st_s, ST)
MAPPING(stb_s, ST)
MAPPING(sth_s, ST)
MAPPING(stw_s, ST)
MAPPING(std, ST)
MAPPING(stm, ST)

