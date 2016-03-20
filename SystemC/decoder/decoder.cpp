#include "Decoder.h"

void Decoder::on_tick()
{
    if(enable.read())
    {
		tmp = input;

		/*switch (tmp)
		{
			case 0: output = "00000001"; break;
			case 1: output = "00000010"; break;
			case 2: output = "00000100"; break;
			case 3: output = "00001000"; break;
			case 4: output = "00010000"; break;
			case 5: output = "00100000"; break;
			case 6: output = "01000000"; break;
			case 7: output = "10000000"; break;
			default: output = "00000000"; break;
		}*/

		int N = tmp;
		output = (00000001<<N)|(00000001>>(8-N));
    }
    else
    {
		output = "00000000";
    }
}
