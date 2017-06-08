#define NPS_CMEM_HIGH_VALUE 12

typedef enum
{
  /* Addresses in memory.  */

  /* Buffer descriptor.  */
  ARC_NPS400_ADDRTYPE_BD,

  /* Job identifier.  */
  ARC_NPS400_ADDRTYPE_JID,

  /* Linked Buffer Descriptor.  */
  ARC_NPS400_ADDRTYPE_LBD,

  /* Multicast Buffer Descriptor.  */
  ARC_NPS400_ADDRTYPE_MBD,

  /* Summarized Address.  */
  ARC_NPS400_ADDRTYPE_SD,

  /* SMEM Security Context Local Memory.  */
  ARC_NPS400_ADDRTYPE_SM,

  /* Extended Address.  */
  ARC_NPS400_ADDRTYPE_XA,

  /* Extended Summarized Address.  */
  ARC_NPS400_ADDRTYPE_XD,

  /* CMEM offset addresses.  */

  /* On-demand Counter Descriptor.  */
  ARC_NPS400_ADDRTYPE_CD,
  /* CMEM Buffer Descriptor.  */
  ARC_NPS400_ADDRTYPE_CBD,

  /* CMEM Job Identifier.  */
  ARC_NPS400_ADDRTYPE_CJID,

  /* CMEM Linked Buffer Descriptor.  */
  ARC_NPS400_ADDRTYPE_CLBD,

  /* CMEM Offset.  */
  ARC_NPS400_ADDRTYPE_CM,

  /* CMEM Summarized Address.  */
  ARC_NPS400_ADDRTYPE_CSD,

  /* CMEM Extended Address.  */
  ARC_NPS400_ADDRTYPE_CXA,

  /* CMEM Extended Summarized Address.  */
  ARC_NPS400_ADDRTYPE_CXD

} arc_nps_address_type;

/* Insert RA register into a 32-bit opcode, with checks.  */
static unsigned long long
insert_ra_chk (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value == 60)
    *errmsg = "LP_COUNT register cannot be used as destination register";

  return insn | (value & 0x3F);
}
/* Insert RB register into a 32-bit opcode.  */
static unsigned long long
insert_rb (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x07) << 24) | (((value >> 3) & 0x07) << 12);
}

/* Insert RB register with checks.  */
static unsigned long long
insert_rb_chk (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value == 60)
    *errmsg = "LP_COUNT register cannot be used as destination register";

  return insn | ((value & 0x07) << 24) | (((value >> 3) & 0x07) << 12);
}

static long long int
extract_rb (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (((insn >> 12) & 0x07) << 3) | ((insn >> 24) & 0x07);

  if (value == 0x3e && invalid)
    *invalid = TRUE; /* A limm operand, it should be extracted in a
			different way.  */

  return value;
}

static unsigned long long
insert_rad (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value & 0x01)
    *errmsg = "cannot use odd number destination register";
  if (value == 60)
    *errmsg = "LP_COUNT register cannot be used as destination register";

  return insn | (value & 0x3F);
}

static unsigned long long
insert_rcd (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value & 0x01)
    *errmsg = "cannot use odd number source register";

  return insn | ((value & 0x3F) << 6);
}

/* Dummy insert ZERO operand function.  */

static unsigned long long
insert_za (unsigned long long insn,
	   long long int value,
	   const char **errmsg)
{
  if (value)
    *errmsg = "operand is not zero";
  return insn;
}

/* Insert Y-bit in bbit/br instructions.  This function is called only
   when solving fixups.  */

static unsigned long long
insert_Ybit (unsigned long long insn,
	     long long int value,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value > 0)
    insn |= 0x08;

  return insn;
}

/* Insert Y-bit in bbit/br instructions.  This function is called only
   when solving fixups.  */

static unsigned long long
insert_NYbit (unsigned long long insn,
	      long long int value,
	      const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value < 0)
    insn |= 0x08;

  return insn;
}

/* Insert H register into a 16-bit opcode.  */

static unsigned long long
insert_rhv1 (unsigned long long insn,
	     long long int value,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn |= ((value & 0x07) << 5) | ((value >> 3) & 0x07);
}

static long long int
extract_rhv1 (unsigned long long insn ATTRIBUTE_UNUSED,
	      bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = ((insn & 0x7) << 3) | ((insn >> 5) & 0x7);

  return value;
}

/* Insert H register into a 16-bit opcode.  */

static unsigned long long
insert_rhv2 (unsigned long long insn,
	     long long int value,
	     const char **errmsg)
{
  if (value == 0x1E)
    *errmsg =
      "Register R30 is a limm indicator";
  return insn |= ((value & 0x07) << 5) | ((value >> 3) & 0x03);
}

static long long int
extract_rhv2 (unsigned long long insn ATTRIBUTE_UNUSED,
	      bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = ((insn >> 5) & 0x07) | ((insn & 0x03) << 3);

  return value;
}

static unsigned long long
insert_r0 (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 0)
    *errmsg = "Register must be R0";
  return insn;
}

static long long int
extract_r0 (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 0;
}


static unsigned long long
insert_r1 (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 1)
    *errmsg = "Register must be R1";
  return insn;
}

static long long int
extract_r1 (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 1;
}

static unsigned long long
insert_r2 (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 2)
    *errmsg = "Register must be R2";
  return insn;
}

static long long int
extract_r2 (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 2;
}

static unsigned long long
insert_r3 (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 3)
    *errmsg = "Register must be R3";
  return insn;
}

static long long int
extract_r3 (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 3;
}

static unsigned long long
insert_sp (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 28)
    *errmsg = "Register must be SP";
  return insn;
}

static long long int
extract_sp (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 28;
}

static unsigned long long
insert_gp (unsigned long long insn,
	   long long int value,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 26)
    *errmsg = "Register must be GP";
  return insn;
}

static long long int
extract_gp (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 26;
}

static unsigned long long
insert_pcl (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 63)
    *errmsg = "Register must be PCL";
  return insn;
}

static long long int
extract_pcl (unsigned long long insn ATTRIBUTE_UNUSED,
	     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 63;
}

static unsigned long long
insert_blink (unsigned long long insn,
	      long long int value,
	      const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 31)
    *errmsg = "Register must be BLINK";
  return insn;
}

static long long int
extract_blink (unsigned long long insn ATTRIBUTE_UNUSED,
	       bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 31;
}

static unsigned long long
insert_ilink1 (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 29)
    *errmsg = "Register must be ILINK1";
  return insn;
}

static long long int
extract_ilink1 (unsigned long long insn ATTRIBUTE_UNUSED,
		bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 29;
}

static unsigned long long
insert_ilink2 (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 30)
    *errmsg = "Register must be ILINK2";
  return insn;
}

static long long int
extract_ilink2 (unsigned long long insn ATTRIBUTE_UNUSED,
		bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return 30;
}

static unsigned long long
insert_ras (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  switch (value)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      insn |= value;
      break;
    case 12:
    case 13:
    case 14:
    case 15:
      insn |= (value - 8);
      break;
    default:
      *errmsg = "Register must be either r0-r3 or r12-r15";
      break;
    }
  return insn;
}

static long long int
extract_ras (unsigned long long insn ATTRIBUTE_UNUSED,
	     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = insn & 0x07;
  if (value > 3)
    return (value + 8);
  else
    return value;
}

static unsigned long long
insert_rbs (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  switch (value)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      insn |= value << 8;
      break;
    case 12:
    case 13:
    case 14:
    case 15:
      insn |= ((value - 8)) << 8;
      break;
    default:
      *errmsg = "Register must be either r0-r3 or r12-r15";
      break;
    }
  return insn;
}

static long long int
extract_rbs (unsigned long long insn ATTRIBUTE_UNUSED,
	     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 8) & 0x07;
  if (value > 3)
    return (value + 8);
  else
    return value;
}

static unsigned long long
insert_rcs (unsigned long long insn,
	    long long int value,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  switch (value)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      insn |= value << 5;
      break;
    case 12:
    case 13:
    case 14:
    case 15:
      insn |= ((value - 8)) << 5;
      break;
    default:
      *errmsg = "Register must be either r0-r3 or r12-r15";
      break;
    }
  return insn;
}

static long long int
extract_rcs (unsigned long long insn ATTRIBUTE_UNUSED,
	     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 5) & 0x07;
  if (value > 3)
    return (value + 8);
  else
    return value;
}

static unsigned long long
insert_simm3s (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  int tmp = 0;
  switch (value)
    {
    case -1:
      tmp = 0x07;
      break;
    case 0:
      tmp = 0x00;
      break;
    case 1:
      tmp = 0x01;
      break;
    case 2:
      tmp = 0x02;
      break;
    case 3:
      tmp = 0x03;
      break;
    case 4:
      tmp = 0x04;
      break;
    case 5:
      tmp = 0x05;
      break;
    case 6:
      tmp = 0x06;
      break;
    default:
      *errmsg = "Accepted values are from -1 to 6";
      break;
    }

  insn |= tmp << 8;
  return insn;
}

static long long int
extract_simm3s (unsigned long long insn ATTRIBUTE_UNUSED,
		bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 8) & 0x07;
  if (value == 7)
    return -1;
  else
    return value;
}

static unsigned long long
insert_rrange (unsigned long long insn,
	       long long int value,
	       const char **errmsg ATTRIBUTE_UNUSED)
{
  int reg1 = (value >> 16) & 0xFFFF;
  int reg2 = value & 0xFFFF;
  if (reg1 != 13)
    {
      *errmsg = "First register of the range should be r13";
      return insn;
    }
  if (reg2 < 13 || reg2 > 26)
    {
      *errmsg = "Last register of the range doesn't fit";
      return insn;
    }
  insn |= ((reg2 - 12) & 0x0F) << 1;
  return insn;
}

static long long int
extract_rrange (unsigned long long insn  ATTRIBUTE_UNUSED,
		bfd_boolean * invalid  ATTRIBUTE_UNUSED)
{
  return (insn >> 1) & 0x0F;
}

static unsigned long long
insert_r13el (unsigned long long insn,
	     long long int value,
	     const char **errmsg)
{
  if (value != 13)
    {
      *errmsg = "Invalid register number, should be fp";
      return insn;
    }

  insn |= 0x02;
  return insn;
}

static unsigned long long
insert_fpel (unsigned long long insn,
	     long long int value,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 27)
    {
      *errmsg = "Invalid register number, should be fp";
      return insn;
    }

  insn |= 0x0100;
  return insn;
}

static long long int
extract_fpel (unsigned long long insn  ATTRIBUTE_UNUSED,
	      bfd_boolean * invalid  ATTRIBUTE_UNUSED)
{
  return (insn & 0x0100) ? 27 : -1;
}

static unsigned long long
insert_blinkel (unsigned long long insn,
		long long int value,
		const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 31)
    {
      *errmsg = "Invalid register number, should be blink";
      return insn;
    }

  insn |= 0x0200;
  return insn;
}

static long long int
extract_blinkel (unsigned long long insn  ATTRIBUTE_UNUSED,
		 bfd_boolean * invalid  ATTRIBUTE_UNUSED)
{
  return (insn & 0x0200) ? 31 : -1;
}

static unsigned long long
insert_pclel (unsigned long long insn,
	      long long int value,
	      const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value != 63)
    {
      *errmsg = "Invalid register number, should be pcl";
      return insn;
    }

  insn |= 0x0400;
  return insn;
}

static long long int
extract_pclel (unsigned long long insn  ATTRIBUTE_UNUSED,
	       bfd_boolean * invalid  ATTRIBUTE_UNUSED)
{
  return (insn & 0x0400) ? 63 : -1;
}

#define INSERT_W6
/* mask = 00000000000000000000111111000000
   insn = 00011bbb000000000BBBwwwwwwDaaZZ1.  */
static unsigned long long
insert_w6 (unsigned long long insn ATTRIBUTE_UNUSED,
	   long long int value ATTRIBUTE_UNUSED,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  insn |= ((value >> 0) & 0x003f) << 6;

  return insn;
}

#define EXTRACT_W6
/* mask = 00000000000000000000111111000000.  */
static long long int
extract_w6 (unsigned long long insn ATTRIBUTE_UNUSED,
	    bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  unsigned value = 0;

  value |= ((insn >> 6) & 0x003f) << 0;

  return value;
}

#define INSERT_G_S
/* mask = 0000011100022000
   insn = 01000ggghhhGG0HH.  */
static unsigned long long
insert_g_s (unsigned long long insn ATTRIBUTE_UNUSED,
	    long long int value ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  insn |= ((value >> 0) & 0x0007) << 8;
  insn |= ((value >> 3) & 0x0003) << 3;

  return insn;
}

#define EXTRACT_G_S
/* mask = 0000011100022000.  */
static long long int
extract_g_s (unsigned long long insn ATTRIBUTE_UNUSED,
	     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = 0;

  value |= ((insn >> 8) & 0x0007) << 0;
  value |= ((insn >> 3) & 0x0003) << 3;

  /* Extend the sign.  */
  int signbit = 1 << (6 - 1);
  value = (value ^ signbit) - signbit;

  return value;
}

/* ARC NPS400 Support: See comment near head of file.  */
#define MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(NAME,OFFSET)          \
static unsigned long long					 \
insert_nps_3bit_reg_at_##OFFSET##_##NAME		         \
                    (unsigned long long insn ATTRIBUTE_UNUSED,   \
                     long long int value ATTRIBUTE_UNUSED,	 \
                     const char **errmsg ATTRIBUTE_UNUSED)	 \
{								 \
  switch (value)						 \
    {								 \
    case 0:                                                      \
    case 1:                                                      \
    case 2:                                                      \
    case 3:                                                      \
      insn |= value << (OFFSET);                                 \
      break;                                                     \
    case 12:                                                     \
    case 13:                                                     \
    case 14:                                                     \
    case 15:                                                     \
      insn |= (value - 8) << (OFFSET);                           \
      break;                                                     \
    default:                                                     \
      *errmsg = "Register must be either r0-r3 or r12-r15";  \
      break;                                                     \
    }                                                            \
  return insn;                                                   \
}                                                                \
                                                                 \
static long long int						 \
extract_nps_3bit_reg_at_##OFFSET##_##NAME                        \
                    (unsigned long long insn ATTRIBUTE_UNUSED,   \
                     bfd_boolean * invalid ATTRIBUTE_UNUSED)     \
{                                                                \
  int value = (insn >> (OFFSET)) & 0x07;			 \
  if (value > 3)                                                 \
    value += 8;                                                  \
  return value;                                                  \
}                                                                \

MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(dst,8)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(dst,24)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(dst,40)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(dst,56)

MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(src2,5)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(src2,21)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(src2,37)
MAKE_3BIT_REG_INSERT_EXTRACT_FUNCS(src2,53)

static unsigned long long
insert_nps_bitop_size_2b (unsigned long long insn ATTRIBUTE_UNUSED,
                          long long int value ATTRIBUTE_UNUSED,
                          const char **errmsg ATTRIBUTE_UNUSED)
{
  switch (value)
    {
    case 1:
      value = 0;
      break;
    case 2:
      value = 1;
      break;
    case 4:
      value = 2;
      break;
    case 8:
      value = 3;
      break;
    default:
      value = 0;
      *errmsg = "Invalid size, should be 1, 2, 4, or 8";
      break;
    }

  insn |= value << 10;
  return insn;
}

static long long int
extract_nps_bitop_size_2b (unsigned long long insn ATTRIBUTE_UNUSED,
                           bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return  1 << ((insn >> 10) & 0x3);
}

static unsigned long long
insert_nps_bitop_uimm8 (unsigned long long insn ATTRIBUTE_UNUSED,
                        long long int value ATTRIBUTE_UNUSED,
                        const char **errmsg ATTRIBUTE_UNUSED)
{
  insn |= ((value >> 5) & 7) << 12;
  insn |= (value & 0x1f);
  return insn;
}

static long long int
extract_nps_bitop_uimm8 (unsigned long long insn ATTRIBUTE_UNUSED,
                         bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return (((insn >> 12) & 0x7) << 5) | (insn & 0x1f);
}

static unsigned long long
insert_nps_rflt_uimm6 (unsigned long long insn ATTRIBUTE_UNUSED,
                       long long int value ATTRIBUTE_UNUSED,
                       const char **errmsg ATTRIBUTE_UNUSED)
{
  switch (value)
    {
    case 1:
    case 2:
    case 4:
      break;

    default:
      *errmsg = "invalid immediate, must be 1, 2, or 4";
      value = 0;
    }

  insn |= (value << 6);
  return insn;
}

static long long int
extract_nps_rflt_uimm6 (unsigned long long insn ATTRIBUTE_UNUSED,
                         bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return (insn >> 6) & 0x3f;
}

static unsigned long long
insert_nps_dst_pos_and_size (unsigned long long insn ATTRIBUTE_UNUSED,
                             long long int value ATTRIBUTE_UNUSED,
                             const char **errmsg ATTRIBUTE_UNUSED)
{
  insn |= ((value & 0x1f) | (((32 - value - 1) & 0x1f) << 10));
  return insn;
}

static long long int
extract_nps_dst_pos_and_size (unsigned long long insn ATTRIBUTE_UNUSED,
                              bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return (insn & 0x1f);
}

static unsigned long long
insert_nps_cmem_uimm16 (unsigned long long insn ATTRIBUTE_UNUSED,
                        long long int value ATTRIBUTE_UNUSED,
                        const char **errmsg ATTRIBUTE_UNUSED)
{
  int top = (value >> 16) & 0xffff;
  if (top != 0x0 && top != NPS_CMEM_HIGH_VALUE)
    *errmsg = "invalid value for CMEM ld/st immediate";
  insn |= (value & 0xffff);
  return insn;
}

static long long int
extract_nps_cmem_uimm16 (unsigned long long insn ATTRIBUTE_UNUSED,
                         bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return (NPS_CMEM_HIGH_VALUE << 16) | (insn & 0xffff);
}

#define MAKE_SRC_POS_INSERT_EXTRACT_FUNCS(NAME,SHIFT)         \
static unsigned long long                                               \
insert_nps_##NAME##_pos (unsigned long long insn ATTRIBUTE_UNUSED,      \
                        long long int value ATTRIBUTE_UNUSED,           \
                        const char **errmsg ATTRIBUTE_UNUSED) \
{                                                             \
 switch (value)                                               \
   {                                                          \
   case 0:                                                    \
   case 8:                                                    \
   case 16:                                                   \
   case 24:                                                   \
     value = value / 8;                                       \
     break;                                                   \
   default:                                                   \
     *errmsg = "Invalid position, should be 0, 8, 16, or 24";       \
     value = 0;                                               \
  }                                                           \
  insn |= (value << SHIFT);                                    \
  return insn;                                                \
}                                                             \
                                                              \
static long long int                                                    \
extract_nps_##NAME##_pos (unsigned long long insn ATTRIBUTE_UNUSED,     \
                          bfd_boolean * invalid ATTRIBUTE_UNUSED)     \
{                                                                     \
  return ((insn >> SHIFT) & 0x3) * 8;                                 \
}

MAKE_SRC_POS_INSERT_EXTRACT_FUNCS (src2, 12)
MAKE_SRC_POS_INSERT_EXTRACT_FUNCS (src1, 10)

#define MAKE_BIAS_INSERT_EXTRACT_FUNCS(NAME,LOWER,UPPER,BITS,BIAS,SHIFT)\
static unsigned long long                                                         \
insert_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,                      \
                   long long int value ATTRIBUTE_UNUSED,                          \
                   const char **errmsg ATTRIBUTE_UNUSED)                \
  {                                                                     \
    if (value < LOWER || value > UPPER)                                 \
      {                                                                 \
        *errmsg = "Invalid size, value must be "                      \
                    #LOWER " to " #UPPER ".";                          \
        return insn;                                                    \
      }                                                                 \
    value -= BIAS;                                                      \
    insn |= (value << SHIFT);                                           \
    return insn;                                                        \
  }                                                                     \
                                                                        \
static long long int                                                              \
extract_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,                     \
                    bfd_boolean * invalid ATTRIBUTE_UNUSED)             \
{                                                                       \
  return ((insn >> SHIFT) & ((1 << BITS) - 1)) + BIAS;                  \
}

MAKE_BIAS_INSERT_EXTRACT_FUNCS (addb_size,2,32,5,1,5)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (andb_size,1,32,5,1,5)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (fxorb_size,8,32,5,8,5)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (wxorb_size,16,32,5,16,5)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (bitop_size,1,32,5,1,10)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (qcmp_size,1,8,3,1,9)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (bitop1_size,1,32,5,1,20)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (bitop2_size,1,32,5,1,25)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (hash_width,1,32,5,1,6)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (hash_len,1,8,3,1,2)
MAKE_BIAS_INSERT_EXTRACT_FUNCS (index3,4,7,2,4,0)

static long long int
extract_nps_qcmp_m3 (unsigned long long insn ATTRIBUTE_UNUSED,
                     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int m3 = (insn >> 5) & 0xf;
  if (m3 == 0xf)
    *invalid = TRUE;
  return m3;
}

static long long int
extract_nps_qcmp_m2 (unsigned long long insn ATTRIBUTE_UNUSED,
                     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  bfd_boolean tmp_invalid = FALSE;
  int m2 = (insn >> 15) & 0x1;
  int m3 = extract_nps_qcmp_m3 (insn, &tmp_invalid);

  if (m2 == 0 && m3 == 0xf)
    *invalid = TRUE;
  return m2;
}

static long long int
extract_nps_qcmp_m1 (unsigned long long insn ATTRIBUTE_UNUSED,
                     bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  bfd_boolean tmp_invalid = FALSE;
  int m1 = (insn >> 14) & 0x1;
  int m2 = extract_nps_qcmp_m2 (insn, &tmp_invalid);
  int m3 = extract_nps_qcmp_m3 (insn, &tmp_invalid);

  if (m1 == 0 && m2 == 0 && m3 == 0xf)
    *invalid = TRUE;
  return m1;
}

static unsigned long long
insert_nps_calc_entry_size (unsigned long long insn ATTRIBUTE_UNUSED,
                            long long int value ATTRIBUTE_UNUSED,
                            const char **errmsg ATTRIBUTE_UNUSED)
{
  unsigned pwr;

  if (value < 1 || value > 256)
    {
      *errmsg = "value out of range 1 - 256";
      return 0;
    }

  for (pwr = 0; (value & 1) == 0; value >>= 1)
    ++pwr;

  if (value != 1)
    {
      *errmsg = "value must be power of 2";
      return 0;
    }

  return insn | (pwr << 8);
}

static long long int
extract_nps_calc_entry_size (unsigned long long insn ATTRIBUTE_UNUSED,
                             bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  unsigned entry_size = (insn >> 8) & 0xf;
  return 1 << entry_size;
}

static unsigned long long
insert_nps_bitop_mod4 (unsigned long long insn ATTRIBUTE_UNUSED,
                           long long int value ATTRIBUTE_UNUSED,
                           const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x2) << 30) | ((value & 0x1) << 47);
}

static long long int
extract_nps_bitop_mod4 (unsigned long long insn ATTRIBUTE_UNUSED,
                            bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 30) & 0x2) | ((insn >> 47) & 0x1);
}

static unsigned long long
insert_nps_bitop_dst_pos3_pos4 (unsigned long long insn ATTRIBUTE_UNUSED,
                                long long int value ATTRIBUTE_UNUSED,
                                const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (value << 42) | (value << 37);
}

static long long int
extract_nps_bitop_dst_pos3_pos4 (unsigned long long insn ATTRIBUTE_UNUSED,
                                 bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  if (((insn >> 42) & 0x1f) != ((insn >> 37) & 0x1f))
    *invalid = TRUE;
  return ((insn >> 37) & 0x1f);
}

static unsigned long long
insert_nps_bitop_ins_ext (unsigned long long insn ATTRIBUTE_UNUSED,
                          long long int value ATTRIBUTE_UNUSED,
                          const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value < 0 || value > 28)
    *errmsg = "Value must be in the range 0 to 28";
  return insn | (value << 20);
}

static long long int
extract_nps_bitop_ins_ext (unsigned long long insn ATTRIBUTE_UNUSED,
                           bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 20) & 0x1f;
  if (value > 28)
    *invalid = TRUE;
  return value;
}

#define MAKE_1BASED_INSERT_EXTRACT_FUNCS(NAME,SHIFT,UPPER,BITS)         \
static unsigned long long                                                         \
insert_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,                      \
                   long long int value ATTRIBUTE_UNUSED,                          \
                   const char **errmsg ATTRIBUTE_UNUSED)                \
{                                                                       \
  if (value < 1 || value > UPPER)                                       \
    *errmsg = "Value must be in the range 1 to " #UPPER;                \
  if (value == UPPER)                                                   \
    value = 0;                                                          \
  return insn | (value << SHIFT);                                       \
}                                                                       \
                                                                        \
static long long int                                                              \
extract_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,                     \
                    bfd_boolean * invalid ATTRIBUTE_UNUSED)             \
{                                                                       \
  int value = (insn >> SHIFT) & ((1 << BITS) - 1);                      \
  if (value == 0)                                                       \
    value = UPPER;                                                      \
  return value;                                                         \
}

MAKE_1BASED_INSERT_EXTRACT_FUNCS (field_size, 6, 8, 3)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (shift_factor, 9, 8, 3)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (bits_to_scramble, 12, 8, 3)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (bdlen_max_len, 5, 256, 8)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (bd_num_buff, 6, 8, 3)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (pmu_num_job, 6, 4, 2)
MAKE_1BASED_INSERT_EXTRACT_FUNCS (proto_size, 16, 64, 6)

static unsigned long long
insert_nps_min_hofs (unsigned long long insn ATTRIBUTE_UNUSED,
                     long long int value ATTRIBUTE_UNUSED,
                     const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value < 0 || value > 240)
    *errmsg = "Value must be in the range 0 to 240";
  if ((value % 16) != 0)
    *errmsg = "Value must be a multiple of 16";
  value = value / 16;
  return insn | (value << 6);
}

static long long int
extract_nps_min_hofs (unsigned long long insn ATTRIBUTE_UNUSED,
                      bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 6) & 0xF;
  return value * 16;
}

#define MAKE_INSERT_NPS_ADDRTYPE(NAME,VALUE)                           \
static unsigned long long                                              \
insert_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,           \
                   long long int value ATTRIBUTE_UNUSED,               \
                   const char **errmsg ATTRIBUTE_UNUSED)               \
{                                                                      \
  if (value != ARC_NPS400_ADDRTYPE_##VALUE)                            \
    *errmsg = "Invalid address type for operand";                   \
  return insn;                                                         \
}                                                                      \
                                                                       \
static long long int                                                   \
extract_nps_##NAME (unsigned long long insn ATTRIBUTE_UNUSED,          \
                    bfd_boolean * invalid ATTRIBUTE_UNUSED)            \
{                                                                      \
  return ARC_NPS400_ADDRTYPE_##VALUE;                                  \
}

MAKE_INSERT_NPS_ADDRTYPE (bd, BD)
MAKE_INSERT_NPS_ADDRTYPE (jid, JID)
MAKE_INSERT_NPS_ADDRTYPE (lbd, LBD)
MAKE_INSERT_NPS_ADDRTYPE (mbd, MBD)
MAKE_INSERT_NPS_ADDRTYPE (sd, SD)
MAKE_INSERT_NPS_ADDRTYPE (sm, SM)
MAKE_INSERT_NPS_ADDRTYPE (xa, XA)
MAKE_INSERT_NPS_ADDRTYPE (xd, XD)
MAKE_INSERT_NPS_ADDRTYPE (cd, CD)
MAKE_INSERT_NPS_ADDRTYPE (cbd, CBD)
MAKE_INSERT_NPS_ADDRTYPE (cjid, CJID)
MAKE_INSERT_NPS_ADDRTYPE (clbd, CLBD)
MAKE_INSERT_NPS_ADDRTYPE (cm, CM)
MAKE_INSERT_NPS_ADDRTYPE (csd, CSD)
MAKE_INSERT_NPS_ADDRTYPE (cxa, CXA)
MAKE_INSERT_NPS_ADDRTYPE (cxd, CXD)

static unsigned long long
insert_nps_rbdouble_64 (unsigned long long insn ATTRIBUTE_UNUSED,
                        long long int value ATTRIBUTE_UNUSED,
                        const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value < 0 || value > 31)
    *errmsg = "Value must be in the range 0 to 31";
  return insn | (value << 43) | (value << 48);
}


static long long int
extract_nps_rbdouble_64 (unsigned long long insn ATTRIBUTE_UNUSED,
                         bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value1 = (insn >> 43) & 0x1F;
  int value2 = (insn >> 48) & 0x1F;

  if (value1 != value2)
    *invalid = TRUE;

  return value1;
}

static long long int
extract_uimm12_20 (unsigned long long insn ATTRIBUTE_UNUSED,
		   bfd_boolean * invalid ATTRIBUTE_UNUSED)
{
  int value = 0;

  value |= ((insn >> 6) & 0x003f) << 0;
  value |= ((insn >> 0) & 0x003f) << 6;

  return value;
}

