#ifndef DISTANCE_H
#define DISTANCE_H

namespace mylib 
{ 
    template<class It>
    constexpr typename std::iterator_traits<It>::difference_type 
    do_distance(It first, It last, std::input_iterator_tag)
    {
        typename std::iterator_traits<It>::difference_type result = 0;
        while (first != last) {
            ++first;
            ++result;
        }
        return result;
    }
    
    template<class It>
    constexpr 
    typename std::iterator_traits<It>::difference_type 
    do_distance(It first, It last, std::random_access_iterator_tag)
    {
        return last - first;
    }
    template<class It>
    constexpr typename std::iterator_traits<It>::difference_type 
    distance(It first, It last)
    {
        return mylib::do_distance(first, last,
            typename std::iterator_traits<It>::iterator_category());
    }

} // namespace mylib
 
#endif //DISTANCE_H