#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define ROW1 D21
#define ROW2 D22
#define ROW3 D23

#define COL1 D18
#define COL2 D19
#define COL3 D20

int Key_Scan(void);
int Key_Check(void);

extern char g_Key;


#endif