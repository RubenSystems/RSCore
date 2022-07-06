//
//  Text.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Text_h
#define Text_h

#include "Allocator.h"

#include <string.h>

namespace core {
	class Text: public Allocator<char> {
		public:
			Text(const char * text) {
				allocateText(text);
				strcpy(data, text);
			}
		
			index_type size() const {
				return currentSize;
			}
		
			const char * c_string() const {
				return data;
			}
		
			Text & operator += (const Text & rhs) {
				allocateTextForSize(size() + rhs.size());
				strcat(data, rhs.data);
				return *this;
			}
		
		private:
			index_type currentSize = 0;
		
			void allocateText(const char * text) {
				allocateTextForSize(strlen(text));
			}
		
			void allocateTextForSize(index_type size) {
				currentSize = size;
				allocate(currentSize + 1);
				operator[](currentSize) = 0;
			}
	};
}

#endif /* Text_h */
