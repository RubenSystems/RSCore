//
//  Array.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Array_h
#define Array_h

#include "Allocator.h"
#include "Output.h"

namespace core {
	template <typename T>
	class Array: public Allocator<T> {
		public:
			Array(typename Allocator<T>::index_type initial_size = 4) {
				Allocator<T>::allocate(initial_size);
			}
		
			Array(T data [], int size) {
				
				Allocator<T>::data = data;
				data = nullptr;
			}
		
			
		
			~Array() {
				if (Allocator<T>::data == nullptr)
					return;
				
				for (int i = 0; i < currentSize; i ++) {
					Allocator<T>::data[i].~T();
				}
			}
		
			Array(const Array & copy) : currentSize(copy.currentSize) {
				Allocator<T>::allocate(copy.Allocator<T>::allocatedSize());
				for(int i = 0; i < copy.currentSize; i ++) {
					Allocator<T>::data[i] = copy.Allocator<T>::data[i];
				}
			}

			Array(Array && move) : currentSize(move.currentSize) {
				Allocator<T>::data = move.Allocator<T>::data;
				move.Allocator<T>::data = nullptr;
			}

			Array & operator = (const Array & copy) {
				Allocator<T>::allocate(copy.Allocator<T>::allocatedSize());
				for(int i = 0; i < copy.currentSize; i ++) {
					Allocator<T>::data[i] = copy.Allocator<T>::data[i];
				}
				
				currentSize = copy.currentSize;
				return *this;
			}

			Array & operator = (Array && move) {
				Allocator<T>::data = move.Allocator<T>::data;
				move.Allocator<T>::data = nullptr;
				
				currentSize = move.currentSize;
				return *this;
			}

			void add (const T & item) {
				if (currentSize >= Allocator<T>::allocated) {
					Allocator<T>::allocate(Allocator<T>::allocated * enlargement);
				}
				Allocator<T>::operator[](currentSize ++) = item;
			}
		
			void add (T && item) {
				if (currentSize >= Allocator<T>::allocated) {
					Allocator<T>::allocate(Allocator<T>::allocated * enlargement);
				}
				
				// TODO: remove std lib
				Allocator<T>::operator[](currentSize ++) = std::move(item);
			}
		
			// Construct and add (if you can come up with a better name email ruben.t.j@icloud.com)
			template <typename... args>
			void conadd(args && ... construction_parameters) {
				if (currentSize >= Allocator<T>::allocated) {
					Allocator<T>::allocate(Allocator<T>::allocated * enlargement);
				}
				
				new(&(Allocator<T>::data[currentSize ++])) T(std::forward<T>(construction_parameters)...);
			};
		
			typename Allocator<T>::index_type size() const {
				return currentSize;
			}
			
			
		
		private:
			static const int enlargement = 2;
			typename Allocator<T>::index_type currentSize = 0;
		
	};
}

#endif /* Array_h */
