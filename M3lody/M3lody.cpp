//Comment to exit debug mode
//#define DEBUG 1
#define SERIAL_FREQ 9600


#include <PS2KeyAdvanced.h>
#include <MIDI.h>
#include "M3lody.h"
#include "M3lody_Const.h"
#include "KeyboardMapping.h"
#define VELOCITY 127

MIDI_CREATE_DEFAULT_INSTANCE();
PS2KeyAdvanced keyboard;
uint8_t playing[10] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
uint8_t playingcount;

M3lody::M3lody(uint8_t clockPin, uint8_t dataPin, uint8_t channel)
{
  _channel = channel;
  octave = 0;
  playingcount=0;
  keyboard.begin( dataPin, clockPin );
  keyboard.setNoRepeat(1);
  keyboard.setNoBreak(0);
}

M3lody::~M3lody()
{
}

bool M3lody::init(){
  #ifdef DEBUG
    Serial.begin(SERIAL_FREQ);
    Serial.println( "M3lody is awake" );
  #else
    MIDI.begin(_channel);
  #endif
}

bool M3lody::update()
{
  if( keyboard.available( ) )
  {
    manageKey(keyboard.read( ));
  }
}

bool M3lody::manageKey(uint16_t key)
{
  uint16_t command=keyconfig[CODE(key)-1];
  #ifdef DEBUG
    Serial.print( "KEY " );
    Serial.print( "Status Bits " );
    Serial.print( STATUS(key), HEX );
    Serial.print( "  Code " );
    Serial.print( CODE(key) , HEX );
    Serial.print( "  command " );
    Serial.print( command , HEX );
    Serial.print( "  pressed " );
    Serial.print( isKeyPressed(STATUS(key)) , HEX );
    Serial.print( "  action " );
    Serial.print(ACTION, HEX);
    uint8_t counter = 0;
    while(counter<playingcount){
      Serial.print(playing[counter]);
      Serial.print("   ");
      counter++;
    }
    Serial.println("");
  #endif
  if(isKeyPressed(STATUS(key))){
    switch(ACTION)
    {
      case ACTION_NOT_IMPLEMENTED:
        #ifdef DEBUG
          Serial.println("Not Implemented");
        #endif
        break;
      case ACTION_NOTE:
        playNote(VALUE+octave);
        break;
      case ACTION_PROGRAM_CHANGE:
        MIDI.sendProgramChange(VALUE, _channel);
        break;
      case ACTION_CONTROL_CHANGE:
        //trasformare in un array di controlli
        //switch(VALUE){
        //  case num:
        //    MIDI.sendControlChange(ControlNumber, ControlValue, _channel);
        //}
        break;
      case ACTION_PITCH_BEND:
        MIDI.sendPitchBend((int)VALUE, _channel);
        break;
      case ACTION_AFTER_TOUCH:
        MIDI.sendAfterTouch(VALUE, _channel);
        break;
      case ACTION_SONG_POSITION:
        MIDI.sendSongPosition(VALUE);
        break;
      case ACTION_SONG_SELECT:
        MIDI.sendSongSelect(VALUE);
        break;
      case ACTION_RT_CLOCK:
        MIDI.sendClock();
        break;
      case ACTION_RT_START:
        MIDI.sendStart();
        break;
      case ACTION_RT_STOP:
        MIDI.sendStop();
        break;
      case ACTION_RT_TICK:
        MIDI.sendTick();
        break;
      case ACTION_RT_CONTINUE:
        MIDI.sendContinue();
        break;
      case ACTION_CUSTOM:
        while(playingcount>0){
          MIDI.sendNoteOff(VALUE+octave,VELOCITY,_channel);
          playingcount--;
        }
        if(VALUE==1){
          #ifdef DEBUG
            Serial.println("Add octave");
          #endif
          if(octave<7*12)
            octave+=12;
        }
        else if(VALUE==2){
          #ifdef DEBUG
            Serial.println("Minus octave");
          #endif
          if(octave>0)
            octave-=12;
        }
       break;
      default:
        #ifdef DEBUG
          Serial.println("Status invalid");
        #endif
        return false;
        break;
    }
  }
  else if (ACTION==ACTION_NOTE){
     stopNote(VALUE+octave);
  }
}

bool M3lody::canPlay(uint8_t note){
  if(playingcount>9)
    return false;
  uint8_t counter=0;
  while(counter<playingcount){
    if(playing[counter]==note)
      return false;
    counter++;
  }
  return true;
}

void M3lody::playNote(uint8_t note){
  if(canPlay(note)){
    #ifdef DEBUG
      Serial.print("NoteON   ");
      Serial.print(note, HEX);
      Serial.print("   Velocity    ");
      Serial.print(VELOCITY, HEX);
      Serial.print("     channel    ");
      Serial.println(_channel, HEX);
    #else
      MIDI.sendNoteOn(note,VELOCITY, _channel);
    #endif
    playing[playingcount]=note;
    playingcount+=1;
          
  }
}

void M3lody::stopNote(uint8_t note){
  #ifdef DEBUG
    Serial.print("NoteOFF    ");
    Serial.println(note, HEX);
  #else
    MIDI.sendNoteOff(note,VELOCITY,_channel);
  #endif
  if(playingcount==0)
    return;
  uint8_t counter=0;
  while(counter<playingcount){
    if(playing[counter]==note){
      while(counter<playingcount-1){
        playing[counter]=playing[counter+1];
        counter++;
      }
      playingcount--;
    }
    counter++;
  }
}

bool M3lody::isKeyPressed(uint8_t state)
{
  return state==STATUS_DOWN 
  || state==STATUS_DOWN+CONTROL_OFFSET 
  || state==STATUS_DOWN+CAPS_OFFSET
  || state==STATUS_DOWN+UPPER_OFFSET
  || state==STATUS_DOWN+CONTROL_OFFSET+CAPS_OFFSET
  || state==STATUS_DOWN+CAPS_OFFSET+UPPER_OFFSET
  || state==STATUS_DOWN+CONTROL_OFFSET+CAPS_OFFSET+UPPER_OFFSET;
}

void M3lody::custom(uint8_t value){

}
