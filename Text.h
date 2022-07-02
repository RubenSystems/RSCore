//
//  Text.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Text_h
#define Text_h

#include "Array.h"

#include <string.h>

namespace core {
	class Text : public Array<char> {
		public:
			Text(const char * chararray) : Array<char>((int)strlen(chararray) + 1, 0, false) {
				memmove(&(Array<char>::operator[](0)), &(chararray), sizeof(char) * strlen(chararray));
			}
		
		
	};
}


#endif /* Text_h */
