


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


