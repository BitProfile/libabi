

namespace Ethereum{namespace ABI{


template<class T>
Arguments & Arguments::operator()(const T &val)
{
    add(val);
    return *this;
}


template<size_t size>
void Arguments::add(const boost::array<unsigned char, size> &val)
{
    addFixedVar(_serializer.serializeFixedData(val.data(), val.size()));
}


template<class T, size_t size>
void Arguments::add(const boost::array<T, size> &val)
{
    for(typename boost::array<T, size>::iterator it=val.begin(), end=val.end(); it!=end; ++it)
    {
        addFixedVar(_serializer.serialize(*it));
    }
}


template<size_t size>
void Arguments::add(const boost::array<std::string, size> &)
{
    throw std::runtime_error("string array is not implemented");
}


template<class T>
void Arguments::add(const std::vector<T> &val)
{
    std::string result = _serializer.serialize(uint256_t(val.size()));
    for(typename std::vector<T>::iterator it=val.begin(), end=val.end(); it!=end; ++it)
    {
        result += _serializer.serialize(*it);
    }
    addDynamicVar(result);
}



}}
