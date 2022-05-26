#ifndef UTILITY_H_
#define UTILITY_H_

namespace mylib
{
    size_t strlen(const char *s)
    {
        size_t count = 0;
        while(*s!='\0')
        {
            count++;
            s++;
        }
        return count;
    }
} // namespace mylib
 
// int mylib::String::stoi() const
// {
//      vector<int> vec;
//  	   for (int i = 0; i < m_size; ++i) 
//         {
//  		   vec.push_back(m_buffer[i] - '0');
//  	   }
//  	   int res = 0;
//  	   for (int i = vec.size() - 1; i >= 0; --i) 
//        {
//  		   res += vec[i] * pow(10, vec.size() - i - 1);
// 	   }
// 	   return res;
// }



#endif //UTILITY_H_