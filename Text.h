//
//  Text.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Text_h
#define Text_h

#include "Allocator.h"
#include "Array.h"

#include <string.h>

namespace core {
	class Text: public Allocator<char> {
		public:
			Text(const char * text) {
				allocateText(text);
				strcpy(data, text);
			}
		
			Text(const Text & copy): currentSize(copy.currentSize) {
				allocate(copy.allocatedSize());
				strcpy(data, copy.data);
			}
			
			Text(Text && move): currentSize(move.currentSize) {
				data = move.data;
				move.data = nullptr;
			}
			
			Text & operator = (const Text & copy) {
				allocate(copy.allocatedSize());
				strcpy(data, copy.data);
				currentSize = copy.currentSize;
				return *this;
			}
			
			Text & operator = (Text && move) {
				data = move.data;
				move.data = nullptr;
				currentSize = move.currentSize;
				return *this;
			}

		
			index_type size() const {
				return currentSize;
			}
		
			const char * c_string() const {
				return data;
			}
		
			Text & operator += (const Text & rhs) {
				allocateTextForSize(allocatedSize() + rhs.size());
				strcat(data, rhs.data);
				data[allocatedSize() + rhs.size()] = 0;
				return *this;
			}
			
			Array<Text> split(const char * at) {
				Array<Text> result;
				char * buffer;
				buffer = strtok(data, at);
				do {
					if (buffer) {
						result.add(buffer);
					} else {
						break;
					}
					buffer = strtok(NULL, at);
				} while (true);
				return result;
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
