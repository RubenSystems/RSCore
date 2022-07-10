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
			
				Array(T type [], int size) {
					
					Allocator<T>::allocate(size);
					memmove(Allocator<T>::data, type, sizeof(T) * size);
				}
			
				~Array() {
					if (Allocator<T>::data == nullptr)
						return;
					
					for (int i = 0; i < currentSize; i ++) {
						Allocator<T>::data[i].~T();
					}
				}
			
				Array(const Array & copy) : currentSize(copy.currentSize) {
					
				}

				Array(Array && move) : currentSize(move.currentSize) {

				}

				Array & operator = (const Array & copy) {
					currentSize = copy.currentSize;
				}

				Array & operator = (Array && move) {
					currentSize = move.currentSize;
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

