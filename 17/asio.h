#ifndef ASIO_H
#define ASIO_H

#ifndef USE_BOOST_ASIO
#if __has_include(<asio.hpp>)
#define USE_BOOST_ASIO 0
#elif __has_include(<boost/asio.hpp>)
#define USE_BOOST_ASIO 1
#else
#error "Asio is not detected"
#endif
#endif

#if USE_BOOST_ASIO
#include <boost/asio.hpp>               // boost::asio::io_context
#include <boost/system/error_code.hpp>  // boost::sytstem::error_code
namespace asio = boost::asio;
using boost::system::error_code;
#else
#include <asio.hpp>                     // asio::io_context
#include <system_error>                 // std::error_code
using std::error_code;
#endif

#endif // ASIO_H
