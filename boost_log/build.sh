set -x
clang++ -DBOOST_LOG_DYN_LINK main.cc -lboost_log -lboost_log_setup \
		-lboost_thread -lboost_system -pthread -std=c++11 -o foo
