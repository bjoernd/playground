#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/logger.hpp>

int main(int, char*[])
{
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";

	auto sink = boost::log::add_console_log();
	boost::log::formatter fm =
	   	boost::log::expressions::stream
			<< "["
			<< boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S.%f")
			<< "] "
			<< boost::log::expressions::message
			;
	boost::log::add_common_attributes();
	sink->set_formatter(fm);

	boost::log::sources::logger lg;
	BOOST_LOG(lg) << "(" << std::setw(20) << __func__ << ")" << " Hello world";
	BOOST_LOG_SEV(lg, 3) << "Hello world";
	BOOST_LOG(lg) << "Hello world";
	BOOST_LOG(lg) << "Hello world";

	return 0;
}
