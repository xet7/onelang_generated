#include <one.hpp>
#include <iostream>
#include <vector>

class ICustomDecoder {
  public:
    virtual vec<int> decode(vec<int> src) = 0;
};

class XorByte : public ICustomDecoder {
  public:
    int xor_value;

    XorByte(int xor_value) {
        this->xor_value = xor_value;
    }

    vec<int> decode(vec<int> src) {
        auto dest = make_shared<vector<int>>(initializer_list<int>{  });
        
        for (int i = 0; i < src->size(); i++) {
            dest->push_back(src->at(i) ^ this->xor_value);
        }
        
        return dest;
    }

  private:
};

class Base64 : public ICustomDecoder {
  public:
    vec<int> decode(vec<int> src) {
        auto dest = make_shared<vector<int>>(initializer_list<int>{  });
        
        // 4 base64 chars => 3 bytes
        for (int i = 0; i < src->size(); i += 4) {
            int ch0 = this->decodeChar(src->at(i));
            int ch1 = this->decodeChar(src->at(i + 1));
            int ch2 = this->decodeChar(src->at(i + 2));
            int ch3 = this->decodeChar(src->at(i + 3));
            
            int trinity = (ch0 << 18) + (ch1 << 12) + (ch2 << 6) + (ch3);
            
            dest->push_back(trinity >> 16);
            dest->push_back((trinity >> 8) & 0xff);
            dest->push_back(trinity & 0xff);
        }
        
        return dest;
    }
    
    int decodeChar(int ch) {
        int value = -1;
        if (ch >= 65 && ch <= 90) {
            // `A-Z` => 0..25
            value = ch - 65;
        } else if (ch >= 97 && ch <= 122) {
            // `a-z` => 26..51
            value = ch - 97 + 26;
        } else if (ch >= 48 && ch <= 57) {
            // `0-9` => 52..61
            value = ch - 48 + 52;
        } else if (ch == 43 || ch == 45) {
            // `+` or `-` => 62
            value = 62;
        } else if (ch == 47 || ch == 95) {
            // `/` or `_` => 63
            value = 63;
        } else if (ch == 61) {
            // `=` => padding
            value = 0;
        } else {
        }
        return value;
    }

  private:
};

class TestClass {
  public:
    void testMethod() {
        auto src1 = make_shared<vector<int>>(initializer_list<int>{ 4, 5, 6 });
        auto decoder = make_shared<XorByte>(0xff);
        auto dst1 = decoder->decode(src1);
        for (auto it = dst1->begin(); it != dst1->end(); ++it) {
            auto x = *it;
            cout << x << endl;
        }
        
        cout << string("|") << endl;
        
        auto src2 = make_shared<vector<int>>(initializer_list<int>{ 97, 71, 86, 115, 98, 71, 56, 61 });
        auto decoder2 = make_shared<Base64>();
        auto dst2 = decoder2->decode(src2);
        for (auto it = dst2->begin(); it != dst2->end(); ++it) {
            auto x = *it;
            cout << x << endl;
        }
    }

  private:
};

int main()
{
    try {
        TestClass c;
        c.testMethod();
    } catch(std::exception& err) {
        cout << "Exception: " << err.what() << '\n';
    }
    return 0;
}