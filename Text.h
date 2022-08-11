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
				strncpy(data, copy.data, copy.currentSize);
			}
			
			Text(Text && move): currentSize(move.currentSize) {
				data = move.data;
				allocated = move.allocated;
				move.data = nullptr;
			}
			
			Text & operator = (const Text & copy) {
				allocate(copy.allocatedSize());
				strncpy(data, copy.data, copy.currentSize);
				currentSize = copy.currentSize;
				return *this;
			}
			
			Text & operator = (Text && move) {
				data = move.data;
				move.data = nullptr;
				currentSize = move.currentSize;
				return *this;
			}
		
			bool operator == (const Text & rhs) {
				return strcmp(c_string(), rhs.c_string());
			}


		
			index_type size() const {
				return currentSize;
			}
		
			const char * c_string() const {
				return data;
			}
		
			Text & operator += (const Text & rhs) {
				index_type current_allocated_size = allocatedSize();
				allocateTextForSize(current_allocated_size + rhs.size());
				strncat(data, rhs.data, current_allocated_size + rhs.size() - 1);
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

namespace std {
	template <> struct hash<core::Text> {
		// djb2
		size_t operator()(const core::Text & text) const {
			unsigned long int hash;
			int c;
			
			hash = 5381;
			const char * c_string = text.c_string();
			for (int i = 0; i < text.size(); i ++) {
				char x = c_string[i];
				c = x;
				hash = ((hash << 5) + hash) + c;
				/* hash * 33 + c */
			}
			return hash;
		}
	};
}

#endif /* Text_h */
