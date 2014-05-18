#pragma once

#include <boost/program_options.hpp>
#include <boost/noncopyable.hpp>
#include "NSClient++.h"

namespace po = boost::program_options;
class cli_parser : public boost::noncopyable {

	NSClient* core_;
	po::options_description common;
	po::options_description settings;
	po::options_description service;
	po::options_description client;
	po::options_description unittest;
	po::options_description test;

	bool help;
	bool version;
	bool log_debug;
	bool no_stderr;
	std::vector<std::string> log_level;
	std::string settings_store;
	std::vector<std::string> unknown_options;
	
	typedef boost::function<int(int, char**)> handler_function;
	typedef std::map<std::string,handler_function> handler_map;
	typedef std::map<std::string,std::string> alias_map;

	void init_logger();
	handler_map get_handlers();
	alias_map get_aliases();
	bool process_common_options(std::string context, po::options_description &desc);

public:
	cli_parser(NSClient* core);
	int parse(int argc, char* argv[]);

private:
	po::basic_parsed_options<char> do_parse(int argc, char* argv[], po::options_description &desc);

	void display_help();
	int parse_help(int argc, char* argv[]);
	int parse_test(int argc, char* argv[]);
	int parse_settings(int argc, char* argv[]);
	int parse_service(int argc, char* argv[]);
	int parse_client(int argc, char* argv[], std::string module_ = "");
	int parse_unittest(int argc, char* argv[]);
	//int exec_client_mode(client_arguments &args);
	std::string get_description(std::string key);
	std::string describe(std::string key);
	std::string describe(std::string key, std::string alias);
};
