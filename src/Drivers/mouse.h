#include "../common.h"
#include "../all_drivers.h"

//EXPERIMENTAL

typedef enum
{
   MOUSE_LEFT_KEY = 0x10,
   MOUSE_RIGHT_KEY = 0x11,
}MOUSE_DATA;

void mouse_handler(struct regs *r);
void mouse_printpos(void);
void mouse_installer(void);

typedef enum MouseCommands
{
    MOUSE_ACK = 0xFA,
    MOUSE_IDENTITY = 0xF2,
    MOUSE_ENABLE_PACKETS = 0xF4,
    MOUSE_DISABLE_DATA = 0xF5,
    MOUSE_READ_PORT = 0x60,
    MOUSE_WRITE_PORT = 0x64,
} MouseCommands;


uint8_t offset;
uint8_t buffer[3];
uint8_t mouse_key;
int16_t mouse_x = 40; 
int16_t mouse_y = 12;

void mouse_wait(unsigned char type)
{
    unsigned int time_o = 100000;
    if (type == 0)
    {   
        while (--time_o)
        {
            if ((inportb(0x64) & 1) == 1)
            {
                break;
            }
        }
        return;
    }
    else
    {
        while (--time_o)
        {
            if ((inportb(0x64) & 2) == 0)
            {
                break;
            }
        }
        return;
    }
}

uint8_t mouse_ctrl_status(void)
{
    mouse_wait(0);
    return inportb(0x64);
}

void mouse_send_cmd(uint8_t cmd)
{
    while (1)
   {
       if ((mouse_ctrl_status() & 2) == 0)
      {
           break;
      }
   }
    outportb(0x64, cmd);
}

void mouse_send_data(uint8_t data)
{
    mouse_wait(1);
    outportb(0x64, 0xD4);
    mouse_wait(1);
    outportb(0x60, data);
}



uint8_t mouse_read_data(void)
{
    mouse_wait(0);
    return inportb(0x60);
}

/*
None    Ancient AT keyboard with translation enabled in the PS/Controller (not possible for the second PS/2 port)
0x00    Standard PS/2 mouse
0x03    Mouse with scroll wheel
0x04    5-button mouse
0xAB, 0x41 or 0xAB, 0xC1    MF2 keyboard with translation enabled in the PS/Controller (not possible for the second PS/2 port)
0xAB, 0x83    MF2 keyboard
*/
uint8_t mouse_type(void)
{
    mouse_send_cmd(MOUSE_DISABLE_DATA);
    if (mouse_read_data() == MOUSE_ACK)
    {
        mouse_send_cmd(MOUSE_IDENTITY);
        if (mouse_read_data() == MOUSE_ACK)
            return mouse_read_data();
    }
}

void mouse_handler(struct regs *r)
{
    uint8_t __status = mouse_ctrl_status();
    if (!(__status & 0x20))
        return;
    buffer[offset] = mouse_read_data();
    offset = (offset + 1) % 3;

    if (offset == 0)
    {
        mouse_key = buffer[0];
        mouse_x += buffer[1] - (0x100 & (buffer[0] << (8-4)));
        if (mouse_x < 0) mouse_x = 0;
        if (mouse_x >= 80) mouse_x = 79;

        mouse_y -= buffer[2] - (0x100 & (buffer[0] << (8-5)));
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_y >= 25) mouse_y = 24;
    }
    outportb(0xA0, 0x20);
    outportb(0x20, 0x20);
    mouse_printpos();

}

void mouse_get_pos(int8_t x, int8_t y)
{
    x = mouse_x;
    y = mouse_y;
}

MOUSE_DATA mouse_get_key(void)
{
    for (uint8_t cout = 0; cout < 3; ++cout)
    {
        if ((buffer[0] & (0x01 << cout)) != (mouse_key & (0x01 << cout)))
        {
            return MOUSE_RIGHT_KEY;
        }
    }
}

void mouse_printpos(void)
{
    print("X: ");
    print(itoa(mouse_x, 10)); 
    print(" Y: ");
    print(itoa(mouse_y, 10));
    if (mouse_get_key() == MOUSE_RIGHT_KEY)
    {
        print("  Right key!");
    }
    else if (mouse_get_key() == MOUSE_LEFT_KEY)
    {
        print("  Left key!");
    }
   
    print("\n");
}

void mouse_installer(void)
{
   uint8_t status = 0;
   
    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT,0xA8);

    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT,0x20);

    mouse_wait(0);
    status = (inportb(MOUSE_READ_PORT) | 2);

    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT, 0x60);

    mouse_wait(1);
    outportb(MOUSE_READ_PORT, status);

    //set sample rate
    mouse_send_data(0xF3);
    mouse_read_data();

    mouse_send_data(200);
    mouse_read_data();

    //set sample rate
    mouse_send_data(0xF3);
    mouse_read_data();

    mouse_send_data(200);
    mouse_read_data();

    //set sample rate
    mouse_send_data(0xF3);
    mouse_read_data();

    mouse_send_data(80);
    mouse_read_data();

    //start sending packets
    mouse_send_data(MOUSE_ENABLE_PACKETS);
    mouse_read_data();

    irq_install_handler(12, mouse_handler);
}