//
//  Array.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 02/07/2022.
//

#ifndef Array_h
#define Array_h

#include "Output.h"
#include "Allocator.h"
#include "ArrayWindow.h"

namespace core {
	template <class T, class Alloc = Allocator<T>>
	class Array: public Alloc {
		public:
			Array() {
				
			}
		
			Array(typename Alloc::index_type initial_size) {
				Alloc::allocate(initial_size);
			}
		
			Array(std::initializer_list<T> initaliser) : currentSize(initaliser.size()) {
				Alloc::allocate(initaliser.size() + enlargement);
				
				for (int i = 0; i < initaliser.size(); i ++) {
					Alloc::data[i] = *(T *)std::move(initaliser.begin() + i);
				}
			}
		
			Array(T data [], typename Alloc::index_type size): currentSize(size) {
				Alloc::allocate(size + enlargement);
				
				for (int i = 0; i < size; i ++) {
					Alloc::data[i] = data[i];
				}
			}
		
			~Array() {
				if (Alloc::data == nullptr)
					return;
				
				for (int i = 0; i < currentSize; i ++) {
					Alloc::data[i].~T();
				}
			}
		
			Array(const Array & copy) : currentSize(copy.currentSize) {
				Alloc::allocate(copy.Alloc::allocatedSize());
				for(int i = 0; i < copy.currentSize; i ++) {
					Alloc::data[i] = copy.Alloc::data[i];
				}
			}

			Array(Array && move) : currentSize(move.currentSize), Alloc(std::move(move)) {
//				Alloc::data = move.Alloc::data;
//				move.Alloc::data = nullptr;
			}

			Array & operator = (const Array & copy) {
				Alloc::allocate(copy.Alloc::allocatedSize());
				for(int i = 0; i < copy.currentSize; i ++) {
					Alloc::data[i] = copy.Alloc::data[i];
				}
				currentSize = copy.currentSize;
				return *this;
			}

			Array & operator = (Array && move) {
				Alloc::operator=(std::move(move));
				
				currentSize = move.currentSize;
				return *this;
			}

			void add (const T & item) {
				if (currentSize >= Alloc::allocated) {
					Alloc::allocate(Alloc::allocated * enlargement);
				}
				Alloc::operator[](currentSize ++) = item;
			}
		
			void add (T && item) {
				if (currentSize >= Alloc::allocated) {
					Alloc::allocate((Alloc::allocated == 0 ? 1 : Alloc::allocated) * enlargement);
				}
				
				Alloc::operator[](currentSize ++) = std::move(item);
			}
			
		
			ArrayWindow<T> subarray(typename Alloc::index_type start, typename Alloc::index_type end) {
				return ArrayWindow<T>(Alloc::data, start, end);
			}
		
			void resize(typename Alloc::index_type new_size) {
				if (currentSize != new_size) {	
					Alloc::allocate(new_size + enlargement);
					currentSize = new_size;
				}
			}
			
			// Construct and add (if you can come up with a better name email ruben.t.j@icloud.com)
			template <typename... args>
			void conadd(args && ... construction_parameters) {
				if (currentSize >= Alloc::allocated) {
					Alloc::allocate(Alloc::allocated * enlargement);
				}
				
				new(&(Alloc::data[currentSize ++])) T(std::forward<args>(construction_parameters)...);
			};
		
			typename Alloc::index_type size() const {
				return currentSize;
			}
			
			
		
		protected:
			static const int enlargement = 2;
			typename Alloc::index_type currentSize = 0;
		
	};
}

#endif /* Array_h */
