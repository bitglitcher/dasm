


struct something
{
    byte 0x5, apple;
    byte 0x4, lime;
    byte 0x8, orange;
}

main:
    add r0, r1;
    and r0, r1;
    ashl r0, r1;
    ashr r0, r1;
    beq 0xff;
    bge something.orange;
    bgt 0xff;
    bgtu 0xff;
    ble 0xff;
    bleu r0;
    blt r4;
    bltu 0xff;
    bne 0xff;
    brk;
    cmp r0, r1;
    dec r0, 0xff;
    div r0, r1;
    gsr r0, sr0;
    inc r0, 0xf;
    jmp r0;
    jmpa 0xffffffff;


