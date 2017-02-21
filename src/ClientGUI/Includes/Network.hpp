#pragma once

#include "Includes/IniParser.hpp"
#include "Includes/HttpClient.hpp"
#include <memory>

boost::asio::io_service io_service;

IniParser pIni_parser("config.ini");
auto params = pIni_parser.fGetParams();

std::shared_ptr<HttpClient> http_client( new HttpClient(io_service, params["client.host"], params["client.port"]));

