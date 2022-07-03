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
		
			Text operator + (const Text & rhs) {
				char buffer [size() + rhs.size() + 1];
				strcpy(buffer, data);
				strcat(buffer, rhs.data);
				buffer[size() + rhs.size()] = 0;
				return buffer;
			}
			
			const char * c_string() {
				return data;
			}

		
		
	};
}


#endif /* Text_h */
