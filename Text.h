//
//  Text.h
//  RSwDE
//
//  Created by Ruben Ticehurst-James on 29/06/2022.
//

#ifndef Text_h
#define Text_h

/*
 This is what most would describe as a string.
 
 */
class Text {
	
	public:
		Text(const char * string) {
			unsigned int size = (unsigned int)strlen(string);
			data = new char[size + 1];
			data[size] = '\0';
			strcpy(data, string);
			this->stringSize = size;
			
		}
	
		~Text() {
			delete data;
		}
	
		Text operator + (const Text & other) {
			char buffer [stringSize + other.size() + 1];
			strcpy(buffer, data);
			strcat(buffer, other.data);
			buffer[stringSize + other.size()] = '\0';
			return buffer;
		}
	
		unsigned int size() const {
			return stringSize;
		}
		
		
		
	private:
		char * data;
		int stringSize;
};

#endif /* Text_h */
