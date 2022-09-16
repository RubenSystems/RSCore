//
//  ArrayWindow.h
//  RSvIDXv2
//
//  Created by Ruben Ticehurst-James on 09/09/2022.
//

#ifndef ArrayWindow_h
#define ArrayWindow_h

#include "Allocator.h"

namespace core {
	template <typename T>
	class ArrayWindow {
		
		public:
			ArrayWindow(T* _data,
						typename Allocator<T>::index_type _start,
						typename Allocator<T>::index_type _end,
						typename Allocator<T>::index_type _used_size = 0): start(_start), end(_end), used_size(_used_size) {
				data = _data;
			}
		
		
			T & operator[](typename Allocator<T>::index_type index) {
				if (index + start > end) {
					throw std::runtime_error("[ARRAY WINDOW] - index out of bounds");
				}
				return data[index + start];
			}
		
			T operator[](typename Allocator<T>::index_type index) const  {
				return operator[](index);
			}
		
			typename Allocator<T>::index_type size(){
				return end - start;
			}
		
			void set_used_size(int _used_size) {
				used_size = _used_size;
			}
		
		private:
			T * data;
			typename Allocator<T>::index_type start;
			typename Allocator<T>::index_type used_size;
			typename Allocator<T>::index_type end;
		
	};
}


#endif /* ArrayWindow_h */
