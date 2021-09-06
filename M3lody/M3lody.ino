#include "M3lody.h"

//On Arduino Uno: only 2 or 3
#define IRQPIN  3

#define DATAPIN 4
#define CHANNEL 1

M3lody m3lody(IRQPIN, DATAPIN, CHANNEL);

void setup( )
{
  m3lody.init();
}

void loop( )
{
  m3lody.update();
}
