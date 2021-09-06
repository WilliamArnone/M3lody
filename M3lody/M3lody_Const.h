#define STATUS(value) value>>8
#define CODE(value) (value&0xFF)
#define ACTION command>>8
#define VALUE (command&0xFF)
#define STATUS_DOWN 0
#define STATUS_UP 0x80
#define CONTROL_OFFSET 0x1
#define CAPS_OFFSET 0x10
#define UPPER_OFFSET 0x40

#define ACTION_NOT_IMPLEMENTED 0
#define ACTION_NOTE 0x1
//what instrument should be played
#define ACTION_PROGRAM_CHANGE 0x2
//changes synth control
#define ACTION_CONTROL_CHANGE 0x3
#define ACTION_PITCH_BEND 0x4
//used for vibrato
#define ACTION_AFTER_TOUCH 0x5
#define ACTION_SONG_POSITION 0x6
#define ACTION_SONG_SELECT 0x7
#define ACTION_RT_CLOCK 0x8
#define ACTION_RT_START 0x9
#define ACTION_RT_STOP 0xA
#define ACTION_RT_TICK 0xB
#define ACTION_RT_CONTINUE 0xC
#define ACTION_CUSTOM 0xD

#define c1 12
#define C1 13
#define d1 14
#define D1 15
#define e1 16
#define f1 17
#define F1 18
#define g1 19
#define G1 20
#define a1 21
#define A1 22
#define b1 23
#define c2 24
#define C2 25
#define d2 26
#define D2 27
#define e2 28
#define f2 29
#define F2 30
#define g2 31
#define G2 32
#define a2 33
#define A2 34
#define b2 35
#define c3 36
#define C3 37
#define d3 38
#define D3 39
#define e3 40
#define f3 41
#define F3 42
#define g3 43
#define G3 44
#define a3 45
#define A3 46
#define b3 47




//Use these for mapping
#define none ACTION_NOT_IMPLEMENTED
#define note(value) (ACTION_NOTE<<8)+value
//what instrument should be played
#define program_change(value) (ACTION_PROGRAM_CHANGE<<8)+value
//changes synth control
#define control_change(index) (ACTION_CONTROL_CHANGE<<8)+index
#define pitch_bend(value) (ACTION_PITCH_BEND<<8)+value
//used for vibrato
#define after_touch(value) (ACTION_AFTER_TOUCH<<8)+value
#define song_position(value) (ACTION_SONG_POSITION<<8)+value
#define song_select(value) (ACTION_SONG_SELECT<<8)+value
#define rt_clock() ACTION_RT_CLOCK<<8
#define rt_start() ACTION_RT_START<<8
#define rt_stop() ACTION_RT_STOP<<8
#define rt_tick() ACTION_RT_TICK<<8
#define rt_continue() ACTION_RT_CONTINUE<<8
#define custom_action(value) (ACTION_CUSTOM<<8)+value
