#ifndef inset
#define inset
#endif //_HEADER_FILE_H_
//FULL ISA DESCRIPTION (D16i Arch)
//Defenitions of the intructions of the D16i Architecture
//RISC Instructions
#define iNOOP            0x00
#define iLI              0x01 //Load immediate
#define iLSINS           0x02 //LOAD STORE INSTRUCTIONS
#define iALUF            0x03
#define iINMI            0x04
#define iJMPR            0x05
#define iMOVF            0x06
#define iJMPD            0x07 //Jump direct
//ALU Instructions (OPs)
#define iADD             0x00
#define iSUB             0x01
#define iADDCO           0x02 //Carry out
#define iSUBCO           0x03 
#define iADDCI           0x04 //Carry In
#define iSUBCI           0x05
#define iADDCOCI         0x06 //Carry out Carry in
#define iSUBCOCI         0x07
#define iAND             0x08
#define iXOR             0x09
#define iOR              0x0a
#define iNOT             0x0b
#define iSHFTL           0x0c
#define iSHFTR           0x0d

//INMI Instruction
#define iSPpp            0x00 //Increment SP keept becase its faster this way
#define iSPss            0x01 //Decrement SP
//#define iBP_SET		 0x02 //BP <= SP Replaced by MOV BP SP
//#define iSTSMR           0x02
//#define iHALT            0x03 //This will only call an Exit() Function on kernel provably
#define iSYSC            0x04 //PC <= IRQ_VECTOR and IRQ <= enable
#define iCR_SWAP         0x06
#define iIRQ_EN		 0x07

//JMP miicroIns
#define iJMPAB           0x00
#define iJMPEQ           0x01
#define iJMPBA           0x02
#define iJMPNEG          0x03
#define iJMPOVR          0x04
#define iJMPZERO         0x05
#define iJMPNONE         0x06
//Special Purpose Registers
#define iSP              0x00
#define iBP              0x01
//#define iDMAP            0x02 //Everything is now address mapped
#define iIRQID		 0x02 //Interrupt ID including SYS Call $0

//#define iKRNLP           0x03 System Call ID


#define iTMRIP           0x04
#define iSYSCR           0x05
#define iLPR             0x06 //Return Register ADDR after IRQ
#define iSTMR            0x07
//MOV micro Instructions
#define iMOVGPRGPR       0x00
#define iMOVGPRSPR       0x01
#define iMOVSPRGPR       0x02
#define iMOVTMRGPR       0x03
#define iMOVGPRDMAR      0x04
//Main GPRS
#define iAX              0x00
#define iBX              0x01
#define iCX              0x02
#define iDX              0x03
#define iEX              0x04
#define iFX              0x05
#define iGX              0x06
#define iHX              0x07
//DMA registers
#define iMMA             0x00 //Mapped Memory Address
#define iMMC             0x01 //Mapped Memory Count

#define iGPR             0x00
#define iSPR             0x01

#define STACK_ADDR       0xff //Just because of the standarts, its 0xffff but this is used fot HI and Lo
/*
ERRR ERROR_REGISTER: Any illegal execution will create an exeption code on this register
*/

/*
Atomic Instructions
#define LL //Load Link
#define SC //Store Conditional
ALR register is nedded to implement that
#define ALR
Also there are not Branch slots, because there will be no multi threading implementation
*/
