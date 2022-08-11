//
//  Dictionary.h
//  RSCore
//
//  Created by Ruben Ticehurst-James on 09/08/2022.
//

#ifndef Dictionary_h
#define Dictionary_h

#include "Array.h"

namespace core {
	
	template <typename Key, typename Value>
	struct DictionaryNode {
		Key key;
		Value value;
	};
	
	template <
		typename Key,
		typename Value,
		typename hash_function = std::hash<Key>
	>
	class Dictionary : protected Array<Array<DictionaryNode<Key, Value>>> {
		
		private:
			typedef DictionaryNode<Key, Value> T;
			typedef Array<T> parent;
			
		
		public:
			
			// Null init every entry
			Dictionary(int number_of_tables = 200) : Array<Array<T>>(number_of_tables) {
				
			}
		
			//Init every entry
			template <typename... args>
			Dictionary(int number_of_tables = 200, args && ... construction_parameters) : Array<Array<T>>(number_of_tables) {
				for (int i = 0; i < number_of_tables; i ++) {
					new(&(Array<Array<T>>::operator[](i))) T(std::forward<T>(construction_parameters)...);
				}
				
			};
		
			Dictionary(const Dictionary & copy) {
				
			}
			
			Dictionary(Dictionary && move) {
				
			}
			
			Dictionary & operator = (const Dictionary & copy) {
				
			}
			
			Dictionary & operator = (Dictionary && move) {
				
			}

			
		
			void add(const T & value) {
				typename Allocator<T>::index_type hash = hasher(value.key) % Allocator<parent>::allocated;
				Array<T> & result = Allocator<parent>::operator[](hash);
				
				for (int i = 0; i < result.size(); i ++){
					if (result[i].key == value.key) {
						result[i] = value;
						return;
					}
				}
				result.add(value);
			}
		
			void add(T && value) {
				typename Allocator<T>::index_type hash = hasher(value.key) % Allocator<parent>::allocated;
				Array<T> & result = Allocator<parent>::operator[](hash);
				
				for (int i = 0; i < result.size(); i ++){
					if (result[i].key == value.key) {
						result[i] = std::move(value);
						return;
					}
				}
				result.add(value);
			}
		
			Value & operator[](const Key & key) {
				typename Allocator<T>::index_type hash = hasher(key) % Allocator<parent>::allocated;
				Array<T> & result = Allocator<parent>::operator[](hash);
				
				for (int i = 0; i < result.size(); i ++){
					if (result[i].key == key) {
						return result[i].value;
					}
				}
				throw std::runtime_error("[DICTIONARY] - key does not exist");
			}
		
			Value operator[](const Key & key) const {
				return operator[](key);
			}
		
		private:
			hash_function hasher;
	};
}

#endif /* Dictionary_h */
