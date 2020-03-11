#ifndef IEXCHANGE_DATA_H
#define IEXCHANGE_DATA_H

#include <boost/shared_ptr.hpp>

namespace ExchangeDataNs
{

class IExchangeData
{
public:
    IExchangeData();
    virtual ~IExchangeData();
};

typedef boost::shared_ptr<IExchangeData> IExchangeDataPtr;

}

#endif // IEXCHANGE_DATA_H
