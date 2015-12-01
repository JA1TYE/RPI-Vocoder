#ifndef RPILIB_MIDI_H
#define RPILIB_MIDI_H
 
int midi_Init(void);
void midi_end(void);
int midi_available(void);
int midi_recv(void);

#endif
