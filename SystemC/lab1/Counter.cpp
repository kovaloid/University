#include "Counter.h"

/**
    SC_METHOD of sink:
        increments internal state and proceeds it to output
  */
void Counter::on_tick()
{
    if(rst.read())
    {
        // clean internal state and output on reset
        c = 0;
        state = 0;
    }
    else
    {
        // increment internal state, update state
        state = c++;
    }
}
