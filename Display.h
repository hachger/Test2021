/*
 * Display.h
 *
 * Created: 08/18/21 16:37:10
 *  Author: German
 */ 
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#define WIDTH	128		/*!<Descripcion del WIDTH */
#define HEIGHT	64

/**brief Titulo breve
*	Descripcion mas detallada
*/
void refreshDisplay1();

/**brief Titulo breve
*	Descripcion mas detallada
*	
*	param [in] param1: descripcion
*	param [out] param2: descripcion
*
*	return explicar que retorna
*/
int refreshDisplay(uint8_t param1, uint8_t *param2);



#endif /* DISPLAY_H_ */