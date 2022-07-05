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
			Text() : Text("") {
				
			}
		
			Text(const char * chararray) : Array<char>((int)strlen(chararray) + 1, 0, false) {
				int length = (int)strlen(chararray);
				strcpy(data, chararray);
				used_size = length + 1;
				operator[](length) = 0;
			}
		

			const char * c_string() const {
				return data;
			}
		
			void operator = (const Text & rhs) {
				int rhsLength = (int)strlen(rhs.data);
				out(rhs.allocated_size << " " << allocated_size << " " << rhsLength);
				
				allocate(rhsLength + 1);
				strcpy(data, rhs.data);
				data[rhsLength] = 0;
			}
		
			void operator += (const Text & rhs) {
				allocate(size() + rhs.size() + 1);
				strcat(data, rhs.data);
			}

			Text operator + (const Text & rhs) const {
				Text newText (c_string());
				newText += rhs;
				return newText;
			}
	};
}


#endif /* Text_h */
